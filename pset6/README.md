# CS50 Problem Set 6

## Installing

Make sure you have PHP installed.

```sh
brew install php
php -v
```

## Building

Comment out `#define _XOPEN_SOURCE 700` in `server.c` and don't use `-Werror` when compiling on OSX, seems to have to do with not having `glibc` on OSX.

```sh
make
```

## Running

```sh
./server -p 1234 /Users/dpwiese/code/dpwiese/cs50/pset6/public
```

* Navigate to [http://localhost:1234/hello.html](http://localhost:1234/hello.html)
* Navigate to [http://localhost:1234/cat.html](http://localhost:1234/cat.html)
