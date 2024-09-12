#include "../StackLinedlist/Stack.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using std::string;
using std::stringstream;

double calculate(double a, char op, double b)
{
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '^':
            return std::pow(a, b);

        default:
            throw std::invalid_argument("Invalid Operator");
    }
}

double calculate(string expr)
{
    Stack operands;
    stringstream ss(expr);
    string op;
    while(ss >> op)
    {
        try
        {
            double operand{ std::stod(op) };
            operands.push(operand);
        }
        catch(const std::invalid_argument& ex)
        {
            double secondOperand{ operands.pop() };
            double firstOperand{ operands.pop() };
            operands.push(calculate(firstOperand, op[0], secondOperand));
        }
    }
    return operands.pop();
}

int main()
{
    string expr{};
    std::getline(std::cin, expr);
    std::cout << expr << " = " << calculate(expr) << '\n';
    return 0;
}
