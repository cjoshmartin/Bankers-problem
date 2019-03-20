//
// Created by Josh Martin on 2019-03-16.
//

#ifndef H4_UPDATE_H
#define H4_UPDATE_H

#include "bankers_struct.h"

int isGreaterThenZero(int val);


void updateNeed(banker * _them);

void allocation_resources(banker * _this, int n, int available[NUMBER_OF_RESOURCES], int need[NUMBER_OF_RESOURCES], int allocation[NUMBER_OF_RESOURCES]);
void free_resources(banker * _this, int n, int available[NUMBER_OF_RESOURCES], int need[NUMBER_OF_RESOURCES], int allocation[NUMBER_OF_RESOURCES]);

void updateAvailable(int n, banker * _them);
#endif //H4_UPDATE_H
