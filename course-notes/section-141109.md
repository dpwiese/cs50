# CS50 Section 09-November-2014

* Javascript - run client side vs php which is run server side
* For some things its a lot faster than php
* Input form validation
* Some downsides is that it is less secure
* Proprietary stuff should never go in javascript
* Validations should be done on both client side AND server side
* JS should be there to help the user not relying on JS

```html
<script type="text/javascript" src="hello.js">
</script>
```

* Variables prefaced with var keyword when its defined (loosely typed)

```html
<script>
    var s = "CS50";
    var n =3.14;
    var b = true;

    alert("Type of b: " + typeof(b));
    b = "make b a string";
</script>
```

* Variables can change type as you use them
* Objects in JS are like associative arrays in php
* Objects and arrays can be nested inside of each other
* DOM: document object model
* People dont often use native javascript
* Instead use libraries such as jquery, markdown, typehead
* These are add-ons
* User validation for CS50 finance using jquery syntax
* jquery uses the same set of selectors as CSS does
* Change is a jquery event handler
* `$` sign says here is some jquery stuff
* `$` its a selector

```html
<script>
    $( "#confirmation" ).css("background-color", "red");

    $( "#confirmation" ).change(function()
    {
        if( $( "#confirmation input").val() != $( "password input").val() );
        {
            // alert("not equal");
            $( "#confirmation" ).addClass("has-error"); //outlines the wrong box in red using bootstrap
            $( "#confirmation" ).removeClass("has-success");
        }
        else
        {
            $( "#confirmation" ).removeClass("has-error");
            $( "#confirmation" ).addClass("has-success")
        }
    })
</script>
```

* Hover event handler
* hover takes two input arguments

```html
<script>
    $( "tbody tr" ).hover(function()
    {
        $(this).css("background-clor", "red");
    },
    function()
    {
        $(this).css("background-color","");
    });
</script>
```

* focus event handler, when object gets focus, eg click on it
* JSON machine readable way of transmitting text file
