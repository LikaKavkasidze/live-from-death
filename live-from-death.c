#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#include "space.h"
#include "map.h"
#include "network.h"

int main(void) {
	int result;

	// Fetch all files to be indexed
	struct GopherMapEntry *gopher_map[256] = {0};
	result = space_initialize(gopher_map, "./space");

	if(result != 0) {
		switch(result) {
			case -1:
				perror("space directory read error");
				break;
			
			case -2:
				perror("malloc error");
				break;
			
			case -3:
				perror("file read error");
				break;
		}

		return 1;
	}
	
	int s_socket;
	result = network_create_socket(&s_socket);

	if(result != 0) {
		perror("failed to bind: no address found\n");
	}

	// Listen for incoming connections
	result = listen(s_socket, 10);

	if(result == -1) {
		perror("listen error");
		return 1;
	}

	int s_csocket;
	struct sockaddr_storage s_caddr;
	char buffer[256];
	unsigned int buffer_read_len;
	socklen_t s_csize = sizeof(s_caddr);

	// Wait for clients
	while(1) {
		// Accept connection from client
		s_csocket = accept(s_socket, (struct sockaddr *) &s_caddr, &s_csize);

		if(s_csocket == -1) {
			perror("accept error");
			continue;
		}

		// Get request
		memset(buffer, 0, sizeof(buffer));
		buffer_read_len = read(s_csocket, buffer, sizeof(buffer));

		// Find file to serve
		char *f_content = 0;
		space_fetch(gopher_map, buffer, buffer_read_len, &f_content);
		unsigned int f_length = strlen(f_content);

		// Send response
		write(s_csocket, f_content, f_length);

		// Close connection
		close(s_csocket);
	}

	close(s_socket);

	return 0;
}
