#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "hash_table_f2a_test.h"

START_TEST(hash_table_test_hash_new_from_two_arrays) {
  static const char * keyList[] = {"red", "orange", "yellow", "green", "blue", "violet"};
  static int valuList[] = {1, 43, 640, 747, 42, 42};
  int ix;
  ValType result;

  for (ix = 0; ix < 6; ix++) {
    HashAdd(keyList[ix], valuList[ix]);
  }

  HashGet(&result, "red");
  ck_assert_int_eq(result, 1);
  HashGet(&result, "orange");
  ck_assert_int_eq(result, 43);
  HashGet(&result, "yellow");
  ck_assert_int_eq(result, 640);
  HashGet(&result, "green");
  ck_assert_int_eq(result, 747);
  HashGet(&result, "blue");
  ck_assert_int_eq(result, 42);
  HashGet(&result, "violet");
  ck_assert_int_eq(result, 42);
}
END_TEST

Suite * hash_table_f2a_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Hash Table F2A");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, hash_table_test_hash_new_from_two_arrays);
  suite_add_tcase(s, tc_core);

  return s;
}
