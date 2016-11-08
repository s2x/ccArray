//
// Created by piotr on 05.11.16.
//

#ifndef LIBCRAZYGOAT_ARRAYHELPER_H
#define LIBCRAZYGOAT_ARRAYHELPER_H

#include "Array.h"
#include <vector>

namespace ccArray {
    class ArrayHelper {
    public:
        static Array setByPath(Array array, std::vector<std::string> path, std::string value);
    };
}

#endif //LIBCRAZYGOAT_ARRAYHELPER_H
