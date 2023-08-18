#include "fractioncalculator.h"
#include "ui_fractioncalculator.h"
#include "FractionLibrary/fraction.h"
#include "FractionLibrary/Fraction_global.h"
#include <QMessageBox>

bool equalsTrigger = false;

FractionCalculator::FractionCalculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FractionCalculator)
{
    ui->setupUi(this);
    ui->selectedOperator->addItem("+");
    ui->selectedOperator->addItem("-");
    ui->selectedOperator->addItem("*");
    ui->selectedOperator->addItem("/");

}

FractionCalculator::~FractionCalculator()
{
    delete ui;
}



void FractionCalculator::on_equals_clicked()
{
    int numerator1;
    int denominator1;
    int numerator2;
    int denominator2;
    Fraction answerFraction;

    // make fraction objects out of num1 and denom1, then num2 and denom2, then call selectedOperator on them. Make new fraction object

    // make fraction1 and fraction2 objects and handle nullPtr and 0 in denoms
    if(ui->num1->toPlainText().isEmpty() == true){
        QMessageBox::information(this, "Fraction Exception", "First numerator is invalid.");
        throw FractionException("First numerator is null.");

    } else {
        numerator1 = ui->num1->toPlainText().toInt();
    }

    if(ui->denom1->toPlainText().isEmpty() == true || ui->denom1->toPlainText().toInt() == 0){
        QMessageBox::information(this, "Fraction Exception", "First denominator is invalid.");
        throw FractionException("First denominator is null.");
    } else {
        denominator1 = ui->denom1->toPlainText().toInt();
    }

    Fraction fraction1 = Fraction(numerator1, denominator1);

    if(ui->num2->toPlainText().isEmpty() == true){
        QMessageBox::information(this, "Fraction Exception", "Second numerator is invalid.");
        throw FractionException("Second numerator is null.");
    } else {
        numerator2 = ui->num2->toPlainText().toInt();
    }

    if(ui->denom2->toPlainText().isEmpty() == true || ui->denom2->toPlainText().toInt() == 0){
        QMessageBox::information(this, "Fraction Exception", "Second denominator is invalid.");
        throw FractionException("Second denominator is null.");
    } else {
        denominator2 = ui->denom2->toPlainText().toInt();
    }

    Fraction fraction2 = Fraction(numerator2, denominator2);

    if(ui->selectedOperator->currentText() == ""){
        throw FractionException("No valid operator selected.");
    } else if (ui->selectedOperator->currentText() == "+"){
        answerFraction = fraction1 + fraction2;
    } else if (ui->selectedOperator->currentText() == "-"){
        answerFraction = fraction1 - fraction2;
    } else if (ui->selectedOperator->currentText() == "*"){
        answerFraction = fraction1 * fraction2;
    } else if (ui->selectedOperator->currentText() == "/"){
        answerFraction = fraction1 / fraction2;
    }

    // if the text browser isn't empty, empty it before appending new answer
    if(ui->answer->toPlainText().isEmpty() != true){
        ui->answer->clear();
    }

    // if numerator and denominator are the same, or numerator is 0, just display numerator
    // else, display full fraction
    if(answerFraction.numerator() == answerFraction.denominator() || answerFraction.numerator() == 0){
        ui->answer->append(QString::number(answerFraction.numerator()));
    } else {
        ui->answer->append(QString::number(answerFraction.numerator()) + "/" + QString::number(answerFraction.denominator()));
    }
}


void FractionCalculator::on_num1_textChanged()
{
    if(ui->answer->toPlainText().isEmpty() != true){
        ui->answer->clear();
    }
}


void FractionCalculator::on_denom1_textChanged()
{
    if(ui->answer->toPlainText().isEmpty() != true){
        ui->answer->clear();
    }
}


void FractionCalculator::on_num2_textChanged()
{
    if(ui->answer->toPlainText().isEmpty() != true){
        ui->answer->clear();
    }
}


void FractionCalculator::on_denom2_textChanged()
{
    if(ui->answer->toPlainText().isEmpty() != true){
        ui->answer->clear();
    }
}


void FractionCalculator::on_closeButton_clicked()
{
    close();
}

