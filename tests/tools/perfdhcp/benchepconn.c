#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <netdb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

struct sockaddr_in addr;

int main(void)
{
	struct timespec ts0, ts1;
	int efd;
	int sock[100];
	int i, j;
	int flags;
	double d;
	struct epoll_event ev;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(53);
	addr.sin_addr.s_addr = inet_addr("149.20.76.29");

	efd = epoll_create(100);
	if (efd < 0) {
		perror("epoll_create");
		exit(1);
	}
	memset(&ev, 0, sizeof(ev));
	ev.events = EPOLLOUT | EPOLLET | EPOLLONESHOT;

	(void) clock_gettime(CLOCK_REALTIME, &ts0);
#define LOOPS 100000
	for (i = 0; i < LOOPS; i++) {
		for (j = 0; j < 100; j++) {
			sock[j] = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (sock[j] < 0) {
				perror("socket");
				exit(1);
			}
			flags = fcntl(sock[j], F_GETFL, 0);
			fcntl(sock[j], F_SETFL, flags | O_NONBLOCK);
			if ((connect(sock[j],
				    (struct sockaddr *) &addr,
				    sizeof(addr)) < 0) &&
			    (errno != EINPROGRESS)) {
				perror("socket");
				exit(1);
			}
			ev.data.fd = sock[j];
			(void) epoll_ctl(efd, EPOLL_CTL_ADD, sock[j], &ev);
		}
		for (j = 0; j < 100; j++)
			(void) close(sock[j]);
	}
	(void) clock_gettime(CLOCK_REALTIME, &ts1);
	d = (double) (ts1.tv_nsec - ts0.tv_nsec);
	d /= 1e9;
	d += (double) (ts1.tv_sec - ts0.tv_sec);
	printf("%d iterations take %.3f s\n", 100 * LOOPS, d);
	return 0;
}
