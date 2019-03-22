//
// Created by Josh Martin on 2019-03-20.
//

#include "utils.h"
#include <stdlib.h>
#include "../bankers_struct.h"

int getRandomResource(int val) {
    int ran = rand();
    if (val < 1)
        return 0;

    int output = ran % val;
    return output;
}


