#ifndef OUTLINESTATSDLG_H
#define OUTLINESTATSDLG_H

#include <QDialog>
#include <QVector>

class SurfaceManager;
class outlineZoomer;
namespace Ui {
class outlineStatsDlg;
}

class outlineStatsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit outlineStatsDlg(QStringList names, SurfaceManager *sm, QWidget *parent = 0);
    ~outlineStatsDlg();
    QStringList m_names;
    QVector<double> xvals;
    QVector<double> yvals;
private slots:
    void on_pushButton_clicked();

private:
    Ui::outlineStatsDlg *ui;

    double mostFrequentRadius;
    QVector<double> radVals;
    QVector<double> sn;
    void readFiles();
    void plot();
    outlineZoomer * zoomer;
    outlineZoomer *radZoomer;
    SurfaceManager *m_surfaceManager;
};

#endif // OUTLINESTATSDLG_H
