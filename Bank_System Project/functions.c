#include "functions.h"
Customer customers[MAX_CUSTOMERS];
int customer_count = 0;
int save_data(Customer customers[], int count)
{

    if (count < 0)
    {
        printf("[!] Critical Error: Invalid record count.\n");
        return 0;
    }

    FILE *file = fopen("customers.txt", "w");
    if (file == NULL)
    {
        printf("[!] Error: Could not open file (Access Denied).\n");
        return 0;
    }
    int saved_count = 0;
    for (int i = 0; i < count; i++)
    {

        if (customers[i].id <= 0)
        {
            printf("[!] Warning: Corrupted ID found for record %d. Skipping...\n", i);
            continue;
        }

        int written = fprintf(file, "%s|%d|%s|%.2f\n", customers[i].name, customers[i].id,
                              customers[i].phone, customers[i].cash);
        if (written > 0)
        {
            saved_count++;
        }
    }
    //  الحماية عند الإغلاق
    if (fclose(file) != 0)
    {
        printf("[!] Error: Failed to close the file properly (Data might be incomplete).\n");
        return 0;
    }

    if (saved_count == count)
    {
        printf("[✓] Success: %d records saved securely.\n", saved_count);
        return 1;
    }
    else
    {
        printf("[!] Warning: Only %d/%d records were saved safely.\n", saved_count, count);
        return 0;
    }
}
int load_data(Customer customers[])
{
    FILE *file = fopen("customers.txt", "r");
    if (file == NULL)
    {
        printf("No existing database found. Starting fresh.\n");
        return 0;
    }

    char line[256];
    int count = 0;

    while (count < MAX_CUSTOMERS && fgets(line, sizeof(line), file) != NULL)
    {

        int parsed = sscanf(line, "%99[^|]|%d|%19[^|]|%f", customers[count].name,
                            &customers[count].id, customers[count].phone, &customers[count].cash);
        if (parsed == 4)
        {
            count++;
        }
    }

    fclose(file);
    printf("Successfully loaded %d customer(s).\n", count);
    return count;
}

