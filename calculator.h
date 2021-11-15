#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <QLCDNumber>

class Calculator : public QWidget
{
    Q_OBJECT
public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();




 // Add you custom slots here

protected:
    void createWidgets();        //Function to create the widgets
    void placeWidget();         // Function to place the widgets
    void makeConnexions();      // Create all the connectivity

//events
protected:
    void keyPressEvent(QKeyEvent *e)override;     //Override the keypress events

private:
    QGridLayout *buttonsLayout; // layout for the buttons
    QVBoxLayout *layout;        //main layout for the button
    QVector<QPushButton*> digits;  //Vector for the digits
    QPushButton *enter;            // enter button
    QPushButton *clear;            // clrear button
    QPushButton *equal;            // = button
    QPushButton *Sqrt;            // = button

    QVector<QPushButton*> operations; //operation buttons
    QLCDNumber  *disp;             // Where to display the numbers
    int * left;          //left operand
    int * right;         // right operand
    QString *operation;  // Pointer on the current operation
    double  *leftOperand;          //left operand
    double * rightOperand;

public slots:
    void newDigit();
    void makeOperation();
    void Clear();
    void Sqrt_function();
    void Equal();


//        void button0Clicked();
//        void button1Clicked();
//        void button2Clicked();
//        void button3Clicked();
//        void button4Clicked();
//        void button5Clicked();
//        void button6Clicked();
//        void button7Clicked();
//        void button8Clicked();
//        void button9Clicked();


};
#endif // CALCULATOR_H
