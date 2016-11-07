//
// Created by piotr on 07.11.16.
//

#include "../src/Array.h"

int main (int argc, char *argv[])
{
    ccArray::Array simpleArray;

    simpleArray["Hello"] = "World!";

    std::cout<<"Hello "<<simpleArray["Hello"]<<std::endl;

    return 0;
}