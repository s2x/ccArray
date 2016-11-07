//
// Created by piotr on 07.11.16.
//
#include <gtest/gtest.h>
#include "../src/Array.h"

TEST(ArraySimpleTests, ValueAssign) {
    ccArray::Array test;
    ASSERT_EQ(std::string("NULL"), test.toString()) << "Empty array to string NULL";

    test["testKey"] = "testValue";
    test["nested"]["nestedKey"] = "nestedValue";
    ASSERT_EQ(std::string("testValue"), (std::string)test["testKey"]) << "Get simple value from array";
    ASSERT_EQ(std::string("nestedValue"), (std::string)test["nested"]["nestedKey"]) << "Get nested value";
}

TEST(ArraySimpleTests, ArrayType) {

}

    int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}