#ifndef SQUARE_ARCH_STRUCTS_H_
#define SQUARE_ARCH_STRUCTS_H_

struct Node {
  int x;
  int y;
  char* lut;
};

struct DieInfo {
  int xMax;
  int yMax;
  struct Node* nodes;
  char* bankA;
  char* bankB;
  char* externalData;
};

#define OR_GATE {0, 31, 31, 31, 31, 31, 31, 31, \
                  31, 31, 31, 31, 31, 31, 31, 31, \
                  31, 31, 31, 31, 31, 31, 31, 31, \
                  31, 31, 31, 31, 31, 31, 31, 31}

#define AND_GATE {0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , \
                   0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , \
                   0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , \
                   0 , 0 , 0 , 0 , 0 , 0 , 0 , 31}

#define ON_GATE  {31, 31, 31, 31, 31, 31, 31, 31, \
                  31, 31, 31, 31, 31, 31, 31, 31, \
                  31, 31, 31, 31, 31, 31, 31, 31, \
                  31, 31, 31, 31, 31, 31, 31, 31}

#define OFF_GATE {0, 0, 0, 0, 0, 0, 0, 0, \
                  0, 0, 0, 0, 0, 0, 0, 0, \
                  0, 0, 0, 0, 0, 0, 0, 0, \
                  0, 0, 0, 0, 0, 0, 0, 0}

#endif
