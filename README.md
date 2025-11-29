# OurTube

Youtube Video Downloader using yt-dlp, ffmpeg and Qt6.

# Build Instructions

## Windows

### Prerequisites
- [7zip](https://www.7-zip.org/)
- [Qt6 for MSVC](https://www.qt.io/download-qt-installer-oss)
- [Visual Studio 2026](https://visualstudio.microsoft.com/vs/community/)

### Instructions
1. Open Project with Visual Studio or x64 Native Tools Command Prompt (or any environment with CMake and Qt6 binaries)
2. Run `compile.cmd` (requires internet the first time to download dependencies)

## Linux

### Dependencies

#### For Arch and derivatives:
`sudo pacman -S --needed qt6-base yt-dlp ffmpeg cmake gcc`

#### For Void Linux:
`sudo xbps-install -S qt6-base qt6-base-devel yt-dlp ffmpeg cmake gcc`

### Instructions
Run `./nob`, the final executable will be placed in ./build/ourtube