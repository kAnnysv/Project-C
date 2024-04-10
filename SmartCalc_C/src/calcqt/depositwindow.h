#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QMainWindow>

#ifdef __cplusplus

extern "C" {
#endif

#include "../calc.h"

#ifdef __cplusplus
}
#endif

namespace Ui {
class depositWindow;
}

class depositWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit depositWindow(QWidget *parent = nullptr);
    ~depositWindow();

private slots:
    void deposit_calc();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::depositWindow *ui;
    double add_dep = 0;
    double total_sum = 0;
    double pay_interest = 0;

};

#endif // DEPOSITWINDOW_H
