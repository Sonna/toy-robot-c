#include "robot_test_helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char * capture_output_robot(void (*block)(Robot), Robot robot) {
  char *stdout_contents;
  long temp_out_size;
  int stdout_dupfd;
  FILE *temp_out;
  size_t result;

  /* duplicate stdout */
  stdout_dupfd = dup(1);

  temp_out = fopen("tmp/test_output.txt", "w+");
  // freopen("redirected_filename.txt", "w", stdout);

  /* replace stdout with our output fd */
  close(1);
  dup(fileno(temp_out));

  /* output something... */
  // printf("Hello World\n");
  (*block)(robot);

  /* flush output so it goes to our file */
  fflush(stdout);

  fseek(temp_out, 0, SEEK_END);
  temp_out_size = ftell(temp_out);
  rewind(temp_out);

  // stdout_contents = static_cast<char*>(malloc(temp_out_size * (sizeof(char))));
  stdout_contents = (char*) malloc(sizeof(char)* temp_out_size);
  if (stdout_contents == NULL) { fputs("Memory error\n", stderr); }

  // fread(stdout_contents, sizeof(char), temp_out_size, temp_out);
  result = fread(stdout_contents, sizeof(char), temp_out_size, temp_out);
  if (temp_out_size >= 0 && result != (size_t)temp_out_size) { fputs("Reading error\n", stderr); }

  fclose(temp_out);

  /* Now restore stdout */
  dup(stdout_dupfd);
  close(stdout_dupfd);

  return stdout_contents;
}
