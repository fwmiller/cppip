#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

static const int LEN = 16;

void
bufdump(uint8_t* buf, int len)
{
	uint8_t* line;
	int i, j, lines;

	lines = (len + LEN - 1) / LEN;
	for (i = 0; i < lines; i++) {
		line = (uint8_t*)buf + i * LEN;
		for (j = 0; j < LEN; j++) {
			printf("%02x ", line[j]);
			if (j == (LEN / 2) - 1)
				printf(" ");
		}
		printf(" ");
		for (j = 0; j < LEN; j++) {
			if (isprint(line[j]))
				printf("%c", (char)line[j]);
			else
				printf(".");
			if (j == (LEN / 2) - 1)
				printf(" ");
		}
		printf("\r\n");
	}
}

uint16_t
ntohs(uint16_t x)
{
	return ((x & 0xff) << 8) |
		((x & 0xff00) >> 8);
}

uint32_t
ntohl(uint32_t x)
{
	return ((x & 0xff) << 24) |
		((x & 0xff00) << 8) |
		((x & 0xff0000) >> 8) |
		((x & 0xff000000) >> 24);
}