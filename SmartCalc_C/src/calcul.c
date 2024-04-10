#include "calc.h"

int check_letter(char c) {
  int err = 1;
  if (c > 96 && c < 117) {
    err = 0;
  }
  return err;
}

int chec_op(char c) {
  int err = 0;
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == ' ' || c == '^' ||
      c == '(' || c == ')' || c == '.' || c == 'a' || c == 'b' || c == 'd' ||
      c == 'e' || c == 'o' || c == 'u' || c == 'q' || c == 'l' || c == 'g' ||
      c == 'm') {
    err = 1;
  }
  return err;
}

int chec_str_end(char c) {
  int err = 0;
  if (c == '\0') {

    err = 1;
  }
  return err;
}

int pars_express(const char *calc_str, double x, double *result) {
  int err = 0;
  if (valid_experss(calc_str)) {
    err = 1;

  } else {
    char mas[STEKSIZE];
    strcpy(mas, calc_str);
    clear_space(mas);
    function_substitution(mas);
    char stek_char[STEKSIZE] = {0};
    double stek_double[STEKSIZE] = {0};

    char tmp_str[STEKSIZE];
    int tmp_count = 0;

    double num = 0;
    char c;
    int count_double = -1;
    int count_char = -1;

    for (size_t i = 0; i <= strlen(mas); i++) {
      c = mas[i];
      if(c == 'x'){
        push_double(x, &count_double, stek_double);
        continue;
      }

      if (isdigit(c) || c == 46) {
        tmp_str[tmp_count] = c;
        tmp_count++;

        if (!isdigit(mas[i + 1]) && mas[i + 1] != 46) {
          tmp_str[tmp_count] = '\0';
          num = atof(tmp_str);
          push_double(num, &count_double, stek_double);
          tmp_count = 0;
          continue;
        }

      } else if (chec_op(c)) {
        if (count_char == -1) {
          push_char(c, &count_char, stek_char);
        } else if (c == '^' && stek_char[count_char] == '^') {
          push_char(c, &count_char, stek_char);

        } else if (c == ')') {
          while (stek_char[count_char] != '(') {
            calc_end(stek_double, &count_double, stek_char, &count_char);
          }
          pop_char(stek_char, &count_char);

        } else if (op_priority(c) > op_priority(stek_char[count_char]) ||
                   stek_char[count_char] == '(') {
          push_char(c, &count_char, stek_char);

        } else {
          calc_end(stek_double, &count_double, stek_char, &count_char);
          if (op_priority(c) > op_priority(stek_char[count_char])) {
            push_char(c, &count_char, stek_char);

          } else {
            calc_end(stek_double, &count_double, stek_char, &count_char);
            push_char(c, &count_char, stek_char);
          }
        }

      } else {

        while (count_char > -1) {
          *result = calc_end(stek_double, &count_double, stek_char, &count_char);
        }
      }
    }

    
  }
  return err;
}

void annuitet_credit(double sum_cred, int time_cred,  double interest, double *monthly_payment, double *overpayment, double *total_payout) {
  
 

  
    double p = interest / 1200;

    *monthly_payment = sum_cred * (p + (p / (pow((1 + p), time_cred) - 1)));
    *total_payout = *monthly_payment  * time_cred;
    *overpayment = *total_payout - sum_cred;

   
  
}

void diffirent_credit(double sum_cred, int time_cred,  double interest, double *min_monthly_payment, double *max_monthly_payment, double *overpayment, double *total_payout){
    double dp;
    double od = sum_cred;
    double abs_interest = interest / 100;

    for(int i = 1; i < time_cred; i++){
      
      dp = sum_cred / time_cred + od * abs_interest /interest;
      od = od - dp;
      if(i == 1){
        *max_monthly_payment = dp;
      }else if(i == time_cred - 1){
        *min_monthly_payment = dp;
      }
    }
    interest = interest / 12;
    *overpayment = interest / 100 * sum_cred * (time_cred  + 1) / 2;
    *total_payout = sum_cred + *overpayment;
}

void simpl_deposit(double sum_dep, int time_dep, double interest, double add_dep, double *total_sum, double *pay_interest){
      
      double p = sum_dep;
      double tmp_interest = 0;
      *pay_interest = 0;
      for(int i = 1; i <= time_dep; i++){
        tmp_interest = p * interest / 1200;

        p += add_dep;

        *pay_interest += tmp_interest;


      }
      
      *total_sum = sum_dep + *pay_interest + add_dep * time_dep;
      

}


void cap_deposit(double sum_dep, int time_dep, double interest, double add_dep,double *total_sum, double *pay_interest){
        double interest_sum = 0;
       
        
        double p = sum_dep;
        for(int i = 1; i <= time_dep; i++){
          interest_sum = p * interest / 1200;
          *pay_interest += interest_sum;
          p += interest_sum + add_dep; 
          interest_sum = 0;

        }
        *total_sum = sum_dep + *pay_interest + add_dep * time_dep;
}




// int main() {
   
//   //double monthly_payment;
//    double overpayment;
//     double total_payout;
//     double min_monthly_payment;
//    double max_monthly_payment;
   
  
//   diffirent_credit(10000000, 12,  10, &min_monthly_payment,&max_monthly_payment, &overpayment, &total_payout);
//   printf("min monthly_payment= %f\n  max_monthly_payment = %f\n overpayment = %f\n  total_payout = %f\n",min_monthly_payment, max_monthly_payment, overpayment, total_payout);
// } 

// int main(){
//   double monthly_payment;
//   double overpayment;
//   double total_payout;

//    annuitet_credit(1000000, 12, 10, &monthly_payment, &overpayment,
//                   &total_payout);

 
//  printf("monthly_payment = %f\n overpayment = %f\n  total_payout = %f\n",monthly_payment, overpayment, total_payout);

 
// }

// int main(){
//   char *str = "-0.456 + 4 * 2 * sin(45) / 2 * (4 +8) - ln(45)";
//   double res;

//   pars_express(str, 22, &res);

//   printf("%f", res);


// }