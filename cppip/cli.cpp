#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"

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

void
cli(void* pMyID)
{
	char cmdline[80];

	for (;;) {
		readline("> ", cmdline, 80);
		if (strlen(cmdline) == 0)
			continue;
		printf("%s\r\n", cmdline);
	}
}