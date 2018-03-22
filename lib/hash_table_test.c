#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "hash_table_test.h"

START_TEST(hash_table_test_hash_new) {
  ht_hash_table* subject = ht_new();

  ck_assert(subject);
  ck_assert_int_eq(subject->size, 53);
  ck_assert_int_eq(subject->count, 0);

  ht_del_hash_table(subject);
  //ck_assert_ptr_null(subject); // ?
}
END_TEST

Suite * hash_table_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Hash Table");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, hash_table_test_hash_new);
  suite_add_tcase(s, tc_core);

  return s;
}
