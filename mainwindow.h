#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "httpclient.h"
#include "tdclient.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TDClient *td;
    QLineEdit *symbol;
    QComboBox *interval;
    QLineEdit *outputsize;
    QPushButton *plot;
    QCustomPlot *customPlot;
    QCPFinancial *financial;
private slots:
    void plotClicked();
};
#endif // MAINWINDOW_H
