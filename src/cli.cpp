#include "cli.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cppip.h"
#include "stats.h"

static int readline(const char *prompt, char *line, int maxlen) {
    int c, pos;

    if (prompt == nullptr || line == nullptr) return (-1);

    memset(line, 0, maxlen);

    printf(prompt);
    for (pos = 0; pos < maxlen - 1; pos++) {
        c = getchar();
        if (c == '\n') break;
        line[pos] = c;
    }
    return 0;
}

static int issep(char *sep, char ch) {
    int i, len;

    if (sep == nullptr) return 0;

    for (len = strlen(sep), i = 0; i < len; i++)
        if (ch == sep[i]) return 1;
    return 0;
}

static void nextarg(char *ln, int *pos, char *sep, char *arg) {
    char *s;
    char ch;

    if (ln == nullptr || pos == nullptr || arg == nullptr) return;

    s = arg;

    /* Skip whitespace */
    ch = ln[*pos];
    while (isspace(ch)) ch = ln[++(*pos)];

    /* Fill in arg until a separator is reached */
    strcpy(s, "");
    while (ch != '\0' && !issep(sep, ch)) {
        *(s++) = ch;
        ch = ln[++(*pos)];
    };
    *s = '\0';
}

static const int CMDLINE_LEN = 128;

void cli(void *pMyID) {
    char cmdline[CMDLINE_LEN];
    char arg[CMDLINE_LEN], sep[CMDLINE_LEN];
    int pos;

    memset(cmdline, 0, CMDLINE_LEN);
    memset(arg, 0, CMDLINE_LEN);
    memset(sep, 0, CMDLINE_LEN);
    strcpy(sep, " ");

    // Generate and send the initial ARP probe packet.  Assumes
    // my_addr->ha is set
    uint8_t *pktbuf = (uint8_t *)malloc(ETH_MTU_SIZE);
    class arp ap;
    ap.set_buf(pktbuf);
    ap.send_probe();

    for (;;) {
        readline("> ", cmdline, CMDLINE_LEN);
        if (strlen(cmdline) == 0) continue;

        pos = 0;
        nextarg(cmdline, &pos, sep, arg);

        if (strcmp(arg, "dump") == 0) {
            memset(arg, 0, CMDLINE_LEN);
            nextarg(cmdline, &pos, sep, arg);
            if (strcmp(arg, "on") == 0)
                dump_enabled = true;
            else if (strcmp(arg, "off") == 0)
                dump_enabled = false;

        } else if (strcmp(arg, "stats") == 0) {
            printf("frames   %u\r\n", stats.get_frame_count());
            printf("ethernet %u\r\n", stats.get_eth_count());
            printf("802.2    %u\r\n", stats.get_ieee802_2_count());
            printf("arp      %u\r\n", stats.get_arp_count());
            printf("rarp     %u\r\n", stats.get_rarp_count());
            printf("ipv4     %u\r\n", stats.get_ipv4_count());
            printf("ipv6     %u\r\n", stats.get_ipv6_count());
            printf("udp      %u\r\n", stats.get_udp_count());
            printf("tcp      %u\r\n", stats.get_tcp_count());

        } else if (strcmp(arg, "arp") == 0) {
        }
    }
}
