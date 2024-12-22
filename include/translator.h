#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <stdexcept>

class Translator {
public:
    double evaluate(const std::string& expression) {
        std::string postfix = infixToPostfix(expression);
        return evaluatePostfix(postfix);
    }

private:
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    } // приоритет операций

    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    } // проверка на оператор

    bool isValidNumber(const std::string& token) {
        bool hasDot = false;
        for (char c : token) {
            if (!isdigit(c)) {
                if (token[0] == '-' && isdigit(token[1])) continue;
                if (c == '.') {
                    if (hasDot) return false;
                    hasDot = true;
                } else {
                    return false;
                }
            }
        }
        return true;
    }

    std::string infixToPostfix(const std::string& infix) {
        std::stack<char> operators;
        std::ostringstream output; // поток строки
        std::string token; //
        int openParentheses = 0;

        for (size_t i = 0; i < infix.length(); ++i) {
            char c = infix[i];


            if (isdigit(c) || (c == '-' && (i == 0 || isOperator(infix[i - 1]) || infix[i - 1] == '('))) {
                token.clear();
                if (c == '-') {
                    token += c;
                    i++;
                }
                while (i < infix.length() && (isdigit(infix[i]) || infix[i] == '.')) {
                    token += infix[i++];
                }
                output << token << ' ';
                --i;
            } else if (c == '(') {
                operators.push('(');
                openParentheses++;
            } else if (c == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    output << operators.top() << ' ';
                    operators.pop();
                }
                if (operators.empty()) {
                    throw std::runtime_error("Unmatched parentheses");
                }
                operators.pop();
                openParentheses--;
            } else if (isOperator(c)) {
                while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                    output << operators.top() << ' ';
                    operators.pop();
                }
                operators.push(c);
            } else if (!isspace(c)) {
                throw std::runtime_error("Invalid token: " + std::string(1, c));
            }
        }

        while (!operators.empty()) {
            if (operators.top() == '(') {
                throw std::runtime_error("Unmatched parentheses");
            }
            output << operators.top() << ' ';
            operators.pop();
        }

        if (openParentheses > 0) {
            throw std::runtime_error("Unmatched parentheses");
        }

        return output.str();
    }

    double evaluatePostfix(const std::string& postfix) {
        std::stack<double> values;
        std::istringstream tokens(postfix); // из постфикса сделать строку
        std::string token;

        //

        while (tokens >> token) {
            if (isValidNumber(token)) {
                values.push(std::stod(token));
            } else if (isOperator(token[0])) {
                if (values.size() < 2) {
                    throw std::runtime_error("Invalid expression: not enough values for operation");
                }
                double right = values.top(); values.pop();
                double left = values.top(); values.pop();
                switch (token[0]) {
                    case '+': values.push(left + right); break;
                    case '-': values.push(left - right); break;
                    case '*': values.push(left * right); break;
                    case '/':
                        if (right == 0) {
                            throw std::runtime_error("Division by zero");
                        }
                        values.push(left / right);
                        break;
                }
            }
        }

        if (values.size() != 1) {
            throw std::runtime_error("Invalid expression: too many values remaining");
        }

        return values.top();
    }
};