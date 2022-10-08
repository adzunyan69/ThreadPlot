#ifndef LOGHANDLER_H
#define LOGHANDLER_H
#include <QMutex>
#include <QTextStream>
#include <QString>
#include <QDateTime>
#include <QThread>

namespace Utility {

namespace UtilityPrivate {
QString getLogMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg);
}



void logMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex messageMutex;
    QMutexLocker locker(&messageMutex);

    auto txt = UtilityPrivate::getLogMsg(type, context, msg);

    QTextStream cout(stdout, QIODevice::WriteOnly);
    cout << txt << Qt::endl;
}

QString UtilityPrivate::getLogMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static long long uid = 0;
    uid++;

    QString txt;
    QString function = context.function;

    switch (type) {
        case QtInfoMsg:
            txt = QString("Info [%1@%2]>> %3").arg(function).arg(context.line).arg(msg);
        break;
        case QtDebugMsg:
            txt = QString("Debug [%1@%2]>> %3").arg(function).arg(context.line).arg(msg);
            break;
        case QtWarningMsg:
            txt = QString("Warning [%1@%2]>> %3").arg(function).arg(context.line).arg(msg);
        break;
        case QtCriticalMsg:
            txt = QString("Critical [%1@%2]>> %3").arg(function).arg(context.line).arg(msg);
        break;
        case QtFatalMsg:
            txt = QString("Fatal [%1@%2]>> %3").arg(function).arg(context.line).arg(msg);
            abort();
        break;
    }

    QDateTime dateTime = QDateTime::currentDateTime();
    txt = QString("%1@%2 %3 | [0x%4] ")
          .arg(uid)
          .arg(dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz"))
          .arg(txt)
          .arg(reinterpret_cast<intptr_t>(QThread::currentThreadId()));

    return txt;
}


}

#endif // LOGHANDLER_H
