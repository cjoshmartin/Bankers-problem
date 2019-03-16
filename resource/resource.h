//
// Created by Josh Martin on 2019-03-16.
//

#ifndef H4_RESOURCE_H
#define H4_RESOURCE_H

/* (4 pts) implementation of request_resources
// TODO: These functions should return 0 if successful otherwise -1
// TODO: NEEDS MUTEX LOCKS */

#include <pthread.h>
#include "../my_structs.h"

enum safeState { success= 0, failure = -1 };


// https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/7_Deadlocks.html

int request_resources(int customer_num, int request[], banker _them);

int release_resources(int customer_num, int release[], banker _them);

void *customer(void *strut);

#endif //H4_RESOURCE_H
