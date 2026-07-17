#include <stdio.h>

int main(void)
{
    int cents;
    while (1)
    {
        printf("Change owed: ");
        scanf("%d", &cents);

        if (cents < 0)
            break;

        int coins = (cents / 25) + ((cents % 25) / 10) + ((cents % 25 % 10) / 5) + (cents % 25 % 10 % 5);
        printf("%d\n", coins);
    }
    return 0;
}