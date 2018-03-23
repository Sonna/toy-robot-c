#ifndef ROBOT_TEST_HELPERS_H
#define ROBOT_TEST_HELPERS_H

#include "robot.h"
#include "test_helpers.h"

const char * capture_output_robot(void (*block)(const Robot*), Robot* robot);
const char * capture_output_robot_exec(
    void (*block)(Robot*, char*, char*),
    Robot* robot, char* raw_command, char* raw_args
);
const char * capture_output_toy_robot_run(int (*block)(char**), char** argv);
const char * capture_output_toy_robot_process(void (*block)(FILE*), FILE* input);

#endif
