//
// Created by Josh Martin on 2019-03-18.
//

#include <printf.h>
#include "printer.h"

banker * _this;


void printer_init(banker * them) {
    _this = them;
}

void print_available(){
    printf("Available system resources are::\n");
    _printer_n(_this->available);
}

void print_maximum() {
    printf("Processes (maximum resources):\n");
    _printer_nXm(_this->maximum);
}

void print_allocation(){
    printf("Processes (currently allocated resources):\n");
    _printer_nXm(_this->allocation);
}

void print_need() {
    printf("(Need = maximum resources - currently allocated resources)\n"
           "Processes (possibly needed resources):\n");
    _printer_nXm(_this->need);
}

void _print_title(int size){

    printf("%2c", ' ');

    for (int j = 0; j < size; ++j) {
        char title_letter = 65 + j;
        printf("%2.9c", title_letter);
    }

    printf("\n");
}
void _printer_n(int arr[NUMBER_OF_CUSTOMERS]){
    int size_i = NUMBER_OF_CUSTOMERS;

    _print_title(size_i);

    for (int i = 0; i < size_i; ++i)
        printf("%d ", arr[i]);

    printf("\n");

}

void _printer_nXm(int arr[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]) {

    int size_i = NUMBER_OF_CUSTOMERS,
            size_j = NUMBER_OF_RESOURCES;

    _print_title(size_j);

    for (int i = 0; i < size_i; ++i) {
        printf("P%d ", i+1);
        for (int j = 0; j < size_j; ++j)
            printf("%d ", arr[i][j] );

        printf("\n");
    }
}

void print_all(){
    print_available();
    print_maximum();
    print_allocation();
    print_need();
}