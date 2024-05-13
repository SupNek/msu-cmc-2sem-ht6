#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int iterations = 0;
double f1(double x); //f1 = 0.6x + 3
double f2(double x); //f2 = (x - 2)^3 - 1
double f3(double x); //f3 = 3/x

static double g1(double x) { // g1 = x + 1
    return x + 1;
}
static double g2(double x) { // g2 = x^3 - 3
    return x * x * x - 3;
}
static double g3(double x) { // g3 = 1/x
    return 1 / x;
}

static double root(double (*f)(double), double (*g)(double), double a, double b, double eps1) { //(1) section division method
    double c = (b + a) / 2; //middle of the section
    while (b - a > eps1) {
        if ((f(a) - g(a)) * (f(c) - g(c)) < 0) b = c;
        else if ((f(b) - g(b)) * (f(c) - g(c)) < 0) a = c;
        else {
            printf("Error wrong section\n");
            exit(-1);
        }
        c = (b + a) / 2;
        iterations++;
    }
    return a;
}
static double integral(double (*f)(double), double a, double b, double eps2) { //(3) Simpson's mathod
    int n = 4; double I_2n = 0, I_n = 0, sum = f(a) + f(b);
    double h = (b - a) / n;
    sum += f(a + h * 2) * 2; //saving previous function values
    do {
        n *= 2;
        I_n = I_2n;
        h = (b - a) / n;
        I_2n = sum;
        for (int i = 1; i < n; i += 2) {
            double y = f(a + i * h);
            sum += y * 2;
            I_2n += y * 4;
        }
        I_2n = I_2n * h / 3;
    } while (fabs(I_n - I_2n) / 15 > eps2);
    return I_2n;
}
int main(int argc, char* argv[]) {
    double ins1 = 0, ins2 = 0, ins3 = 0, sum = 0;
    double (*funcs[3])(double) = { g1, g2, g3 };
    if (argc >= 2) {
        if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) { //help
            char line[] = "--help or -h  : prints every possible keys\n"
                "--root or -r  : prints abscissa of functions intersection\n"
                "--iterations or -i  : prints number of iterations made by root function\n"
                "--test-root or -R  : starts testing for root function\n"
                "--test-integral or -I  : starts testing for integral function\n";
            puts(line);
        }
        else if (!strcmp(argv[1], "-r") || !strcmp(argv[1], "--root")) { //root
            printf("f1 and f2 intersection with x ~ %.6f\n", root(f1, f2, -10, 10, 0.0001));
            printf("f2 and f3 intersection with x ~ %.6f\n", root(f2, f3, -10, 10, 0.0001));
            printf("f1 and f3 intersection with x ~ %.6f\n", root(f1, f3, -10, 10, 0.0001));
        }
        else if (!strcmp(argv[1], "-i") || !strcmp(argv[1], "--iterations")) { //iterations
            root(f1, f2, -10, 10, 0.0001);
            root(f2, f3, -10, 10, 0.0001);
            root(f1, f3, -10, 10, 0.0001);
            printf("The number of iterations: %d\n", iterations);
        }
        else if (!strcmp(argv[1], "-R") || !strcmp(argv[1], "--test-root")) { //testing for root
            double a, b, eps1, result; int func_ind1, func_ind2;
            sscanf(argv[2], "%d:%d:%lf:%lf:%lf:%lf", &func_ind1, &func_ind2, &a, &b, &eps1, &result);
            double intersection = root(funcs[func_ind1 - 1], funcs[func_ind2 - 1], a, b, eps1);
            printf("_________________________\n");
            printf("Result: %.6f\n", intersection);
            printf("Absolute error: %.6f\n", fabs(intersection - result));
            printf("Relative error: %.6f\n", fabs(intersection - result) / result);
            printf("\n___________________________________________\n");
        }
        else if (!strcmp(argv[1], "-I") || !strcmp(argv[1], "--test-integral")) { //testing for integral
            double a, b, eps2, result; int func_ind1;
            sscanf(argv[2], "%d:%lf:%lf:%lf:%lf", &func_ind1, &a, &b, &eps2, &result);
            double integ = integral(funcs[func_ind1 - 1], a, b, eps2);
            printf("\n_________________________\n");
            printf("Result: %.6f\n", integ);
            printf("Absolute error: %.6f\n", fabs(integ - result));
            printf("Relative error: %.6f\n", fabs(integ - result) / result);
            printf("\n___________________________________________\n");
        }
        else {
            printf("Error! Wrong command key!\n");
            exit(-1);
        }
    }
    else {
        ins1 = root(f1, f2, -10, 10, 0.0001); //correct answer: x ~ 3.8478
        ins2 = root(f2, f3, -10, 10, 0.0001); //correct answer: x ~ 3.2439
        ins3 = root(f1, f3, -10, 10, 0.0001); //correct answer: x ~ 0.8541
        sum += integral(f1, ins3, ins2, 0.0001);
        sum -= integral(f3, ins3, ins2, 0.0001);
        sum += integral(f1, ins2, ins1, 0.0001);
        sum -= integral(f2, ins2, ins1, 0.0001);
        printf("Area: %.6f\n", sum);
    }
    return 0;
}
