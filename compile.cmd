@echo off
cmake --preset msvc
cmake --build build --config Release

set DIR=build\Release
md "%DIR%\bin" 2>nul
md "deps" 2>nul

windeployqt "%DIR%\OurTube.exe" --release --no-system-d3d-compiler --no-system-dxc-compiler --no-compiler-runtime --no-opengl-sw --no-translations --no-network --no-svg
rd /s /q "%DIR%\imageformats"

IF NOT EXIST "deps\yt-dlp.exe" (
    echo Downloading yt-dlp...
    curl -L "https://github.com/yt-dlp/yt-dlp/releases/download/2025.11.12/yt-dlp.exe" -o "deps\yt-dlp.exe"
)

IF NOT EXIST "deps\ffmpeg.7z" (
    echo Downloading ffmpeg...
    curl -L "https://www.gyan.dev/ffmpeg/builds/ffmpeg-git-essentials.7z" -o "deps\ffmpeg.7z"
    7z x "deps\ffmpeg.7z" -o"deps\ffmpeg" -y
    for /d %%D in ("deps\ffmpeg\*") do (
        move /Y "%%D\bin\ffmpeg.exe" "deps"
        move /Y "%%D\bin\ffprobe.exe" "deps"
        rd /s /q "deps\ffmpeg"
        goto :EndLoop
    )
)

:EndLoop
for %%F in (yt-dlp ffmpeg ffprobe) do (
    copy /Y "deps\%%F.exe" "%DIR%\bin"
)
