#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QProcess>
#include <QDebug>
#include <QStandardPaths>
#include <QTextEdit>

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
    comboBox->addItem("webm");
    comboBox->addItem("mp3");
    comboBox->addItem("aac");
    comboBox->addItem("mp4");
    comboBox->addItem("mkv");

    layout->addWidget(comboBox);

    QHBoxLayout *folderLayout = new QHBoxLayout;

    QLineEdit *folderPath = new QLineEdit();
    folderPath->setText(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation));
    folderPath->setPlaceholderText("No folder selected");
    folderLayout->addWidget(folderPath);

    QPushButton *selectFolderButton = new QPushButton("Select Folder");
    selectFolderButton->setFixedWidth(100);
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
        QWidget *downloadWindow = new QWidget();
        downloadWindow->setWindowTitle("Download Output");
        downloadWindow->resize(600, 400);

        QVBoxLayout *vLayout = new QVBoxLayout(downloadWindow);
        QTextEdit *textEdit = new QTextEdit(downloadWindow);
        textEdit->setReadOnly(true);
        vLayout->addWidget(textEdit);

        downloadWindow->setLayout(vLayout);
        downloadWindow->show();

        QProcess *process = new QProcess(downloadWindow);
        QString url = textInput->text();
        QString format = comboBox->currentText();
        QString outputFolder = folderPath->text();

#if _WIN32
        QString ytDlpPath = QCoreApplication::applicationDirPath() + "/yt-dlp.exe";
#else
        QString ytDlpPath = "yt-dlp";
#endif

        QStringList args;
        args << url;
        args << "-o" << (outputFolder + "/%(title)s.%(ext)s");
#if _WIN32
        args << "--ffmpeg-location" << (QCoreApplication::applicationDirPath() + "/ffmpeg");
#endif

        if (format != "webm") {
            args << "-t" << format;
        }

        QObject::connect(process, &QProcess::readyReadStandardOutput, [=]() {
            QByteArray data = process->readAllStandardOutput();
            QTextCursor cursor = textEdit->textCursor();
            cursor.movePosition(QTextCursor::End);
            cursor.insertText(QString::fromLocal8Bit(data));
            textEdit->setTextCursor(cursor);
        });

        QObject::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                         [=](int exitCode, QProcess::ExitStatus status){
            QTextCursor cursor = textEdit->textCursor();
            cursor.movePosition(QTextCursor::End);
            cursor.insertText(QString("Finished with code %1").arg(exitCode));
            textEdit->setTextCursor(cursor);
        });

        process->start(ytDlpPath, args);
    });

    return app.exec();
}
