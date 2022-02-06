#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "cppip.h"
#include "inq.h"
#include "stats.h"

#include <pcap.h>

static const int INTF_NAME_MAX_LEN = 4096;
static char intf_name[INTF_NAME_MAX_LEN];
pcap_t *intf_handl;

extern class arptab_entry *my_addr;

static void packet_handler(u_char *param, const struct pcap_pkthdr *header,
                           const u_char *pkt_data);

void arptab_init();

int main() {
    pcap_if_t *alldevs;
    pcap_if_t *intf;
    char errbuf[PCAP_ERRBUF_SIZE];
    int inum;
    int i = 0;

    printf("C++ Internet Protocols (cppip)\r\n");

    arptab_init();
    // Assign initial MAC address to support the initial ARP probe
    uint8_t ha[ETH_ADDR_LEN] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    my_addr->set_ha(ha);

    /* Retrieve device list */
    if (pcap_findalldevs(&alldevs, errbuf) == (-1)) {
        fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
        exit(-1);
    }
    for (intf = alldevs; intf != nullptr; intf = intf->next) {
        printf("%d ", ++i);
        // printf("%s ", d->name);
        if (intf->description)
            printf("%s\n", intf->description);
        else
            printf("(No description available)\n");
    }
    printf("Enter the interface number (1-%d):", i);
    int result = scanf("%d", &inum);
    if (result < 0) {
        printf("\nscanf() failed\n");
        exit(-1);
    }
    if (inum < 1 || inum > i) {
        printf("\nInterface number out of range\n");
        /* Free the device list */
        pcap_freealldevs(alldevs);
        exit(-1);
    }

    /* Jump to selected adapter */
    for (intf = alldevs, i = 0; i < inum - 1; intf = intf->next, i++)
        ;

    /* Open the device */
    /* Open the adapter */
    intf_handl = pcap_open_live(intf->name,  // Device Name
                                65536,       // Portion of packet to capture
                                // 65536 grants that the whole packet
                                // will be captured on all the MACs
                                1,        // Promiscuous mode
                                1000,     // Read timeout
                                errbuf);  // Error buffer
    if (intf_handl == nullptr) {
        fprintf(stderr, "\nOpen adapter %s failed", intf->name);
        pcap_freealldevs(alldevs);
        return (-1);
    }
    printf("\nListening on %s...\n", intf->description);

    memset(intf_name, 0, INTF_NAME_MAX_LEN);
    strcpy(intf_name, intf->name);
    printf("Interface name %s\r\n", intf_name);

    pcap_freealldevs(alldevs);

    //_beginthread(cli, 0, nullptr);

    // Send ARP announcement
    class arp a;
    a.send_probe();

    /* start the capture */
    pcap_loop(intf_handl, 0, packet_handler, nullptr);

    // Leave the interface adapter handle open so we can write raw packets
    // pcap_close(intf_handl);

    return 0;
}

/* Callback function invoked by libpcap for every incoming packet */
static void packet_handler(u_char *param, const struct pcap_pkthdr *header,
                           const u_char *pkt_data) {
    if (dump_enabled) {
        printf("\r\nFrame %u\r\n", stats.get_frame_count());
        // bufdump((uint8_t *)pkt_data, header->len);
    }
    stats.inc_frame_count();

    class eth eth;
    eth.set_buf((uint8_t *)pkt_data);
    if (dump_enabled) eth.dump();
    eth.receive();
}
