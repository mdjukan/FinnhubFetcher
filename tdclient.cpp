#include "tdclient.h"
#include "httpclient.h"
#include <QJsonArray>
#include <QJsonObject>

QString intervalToString(Interval interval) {
    switch (interval) {
    case Interval::I_1MIN:   return "1min";
    case Interval::I_5MIN:   return "5min";
    case Interval::I_15MIN:  return "15min";
    case Interval::I_30MIN:  return "30min";
    case Interval::I_45MIN:  return "45min";
    case Interval::I_1H:     return "1h";
    case Interval::I_2H:     return "2h";
    case Interval::I_4H:     return "4h";
    case Interval::I_8H:     return "8h";
    case Interval::I_1DAY:   return "1day";
    case Interval::I_1WEEK:  return "1week";
    case Interval::I_1MONTH: return "1month";
    }
}

//API vrace time string u razlicitom formatu u zavisnosti od intervala
//za sve ispod jednog dana
//2024-10-14 09:30:00

//za 1day i preko 1day
//2024-10-14
QDate dateFromString(QString date, Interval interval) {
    QString format;
    switch (interval) {
    case Interval::I_1MIN:
    case Interval::I_5MIN:
    case Interval::I_15MIN:
    case Interval::I_30MIN:
    case Interval::I_45MIN:
    case Interval::I_1H:
    case Interval::I_2H:
    case Interval::I_4H:
    case Interval::I_8H:
        format = "yyyy-MM-dd HH:mm:ss";
        break;
    case Interval::I_1DAY:
    case Interval::I_1WEEK:
    case Interval::I_1MONTH:
        format = "yyyy-MM-dd";
    }

    return QDate::fromString(date, format);
}



TDClient::TDClient(QString apiKey, QObject *parent) : QObject(parent), apiKey(apiKey) {
    httpclient = new HttpClient(this);
}

//za sad ne mislim error
//postoje dve vrste error http error, i api error
//kako funkcionisu execptions u c++?
TimeSeries TDClient::timeSeries(QString symbol, Interval interval, int outputsize) {
    QUrl url = formUrl(symbol, interval, outputsize);
    QJsonDocument *jsonDoc = httpclient->makeRequest(url); //pretpostavicu da ovo nije nullptr

    TimeSeries result;
    QJsonObject obj = jsonDoc->object();
    QJsonArray arr = obj["values"].toArray();
    for (const QJsonValue &value : arr) {
        QJsonObject value_obj = value.toObject();
        result.time.push_back(dateFromString(value_obj["time"].toString(), interval));
        result.open.push_back(value_obj["open"].toString().toDouble());
        result.high.push_back(value_obj["high"].toString().toDouble());
        result.low.push_back(value_obj["low"].toString().toDouble());
        result.close.push_back(value_obj["close"].toString().toDouble());
    }

    return result;
}

QUrl TDClient::formUrl(QString symbol, Interval interval, int outputsize) {
    QString baseUrl = "https://api.twelvedata.com/time_series";
    QString url = QString("%1?symbol=%2&interval=%3&apikey=%4&outputsize=%5&source=docs")
    .arg(baseUrl)
    .arg(symbol)
    .arg(intervalToString(interval))
    .arg(apiKey)
    .arg(outputsize);

    return QUrl(url);
}

Interval intervalFromString(QString str)
{
    if (str == "1min") return Interval::I_1MIN;
    if (str == "5min") return Interval::I_5MIN;
    if (str == "15min") return Interval::I_15MIN;
    if (str == "30min") return Interval::I_30MIN;
    if (str == "45min") return Interval::I_45MIN;
    if (str == "1h") return Interval::I_1H;
    if (str == "2h") return Interval::I_2H;
    if (str == "4h") return Interval::I_4H;
    if (str == "8h") return Interval::I_8H;
    if (str == "1day") return Interval::I_1DAY;
    if (str == "1week") return Interval::I_1WEEK;
    if (str == "1month") return Interval::I_1MONTH;
    return Interval::I_1MONTH;
}
