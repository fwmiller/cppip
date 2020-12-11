#include "cppip.h"

socket::socket(int domain, int type, int protocol)
{
	return;
}

int
socket::bind(struct sockaddr* addr, int addrlen)
{
	return (-1);
}

int
socket::send(const uint8_t *buf, unsigned len, int flags)
{
	return (-1);
}

int
socket::sendto(const uint8_t* buf, unsigned len, int flags, const struct sockaddr *to, unsigned tolen)
{
	return (-1);
}

int
socket::recv(uint8_t* buf, unsigned len, int flags)
{
	return (-1);
}

int
socket::recvfrom(uint8_t* buf, unsigned len, int flags, struct sockaddr* from, unsigned* fromlen)
{
	return (-1);
}

int
socket::close()
{
	return (-1);
}