#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include "tdwebsocketclient.h"
#include "tdclient.h"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    td = new TDClient("d4b37649faf1431e99784e09402a3c48", this);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QGridLayout *layout = new QGridLayout(centralWidget);
    centralWidget->setLayout(layout);

    symbol = new QLineEdit();
    interval = new QComboBox();
    outputsize = new QLineEdit();
    plot = new QPushButton("Plot");
    customPlot = new QCustomPlot(this);
    financial = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->yAxis->grid()->setVisible(true);

    for (int i = static_cast<int>(Interval::I_1MIN); i <= static_cast<int>(Interval::I_1MONTH); ++i) {
        interval->addItem(intervalToString(static_cast<Interval>(i)));
    }

    layout->addWidget(symbol, 0, 0, 1, 1);
    layout->addWidget(interval, 0, 1, 1, 1);
    layout->addWidget(outputsize, 0, 2, 1, 1);
    layout->addWidget(plot, 0, 3, 1, 1);
    layout->addWidget(customPlot, 1, 0, 4, 4);

    customPlot->xAxis->setLabel("Time");
    customPlot->yAxis->setLabel("Price");

    connect(plot, &QPushButton::clicked, this, &MainWindow::plotClicked);

    TDWebSocketClient socket("d4b37649faf1431e99784e09402a3c48");
    socket.connectToServer();
    socket.subscribe("AAPL");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plotClicked()
{
    TimeSeries ts = td->timeSeries(symbol->text(), intervalFromString(interval->currentText()), outputsize->text().toInt());
    QVector<double> time;
    for (int i=1; i<=ts.time.size(); i++) {
        time.push_back(i);
    }

    financial->setData(time, ts.open, ts.high, ts.low, ts.close);
    customPlot->xAxis->setRange(0, time.size()+1);
    customPlot->yAxis->setRange(*std::min_element(ts.low.begin(), ts.low.end()), *std::max_element(ts.high.begin(), ts.high.end()));
    customPlot->replot();
}
