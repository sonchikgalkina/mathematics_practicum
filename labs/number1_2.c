#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

enum status_code {
    invalid_args,
    wrong_of_args,
    overflow,
    error_memory,
    ok
};

void print_error(int status) {
    switch (status)
    {
    case invalid_args:
        printf("invalid args\n");
        break;
    case wrong_of_args:
        printf("wrong amount of arguments\n");
        break;
    case overflow:
        printf("overflow\n");
        break;
    case error_memory:
        printf("error\n");
        break;
    default:
        break;
    }
}

int function_l(char* str) {
    int ans = 0;
    while (str[ans] != '\0') {
        ans++;
        if (errno == ERANGE) {
            return INT_MAX;
        }
    }
    return ans;
}

int function_r(char* str, char** ans) {
    int n = function_l(str);
    if (errno == overflow) {
        return overflow;
    }
    *ans = (char*)malloc(sizeof(char) * (n + 1));
    if (*ans == NULL) {
        return error_memory;
    }
    (*ans)[n] = '\0';
    n--;
    int ind = 0;
    while (n >= 0) {
        (*ans)[ind] = str[n];
        ind++;
        n--;
    }
    return ok;
}

int function_u(char* str, char** ans) {
    *ans = (char*)malloc(sizeof(str));
    if (*ans == NULL) {
        return error_memory;
    }
    int ind = 0;
    while (str[ind] != '\0') {
        if ((ind & 1)) {
            (*ans)[ind] = toupper(str[ind]);
        }
        else {
            (*ans)[ind] = str[ind];
        }
        ind++;
    }
    (*ans)[ind] = '\0';
    if (errno == ERANGE) {
        return overflow;
    }
    return ok;
}

int function_n(char* str, char** ans) {
    *ans = (char*)malloc(sizeof(str));
    if (*ans == NULL) {
        return error_memory;
    }
    int ind = 0;
    int ans_ind = 0;
    while (str[ind] != '\0') {
        if (isdigit(str[ind])) {
            (*ans)[ans_ind] = str[ind];
            ans_ind++;
        }
        ind++;
    }
    ind = 0;
    while (str[ind] != '\0') {
        if (isalpha(str[ind])) {
            (*ans)[ans_ind] = str[ind];
            ans_ind++;
        }
        ind++;
    }
    ind = 0;
    while (str[ind] != '\0') {
        if (!isalpha(str[ind]) && !isdigit(str[ind])) {
            (*ans)[ans_ind] = str[ind];
            ans_ind++;
        }
        ind++;
    }
    (*ans)[ind] = '\0';
    if (errno == ERANGE) {
        return overflow;
    }
    return ok;
}

int get_strings(int argc, char** argv, char*** ans) {
    *ans = (char**)malloc(sizeof(char*) * (argc - 3));
    if (*ans == NULL) {
        return error_memory;
    }
    (*ans)[0] = argv[2];
    for (int i = 4; i < argc; i++) {
        (*ans)[i-3] = argv[i];
    }
    return ok;
}

int function_c(int seed, int amount, char** strings, char** ans) {
    int size = 0;
    for (int i = 0; i < amount; i++) {
        size += function_l(strings[i]);
        if (errno == ERANGE) {
            return overflow;
        }
    }
    *ans = (char*)malloc(sizeof(char) * (size + 1));
    if (*ans == NULL) {
        return error_memory;
    }
    srand(seed);
    int* arr = (int*)calloc(amount, sizeof(int));
    int mega_ind = 0;
    for (int i = 0; i < amount; i++) {
        int ind = rand() % amount;
        while (arr[ind]) {
            ind++;
            ind %= amount;
        }
        arr[ind] = 1;
        for (int j = 0; strings[ind][j]; j++) {
            (*ans)[mega_ind] = strings[ind][j];
            mega_ind++;
        }
    }
    (*ans)[mega_ind] = '\0';
    free(arr);
    return ok;
}

int valid_args(int argc, char** argv) {
    if (argc < 3) {
        return wrong_of_args;
    }
    char flags[] = {'l', 'r', 'u', 'n', 'c'};
    int n = function_l(argv[1]);
    if (errno == ERANGE) {
        return overflow;
    }
    if (n != 2) {
        return invalid_args;
    }
    if (argv[1][0] != '-') {
        return invalid_args;
    }
    bool flag = false;
    for (int i = 0; i < 5; i++) {
        if (argv[1][1] == flags[i]) {
            flag = true;
        }
    }
    if (!flag) {
        return invalid_args;
    }
    if (argv[1][1] == 'c') {
        if (argc < 4) {
            return wrong_of_args; 
        }
        int ind = 0;
        while (argv[3][ind] != '\0') {
            if (!isdigit(argv[3][ind])) {
                return invalid_args;
            }
            ind++;
        }
        int n = atoi(argv[3]);
        if (errno == ERANGE) {
            return overflow;
        }
    }
    return ok;
}

int main(int argc, char** argv) {
    int status = valid_args(argc, argv);
    if (status != ok) {
        print_error(status);
        return 1;
    }
    switch (argv[1][1])
    {
    case 'l':
        int ans = function_l(argv[2]);
        if (status != ok) {
            print_error(status);
            return 1;
        }
        printf("the length of the string is %d.\n", ans);
        break;
    case 'r':
        char* rstr;
        status = function_r(argv[2], &rstr);
        if (status != ok) {
            free(rstr);
            print_error(status);
            return 1;
        }
        printf("reversed string: %s\n", rstr);
        free(rstr);
        break;
    case 'u':
        char* odd_upper_str;
        atus = function_u(argv[2], &odd_upper_str);
        if (status != ok) {
            free(odd_upper_str);
            print_error(status);
            return 1;
        }
        printf("string, after upping case of every odd index: %s.\n", odd_upper_str);
        free(odd_upper_str);
        break;
    case 'n':
        char* str;
        status = function_n(argv[2], &str);
        if (status != ok) {
            print_error(status);
            return 1;
        }
        printf("sorted string: %s.\n", str);
        free(str);
        break;
    case 'c':
    {
        char** ans;
        int status = get_strings(argc, argv, &ans);
        if (status != ok) {
            print_error(status);
            return 1;
        }
        char* ans1;
        int seed = atoi(argv[3]);
        status = function_c(seed, argc - 3, ans, &ans1);
        if (status != ok) {
            print_error(status);
            return 1;
        }
        printf("%s\n", ans1);
        free(ans);
        free(ans1);
        break;
    }
    default:
        break;
    }
    return 0;
}
