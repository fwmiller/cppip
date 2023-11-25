#include <stdio.h>
#include "cppip.h"
#include "dhcp.h"

static void
dhcp_dump_msg_type(uint8_t type) {
    switch (type) {
    case DHCPDISCOVER:
        printf("DHCPDISCOVER");
        break;
    case DHCPOFFER:
        printf("DHCPOFFER");
        break;
    case DHCPREQUEST:
        printf("DHCPREQUEST");
        break;
    case DHCPDECLINE:
        printf("DHCPDECLINE");
        break;
    case DHCPACK:
        printf("DHCPACK");
        break;
    case DHCPNAK:
        printf("DHCPNAK");
        break;
    case DHCPRELEASE:
        printf("DHCPRELEASE");
        break;
    case DHCPINFORM:
        printf("DHCPINFORM");
        break;
    case DHCPFORCERENEW:
        printf("DHCPFORCERENEW");
        break;
    case DHCPLEASEQUERY:
        printf("DHCPLEASEQUERY");
        break;
    case DHCPLEASEUNASSIGNED:
        printf("DHCPLEASEUNASSIGNED");
        break;
    case DHCPLEASEUNKNOWN:
        printf("DHCPLEASEUNKNOWN");
        break;
    case DHCPLEASEACTIVE:
        printf("DHCPLEASEACTIVE");
        break;
    case DHCPBULKLEASEQUERY:
        printf("DHCPBULKLEASEQUERY");
        break;
    case DHCPLEASEQUERYDONE:
        printf("DHCPLEASEQUERYDONE");
        break;
    case DHCPACTIVELEASEQUERY:
        printf("DHCPACTIVELEASEQUERY");
        break;
    case DHCPLEASEQUERYSTATUS:
        printf("DHCPLEASEQUERYSTATUS");
        break;
    case DHCPTLS:
        printf("DHCPTLS");
        break;
    default:
        printf("UNKNOWN");
    };
}

