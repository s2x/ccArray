#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
class Node {
private:
	std::string value;
	std::string name;
	std::vector<Node *> childs;
	bool isset;
	bool is_array;
	bool has_valid_childs;
	int last_key_id;
	Node *parent;
	void setParent(Node *parent) {
		this->parent = parent;
	}

public:
	static const int TYPE_NOT_SET = 0;
	static const int TYPE_VALUE = 1;
	static const int TYPE_ARRAY = 2;
	static const int TYPE_LIST = 3;

	static int string2int(std::string value) {
		int tmp;
		std::istringstream(value) >> tmp;
		return tmp;
	}

	/**
	 * Return name o this node
	 */
	std::string getName() {
		return this->name;
	}

	/**
	 * Return value of this node as string
	 * If array or list return "ARRAY"
	 * see toString function
	 */
	std::string getValue() {
		return this->toString();
	}

	static std::string int2string(int value, std::string format = "%d") {
		char buffer[50];
		sprintf(buffer, format.c_str(), value);
		return buffer;
	}

	Node() {
		this->isset = false;
		this->last_key_id = 0;
		this->is_array = false;
		this->parent = NULL;
		this->has_valid_childs = false;
	}
	Node(std::string name) {
		this->name = name;
		this->isset = false;
		this->last_key_id = 0;
		this->is_array = false;
		this->parent = NULL;
		this->has_valid_childs = false;
	}

	/**
	 * Destructor
	 */
	~Node() {
		//delete all chidrens
		for (std::vector<Node *>::iterator it = childs.begin();
				it != childs.end(); ++it) {
			delete (*it);
		}
	}

	/**
	 * unset one child
	 */
	void unset(std::string key) {
		//find key and delete
		for (std::vector<Node *>::iterator it = childs.begin();
				it != childs.end();) {
			if ((*it)->getName() == key) {
				it = childs.erase(it);
			} else {
				it++;
			}
		}
	}

	/**
	 * Retrun all childrens
	 */
	std::vector<Node *> getChildrens() {
		return this->childs;
	}

	/**
	 * Get parent node
	 * Return null if root
	 */
	Node *getParent() {
		return this->parent;

	}

	/**
	 * Get node type
	 */
	int getType() const {
		if (this->childs.size() > 0 && this->has_valid_childs) {
			if (this->is_array)
				return TYPE_ARRAY;
			return TYPE_LIST;
		}
		if (this->isset)
			return TYPE_VALUE;
		return TYPE_NOT_SET;
	}

	/**
	 * != operator overload
	 */
	bool operator!=(Node &b) {
		return (*this == b) ? false : true;
	}

	/**
	 * == operator overload
	 */
	bool operator==(Node &b) {
		//test if type is equal
		if (this->getType() != b.getType())
			return false;

		switch (this->getType()) {
		case TYPE_NOT_SET:
			return true;
			break;
		case TYPE_VALUE:
			//test only the value
			return (this->value == b.value) ? true : false;
			break;
		case TYPE_ARRAY:
		case TYPE_LIST:
			// check if size is the same
			if (this->childs.size() != b.childs.size()) {
				return false;
			}

			//test childs if equal
			for (std::vector<Node *>::iterator it = childs.begin();
					it != childs.end(); it++) {

				//check if key exists
				if (!b[(*it)->getName()]) {
					return false;
				}

				//check if nodes are equal, recurency
				if ((b[(*it)->getName()] != (**it)))
					return false;
			}

			return true;
			break;
		}
		return false;
	}

	/**
	 * Return as string
	 *
	 */
	std::string toString() const {
		switch (this->getType()) {
		case TYPE_NOT_SET:
			return "NULL";
			break;
		case TYPE_VALUE:
			return this->value;
			break;
		case TYPE_ARRAY:
			return "Array";
			break;
		case TYPE_LIST:
			return "Array";
			break;
		}
		return "";
	}

	/**
	 * check if node has valid childrens
	 */
	bool hasChildrens() {
		return this->has_valid_childs;
	}

	/**
	 * Value assign
	 */
	Node& operator=(std::string value) {
		//cleanup some data
		this->isset = true;
		this->childs.clear();
		this->is_array = false;
		this->has_valid_childs = false;
		this->value = value;

		//update parent nodes
		Node *tmp = this->parent;
		while (tmp) {
			tmp->isset=true;
			if (tmp->childs.size() > 0) {
				tmp->has_valid_childs = true;
			}
			tmp = tmp->getParent();
		}
		return *this;
	}

