# Quiz 1 Review

## Question 0

```c
s->id
```

equivalent to

```c
(*s).id
```

* Dereference the pointer gives us the struct, then dot to get at the field

## Question 1

d. 80

## Question 2

a.

* jquery is a library nice functions for us to use
* node.js is a library? a bunch of js that is standalone

## Question 3

CSS selector:

```
#id
.class
```

* Remember ids are unique on each page, class not unique

## Question 4 - 6

* F queue is data structure FIFO
* T stack is LIFO
* F at least 26 usually

## Question 5

* Document Object Model (DOM)

```html
<!DOCTYPE html>

<html>

    <head>
        <title>CS50<\title>
    </head>

    <body>
        <h1>CS50</h1>
        <h3>Under Construction</h3>
        <h6>Copyright 2012</h6>
    </body>

</html>
```

* Squares are tags, circles are actual text in DOM diagram

## Question 8

```c
// scanf gets input from the user, reverse of printf
scanf("%d", &n);
```

## Question 9

* What does `&n` mean? means "the address of n"
* We need to give `scanf` the address of n so it knows where to put the value that it gets from the user. its an empty box
* would be in scope of scanf and not in my scope

## Question 11

* `sscanf` scans from given line instead of user input
* `foo` will return 0
* point of c
* `sscanf` returns 1 if it matches 1 thing...

## Question 12

## Question 13

* it helps for troubleshooting, since 1 or -1 are common for errors, but that might be what someone entered

## Question 14

* name is the important field when using get an post

```php
if (empty($_POST["email"])) || empty() || empty())

// == vs ===
// == "massages" types
// === is a strict comparison

// []==false evaluates to true in php
// ""==false
```

```php
<?php

// check that all fields are not empty

if ($_POST["email"] === "" //this might not work. better to use empty()
{
    echo("failure");
}
// check that password and confirmation are the same
else if ( $_POST["password"] != $_POST["confirmation"])
{
    echo("failure");
}
else
{

}

?>
```

## Question 15: CLIENT SIDE VALIDATION USING JQUERY

* in JS use id to get something from form
* jquery select DOM elements.. `$` sign special jquery symbol
* do select element with id of email do `"#email"`
* for all practical purposes in JS single and double quotes are equivalent

```
if($("#email").val() == "" )

if($("#email").val() == $("#confirmation").val())
```

* also replace echo failures with return false and success with return true

## Question 16: Buffer Overflow

* buffer is like a small array that temporarily holds some data
* like when doing stuff with linked lists
* buffer overflow, allocated some temp mem on stack
* and write beyond buffer

## Question 18

* when `foo` is called, the address of the code what was called in main is stored in stack (return address)
* so adversary can change return address

## Question 19

```c
typdef struct node {

}
```

* node; <- typdefing the whole thing called node
* normally first node is not necessary but
* can do:

```c
struct node {

}
```

* but then every time we refer to it as: struct node.

* insert: O(n) because at worst we have to check every element in the list to get to the end, if the number we are inserting is big
* delete: Omega(1) if the first element we want to delete is first element in list

## Question 21

## Question 22: Doubly Linked List

* struct node* prev;

## Question 23: skip in section, but look over!

## Question 24: tried to write data into location we don't actually own. eg malloced memory and then overstep amount we allocate

## Question 25: didnt free 40 bytes. malloced 40 bytes then threw away pointer without freeing

## Question 26:

## Question 27: Incorrect

* no control flow/conditions.. doesnt just go top to bottom

## Question 28: Not Relevant

## Question 29: Lossless compression

* jpeg is lossy... will compress every time its saved

## Question 30: Not important?

## Question 31:
