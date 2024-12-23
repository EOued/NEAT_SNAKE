#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
void sendError(const char* error, int exitCode)
{
  if (!error) fprintf(stderr, "No error message provided (bad usage)");
  else
    fprintf(stderr, "%s\n", error);
  exit(exitCode);
}
