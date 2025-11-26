# OurTube

Youtube Video Downloader using yt-dlp, ffmpeg and Qt6.

# Build Instructions

## Windows

### Prerequisites
- [7zip](https://www.7-zip.org/)
- [Qt6](https://www.qt.io/download-qt-installer-oss)
- [CMake](https://cmake.org/download/)
- mingw_64

### Instructions

Compile the project.
```sh
$ make
```
or, if CMake can't find your Qt6 cmake path, specify it using QT_CMAKE_PATH
```sh
$ make QT_CMAKE_PATH=C:\Qt\6.10.1\mingw_64\lib\cmake
```

Bundle it together with Qt6 libs, ffmpeg and yt-dlp.
```console
$ .\deploy-win.cmd
```

## Arch Linux

### Prerequisites
```sh
$ sudo pacman -S --needed qt6-base yt-dlp ffmpeg
```

### Instructions
```sh
$ make
```
