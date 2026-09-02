#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

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
        if (isdigit(*str)) {
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

double function_a(double x) {
    return log(1 + x) / x;
}

double function_b(double x) {
    return exp(-(pow(x, 2) / 2));
}

double function_c(double x) {
    if (x == 1 || x <= 0) {
        return -1;
    }
    return log(1 / (1 - x));
}

double function_d(double x) {
    return pow(x, x);
}

double rectangle(double a, double b, double n, double (*f)(double), double epsilon) {
    double summ = 0.0;
    double new_summ = 0.1 + epsilon;
    double h = (b - a) / n;

    while (fabs(new_summ - summ) > epsilon) {
        summ = new_summ;
        new_summ = 0.0;
        for (int i = 1; i <= n; i++) {
            double x = a + i * h;
            new_summ += f(x);
        }
    }
    double res = h * new_summ;
    return res;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("error\n");
        return 1;
    }
    // if (string(argv[1])) {
    //     printf("invalid epsilon\n");
    //     return 1;
    // }
    double epsilon = atof(argv[1]);
    if (epsilon <= 0.0) {
        printf("invalid epsilon\n");
        return 1;
    }

    double result1 = rectangle(0, 1, 100, function_a, epsilon);
    printf("first integral: %lf\n", result1);
    double result2 = rectangle(0, 1, 100, function_b, epsilon);
    printf("second integral: %lf\n", result2);
    double result3 = rectangle(0, 1, 100, function_c, epsilon);
    printf("third integral: %lf\n", result3);
    double result4 = rectangle(0, 1, 100, function_d, epsilon);
    printf("fourth integral: %lf\n", result4);
}
