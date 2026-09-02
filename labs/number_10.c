#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>

#define SIZE 33

bool check_base(int base) {
    if (base < 2 || base > 36)
    {
        return false;
    }

    return true;
}

void* convert_from_decimal(int base, int number) {
    int sign = 1;

    if (number < 0) {
        sign = -1;
        number *= -1;
    }

    int r;
    static char buf[SIZE];
    char* ptr = buf + SIZE - 1;
    *ptr = '\0';

    while(number > 0) {
        r = number % base;
        *--ptr = (r > 9)? r - 10 + 'A' : r + '0';
        number /= base;
    }

    if (sign == -1) {
        *--ptr = '-';
    }

    return ptr;
}

int convert_to_decimal(char* number, int base) 
{
    if (!number)
    {
        return 0;
    }
    int symbol = 1;
    char *ptr = NULL;
    int result = 0;

    if (*number == '-')
    {
        symbol = -1;
        ptr = number + 1;
    }
    else
    {
        ptr = number;
    }
    while (*ptr)
    {
        result = result * base + (isdigit(*ptr) ? *ptr  - '0' : *ptr - 'A' + 10);
        ptr++;
    }
    return result * symbol;
}

int check_integer(char *digits, int base)
{
    int i = 0;
    if (!digits)
        return 0;
    if(digits[i] == '-') 
    {
        i = 1;
    }

    if (base >= 10)
    {
        while(digits[i])
        {
            if (digits[i] - 'A' + 10 >= base) 
            {
                return 0;
            }
            i++;
        }
    }
    else {
        while(digits[i])
        {
            if (digits[i] - '0' >= base) 
            {
                return 0;
            }
            i++;
        }
    }
    return 1;
}

int main() {
    int base;
    int flag = 0;

    printf("enter the base of the number system: ");
    scanf("%d", &base);

    if (!check_base(base))
    {
        printf("invalid base\n");
        return 1;
    }
    char digits[100];
    int max_digit = INT_MIN;

    while (1)
    {
        printf("enter digit:\n");
        scanf("%s", digits);

        if (strcmp(digits, "stop") == 0 || strcmp(digits, "Stop") == 0)
        {
            break;
        }

        if (!check_integer(digits, base))
        {
            printf("invalid integer for base %d\n", base);
            return 1;
        }
        flag = 1;
        
        int num = convert_to_decimal(digits, base); 

        if (abs(num) > abs(max_digit))
        {
            max_digit = num;
        }

    }

    char res[256];
    int len = 0;
    int max_elem = max_digit;

    if (flag == 1)
    {
        printf("the maximum element in base 10: %d\n", max_elem);

        printf("max value in base 9: %s\n", convert_from_decimal(9, max_elem));
        printf("max value in base 18: %s\n", convert_from_decimal(18, max_elem));
        printf("max value in base 27: %s\n", convert_from_decimal(27, max_elem));
        printf("max value in base 36: %s\n", convert_from_decimal(36, max_elem));
    }
    return 0;
}
