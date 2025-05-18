#include "astigpolargraph.h"
#include "ui_astigpolargraph.h"
#include "surfacemanager.h"
#include <QtCharts/QLegendMarker>


astigPolargraph::astigPolargraph(    QList<int>list, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::astigPolargraph), m_list(list)
{
    ui->setupUi(this);
    
    QPolarChart *chart = new QPolarChart();

    // process each wave front and place astig on the chart
    ui->waveFrontTable->setRowCount(m_list.size());

    QValueAxis *angularAxis = new QValueAxis();
    angularAxis->setTickCount(9); // First and last ticks are co-located on 0/360 angle.
    angularAxis->setLabelFormat("%.0f");
    angularAxis->setShadesVisible(true);
    angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
    chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);

    QValueAxis *radialAxis = new QValueAxis();
    radialAxis->setTickCount(5);
    radialAxis->setLabelFormat("%.1f");
    chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);
    double maxAstig = 1.;

    QVector<wavefront *>  wavefronts =SurfaceManager::get_instance()->m_wavefronts;

    for(int ndx = 0; ndx < m_list.length(); ++ndx){
        wavefront *wf = wavefronts[m_list[ndx]];
        QString name = wf->name;
        int slashndx = name.lastIndexOf('/');
        QString shortName = name.mid(name.lastIndexOf('/',slashndx-1));
        QTableWidgetItem *item = new QTableWidgetItem(shortName, 0);
        ui->waveFrontTable->setItem(ndx,0,item);
        double xastig = wf->InputZerns[4];
        double yastig = wf->InputZerns[5];
        double mag = sqrt(xastig * xastig + yastig * yastig);
        if (mag > maxAstig) maxAstig = mag;

        double angle = (atan2(yastig,xastig)/2.) * 180./M_PI;
        angle = 90 - angle;
        QScatterSeries *series = new QScatterSeries();

        int lastndx = name.lastIndexOf('/');
        if (lastndx != -1)
            name = name.mid(lastndx);
        series->setName(name);
        series->append(angle,mag);
        series->append(angle+180,mag);
        chart->addSeries(series);
        series->attachAxis(radialAxis);
        series->attachAxis(angularAxis);

        QLineSeries *line = new QLineSeries();
        line->append(angle,mag);
        line->append(angle+180,mag);
        chart->addSeries(line);
        line->attachAxis(radialAxis);
        line->attachAxis(angularAxis);
        chart->legend()->markers(line)[0]->setVisible(false);

        line->setPen(QPen(series->brush(),5));

        QTableWidgetItem *pv = new QTableWidgetItem(QString().number(mag), 0);
        item->setForeground(series->brush());
        ui->waveFrontTable->setItem(ndx, 1, pv);
        QTableWidgetItem *anglewidget = new QTableWidgetItem(QString().number(angle,'f',1), 0);
        ui->waveFrontTable->setItem(ndx, 2, anglewidget);
    }

    chart->setTitle("Magnitude and axis of high edge");
    if (m_list.length() > 4)
        chart->legend()->setAlignment(Qt::AlignRight);
    else chart->legend()->setAlignment(Qt::AlignBottom);

    maxAstig = ceil(maxAstig);
    radialAxis->setRange(0, maxAstig);
    angularAxis->setRange(0, 360);

    ui->polarChart->setChart(chart);
}

astigPolargraph::~astigPolargraph()
{
    delete ui;
}
