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

int move_x(char* facing) {
  ht_hash_table* cardinal_x_movement = ht_new();

  ht_insert(cardinal_x_movement, "NORTH", "0");
  ht_insert(cardinal_x_movement, "EAST", "1");
  ht_insert(cardinal_x_movement, "SOUTH", "0");
  ht_insert(cardinal_x_movement, "WEST", "-1");

  char* result = strdup(ht_search(cardinal_x_movement, facing));

  ht_del_hash_table(cardinal_x_movement);
  return atoi(result);
}

int move_y(char* facing) {
  ht_hash_table* cardinal_y_movement = ht_new();

  ht_insert(cardinal_y_movement, "NORTH", "1");
  ht_insert(cardinal_y_movement, "EAST", "0");
  ht_insert(cardinal_y_movement, "SOUTH", "-1");
  ht_insert(cardinal_y_movement, "WEST", "0");

  char* result = strdup(ht_search(cardinal_y_movement, facing));

  ht_del_hash_table(cardinal_y_movement);
  return atoi(result);
}


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
  strncpy(robot.facing, turn_left(robot.facing), 5);
}

void robot_right(Robot robot) {
  strncpy(robot.facing, turn_right(robot.facing), 5);
}

void robot_move(Robot* robot) {
  // printf("robot->x{%d} += move_x(robot->facing{%s}){%d};\n", robot->x, robot->facing, move_x(robot->facing));
  robot->x += move_x(robot->facing);
  robot->y += move_y(robot->facing);

  if (robot->x < 0 || robot->x > 4) {
    // printf("robot->x{%d} -= move_x(robot->facing{%s}){%d};\n", robot->x, robot->facing, move_x(robot->facing));
    robot->x -= move_x(robot->facing);
  }

  if (robot->y < 0 || robot->y > 4) {
    robot->y -= move_y(robot->facing);
  }
}

void robot_place(Robot* robot, char* raw_coordinates) {
  robot->x = atoi(&raw_coordinates[0]);
  robot->y = atoi(&raw_coordinates[2]);
  strncpy(robot->facing, raw_coordinates + 4, 5);
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
