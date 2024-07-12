#!/bin/bash

if_file() {
	path="$1"
	callback=$2

	if [ -f $path ]; then
		$callback
	fi
}

#paths
SOURCE="./src/*.cpp"
OUTPUT="./bin/asteroids"
FLAGS="-lsfml-graphics -lsfml-window -lsfml-system"
INCLUDE="./include/"
LIBS="./lib/"

clean() {
	if_file $OUTPUT "rm $OUTPUT"
}

build () {
	g++ $SOURCE -o $OUTPUT -I$LIBS -I$INCLUDE $FLAGS
}

run() {
	$OUTPUT
}

main() {
	$1
	$2
	$3
}

#callbacks ment to be clean, build or run
main $1 $2 $3
