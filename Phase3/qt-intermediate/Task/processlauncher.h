#ifndef PROCESSLAUNCHER_H
#define PROCESSLAUNCHER_H

#include <QObject>
#include <QProcess>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>

class ProcessLauncher : public QObject {
    Q_OBJECT

public:
    explicit ProcessLauncher(QObject *parent = nullptr);
    void startProcess(const QString &program, const QStringList &arguments = {});

private slots:
    void readOutput();
    void readError();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    QProcess *process;
};

#endif // PROCESSLAUNCHER_H
