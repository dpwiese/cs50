# CS50 Fall 2014

https://cdn.cs50.net/2014/fall/

Download and install https://github.com/cs50/libcs50/

```sh
xcode-select -p
# /Applications/Xcode.app/Contents/Developer

sudo xcode-select --switch /Library/Developer/CommandLineTools

gcc --version
# gcc (GCC) 12.1.0
# Copyright (C) 2022 Free Software Foundation, Inc.
# This is free software; see the source for copying conditions.  There is NO
# warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

clang --version
# Apple clang version 14.0.3 (clang-1403.0.22.14.1)
# Target: arm64-apple-darwin22.5.0
# Thread model: posix
# InstalledDir: /Library/Developer/CommandLineTools/usr/bin
# dpwiese@Daniels-MacBook-Pro-2 pset1 %

which gcc
# /usr/local/bin/gcc

brew info gcc
# ==> gcc: stable 13.2.0 (bottled), HEAD
# GNU compiler collection
# https://gcc.gnu.org/
# /opt/homebrew/Cellar/gcc/13.2.0 (1,489 files, 383.0MB) *
#   Poured from bottle using the formulae.brew.sh API on 2023-09-15 at 05:55:26
# From: https://github.com/Homebrew/homebrew-core/blob/HEAD/Formula/g/gcc.rb
# License: GPL-3.0-or-later with GCC-exception-3.1
# ==> Dependencies
# Required: gmp ✔, isl ✔, libmpc ✔, mpfr ✔, zstd ✔
# ==> Options
# --HEAD
#   Install HEAD version
# ==> Analytics
# install: 121,344 (30 days), 289,367 (90 days), 568,291 (365 days)
# install-on-request: 59,263 (30 days), 141,386 (90 days), 285,472 (365 days)
# build-error: 88 (30 days)

# If you WANT to make symbolic link you can
ln -s gcc-13 gcc
ln -s /usr/local/bin/gcc gcc-12

# Or create alias in ~/.zshrc (or corresponding file, depending on shell)
alias gcc='/opt/homebrew/bin/gcc-13'
alias gcc-12='/usr/local/bin/gcc'

# But rather just compile with gcc-13
gcc-13 -o credit credit.c

# LibCS50 installed to /usr/local
/usr/local/include/cs50.h
/usr/local/src/cs50.c

# Need to add the following to .zshrc to find LibCS50
export C_INCLUDE_PATH=/usr/local/include
```
