//
// Created by Josh Martin on 2019-03-16.
//

#include <printf.h>
#include "safe.h"
#include "update/update.h"

int isSafe(int available[NUMBER_OF_RESOURCES], int need[NUMBER_OF_RESOURCES], int allocation[NUMBER_OF_RESOURCES]) {
    // TODO: Do I check a single process or do I find a good seq?
    //  TODO: How do I find a good seq?

    int //  safeSeq[NUMBER_OF_CUSTOMERS],
            working[NUMBER_OF_RESOURCES],
            i =0,
            j =0;

    for (j = 0; j < NUMBER_OF_RESOURCES; j++){
        working[j]= available[j];
    }
    int found = FALSE;
    j=0;
    while ( j < NUMBER_OF_RESOURCES && need[j] < working[j] ) {
        j++;
    } // end of while

    if (j == NUMBER_OF_RESOURCES){
        for(int k= 0; k < NUMBER_OF_RESOURCES; k++)
            working[k] += allocation[k];
        found = TRUE;

    } // end of if

    if(found == FALSE){
        printf("❌: System failed \n\n");
        return FALSE;
    }

    printf("✅: System Successful \n\n");
    return TRUE;
}
