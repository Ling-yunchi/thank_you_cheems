#pragma once

//bitmask
const int GroundTag = 0;
const int GroundCateoryBitmask =      0x00001111;
const int GroundCollisionBitmask =    0x00000011;
const int GroundContactTestBitmask =  0x10000000;

const int CheemsTag = 1;
const int CheemsCateoryBitmask =      0x10000001;
const int CheemsCollisionBitmask =    0x00000001;
const int CheemsContactTestBitmask =  0x00000111;

const int SoybeanTag = 2;
const int SoybeanCateoryBitmask =     0x01000010;
const int SoybeanCollisionBitmask =   0x00000010;
const int SoybeanContactTestBitmask = 0x01000011;

const int DropTag = 3;
const int DropCateoryBitmask =        0x00000100;
const int DropCollisionBitmask =      0x00000000;
const int DropContactTestBitmask =    0x00000001;

const int AttackTag = 4;
const int AttackCateoryBitmask =      0x01000000;
const int AttackCollisionBitmask =    0x00000000;
const int AttackContactTestBitmask =  0x01000000;
