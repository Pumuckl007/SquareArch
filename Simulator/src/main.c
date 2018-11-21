#include <stdio.h>
#include "node.c"
#include "SquareArchStructs.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ( byte & 0x80 ? '1' : '0' ), \
  ( byte & 0x40 ? '1' : '0' ), \
  ( byte & 0x20 ? '1' : '0' ), \
  ( byte & 0x10 ? '1' : '0' ), \
  ( byte & 0x08 ? '1' : '0' ), \
  ( byte & 0x04 ? '1' : '0' ), \
  ( byte & 0x02 ? '1' : '0' ), \
  ( byte & 0x01 ? '1' : '0' )

void printBank(char* bank, int r, int c){
  printf("Printing Bank (%i x %i)\n", r, c);
  for(int i = 0; i < r; i++){
    printf("(");
    for(int k = 0; k < c - 1; k++){
      printf(BYTE_TO_BINARY_PATTERN ", ", BYTE_TO_BINARY(bank[i * c + k]));
    }
    printf(BYTE_TO_BINARY_PATTERN ")\n", BYTE_TO_BINARY(bank[i * c + c - 1]));
  }
}

int main(int argc, const char* argv[]){
  char bank1[10][5];
  char bank2[10][5];

  for(int i = 0; i<10; i++){
    for(int k = 0; k<5; k++){
      bank1[i][k] = 0;
      bank2[i][k] = 0;
    }
  }

  char externalData[26] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,
    0,
    1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,
    0,
    0
  };

  char luts[10][3][32] = {
    {ON_GATE, ON_GATE, ON_GATE},
    {OR_GATE, OR_GATE, OR_GATE},
    {OR_GATE, OR_GATE, OR_GATE},
    {OR_GATE, OR_GATE, OR_GATE},
    {OR_GATE, OR_GATE, OR_GATE},
    {OR_GATE, OR_GATE, OR_GATE},
    {OR_GATE, OR_GATE, OR_GATE},
    {OR_GATE, OR_GATE, OR_GATE},
    {OR_GATE, OR_GATE, OR_GATE},
    {OR_GATE, OR_GATE, OR_GATE}
  };
  struct Node nodes[10][3];
  struct DieInfo info;
  info.xMax  = 10;
  info.yMax  = 3;
  info.nodes = (struct Node*) &nodes;
  info.bankA = (char *) &bank1;
  info.bankB = (char *) &bank2;
  info.externalData = (char *) &externalData;
  initNodes((char *) luts, &info);
  printBank(info.bankA, 10, 3);

  updateAllNodes(&info, info.bankA, info.bankB);
  printBank(info.bankB, 10, 3);

  updateAllNodes(&info, info.bankB, info.bankA);
  printBank(info.bankA, 10, 3);
}
