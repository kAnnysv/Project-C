#ifndef CALC_H
#define CALC_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STEKSIZE 300
// #define COS a
// #define SIN b
// #define TAN d
// #define ACOS e
// #define ASIN o
// #define ATAN u
// #define SQRT q
// #define LN l
// #define LOG g
// #define MOD m

int check_letter(char c);
int valid_func(char c);
int valid_experss(const char *mas);
int pars_express(const char *calc_str, double x, double *result);


void push_double(double n, int *i, double *mas);
double pop_double(double *mas, int *i);
void push_char(char n, int *i, char *mas);
char pop_char(char *mas, int *i);

int op_priority(char c);

void calc (double *stek_double, int *count_double, char c);
double calc_end (double *stek_double, int *count_double, char *stek_char, int *count_char);

void clear_space (char *mas);
void function_substitution(char *mas);

void annuitet_credit(double sum_cred, int time_cred,  double interest, double *monthly_payment, double *overpayment, double *total_payout);
void diffirent_credit(double sum_cred, int time_cred,  double interest, double *min_monthly_payment, double *max_monthly_payment, double *overpayment, double *total_payout);

void simpl_deposit(double sum_dep, int time_dep, double interest, double add_dep, double *total_sum, double *pay_interest);
void cap_deposit(double sum_dep, int time_dep, double interest, double add_dep,double *total_sum, double *pay_interest);



#endif
