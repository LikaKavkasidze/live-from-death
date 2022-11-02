#pragma once

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "map.h"

#define INDEX_PAGE "index"

int space_initialize(struct GopherMapEntry **gopher_map, char *s_directory_name);
void space_fetch(struct GopherMapEntry **gopher_map, char *address, int address_length, char **f_content);
