#!/bin/bash

number="$1"

if [ ! -f "./bin/scenes/scene$number.json" ]; then
    echo "There is no scene $number"
    exit 1
fi

cp "./bin/scenes/scene$number.json" ./bin/scene.json
echo "Scene changed to $number"
