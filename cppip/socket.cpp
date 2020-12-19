#include <string.h>
#include "cppip.h"

socket::socket(int domain, int type, int protocol)
{
	return;
}

int
socket::bind(struct sockaddr* addr, int addrlen)
{
	if (this->state != SOCKET_OPEN)
		return (-1);
}

int
socket::send(const uint8_t *buf, unsigned len, int flags)
{
	if (this->state != SOCKET_READY)
		return (-1);

	return (-1);
}

int
socket::sendto(const uint8_t* buf, unsigned len, int flags, const struct sockaddr *to, unsigned tolen)
{
	if (this->state != SOCKET_READY)
		return (-1);
	return (-1);
}

int
socket::recv(uint8_t* buf, unsigned len, int flags)
{
	if (this->state != SOCKET_READY)
		return (-1);
	return (-1);
}

int
socket::recvfrom(uint8_t* buf, unsigned len, int flags, struct sockaddr* from, unsigned* fromlen)
{
	if (this->state != SOCKET_READY)
		return (-1);
	return (-1);
}

int
socket::close()
{
	if (this->state != SOCKET_READY)
		return (-1);
	return (-1);
}