#include <stdio.h>

int main()
{
    char note[100];
    FILE *ptr;


    ptr = fopen("notes.txt", "w");
    
    printf("Write your note: ");
    scanf("%s", note); 
    
    
    fprintf(ptr, "%s", note); 
    fclose(ptr);

    
    ptr = fopen("notes.txt", "r");
    fscanf(ptr, "%s", note);
    
    printf("Your note is: %s\n", note);
    fclose(ptr);

    return 0;
}