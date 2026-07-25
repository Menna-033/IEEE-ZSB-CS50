#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);

    char s[1000000];
    scanf("%s", s);


    long long sum = 0;

    for (int i = 0; i < n; i++)
    {
      
        int number = s[i] - '0';
        sum = sum + number;
    }

    printf("%lld\n", sum);

    return 0;
}