#include "space.h"

int space_initialize(struct GopherMapEntry **gopher_map, char *s_directory_name) {
	DIR *s_directory;
	struct dirent *file;

	s_directory = opendir(s_directory_name);

	if(s_directory == NULL) {
		return -1;
	}

	while(file = readdir(s_directory)) {
		// Not the best way at all to check for hidden files
		if(file->d_name[0] != '.') {
			unsigned int f_name_length = strlen(file->d_name) + strlen(s_directory_name) + 2;
			char *f_name = malloc(f_name_length * sizeof(char));
			*f_name = '\0';

			if(f_name == NULL) {
				return -2;
			}

			strcat(f_name, s_directory_name);
			strcat(f_name, "/");
			strcat(f_name, file->d_name);

			// Allocate a large chunk of memory for file content
			char *f_index_content = malloc(10000 * sizeof(char));
			unsigned int f_index_length;

			if(f_index_content == NULL) {
				return -2;
			}

			FILE *f_handle;

			// Read the full index file
			f_handle = fopen(f_name, "r");

			if(f_handle == NULL) {
				return -3;
			}

			f_index_length = fread(f_index_content, 1, 10000, f_handle);
			fclose(f_handle);

			if(f_index_length == -1) {
				return -3;
			}

			map_insert(gopher_map, file->d_name, f_index_content);

			free(f_index_content);
			free(f_name);
		}
	}

	closedir(s_directory);
}

void space_fetch(struct GopherMapEntry **gopher_map, char *address, int address_length, char **f_content) {
	// Trim request
	address[address_length - 2] = '\0';

	map_find(gopher_map, address + 1, f_content);

	// Default to index
	if(*f_content == NULL) {
		map_find(gopher_map, "index", f_content);
	}
}
