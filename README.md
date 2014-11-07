ccArray
=======

Is a simple C++ class than behave like PHP array. Its made for manipulating strings, so values like integers or float have to be converted to string.  
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
