#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QProcess>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("OurTube");

    QVBoxLayout *layout = new QVBoxLayout(&window);

    QLineEdit *textInput = new QLineEdit();
    textInput->setPlaceholderText("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    layout->addWidget(textInput, 0);

    QComboBox *comboBox = new QComboBox();
    comboBox->addItem("mp4");
    comboBox->addItem("mp4 (video only)");
    comboBox->addItem("mp3");
    comboBox->addItem("webm");
    comboBox->addItem("best format");
    layout->addWidget(comboBox);

    QHBoxLayout *folderLayout = new QHBoxLayout;

    QLineEdit *folderPath = new QLineEdit();
    folderPath->setText("C:/Users/samue/Downloads");
    folderPath->setPlaceholderText("No folder selected");
    folderLayout->addWidget(folderPath);

    QPushButton *selectFolderButton = new QPushButton("Select Folder");
    selectFolderButton->setFixedWidth(120);
    folderLayout->addWidget(selectFolderButton);

    layout->addLayout(folderLayout);

    QObject::connect(selectFolderButton, &QPushButton::clicked, [&]() {
        QString dir = QFileDialog::getExistingDirectory(&window, 
                                                        "Select Download Folder", 
                                                        "",
                                                        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if (!dir.isEmpty()) {
            folderPath->setText(dir);
        }
    });

    QPushButton *button = new QPushButton("Download");
    layout->addWidget(button);

    layout->addStretch();

    window.setLayout(layout);
    window.show();

    QObject::connect(button, &QPushButton::clicked, [&]() {
        QString url = textInput->text();
        QString format = comboBox->currentText();
        QString outputFolder = folderPath->text();

        QStringList args;
        args << url;
        args << "-o" << (outputFolder + "/%(title)s.%(ext)s");
        args << "--ffmpeg-location" << (QCoreApplication::applicationDirPath() + "/ffmpeg");
        if (format == "mp3") args << "-x" << "--audio-format" << "mp3";
        else if (format == "mp4 (video only)") args << "-f" << "bestvideo";
        else if (format == "webm") args << "-f" << "bestvideo[ext=webm]+bestaudio[ext=webm]";

        QString ytDlpPath = QCoreApplication::applicationDirPath() + "/yt-dlp.exe";

        QProcess *process = new QProcess(&window);

        QObject::connect(process, &QProcess::readyReadStandardOutput, [=]() {
            qDebug() << process->readAllStandardOutput();
        });

        QObject::connect(process, &QProcess::readyReadStandardError, [=]() {
            qDebug() << "ERROR:" << process->readAllStandardError();
        });

        process->start(ytDlpPath, args);

        if (!process->waitForStarted()) {
            qDebug() << "Failed to start yt-dlp process!";
            return;
        }
    });

    return app.exec();
}
