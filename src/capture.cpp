#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include "cppip.h"
#include "stats.h"

#include <pcap.h>

static const int INTF_NAME_MAX_LEN = 4096;
static char intf_name[INTF_NAME_MAX_LEN];
pcap_t *intf_handl;

void
initialize_pcap() {
    pcap_if_t *alldevs;
    pcap_if_t *intf;
    char errbuf[PCAP_ERRBUF_SIZE];
    int i, inum;

    /* Retrieve device list */
    if (pcap_findalldevs(&alldevs, errbuf) == (-1)) {
        fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
        exit(-1);
    }
    for (i = 0, intf = alldevs; intf != NULL; intf = intf->next) {
        printf("%d ", ++i);
        // printf("%s ", d->name);
        if (intf->name)
            printf("%s: ", intf->name);
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
    if (intf_handl == NULL) {
        fprintf(stderr, "\nOpen adapter %s failed", intf->name);
        pcap_freealldevs(alldevs);
        return;
    }
    printf("\nListening on %s\n",
           (intf->name == NULL ? intf->description : intf->name));

    memset(intf_name, 0, INTF_NAME_MAX_LEN);
    strcpy(intf_name, intf->name);

    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, intf_name);

    ioctl(pcap_fileno(intf_handl), SIOCGIFHWADDR, &ifr);
    dump_ethaddr((uint8_t *) ifr.ifr_hwaddr.sa_data);
    printf("\r\n");

    pcap_freealldevs(alldevs);
}

/* Callback function invoked by libpcap for every incoming packet */
void
packet_handler(u_char *param, const struct pcap_pkthdr *header,
               const u_char *pkt_data) {
    if (dump_enabled) {
        printf("\r\nFrame %u length %u\r\n", stats.get_frame_count(),
               header->len);
        // bufdump((uint8_t *)pkt_data, header->len);
    }
    stats.inc_frame_count();

    class eth eth;
    eth.set_frame((uint8_t *) pkt_data);
    eth.set_framelen(header->len);
    if (dump_enabled)
        eth.dump();
    eth.receive();
}
