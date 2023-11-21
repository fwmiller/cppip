#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "eth.h"
#include "ports.h"

#define DHCP_PORT_SERVER 67
#define DHCP_PORT_CLIENT 68

struct dhcp_hdr {
    uint8_t op;
    uint8_t htype;
    uint8_t hlen;
    uint8_t hops;
    uint32_t xid;
    uint16_t secs;
    uint16_t flags;
    uint32_t ciaddr;
    uint32_t yiaddr;
    uint32_t siaddr;
    uint32_t giaddr;
};

typedef struct dhcp_hdr *dhcp_hdr_t;

void
dhcp_dump(uint8_t *buf) {
    dhcp_hdr_t dh = (dhcp_hdr_t) buf;

    if (dh->op == 1)
        printf("request");
    else if (dh->op == 2)
        printf("reply");
    else
        printf("UNKNOWN");

    printf(" 0x%08x", dh->xid);

    printf("\r\n");
}

void *
dhcp(void *pthread_arg) {
    class port dhcp_server;
    class port dhcp_client;
    uint8_t buf[ETH_MTU_SIZE];
    int len, n;

    dhcp_server.bind(DHCP_PORT_SERVER);
    dhcp_client.bind(DHCP_PORT_CLIENT);

    for (;;) {
        n = dhcp_server.get_nbufs();
        while (n > 0) {
            memset(buf, 0, ETH_MTU_SIZE);
            len = dhcp_server.receive(buf, ETH_MTU_SIZE);
            if (len < 0)
                break;

            printf("dhcp server ");
            dhcp_dump(buf);
        }
        n = dhcp_client.get_nbufs();
        while (n > 0) {
            memset(buf, 0, ETH_MTU_SIZE);
            len = dhcp_client.receive(buf, ETH_MTU_SIZE);
            if (len < 0)
                break;

            printf("dhcp client ");
            dhcp_dump(buf);
        }
        usleep(20000);  // 20 milliseconds
    }

    /* Not reached */
    return NULL;
}
