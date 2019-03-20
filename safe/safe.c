//
// Created by Josh Martin on 2019-03-16.
//

#include <printf.h>
#include "safe.h"
#include "update/update.h"

int isSafe(banker * _them) {

    int finish[NUMBER_OF_RESOURCES] = {FALSE},
            safeSeq[NUMBER_OF_CUSTOMERS],
            working[NUMBER_OF_CUSTOMERS],
            i =0,
            j =0;

    updateNeed(&_them);

    for (j = 0; j < NUMBER_OF_CUSTOMERS; j++){
        working[j]= _them->available[j];
    }

    while ( i < NUMBER_OF_CUSTOMERS){

        int found = FALSE;

        for(int process = 0; process < NUMBER_OF_CUSTOMERS; process++){

            if(finish[process] == FALSE){
                j=0;
                while (
                        j < NUMBER_OF_CUSTOMERS
                        && _them->need[process][j] > working[j]
                        ) {
                    j++;
                } // end of while

                if (j == NUMBER_OF_RESOURCES){
                    for(int k= 0; k < NUMBER_OF_RESOURCES; k++)
                        working[k] += _them->allocation[process][k];

                    safeSeq[i++] = process;

                    finish[process] = TRUE;

                    found = TRUE;

                } // end of if
            } // end of if
        } // end of for

        if(found == FALSE){
            printf("System failed");
            return FALSE;
        }
    } // end of while , TODO: Could make this into thread

    printf("System is in safe state.\nSafe sequence is: ");
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
        printf("%d ", safeSeq[i]);

    return TRUE;
}
