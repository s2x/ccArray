//
// Created by piotr on 02.11.16.
//

#include "Array.h"
namespace ccArray {

    const int Array::TYPE_NOT_SET = 0;
    const int Array::TYPE_VALUE = 1;
    const int Array::TYPE_ARRAY = 2;
    const int Array::TYPE_LIST = 3;

    std::string Array::getName() {
        return this->name;
    }

    std::string Array::getValue() {
        return this->toString();
    }

    Array::Array() : name("") {
        this->isset = false;
        this->last_key_id = 0;
        this->is_array = false;
        this->parent = NULL;
        this->has_valid_childs = false;
    }

    Array::Array(std::string name) : name(name) {
        this->isset = false;
        this->last_key_id = 0;
        this->is_array = false;
        this->parent = NULL;
        this->has_valid_childs = false;
    }

    Array::Array(Array &b) : name(b.name), value(b.value) {
        this->isset = b.isset;
        this->last_key_id = b.last_key_id;
        this->parent = NULL;

        //clear childs
        this->childs.clear();

        //copy all childs
        for (auto it : b.childs) {
            Array *tmp = new Array(*it);
            tmp->setParent(this);
            this->childs.push_back(tmp);
        }
        this->has_valid_childs = b.has_valid_childs;
        this->is_array = b.is_array;

    }

    Array::~Array() {
        //delete all childrens
        for (auto it: this->childs) {
            delete (it);
        }
    }

    void Array::unset(std::string key) {
        //find key and delete
        for (auto it = childs.begin(); it != childs.end();) {
            if ((*it)->getName() == key) {
                childs.erase(it);
                return;
            } else {
                it++;
            }
        }
    }

    std::vector<Array *> Array::getChildrens() {
        return this->childs;
    }

    Array *Array::getParent() {
        return this->parent;
    }

    int Array::getType() const {
        if (this->childs.size() > 0 && this->has_valid_childs) {
            if (this->is_array)
                return TYPE_ARRAY;
            return TYPE_LIST;
        }
        if (this->isset)
            return TYPE_VALUE;
        return TYPE_NOT_SET;
    }

    bool Array::operator!=(Array &b) {
        return !(*this == b);
    }

    bool Array::operator==(Array &b) {
        //test if type is equal
        if (this->getType() != b.getType())
            return false;

        switch (this->getType()) {
            case TYPE_NOT_SET:
                return true;
            case TYPE_VALUE:
                //test only the value
                return this->value == b.value;
            case TYPE_ARRAY:
            case TYPE_LIST:
                // check if size is the same
                if (this->childs.size() != b.childs.size()) {
                    return false;
                }

                //test childs if equal
                for (auto it : childs) {

                    //check if key exists
                    if (!b[it->getName()]) {
                        return false;
                    }

                    //check if nodes are equal, recurency
                    if ((b[it->getName()] != (*it)))
                        return false;
                }
                return true;
            default:
                return false;
        }
    }


    Array &Array::operator=(std::string value) {
        //cleanup some data
        this->isset = true;
        this->childs.clear();
        this->is_array = false;
        this->has_valid_childs = false;
        this->value = value;

        //update parent nodes
        Array *tmp = this->parent;
        while (tmp) {
            tmp->isset = true;
            if (tmp->childs.size() > 0) {
                tmp->has_valid_childs = true;
            }
            tmp = tmp->getParent();
        }
        return *this;
    }

    std::string Array::toString() const {
        switch (this->getType()) {
            case TYPE_NOT_SET:
                return "NULL";
            case TYPE_VALUE:
                return this->value;
            case TYPE_ARRAY:
                return "Array";
            case TYPE_LIST:
                return "Array";
            default:
                return "";
        }
    }

    bool Array::hasChildrens() {
        return this->has_valid_childs;
    }

    Array &Array::operator[](std::string key) {
        for (auto it: childs) {
            if (it->name == key) {
                return (*it);
            }
        }

        key = (key == "") ? std::to_string(this->last_key_id) : key;

        if (this->keyIsInt(key) && std::stoi(key) >= this->last_key_id) {
            this->last_key_id = std::stoi(key) + 1;
        } else {
            this->is_array = true;
        }

        Array *tmp = new Array(key);
        tmp->setParent(this);
        this->childs.push_back(tmp);
        return *tmp;
    }

    Array::operator std::string() const {
        return this->toString();
    }

    std::ostream &operator<<(std::ostream &os, const Array &dt) {
        os << dt.toString();
        return os;
    }

    Array::operator void *() {
        if (this->isset) {
            return this;
        }

        //to do cleanup search path
//    Array *tmp = this;
//    while (tmp->parent && !tmp->parent->has_valid_childs) {
//        tmp = tmp->parent;
//    }
//    tmp->parent->unset(tmp->getName());

        return 0;
    }

    bool Array::keyIsInt(std::string key) {
        try {
            return (key == std::to_string(std::stoi(key)));
        } catch (...) {
            return false;
        }
    }

    void Array::setParent(Array *parent) {
        this->parent = parent;
    }

    Array &Array::operator=(Array &b) {
        //copy some settings
        this->isset = b.isset;
        this->last_key_id = b.last_key_id;
        this->is_array = b.is_array;
        this->has_valid_childs = b.has_valid_childs;
        this->name = b.name;
        this->value = b.value;

        //clear childs
        this->childs.clear();

        //copy all childs

        for (auto it : b.childs) {
            Array *tmp = new Array(*it);
            tmp->setParent(this);
            this->childs.push_back(tmp);
        }
        //force settings
        this->has_valid_childs = b.has_valid_childs;
        this->is_array = b.is_array;
        return *this;
    }

    Array &Array::operator=(const Array &b) {

        //copy some settings
        this->isset = b.isset;
        this->last_key_id = b.last_key_id;
        this->is_array = b.is_array;
        this->has_valid_childs = b.has_valid_childs;
        this->name = b.name;
        this->value = b.value;

        //clear childs
        this->childs.clear();

        //copy all childs

        for (auto it : b.childs) {
            Array *tmp = new Array(*it);
            tmp->setParent(this);
            this->childs.push_back(tmp);
        }
        //force settings
        this->has_valid_childs = b.has_valid_childs;
        this->is_array = b.is_array;
        return *this;
    }
}