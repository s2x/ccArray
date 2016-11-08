//
// Created by piotr on 02.11.16.
//

#ifndef LIBCRAZYGOAT_ARRAY_H
#define LIBCRAZYGOAT_ARRAY_H


#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>

namespace ccArray {

    class Array {
    private:
        std::string value;
        std::string name;
        std::vector<Array *> childs;
        bool isset;
        bool is_array;
        bool has_valid_childs;
        int last_key_id;
        Array *parent;

        void setParent(Array *parent);

        bool keyIsInt(std::string key);

    public:
        static const int TYPE_NOT_SET;
        static const int TYPE_VALUE;
        static const int TYPE_ARRAY;
        static const int TYPE_LIST;

        /**
         * Constructors
         */
        Array();

        explicit Array(std::string name);

        Array(Array &b);

        /**
         * Destructor
         */
        ~Array();

        /**
         * Return name o this node
         */
        std::string getName();

        /**
         * Return value of this node as string
         * If array or list return "ARRAY"
         * see toString function
         */
        std::string getValue();

        /**
         * Retrun all childrens
         */
        std::vector<Array *> getChildrens();

        /**
         * Get parent node
         * Return null if root
         */
        Array *getParent();

        /**
         * Get node type
         */
        int getType() const;

        /**
         * != operator overload
         */
        bool operator!=(Array &b);

        /**
         * == operator overload
         */
        bool operator==(Array &b);

        /**
         * Value assign
         */
        Array &operator=(std::string value);

        Array &operator=(Array &b);

        Array &operator=(const Array &b);


        Array &operator[](std::string key);

        operator std::string() const;

        friend std::ostream &operator<<(std::ostream &os, const Array &dt);

        operator void *();

        /**
         * Return as string
         *
         */
        std::string toString() const;

        /**
         * unset one child
         */
        void unset(std::string key);

        /**
         * check if node has valid childrens
         */
        bool hasChildrens();
    };

}

#endif //LIBCRAZYGOAT_ARRAY_H
