#!/bin/sh

gcc -g -o game main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wpedantic
