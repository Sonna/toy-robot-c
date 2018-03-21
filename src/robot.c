#include <string.h>

#include "robot.h"

Robot robot_new(const int x, const int y, const char* facing) {
  Robot robot;

  robot.x = x;
  robot.y = y;
  robot.facing = strdup(facing);

  return robot;
}

// Robot robot_report(const Robot robot) {
void robot_report(const Robot robot) {
  printf("%d,%d,%s\n", robot.x, robot.y, robot.facing);
  //return robot;
}

void toy_robot_process(FILE* input) {
  char buff[255];
  Robot robot = robot_new(0, 0, "NORTH");

  fscanf(input, "%s", buff);
  printf("%s\n", buff );

  robot_report(robot);
  return;
}

int toy_robot_run(char** argv) {
  //printf("Hello World\n");

  if (argv[1]) {
    FILE *input;
    input = fopen(argv[1], "r");

    toy_robot_process(input);

    fclose(input);
  } else {
    toy_robot_process(stdin);
  }

  return 0;
}
