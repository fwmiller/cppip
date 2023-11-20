#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "eth.h"
#include "ports.h"

#define DHCP_PORT_1 67
#define DHCP_PORT_2 68

void *
dhcp(void *pthread_arg) {
    class port dhcp_port1;
    class port dhcp_port2;
    uint8_t buf[ETH_MTU_SIZE];
    int len, n;

    dhcp_port1.bind(DHCP_PORT_1);
    dhcp_port2.bind(DHCP_PORT_2);

    for (;;) {
        n = dhcp_port1.get_nbufs();
        while (n > 0) {
            memset(buf, 0, ETH_MTU_SIZE);
            len = dhcp_port1.receive(buf, ETH_MTU_SIZE);
            if (len < 0)
                break;

            printf("dhcp: port %d len %d\r\n", DHCP_PORT_1, len);
            bufdump(buf, len);
        }
        n = dhcp_port2.get_nbufs();
        while (n > 0) {
            memset(buf, 0, ETH_MTU_SIZE);
            len = dhcp_port2.receive(buf, ETH_MTU_SIZE);
            if (len < 0)
                break;

            printf("dhcp: port %d len %d\r\n", DHCP_PORT_2, len);
            bufdump(buf, len);
        }
        usleep(20000);  // 20 milliseconds
    }

    /* Not reached */
    return NULL;
}
