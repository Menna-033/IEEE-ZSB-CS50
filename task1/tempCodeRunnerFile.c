#include <stdio.h>
int mario(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j >= 0; j--)

        {

            if (i >= j)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}
int main(void)
{
    int z = 0;
    while (1)
    {
        do
        {
            printf("height = ");
            scanf("%d", &z);
        } while (z < 1 || z > 8);
        mario(z);
    }
    return 0;
}
