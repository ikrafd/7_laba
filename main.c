#include <stdio.h>
#include <math.h>

void check_char (double *var);
void check_char_int (int *var);
double fun1(double, double);
double fun2(double, double);
double root1(double (*fun) (double, double), double, double, double, double);
double root2(double (*fun) (double, double), double, double, double);

int main() {
    int equat, metod,  epsi=0;
    double y, a, b, x, counter, e;
    char er;
    printf("Enter 1 if cos(y/x)-2*sin(1/x)+1/x\n"
           "Enter 2 if sin(log(x))-cos(log(x))+y*log(x)\n");
    check_char_int (&equat);

    printf("\"Enter 1 to use half division method or 2 to use Newton's method:\n");
    check_char_int (&metod);

    printf("Enter y\n");
    check_char (&y);
    do {
        er=0;
        printf("Enter a1\n");
        check_char(&a);
        printf("Enter a2\n");
        check_char(&b);
        if(a>b){
            printf("Low border is higher then top\n");
            fflush(stdin);
            er = 1;
        }
    }while (er);

    printf("Enter epsilon\n");
    check_char (&e);

    if(metod==1){
        if(equat==1){
           x=root1(fun1, a, b, y, e);
        }else{
           x=root1(fun2, a, b, y, e);
        }
    }else{
        if(equat==1){
            x=root2(fun1, a, y, e);
        }else{
            x=root2(fun2, a, y, e);
        }
    }

    counter=e;
    while (counter < 1) {
        counter*= 10;
        epsi++;
    }
    printf("Result:%.*lf", epsi, x);
    return 0;
}

void check_char_int (int *var){
    char er, ch;
    do {
        er = 0;
        scanf("%i%c", var, &ch);
        if(ch != '\n') {
            printf("Invalid data\n");
            er = 1;
            fflush(stdin);
        }else if ((*var<1)||(*var>2)){
            er = 1;
            printf("Enter 1 or 2\n");
            fflush(stdin);
        }
    } while(er);
}
void check_char (double *var){
    char er, ch;
    do {
        er = 0;
        scanf("%lf%c", var, &ch);
        if(ch != '\n') {
            printf("Invalid data\n");
            er = 1;
            fflush(stdin);
        }
    } while(er);
}

double fun1(double x, double y){
    return (cos(y/x)-2*sin(1/x)+1/x);
}

double fun2(double x, double y){
    return (sin(log(x))-cos(log(x))+y*log(x));
}

double root1(double (*fun) (double, double), double a, double b, double y, double e) {
    double x;
    do{
        x=(a+b)/2;
        if (((*fun) (a, y) * (*fun)(x, y))>0) {
            a=x;
        }else{
            b=x;
        }
    }while(fabs(b-a)>e);

    if (fabs((*fun)(x,y))>1){
        printf("There are no roots in this range");
        return 0;
    }
    return x;
}

double root2(double (*fun) (double, double), double a, double t, double e) {
    double delta, k, der, r=a;

    do {
        k = (*fun)(r, t);
        der = ((*fun)(r + pow(10, -6), t) - k) / pow(10, -6);
        if( isnan(k) || isnan(der)) {
            printf("Value doesn't belong to the domain of function");
            return 0;
        }
        delta = k / der;
        r -= delta;
    } while (fabs(delta) > e);

    if(fabs((*fun)(r,t))>1){
        printf("There are no roots in this range");
        return 0;
    }
    return r;
}

