#include "compiler.h"

int main(int argc, char *argv[])
{
  char *list[] ={"../examples/basic.tem"};
  scan_file_list(list, 1);   

  return EXIT_SUCCESS;
}

