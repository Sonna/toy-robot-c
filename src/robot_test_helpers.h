#ifndef ROBOT_TEST_HELPERS_H
#define ROBOT_TEST_HELPERS_H

#include "robot.h"
#include "test_helpers.h"

const char * capture_output_robot(void (*block)(Robot), Robot robot);

#endif
