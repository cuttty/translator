//
// Created by Софья Фролова  on 19.12.2024.
//
#include "../include/translator.h"

int main(int argc, char **argv)
{
    //::testing::InitGoogleTest(&argc, argv);
    // return RUN_ALL_TESTS();

    Translator t1;
    std::string s = "1";

    while (s != "0") {
        try {
            std::cout << "Введите выражение: ";
            std::cin >> s;
            std::cout << s << std::endl;
            std::cout << "Результат: " << t1.evaluate(s) << std::endl;
        } catch (std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        } catch (std::runtime_error& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }
}