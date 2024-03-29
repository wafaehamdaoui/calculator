# calculator

This project shows how to use signals and slots to implement the functionality of a calculator widget, and how to use QGridLayout to place child widgets in a grid.

![image](https://user-images.githubusercontent.com/75392302/141868380-331a6cd1-1f0b-452c-899a-75543cbac429.png)


This project consists of one class is the calculator class, with all the calculator functionality.

## Declaration of class:

The Calculator class provides a simple calculator widget. It inherits from QWidget and has several private slots associated with the calculator's buttons.

The layout is handled by a single QGridLayout. Most child widgets occupy only one cell in the grid layout;we only need to pass a row and a column to addWidget(). Except the clear widget occupy more than one column

Buttons are grouped in categories(digits and operations) according to their behavior.

All the digit buttons (labeled 0 to 9) append a digit.

![image](https://user-images.githubusercontent.com/75392302/141998955-794124f0-6c57-4667-b2f2-84ae0fb3d009.png)


And all the operation buttons ( +, - , * , / , pow ) define which operation we will do.

![image](https://user-images.githubusercontent.com/75392302/141999251-d978eebc-9049-4476-a0c1-f96163679b13.png)


The other buttons( enter, = , sqrt , clear) have their own slots( Equal() , Sqrt_function() , Clear()).

![image](https://user-images.githubusercontent.com/75392302/141999538-ef378f6e-f11c-4c61-bc0c-9c68631454dd.png)

### Remark:
to understand more the construction of the claculator widget and how we orgnise and place its child widgets you can visit Fun_Whith_layouts repository ,here is the link:https://github.com/wafaehamdaoui/Fun-with-Layout

# Calculator Class Implementation:

These variables, together with the contents of the calculator display (a QLCDNumber), encode the state of the calculator:

```cpp
double calcValue = 0.0;
bool divTrigger=false;
bool addTrigger=false;
bool multiTrigger=false;
bool subTrigger=false;
bool powTrigger=false;
```

calcValue : contains the value stored in the calculator's disp .Clear All resets calcValue to zero.

divTrigger : stores a temporary value when clicked on  division button.

multiTrigger : stores a temporary value when clicked on  multiplication button.

addTrigger : stores a temporary value when clicked on  addition button.

subTrigger : stores a temporary value when clicked on substraction button.

The value of these variables, determine wich operations I will make betwen the two numbers. So they take "false" first and if I clicked on the operation this variable will take "true". 

The table below shows the evolution of the calculator state as the user enters a mathematical expression.

![image](https://user-images.githubusercontent.com/75392302/142051701-4eb9dc09-549c-488d-90e5-47ea78d83c50.png)

Pressing one of the calculator's digit buttons will emit the button's clicked() signal, which will trigger the newDigits() slot. And we append the new digit to the value in the display.

```cpp
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
```

And Pressing one of the calculator's operation buttons will emit the button's clicked() signal, which will trigger the makeOperation() slot.

```cpp
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
```

Then we perform the operation. If we pressing  '/' so we should check if the deminator is defferent to zero if it's the case so we append "error" . If  everything goes well and  after pressing 'enter' ou '=' button  the result of the operation will display in the LCDNumber .

```cpp
void Calculator::Equal()
{

    double result=0.0;
    auto power = 1.0;
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
            power *=calcValue;
         }
         result = power;
     }

    disp->display(result);
  }
}
```



And we set diviTrigger/multiTrigger/addTrigger/subTrigger to false. This ensures that if the user types a new digit, the digit will be considered as a new operand, instead of being appended to the current value.

```cpp
    divTrigger=false;
     addTrigger=false;
     multiTrigger=false;
     subTrigger=false;
     powTrigger=false;
```

For the sqrt_function() we shoud verify if the operand number is positive if yes so we can make the operation , if not we will display "error" in the LCDNumber.

```cpp
void Calculator::Sqrt_function(){

   auto diplay = disp->value();
   Clear();
   if(diplay>0)
       disp->display(sqrt(diplay));
   disp->display("Error");
}
```
here is a short similation:

![error_s_1_](https://user-images.githubusercontent.com/75392302/142069732-832911dc-4f0b-4f08-b57a-0d119085a9a5.gif)

The Clear() slot resets the calculator to its initial state.

```cpp
void Calculator::Clear(){
        disp->display(0);
        left=nullptr;
        right=nullptr;
 }
```
here is a short similation:

![Screenrecorder-2021-11-16-23-01-06-68_1_](https://user-images.githubusercontent.com/75392302/142073237-f87a2469-f914-400e-affe-ffaa56a8ed0f.gif)


## Demo:

This video in the links shows how the Calculator works.

Addition example : https://github.com/wafaehamdaoui/calculator/blob/main/Addition.gif



## conclusion:

Now our calculator is ready to do any basic operation and some complexe operation like pow and sqrt.

what we can look for now is to adding the three or more operand such as (24 * 23 + 23)!


> Excellent work. Loved the illustration and the extreme case processing of sqrt(-4).
