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
    ccArray::Array test;
    test["Hello"] = "World";

    test["array"]["nestedKey"] = "nestedValue";

    test["list"][""] = "value1";
    test["list"][""] = "value2";

    test["array2"][""] = "value1";
    test["array2"][""] = "value2";
    test["array2"]["asoc"] = "valueAsoc";

    ASSERT_EQ(ccArray::Array::TYPE_VALUE, test["Hello"].getType()) << "Test hello is value";
    ASSERT_EQ(ccArray::Array::TYPE_VALUE, test["array"]["nestedKey"].getType()) << "Test test[array][nestedKey] is value";

    ASSERT_EQ(ccArray::Array::TYPE_ARRAY, test["array"].getType()) << "Test test[array] is array";
    ASSERT_EQ(ccArray::Array::TYPE_ARRAY, test["array2"].getType()) << "Test test[array] is array";
    ASSERT_EQ(ccArray::Array::TYPE_LIST, test["list"].getType()) << "Test test[list] is list";;
}

    int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}