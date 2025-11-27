@echo off

mkdir "deploy-win"
mkdir "deploy-win\ffmpeg"
copy "build\Release\OurTube.exe" "deploy-win"
windeployqt.exe --no-system-d3d-compiler --no-system-dxc-compiler --no-opengl-sw --release --no-translations "deploy-win\OurTube.exe"

IF NOT EXIST "deploy-win\yt-dlp.exe" (
    curl -L "https://github.com/yt-dlp/yt-dlp/releases/download/2025.11.12/yt-dlp.exe" -o "deploy-win\yt-dlp.exe"
) ELSE (
    echo yt-dlp.exe already exists, skipping download.
)

IF NOT EXIST "deploy-win\ffmpeg\ffmpeg.exe" (
    curl -L "https://www.gyan.dev/ffmpeg/builds/ffmpeg-git-essentials.7z" -o "deploy-win\ffmpeg-temp.7z"
    7z x "deploy-win\ffmpeg-temp.7z" -o"deploy-win\ffmpeg-temp" -y
    for /d %%D in ("deploy-win\ffmpeg-temp\*") do (
        echo Moving ffmpeg.exe from %%D\bin
        move /Y "%%D\bin\ffmpeg.exe" "deploy-win\ffmpeg"
        move /Y "%%D\bin\ffprobe.exe" "deploy-win\ffmpeg"
        rd /s /q "deploy-win\ffmpeg-temp"
        del /q "deploy-win\ffmpeg-temp.7z"
	pause
        exit /b 0
    )
) ELSE (
    echo ffmpeg.exe already exists, skipping download.
)
pause
