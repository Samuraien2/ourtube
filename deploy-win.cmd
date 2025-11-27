@echo off

mkdir "deploy"
mkdir "deploy\ffmpeg"
copy "build\Release\ourtube.exe" "deploy\OurTube.exe"
windeployqt.exe "deploy\OurTube.exe" --release --no-system-d3d-compiler --no-system-dxc-compiler --no-opengl-sw --no-translations --no-network --no-svg

IF NOT EXIST "deploy\yt-dlp.exe" (
    curl -L "https://github.com/yt-dlp/yt-dlp/releases/download/2025.11.12/yt-dlp.exe" -o "deploy\yt-dlp.exe"
) ELSE (
    echo yt-dlp.exe already exists, skipping download.
)

IF NOT EXIST "deploy\ffmpeg\ffmpeg.exe" (
    curl -L "https://www.gyan.dev/ffmpeg/builds/ffmpeg-git-essentials.7z" -o "deploy\ffmpeg-temp.7z"
    7z x "deploy\ffmpeg-temp.7z" -o"deploy\ffmpeg-temp" -y
    for /d %%D in ("deploy\ffmpeg-temp\*") do (
        move /Y "%%D\bin\ffmpeg.exe" "deploy\ffmpeg"
        move /Y "%%D\bin\ffprobe.exe" "deploy\ffmpeg"
        rd /s /q "deploy\ffmpeg-temp"
        del /q "deploy\ffmpeg-temp.7z"
        pause
        exit /b 0
    )
) ELSE (
    echo ffmpeg.exe already exists, skipping download.
)
pause
