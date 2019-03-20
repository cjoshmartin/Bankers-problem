//
// Created by Josh Martin on 2019-03-18.
//

#include <printf.h>
#include "printer.h"

#define Number_of_lines 50
banker * _this;

void _print_title(int size){

    printf("%2c", ' ');

    for (int j = 0; j < size; ++j) {
        char title_letter = 65 + j;
        printf("%3c", title_letter);
    }

    printf("\n");
}

void _print_lines(int size){
    for (int i = 0; i <size ; ++i) {
        printf("-");
    }
    printf("\n");
}

void _printer_n(int arr[NUMBER_OF_RESOURCES]){
    int size_i = NUMBER_OF_RESOURCES;

    _print_title(size_i);
    printf("%3c", ' ');

    for (int i = 0; i < size_i; ++i)
        printf("%3d", arr[i]);

    printf("\n");

}

void _printer_nXm(int arr[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]) {

    int size_i = NUMBER_OF_CUSTOMERS,
            size_j = NUMBER_OF_RESOURCES;

    _print_title(size_j);

    for (int i = 0; i < size_i; ++i) {
        printf("P%d", i+1);
        for (int j = 0; j < size_j; ++j)
            printf("%3d", arr[i][j] );

        printf("\n");
    }
}

void printer_init(banker * them) {
    _this = them;
}

void print_available(){
    printf("Available system resources are:\n");
    _printer_n(_this->available);
}

void print_request(int request [NUMBER_OF_RESOURCES]) {
    printf("REQUESTING RESOURCES ARRAY:\n");
    _print_lines(Number_of_lines);
    _printer_n(request);
    _print_lines(Number_of_lines);
}

void print_release(int release[NUMBER_OF_RESOURCES]) {
    printf("RELEASING RESOURCES ARRAY:\n");
    _print_lines(Number_of_lines);
    _printer_n(release);
    _print_lines(Number_of_lines);
}

void print_maximum() {
    printf("MAXIMUM RESOURCES:\n");
    _printer_nXm(_this->maximum);
}

void print_allocation(){
    printf("ALLOCATED RESOURCES:\n");
    _printer_nXm(_this->allocation);
}

void print_need() {
    printf("NEED, UPDATED:\n");
    _printer_nXm(_this->need);
}

void print_all(){
    printf("\n");
    _print_lines(Number_of_lines);
    print_available();
    print_maximum();
    print_allocation();
    print_need();
    _print_lines(Number_of_lines);
}

