#include <string.h>
#include "cppip.h"

static const int MAX_SOCKETS = 64;

static bool initialized = false;
static int sockets_open_count = 0;
static struct socket_desc socketstab[MAX_SOCKETS];

static void
socket_desc_init(struct socket_desc* desc)
{
	desc->state = SOCKET_FREE;
	desc->open_count = 0;
	desc->port = 0;
	memset(desc->rcvd_data, 0, SOCKET_INPUT_BUFFER_SIZE);
	desc->h = 0;
	desc->t = 0;
	desc->full = false;
}

socket::socket(int domain, int type, int protocol)
{
	if (!initialized) {
		for (int i = 0; i < MAX_SOCKETS; i++)
			socket_desc_init(&(socketstab[i]));
		initialized = true;
	}
	if (sockets_open_count == MAX_SOCKETS)
		return;

	for (int i = 0; i < MAX_SOCKETS; i++) {
		struct socket_desc* desc = &(socketstab[i]);

		if (desc->state == SOCKET_FREE) {
			desc->state = SOCKET_OPEN;
			sockets_open_count++;
		}
	}
}

int
socket::bind(struct sockaddr* addr, int addrlen)
{
	if (this->desc->state != SOCKET_OPEN)
		return (-1);

	// Search the socketstab to see whether this port is already bound
	for (int i = 0; i < MAX_SOCKETS; i++) {
		struct socket_desc* desc = &(socketstab[i]);

	}
	return 0;
}

int
socket::send(const uint8_t *buf, unsigned len, int flags)
{
	if (this->desc->state != SOCKET_READY)
		return (-1);

	return (-1);
}

int
socket::sendto(const uint8_t* buf, unsigned len, int flags, const struct sockaddr *to, unsigned tolen)
{
	if (this->desc->state != SOCKET_READY)
		return (-1);
	return (-1);
}

int
socket::recv(uint8_t* buf, unsigned len, int flags)
{
	if (this->desc->state != SOCKET_READY)
		return (-1);
	return (-1);
}

int
socket::recvfrom(uint8_t* buf, unsigned len, int flags, struct sockaddr* from, unsigned* fromlen)
{
	if (this->desc->state != SOCKET_READY)
		return (-1);
	return (-1);
}

int
socket::close()
{
	if (this->desc->state != SOCKET_READY)
		return (-1);
	return (-1);
}