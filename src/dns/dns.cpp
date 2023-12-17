#include "dns.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ports.h"

static void
dns_dump(uint8_t *buf, int buflen) {
    dns_hdr_t dh = (dns_hdr_t) buf;

    bufdump(buf, buflen);

    printf("dns id 0x%04x", reverse_byte_order_short(dh->id));

    uint16_t op = reverse_byte_order_short(dh->op);
    if (op >> 15)
        printf(" RESPONSE");
    else
        printf(" QUERY");

    uint16_t opcode = (op >> 11) & 0x0f;
    uint16_t aa = (op >> 10) & 0x01;
    uint16_t tc = (op >> 9) & 0x01;
    uint16_t rd = (op >> 8) & 0x01;
    uint16_t ra = (op >> 7) & 0x01;
    uint16_t rcode = op & 0x0f;

    printf(" opcode %u", opcode);

    if (aa)
        printf(" AUTH ANSWER");
    if (tc)
        printf(" TRUNCATED");
    if (rd)
        printf(" RECURSION DESIRED");
    if (ra)
        printf(" RECURSION AVAIL");

    printf(" response code %u", rcode);
    printf("\r\n");

    printf("  qdcount %d", reverse_byte_order_short(dh->qdcount));
    printf(" ancount %d", reverse_byte_order_short(dh->ancount));
    printf(" nscount %d", reverse_byte_order_short(dh->nscount));
    printf(" arcount %d\r\n", reverse_byte_order_short(dh->arcount));

    char *q = ((char *) buf) + sizeof(struct dns_hdr);
    int qlen = *((uint8_t *) q);
    while (qlen > 0) {
        printf("  ");
        for (int i = 0; i < qlen; i++)
            printf("%c", q[i + 1]);
        printf("\r\n");

        q += qlen + 1;
        qlen = *((uint8_t *) q);
    }
}

void *
dns(void *pthread_arg) {
    class port dns_client, mdns_client;
    uint8_t buf[ETH_MTU_SIZE];
    int len, n;

    dns_client.bind(53);
    mdns_client.bind(5353);

    for (;;) {
        n = dns_client.get_nbufs();
        while (n > 0) {
            memset(buf, 0, ETH_MTU_SIZE);
            len = dns_client.receive(buf, ETH_MTU_SIZE);
            if (len < 0)
                break;
#if _DEBUG_DNS
            dns_dump(buf, len);
#endif
        }
        n = mdns_client.get_nbufs();
        while (n > 0) {
            memset(buf, 0, ETH_MTU_SIZE);
            len = mdns_client.receive(buf, ETH_MTU_SIZE);
            if (len < 0)
#if _DEBUG_DNS
                printf("receive dns packet failed\r\n");
#endif
            break;
#if _DEBUG_DNS
            dns_dump(buf, len);
#endif
        }
        usleep(20000);  // 20 milliseconds
    }

    /* Not reached */
    return NULL;
}
