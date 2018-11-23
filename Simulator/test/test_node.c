#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdio.h>
#include "node.c"
#include "SquareArchStructs.h"
#include "BinaryPrinting.h"

void assertArrays(char* actual, char* expected, int len){
  for(int i = 0; i < len; i++){
    CU_ASSERT_EQUAL(actual[i], expected[i]);
    if(actual[i] != expected[i]){
      printf("Expected "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(expected[i]));
      printf(" but got "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(actual[i]));
      printf(" at %d.\n", i);
    }
  }
}

void test_getNodeOutput(void){
  char bank1[3][3] = {
    { 0b00000, 0b00100, 0b00000 },
    { 0b01000, 0b00001, 0b00010 },
    { 0b00000, 0b10000, 0b00000 }
  };

  char bank2[3][3] = {
    { 0b00000, 0b00000, 0b00000 },
    { 0b00001, 0b00000, 0b00000 },
    { 0b00000, 0b00000, 0b00000 }
  };

  char externalData[12] = {
    0, 0, 0,
    0,
    0,
    1,
    0, 0, 0,
    0,
    0,
    0
  };

  char luts[3][3][32] = {
    {OFF_GATE, OFF_GATE, OFF_GATE},
    {ON_GATE, OR_GATE, OFF_GATE},
    {OFF_GATE, OFF_GATE, OR_GATE}
  };
  struct Node nodes[3][3];
  struct DieInfo info;
  info.xMax  = 3;
  info.yMax  = 3;
  info.nodes = (struct Node*) &nodes;
  info.bankA = (char *) &bank1;
  info.bankB = (char *) &bank2;
  info.externalData = (char *) &externalData;
  initNodes((char *) luts, &info);

  char retVal = getNodeOutput(&( nodes[1][1] ), &info, (char *) &bank1);
  CU_ASSERT_EQUAL_FATAL(retVal, 31);

  retVal = getNodeOutput(&( nodes[0][0] ), &info, (char *) &bank1);
  CU_ASSERT_EQUAL_FATAL(retVal, 0);

  retVal = getNodeOutput(&( nodes[2][2] ), &info, (char *) &bank1);
  CU_ASSERT_EQUAL_FATAL(retVal, 31);
}

void test_getNodeOutputNonSquare(void){
  char bank1[2][3] = {
    { 0b00000, 0b00100, 0b00000},
    { 0b01000, 0b00001, 0b00010}
  };

  char bank2[2][3] = {
    { 0b00000, 0b00000, 0b00000},
    { 0b00000, 0b00000, 0b00000}
  };

  char externalData[10] = {
    0, 0, 0,
    1,
    1,
    0, 1, 0,
    0,
    0
  };

  char luts[2][3][32] = {
    {OFF_GATE, OR_GATE, OR_GATE},
    {ON_GATE, AND_GATE, OFF_GATE}
  };
  struct Node nodes[2][3];
  struct DieInfo info;
  info.xMax  = 2;
  info.yMax  = 3;
  info.nodes = (struct Node*) &nodes;
  info.bankA = (char *) &bank1;
  info.bankB = (char *) &bank2;
  info.externalData = (char *) &externalData;
  initNodes((char *) luts, &info);

  char retVal = getNodeOutput(&( nodes[0][2] ), &info, (char *) &bank1);
  CU_ASSERT_EQUAL_FATAL(retVal, 31);

  retVal = getNodeOutput(&( nodes[0][0] ), &info, (char *) &bank1);
  CU_ASSERT_EQUAL_FATAL(retVal, 0);

  retVal = getNodeOutput(&( nodes[0][1] ), &info, (char *) &bank1);
  CU_ASSERT_EQUAL_FATAL(retVal, 0);
}

void test_updateAllNodes(void){
  char bank1[3][3] = {
    { 0b00000, 0b00100, 0b00000 },
    { 0b01000, 0b00001, 0b00010 },
    { 0b00000, 0b10000, 0b00000 }
  };

  char bank2[3][3] = {
    { 0b00000, 0b00000, 0b00000 },
    { 0b00000, 0b00000, 0b00000 },
    { 0b00000, 0b00000, 0b00000 }
  };

  char externalData[12] = {
    0, 0, 0,
    0,
    0,
    1,
    0, 0, 0,
    0,
    0,
    0
  };

  char luts[3][3][32] = {
    {OFF_GATE, OFF_GATE, OFF_GATE},
    {ON_GATE, OR_GATE, OFF_GATE},
    {OFF_GATE, OFF_GATE, OR_GATE}
  };
  struct Node nodes[3][3];
  struct DieInfo info;
  info.xMax  = 3;
  info.yMax  = 3;
  info.nodes = (struct Node*) &nodes;
  info.bankA = (char *) &bank1;
  info.bankB = (char *) &bank2;
  info.externalData = (char *) &externalData;
  initNodes((char *) luts, &info);

  updateAllNodes(&info, info.bankA, info.bankB);

  char results[3][3] = {
    { 0b00000, 0b00000, 0b00000 },
    { 0b11111, 0b11111, 0b00000 },
    { 0b00000, 0b00000, 0b11111 }
  };
  assertArrays(info.bankB, &results[0][0], 9);

}

