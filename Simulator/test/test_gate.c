#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdio.h>
#include "gate.c"
#include "SquareArchStructs.h"
#include "BinaryPrinting.h"

void assertBin(char actual, char expected){
  if(actual != expected){
    printf("Expected "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(expected));
    printf(" but got "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(actual));
    printf(".\n");
  }
}

void test_getShift(){
  CU_ASSERT_EQUAL(0, getShiftBasedOnDirection(UPWARDS));
  CU_ASSERT_EQUAL(1, getShiftBasedOnDirection(RIGHTWARDS));
  CU_ASSERT_EQUAL(2, getShiftBasedOnDirection(DOWNWARDS));
  CU_ASSERT_EQUAL(3, getShiftBasedOnDirection(LEFTWARDS));
}

void test_rotateBits(){
  int top = 0;
  int right = 1;
  int bottom = 0;
  int left = 1;
  int self = 0;

  char bits = (top << 4) | (right << 3) | (bottom << 2) | (left << 1) | self;
  CU_ASSERT_EQUAL(0b10100, rotateBit(bits, RIGHTWARDS));
  assertBin(rotateBit(bits, RIGHTWARDS), 0b10100);

  CU_ASSERT_EQUAL(0b10100, rotateBit(bits, LEFTWARDS));
  assertBin(rotateBit(bits, LEFTWARDS), 0b10100);

  CU_ASSERT_EQUAL(0b01010, rotateBit(bits, DOWNWARDS));
  assertBin(rotateBit(bits, DOWNWARDS), 0b01010);

  CU_ASSERT_EQUAL(0b01010, rotateBit(bits, UPWARDS));
  assertBin(rotateBit(bits, UPWARDS), 0b01010);

  top = 1;
  right = 0;
  bottom = 0;
  left = 0;
  self = 1;
  bits = (top << 4) | (right << 3) | (bottom << 2) | (left << 1) | self;

}

void test_rotateLeft(){
  getGate(0,0,0);
}

int testGate (){

  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if(CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  pSuite = CU_add_suite("Gate Suite", NULL, NULL);
  if(NULL == pSuite){
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if(NULL == CU_add_test(pSuite, "Test Gate Rotate Left", test_rotateLeft)){
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if(NULL == CU_add_test(pSuite, "Test Get Shift", test_getShift)){
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if(NULL == CU_add_test(pSuite, "Test Rotate Bits", test_rotateBits)){
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
