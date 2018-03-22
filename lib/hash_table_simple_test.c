#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "hash_table_simple_test.h"

START_TEST(hash_table_simple_test_hash_new) {
  hash_t *subject = hash_new(15);

  ck_assert_int_eq(subject->size, 15);
}
END_TEST

START_TEST(hash_table_simple_test_hash_insert) {
  hash_t *subject = hash_new(15);
  hash_insert(subject, "hello", "world");

  ck_assert_str_eq(hash_lookup(subject, "hello"), "world");
}
END_TEST

START_TEST(hash_table_simple_test_hash_multiple_inserts) {
  hash_t *subject = hash_new(15);
  hash_insert(subject, "hello", "world");
  hash_insert(subject, "a", "b");

  ck_assert_str_eq(hash_lookup(subject, "hello"), "world");
  ck_assert_str_eq(hash_lookup(subject, "a"), "b");
}
END_TEST

START_TEST(hash_table_simple_test_hash_lookup_unknown_key_returns_null) {
  hash_t *subject = hash_new(15);
  hash_insert(subject, "hello", "world");
  hash_insert(subject, "a", "b");

  ck_assert_ptr_null(hash_lookup(subject, "foo"));
}
END_TEST

Suite * hash_table_simple_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Hash Table simple");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, hash_table_simple_test_hash_new);
  tcase_add_test(tc_core, hash_table_simple_test_hash_insert);
  tcase_add_test(tc_core, hash_table_simple_test_hash_multiple_inserts);
  tcase_add_test(tc_core, hash_table_simple_test_hash_lookup_unknown_key_returns_null);
  suite_add_tcase(s, tc_core);

  return s;
}
