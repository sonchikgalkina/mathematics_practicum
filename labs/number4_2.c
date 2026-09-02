#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


enum error {
    ok,
    invalid_value,
    error_memory
};

typedef struct {
    double x, y;

} point;

void print_errors(int flag) {
    switch (flag)
    {
    case invalid_value:
        printf("invalid value\n");
        break;

    case error_memory:
        printf("error with memory allocation\n");
        break;

    default:
        break;
    }
}

enum error value_of_polynomial(double* result, double a, int degree, ...) {
    va_list args;
    va_start(args, degree);
    if (degree >= 0) {
        for (int i = 0; i <= degree; i++) {
            *result = *result * a + va_arg(args, double);
        }
    }
    else {
        if (a == 0) {
            return invalid_value;
        }
        for (int i = 0; i >= degree; i--) {
            *result = *result / a + va_arg(args, double);
        }
    }
    va_end(args);
    return ok;
}

enum error is_convex(int n, ...) {
    if (n < 3) {
        return invalid_value;
    }
    va_list args;
    va_start(args, n);
    point* points = va_arg(args, point*);
    va_end(args);
    int NEG = 0;
    for (int a = 0; a < n; a++) {
        int b = (a + 1) % n;
        int c = (a + 2) % n;
        double xA = points[a].x;
        double yA = points[a].y;
        double xB = points[b].x;
        double yB = points[b].y;
        double xC = points[c].x;
        double yC = points[c].y;
        double POS = (xB - xA) * (yC - yB) - (yB - yA) * (xC - xB);
        if (POS > 0) {
            POS++;
        }
        else if (POS < 0) {
            NEG++;
        }
        if (POS > 0 && NEG > 0) {
            return invalid_value;
        }
    }
    return ok;
}

int main() {
    double result = 0;
    double a = 1.0;
    int degree = 3;
    enum error result_pol = value_of_polynomial(&result, a, degree, 4.0, 5.0, 1.0, 6.0);
    if (result_pol != ok) {
        print_errors(result_pol);
    }
    if (result_pol == ok) {
        printf("the result of polynom is %f\n", result);
    }
    int n = 3;
    point point[3] = {{1, 2}, {4, 2}, {7, 2}};
    enum error polygon_res = is_convex(n, point[0], point[1], point[2]);
    if (polygon_res == invalid_value) {
        printf("this polygon is not convex\n");
    }
    else if (polygon_res == ok) {
        printf("this polygon is convex\n");
    }
    return 0;
}
