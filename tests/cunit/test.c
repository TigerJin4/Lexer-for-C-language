#include <stddef.h>
#include "../../string-helpers.h"
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>
#include "test.h"

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void) {
  return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void) {
  return 0;
}

/* The test initialization function.
 * Opens the temporary file used by the test.
 */
void init_test1(void) {
  return;
}

/* The test cleanup function.
 * Closes the temporary file used by the test in particular.
 */
void clean_test1(void) {
  return;
}

/* Simple test of is_digit().
 */
void testISDIGIT_Integers(void) {
  CU_ASSERT_FALSE(is_digit(0));
  CU_ASSERT_FALSE(is_digit(9));
  CU_ASSERT_FALSE(is_digit(-1));
}

void testISDIGIT_Digits(void) {
  CU_ASSERT_TRUE(is_digit('1'));
  CU_ASSERT_TRUE(is_digit('0'));
  CU_ASSERT_TRUE(is_digit('9'));
}

void testISDIGIT_EscChars(void) {
  CU_ASSERT_FALSE(is_digit('\0'));
  CU_ASSERT_FALSE(is_digit('\"'));
  CU_ASSERT_FALSE(is_digit('\n'));
}
/* IS ALPHA TESTS */
void testISALPHA_Lalphas(void) {
  CU_ASSERT_TRUE(is_alpha('a'));
  CU_ASSERT_TRUE(is_alpha('b'));
  CU_ASSERT_FALSE(is_alpha(':'));
}

void testISALPHA_Ualphas(void) {
  CU_ASSERT_TRUE(is_alpha('A'));
  CU_ASSERT_TRUE(is_alpha('B'));
  CU_ASSERT_FALSE(is_alpha('6'));
}
void testISALPHA_OTHER(void) {
  CU_ASSERT_FALSE(is_alpha('\0'));
  CU_ASSERT_FALSE(is_alpha('\"'));
  CU_ASSERT_FALSE(is_alpha('\n'));
}

/* IS SPACE TESTS */
void testISSPACE_ALPHA(void) {
  CU_ASSERT_FALSE(is_space('a'));
  CU_ASSERT_FALSE(is_space('B'));
  CU_ASSERT_FALSE(is_space('\0'));
}

void testISSPACE_DIGIT(void) {
  CU_ASSERT_FALSE(is_space('1'));
  CU_ASSERT_FALSE(is_space('2'));
  CU_ASSERT_FALSE(is_space('\n'));
}
void testISSPACE_SPACE(void) {
  CU_ASSERT_TRUE(is_space(' '));
}

/* IS IDENTIFIER COMPONENT TESTS */
void testISCOMP_ALPHA(void) {
  CU_ASSERT_TRUE(is_identifier_component('a'));
  CU_ASSERT_TRUE(is_identifier_component('B'));
  CU_ASSERT_FALSE(is_identifier_component('\0'));
}

void testISCOMP_DIGIT(void) {
  CU_ASSERT_TRUE(is_identifier_component('1'));
  CU_ASSERT_TRUE(is_identifier_component('2'));
  CU_ASSERT_FALSE(is_identifier_component('\n'));
}
void testISCOMP_UNDERSCORE(void) {
  CU_ASSERT_TRUE(is_identifier_component('_'));
}

/* IS IDENTIFIER TESTS */
void testISID_ALPHA(void) {
  CU_ASSERT_TRUE(is_valid_identifier("a"));
  CU_ASSERT_TRUE(is_valid_identifier("int"));
}

void testISID_DIGIT(void) {
  CU_ASSERT_TRUE(is_valid_identifier("124"));
  CU_ASSERT_TRUE(is_valid_identifier("042"));
}
void testISID_COMBINATION(void) {
  CU_ASSERT_TRUE(is_valid_identifier("1_2r"));
  CU_ASSERT_TRUE(is_valid_identifier("4e__2r"));
  CU_ASSERT_TRUE(is_valid_identifier("_4466gr"));
}

/* STRCONCAT tests */
void testISCON(void) {
  char* output1 = "Hello World";
  char* input1[2] = {"Hello ", "World"};
  CU_ASSERT_STRING_EQUAL(str_concat(input1,2), output1);

  char* output2 = "I Love CS61C!";
  char* input2[5] = {"I", " Love ", "CS6", "1C", "!"};
  CU_ASSERT_STRING_EQUAL(str_concat(input2, 5), output2);
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main() {
  CU_TestInfo isdigit_tests[] = {{"Test actual digits", testISDIGIT_Digits},
                                 {"Test esc chars", testISDIGIT_EscChars},
                                 {"Test numbers", testISDIGIT_Integers},
                                 CU_TEST_INFO_NULL};
  CU_TestInfo isalpha_tests[] = {{"Test lowercase", testISALPHA_Lalphas},
                                 {"Test uppercase", testISALPHA_Ualphas},
                                 {"Test esc chars", testISALPHA_OTHER},
                                 CU_TEST_INFO_NULL};
  CU_TestInfo isspace_tests[] = {{"Test digits", testISSPACE_ALPHA},
                                 {"Test alphabet", testISSPACE_DIGIT},
                                 {"Test space", testISSPACE_SPACE},
                                 CU_TEST_INFO_NULL};
  CU_TestInfo is_identifier_component_tests[] = {{"Test alphabet", testISCOMP_ALPHA},
                                                 {"Test digit", testISCOMP_DIGIT},
                                                 {"Test underscore", testISCOMP_UNDERSCORE},
                                                 CU_TEST_INFO_NULL};
  CU_TestInfo is_valid_identifier_tests[] = {{"Test digits", testISID_DIGIT},
                                             {"Test alphabet", testISID_ALPHA},
                                             {"Test combination", testISID_COMBINATION},
                                             CU_TEST_INFO_NULL};
  CU_TestInfo str_concat_tests[] = {{"test1", testISCON},
                                             CU_TEST_INFO_NULL};
  CU_SuiteInfo suites[] = {{"is_digit testing", init_suite1, clean_suite1,
                           isdigit_tests},
                           {"is_alpha testing", init_suite1, clean_suite1,
                           isalpha_tests},
                           {"is_space testing", init_suite1, clean_suite1,
                           isspace_tests},
                           {"is_identifier_component testing", init_suite1, clean_suite1,
                           is_identifier_component_tests},
                           {"is_valid_identifier testing", init_suite1, clean_suite1,
                           is_valid_identifier_tests},
                           {"str_concat testing", init_suite1, clean_suite1,
                           str_concat_tests},
                           CU_SUITE_INFO_NULL};

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  if (CU_register_suites(suites)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
