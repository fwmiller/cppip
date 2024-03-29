#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "cppip.h"

#include <pcap.h>

extern pcap_t *intf_handl;

void initialize_pcap();
void packet_handler(u_char *param, const struct pcap_pkthdr *header,
                    const u_char *pkt_data);
void *dhcp(void *pthread_arg);
void *dns(void *pthread_arg);

void
set_color_none() {
    printf("\033[0m");
}

void
set_color_cyan() {
    printf("\033[0;36m");
}

int
main() {
    pthread_t dhcp_thread, dns_thread, cli_thread;

    printf("C++ Internet Protocols (");
    set_color_cyan();
    printf("cppip");
    set_color_none();
    printf(")\r\n");

    // Assign initial MAC address to support the initial ARP probe
    // uint8_t ha[ETH_ADDR_LEN] = {0xde, 0xad, 0xbe, 0xef, 0xfe, 0xed};
    // my_addr->set_ha(ha);

    cppip_init();
    pthread_create(&dhcp_thread, NULL, dhcp, NULL);
    pthread_create(&dns_thread, NULL, dns, NULL);
    initialize_pcap();
    pthread_create(&cli_thread, NULL, cli, NULL);

    /* Start the capture */
    pcap_loop(intf_handl, 0, packet_handler, NULL);

    // Not reached

    // Leave the interface adapter handle open so we can write raw packets
    // pcap_close(intf_handl);
    return 0;
}
