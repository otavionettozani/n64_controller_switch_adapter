LIB_PATH = ./BBBIOlib/BBBio_lib/
SUBMODULE_PATH = ./BBBIOlib
COMPILED_FILE = ./dist/main

dependencies:
	cd ${SUBMODULE_PATH} && make

project: dependencies
	gcc main.c -o ${COMPILED_FILE} -L ${LIB_PATH} -lBBBio
