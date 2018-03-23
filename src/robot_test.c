#include <check.h>
#include <stdlib.h>

#include "test_helpers.h"
#include "robot_test_helpers.h"

#include "robot.h"

START_TEST(robot_test_robot_report) {
  Robot subject = robot_new(0, 0, "NORTH");

  const char* stdout_contents = capture_output_robot(robot_report, &subject);
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

START_TEST(robot_test_robot_left) {
  Robot subject = robot_new(0, 0, "NORTH");

  robot_left(&subject);

  ck_assert_int_eq(subject.x, 0);
  ck_assert_int_eq(subject.y, 0);
  ck_assert_str_eq(subject.facing, "WEST");
}
END_TEST

START_TEST(robot_test_robot_left_from_WEST) {
  Robot subject = robot_new(0, 0, "WEST");

  robot_left(&subject);

  ck_assert_int_eq(subject.x, 0);
  ck_assert_int_eq(subject.y, 0);
  ck_assert_str_eq(subject.facing, "SOUTH");
}
END_TEST

START_TEST(robot_test_robot_left_from_SOUTH) {
  Robot subject = robot_new(0, 0, "SOUTH");

  robot_left(&subject);

  ck_assert_int_eq(subject.x, 0);
  ck_assert_int_eq(subject.y, 0);
  ck_assert_str_eq(subject.facing, "EAST");
}
END_TEST

START_TEST(robot_test_robot_left_from_EAST) {
  Robot subject = robot_new(0, 0, "EAST");

  robot_left(&subject);

  ck_assert_int_eq(subject.x, 0);
  ck_assert_int_eq(subject.y, 0);
  ck_assert_str_eq(subject.facing, "NORTH");
}
END_TEST

START_TEST(robot_test_robot_right) {
  Robot subject = robot_new(0, 0, "NORTH");

  robot_right(&subject);

  ck_assert_int_eq(subject.x, 0);
  ck_assert_int_eq(subject.y, 0);
  ck_assert_str_eq(subject.facing, "EAST");
}
END_TEST

START_TEST(robot_test_robot_right_from_EAST) {
  Robot subject = robot_new(0, 0, "EAST");

  robot_right(&subject);

  ck_assert_int_eq(subject.x, 0);
  ck_assert_int_eq(subject.y, 0);
  ck_assert_str_eq(subject.facing, "SOUTH");
}
END_TEST

START_TEST(robot_test_robot_right_from_SOUTH) {
  Robot subject = robot_new(0, 0, "SOUTH");

  robot_right(&subject);

  ck_assert_int_eq(subject.x, 0);
  ck_assert_int_eq(subject.y, 0);
  ck_assert_str_eq(subject.facing, "WEST");
}
END_TEST

START_TEST(robot_test_robot_right_from_WEST) {
  Robot subject = robot_new(0, 0, "WEST");

  robot_right(&subject);

  ck_assert_int_eq(subject.x, 0);
  ck_assert_int_eq(subject.y, 0);
  ck_assert_str_eq(subject.facing, "NORTH");
}
END_TEST

START_TEST(robot_test_robot_move) {
  Robot subject = robot_new(0, 0, "NORTH");

  robot_move(&subject);

  ck_assert_int_eq(subject.x, 0);
  ck_assert_int_eq(subject.y, 1);
  ck_assert_str_eq(subject.facing, "NORTH");
}
END_TEST

START_TEST(robot_test_robot_move_EAST) {
  Robot subject = robot_new(0, 0, "EAST");

  robot_move(&subject);

  ck_assert_int_eq(subject.x, 1);
  ck_assert_int_eq(subject.y, 0);
  ck_assert_str_eq(subject.facing, "EAST");
}
END_TEST

START_TEST(robot_test_robot_move_WEST) {
  Robot subject = robot_new(2, 2, "WEST");

  robot_move(&subject);

  ck_assert_int_eq(subject.x, 1);
  ck_assert_int_eq(subject.y, 2);
  ck_assert_str_eq(subject.facing, "WEST");
}
END_TEST

START_TEST(robot_test_robot_move_SOUTH) {
  Robot subject = robot_new(2, 2, "SOUTH");

  robot_move(&subject);

  ck_assert_int_eq(subject.x, 2);
  ck_assert_int_eq(subject.y, 1);
  ck_assert_str_eq(subject.facing, "SOUTH");
}
END_TEST

START_TEST(robot_test_robot_move_does_not_fall_off_table_at_00SOUTH) {
  Robot subject = robot_new(0, 0, "SOUTH");

  robot_move(&subject);

  ck_assert_int_eq(subject.x, 0);
  ck_assert_int_eq(subject.y, 0);
  ck_assert_str_eq(subject.facing, "SOUTH");
}
END_TEST

START_TEST(robot_test_robot_move_does_not_fall_off_table_at_00WEST) {
  Robot subject = robot_new(0, 0, "WEST");

  robot_move(&subject);

  ck_assert_int_eq(subject.x, 0);
  ck_assert_int_eq(subject.y, 0);
  ck_assert_str_eq(subject.facing, "WEST");
}
END_TEST

START_TEST(robot_test_robot_move_does_not_fall_off_table_at_04WEST) {
  Robot subject = robot_new(0, 4, "WEST");

  robot_move(&subject);

  ck_assert_int_eq(subject.x, 0);
  ck_assert_int_eq(subject.y, 4);
  ck_assert_str_eq(subject.facing, "WEST");
}
END_TEST

START_TEST(robot_test_robot_move_does_not_fall_off_table_at_04NORTH) {
  Robot subject = robot_new(0, 4, "NORTH");

  robot_move(&subject);

  ck_assert_int_eq(subject.x, 0);
  ck_assert_int_eq(subject.y, 4);
  ck_assert_str_eq(subject.facing, "NORTH");
}
END_TEST

START_TEST(robot_test_robot_move_does_not_fall_off_table_at_44NORTH) {
  Robot subject = robot_new(4, 4, "NORTH");

  robot_move(&subject);

  ck_assert_int_eq(subject.x, 4);
  ck_assert_int_eq(subject.y, 4);
  ck_assert_str_eq(subject.facing, "NORTH");
}
END_TEST

START_TEST(robot_test_robot_move_does_not_fall_off_table_at_44EAST) {
  Robot subject = robot_new(4, 4, "EAST");

  robot_move(&subject);

  ck_assert_int_eq(subject.x, 4);
  ck_assert_int_eq(subject.y, 4);
  ck_assert_str_eq(subject.facing, "EAST");
}
END_TEST

START_TEST(robot_test_robot_move_does_not_fall_off_table_at_40EAST) {
  Robot subject = robot_new(4, 0, "EAST");

  robot_move(&subject);

  ck_assert_int_eq(subject.x, 4);
  ck_assert_int_eq(subject.y, 0);
  ck_assert_str_eq(subject.facing, "EAST");
}
END_TEST

START_TEST(robot_test_robot_move_does_not_fall_off_table_at_40SOUTH) {
  Robot subject = robot_new(4, 0, "SOUTH");

  robot_move(&subject);

  ck_assert_int_eq(subject.x, 4);
  ck_assert_int_eq(subject.y, 0);
  ck_assert_str_eq(subject.facing, "SOUTH");
}
END_TEST

START_TEST(robot_test_robot_place) {
  Robot subject = robot_new(0, 0, "NORTH");

  robot_place(&subject, "4,2,SOUTH");

  ck_assert_int_eq(subject.x, 4);
  ck_assert_int_eq(subject.y, 2);
  ck_assert_str_eq(subject.facing, "SOUTH");
}
END_TEST

START_TEST(robot_test_robot_place_at_13EAST) {
  Robot subject = robot_new(0, 0, "NORTH");

  robot_place(&subject, "1,3,EAST");

  ck_assert_int_eq(subject.x, 1);
  ck_assert_int_eq(subject.y, 3);
  ck_assert_str_eq(subject.facing, "EAST");
}
END_TEST

START_TEST(robot_test_robot_exec_REPORT) {
  Robot subject = robot_new(0, 0, "NORTH");

  //robot_exec(&subject, "REPORT");

  const char* stdout_contents = capture_output_robot_exec(robot_exec, &subject, "REPORT", "");
  const char* expected_output = "0,0,NORTH\n";
  ck_assert_int_eq(0, strncmp(stdout_contents, expected_output, strlen(expected_output)));
}
END_TEST

START_TEST(robot_test_robot_exec_PLACE) {
  Robot subject = robot_new(0, 0, "NORTH");

  robot_exec(&subject, "PLACE", "3,3,WEST");

  ck_assert_int_eq(subject.x, 3);
  ck_assert_int_eq(subject.y, 3);
  ck_assert_str_eq(subject.facing, "WEST");
}
END_TEST

START_TEST(robot_test_robot_exec_MOVE) {
  Robot subject = robot_new(0, 0, "NORTH");

  robot_exec(&subject, "MOVE", "");

  ck_assert_int_eq(subject.x, 0);
  ck_assert_int_eq(subject.y, 1);
  ck_assert_str_eq(subject.facing, "NORTH");
}
END_TEST

START_TEST(robot_test_robot_exec_LEFT) {
  Robot subject = robot_new(0, 0, "NORTH");

  robot_exec(&subject, "LEFT", "");

  ck_assert_int_eq(subject.x, 0);
  ck_assert_int_eq(subject.y, 0);
  ck_assert_str_eq(subject.facing, "WEST");
}
END_TEST

START_TEST(robot_test_robot_exec_RIGHT) {
  Robot subject = robot_new(0, 0, "NORTH");

  robot_exec(&subject, "RIGHT", "");

  ck_assert_int_eq(subject.x, 0);
  ck_assert_int_eq(subject.y, 0);
  ck_assert_str_eq(subject.facing, "EAST");
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
  tcase_add_test(tc_core, robot_test_robot_left);
  tcase_add_test(tc_core, robot_test_robot_left_from_WEST);
  tcase_add_test(tc_core, robot_test_robot_left_from_SOUTH);
  tcase_add_test(tc_core, robot_test_robot_left_from_EAST);
  tcase_add_test(tc_core, robot_test_robot_right);
  tcase_add_test(tc_core, robot_test_robot_right_from_EAST);
  tcase_add_test(tc_core, robot_test_robot_right_from_SOUTH);
  tcase_add_test(tc_core, robot_test_robot_right_from_WEST);
  tcase_add_test(tc_core, robot_test_robot_move);
  tcase_add_test(tc_core, robot_test_robot_move_WEST);
  tcase_add_test(tc_core, robot_test_robot_move_EAST);
  tcase_add_test(tc_core, robot_test_robot_move_SOUTH);
  tcase_add_test(tc_core, robot_test_robot_move_does_not_fall_off_table_at_00SOUTH);
  tcase_add_test(tc_core, robot_test_robot_move_does_not_fall_off_table_at_00WEST);
  tcase_add_test(tc_core, robot_test_robot_move_does_not_fall_off_table_at_04WEST);
  tcase_add_test(tc_core, robot_test_robot_move_does_not_fall_off_table_at_04NORTH);
  tcase_add_test(tc_core, robot_test_robot_move_does_not_fall_off_table_at_44NORTH);
  tcase_add_test(tc_core, robot_test_robot_move_does_not_fall_off_table_at_44EAST);
  tcase_add_test(tc_core, robot_test_robot_move_does_not_fall_off_table_at_40EAST);
  tcase_add_test(tc_core, robot_test_robot_move_does_not_fall_off_table_at_40SOUTH);
  tcase_add_test(tc_core, robot_test_robot_place);
  tcase_add_test(tc_core, robot_test_robot_place_at_13EAST);
  tcase_add_test(tc_core, robot_test_robot_exec_REPORT);
  tcase_add_test(tc_core, robot_test_robot_exec_PLACE);
  tcase_add_test(tc_core, robot_test_robot_exec_MOVE);
  tcase_add_test(tc_core, robot_test_robot_exec_LEFT);
  tcase_add_test(tc_core, robot_test_robot_exec_RIGHT);

  suite_add_tcase(s, tc_core);

  return s;
}
