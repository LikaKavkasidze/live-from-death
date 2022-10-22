#pragma once

#include <string.h>
#include <stdlib.h>

// Hash map using open adressing
struct GopherMapEntry {
	// Type defines the maximum number of elements (here 256)
	char *path;
	char *content;
};

void map_insert(struct GopherMapEntry **map, char *path, char *content);
void map_find(struct GopherMapEntry **map, char *path, char **content);
void map_free(struct GopherMapEntry **map, unsigned int size);
