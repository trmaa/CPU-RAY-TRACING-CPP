#!/bin/bash

if_file() {
	local file="$1"
	local callback=$2
	local error_callback=$3
	
	if [ -f "$file" ]; then 
		$callback
	elif [ -n "$error_callback" ]; then
		$error_callback
	fi
}

path="./bin/raytracer"

main() {
	clear
	if_file $path "rm $path"
	g++ -o $path ./src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system
	if_file $path $path "echo srry..."
}

main
