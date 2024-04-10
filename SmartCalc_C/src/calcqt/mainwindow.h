#ifndef MAINWINDOW_H
#define MAINWINDOW_H

extern "C" {
#include "../calc.h"
}

#include <QMainWindow>
#include <QVector>

#include "crediwindow.h"
#include "depositwindow.h"


#ifdef __cplusplus

extern "C" {
#endif

#include "../calc.h"

#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void digits_numbers();

    void on_pushButton_AC_clicked();
    void get_result();





    void on_pushButton_graf_clicked();

    void on_pushButton_credit_clicked();

    

    void on_pushButton_deposit_clicked();

private:
  Ui::MainWindow *ui;
  double x;


};
#endif // MAINWINDOW_H