void create_customer(void)
{
    Customer new_customer;
    int valid;
    do
    {
        valid = 1;
        printf("Enter Your Name:\n");
        fgets(new_customer.name, sizeof(new_customer.name), stdin);
        new_customer.name[strcspn(new_customer.name, "\n")] = '\0';
        if (strlen(new_customer.name) == 0)
        {
            valid = 0;
        }
        for (int i = 0; i < strlen(new_customer.name); i++)
        {
            if ((new_customer.name[i] >= 'A' && new_customer.name[i] <= 'Z') ||
                (new_customer.name[i] >= 'a' && new_customer.name[i] <= 'z') ||
                (new_customer.name[i] == ' '))
            {
            }
            else
            {
                valid = 0;
                break;
            }
        }
        if (valid == 0)
        {
            printf("invalid name enter again\n");
        }
    }
    while (valid == 0);
    do
    {
        valid = 1;
        printf("Enter Your Phone:\n");
        scanf("%s", new_customer.phone);
        for (int j = 0; j < strlen(new_customer.phone); j++)
        {
            if (new_customer.phone[j] >= '0' && new_customer.phone[j] <= '9')
            {
            }
            else
            {
                valid = 0;
                break;
            }
        }
        if (valid == 0)
        {
            printf("invalid phone enter again \n");
        }
    }
    while (valid == 0);
    do
    {
        valid = 1;

        char cash[20];

        printf("Enter Your Cash:\n");

        scanf("%19s", cash);

        int dots = 0;

        for (int i = 0; i < strlen(cash); i++)
        {
            if (cash[i] == '.')
            {
                dots++;
            }
            else if (cash[i] < '0' || cash[i] > '9')
            {
                valid = 0;
                break;
            }
        }

        if (dots > 1)
        {
            valid = 0;
        }

        if (valid == 1)
        {
            new_customer.cash = atof(cash);
        }

        if (valid == 0)
        {
            printf("invalid cash enter again\n");
        }
    }
    while (valid == 0);
    if (customer_count >= MAX_CUSTOMERS)
    {
        printf("Customer limit reached\n");
        return;
    }

    int max_id = 0;
    for (int j = 0; j < customer_count; j++)
    {
        if (customers[j].id > max_id)
        {
            max_id = customers[j].id;
        }
    }
    new_customer.id = max_id + 1;
    customers[customer_count] = new_customer;
    customer_count++;
    printf("Customer Created Successfully !\n");
    printf("Your id is %i\n",new_customer.id);
}
// deposit
void deposit(void)
{
    int found = 0;
    int ID;

    printf("ID: ");
    scanf("%i", &ID);

    // search for ID in customers
    for (int i = 0; i < customer_count; i++)
    {
        if (customers[i].id == ID)
        {
            found = 1;

            char amount[20];
            float amount_value;
            int valid;

            do
            {
                valid = 1;

                printf("Enter the amount:\n");
                scanf("%19s", amount);

                int dots = 0;

                for (int i = 0; i < strlen(amount); i++)
                {
                    if (amount[i] == '.')
                    {
                        dots++;
                    }
                    else if (amount[i] < '0' || amount[i] > '9')
                    {
                        valid = 0;
                        break;
                    }
                }

                if (dots > 1)
                {
                    valid = 0;
                }

                if (valid == 0)
                {
                    printf("Invalid amount, enter again\n");
                }
            }
            while (valid == 0);

            amount_value = atof(amount);

            customers[i].cash += amount_value;

            printf("New cash: %.2f\n", customers[i].cash);

            break;
        }
    }

    if (found == 0)
    {
        printf("ID not found\n");
    }
}
void transfer_money(Customer customers[], int count)
{
    int sender_id, receiver_id;
    char amount[20];
    float amount_value;

    printf("Enter Sender ID: ");
    scanf("%d", &sender_id);
    printf("Enter Receiver ID: ");
    scanf("%d", &receiver_id);

    if (sender_id == receiver_id)
    {
        printf("Error: Sender and Receiver IDs cannot be the same!\n");
        return;
    }

    int sender_index = -1, receiver_index = -1;
    for (int i = 0; i < count; i++)
    {
        if (customers[i].id == sender_id)
        {
            sender_index = i;
        }
        if (customers[i].id == receiver_id)
        {
            receiver_index = i;
        }
    }

    if (sender_index == -1)
    {
        printf("Error: Sender ID not found!\n");
        return;
    }
    if (receiver_index == -1)
    {
        printf("Error: Receiver ID not found!\n");
        return;
    }
    printf("Enter Amount to Transfer: ");
    scanf("%19s", amount);

    int valid = 1;

    int dots = 0;

    for (int i = 0; i < strlen(amount); i++)
    {
        if (amount[i] == '.')
        {
            dots++;
        }
        else if (amount[i] < '0' || amount[i] > '9')
        {
            valid = 0;
            break;
        }
    }

    if (dots > 1)
    {
        valid = 0;
    }

    if (valid == 0)
    {
        printf("Invalid amount!\n");
    }
    else
    {
        amount_value = atof(amount);

        if (amount_value <= 0)
        {
            printf("Error: Amount must be greater than zero!\n");
        }
        else if (customers[sender_index].cash < amount_value)
        {
            printf("Error: Insufficient cash in sender account!\n");
        }
        else
        {
            customers[sender_index].cash -= amount_value;
            customers[receiver_index].cash += amount_value;
            printf("Transfer successful!\n");
            printf("Sender New Cash Balance: %.2f\n", customers[sender_index].cash);
            printf("Receiver New Cash Balance: %.2f\n", customers[receiver_index].cash);
        }
    }
}
void delete_customer()
{
    int target_id;
    printf("Enter Customer ID to delete: ");
    scanf("%d", &target_id);

    int found_index = -1;

    for (int i = 0; i < customer_count; i++)
    {
        if (customers[i].id == target_id)
        {
            found_index = i;
            break;
        }
    }

    if (found_index == -1)
    {
        printf("Customer with ID %d not found!\n", target_id);
        return;
    }

    for (int i = found_index; i < customer_count - 1; i++)
    {
        customers[i] = customers[i + 1];
    }

    customer_count--;
    printf("Customer deleted successfully!\n");
}

