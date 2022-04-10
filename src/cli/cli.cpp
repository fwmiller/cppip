#include "cli.h"
#include <ctype.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "arptab.h"
#include "byteq.h"
#include "stats.h"
#include "udptab.h"

static const int CMDLINE_LEN = 128;

char *readline(const char *prompt);

void byteq_test();
void bufq_test();

void nextarg(char *ln, int *pos, char *sep, char *arg);

static void
cmd_dump(char *cmdline, int *pos, char *sep, char *arg) {
    memset(arg, 0, CMDLINE_LEN);
    nextarg(cmdline, pos, sep, arg);
    if (strcmp(arg, "on") == 0)
        dump_enabled = true;
    else if (strcmp(arg, "off") == 0)
        dump_enabled = false;
}

static void
cmd_stats() {
    printf("frames   %u\r\n", stats.get_frame_count());
    printf("ethernet %u\r\n", stats.get_eth_count());
    printf("802.2    %u\r\n", stats.get_ieee802_2_count());
    printf("arp      %u\r\n", stats.get_arp_count());
    printf("rarp     %u\r\n", stats.get_rarp_count());
    printf("ipv4     %u\r\n", stats.get_ipv4_count());
    printf("ipv6     %u\r\n", stats.get_ipv6_count());
    printf("icmp     %u\r\n", stats.get_icmp_count());
    printf("udp      %u\r\n", stats.get_udp_count());
    printf("tcp      %u\r\n", stats.get_tcp_count());
}

void *
cli(void *pthread_arg) {
    char *cmdline = NULL;
    char arg[CMDLINE_LEN], sep[CMDLINE_LEN];
    int pos;

    memset(arg, 0, CMDLINE_LEN);
    memset(sep, 0, CMDLINE_LEN);
    strcpy(sep, " ");

    for (;;) {
        if (cmdline != NULL) {
            free(cmdline);
            cmdline = NULL;
        }
        cmdline = readline("\033[0;36mcppip\033[0m> ");
        if (cmdline == NULL || strlen(cmdline) == 0)
            continue;

        pos = 0;
        nextarg(cmdline, &pos, sep, arg);

        if (strcmp(arg, "quit") == 0 || strcmp(arg, "exit") == 0)
            exit(0);

        else if (strcmp(arg, "dump") == 0) {
            cmd_dump(cmdline, &pos, sep, arg);

            add_history(cmdline);

        } else if (strcmp(arg, "stats") == 0) {
            cmd_stats();

            add_history(cmdline);

        } else if (strcmp(arg, "arp") == 0) {
            arptab.dump();

            add_history(cmdline);

        } else if (strcmp(arg, "help") == 0) {
            printf("Commands:\r\n");
            printf("dump (on|off)\r\n");
            printf("stats\r\n");
            printf("arp\r\n");
            printf("udp\r\n");
            printf("byteq\r\n");
            printf("bufq\r\n");
            printf("quit | exit\r\n");

            add_history(cmdline);

        } else if (strcmp(arg, "byteq") == 0) {
            byteq_test();

            add_history(cmdline);

        } else if (strcmp(arg, "bufq") == 0) {
            bufq_test();

            add_history(cmdline);

        } else if (strcmp(arg, "udp") == 0) {
            udptab.dump();

            add_history(cmdline);
        }
    }
}
