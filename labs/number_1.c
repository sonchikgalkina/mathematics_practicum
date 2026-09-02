#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

int multiples(int number, int *result) {
    if (number < 0) {
        number = -number;
    }
    for (int i = 0; i < 100; i += number) {
        if (i % number == 0) {
            result[i] += i;
        }
    }
}

bool prime_composite(int number) {
    if (number > 1) {
        for (int i = 2; i < number; i++) 
            if (number % i == 0) 
                return false;
        return true;    
    }    
    else 
        return true;
}
   
int splitNumber(int number, int* arr) {
    int count = 0;
    int digit;
    if (number < 0) {
        number = -number;
    }
    if (number >= 0 && number < 10) {
        arr[0] = number;
        return 1;
    }
    while (number != 0) {
        digit = number % 10;
        arr[count] = digit;
        count++;
        number /= 10;
    }
    for (int i = count - 1; i <= 0; i--) {
        arr[i] += i;
    }
    return count;
}

void power_table(int number, int table[][number]) {
    table[0][0] = 1;
    for (int i = 1; i < 11; i++) {
        table[i][0] = 1;
        table[i][1] = i;
    }
    for (int i = 2; i < number; i++) {
        table[0][i] = 0;
        table[1][i] = 1;
    }
    for (int base = 2; base < 11; base++) {
        for (int st = 2; st < number; st++) {
            table[base][st] = table[base][st - 1] * base;
        }
    }
}

int Sum(int number, int *summ) {
    int sum_num = 0;
    if (number > 0) {
        for (int i = 1; i <= number; i++) {
            sum_num += i;
        }
        *summ += sum_num;
    }
}

unsigned long long Factorial(unsigned int number, unsigned long long result) {
    for (unsigned int i = 1; i <= number; i++) {
        if (result > ULLONG_MAX / i) {
            return 0;
        }
        result *= i;
    }
    return result;
}

bool integer(const char *str) {
    int string_lenght = strlen(str);
    if (*str == '\0') {
        return false;
    }
    if (*str == '+' || *str == '-') {
        str++;
    }
    if (*str == '0' && *(str + 1) != '\0') {
        return false;
    }
    while (*str) {
        if (*str < '0' || *str > '9') {
            return false;
        }
        str++;
    }
    return true;
}

int main(int argc, char *argv[]) {
    int num = atoi(argv[1]);
    int Num = abs(num);
    if (argc != 3) {
        printf("error\n");
    }
    else {
        if (integer(argv[1])) {
            long int number = atoi(argv[1]);
            if (strlen(argv[2]) != 2 || argv[2][0] != '-' && argv[2][0] != '/') {
                printf("invalid flag\n");
                return 0;
            }
            else {
                if (argv[2][1] == 'h') {
                    int result[100] = {0};
                    if (number < INT_MAX) {
                        multiples(number, result);
                        if (number == 0) {
                            printf("0\n");
                        }
                        for (int i = 0; i < 100; i++) {
                            if (result[i] != 0) {
                                printf("%d\n", result[i]);
                            }
                        }
                    }
                    else {
                        printf("overflow\n");
                    }
                }
                else if (argv[2][1] == 'p') {
                    if (number < INT_MAX) {
                        if (number < 0) {
                            number = -number;
                        }
                        if (prime_composite(number)) {
                            printf("this digit is prime\n");
                        }
                        else {
                            printf("this digit is composite\n");
                        }
                    }
                    else {
                        printf("overflow\n");
                    }
                }
                else if (argv[2][1] == 's') {
                    if (number < INT_MAX) {
                        int arr[100] = {0};
                        int count = splitNumber(number, arr);
                        for (int j = count -1; j >= 0; j--) {
                            printf("%d ", arr[j]);
                        }
                    }
                    else {
                        printf("overflow\n");
                    }
                }
                else if (argv[2][1] == 'e') {
                    if (Num > 10) {
                        printf("error\n");
                        return 0;
                    }
                    int base = 10;
                    int degree = Num;
                    int table[base + 1][degree + 1];
                    power_table(degree + 1, table);
                    for (int base = 0; base <= 10; base++) {
                        printf("\n");
                        for (int j = 0; j <= degree; j++) {
                            printf("%d^%d = %d", base, j, table[base][j]);

                        }
                    }
                    printf("\n");
                    return 0;
                        
                }
                else if (argv[2][1] == 'a') {
                    if (number != 0) {
                        if (number < INT_MAX) {
                            int summ = 0;
                            Sum(number, &summ);
                            if (summ > INT_MAX - number) {
                                printf("error\n");
                                return 0;
                            }
                            else {
                                printf("%d\n", summ);
                            }
                        }
                        else {
                            printf("overflow\n");
                        }
                    }
                    else {
                        printf("error\n");
                    }
                }
                else if (argv[2][1] == 'f') {
                    if (number > 0) {
                        if (number < INT_MAX) {
                            unsigned long long result = 1;
                            long long factorial = Factorial(number, result);
                            printf("%lli\n", factorial);
                        }
                        else {
                            printf("overflow\n");
                        }
                    }
                    else {
                        printf("error\n");
                    }
                }
                else {
                    printf("invalid flag\n");
                }
            }
        }
        else {
            printf("error\n");
        }
        return 0;
    }
    return 0;
}
