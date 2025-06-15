#!/bin/bash
echo -e "-------------------------------------------------------------------------------\n"
echo -e "Compilation test\n"
cd src

make clean
make gcov_report
# cat valgrind.txt