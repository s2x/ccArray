//
// Created by piotr on 07.11.16.
//
#include <gtest/gtest.h>
#include "../include/ccArray/Array.h"

ccArray::Array getEmptyArray() {
    ccArray::Array ret;
    return ret;
}

ccArray::Array setArrayKeyValue(ccArray::Array array, std::string key, std::string value) {
    array[key] = value;
    return array;
}

TEST(ArraySimpleTests, ValueAssign) {
    ccArray::Array test;
    ASSERT_EQ(std::string("NULL"), test.toString()) << "Empty array to string NULL";

    test["testKey"] = "testValue";
    test["nested"]["nestedKey"] = "nestedValue";
    ASSERT_EQ(std::string("testValue"), (std::string)test["testKey"]) << "Get simple value from array";
    ASSERT_EQ(std::string("nestedValue"), (std::string)test["nested"]["nestedKey"]) << "Get nested value";
}

TEST(ArraySimpleTests, basicFunctions) {
    ccArray::Array test;
    test["testKey"] = "testValue";

    ASSERT_EQ(std::string("testValue"), test["testKey"].getValue()) << "Get simple value from array by getValue";
    ASSERT_EQ(std::string("testKey"), test["testKey"].getName()) << "Get simple value from array by getValue";
    ASSERT_FALSE(test["testKey"].hasChildrens());
    ASSERT_TRUE(test.hasChildrens());
    ASSERT_EQ(1, test.getChildrens().size());

    ASSERT_TRUE(test["not_exists"] == nullptr);
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

TEST(ArraySimpleTests, EqualTest) {
    ccArray::Array test1;
    ccArray::Array test2;

    ASSERT_TRUE(test1 == test2);

    test1["key"] = "value";
    test2["key"] = "value";
    test1["assoc"]["test"] = "1";
    test2["assoc"]["test"] = "1";
    test1["list"][""] = "1";
    test2["list"][""] = "1";
    ASSERT_TRUE(test1 == test2);

    test2["list"][""] = "2";
    ASSERT_TRUE(test1 != test2);

    test2["list"]["asoc"] = "2";
    ASSERT_TRUE(test1 != test2);

    test2.unset("list");
    test2["list"][""] = "1";
    ASSERT_TRUE(test1 == test2);
}

TEST(ArraySimpleTests, ArrayToString) {
    ccArray::Array test;
    ASSERT_EQ("NULL", test.toString());
    test["Value"] = "value";
    ASSERT_EQ("value", test["Value"].toString());

    test["assoc"]["key"] = "value";
    ASSERT_EQ("Array", test["assoc"].toString());

    test["list"][""] = "value";
    ASSERT_EQ("Array", test["list"].toString());

}

TEST(ArraySimpleTests, functionTest) {
    ccArray::Array test;
    test = setArrayKeyValue(test, "key", "value");

    ASSERT_EQ(std::string("value"), (std::string)test["key"]) << "Get simple value from array";
}

    int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}