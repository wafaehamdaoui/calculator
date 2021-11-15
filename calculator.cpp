#include "calculator.h"
#include <QKeyEvent>
#include <QApplication>
#include <math.h>

double calcValue = 0.0;
bool divTrigger=false;
bool addTrigger=false;
bool multiTrigger=false;
bool subTrigger=false;
bool powTrigger=false;


Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    createWidgets();
    placeWidget();
    makeConnexions();


}

Calculator::~Calculator()
{
    delete disp;
    delete layout;
    delete buttonsLayout;
}


void Calculator::createWidgets()
{
    //Creating the layouts
    layout = new QVBoxLayout();
    layout->setSpacing(2);

    //grid layout
    buttonsLayout = new QGridLayout;


    //creating the buttons
    for(int i=0; i < 10; i++)
    {
        digits.push_back(new QPushButton(QString::number(i)));
        digits.back()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        digits.back()->resize(sizeHint().width(), sizeHint().height());
    }
    //. button
    Sqrt = new QPushButton("sqrt",this);
    Sqrt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    Sqrt->resize(sizeHint().width(), sizeHint().height());

    //= button
    equal = new QPushButton("=",this);
    equal->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    equal->resize(sizeHint().width(), sizeHint().height());

    //enter button
    enter = new QPushButton("Enter",this);
    enter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    enter->resize(sizeHint().width(), sizeHint().height());
    //clear button
    clear = new QPushButton("Clear All",this);
    clear->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    clear->resize(sizeHint().width(), sizeHint().height());



    //operatiosn buttons
    operations.push_back(new QPushButton("+"));
    operations.push_back(new QPushButton("-"));
    operations.push_back(new QPushButton("*"));
    operations.push_back(new QPushButton("/"));
    operations.push_back(new QPushButton("pow"));



    //creating the lcd
    disp = new QLCDNumber(this);
    disp->setDigitCount(6);

}

void Calculator::placeWidget()
{

    layout->addWidget(disp);
    layout->addLayout(buttonsLayout);


    //adding the buttons
    for(int i=1; i <10; i++)
        buttonsLayout->addWidget(digits[i], (i-1)/3, (i-1)%3);


    //Adding the operations
    for(int i=0; i < 5; i++)
        buttonsLayout->addWidget(operations[ i], i, 5);

    //Adding the 0 button
    buttonsLayout->addWidget(digits[0], 3, 0);
    buttonsLayout->addWidget(equal, 3, 1, 1,1);
    buttonsLayout->addWidget(clear, 4, 0, 1,2);
    buttonsLayout->addWidget(enter, 3, 2, 1,1);
    buttonsLayout->addWidget(Sqrt, 4,2,1,1);

    setLayout(layout);
}

void Calculator::newDigit(){

        auto button = dynamic_cast<QPushButton*>(sender());

        //getting the value
        int value = button->text().toInt();

        //Check if we have an operation defined
        if(operation)
        {
            //check if we have a value or not
            if(!right)
                right = new int{value};
            else
                *right = 10 * (*right) + value;

            disp->display(*right);

        }
        else
        {
            if(!left)
                left = new int{value};
            else
                *left = 10 * (*left) + value;

            disp->display(*left);
        }


}

void Calculator::makeOperation()
{


     divTrigger=false;
     addTrigger=false;
     multiTrigger=false;
     subTrigger=false;
     powTrigger=false;

     auto button = dynamic_cast<QPushButton*>(sender());
     calcValue = disp->value();

     QString Operation = button->text();
     if(QString::compare(Operation,"/",Qt::CaseInsensitive)==0){
         divTrigger = true;
     }else if(QString::compare(Operation,"*",Qt::CaseInsensitive)==0){
         multiTrigger = true;
     }else if(QString::compare(Operation,"+",Qt::CaseInsensitive)==0){
         addTrigger = true;
     }else if(QString::compare(Operation,"-",Qt::CaseInsensitive)==0){
         subTrigger = true;
     }else if(QString::compare(Operation,"pow",Qt::CaseInsensitive)==0){
         powTrigger = true;
}

     Clear();

}

void Calculator::Clear(){
        disp->display(0);
//        delete left;
        left=nullptr;
//        delete right;
        right=nullptr;
 }

void Calculator::keyPressEvent(QKeyEvent *e)
{
    //Exiting the application by a click on space
    if( e->key() == Qt::Key_Escape)
        qApp->exit(0);
}
void Calculator::Sqrt_function(){

   auto diplay = disp->value();
   Clear();
    disp->display(sqrt(diplay));
}

void Calculator::makeConnexions()
{

    for(int i=0; i <10; i++)
         connect(digits[i], &QPushButton::clicked,
                 this, &Calculator::newDigit);
    connect(clear, &QPushButton::clicked,
            this, &Calculator::Clear);
    connect(Sqrt, &QPushButton::clicked,
            this, &Calculator::Sqrt_function);
    for(int i=0; i < 5; i++){
    connect(operations[i], &QPushButton::clicked,
            this, &Calculator::makeOperation);}
    connect(equal,&QPushButton::clicked,this,&Calculator::Equal);
    connect(enter, &QPushButton::clicked,
            this, &Calculator::Equal);



}
void Calculator::Equal()
{

    double result=0.0;
//    QString dispValue = QString :: number(disp->value());
    double dispValue = disp->value();
    if(addTrigger || subTrigger || divTrigger || multiTrigger || powTrigger){
     if (addTrigger) {
           result = calcValue + dispValue ;
       } else if (subTrigger) {
           result = calcValue - dispValue;
       } else if (multiTrigger) {
           result = calcValue * dispValue;
       } else if (divTrigger) {
           if (dispValue == 0.0)
               disp->display("Error");
           result = calcValue / dispValue;
       } else if (powTrigger) {
         for(int i=dispValue  ; i>0 ; i--){
             result = calcValue ;
             result *=calcValue;
         }
     }

    disp->display(result);


}
}
