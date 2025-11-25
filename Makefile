all:
	cmake -B build -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:\Qt\6.10.1\mingw_64\lib\cmake" -DCMAKE_BUILD_TYPE=Release
	cmake --build build

r:
	deploy-win/OurTube.exe

win:
	deploy-win.cmd