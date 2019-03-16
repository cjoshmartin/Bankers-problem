//
// Created by Josh Martin on 2019-03-16.
//

#ifndef H4_UPDATE_H
#define H4_UPDATE_H

#include "../my_structs.h"

int isGreaterThenZero(int val);

void calculateANeed(int i, int j, banker _them);

void updateNeed(banker _them);

void updateAvailable(int size, banker _them);
#endif //H4_UPDATE_H
