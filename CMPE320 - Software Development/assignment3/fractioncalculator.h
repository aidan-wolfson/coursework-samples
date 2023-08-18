#ifndef FRACTIONCALCULATOR_H
#define FRACTIONCALCULATOR_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class FractionCalculator; }
QT_END_NAMESPACE

class FractionCalculator : public QMainWindow
{
    Q_OBJECT

public:
    FractionCalculator(QWidget *parent = nullptr);
    ~FractionCalculator();

private:
    Ui::FractionCalculator *ui;

private slots:
    void on_equals_clicked();
    void on_num1_textChanged();
    void on_denom1_textChanged();
    void on_num2_textChanged();
    void on_denom2_textChanged();
    void on_closeButton_clicked();
};
#endif // FRACTIONCALCULATOR_H
