//
// Created by Josh Martin on 2019-03-18.
//

#ifndef H4_PRINTER_H
#define H4_PRINTER_H

#include "general.h"
#include "my_structs.h"

void printer_init(banker * them);
void print_available();
void print_request(int request[NUMBER_OF_RESOURCES]);
void print_release(int release[NUMBER_OF_RESOURCES]);
void print_need();
void print_maximum();
void print_allocation();
void _printer_n(int arr[NUMBER_OF_CUSTOMERS]);
void _printer_nXm(int arr[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]);
void print_all();
#endif //H4_PRINTER_H
