#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

enum error {
    ok = -1,
    wrong_arguments,
    wrong_epsilon
};

int check_prime(int num) {
    if (num <= 0) {
        return -1;
    }
    if (num == 2) {
        return 1;
    }
    if ((!num & 1)) {
        return 0;
    }
    for (int i = 3; i <= (int) sqrt(num); i += 2) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

bool check_float(char* str) {
    int n = strlen(str);
    if (!isdigit(str[0]) && str[0] != '-') {
        return false;
    }
    int count_dot = 0;
    for (int i = 1; i < n; i++) {
        if (!isdigit(str[i])) {
            if (str[i] == '.') {
                count_dot++;
            }
            else {
                return false;
            }
            if (count_dot > 1) {
                return false;
            }
        }
    }
    return true;
}

double e_limits(double epsilon) {
    int n = 1;
    double result = 2;
    double current = result;
    do {
        n++;
        result = current;
        current = pow((1 + 1.0/n), n);
    } while (fabs(current - result) > epsilon);
    return current;
}

double e_row(double epsilon) {
    int n = 1;
    double f = 1;
    double result1 = 2;
    double result2 = result1;
    do {
        n++;
        result1 = result2;
        f *= n;
        result2 += 1/f;
    } while (fabs(result1 - result2) > epsilon);
    return result2;
}

double e_equation(double epsilon) {
    double x = 2;
    double x1 = x;
    do {
        x = x1;
        x1 = x - (log(x) - 1) * x;
    } while (fabs(x1 - x) > epsilon);
    return x1;
}

double pi_limits(double epsilon) {
    int n = 1;
    double result1 = 4;
    double result2 = result1;
    do {
        result1  = result2;
        result2 = result2 * 4 * (n + 1) * n / ((2 * n + 1) * (2 * n + 1));
        n++;
    } while (fabs(result1 - result2) > epsilon);
    return result2;
}

double pi_row(double epsilon) {
    double n = 1.0;
    double summ = 0.0;
    double current;
    while (fabs(current) >= epsilon) {
        current = pow(-1, n - 1) / (2 * n -1);
        summ += current;
        n++;
    }
    return 4 * summ;
}

double pi_equation(double epsilon) {
    double x = 3;
    double x1 = x;
    do {
        x = x1;
        x1 = x + (cos(x) + 1) / (sin(x));
    } while (fabs(x - x1) > epsilon);
    return x1;
}

double ln_limits(double epsilon) {
    int n = 1;
    double result1 = 1;
    double result2 = result1;
    do {
        n++;
        result1 = result2;
        result2 = n * (pow(2, 1.0/(double)n) - 1);
    } while (fabs(result2 - result1) > epsilon);
    return result2;
}

double ln_row(double epsilon) {
    double n = 1;
    double summ = 0.0;
    double current = 1.0;
    while (fabs(current) >= epsilon) {
        current = pow(-1, n -1) / n;
        summ += current;
        n++;
    }
    return summ;
}

double ln_equation(double epsilon) {
    double x = 1.0;
    double e = e_equation(epsilon);
    double x1 = x - ((pow(e, x) - 2.0) / (pow(e, x)));
    do {
        x = x1;
        x1 = x - ((pow(e, x) - 2.0) / (pow(e, x)));
    } while (fabs(x - x1) > epsilon);
    return x1;
}

double root_limits(double epsilon) {
    double x = -0.5;
    double x1 = x - x * x / 2 + 1;
    do {
        x = x1;
        x1 = x - x * x / 2 + 1;
    } while (fabs(x1 - x) > epsilon);
    return x1;
}

double root_row(double epsilon) {
    double tmp = 1;
    double result1 = 0;
    double result2 = pow(2, 0.25);
    do {
        result1 = tmp;
        tmp *= result2;
    } while (fabsl(tmp - result1) > epsilon);
    return tmp;
}

double root_equation(double epsilon) {
    double x = 2;
    double x1 = x - (x * x - 2) / (2 * x);
    do {
        x = x1;
        x1 = x - (x * x - 2) / (2 * x);
    } while (fabs(x1 - x) > epsilon);
    return x1;
}

double gamma_limits(double epsilon) {
    double result1 = 0;
    double result2 = 0;
    int m = 1;
    do {
        m++;
        result1 = result2;
        result2 = 0;
        double lg = 0;
        double comb = m;
        double pl = 0;
        for (int k = 2; k <= m; k++) {
            comb *= (m - k + 1.0) / k;
            lg += log(k);
            pl = comb * lg / k;
            if (k & 1) pl *= -1;
            result2 == pl;
        }
    } while (fabs(result1 - result2) > epsilon);
    return result2;
}

double gamma_row(double epsilon) {
    int k = 2;
    double pi = pi_equation(epsilon);
    double result1 = (1.0 / pow(floor(sqrt(k)), 2)) - 1.0 / k;
    double result2 = result1;
    long long tmp;
    do {
        k++;
        result1 = result2;
        result2 = (1.0 / pow(floor(sqrt(k)), 2)) - 1.0 / k;
        tmp = (int)sqrt(k);
    } while (fabs(result1 - result2) > epsilon || (tmp * tmp == k));
    return result2 - pi * pi / 6;
}

double gamma_equation(double epsilon) {
    double pr= 0.5;
    int t = 2;
    double result1 = 0.0;
    double result2 = -log(0.5 * log(2));
    do {
        t++;
        result1 = result2;
        if (check_prime(t)) pr *= (t - 1.0)/t;
        result2 = -log(pr * log(t));
    } while (fabs(result2 - result1) >= epsilon);
    return result2;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("error\n");
        return 1;
    }
    if (!check_float(argv[1])) {
        printf("error\n");
        return 1;
    }
    double epsilon = atof(argv[1]);
    if (epsilon <= 0.0) {
        printf("error\n");
        return 1;
    }
    printf("e = %.10lf (limit)\n", e_limits(epsilon));
	printf("e = %.10lf (series)\n", e_row(epsilon));
	printf("e = %.10lf (equation)\n\n", e_equation(epsilon));
	printf("pi = %.10lf (limit)\n", pi_limits(epsilon));
	printf("pi = %.10lf (series)\n", pi_row(epsilon));
	printf("pi = %.10lf (equation)\n\n", pi_equation(epsilon));
	printf("ln2 = %.10lf (limit)\n", ln_limits(epsilon));
	printf("ln2 = %.10lf (series)\n", ln_row(epsilon));
	printf("ln2 = %.10lf (equation)\n\n", ln_equation(epsilon));
	printf("sqrt2 = %.10lf (limit)\n", root_limits(epsilon));
	printf("sqrt2 = %.10lf (series)\n", root_row(epsilon));
	printf("sqrt2 = %.10lf (equation)\n\n", root_equation(epsilon));
	printf("gamma = %.10lf (limit)\n", gamma_limits(epsilon));
	printf("gamma = %.10lf (series)\n", gamma_row(epsilon));
	printf("gamma = %.10lf (equation)\n", gamma_equation(epsilon));
    return 0;
}






