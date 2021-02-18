#!/bin/sh
g++ $1 -lgtest -L. -I. -pthread -DLEAK_TEST
