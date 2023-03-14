#!/bin/bash
cd build
make
./unit_tests
./main c
