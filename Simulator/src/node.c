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

/**
* Finds the data which a node will output given the given inputs.
*
* @param info the die info used to find the external data
* @param x the x position of the node querry
* @param y the y position of the node querry
* @param bank the 2d array which contains all node outputs
* @param shift the number of bits to shift the value to the left
* @return the value outputed from the node shifted shift to the left
*/
char getDataFromNodeIndex(struct DieInfo* info, int x, int y, char* bank,
                          int shift){
  if(x < 0){
    return info->externalData[info->xMax * 2 + info->yMax * 2 - y - 1] << shift;
  }
  if(x >= info->xMax){
    return info->externalData[info->xMax + y] << shift;
  }
  if(y < 0){
    return info->externalData[x] << shift;
  }
  if(y >= info->yMax){
    return info->externalData[info->xMax * 2 + info->yMax - x - 1] << shift;
  }

  return bank[x + y * info->xMax];
}

/**
* Finds the output of the given node based on the nodes around it. Looks in
* Die info to find the external data and looks in result map for the previous
* node outputs.
*
* @param node the node for which to generate the output
* @param info the die info which the nodes live in.
* @param resultMap the previous results from all the nodes
* @return the new result of this node
*/
char getNodeOutput(struct Node* node, struct DieInfo* info, char* resultMap){
  char top    = getDataFromNodeIndex(info, node->x, node->y - 1, resultMap,
                                     TOP_SHIFT);
  char bottom = getDataFromNodeIndex(info, node->x, node->y + 1, resultMap,
                                     BOTTOM_SHIFT);
  char right  = getDataFromNodeIndex(info, node->x + 1, node->y, resultMap,
                                     RIGHT_SHIFT);
  char left   = getDataFromNodeIndex(info, node->x - 1, node->y, resultMap,
                                     LEFT_SHIFT);
  char self   = getDataFromNodeIndex(info, node->x, node->y, resultMap,
                                     SELF_SHIFT);

  top    &= TOP_MASK;
  bottom &= BOTTOM_MASK;
  right  &= RIGHT_MASK;
  left   &= LEFT_MASK;
  self   &= SELF_MASK;

  char total = top | bottom | right | left | self;

  return node->lut[total];
}

/**
* Updates all the nodes by using the values in readBank and writing them to
* writeBank.
*
* @param info the die info for all the nodes
* @param readBank the bank of data to read from
* @param writeBank the bank of data to write to
* @return 0 on success
*/
int updateAllNodes(struct DieInfo* info, char* readBank, char* writeBank){
  for(int i = 0; i < info->xMax * info->yMax; i++){
    struct Node* currentNode = info->nodes + i;
    writeBank[i] = getNodeOutput(currentNode, info, readBank);
  }
  return 0;
}

/**
* Initializes a die info based on the given look up tables of the nodes.
* Each look up table is an array of 32 8-bit values which represent the output
* of each node based on the inputs.
* The format for node ouputs is TRBLS corresponding to 0b11111. T: Top,
* R: Right, B: Bottom, L: Left, S: Self.
*
* @param luts the look up tables for all the nodes
* @param info the die info which contains the nodes
* @reutrn 0 on success
*/
int initNodes(char* luts, struct DieInfo* info){
  for(int y = 0; y < info->yMax; y++){
    for(int x = 0; x < info->xMax; x++){
      struct Node* currentNode = info->nodes + x + y * info->xMax;
      currentNode->x   = x;
      currentNode->y   = y;
      currentNode->lut = luts + 32 * ( x + y * info->xMax );
      if(*luts != 0 || (x == 3 && y == 1)){
        printf("here");
      }
    }
  }
  return 0;
}
