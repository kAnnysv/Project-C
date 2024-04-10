
#include <check.h>
#include <stdlib.h>
#include "calc.h"

START_TEST(s21_smart) {
  double res = 0;
  int err = 0;
  

  char *err_str = "rty..";
  err = pars_express(err_str, 2, &res);
  ck_assert_int_eq(err, 1);
  res = 0;
  char *af_str = "-0.456 + 4 * 2 * (456 + 3.567)";
  err = pars_express(af_str, 2, &res);
  ck_assert_float_eq_tol(res,3676.08, 1e-7);
  ck_assert_int_eq(err, 0);
  res = 0;
  char *af_str2 = "-0.456 + 4 * 2 * sin(45) / 2 * (4 +8) - ln(45)";
  err = pars_express(af_str2, 2, &res); 
  ck_assert_float_eq_tol(res, 36.580707, 1e-7);
  ck_assert_int_eq(err, 0);
  
  


}
END_TEST

START_TEST(credit_calc) {
  double monthly_payment = 0;
  double overpayment_amount = 0;
  double total_payout = 0;
  double min_monthly_payment = 0;
  double max_monthly_payment = 0;


  annuitet_credit(1000000, 12, 10, &monthly_payment, &overpayment_amount,
                  &total_payout);

  ck_assert_float_eq(monthly_payment, 87915.89);
   ck_assert_double_eq_tol(overpayment_amount, 54990.6, 1);
   ck_assert_double_eq_tol(total_payout, 1054990.64, 1);

  
  overpayment_amount = 0;
  total_payout = 0;
  diffirent_credit(1000000, 12, 10, &min_monthly_payment, &max_monthly_payment, &overpayment_amount,
                  &total_payout);

   ck_assert_double_eq_tol(overpayment_amount, 54166.67, 1);
   ck_assert_double_eq_tol(total_payout, 1054166, 1);
   ck_assert_double_eq_tol(max_monthly_payment, 93333.3, 1);
   ck_assert_double_eq_tol(min_monthly_payment, 84408.99, 1);

}
END_TEST

START_TEST(s21_deposit_calc){
  double total_sum;
  double pay_interest;

  simpl_deposit(1000, 12, 12, 1000, &total_sum, &pay_interest);
  ck_assert_double_eq_tol(total_sum, 13780, 1);
  ck_assert_double_eq_tol(pay_interest, 780, 1);

  total_sum = 0;
  pay_interest = 0;
   


  cap_deposit(1000, 12, 12, 1000, &total_sum, &pay_interest);
  ck_assert_double_eq_tol(total_sum, 13809.33, 1);
  ck_assert_double_eq_tol(pay_interest, 809.33, 1);




}
END_TEST

Suite *smartcalc(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("\033s21_smartcalc\033");
  tc = tcase_create("case_all_test");

  tcase_add_test(tc, s21_smart);
  tcase_add_test(tc, credit_calc);
  tcase_add_test(tc, s21_deposit_calc);

  suite_add_tcase(s, tc);
  return s;
}






void case_test(Suite *s, int *fail) {
  SRunner *runner = srunner_create(s);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  *fail = srunner_ntests_failed(runner);
  srunner_free(runner);
}

int main() {
  int fail = 0;
  SRunner *sr;

  sr = srunner_create(smartcalc());

  srunner_run_all(sr, CK_NORMAL);
  fail = srunner_ntests_failed(sr);
  srunner_free(sr);

  return fail;
}
