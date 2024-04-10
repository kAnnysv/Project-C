#ifndef CREDIWINDOW_H
#define CREDIWINDOW_H

#include <QMainWindow>


#ifdef __cplusplus

extern "C" {
#endif

#include "../calc.h"

#ifdef __cplusplus
}
#endif

namespace Ui {
class crediWindow;
}

class crediWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit crediWindow(QWidget *parent = nullptr);
    ~crediWindow();
private slots:
    void credit_calc();


    void on_pushButton_clicked();

private:
    Ui::crediWindow *ui;
    double monthly_payment;
    double overpayment;
    double total_payout;
    double min_monthly_payment;
    double max_monthly_payment;
};

#endif // CREDIWINDOW_H
