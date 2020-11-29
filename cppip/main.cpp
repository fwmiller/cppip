#include <stdio.h>
#include "cppip.h"

/*
uint8_t pkt[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x08, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x0a, 0x20, 0x3f, 0xc0, 0x0a, 0x20, 0x3c,
                  0x01, 0x0a, 0x00, 0x3c, 0x00, 0x10, 0x00, 0x00 };
*/

//#include "traces/arp.c"
//#include "traces/rarp_req_reply.c"
//#include "traces/sip-rtp-g711.c"

#include <pcap.h>

static void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data);

int main()
{
	pcap_if_t* alldevs;
	pcap_if_t* d;
	pcap_t* adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	int inum;
	int i = 0;

	printf("C++ Internet Protocols (cppip)\r\n");

	/* Retrieve the device list */
	if (pcap_findalldevs(&alldevs, errbuf) == (-1))	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(-1);
	}
	for (d = alldevs; d != nullptr; d = d->next) {
		printf("%d ", ++i);
		//printf("%s ", d->name);
		if (d->description)
			printf("%s\n", d->description);
		else
			printf("(No description available)\n");
	}
	printf("Enter the interface number (1-%d):", i);
	scanf_s("%d", &inum);

	if (inum < 1 || inum > i) {
		printf("\nInterface number out of range\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return (-1);
	}

	/* Jump to the selected adapter */
	for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++);

	/* Open the device */
	/* Open the adapter */
	if ((adhandle = pcap_open_live(d->name,	// name of the device
		65536,								// portion of the packet to capture
											//  65536 grants that the whole packet will be captured on all the MACs
		1,									// promiscuous mode (nonzero means promiscuous)
		1000,								// read timeout
		errbuf								// error buffer
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return (-1);
	}
	printf("\nListening on %s...\n", d->description);

	/* At this point, we don't need any more the device list. Free it */
	pcap_freealldevs(alldevs);

	/* start the capture */
	pcap_loop(adhandle, 0, packet_handler, NULL);

	pcap_close(adhandle);
	return 0;
}

static unsigned pkt_count = 0;

/* Callback function invoked by libpcap for every incoming packet */
static void
packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)
{
	printf("Frame %u\r\n", ++pkt_count);
	//bufdump((uint8_t *)pkt_data, header->len);

	class eth eth;
	eth.set_buf((uint8_t*)pkt_data);
	eth.dump();
	eth.receive();
}