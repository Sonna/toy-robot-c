#include <check.h>

#include "prime_test.h"

START_TEST(prime_test_is_prime) {
  int subject = is_prime(757);

  ck_assert(subject);
}
END_TEST

START_TEST(prime_test_is_not_prime) {
  int subject = is_prime(42);

  ck_assert(!subject);
}
END_TEST

START_TEST(prime_test_next_prime) {
  int subject = next_prime(758);

  ck_assert_int_eq(subject, 761);
}
END_TEST

Suite * prime_test_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Prime");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, prime_test_is_prime);
  tcase_add_test(tc_core, prime_test_is_not_prime);
  tcase_add_test(tc_core, prime_test_next_prime);
  suite_add_tcase(s, tc_core);

  return s;
}
