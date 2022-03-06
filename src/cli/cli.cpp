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

char *readline(const char *prompt);

static int
issep(char *sep, char ch) {
    int i, len;

    if (sep == NULL)
        return 0;

    for (len = strlen(sep), i = 0; i < len; i++)
        if (ch == sep[i])
            return 1;
    return 0;
}

static void
nextarg(char *ln, int *pos, char *sep, char *arg) {
    char *s;
    char ch;

    if (ln == NULL || pos == NULL || arg == NULL)
        return;

    s = arg;

    /* Skip whitespace */
    ch = ln[*pos];
    while (isspace(ch))
        ch = ln[++(*pos)];

    /* Fill in arg until a separator is reached */
    strcpy(s, "");
    while (ch != '\0' && !issep(sep, ch)) {
        *(s++) = ch;
        ch = ln[++(*pos)];
    };
    *s = '\0';
}

static void
byteq_test() {
    byteq q;
    char ch = 'a';
    char recv;

    for (;;) {
        for (int i = 0; i < 10; i++) {
            q.append((buf_t) &ch, 1);
            q.dump_contents();

            if (ch == 'z')
                ch = 'a';
            else
                ch++;
        }
        for (int i = 0; i < 11; i++) {
            q.remove((buf_t) &recv, 1);
            q.dump_contents();
        }
    }
}

static const int CMDLINE_LEN = 128;

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
        cmdline = readline("cppip> ");
        if (cmdline == NULL || strlen(cmdline) == 0)
            continue;

        pos = 0;
        nextarg(cmdline, &pos, sep, arg);

        if (strcmp(arg, "quit") == 0 || strcmp(arg, "exit") == 0)
            exit(0);

        else if (strcmp(arg, "dump") == 0) {
            memset(arg, 0, CMDLINE_LEN);
            nextarg(cmdline, &pos, sep, arg);
            if (strcmp(arg, "on") == 0)
                dump_enabled = true;
            else if (strcmp(arg, "off") == 0)
                dump_enabled = false;

            add_history(cmdline);

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

            add_history(cmdline);

        } else if (strcmp(arg, "arp") == 0) {
            arptab.dump();

            add_history(cmdline);

        } else if (strcmp(arg, "help") == 0) {
            printf("Commands:\r\n");
            printf("dump (on|off)\r\n");
            printf("stats\r\n");
            printf("arp\r\n");
            printf("quit | exit\r\n");

            add_history(cmdline);

        } else if (strcmp(arg, "byteq") == 0) {
            byteq_test();
        }
    }
}
