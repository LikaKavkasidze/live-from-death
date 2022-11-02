#include "network.h"

int network_create_socket(int *s_socket) {
	int s_result;
	struct addrinfo s_hints, *s_info, *s_aip;

	// Give hints to `getaddrinfo`
	memset(&s_hints, 0, sizeof s_hints);
	s_hints.ai_family = AF_UNSPEC;
	s_hints.ai_socktype = SOCK_STREAM;
	s_hints.ai_flags = AI_PASSIVE;

	// Get server address, port, and everything
	s_result = getaddrinfo(NULL, "gopher", &s_hints, &s_info);
	if(s_result != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(s_result));
		return -1;
	}

	// Bind to the first valid address
	for(s_aip = s_info; s_aip != NULL; s_aip = s_aip->ai_next) {
		// Create a socket
		*s_socket = socket(s_aip->ai_family, s_aip->ai_socktype, s_aip->ai_protocol);

		if(*s_socket == -1) {
			continue;
		}

		// Bind to the socket
		s_result = bind(*s_socket, s_aip->ai_addr, s_aip->ai_addrlen);

		if(s_result == -1) {
			close(*s_socket);
			continue;
		}

		break;
	}

	freeaddrinfo(s_info);

	if(s_aip == NULL) {
		return -1;
	}
}
