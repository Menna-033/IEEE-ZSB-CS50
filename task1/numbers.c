#include <stdio.h>
int main(void)
{
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);

    if (x < y && y < z)
    {
        printf("%d\n%d\n%d\n", x, y, z);
    }
    else if (y < x && x < z)
    {
        printf("%d\n%d\n%d\n", y, x, z);
    }
    else if (z > y && x > z)
    {
        printf("%d\n%d\n%d\n", y, z, x);
    }
    else if (y < x && y > z)
    {
        printf("%d\n%d\n%d\n", z, y, x);
    }
    else if (z < y && x < z)
    {
        printf("%d\n%d\n%d\n", x, z, y);
    }
    else if (x < y && x > z)
    {
        printf("%d\n%d\n%d\n", z, x, y);
    }

    printf("\n%d\n%d\n%d", x, y, z);
}