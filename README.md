# calculator

This project shows how to use signals and slots to implement the functionality of a calculator widget, and how to use QGridLayout to place child widgets in a grid.

![image](https://user-images.githubusercontent.com/75392302/141868380-331a6cd1-1f0b-452c-899a-75543cbac429.png)


The project consists of a class:

Calculator is the calculator widget, with all the calculator functionality.

The Calculator class provides a simple calculator widget. It inherits from QWidget and has several private slots associated with the calculator's buttons.

Buttons are grouped in categories(digits and operations) according to their behavior.

All the digit buttons (labeled 0 to 9) append a digit.

And all the operation buttons ( +, - , * , / , pow ) define which operation we will do.

The other buttons( enter, = , sqrt) have their own slots( Equal() , Sqrt_function).

These variables, together with the contents of the calculator display (a QLCDNumber), encode the state of the calculator:

calcvalue : contains the value stored in the calculator's disp .Clear All resets calcValue to zero.

divTrigger : stores a temporary value when clicked on  division button.

multiTrigger : stores a temporary value when clicked on  multiplication button.

addTrigger : stores a temporary value when clicked on  addition button.

subTrigger : stores a temporary value when clicked on substraction button.

The value of these variables, determine wich operations I will make betwen the two numbers. So they take "false" first and if I clicked on the operation this variable will take "true". 

The table below shows the evolution of the calculator state as the user enters a mathematical expression.

![image](https://user-images.githubusercontent.com/75392302/141990326-a7cdbdf6-9c25-441c-9537-4a3e7d76adf9.png)