static void
dhcp_dump_opt_type(uint8_t type, uint8_t len, uint8_t *val) {
    switch (type) {
    case DHCP_OPT_PAD:
        printf("pad");
        break;
    case DHCP_OPT_SUBNET_MASK:
        printf("subnet mask ");
        dump_ipaddr(reverse_byte_order_long(*((uint32_t *) val)));
        break;
    case DHCP_OPT_TIME_OFFSET:
        printf("time offset");
        break;
    case DHCP_OPT_ROUTER:
        printf("router ");
        dump_ipaddr(reverse_byte_order_long(*((uint32_t *) val)));
        break;
    case DHCP_OPT_TIME_SERVER:
        printf("time server");
        break;
    case DHCP_OPT_NAME_SERVER:
        printf("name server ");
        dump_ipaddr(reverse_byte_order_long(*((uint32_t *) val)));
        break;
    case DHCP_OPT_DOMAIN_NAME_SERVER:
        printf("domain name server ");
        dump_ipaddr(reverse_byte_order_long(*((uint32_t *) val)));
        break;
    case DHCP_OPT_LOG_SERVER:
        printf("log server");
        break;
    case DHCP_OPT_COOKIE_SERVER:
        printf("cookie server");
        break;
    case DHCP_OPT_LPR_SERVER:
        printf("lpr server");
        break;
    case DHCP_OPT_IMPRESS_SERVER:
        printf("impress server");
        break;
    case DHCP_OPT_RESOURCE_LOCATION_SERVER:
        printf("location server");
        break;
    case DHCP_OPT_HOST_NAME:
        printf("host name ");
        for (int i = 0; i < len; i++)
            printf("%c", val[i]);
        break;
    case DHCP_OPT_BOOT_FILE_SIZE:
        printf("boot file size");
        break;
    case DHCP_OPT_MERIT_DUMP_FILE:
        printf("merit dump file");
        break;
    case DHCP_OPT_DOMAIN_NAME:
        printf("domain name ");
        for (int i = 0; i < len; i++)
            printf("%c", val[i]);
        break;
    case DHCP_OPT_SWAP_SERVER:
        printf("swap server");
        break;
    case DHCP_OPT_ROOT_PATH:
        printf("root path");
        break;
    case DHCP_OPT_EXTENSIONS_PATH:
        printf("extensions path");
        break;
    case DHCP_OPT_REQUESTED_IP_ADDR:
        printf("ip address ");
        dump_ipaddr(reverse_byte_order_long(*((uint32_t *) val)));
        break;
    case DHCP_OPT_IP_ADDR_LEASE_TIME:
        printf("ip address lease time");
        break;
    case DHCP_OPT_OVERLOAD:
        printf("overload");
        break;
    case DHCP_OPT_MESSAGE_TYPE:
        printf("message type ");
        dhcp_dump_msg_type(*val);
        break;
    case DHCP_OPT_SERVER_ID:
        printf("server id");
        break;
    case DHCP_OPT_PARAMETER_REQ_LIST:
        printf("parameter request list");
        break;
    case DHCP_OPT_MESSAGE:
        printf("message");
        break;
    case DHCP_OPT_MAX_DHCP_MSG_SIZE:
        printf("max dhcp message size");
        break;
    case DHCP_OPT_RENEWAL:
        printf("renewal");
        break;
    case DHCP_OPT_REBINDING:
        printf("rebinding");
        break;
    case DHCP_OPT_VENDOR_CLASS_ID:
        printf("vendor class id");
        break;
    case DHCP_OPT_CLIENT_ID:
        printf("client id");
        break;
    case DHCP_OPT_TFTP_SERVER_NAME:
        printf("tftp server name ");
        for (int i = 0; i < len; i++)
            printf("%c", val[i]);
        break;
    case DHCP_OPT_BOOTFILE_NAME:
        printf("bootfile name ");
        for (int i = 0; i < len; i++)
            printf("%c", val[i]);
        break;
    case DHCP_OPT_END:
        printf("end");
        break;
    default:
        printf("UNKNOWN");
    }
}

void
dhcp_dump(uint8_t *buf, int buflen) {
    dhcp_hdr_t dh = (dhcp_hdr_t) buf;
    uint8_t *type, *len, *val;

    if (dh->op == 1)
        printf("request");
    else if (dh->op == 2)
        printf("reply");
    else
        printf("UNKNOWN");

    printf(" xid 0x%08x secs %u flags 0x%04x\r\n",
           reverse_byte_order_long(dh->xid),
           reverse_byte_order_short(dh->secs),
           reverse_byte_order_short(dh->flags));

    printf("  ciaddr ");
    dump_ipaddr(reverse_byte_order_long(dh->ciaddr));
    printf(" yiaddr ");
    dump_ipaddr(reverse_byte_order_long(dh->yiaddr));
    printf("\r\n  siaddr ");
    dump_ipaddr(reverse_byte_order_long(dh->siaddr));
    printf(" giaddr ");
    dump_ipaddr(reverse_byte_order_long(dh->siaddr));
    printf("\r\n");
    printf("  chaddr ");
    dump_ethaddr(dh->chaddr);
    printf("\r\n");
#if 0
    printf("  sname\r\n");
    bufdump(dh->sname, 64);

    printf("  file\r\n");
    bufdump(dh->file, 128);
#endif

    int optlen = buflen - sizeof(struct dhcp_hdr);
    uint8_t *opt = buf + sizeof(struct dhcp_hdr);
    while (optlen > 0) {
        type = opt;
        len = opt + 1;
        val = opt + 2;

        printf("  ");
        dhcp_dump_opt_type(*type, *len, val);
        // printf(" len %d", *len);
        printf("\r\n");

        if (*type == DHCP_OPT_END)
            break;

        opt += *len + 2;
        optlen -= *len + 2;
    }
}