	/**
	 * Append node
	 */
	Node& append() {
		Node *tmp = new Node(Node::int2string(last_key_id));
		this->childs.push_back(tmp);
		this->last_key_id++;
		return *tmp;
	}

	Node& operator[](std::string key) {
		for (std::vector<Node *>::iterator it = this->childs.begin();
				it != this->childs.end(); ++it) {
			if ((*it)->name == key) {
				return *(*it);
			}
		}
		Node *tmp = NULL;

		if (key == "" || key == Node::int2string(Node::string2int(key))) {
			if (key == "")
				key = Node::int2string(this->last_key_id);
			tmp = new Node(key);
			if (Node::string2int(key) >= this->last_key_id)
				this->last_key_id = Node::string2int(key) + 1;
		} else {
			//this is not list, this is map!
			// this->is_array = true;
			tmp = new Node(key);
		}

		tmp->setParent(this);
		this->childs.push_back(tmp);
		return *tmp;
	}

	operator std::string() const {
		return this->toString();
	}

	friend std::ostream& operator<<(std::ostream& os, const Node& dt) {
		os << dt.toString();
		return os;
	}

	operator void*() {
		if (isset == true)
			return this;
		//to do cleanup search path
		Node *tmp = this;
		while (tmp->parent && tmp->parent->has_valid_childs == false) {
			tmp = tmp->parent;
		}
		//std::cout<<tmp->parent->getName()<<std::endl;
		tmp->parent->unset(tmp->getName());

		return 0;
		//return isset==true ? this : 0;
	}

	void print();
};

void Node::print() {
	std::cout << "Node::" << this->name << ": " << this->toString()
			<<", Type: " <<this->getType()<<std::endl;
}

void node_get_leafs(Node *root, std::vector<Node *> *leafs) {

	if (root->hasChildrens()) {
		std::vector<Node *> tmp = root->getChildrens();
		for (std::vector<Node *>::iterator it = tmp.begin(); it != tmp.end();
				++it) {

			node_get_leafs((*it), leafs);
		}

	} else {

		leafs->push_back(root);
	}
}

std::string build_http_query(Node *root) {
	std::vector<Node *> leafs;

	node_get_leafs(root, &leafs);
	std::string query = "";

	for (std::vector<Node *>::iterator it = leafs.begin(); it != leafs.end();
			++it) {
		std::string name = "";
		std::string last_name = (*it)->getName();
		Node *parent = (*it);
		while (parent->getParent()->getParent()) {
			name = "[" + parent->getName() + "]" + name;
			last_name = parent->getName();
			parent = parent->getParent();
		}
		query += parent->getName() + name + "=" + (*it)->getValue();

		if ((it + 1) != leafs.end())
			query += "&";
	}
	return query;
}

int main(void) {

	Node test;
	test["id"] = "1";
	test["title"] = "test titile";
	test["book"]["1"]["name"] = "1";
	test["book"]["1"]["author"] = "John Smith";

	//autoinc
	test["autoinc"][""] = "0";
	test["autoinc"][""] = "1";
	test["autoinc"][""] = "2";
	test["autoinc"][""] = "3";
	test["autoinc"]["8"] = "8";
	test["autoinc"]["abc"] = "abc";
	test["autoinc"][""] = "9";

	Node test1, test2;
	test1["id"] = "test2";
	test1["name"] = "test2";
	test1["name"]["bla"] = "test2";
	test2["id"] = "test2";
	test2["name"] = "test2";
	test2["name"]["bla"] = "test2";

	if (test1 == test2) {
		std::cout << "Test operator == true" << std::endl;
	} else {
		std::cout << "Test operator == false" << std::endl;
	}

	//testing if exists
	if (test["check"]["if"]["exists"]) {
		std::cout << "Check fail\n";
	} else {
		std::cout << "Check ok\n";
	}

	std::vector<Node *> leafs;
	node_get_leafs(&test, &leafs);
	for (std::vector<Node *>::iterator it = leafs.begin(); it != leafs.end();
			++it) {
		Node *parent = (*it);
		std::string name = "";
		while (parent->getParent()) {
			name = parent->getName() + name;
			parent = parent->getParent();
			if (parent->getParent())
				name = "." + name;
		}
		std::cout << name << "=" << (*it)->getValue() << std::endl;
	}

}
