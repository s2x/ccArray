//
// Created by piotr on 05.11.16.
//

#include "../../include/ccArray/ArrayHelper.h"
namespace ccArray {
    Array ArrayHelper::setByPath(Array array, std::vector<std::string> path, std::string value) {
        if (path.size() == 0) {

        } else if (path.size() == 1) {
            std::cout << "ok:" << path.size() << std::endl;
            array[path[0]] = value;
        } else {
            std::cout << "not ok:" << path.size() << std::endl;
            auto subPath = path;
            subPath.erase(subPath.begin(), subPath.begin() + 1);
            array[path[0]] = ArrayHelper::setByPath(array[path[0]], subPath, value);
        }
        return array;
    }
}