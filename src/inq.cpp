#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "inq.h"

inq::inq()
{
	memset(this->q, 0, MAX_INQ_SIZE);
	this->h = 0;
	this->t = 0;
	this->full = false;
}

uint16_t
inq::get_port()
{
	return this->port;
}

void
 inq::set_port(uint16_t port)
{
	this->port = port;
}

int
 inq::append(buf_t buf, int len)
{
	if (this->full)
		return 0;

	int
	 h = this->h;
	for (int i = 0;;) {
		this->q[h] = buf[i++];

		h = (h + 1) % MAX_INQ_SIZE;
		if (h == this->t) {
			this->h = h;
			this->full = true;
			return i;
		}
		if (i == len) {
			this->h = h;
			return i;
		}
	}
}

int
 inq::remove(buf_t buf, int len)
{
	int
	 t = this->t;
	for (int i = 0;;) {
		if (i == len) {
			this->t = t;
			return i;
		}
		if (t == this->h && !full) {
			this->t = t;
			return i;
		}
		buf[i++] = this->q[t];
		this->q[t] = 0;

		if (full)
			full = false;
		t = (t + 1) % MAX_INQ_SIZE;
	}
}

void
 inq::dump()
{
	printf(" ");
	for (int i = 0; i < MAX_INQ_SIZE; i++)
		if (i == this->h)
			printf("h");
		else if (i == this->t)
			printf("t");
		else
			printf(" ");

	printf(" \r\n[");
	for (int i = 0; i < MAX_INQ_SIZE; i++)
		if (isprint(this->q[i]))
			printf("%c", this->q[i]);
		else
			printf(".");

	printf("]\r\n");
}
