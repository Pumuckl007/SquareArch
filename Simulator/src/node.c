#include "SquareArchStructs.h"

#define TOP_SHIFT 4
#define RIGHT_SHIFT 3
#define BOTTOM_SHIFT 2
#define LEFT_SHIFT 1
#define SELF_SHIFT 0

#define TOP_MASK    0b1 << TOP_SHIFT
#define RIGHT_MASK  0b1 << RIGHT_SHIFT
#define BOTTOM_MASK 0b1 << BOTTOM_SHIFT
#define LEFT_MASK   0b1 << LEFT_SHIFT
#define SELF_MASK   0b1 << SELF_SHIFT

char getDataFromNodeIndex(struct DieInfo* info, int x, int y, char* bank){
  if(x < 0) {
    return info->externalData[info->xMax * 2 + info->yMax * 2 - y - 1];
  }
  if(x > info->xMax) {
    return info->externalData[info->xMax + y];
  }
  if(y < 0) {
    return info->externalData[x];
  }
  if(y > info->yMax) {
    return info->externalData[info->xMax * 2 + info->yMax - x - 1];
  }

  return bank[x + y * info->xMax];
}

char getNodeOutput(struct Node* node, struct DieInfo* info, char* resultMap){
  char top = getDataFromNodeIndex(info, node->x, node->y-1, resultMap);
  char bottom = getDataFromNodeIndex(info, node->x, node->y+1, resultMap);
  char right = getDataFromNodeIndex(info, node->x+1, node->y, resultMap);
  char left = getDataFromNodeIndex(info, node->x-1, node->y, resultMap);
  char self = getDataFromNodeIndex(info, node->x, node->y, resultMap);

  top &= TOP_MASK;
  bottom &= BOTTOM_MASK;
  right &= RIGHT_MASK;
  left &= LEFT_MASK;
  self &= SELF_MASK;

  char total = top | bottom | right | left | self;

  return node->lut[total];
}

int initNodes(char* luts, struct DieInfo* info){
  for(int h = 0; h<info->yMax; h++) {
    for(int w = 0; w<info->xMax; w++) {
      struct Node* currentNode = info->nodes + w + h*info->xMax;
      currentNode->x = w;
      currentNode->y = h;
      currentNode->lut = luts + 32*(w + h*info->xMax);
    }
  }
  return 0;
}
