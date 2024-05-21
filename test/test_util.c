#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <app/util.h>

void test_match_handler_pattern(void **state) {
  (void) state; /* unused */

  const char *pattern = "/api/*/user/*";
  const char *uri = "/api/v1/user/123";

  char **result = match_handler_pattern(pattern, uri);

  assert_non_null(result);
  assert_string_equal(result[0], "v1");
  assert_string_equal(result[1], "123");
  assert_null(result[2]);

}

int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_match_handler_pattern),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
