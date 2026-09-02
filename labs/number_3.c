#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool integer(const char *str) {
    if (strlen(str) > 10) {
        return false;
    }
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

bool string(char *str) {
    if (strlen(str) > 6) {
        return 6;
    }
    int count = 0;
    if (*str == '\0') {
        return false;
    }
    if (*str == '+' || *str == '-') {
        str++;
        if (*str == '\0') {
            return false;
        }
    }
    while (*str) {
        if (*str >= '0' && *str <= '9') {
            str++;
            if (*str == '.') {
                count += 1;
                str++;
                if (*str == '\0') {
                    return false;
                }
            }
        }
        else {
            return false;
        }
    }
    if (count == 0 || count > 1) {
        return false;
    }
    return true;
}

int multiple(int a, int b) {
    if (b == 0) {
        return false;
    }
    if (a % b == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

double max(double a, double b, double c) {
    double max = a;
    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    return max;
}

double min(double a, double b, double c) {
    double min = a;
    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }
    return min;
}

bool triangle(double num1, double num2, double num3, double epsilon) {
    double max_el = max(num1, num2, num3);
    double min_el = min(num1, num2, num3);
    double middle_el = (num1 + num2 + num3) - max_el - min_el;
    if (fabs(min_el * min_el + middle_el * middle_el - max_el * max_el) < epsilon) {
        return true;
    }
    else {
        return false;
    }
}

void permutation(double new_array[][3], double array[], int n, int *count) {
    if (n == 1) {
        for (int i = 0; i < 3; i++) {
            new_array[*count][i] = array[i];
        }
        (*count)++;
        return;
    }
    for(int i = 0; i < n; i++) {
        permutation(new_array, array, n - 1, count);
        if (n % 2 == 0) {
            double temp = array[i];
            array[i] = array[n - 1];
            array[n - 1] = temp;
        }
        else {
            double temp = array[i];
            array[i] = array[n - 1];
            array[n - 1] = temp;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("error\n");
        return 0;
    }
    if (strlen(argv[1]) != 2 || argv[1][0] != '-' && argv[1][0] != '/') {
        printf("invalid flag\n");
        return 0;
    }
    else {
        if (argv[1][1] == 'q') {
            if (argc != 6) {
                printf("error\n");
            }
            else {
                if ((string(argv[2])) && (string(argv[3])) && (string(argv[4])) && (string(argv[5]))) {
                    int count = 0;
                    double new_array[100][3] = {0.0};
                    double array[3];
                    double epsilon = atof(argv[2]);
                    double num1 = atof(argv[3]);
                    double num2 = atof(argv[4]);
                    double num3 = atof(argv[5]);
                    array[0] = num1;
                    array[1] = num2;
                    array[2] = num3;
                    permutation(new_array, array, 3, &count);
                    for (int i = 0; i < count; i++) {
                        double discr = pow(new_array[2][1], 2) - 4 * new_array[i][0] * new_array[i][2];
                        if (discr > epsilon) {
                            double x1 = (-new_array[i][1] + sqrt(discr)) / (2 * new_array[i][0]);
                            double x2 = (-new_array[i][1]) - sqrt(discr) / (2 * new_array[i][0]);
                            printf("permutation %lf %lf %lf:\n", new_array[i][0], new_array[i][1], new_array[i][2]);
                            printf("the solution is a complex number\n");
                            printf("\n");
                        }
                    }
                }
                else {
                    printf("error\n");
                }
            }
        }
        else if (argv[1][1] == 'm') {
            if (argc != 4) {
                printf("error\n");
                return 0;
            }
            else {
                if (integer(argv[2]) && integer(argv[3])) {
                    if (multiple(atoi(argv[2]), atoi(argv[3]))) {
                        printf("yes\n");
                    }
                    else {
                        printf("no\n");
                    }
                }
                else {
                    printf("error\n");
                }
            }
        }
        else if (argv[1][1] == 't') {
            if (argc != 6) {
                printf("error\n");
                return 0;
            }
            else {
                if ((string(argv[2])) && (string(argv[3])) && string(argv[4]) && string(argv[5])) {
                    if (triangle(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]))) {
                        printf("it is triangle\n");
                    }
                    else {
                        printf("it is not triangle\n");
                    }
                }
                else {
                    printf("error\n");
                }
            }
        }
        else {
            printf("invalid flag\n");
        }
    }
}
