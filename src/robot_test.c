#include <check.h>
#include <stdlib.h>

#include "test_helpers.h"
#include "robot_test_helpers.h"

#include "robot.h"

START_TEST(robot_test_robot_report) {
  Robot subject = robot_new(0, 0, "NORTH");

  const char* stdout_contents = capture_output_robot(robot_report, subject);
  const char* expected_output = "0,0,NORTH\n";
  ck_assert_int_eq(0, strncmp(stdout_contents, expected_output, strlen(expected_output)));
  //ck_assert_str_eq(stdout_contents, expected_output);
}
END_TEST

START_TEST(robot_test_robot_new) {
  Robot subject = robot_new(0, 0, "NORTH");

  ck_assert_int_eq(subject.x, 0);
  ck_assert_int_eq(subject.y, 0);
  ck_assert_str_eq(subject.facing, "NORTH");
}
END_TEST

Suite * robot_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Robot");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, robot_test_robot_new);
  tcase_add_test(tc_core, robot_test_robot_report);
  suite_add_tcase(s, tc_core);

  return s;
}
