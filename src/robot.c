#include <string.h>

#include "../lib/hash_table.h"

#include "robot.h"

char* turn_left(char* facing) {
  ht_hash_table* cardinal_counter_clockwise = ht_new();

  ht_insert(cardinal_counter_clockwise, "NORTH", "WEST");
  ht_insert(cardinal_counter_clockwise, "WEST", "SOUTH");
  ht_insert(cardinal_counter_clockwise, "SOUTH", "EAST");
  ht_insert(cardinal_counter_clockwise, "EAST", "NORTH");

  char* result = strdup(ht_search(cardinal_counter_clockwise, facing));

  ht_del_hash_table(cardinal_counter_clockwise);
  return result;
}

char* turn_right(char* facing) {
  ht_hash_table* cardinal_clockwise = ht_new();

  ht_insert(cardinal_clockwise, "NORTH", "EAST");
  ht_insert(cardinal_clockwise, "EAST", "SOUTH");
  ht_insert(cardinal_clockwise, "SOUTH", "WEST");
  ht_insert(cardinal_clockwise, "WEST", "NORTH");

  char* result = strdup(ht_search(cardinal_clockwise, facing));

  ht_del_hash_table(cardinal_clockwise);
  return result;
}

// char* move_x(char* facing) {}
// char* move_y(char* facing) {}


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
}

void robot_left(Robot robot) {
  //robot.facing = TURN[robot.facing]["LEFT"];
  // char* new_facing = turn_left(robot.facing);

  // free(robot.facing);
  // robot.facing = malloc(6);
  // robot.facing = strdup(new_facing);
  strncpy(robot.facing, turn_left(robot.facing), 5);
  // strncpy(robot.facing, turn_left(robot.facing), sizeof(robot.facing));
  //strncpy(robot.facing, new_facing, sizeof(robot.facing));
  //strcpy(robot.facing, turn_left(robot.facing));
}

void robot_right(Robot robot) {
  //robot.facing = TURN[robot.facing]["RIGHT"];
  // char* new_facing = turn_right(robot.facing);

  // free(robot.facing);
  // robot.facing = malloc(6);
  // robot.facing = strdup(new_facing);
  strncpy(robot.facing, turn_right(robot.facing), 5);
  // strncpy(robot.facing, turn_right(robot.facing), sizeof(robot.facing));
  //strncpy(robot.facing, new_facing, sizeof(robot.facing));
  // robot.facing = strdup(turn_right(robot.facing));
  //strcpy(robot.facing, turn_right(robot.facing));
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
