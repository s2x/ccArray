#include "ccArray.h"

using namespace cc_array;

void node_get_leafs(ccArray *root, std::vector<ccArray *> *leafs) {

	if (root->hasChildrens()) {
		std::vector<ccArray *> tmp = root->getChildrens();
		for (std::vector<ccArray *>::iterator it = tmp.begin(); it != tmp.end();
				++it) {

			node_get_leafs((*it), leafs);
		}

	} else {

		leafs->push_back(root);
	}
}

std::string build_http_query(ccArray *root) {
	std::vector<ccArray *> leafs;

	node_get_leafs(root, &leafs);
	std::string query = "";

	for (std::vector<ccArray *>::iterator it = leafs.begin(); it != leafs.end();
			++it) {
		std::string name = "";
		std::string last_name = (*it)->getName();
		ccArray *parent = (*it);
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

	ccArray test;
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

	ccArray test1;
	test1["1"]["Name"] = "2";
	test1["2"]["Name"] = "2";
	ccArray test2 = test1;


	if (test1["1"] == test1["2"]) {
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

	std::vector<ccArray *> leafs;
	node_get_leafs(&test1, &leafs);
	for (std::vector<ccArray *>::iterator it = leafs.begin(); it != leafs.end();
			++it) {
		ccArray *parent = (*it);
		std::string name = "";
		while (parent->getParent()) {
			name = parent->getName() + name;
			parent = parent->getParent();
			if (parent->getParent())
				name = "." + name;
		}
		std::cout << name << "=" << (*it)->getValue() << std::endl;
	}

	std::cout<<"Using copy!"<<std::endl;
	leafs.clear();
	node_get_leafs(&test2, &leafs);
	for (std::vector<ccArray *>::iterator it = leafs.begin(); it != leafs.end();
			++it) {
		ccArray *parent = (*it);
		std::string name = "";
		while (parent->getParent()) {
			name = parent->getName() + name;
			parent = parent->getParent();
			if (parent->getParent())
				name = "." + name;
		}
		std::cout << name << "=" << (*it)->getValue() << std::endl;
	}
	return 0;
}

