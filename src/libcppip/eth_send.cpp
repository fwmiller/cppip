#include <pcap/pcap.h>
#include <stdlib.h>
#include "cppip.h"

extern pcap_t *intf_handl;

void
eth::send() {
    if (this->frame == NULL)
        return;

    printf("eth::send()\r\n");
    bufdump(this->frame, this->framelen);

    /* Send down the packet */
    if (pcap_sendpacket(intf_handl, this->frame, this->framelen) != 0) {
        printf("eth::send: pcap_sendpacket() failed ");
        pcap_perror(intf_handl, (char *) "eth::send() ");
    }
}
