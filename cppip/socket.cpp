#include <string.h>
#include "cppip.h"

static const int MAX_SOCKETS = 64;

// These are shared global data structure and need synchronization
//  in a multi-threaded environment
static bool initialized = false;
static int sockets_open_count = 0;
static struct socket_desc socketstab[MAX_SOCKETS];

buf_t
socket::get_buf()
{
	return this->buf;
}

void
socket::set_buf(buf_t buf)
{
	this->buf = buf;
}

int
socket::get_len()
{
	return this->len;
}

void
socket::set_len(int len)
{
	this->len = len;
}

int
socket::receive()
{
	if (this->buf == nullptr)
		return (-1);

	return (-1);
}

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

static struct socket_desc *
socket_alloc()
{
	if (!initialized) {
		for (int i = 0; i < MAX_SOCKETS; i++)
			socket_desc_init(&(socketstab[i]));
		initialized = true;
	}
	if (sockets_open_count == MAX_SOCKETS)
		return nullptr;

	for (int i = 0; i < MAX_SOCKETS; i++) {
		struct socket_desc* desc = &(socketstab[i]);

		if (desc->state == SOCKET_FREE) {
			desc->state = SOCKET_OPEN;
			sockets_open_count++;
			return desc;
		}
	}
	return nullptr;
}

socket::socket()
{
	// Sync wait
	this->desc = socket_alloc();
	// Sync signal
}

socket::socket(int domain, int type, int protocol)
{
	// Sync wait
	this->desc = socket_alloc();
	// Sync signal
}

int
socket::bind(struct sockaddr* addr, int addrlen)
{
	if (this->desc->state != SOCKET_OPEN)
		return (-1);

	// Sync wait

	// Search the socketstab to see whether this port is already bound
	for (int i = 0; i < MAX_SOCKETS; i++) {
		struct socket_desc* desc = &(socketstab[i]);

	}

	// Sync signal
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
	return (-1);
}