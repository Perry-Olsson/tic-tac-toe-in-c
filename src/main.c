#include <stdio.h>
#include "helper.h"

int main() 
{
    int num1;
    int num2;

    num1 = 10;
    num2 = 20;
    int sum = num1 + num2;
    char my_string[100];
    snprintf(my_string, 100, "The sum is %d", sum);
    for (int i = 0; my_string[i] != '\0'; i++) {
        printf("%c", my_string[i]);
    }
    printf("\n");
    print_text();
    return 0;
}
