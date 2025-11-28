@echo off

mkdir "deploy"
mkdir "deploy\bin"
copy "build\Release\ourtube.exe" "deploy\OurTube.exe"
windeployqt.exe "deploy\OurTube.exe" --release --no-system-d3d-compiler --no-system-dxc-compiler --no-opengl-sw --no-translations --no-network --no-svg
rd /s /q "deploy\imageformats"

IF NOT EXIST "deploy\bin\yt-dlp.exe" (
    curl -L "https://github.com/yt-dlp/yt-dlp/releases/download/2025.11.12/yt-dlp.exe" -o "deploy\bin\yt-dlp.exe"
) ELSE (
    echo yt-dlp.exe already exists, skipping download.
)

IF NOT EXIST "deploy\bin\ffmpeg.exe" (
    curl -L "https://www.gyan.dev/ffmpeg/builds/ffmpeg-git-essentials.7z" -o "deploy\ffmpeg-temp.7z"
    7z x "deploy\ffmpeg-temp.7z" -o"deploy\ffmpeg-temp" -y
    for /d %%D in ("deploy\ffmpeg-temp\*") do (
        move /Y "%%D\bin\ffmpeg.exe" "deploy\bin"
        move /Y "%%D\bin\ffprobe.exe" "deploy\bin"
        rd /s /q "deploy\ffmpeg-temp"
        del /q "deploy\ffmpeg-temp.7z"
        pause
        exit /b 0
    )
) ELSE (
    echo ffmpeg.exe already exists, skipping download.
)
pause
