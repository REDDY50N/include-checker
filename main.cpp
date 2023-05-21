#include <QCoreApplication>

#include "includechecker.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QString directory = ".";
    QStringList extensions = { "*.h", "*.cpp" };

    IncludeChecker checker;

    QStringList allIncludes = checker.findIncludes(directory, extensions);
    qDebug() << "All includes:";
    for (const auto &includeFile : allIncludes) {
        qDebug() << includeFile;
    }

    QStringList ownIncludes = checker.findOwnIncludes(directory, extensions);
    qDebug() << "\nOwn includes:";
    for (const auto &ownIncludeFile : ownIncludes) {
        qDebug() << ownIncludeFile;
    }

    return 0;
}
