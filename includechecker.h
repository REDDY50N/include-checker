#ifndef INCLUDECHECKER_H
#define INCLUDECHECKER_H

#include <QObject>

#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>
#include <QDebug>

class IncludeChecker : public QObject
{
    Q_OBJECT

public:
    IncludeChecker(QObject *parent = nullptr) : QObject(parent) {}

    QStringList findIncludes(const QString &directory, const QStringList &extensions)
    {
        QStringList includeFiles;

        QDirIterator dirIt(directory, extensions, QDir::Files, QDirIterator::Subdirectories);
        while (dirIt.hasNext()) {
            QString filePath = dirIt.next();
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                while (!in.atEnd()) {
                    QString line = in.readLine();
                    if (line.startsWith("#include")) {
                        QString includeFilePath = line.mid(9).trimmed();
                        if (includeFilePath.startsWith('"')) {
                            includeFilePath = includeFilePath.mid(1, includeFilePath.length() - 2);
                            includeFilePath = QDir::cleanPath(QFileInfo(file).dir().filePath(includeFilePath));
                            includeFiles.append(includeFilePath);
                        }
                    }
                }
                file.close();
            }
        }

        return includeFiles;
    }

    QStringList findOwnIncludes(const QString &directory, const QStringList &extensions)
    {
        QStringList ownIncludeFiles;

        QDirIterator dirIt(directory, extensions, QDir::Files, QDirIterator::Subdirectories);
        while (dirIt.hasNext()) {
            QString filePath = dirIt.next();
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                while (!in.atEnd()) {
                    QString line = in.readLine();
                    if (line.startsWith("#include")) {
                        QString includeFilePath = line.mid(9).trimmed();
                        if (includeFilePath.startsWith('"')) {
                            includeFilePath = includeFilePath.mid(1, includeFilePath.length() - 2);
                            includeFilePath = QDir::cleanPath(QFileInfo(file).dir().filePath(includeFilePath));
                            if (includeFilePath.startsWith(directory)) {
                                ownIncludeFiles.append(includeFilePath);
                            }
                        }
                    }
                }
                file.close();
            }
        }

        return ownIncludeFiles;
    }
};


#endif // INCLUDECHECKER_H
