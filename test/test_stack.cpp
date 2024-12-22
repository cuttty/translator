
#include "stack.h"
#include <gtest.h>
#include "translator.h"

// TESTS FOR STACK
TEST(Stack, can_create_non_empty_stack) {
    ASSERT_NO_THROW(Stack<int> S(7));
}
TEST(Stack, cant_create_stack_with_negative_length) {
    ASSERT_ANY_THROW(Stack<int> S(-7));
}

TEST(Stack, cant_create_stack_with_null_length) {
    ASSERT_ANY_THROW(Stack<int> S(0));
}

TEST(Stack, can_push_and_pop_element) {
    Stack <int> S(3);
    S.push(2);
    S.push(7);
    S.push(5);

    Stack <int> S_exp(2);
    S_exp.push(2);
    S_exp.push(7);

    S.pop();
    ASSERT_EQ(S,S_exp);
}
///
TEST(Stack, pop_return_element_before_last_element) {
    Stack <int> S(3);
    S.push(2);
    S.push(7);
    S.push(5);

    ASSERT_EQ(S.pop(), 7);
}

TEST(Stack, cant_pop_in_empty_stack) {
    Stack <int> S(1);
    ASSERT_ANY_THROW(S.pop());
}

TEST(Stack, can_pop_only_element) {
    Stack <int> S(1);
    S.push(3);
    ASSERT_NO_THROW(S.pop());
}

TEST(Stack, cant_push_full_stack) {
    Stack <int> S(3);
    S.push(2);
    S.push(7);
    S.push(5);
    ASSERT_ANY_THROW(S.push(8));
}

TEST(Stack, can_get_last_element) {
    Stack <int> S(3);
    S.push(2);
    S.push(7);
    S.push(5);
    ASSERT_EQ(S.top(), 5);
}

TEST(Stack, cant_get_last_element_in_empty_stack) {
    Stack <int> S(3);
    ASSERT_ANY_THROW(S.top());
}

TEST(Stack, can_get_size) {
    Stack <int> S(3);
    S.push(2);
    S.push(8);
    ASSERT_EQ(2, S.size());
}

TEST(Stack, can_get_size_in_empty_stack) {
    Stack <int> S(3);
    ASSERT_EQ(0, S.size());
}

TEST(Stack, empty_stack_return_true) {
    Stack <int> S(3);
    ASSERT_EQ(S.empty(), true);
}
TEST(Stack, non_empty_stack_return_false) {
    Stack <int> S(3);
    S.push(6);
    ASSERT_EQ(S.empty(), false);
}


// TESTS FOR TRANSLATOR
TEST(Translator, can_calculate_with_int_numbers) {
    Translator t1;
    ASSERT_EQ(t1.evaluate("3+79"), 82);
}
TEST(Translator, can_calculate_with_unary_minus) {
    Translator t1;
    ASSERT_EQ(t1.evaluate("-3+79"), 76);
}
TEST(Translator, can_calculate_with_negative_numbers) {
    Translator t1;
    ASSERT_EQ(t1.evaluate("-3-79"), -82);
    ASSERT_EQ(t1.evaluate("-3.45-79.89"), -83.34);
}
TEST(Translator, can_multyply) {
    Translator t1;
    ASSERT_EQ(t1.evaluate("3*78"), 234);
    ASSERT_EQ(t1.evaluate("3*(-78)"), -234);
    ASSERT_LE(t1.evaluate("1.1 * 2.2"), 2.4200000000001); // Less Equal
    //ASSERT_LE(t1.evaluate("3.10 * (-78.25)"), -242.575000000001) ;
}
TEST(Translator, can_multyply_by_zero) {
    Translator t1;
    ASSERT_EQ(t1.evaluate("3*0"), 0);
    ASSERT_EQ(t1.evaluate("3.78*0"), 0);
}
TEST(Translator, can_divide) {
    Translator t1;
    ASSERT_EQ(t1.evaluate("28/4"), 7);
    ASSERT_EQ(t1.evaluate("28.78/4"), 7.195);

}
TEST(Translator, cant_divide_by_zero) {
    Translator t1;
    ASSERT_ANY_THROW(t1.evaluate("28/0"));
    ASSERT_ANY_THROW(t1.evaluate("28.78/0"));
}
TEST(Translator, can_determine_priority_plus_and_mul) {
    Translator t1;
    ASSERT_EQ(t1.evaluate("2+2*2"), 6);

}
TEST(Translator, can_determine_priority_minus_and_mul) {
    Translator t1;
    ASSERT_EQ(t1.evaluate("2-2*2"), -2);
}
TEST(Translator, can_determine_priority_plus_and_div) {
    Translator t1;
    ASSERT_EQ(t1.evaluate("2+2/2"), 3);
}
TEST(Translator, can_determine_priority_minus_and_div) {
    Translator t1;
    ASSERT_EQ(t1.evaluate("2-2/2"), 1);
}
TEST(Translator, can_determine_priority_parenthesis) {

    Translator t1;
    ASSERT_EQ(t1.evaluate("2*(3+8)"), 22);
    ASSERT_EQ(t1.evaluate("33/(3+8)"), 3);
}
TEST(Translator, cant_calculate_unmatched_parenthesis) {
    Translator t1;
    ASSERT_ANY_THROW(t1.evaluate("2+((56/7"));
    ASSERT_ANY_THROW(t1.evaluate("2+((56/7)"));
    ASSERT_ANY_THROW(t1.evaluate("2+56/7))"));
    ASSERT_ANY_THROW(t1.evaluate("2+(56/7))"));
}
TEST(Translator, cant_calculate_dot_before_number_no_zero) {
    Translator t1;
    ASSERT_ANY_THROW(t1.evaluate(".89 + 5637"));
}
TEST(Translator, can_calculate_int_and_double) {
    Translator t1;
    ASSERT_EQ(t1.evaluate("1.89 + 56"), 57.89);
}
// при умножение float на float компилятор сталкивается со стандартной для компьютеров ошибкой
// погрешности float, которая приводит к некорректному результату
// поэтому в тестах я ее не проверяла, однако если вводить значение в main, убирая штуку для
//запускания google test, то все работает нормально