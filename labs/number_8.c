#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

typedef enum {
    ok,
    error_with_number_of_arguments,
    error_opening_file,
    error_argument,
    overflow

} status_code;

void print_errors(int flag) {
    switch(flag) {
        case error_with_number_of_arguments:
            printf("invalid value\n");
            break;
        case error_opening_file:
            printf("error with file\n");
            break;
        case error_argument:
            printf("it's wrong argument\n");
            break;
        default:
            break;
    }
}

char* remove_zeros(char* str) {
    int i, j = 0;
    int len = strlen(str);
    while (str[j] == '0') {
        j++;
    }
    if (j == len) {
        str[1] = '\0';
    } 
    else {
        for (i = 0; i < len - j; i++) {
            str[i] = str[i + j];
        }
        str[i] = '\0';
    }
    return str;
}

status_code find_min_base(char *number, int *base) {
    int len = strlen(number);
    int max = 0;
    int i = 0;
    if (number[0] == '-') {
        i++;
    }
    for (; i < len; ++i) {
        if (number[i] >= '0' && number[i] <= '9') {
            max = fmax(max, number[i] - '0');
        }
        else if ((number[i] >= 'A' && number[i] <= 'Z') || (number[i] >= 'a' && number[i] <= 'z')) {
            max = fmax(max, number[i] - 'A' + 10);
        }
        else {
            return error_argument;
        }
    }
    *base = max + 1;
    if (*base < 2) {
        *base = 2;
    }
    return ok;
}

int other_base_to_ten(char* number, int base) {
    if (!number) {
        return error_argument;
    }
    int symbol = 1;
    char *ptr = number;
    int result = 0;
    if (*number == '-') {
        symbol = -1;
        ptr++;
    }
    while (*ptr) {
        if (result > INT_MAX / base || (isdigit(*ptr) ? *ptr  - '0' : *ptr - 'A' + 10) > INT_MAX - result * base) {
            return overflow;
        }
        result = result * base + (isdigit(*ptr) ? *ptr  - '0' : *ptr - 'A' + 10);
        ptr++;
    }
    return result * symbol;
}

status_code in_file(const char *file1, const char *file2) {
    if (strcmp(file1, file2) == 0) {
        return error_opening_file;
    }
    FILE *input = fopen(file1, "r");
    FILE *output = fopen(file2, "w");
    if (!input || !output) {
        fclose(input);
        fclose(output);
        return error_opening_file;
    }
    char mas[256];
    status_code st;
    int base, res;
    while (fscanf(input, "%s", mas) != EOF) {
        char *new_nums = remove_zeros(mas);
        st = find_min_base(new_nums, &base);
        if (st == error_argument) {
            fprintf(output, "invalid input\n");
        }
        else if (st == overflow) {
            fprintf(output, "overflow\n");
        }
        else {
            fprintf(output, "%s %d %d\n", new_nums, base, other_base_to_ten(new_nums, base));
        }
    }
    fclose(input);
    fclose(output);
    return ok;
}

int main(int argc, char*argv[]) {
    if (argc != 3 ) {
        printf("wrong number of arguments\n");
        return 0;
    }
    char *input = argv[1];
    char *output = argv[2];
    status_code st = in_file(input, output);
    if (st != ok) {
        print_errors(st);
    }

    else {
        printf("ok\n");
    }
    return 0;
}
