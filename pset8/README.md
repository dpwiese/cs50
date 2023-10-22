# CS50 Problem Set 8

Add marker walkthrough

```php
// place is an object returned by search.php
// json array of objects
// place is one of the items in this array
// everything in google map API is represented as an object
// within that object we need a map
// glbal variable map
// new? or markerwithlabel? is a function takes an object and returns a new object
// MarkerWithLabel is a function that takes one argument, which happens to be an object
// object delimited by curly braces
// options of interest: label content: text label should take, position, map is reference to map you want to add it to
// position is a google maps lat and lon which google has as an object
// new google.maps.LatLng whcih takes lat and lon, which we can get from place object

// three things that need to happen
// 1) click marker -> show box
//      - when we click on marker, respond google.maps.event.addListener(marker,eventwearelisteningfor: "click")
//      - whenever marker is clicked, run this function:
//      - function(){
//            // inside here get data from server AJAX showinfobox inside scripts.js
//     
//
//                  }
//      - in JS objects have events which when happens event binding, calls a function
//      - in JS functions can be treated as and passed along as variables
// 2)
// 3)
```

Remove marker walkthrough

```php
// not actually destroying marker, but just attaching it to an imaginary map
// to delete all of the markers store all markers in global array looping through setting each one to null
```


```php
// get places matching query (asynchronously)
var content = {
    geo: 'Cambridge'
    // place.place_name
};

$.getJSON("artcles.php", content)
.done(function(data, textStatus, jqXHR) {

    // call typeahead's callback with search results (i.e., places)
    cb(data);
})
.fail(function(jqXHR, textStatus, errorThrown) {

    // log error to browser's console
    console.log(errorThrown.toString());
});
```
