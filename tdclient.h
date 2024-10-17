#ifndef TDCLIENT_H
#define TDCLIENT_H

#include <QVector>
#include <QDate>
#include <QString>
#include <QUrl>
#include "httpclient.h"

enum class Interval {
    I_1MIN, I_5MIN, I_15MIN, I_30MIN, I_45MIN, I_1H, I_2H, I_4H, I_8H, I_1DAY, I_1WEEK, I_1MONTH
};

QString intervalToString(Interval interval);
Interval intervalFromString(QString str);

//ovo ce mozda biti izbaceno!
class TimeSeries {
public:
    QVector<QDate> time;
    QVector<double> open, high, low, close, volume;
};

class TDClient : public QObject {
private:
    QString apiKey;
    HttpClient *httpclient;
    QUrl formUrl(QString symbol, Interval interval, int outputsize);
public:
    TDClient(QString apiKey, QObject *parent);
    TimeSeries timeSeries(QString symbol, Interval interval, int outputsize);
};

#endif // TDCLIENT_H
