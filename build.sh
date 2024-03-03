#!/bin/bash

set -xe

cc -Wall -Werror -Wextra -std=c2x -pedantic -ggdb -o collatz collatz.c