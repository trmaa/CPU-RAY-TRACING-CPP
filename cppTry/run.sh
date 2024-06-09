if [ -f ./bin/local/launcher.exe ]; then
	./bin/local/launcher.exe
else
	./build.sh
fi
