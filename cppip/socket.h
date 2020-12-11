#ifndef __SOCKET_H
#define __SOCKET_H

static const int AF_INET = 0;
static const int AF_INET6 = 1;

static const int SOCK_STREAM = 0;
static const int SOCK_DGRAM = 1;
static const int SOCK_SEQPACKET = 2;
static const int SOCK_RAW = 3;

//static const int IPPROTO_IP = 0;
//static const int IPPROTO_IPV6 = 1;
//static const int IPPROTO_ICMP = 2;
//static const int IPPROTO_RAW = 3;
//static const int IPPROTO_TCP = 4;
//static const int IPPROTO_UDP = 5;

class socket {
public:
	socket(int domain, int type, int protocol);
	int bind(struct sockaddr* addr, int addrlen);
	int send();
	int sendto();
	int recv();
	int recvfrom();
	int close();
};

#endif