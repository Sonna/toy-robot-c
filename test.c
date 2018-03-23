#include <check.h>
#include <stdlib.h>

#include "src/robot_test.h"
#include "lib/hash_table_test.h"
#include "lib/prime_test.h"

int main(void)
{
  int number_failed;
  SRunner *sr;

  sr = srunner_create(robot_suite());
  srunner_add_suite(sr, hash_table_suite());
  srunner_add_suite(sr, prime_test_suite());

  //srunner_run_all(sr, CK_NORMAL);
  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
