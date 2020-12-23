#ifndef __SOCKET_H
#define __SOCKET_H

enum SOCKET_STATE { SOCKET_FREE, SOCKET_OPEN, SOCKET_READY, SOCKET_ERROR };

static const int SOCKET_INPUT_BUFFER_SIZE = (1 << 16);	// 64 KB

static const int AF_INET = 0;
static const int AF_INET6 = 1;

static const int SOCK_STREAM = 0;
static const int SOCK_DGRAM = 1;
static const int SOCK_SEQPACKET = 2;
static const int SOCK_RAW = 3;

// These are provided by Windows
//static const int IPPROTO_IP = 0;
//static const int IPPROTO_IPV6 = 1;
//static const int IPPROTO_ICMP = 2;
//static const int IPPROTO_RAW = 3;
//static const int IPPROTO_TCP = 4;
//static const int IPPROTO_UDP = 5;

struct socket_desc {
	enum SOCKET_STATE state;
	int open_count;
	uint16_t port;				// UDP port number
	uint8_t rcvd_data[SOCKET_INPUT_BUFFER_SIZE];
	int h, t;
	bool full;
};

class socket {
private:
	struct socket_desc* desc;

public:
	socket(int domain, int type, int protocol);
	int bind(struct sockaddr* addr, int addrlen);
	int send(const uint8_t* buf, unsigned len, int flags);
	int sendto(const uint8_t* buf, unsigned len, int flags,
		const struct sockaddr* to, unsigned tolen);
	int recv(uint8_t *buf, unsigned len, int flags);
	int recvfrom(uint8_t* buf, unsigned len, int flags,
		struct sockaddr* from, unsigned *fromlen);
	int close();
};

#endif