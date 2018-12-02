#include "SquareArchStructs.h"

#define SELF_MASK 0b1
#define COMPLETE_MASK 0b11111

#define NO_ROTATION 0
#define ROTATE_RIGHT 1
#define ROTATE_DOWN 2
#define ROTATE_LEFT 3
#define CORRECTION_RIGHT_SHIFT 4

/**
* Finds how many bits to shift over to achive a rotation to the given direction.
*
* @param direction the direction to face to
* @return the number of bits to shift
*/
int getShiftBasedOnDirection(enum GateDirection direction){
  int toShift = NO_ROTATION;
  if(direction == RIGHTWARDS){
    toShift = ROTATE_RIGHT;
  } else if(direction == DOWNWARDS){
    toShift = ROTATE_DOWN;
  } else if(direction == LEFTWARDS){
    toShift = ROTATE_LEFT;
  }
  return toShift;
}

/**
* Rotates a bit squences from up to the direction specified. The bit sequence
* is in the format 0bTRBLS where T is Top, R is right and so on, S is self.
*
* @param bit the bit to rotate
* @param direction the direction to rotate the bit to
* @return the newly rotated set of bits
*/
char rotateBit(char bit, enum GateDirection direction){
  bit = bit & (~SELF_MASK);
  int toRotateBits = ((int)bit) & (~SELF_MASK);

  int toShift = getShiftBasedOnDirection(direction);

  toRotateBits = toRotateBits << toShift;
  int overflow = toRotateBits & ~COMPLETE_MASK;
  overflow = overflow >> CORRECTION_RIGHT_SHIFT;
  return ((bit & SELF_MASK) | overflow | toRotateBits) & COMPLETE_MASK;
}

void getGate(char *original, char *rotated, enum GateDirection direction){

}
