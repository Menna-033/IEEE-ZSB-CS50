#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    char text[10000];
    printf("Text: ");
    fgets(text, sizeof(text), stdin);

    int letters = 0;
    int words = 0;
    int sentences = 0;
    int n = strlen(text);

    for (int i = 0; i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        if (isalpha(text[i]) && (i == 0 || isspace(text[i - 1])))
        {
            words++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }


    float L = ((float)letters / words) * 100;
    float S = ((float)sentences / words) * 100;
    
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);



    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

    return 0;
}