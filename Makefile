ifeq ($(OS),Windows_NT)
QT_CMAKE_PATH := C:\Qt\6.10.1\mingw_64\lib\cmake
endif

ifneq ($(QT_CMAKE_PATH),)
CMAKE_PREFIX_PATH = -DCMAKE_PREFIX_PATH=$(QT_CMAKE_PATH)
endif

all:
	cmake -B build -DCMAKE_BUILD_TYPE=Release $(QT_CMAKE_PATH)
	cmake --build build

r:
	build/OurTube
# deploy-win/OurTube.exe

clean:
	rm -rf build

win:
	deploy-win.cmd
