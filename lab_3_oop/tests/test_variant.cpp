#include <gtest/gtest.h>
#include <sstream>
#include <utility>
#include "phone_ops.h"

TEST(PhoneNumberOperations, NormalizeAndCompare) {
    PhoneNumber formatted("+7 (999) 123-45-67");
    PhoneNumber digits("79991234567");

    EXPECT_STREQ(formatted.c_str(), "79991234567");
    EXPECT_TRUE(formatted == digits);
    EXPECT_FALSE(formatted == PhoneNumber("89991234567"));
    EXPECT_TRUE(PhoneNumber(formatted.c_str()) == formatted);
    EXPECT_STREQ(PhoneNumber().c_str(), "");
    EXPECT_TRUE(PhoneNumber(" +()- ") == PhoneNumber(""));
    EXPECT_STREQ(PhoneNumber("00 (12)").c_str(), "0012");
}

TEST(PhoneNumberOperations, CopyAndMove) {
    PhoneNumber original("+7 (123)");
    PhoneNumber copy(original);

    EXPECT_NE(original.c_str(), copy.c_str());
    original = PhoneNumber("456");
    EXPECT_STREQ(copy.c_str(), "7123");

    original = copy;
    EXPECT_NE(original.c_str(), copy.c_str());
    PhoneNumber moved(std::move(original));
    EXPECT_STREQ(original.c_str(), "");
    EXPECT_STREQ(moved.c_str(), "7123");
    original = std::move(moved);
    EXPECT_STREQ(moved.c_str(), "");
    EXPECT_STREQ(original.c_str(), "7123");
}

TEST(PhoneSetOperations, EmptySet) {
    const PhoneNumberSet numbers;
    EXPECT_TRUE(numbers.empty());
    EXPECT_EQ(numbers.size(), 0);
    EXPECT_EQ(numbers.capacity(), 0);
    EXPECT_FALSE(numbers.contains("123"));
    EXPECT_FALSE(numbers("123"));
}

TEST(PhoneSetOperations, AddAndNormalizedDuplicate) {
    PhoneNumberSet numbers;
    EXPECT_TRUE(numbers.add("+7 (999) 123-45-67"));
    EXPECT_FALSE(numbers.add("79991234567"));
    EXPECT_EQ(numbers.size(), 1);
    EXPECT_TRUE(numbers.contains("7-999-123-45-67"));
    EXPECT_TRUE(numbers("79991234567"));
    EXPECT_FALSE(numbers("89991234567"));
}

TEST(PhoneSetOperations, RemoveUsesLastElement) {
    PhoneNumberSet numbers;
    numbers.add("111");
    numbers.add("222");
    numbers.add("333");
    numbers.add("444");

    EXPECT_TRUE(numbers.remove("2-22"));
    EXPECT_FALSE(numbers.remove("222"));
    EXPECT_FALSE(numbers.remove("999"));
    EXPECT_EQ(numbers.size(), 3);
    EXPECT_EQ(numbers.capacity(), 4);
    std::ostringstream out;
    out << numbers;
    EXPECT_EQ(out.str(), "{ 111, 444, 333 }");
    EXPECT_TRUE(numbers.remove("111"));
    EXPECT_TRUE(numbers.remove("444"));
    EXPECT_TRUE(numbers.remove("333"));
    EXPECT_TRUE(numbers.empty());
    EXPECT_FALSE(numbers.remove("333"));
    EXPECT_TRUE(numbers.add("555"));
}

TEST(PhoneSetOperations, CopyConstructorAndAssignment) {
    PhoneNumberSet original;
    original.add("111");
    original.add("222");
    PhoneNumberSet copy(original);

    EXPECT_EQ(copy, original);
    EXPECT_EQ(copy.capacity(), original.capacity());
    copy.remove("111");
    copy.add("333");
    original.remove("222");
    EXPECT_TRUE(original("111"));
    EXPECT_FALSE(original("333"));
    EXPECT_TRUE(copy("222"));
    EXPECT_FALSE(copy("111"));

    copy = original;
    original.remove("111");
    EXPECT_TRUE(copy("111"));
    PhoneNumberSet& alias = copy;
    copy = alias;
    EXPECT_TRUE(copy("111"));
}

TEST(PhoneSetOperations, MoveConstructorAndAssignment) {
    PhoneNumberSet original;
    original.add("111");
    original.add("222");
    PhoneNumberSet moved(std::move(original));

    EXPECT_EQ(moved.size(), 2);
    EXPECT_TRUE(moved("111"));
    EXPECT_TRUE(moved("222"));
    EXPECT_TRUE(original.empty());
    EXPECT_EQ(original.capacity(), 0);
    EXPECT_FALSE(original("111"));
    PhoneNumberSet copy(original);
    EXPECT_TRUE(copy.empty());
    EXPECT_TRUE(original.add("333"));
    EXPECT_FALSE(moved("333"));

    original = std::move(moved);
    EXPECT_TRUE(moved.empty());
    EXPECT_EQ(moved.capacity(), 0);
    EXPECT_TRUE(original("111"));
    EXPECT_FALSE(original("333"));
    PhoneNumberSet& alias = original;
    original = std::move(alias);
    EXPECT_EQ(original.size(), 2);
}

