#!/bin/sh

mkdir -p obj
pushd obj >> /dev/null
rm -f *
echo "Compiling " ../src/*.c
cc -W -Werror -ansi -pedantic -I ../inc -c ../src/*.c
ar r ../libmy.a *.o
echo done
popd >> /dev/null
