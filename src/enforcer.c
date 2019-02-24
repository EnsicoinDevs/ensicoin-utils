#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

static void
enforcer_error(const char *format, ...) {
	va_list ap;

	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);

	exit(EXIT_FAILURE);
}

static int
enforcer_open_node(const char *hostname) {
	struct addrinfo hints;
	struct addrinfo *res;
	int retval;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if((retval = getaddrinfo(hostname, "4224", &hints, &res)) != 0) {
		enforcer_error("ensicoin-enforcer: Unable to getaddrinfo for '%s': %s\n",
			hostname, gai_strerror(retval));
	}

	int sockfd = -1;
	for(struct addrinfo *it = res;
		sockfd == -1 && it != NULL;
		it = it->ai_next) {

		if((sockfd = socket(it->ai_family, it->ai_socktype, it->ai_protocol)) != -1
			&& connect(sockfd, it->ai_addr, it->ai_addrlen) == -1) {

			close(sockfd);
			sockfd = -1;
		}
	}

	if(sockfd == -1) {
		enforcer_error("ensicoin-enforcer: Unable to connect to '%s': %s\n",
			hostname, strerror(errno));
	}

	freeaddrinfo(res);

	return sockfd;
}

static void
enforcer_enforce(int sockfd, int random, const char *hostname) {
	char buffer[512];
	ssize_t readval;

	do {
		readval = read(random, buffer, sizeof(buffer));
	} while(readval > 0 && send(sockfd, buffer, readval, 0) > 0);

	if(readval > 0) {
		enforcer_error("ensicoin-enforcer: Service '%s' closed connection: %s\n",
			hostname, strerror(errno));
	}
}

int
main(int argc,
	char **argv) {
	if(argc != 2) {
		fprintf(stderr, "usage: ensicoin-enforcer <hostname>\n");
		exit(EXIT_FAILURE);
	}

	char *hostname = argv[1];
	int sockfd = enforcer_open_node(hostname);
	int random = open("/dev/random", O_RDONLY);


	close(random);
	shutdown(sockfd, SHUT_RDWR);
	close(sockfd);

	exit(EXIT_SUCCESS);
}

