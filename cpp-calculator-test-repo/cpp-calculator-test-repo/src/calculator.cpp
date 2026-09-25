#include "calculator.h"

double calculate(double a, char operation, double b)
{
    switch (operation)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default:  return 0.0;
    }
}
