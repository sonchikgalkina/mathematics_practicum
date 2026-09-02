#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

enum error {
    error_memory,
    overflow,
    invalid_value,
    ok
};

void print_errors(int flag) {
    switch (flag) {
    case error_memory:
        printf("error with allocation memory\n");
        break;
    case overflow:
        printf("iverflow\n");
        break;
    case invalid_value:
        printf("Invalid value\n");
        break;
    }
}

double factorial(int n) {
    double fact = 1;
    for(int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

enum error decomposition_of_polynomial(double eps, double a, double** result, int degree, ...) {
    va_list arg;
    va_start(arg, degree); 
    double* array_for_coefficient = (double*)malloc((degree + 1) * sizeof(double));
    if (!array_for_coefficient) {
        free(array_for_coefficient);
        return error_memory;
    }
    *result = (double*)malloc((degree + 1) * sizeof(double));
    if (!*result) {
        free(result);
        return error_memory;
    }
    for (int i = 0; i <= degree; i++) {
        (*result)[i] = 0.0;
    }
    int power = 1;
    for (int i = 0; i <= degree; i++) {
        double c = va_arg(arg, double);
        array_for_coefficient[i] = power * c;
        power *= a;
    }
    va_end(arg);
    (*result)[0] = array_for_coefficient[0]; 
    for (int i = 1; i <= degree; i++) {
        double prev_result = (*result)[i];
        (*result)[i] = (array_for_coefficient[i] / factorial(i)) - a * (*result)[i - 1];
        if (fabs((*result)[i] - prev_result) < eps) {
            free(array_for_coefficient);
            return invalid_value;
        }
    }
    free(array_for_coefficient);
    return ok;
}

int main() {
    double* result;
    int degree = 3;
    int coef = decomposition_of_polynomial(0.00001, 2.0, &result, degree, 2.0, -5.0, 3.0, 1.0);
    if (coef != ok) {
        print_errors(coef);
    }
    else {
        for(int i = 0; i <= 3; i++) {
            printf("g%d: %f \n", i, result[i]);
        }
        printf("\n");
    }
    free(result);
    return 0;
}
