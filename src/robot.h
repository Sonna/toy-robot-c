#include <stdio.h>
#include <stdlib.h>

#include "../lib/hash_table.h"

#ifndef ROBOT_H
#define ROBOT_H

typedef struct Robot {
    int x;
    int y;
    char * facing;
} Robot;

// Robot robot_new(int x, int y, char* facing);
Robot* robot_new(const int x, const int y, const char* facing);
void robot_destroy(Robot* robot);
void robot_report(const Robot* robot);
void robot_left(Robot* robot);
void robot_right(Robot* robot);
void robot_move(Robot* robot);
void robot_place(Robot* robot, char* raw_coordinates);
void robot_exec(Robot* robot, char* raw_command, char* raw_args);

void toy_robot_process(FILE* input);
int toy_robot_run(char** argv);

#endif
