#include "mainwindow.h"
#include "httpclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    HttpClient httpclient;
    httpclient.makeRequest(QUrl("https://finnhub.io/api/v1/quote?symbol=AAPL&token=cs58pqhr01qo1hu16h70cs58pqhr01qo1hu16h7g"));
    w.show();
    return a.exec();
}
