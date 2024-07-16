#ifndef SCAN_H
#define SCAN_H

#include "tokens.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/debug.h"
#include "../config.h"

typedef unsigned int token_t;
// Describes the start word index and end for each line,
// each descriptor describes a line in the program.
struct line_desc {
  size_t start;
  size_t end;
};

struct token_desc {
  char value[TEMMA_DEFAULT_TOKEN_SIZE];
  token_t tkn;
};

int scan_file_list(char *farr[], size_t farr_length);

#endif // !SCAN_H
