#include <QCoreApplication>
#include "processlauncher.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    ProcessLauncher launcher;

    QString programPath = "D:/repos/qt/build-untitled-Desktop_Qt_5_14_2_MinGW_64_bit-Release/release/untitled.exe";

    // Check if the file exists before starting
    if (!QFile::exists(programPath)) {
        qDebug() << "Error: External program does not exist at path:" << programPath;
        return -1;  // Exit with an error code
    }

    launcher.startProcess(programPath);   // Start external program
    return app.exec();
}
