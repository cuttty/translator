#include <gtest.h>
#include "translator.h"

int main(int argc, char **argv)
{
    //::testing::InitGoogleTest(&argc, argv);
   // return RUN_ALL_TESTS();

     Translator t1;
     std::cout << "введите выражение: ";
     std::string s;
     std::cin >> s;
     std::cout << t1.evaluate(s) << std::endl;
}
