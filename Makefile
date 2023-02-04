# First variables
PROJECT_NAME = als-basic-utilities
BUILD_DIR = /tmp/build_tmp/${PROJECT_NAME}
INCLUDE_DIR = /usr/include/${PROJECT_NAME}
LIB_DIR = /usr/lib
BIN_DIR = /usr/bin
CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -fPIC -O3 -pthread
LIBRARY_DEPENDENCIES = 

all: ${BUILD_DIR}/libals-basic-utilities.so

${BUILD_DIR}/libals-basic-utilities.so: ${BUILD_DIR}/FormatNumber.o\
		${BUILD_DIR}/ToString.o
	${CXX} -shared ${CXXFLAGS} ${LIBRARY_DEPENDENCIES} -o ${BUILD_DIR}/libals-basic-utilities.so\
		${BUILD_DIR}/FormatNumber.o\
		${BUILD_DIR}/ToString.o

install:
	mkdir -p ${INCLUDE_DIR}
	cp FileOperations.hpp ${INCLUDE_DIR}/FileOperations.hpp
	cp -T ToString.hpp ${INCLUDE_DIR}/ToString.hpp
	cp -T FormatNumber.hpp ${INCLUDE_DIR}/FormatNumber.hpp
	install -T ${BUILD_DIR}/libals-basic-utilities.so ${LIB_DIR}/libals-basic-utilities.so
	rm -r ${BUILD_DIR}


${BUILD_DIR}/%.o: %.cpp %.hpp
	mkdir -p $(@D)
	${CXX} ${CXXFLAGS} -o $@ -c $<
    
