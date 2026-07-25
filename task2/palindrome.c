#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    long long arr[100000];

    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &arr[i]);
    }


    for (int i = 0; i < n / 2; i++)
    {
        if (arr[i] != arr[n - 1 - i])
        {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");

    return 0;
}