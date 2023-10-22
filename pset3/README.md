# CS50 Problem Set 3

## Installation

Install Java

```sh
brew install java

sudo ln -sfn /opt/homebrew/opt/openjdk/libexec/openjdk.jdk \
     /Library/Java/JavaVirtualMachines/openjdk.jdk
```

[https://github.com/cs50/spl/](https://github.com/cs50/spl/)

```sh
export CLASSPATH=/usr/local/lib/spl.jar
```

## Building

Each of the directories `breakout` and `find` are for a separate problem.

```sh
# Make breakout
cd breakout
make

# Make find
cd find
make
```

## Running

```sh
# Don't forget to export CLASSPATH
cd breakout
export CLASSPATH=/usr/local/lib/spl.jar
./breakout

# Example: this generates 1000 pseudorandom numbers then searches them for 42
cd find
./generate 1000 | ./find 42
```