void withdraw()
{
    int target_id;
    char amount[20];
    float amount_value;

    printf("Enter Customer ID: ");
    scanf("%d", &target_id);

    int found_index = -1;

    for (int i = 0; i < customer_count; i++)
    {
        if (customers[i].id == target_id)
        {
            found_index = i;
            break;
        }
    }

    if (found_index == -1)
    {
        printf("Customer not found!\n");
        return;
    }

    printf("Enter amount to withdraw: ");
    scanf("%19s", amount);

    int valid = 1;

    int dots = 0;

    for (int i = 0; i < strlen(amount); i++)
    {
        if (amount[i] == '.')
        {
            dots++;
        }
        else if (amount[i] < '0' || amount[i] > '9')
        {
            valid = 0;
            break;
        }
    }

    if (dots > 1)
    {
        valid = 0;
    }

    if (valid == 0)
    {
        printf("Invalid amount!\n");
        return;
    }

    amount_value = atof(amount);

    if (amount_value <= 0)
    {
        printf("Error: Amount must be greater than zero!\n");
    }
    else if (customers[found_index].cash < amount_value)
    {
        printf("Error: Insufficient balance! (Current balance: %.2f)\n",
               customers[found_index].cash);
    }
    else
    {
        customers[found_index].cash -= amount_value;

        printf("Withdrawal successful! Remaining balance: %.2f\n", customers[found_index].cash);
    }
}
void edit_customer(void)
{
    int found = 0;
    int id;
    printf("Enter ID:");
    scanf("%i", &id);
    getchar(); // consume the newline character left by scanf
    // check if ID is valid
    for (int i = 0; i < customer_count; i++)
    {
        if (customers[i].id == id)

        {
            printf("found\n");
            found = 1;
            printf("Choose your option\n");
            int choice;
            do
            {
                printf("1. Edit name\n");
                printf("2. Edit phone\n");
                printf("3. Exit\n");

                printf("Enter your choice: ");
                scanf("%d", &choice);
                getchar();
                // change name
                if (choice == 1)
                {
                    printf("Enter new name:");
                    fgets(customers[i].name, sizeof(customers[i].name), stdin);
                    customers[i].name[strcspn(customers[i].name, "\n")] = '\0';
                    printf("Customer information updated successfully.\n");
                }
                // change phone
                else if (choice == 2)
                {

                    printf("Enter new phone:");
                    fgets(customers[i].phone, sizeof(customers[i].phone), stdin);
                    customers[i].phone[strcspn(customers[i].phone, "\n")] = '\0';
                    printf("Customer information updated successfully.\n");
                }
                else if (choice == 3)
                {
                    break;
                }
                else
                {
                    printf("Invalid choice, enter again\n");
                }
            }
            while (choice != 3);
        }
    }
    if (found == 0)
    {
        printf("invalid id\n");
    }
}
void print_customer_data(void)
{
    int target_id;
    printf("Enter Customer ID to view: ");
    scanf("%d", &target_id);
    int found = 0;

    for (int i = 0; i < customer_count; i++)
    {
        if (customers[i].id == target_id)
        {
            printf("\n============================================\n");
            printf("         CUSTOMER INFORMATION REPORT        \n");
            printf("============================================\n");
            printf(" [ID]      : %d\n", customers[i].id);
            printf(" [Name]    : %s\n", customers[i].name);
            printf(" [Phone]   : %s\n", customers[i].phone);
            printf(" [Balance] : %.2f $\n", customers[i].cash);
            printf("============================================\n");

            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("[!] Error: Customer ID %d not found in records.\n", target_id);
    }
}
