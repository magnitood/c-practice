#!/bin/bash

set -xe

CFLAGS="-Wall -Wextra `pkg-config --cflags raylib`"
LDFLAGS="`pkg-config --libs raylib`"
gcc main.c -o main $CFLAGS $LDFLAGS
