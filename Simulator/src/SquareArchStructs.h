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

enum GateDirection {UPWARDS, DOWNWARDS, LEFTWARDS, RIGHTWARDS};
enum GateType {OR, AND, ON, OFF, REPEATER, OSCILLATOR};

struct Gate {
        enum GateType gateType;
        enum GateDirection direction;
        char* gateData;
};


#endif
