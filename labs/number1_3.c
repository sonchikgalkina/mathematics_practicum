#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum status_code {
    ok,
    error_memory,
    error_base,
    error_argument
};

void print_errors(int error) {
    switch(error) {
        case error_memory:
            printf("error with memory allocation\n");
            break;

        case error_base:
            printf("wrong base\n");
            break;

        case error_argument:
            printf("this is wrong\n");
            break;

        default:
            break;
    }
}

int sum_digits(long long int number1, long long int number2) {
    long long int sum = 0;
    long long int carry = 0;

    sum = number1 ^ number2;
    carry = (number1 & number2) << 1;

    while (carry > 0) {
        long long int tmp = sum;
        sum = sum ^ carry;
        carry = (tmp & carry) << 1;
    }
    return sum;
}

int negative_digit(int number) {
    return sum_digits(~number, 1);
}

int subtraction(int number1, int number2) {
    return sum_digits(number1, negative_digit(number2));
}

enum status_code converting_number(long long int number, unsigned int r, char** result) {
    int remainder = 0;

    if (r < 1 || r > 5) {
        return error_base;
    }

    int count = 0;
    int flag = 0;
    

    if (number < 0) {
        number = negative_digit(number);
        count = sum_digits(count, 1);
        flag = 1;
    }

    long long int new_number = number;

    while (new_number > 0) {
        count = sum_digits(count, 1);
        new_number >>= r;
    }

    if (flag) {
        *result = (char*)malloc(sizeof(char) * sum_digits(count, 1));

        if (*result == NULL) {
            return error_memory;
        }

        (*result)[count] = '\0';
        (*result)[0] = '-';
    }

    else {
        *result = (char*)malloc(sizeof(char) * sum_digits(count, 1));
        if (*result == NULL) {
            return error_memory;
        }
        (*result)[count] = '\0';
    }
    while (number) {
        remainder = number & subtraction((1 << r), 1);
        count = subtraction(count, 1);
        (*result)[count] = (remainder < 10) ? sum_digits(remainder, '0') : subtraction(sum_digits(remainder, 'A'), 10);
        number >>= r;
    }
    return ok;
}

int main() {
    long long int number;
    printf("enter a digit in 10 in decimal notation: \n");

    if (scanf("%lld", &number) != 1) {
        return error_argument;
    }

    int r;
    printf("enter degree of 2: \n");

    if (scanf("%d", &r) != 1) {
        return error_base;
    }

    char* result = NULL;

    enum status_code n = converting_number(number, r, &result);
    if (n == ok) {
        printf("a %lld in %d system: \n", number, 1 << r);
        printf("%s\n", result);
    }
    else {
        print_errors(n);
    }
    free(result);
}
