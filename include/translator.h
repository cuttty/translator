//
// Created by Софья Фролова  on 07.12.2024.
//


#ifndef TRANSLATOR_TRANSLATOR__H
#define TRANSLATOR_TRANSLATOR__H

#endif //TRANSLATOR_TRANSLATOR__H
#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>

class Translator {
public:
    double evaluate(const std::string& expression) {
        std::stack<double> values;
        std::stack<char> operators;
        std::stack<char> parentheses;

        for (size_t i = 0; i < expression.size(); ++i) {
            char c = expression[i];

            if (c == '-') {
                // Check if the minus sign is at the beginning of a number
                if (i == 0 || expression[i - 1] == '(') {
                    size_t j = i + 1;
                    while (j < expression.size() && (isdigit(expression[j]) || expression[j] == '.')) {
                        ++j;
                    }
                    double value = -std::stod(expression.substr(i + 1, j - i - 1));
                    values.push(value);
                    i = j - 1;
                } else {
                    // Otherwise, treat it as a subtraction operator
                    while (!operators.empty() && precedence(c) <= precedence(operators.top())) {
                        applyOperator(values, operators);
                    }
                    operators.push(c);
                }
            } else if (isdigit(c)) {
                if (expression[i - 1] == '.' || expression[i + 1] == '.') {
                    if (expression[i - 2] == '.' || expression[i + 2] == '.') {
                        throw std::invalid_argument("Invalid floating point number");
                    } else {
                        size_t j = i + 1;
                        while (!isdigit(expression[j])) {
                            if (expression[j] == '.') {
                                throw std::invalid_argument("Invalid floating point number");
                            }
                            ++j;
                        }
                    }
                }
                // Parse number
                size_t j = i;
                while (j < expression.size() && (isdigit(expression[j]) || expression[j] == '.')) {
                    ++j;
                }
                if (j > i + 1 && expression[j] == '.') {
                    // Check if the number starts with a dot
                    if (i == 0 || !isdigit(expression[i - 1])) {
                        throw std::invalid_argument("Floating point number can't start with a dot");
                    }
                }
                double value = std::stod(expression.substr(i, j - i));
                values.push(value);
                i = j - 1;
            } else if (c == '.') {
                if (expression[i - 1] == '.' || expression[i + 1] == '.') {
                    throw std::invalid_argument("Invalid floating point number");
                }
                // Check if the dot is at the beginning of the number
                if (i == 0 || !isdigit(expression[i - 1])) {
                    throw std::invalid_argument("Floating point number can't start with a dot");
                }
            } else if (c == '(') {
                parentheses.push(c);
                operators.push(c);
            } else if (c == ')') {
                if (parentheses.empty()) {
                    throw std::invalid_argument("Unmatched closing parenthesis");
                }
                parentheses.pop();
                while (operators.top() != '(') {
                    applyOperator(values, operators);
                }
                operators.pop(); // Remove '('
            } else if (c == '+' || c == '*' || c == '/') {
                if (i == 0) {
                    throw std::runtime_error("Invalid expression");
                }
                size_t jPos = i + 1;
                size_t jNeg = i - 1;
                while (expression[jPos] == ' ') {
                    jPos++;
                }
                while (expression[jNeg] == ' ') {
                    jNeg--;
                }

                if (expression[jPos] == ')' || expression[jNeg] == '(') {
                    throw std::runtime_error("Invalid expression");
                }

                if (expression[jPos] == '(') {
                    jPos++;
                    while (expression[jPos] == ' ') {
                        jPos++;
                    }
                    if (expression[jPos] == ')') {
                        throw std::runtime_error("Invalid expression");
                    }
                }

                if (expression[jNeg] == ')') {
                    jNeg--;
                    while (expression[jNeg] == ' ') {
                        jNeg++;
                    }
                    if (expression[jNeg] == '(') {
                        throw std::runtime_error("Invalid expression");
                    }
                }

                while (!operators.empty() && precedence(c) <= precedence(operators.top())) {
                    applyOperator(values, operators);
                }
                operators.push(c);
            } else if (c == ' ') {
                // Ignore spaces
            } else {
                throw std::invalid_argument("Invalid character in input string");
            }
        }

        if (!parentheses.empty()) {
            throw std::invalid_argument("Unmatched opening parenthesis");
        }

        while (!operators.empty()) {
            applyOperator(values, operators);
        }

        if (values.size() != 1) {
            throw std::invalid_argument("Invalid expression");
        }

        return values.top();
    }

private:
    int precedence(char op) {
        if (op == '+' || op == '-') {
            return 1;
        } else if (op == '*' || op == '/') {
            return 2;
        } else {
            return 0;
        }
    }

    void applyOperator(std::stack<double>& values, std::stack<char>& operators) {
        double b = values.top();
        values.pop();
        double a = values.top();
        values.pop();
        char op = operators.top();
        operators.pop();

        switch (op) {
            case '+':
                values.push(a + b);
                break;
            case '-':
                values.push(a - b);
                break;
            case '*':
                values.push(a * b);
                break;
            case '/':
                if (b == 0) {
                    throw std::runtime_error("Division by zero");
                }
                values.push(a / b);
                break;
            default:
                throw std::invalid_argument("Invalid operator");
        }
    }
};