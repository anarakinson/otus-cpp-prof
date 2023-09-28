#include <ip_filter.h>

#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>


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


//////////////