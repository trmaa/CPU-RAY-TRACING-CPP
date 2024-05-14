#!/bin/bash

if [ -f ./bin/launcher.exe ]; then
	rm ./bin/launcher.exe
fi

g++ -o ./bin/launcher.exe ./src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system

./bin/launcher.exe
