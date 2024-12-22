//
// Created by Софья Фролова  on 19.12.2024.
//
#include "../include/translator.h"

int main(int argc, char **argv)
{
    Translator translator;
    std::string expression = "";

    std::cout << "Welcome to the Calculator!" << std::endl << std::endl;

    while (expression != "0") {
        std::cout << "Enter a mathematical expression: ";
        std::getline(std::cin, expression);

        try {
            double result = translator.evaluate(expression);
            std::cout << "Result: " << result << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Error evaluating expression: " << e.what() << std::endl;
        }
    }
    std::cout << "Thanks for using the Calculator!" << std::endl << std::endl;
    return 0;

}