void test_updateAllNodesNonSquare(void){
  char bank1[3][5] = {
    { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000 },
    { 0b01000, 0b00001, 0b01010, 0b00000, 0b00000 },
    { 0b00000, 0b10000, 0b00000, 0b00000, 0b00000 }
  };

  char bank2[3][5] = {
    { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000 },
    { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000 },
    { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000 }
  };

  char externalData[16] = {
    0, 0, 0, 1, 1,
    0,
    1,
    0,
    0, 0, 0, 1, 1,
    0,
    0,
    0
  };

  char lutTest[32] = OFF_GATE;


  char luts[3][5][32] = {
    {OFF_GATE, OFF_GATE, OFF_GATE, BOTTOM_GATE, TOP_GATE},
    {ON_GATE, OR_GATE, ON_GATE, LEFT_GATE, RIGHT_GATE},
    {OFF_GATE, OFF_GATE, OR_GATE, BOTTOM_GATE, TOP_GATE}
  };

  struct Node nodes[3][5];
  struct DieInfo info;
  info.xMax  = 5;
  info.yMax  = 3;
  info.nodes = (struct Node*) &nodes;
  info.bankA = (char *) &bank1;
  info.bankB = (char *) &bank2;
  info.externalData = (char *) &externalData;
  initNodes((char *) luts, &info);

  updateAllNodes(&info, info.bankA, info.bankB);

  char results[3][5] = {
    { 0b00000, 0b00000, 0b00000, 0b00000, 0b11111 },
    { 0b11111, 0b11111, 0b11111, 0b11111, 0b11111 },
    { 0b00000, 0b00000, 0b11111, 0b11111, 0b00000 }
  };

  assertArrays(info.bankB, &results[0][0], 15);

}

void test_initNodes(void){
  char luts[1][32] = { AND_GATE };

  struct Node nodes[1][1];
  struct DieInfo info;
  info.xMax  = 1;
  info.yMax  = 1;
  info.nodes = (struct Node*) &nodes;
  int retVal = initNodes((char *) luts, &info);
  CU_ASSERT_EQUAL_FATAL(nodes[0][0].x, 0);
  CU_ASSERT_EQUAL_FATAL(nodes[0][0].y, 0);
  CU_ASSERT_EQUAL_FATAL(nodes[0][0].lut[31], 31);

  char luts2[3][3][32] = {
    {OFF_GATE, OFF_GATE, OFF_GATE},
    {ON_GATE, OR_GATE, OFF_GATE},
    {OFF_GATE, OFF_GATE, OFF_GATE}
  };
  struct Node nodes2[3][3];
  struct DieInfo info2;
  info2.xMax  = 3;
  info2.yMax  = 3;
  info2.nodes = (struct Node*) &nodes2;
  retVal      = initNodes((char *) luts2, &info2);
  CU_ASSERT_EQUAL_FATAL(nodes2[1][1].x, 1);
  CU_ASSERT_EQUAL_FATAL(nodes2[1][1].y, 1);
  CU_ASSERT_EQUAL_FATAL(nodes2[1][1].lut[0], 0);
}

int testNode (){

  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if(CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  pSuite = CU_add_suite("Node Suite", NULL, NULL);
  if(NULL == pSuite){
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if(NULL == CU_add_test(pSuite, "Test Get Node Output", test_getNodeOutput)){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if(NULL ==
     CU_add_test(pSuite, "Test Get Node Output With Non Square",
                 test_getNodeOutput)){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if(NULL == CU_add_test(pSuite, "Test Init Nodes", test_initNodes)){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if(NULL == CU_add_test(pSuite, "Test Update Nodes", test_updateAllNodes)){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if(NULL ==
     CU_add_test(pSuite, "Test Update Nodes Non Square",
                 test_updateAllNodesNonSquare)){
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
