#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

int divider(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

double epsilon() {
    double eps = 1.0;
    while (1.0 + eps > 1.0) {
        eps /= 2;
    }
    return eps;
}

int finite_representation(double num, int base) {
    if (base < 2) {
        return false;
    }
    double eps = epsilon();
    int numerator, denominator = 1;
    while (num - floor(num) > eps) {
        num *= 10;
        denominator *= 10;
    }
    numerator = (int)num;
    int div = divider(numerator, denominator);
    numerator /= div;
    denominator /= div;
    for (int i = 2; i <= denominator; i++) {
        if (denominator % i == 0) {
            if (base % i != 0) {
                return false;
            }
        }
        while (denominator % i == 0) {
            denominator /= i;
        }
    }
    return true; 
}

char* finite_more(int base, int amount, ...) {
    va_list args;
    va_start(args, amount);
    char* ans = (char*)malloc(sizeof(char) * (amount + 1));
    ans[amount] = '\0';
    for (int i = 0; i < amount; i++) {
        double num = va_arg(args, double);
        ans[i] = finite_representation(num, base) + '0';
    }
    va_end(args);
    return ans;
}

int main() {
    char* ans = finite_more(5, 3, 0.1, 0.2, 0.3);
    printf("finite: %s\n", ans);
    free(ans);
    return 0;
}
