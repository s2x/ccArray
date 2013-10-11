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
    this->parent  = parent;
  }

public:
  static int string2int(std::string value) {
	  int tmp;
	  std::istringstream ( value ) >> tmp;
	  return tmp;
  }
  std::string getName() {
    return this->name;
  }

  std::string getValue() {
    return this->toString();
  }

  static std::string int2string(int value, std::string format="%d") {
	  char buffer [50];
	  sprintf (buffer, format.c_str() ,value);
	  return buffer;
  }
  static const int TYPE_NOT_SET = 0;
  static const int TYPE_VALUE = 1;
  static const int TYPE_ARRAY = 2;
  static const int TYPE_LIST = 3;

  Node() {this->isset = false; this->last_key_id = 0; this->is_array = false;this->parent = NULL; this->has_valid_childs = false;}
  Node(std::string name) {
    this->name = name;
    this->isset = false;
    this->last_key_id = 0;
    this->is_array = false;
    this->parent = NULL;
    this->has_valid_childs = false;
  }

  ~Node() {
	  for (std::vector<Node *>::iterator it = childs.begin() ; it != childs.end(); ++it) {
      delete (*it);
	  }
  }

  void unset(std::string key) {
	  for (std::vector<Node *>::iterator it = childs.begin() ; it != childs.end(); ++it) {
      if ((*it)->getName() == key)  {
         childs.erase(it);
      }
	  }
  }

  std::vector<Node *> getChildrens() {
    return this->childs;
  }

  Node *getParent() {
     return this->parent;

  }

  int getType() const{
    if (this->childs.size()>0 && this->has_valid_childs) {
      if (this->is_array) return TYPE_ARRAY;
      return TYPE_LIST;
    }
    if (this->isset) return TYPE_VALUE;
    return TYPE_NOT_SET;
  }

  std::string toString() const {
    switch (this->getType()) {
      case TYPE_NOT_SET: return "NULL"; break;
      case TYPE_VALUE: return this->value; break;
      case TYPE_ARRAY: return "Array"; break; 
      case TYPE_LIST: return "Array"; break; 
    }
    return "";
  }

  bool hasChildrens() {
    return this->has_valid_childs;
  }

  Node& operator= (std::string value) { 
    this->isset = true;
    this->childs.clear();
    this->is_array = false;
    this->has_valid_childs = false;
    this->value = value;

    if (this->parent) {
      if (this->parent->childs.size()>0) {
        this->parent->has_valid_childs = true;
      }
    }
    return *this;
  }

  Node& append() {
    Node *tmp = new Node(Node::int2string(last_key_id));
    this->childs.push_back(tmp);
    this->last_key_id++;
    return *tmp;
  }

  Node& operator[] (std::string key) { 
    for (std::vector<Node *>::iterator it = this->childs.begin() ; it != this->childs.end(); ++it) {
      if ((*it)->name == key) {
        return *(*it);
      }
    }
    if (key == Node::int2string(Node::string2int(key))) {
          this->last_key_id = Node::string2int(key)+1;
    } else {
      //this is not list, this is map!
     // this->is_array = true;
    }

    Node *tmp = new Node(key);
    tmp->setParent(this);
    this->childs.push_back(tmp);
    return *tmp;
  }

  operator std::string () const { 
    return this->toString();
  }

  friend std::ostream& operator<<(std::ostream& os, const Node& dt) {
      os<<dt.toString();
      return os;
  }

  operator void*() {
    if (isset==true) return this;
    //to do cleanup search path 
    Node *tmp = this;
    while (tmp->parent && tmp->parent->has_valid_childs == false) {
        tmp = this->parent;
    }
    this->parent->unset(tmp->getName());
    
    return 0;
    //return isset==true ? this : 0;
  }

  void print();
};

void Node::print()
{
  std::cout << "Node::"<<this->name<<": " << this->toString() << std::endl;
}

void node_get_leafs(Node *root, std::vector<Node *> *leafs) {

  if (root->hasChildrens()) {
    std::vector<Node *> tmp = root->getChildrens();
	  for (std::vector<Node *>::iterator it = tmp.begin() ; it != tmp.end(); ++it) {
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

  for (std::vector<Node *>::iterator it = leafs.begin() ; it != leafs.end(); ++it) {
    std::string name = "";
    std::string last_name = (*it)->getName();
    Node *parent = (*it)->getParent();
    while (parent->getParent()) {
      name = "["+parent->getName()+"]"+name;
      last_name = parent->getName();
      parent= parent->getParent();
    }  
    last_name += name;
    query += last_name+"="+(*it)->getValue();
    
    if ((it+1) != leafs.end()) query +="&";
  }
  return query;
}


int main(void)
{

  Node x;
  x["test"] = "123";
  x["test2"] = "234";
  x["test_array"]["test"] = "test";
   x["test_array"]["test2"]["test3"] = "test";
 std::vector<Node *> tmp = x.getChildrens();
	  for (std::vector<Node *>::iterator it = tmp.begin() ; it != tmp.end(); ++it) {
      std::cout<<"["<<(*it)->getName()<<"] = "<<(*it)->getValue()<<std::endl;
	  }

  std::cout<<build_http_query(&x)<<std::endl;

}
