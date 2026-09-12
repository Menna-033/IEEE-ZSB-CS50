#include "functions.h"
#include <stdio.h>

int main(void)
{
    int choice;
    customer_count = load_data(customers);

    do
    {
        printf("Choose your option\n");
        printf("1. Create Customer\n");
        printf("2. Edit Customer\n");
        printf("3. View Customer\n");
        printf("4. Delete Customer\n");
        printf("5. Deposit\n");
        printf("6. Withdraw\n");
        printf("7. Transfer Money\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");

        char extra;

        if (scanf("%d%c", &choice, &extra) != 2 || extra != '\n')
        {
            printf("Invalid choice!\n");

            continue;
        }
        if (choice == 1)
        {
            create_customer();
            save_data(customers, customer_count);
        }
        else if (choice == 2)
        {
            edit_customer();
            save_data(customers, customer_count);
        }
        else if (choice == 3)
        {
            print_customer_data();
            save_data(customers, customer_count);
        }
        else if (choice == 4)
        {
            delete_customer();
            save_data(customers, customer_count);
        }
        else if (choice == 5)
        {
            deposit();

            save_data(customers, customer_count);
        }
        else if (choice == 6)
        {
            withdraw();
            save_data(customers, customer_count);
        }
        else if (choice == 7)
        {
            transfer_money(customers, customer_count);
            save_data(customers, customer_count);
        }
        else if (choice == 8)
        {
            save_data(customers, customer_count);
            printf("Goodbye!\n");
            return 0;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
    while (choice != 8);
    return 0;
}