TEST(PhoneSetOperations, CompoundOperatorsReturnReference) {
    PhoneNumberSet numbers;
    EXPECT_EQ(&(numbers += "111"), &numbers);
    (numbers += "222") += "1-11";
    EXPECT_EQ(numbers.size(), 2);
    EXPECT_EQ(&(numbers -= "1-11"), &numbers);
    (numbers -= "999") -= "222";
    EXPECT_TRUE(numbers.empty());
}

TEST(PhoneSetOperations, EqualityIgnoresOrder) {
    PhoneNumberSet first;
    first.add("111");
    first.add("222");
    PhoneNumberSet second;
    second.add("2-22");
    second.add("1-11");
    EXPECT_TRUE(first == second);
    EXPECT_FALSE(first != second);

    second.remove("111");
    EXPECT_FALSE(first == second);
    EXPECT_TRUE(first != second);
    second.add("333");
    EXPECT_NE(first, second);
    EXPECT_EQ(PhoneNumberSet(), PhoneNumberSet());
}

TEST(PhoneSetOperations, PrintPreservesInsertionOrder) {
    PhoneNumberSet numbers;
    std::ostringstream empty;
    empty << numbers;
    EXPECT_EQ(empty.str(), "{ }");
    numbers.add("+3 (33)");
    numbers.add("111");
    numbers.add("222");
    std::ostringstream out;
    out << numbers;
    EXPECT_EQ(out.str(), "{ 333, 111, 222 }");
}

TEST(PhoneSetAlgebra, UnionIntersectionAndDifference) {
    PhoneNumberSet first;
    first.add("111");
    first.add("2-22");
    PhoneNumberSet second;
    second.add("222");
    second.add("333");
    const PhoneNumberSet saved_first(first);
    const PhoneNumberSet saved_second(second);

    PhoneNumberSet united = first | second;
    EXPECT_EQ(united.size(), 3);
    EXPECT_TRUE(united("111"));
    EXPECT_TRUE(united("222"));
    EXPECT_TRUE(united("333"));
    EXPECT_EQ(united, second | first);

    PhoneNumberSet common = first & second;
    EXPECT_EQ(common.size(), 1);
    EXPECT_TRUE(common("222"));
    EXPECT_EQ(common, second & first);

    PhoneNumberSet difference = first - second;
    EXPECT_EQ(difference.size(), 1);
    EXPECT_TRUE(difference("111"));
    EXPECT_FALSE(difference("222"));
    EXPECT_TRUE((second - first)("333"));
    united.remove("111");
    common.add("999");
    EXPECT_EQ(first, saved_first);
    EXPECT_EQ(second, saved_second);
}

TEST(PhoneSetAlgebra, EmptyOperandsAndSelfOperations) {
    PhoneNumberSet empty;
    PhoneNumberSet numbers;
    numbers.add("111");
    EXPECT_EQ(numbers | empty, numbers);
    EXPECT_EQ(empty | numbers, numbers);
    EXPECT_TRUE((numbers & empty).empty());
    EXPECT_TRUE((empty & numbers).empty());
    EXPECT_EQ(numbers - empty, numbers);
    EXPECT_TRUE((empty - numbers).empty());
    EXPECT_EQ(numbers | numbers, numbers);
    EXPECT_EQ(numbers & numbers, numbers);
    EXPECT_TRUE((numbers - numbers).empty());
    EXPECT_TRUE((empty | empty).empty());
    EXPECT_TRUE((empty & empty).empty());
    EXPECT_TRUE((empty - empty).empty());
}

TEST(PhoneSetStress, ThousandAdditionsDuplicatesAndRemovals) {
    PhoneNumberSet numbers;
    for (int i = 0; i < 1000; i++) {
        std::ostringstream text;
        text << "+7 (900) " << i;
        ASSERT_TRUE(numbers.add(PhoneNumber(text.str().c_str())));
    }
    EXPECT_EQ(numbers.size(), 1000);
    EXPECT_EQ(numbers.capacity(), 1024);

    for (int i = 0; i < 1000; i++) {
        std::ostringstream text;
        text << "7900" << i;
        PhoneNumber number(text.str().c_str());
        EXPECT_TRUE(numbers(number));
        EXPECT_FALSE(numbers.add(number));
    }
    EXPECT_EQ(numbers.size(), 1000);
    PhoneNumberSet copy(numbers);
    for (int i = 0; i < 1000; i++) {
        std::ostringstream text;
        text << "7900" << i;
        EXPECT_TRUE(numbers.remove(PhoneNumber(text.str().c_str())));
    }
    EXPECT_TRUE(numbers.empty());
    EXPECT_EQ(copy.size(), 1000);
    EXPECT_TRUE(copy("7900999"));
}
