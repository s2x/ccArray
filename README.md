ccArray
=======

Is a simple C++ class than behave like PHP array. Its made for manipulating strings, so values like integers or float have to be converted to string. Remember that this class is still in very early alpha, so it can be broken in some parts.

# Some examples of usage
here you will find some examples of usage.
## Basic assoc array

This is a very simple assoc array, no multidimension array yet. 

```cpp
Node test;
test["id"] = "1";
test["title"] = "test titile";  
```
output:
```
id=1
title=test titile
```
## Multidimension array

```cpp
Node test;
test["book"]["1"]["name"] = "1";
test["book"]["1"]["author"] = "John Smith";  
```
output:
```
book.1.name=1
book.1.author=John Smith
```
## Autoincrement of array

```cpp
Node test;
test["autoinc"][""] = "0";
test["autoinc"][""] = "1";
test["autoinc"][""] = "2";
test["autoinc"][""] = "3";
```
output:
```
autoinc.0=0
autoinc.1=1
autoinc.2=2
autoinc.3=3
```

## Checking if node exists
```
//as simple as this
if (test["check"]["if"]["exisits"]) {
  //some code here
}
```

# What not working

 - Comparinsion - you cant do like this
```
Node test;
test["id1"] = "1";
test["id2"] = "2";
if (test["id1"] == test["id2"]) {
  //this wont work
}
```
 - Cloning/coping
```
Node test1;
Node test2;
test1["1"] = "1";
//this wont work
test2 = test1
```
