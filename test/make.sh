#!/bin/sh
pushd ../ >> /dev/null
./make.sh
popd >> /dev/null
#cc main.c -Ilibmy/inc -Llibmy -lmy --debug -W -Werror --ansi --pedantic  -o a.out
cc main.c -I../inc -L../ -lmy -O3 -W -Werror --ansi --pedantic  -o a.out
