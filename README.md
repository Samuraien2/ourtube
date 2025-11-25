# OurTube

Youtube Video Downloader using yt-dlp, ffmpeg and Qt6.
Currently in-progress but should work somewhat.

## Downloads

Use the packaged release

## Build Instructions

### Windows

Prerequisites:
- [7zip](https://www.7-zip.org/)
- [Qt6](https://www.qt.io/download-qt-installer-oss)
- [CMake](https://cmake.org/download/)
- mingw64

```sh
$ cmake -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
# or add Qt6 cmake path
$ cmake -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="C:\Qt\6.10.1\mingw_64\lib\cmake"
$ cmake --build build
```