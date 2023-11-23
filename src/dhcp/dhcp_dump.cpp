#include <stdio.h>
#include "cppip.h"
#include "dhcp.h"

static void
dhcp_dump_opt_type(uint8_t type) {
    switch (type) {
    case DHCP_OPT_PAD:
        printf("pad");
        break;
    case DHCP_OPT_SUBNET_MASK:
        printf("subnet mask");
        break;
    case DHCP_OPT_TIME_OFFSET:
        printf("time offset");
        break;
    case DHCP_OPT_ROUTER:
        printf("router");
        break;
    case DHCP_OPT_TIME_SERVER:
        printf("time server");
        break;
    case DHCP_OPT_NAME_SERVER:
        printf("name server");
        break;
    case DHCP_OPT_DOMAIN_NAME_SERVER:
        printf("domain name server");
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
        printf("host name");
        break;
    case DHCP_OPT_BOOT_FILE_SIZE:
        printf("boot file size");
        break;
    case DHCP_OPT_MERIT_DUMP_FILE:
        printf("merit dump file");
        break;
    case DHCP_OPT_DOMAIN_NAME:
        printf("domain name");
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
        printf("ip address");
        break;
    case DHCP_OPT_IP_ADDR_LEASE_TIME:
        printf("ip address lease time");
        break;
    case DHCP_OPT_OVERLOAD:
        printf("overload");
        break;
    case DHCP_OPT_MESSAGE_TYPE:
        printf("message type");
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
        printf("tftp server name");
        break;
    case DHCP_OPT_BOOTFILE_NAME:
        printf("bootfile name");
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
        printf("  ");
        dhcp_dump_opt_type(*opt);
        printf("\r\n");

        if (*opt == DHCP_OPT_END)
            break;

        optlen -= *(opt + 1) + 2;
        opt += *(opt + 1) + 2;
    }
}
