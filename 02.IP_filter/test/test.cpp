#include <ip_filter.hpp>

#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>


TEST(Basic, Basic_Test) {
    int a = 1;
    int b = 1;
    EXPECT_EQ(a, b);
}


TEST(Test, Basic_Test) {
    // Arrange
    const int expected_zero_size = 0;
    
    std::vector<std::string> vec{};

    // Assert
    EXPECT_EQ(vec.size(), expected_zero_size);

    vec.push_back("1");
    const size_t expected_size = 1;

    EXPECT_NE(vec.size(), expected_zero_size);
    EXPECT_EQ(vec.size(), expected_size);
}


TEST(Test, Split_Test) {
    // Arrange
    std::vector<std::string> vec0{"1", "2", "3", "4"};   // 1.2.3.4
    std::string str{"1.2.3.4"};
    
    // Act
    std::vector<std::string> vec1 = split(str, '.');

    // Assert
    EXPECT_EQ(vec0, vec1);
}


TEST(Test, Comparison_Test) {
    // Arrange
    std::vector<std::string> vec0{"1", "2", "3", "4"};   // 1.2.3.4
    std::vector<std::string> vec1{"2", "2", "3", "4"};   // 2.2.3.4
    std::vector<std::string> vec2{"10", "2", "3", "4"};  // 10.2.3.4
    std::vector<std::string> vec3{"1", "2", "4", "125"}; // 1.2.3.125

    std::array<uint8_t, 4> row0 = convert_row(vec0);
    std::array<uint8_t, 4> row1 = convert_row(vec1);
    std::array<uint8_t, 4> row2 = convert_row(vec2);
    std::array<uint8_t, 4> row3 = convert_row(vec3);

    // Assert
    // Greater than
    EXPECT_GT(vector_cmp(row3, row0), false);
    EXPECT_GT(vector_cmp(row2, row1), false);
    EXPECT_GT(vector_cmp(row2, row3), false);
    // Less than
    EXPECT_LT(vector_cmp(row3, row1), true);
}


TEST(Test, Filter_Test) {
    // Arrange
    std::array<uint8_t, 4> vec0{1, 2, 3, 4};       // 1.2.3.4
    std::array<uint8_t, 4> vec1{1, 2, 124, 125};   // 1.2.124.125
    std::array<uint8_t, 4> vec2{1, 125, 3, 4};     // 1.125.3.4
    std::array<uint8_t, 4> vec3{11, 2, 4, 4};      // 11.2.3.125

    // Act
    std::vector<std::array<uint8_t, 4>> all_vecs{vec0, vec1, vec2, vec3};
    std::vector<std::array<uint8_t, 4>> reference{vec0, vec1};      // started with '1.2'

    std::vector<std::array<uint8_t, 4>> filtered = filter(all_vecs, 1, 2);     // started with '1.2'

    // Assert
    EXPECT_EQ(reference, filtered);
}


TEST(Test, Filter_Any_Test) {
    // Arrange
    std::array<uint8_t, 4> vec0{1, 2, 3, 4};       // 1.2.3.4
    std::array<uint8_t, 4> vec1{1, 2, 124, 125};   // 1.2.124.125
    std::array<uint8_t, 4> vec2{1, 125, 3, 4};     // 1.125.3.4
    std::array<uint8_t, 4> vec3{11, 2, 4, 4};      // 11.2.3.125

    // Act
    std::vector<std::array<uint8_t, 4>> all_vecs{vec0, vec1, vec2, vec3};
    std::vector<std::array<uint8_t, 4>> reference{vec1, vec2};      // contains '125.'

    std::vector<std::array<uint8_t, 4>> filtered = filter_any(all_vecs, 125);  // contains '125.'

    // Assert
    EXPECT_EQ(reference, filtered);
}



int main(int argc, char** argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
