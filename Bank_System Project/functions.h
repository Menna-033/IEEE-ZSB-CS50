#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CUSTOMERS 100
typedef struct
{
    int id;
    char name[100];
    char phone[20];
    float cash;
} Customer;
extern Customer customers[100];
extern int customer_count;
int save_data(Customer customers[], int count);

int load_data(Customer customers[]);

void create_customer(void);

void deposit(void);

void transfer_money(Customer customers[], int count);

void delete_customer(void);

void withdraw(void);

void edit_customer(void);

void print_customer_data(void);
#endif
