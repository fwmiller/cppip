#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "cppip.h"

static int
readline(const char* prompt, char* line, int maxlen)
{
	int c, pos;

	if (prompt == NULL || line == NULL)
		return (-1);

	memset(line, 0, maxlen);

	printf(prompt);
	for (pos = 0; pos < maxlen - 1; pos++) {
		c = getchar();
		if (c == '\n')
			break;
		line[pos] = c;
	}
	return 0;
}

static int
issep(char* sep, char ch)
{
	int i, len;

	if (sep == NULL)
		return 0;

	for (len = strlen(sep), i = 0; i < len; i++)
		if (ch == sep[i])
			return 1;
	return 0;
}

static void
nextarg(char* ln, int* pos, char* sep, char* arg)
{
	char* s;
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

static const int CMDLINE_LEN = 128;

void
cli(void* pMyID)
{
	char cmdline[CMDLINE_LEN];
	char arg[CMDLINE_LEN], sep[CMDLINE_LEN];
	int pos;

	memset(cmdline, 0, CMDLINE_LEN);
	memset(arg, 0, CMDLINE_LEN);
	memset(sep, 0, CMDLINE_LEN);
	strcpy(sep, " ");

	for (;;) {
		readline("> ", cmdline, CMDLINE_LEN);
		if (strlen(cmdline) == 0)
			continue;

		pos = 0;
		nextarg(cmdline, &pos, sep, arg);

		if (strcmp(arg, "dump") == 0) {
			memset(arg, 0, CMDLINE_LEN);
			nextarg(cmdline, &pos, sep, arg);
			if (strcmp(arg, "on") == 0)
				dump_enabled = true;
			else if (strcmp(arg, "off") == 0)
				dump_enabled = false;
		}
	}
}