#include "cppip.h"
#include "stats.h"

void
 eth::receive()
{
	uint16_t
	    ethertype;

	ethertype = this->get_ethertype();
	if (ethertype < ETH_MTU_SIZE) {
		stats.inc_ieee802_2_count();

		class ieee802_2
		    llc;
		llc.set_buf(this->buf + sizeof(struct eth_hdr));
		if (dump_enabled)
			llc.dump();
		llc.receive();
		return;
	}
	stats.inc_eth_count();

	switch (ethertype) {
	case ETHERTYPE_ARP:
	case ETHERTYPE_RARP:
		{
			if (ethertype == ETHERTYPE_ARP)
				stats.inc_arp_count();
			else if (ethertype == ETHERTYPE_RARP)
				stats.inc_rarp_count();

			class arp
			    arp;
			arp.set_buf(this->buf + sizeof(struct eth_hdr));
			if (dump_enabled)
				arp.dump();
			arp.receive();
		}
		break;
	case ETHERTYPE_IPV4:
		{
			stats.inc_ipv4_count();

			class ipv4
			    ip;
			ip.set_buf(this->buf + sizeof(struct eth_hdr));
			if (dump_enabled)
				ip.dump();
			ip.receive();
		}
		break;
	case ETHERTYPE_IPV6:
		{
			stats.inc_ipv6_count();

			class ipv6
			    ip;
			ip.set_buf(this->buf + sizeof(struct eth_hdr));
			if (dump_enabled)
				ip.dump();
			ip.receive();
		}
		break;
	}
}
