#!/bin/bash

error() {
	msg="$1"
	echo -e "\e[31m$msg\e[0m"
}

commit() {
	msg="$1"
	echo "ADD"
	git add .
	echo "COMMIT"
	git commit -m "$msg"
	echo "PUSH"
	git push
}

#------------------------------------------------------------------------ end of Libs

EXECUTABLE="./bin/app"
SRC="./src/*.cpp"
INCLUDE="./include/"
LIB="./lib/"
FLAGS="-lsfml-graphics -lsfml-window -lsfml-system -ltbb"

run() {
	if [ ! -f "$EXECUTABLE" ]; then
		error "Error: $EXECUTABLE not found."
		return
	fi
	$EXECUTABLE
}

clean() {
	rm ./*.o
	if [ ! -f "$EXECUTABLE" ]; then
		return
	fi
	rm $EXECUTABLE
}

build() {
	g++ -c src/main.cpp src/shader.cpp -I./include
	g++ main.o shader.o -o ./bin/app -L./lib -Wl,-rpath=./lib -lsfml-graphics -lsfml-window -lsfml-system
	rm ./*.o
}

init() {
	find "./" -mindepth 1 ! -name "manager.sh" -exec rm -rf {} +
	mkdir bin
	mkdir src
	mkdir include
	mkdir lib
	touch src/main.cpp
	echo "#include<iostream>" > src/main.cpp
	echo 'int main() {std::cout<<"hola :)";}' >> src/main.cpp
	git init
	git branch -M main
	git add .
	git commit -m "first :)"
}

main() {
	for callback in "$@"; do
		if declare -f "$callback" > /dev/null; then
			"$callback"
		else
			error "Error: Function '$callback' not found."
		fi
	done
}

main "$@"
