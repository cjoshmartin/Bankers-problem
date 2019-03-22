//
// Created by Josh Martin on 2019-03-16.
//

#include <stdio.h>
#include "../printer/printer.h"
#include "safe.h"
#include "../update/update.h"

int finishCheck(banker * _them, int finish[NUMBER_OF_CUSTOMERS], int work[NUMBER_OF_RESOURCES]) {
    int unsafe = 0,
    zero_count = 0;

    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i) {
        if (!finish[i]) {
            // check that need is > to work for all resources
            for (int j = 0; j < NUMBER_OF_RESOURCES; ++j) {

                if (_them->need[i][j] > work[j]) {
                    unsafe = 1;	// should loop back and recheck?
                    break;
                }
            }
            // if so, place in safe sequence
            if (!unsafe) {
                for (int j = 0; j < NUMBER_OF_RESOURCES; ++j) {
                    work[j] += _them->allocation[i][j];
                }
                finish[i] = 1;
            }
            else {
                zero_count++;
            }
        }
    }

    return (zero_count > 0) ? 1 : 0;

}

int isSafe(banker *_them, int available[NUMBER_OF_RESOURCES], int need[NUMBER_OF_RESOURCES], int allocation[NUMBER_OF_RESOURCES]) {

    int finish[NUMBER_OF_CUSTOMERS] = {FALSE};
    int work[NUMBER_OF_RESOURCES];

    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
        work[i] = available[i];
    }

    printf("\n\n");
    _print_lines(50);
    printf("Is Safe Check:\n");
    _print_lines(50);
    printf("NeeD :\n");
    _printer_n(need);
    printf("Allocation\n");
    _printer_n(allocation);
    printf("Available\n");
    _printer_n(available);
    _print_lines(50);
    printf("\n");
    _print_lines(50);

    for (int j = 0; j < NUMBER_OF_CUSTOMERS; ++j) {
        if(finishCheck(_them, finish, work))
            continue;

        break;
    }

    // Confirm that all finish[i] are true before leaving allocation
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i) {
        if (!finish[i])
            return FALSE;

    }

    return TRUE;
}


