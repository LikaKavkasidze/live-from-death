#include "map.h"

void map_insert(struct GopherMapEntry **map, char *path, char *content) {
	// Compute hash
	int c = 0;
	unsigned char hash = 1;

	while(path[c] != 0) {
		hash = hash * path[c] + 1;
		c++;
	}

	// Find element not currently used
	unsigned char position = hash;
	while(map[position] != NULL) position++;

	// Fill map entry
	char *content_local = malloc(strlen(content) + 1);
	strcpy(content_local, content);

	char *path_local = malloc(strlen(path) + 1);
	strcpy(path_local, path);

	struct GopherMapEntry *map_entry = (struct GopherMapEntry *) malloc(sizeof(struct GopherMapEntry));

	map_entry->path = path_local;
	map_entry->content = content_local;

	map[position] = map_entry;
}

void map_find(struct GopherMapEntry **map, char *path, char **content) {
	// Compute hash
	int c = 0;
	unsigned char hash = 1;

	while(path[c] != 0) {
		hash = hash * path[c] + 1;
		c++;
	}

	// Find element that match
	unsigned char position = hash;
	while(map[position] != 0 && strcmp(map[position]->path, path) != 0) position++;

	// On error: no element found
	if(map[position] == 0) {
		*content = 0;
		return;
	}

	// Return element
	*content = map[position]->content;
}

void map_free(struct GopherMapEntry **map, unsigned int size) {
	for(unsigned int i = 0; i < size; i++) {
		// If an element exists, free it's content
		if(map[i] != 0) {
			free(map[i]->path);
			free(map[i]->content);
			free(map[i]);
		}
	}
}
