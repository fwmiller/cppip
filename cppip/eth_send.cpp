#include "cppip.h"
#include <pcap.h>

extern pcap_t* intf_handl;

void
eth::send()
{
	if (this->buf == nullptr)
		return;

	printf("eth::send()\r\n");
	bufdump(this->buf, this->buflen);

    /* Send down the packet */
	if (pcap_sendpacket(intf_handl, this->buf, this->buflen) != 0) {
		printf("eth::send: pcap_sendpacket() failed ");
		pcap_perror(intf_handl, (char*)"eth::send() ");
	}
}