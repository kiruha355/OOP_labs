#include <gtest/gtest.h>
#include <sstream>
#include <utility>
#include "string_ops.h"

TEST(StringOperations, EmptyString) {
    String text;
    EXPECT_TRUE(text.empty());
    EXPECT_EQ(text.size(), 0);
    EXPECT_EQ(text.capacity(), 1);
    EXPECT_STREQ(text.c_str(), "");
}

TEST(StringOperations, CreateFromText) {
    String text("Hello");
    EXPECT_EQ(text.size(), 5);
    EXPECT_STREQ(text.c_str(), "Hello");
}

TEST(StringOperations, DeepCopy) {
    String original("abc");
    String copy(original);
    copy[0] = 'X';
    EXPECT_STREQ(original.c_str(), "abc");
    EXPECT_STREQ(copy.c_str(), "Xbc");
}

TEST(StringOperations, MoveConstructor) {
    String original("abc");
    const char* buffer = original.c_str();
    String moved(std::move(original));
    EXPECT_EQ(moved.c_str(), buffer);
    EXPECT_STREQ(moved.c_str(), "abc");
    EXPECT_TRUE(original.empty());
    EXPECT_STREQ(original.c_str(), "");
    original.push_back('x');
    EXPECT_STREQ(original.c_str(), "x");
}

TEST(StringOperations, CopyAssignment) {
    String original("abc");
    String copy("old text");
    copy = original;
    original[0] = 'X';
    EXPECT_STREQ(copy.c_str(), "abc");
}

TEST(StringOperations, MoveAssignment) {
    String original("abc");
    String moved("old text");
    const char* buffer = original.c_str();
    moved = std::move(original);
    EXPECT_EQ(moved.c_str(), buffer);
    EXPECT_STREQ(moved.c_str(), "abc");
    EXPECT_TRUE(original.empty());
}

TEST(StringOperations, SelfAssignment) {
    String text("abc");
    text = text;
    EXPECT_STREQ(text.c_str(), "abc");
    text = std::move(text);
    EXPECT_STREQ(text.c_str(), "abc");
}

TEST(StringOperations, PushBackAndGrowth) {
    String text;
    text.push_back('a');
    EXPECT_EQ(text.capacity(), 1);
    text.push_back('b');
    EXPECT_EQ(text.capacity(), 2);
    text.push_back('c');
    EXPECT_EQ(text.capacity(), 4);
    EXPECT_STREQ(text.c_str(), "abc");
    EXPECT_EQ(text[text.size()], '\0');
}

TEST(StringOperations, AppendAndEmpty) {
    String text("Hello");
    text.append("");
    text.append(", World!");
    EXPECT_STREQ(text.c_str(), "Hello, World!");
    String empty;
    empty.append(text);
    EXPECT_STREQ(empty.c_str(), text.c_str());
}

TEST(StringOperations, AppendToSelf) {
    String text("abc");
    text.append(text);
    EXPECT_STREQ(text.c_str(), "abcabc");
}

TEST(StringOperations, FindSubstring) {
    String text("Hello, World!");
    EXPECT_EQ(text.find("World"), 7);
    EXPECT_EQ(text.find("!"), 12);
    EXPECT_EQ(text.find("missing"), String::npos);
    EXPECT_EQ(text.find(""), 0);
    EXPECT_EQ(String().find(""), 0);
    EXPECT_EQ(String().find("a"), String::npos);
}

TEST(StringOperations, ClearAndReuse) {
    String text("abc");
    std::size_t capacity = text.capacity();
    text.clear();
    EXPECT_TRUE(text.empty());
    EXPECT_STREQ(text.c_str(), "");
    EXPECT_EQ(text.capacity(), capacity);
    text.push_back('x');
    EXPECT_STREQ(text.c_str(), "x");
}

TEST(StringOperations, PrintAndSwap) {
    String first("abc");
    String second("xyz");
    first.swap(second);
    std::ostringstream out;
    first.print(out);
    EXPECT_EQ(out.str(), "xyz");
    EXPECT_STREQ(second.c_str(), "abc");
}

TEST(StringWrap, WidthFour) {
    String text("aa bb ccc");
    EXPECT_STREQ(text.wrap(4).c_str(), "aa\nbb\nccc");
    EXPECT_STREQ(text.c_str(), "aa bb ccc");
}

TEST(StringWrap, ExactWidth) {
    EXPECT_STREQ(String("aa bb ccc").wrap(5).c_str(), "aa bb\nccc");
    EXPECT_STREQ(String("aa bb").wrap(5).c_str(), "aa bb");
}

TEST(StringWrap, EmptyAndOneCharacter) {
    EXPECT_STREQ(String().wrap(4).c_str(), "");
    EXPECT_STREQ(String("a").wrap(1).c_str(), "a");
    EXPECT_STREQ(String("a b c").wrap(1).c_str(), "a\nb\nc");
}

TEST(StringWrap, LongWord) {
    EXPECT_STREQ(String("a abcdef b").wrap(3).c_str(), "a\nabcdef\nb");
}

TEST(StringWrap, ExtraSpaces) {
    EXPECT_STREQ(String("  aa   bb\tccc  ").wrap(5).c_str(), "aa bb\nccc");
    EXPECT_STREQ(String("   ").wrap(5).c_str(), "");
}

TEST(StringWrap, ExistingNewlines) {
    EXPECT_STREQ(String("aa\nbb ccc").wrap(6).c_str(), "aa\nbb ccc");
    EXPECT_STREQ(String("\n\naa\n").wrap(5).c_str(), "\n\naa\n");
}

TEST(StringWrap, WideLine) {
    EXPECT_STREQ(String("one two three").wrap(80).c_str(), "one two three");
}
