#include "processlauncher.h"
#include <QDebug>
#include <QDir>
#include <QFile>

ProcessLauncher::ProcessLauncher(QObject *parent) : QObject(parent) {
    process = new QProcess(this);
    connect(process, &QProcess::readyReadStandardOutput, this, &ProcessLauncher::readOutput);
    connect(process, &QProcess::readyReadStandardError, this, &ProcessLauncher::readError);
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &ProcessLauncher::processFinished);
}

//void ProcessLauncher::startProcess(const QString &program, const QStringList &arguments) {
//    process->start(program, arguments);
//    if (!process->waitForStarted()) {
//        qDebug() << "Failed to start process:" << program;
//    }
//}


void ProcessLauncher::startProcess(const QString &program, const QStringList &arguments) {
    qDebug() << "Trying to start:" << program;
    //qDebug() << "Arguments:" << arguments;
    qDebug() << "Working directory:" << QDir::currentPath();

    if (!QFile::exists(program)) {
        qDebug() << "Error: Program does not exist at path:" << program;
        return;
    }

    process->start(program, arguments);

    if (!process->waitForStarted()) {
        qDebug() << "Failed to start process:" << program;
        qDebug() << "QProcess Error:" << process->errorString();
    }
}



void ProcessLauncher::readOutput() {
    qDebug() << "Output:" << process->readAllStandardOutput().data();
}

void ProcessLauncher::readError() {
    qDebug() << "Error:" << process->readAllStandardError();
}

void ProcessLauncher::processFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    qDebug() << "Process finished with exit code:" << exitCode;
    if (exitStatus == QProcess::CrashExit) {
        qDebug() << "Process crashed.";
    }
    qApp->quit();
}
