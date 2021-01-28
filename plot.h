#pragma once

#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_plot_textlabel.h>

class Plot: public QwtPlot
{
    Q_OBJECT

public:
    enum ColorMap
    {
        RGBMap,
        IndexMap,
        HueMap,
        AlphaMap
    };

    Plot( QWidget * = NULL );

public Q_SLOTS:
    void showContour( bool on );
    void showSpectrogram( bool on );
    void setColorMap( int );
    void setAlpha( int );

#ifndef QT_NO_PRINTER
    void printPlot();
#endif

private:
    QwtPlotSpectrogram *d_spectrogram;
    QwtPlotTextLabel* d_lblIP;
    QwtPlotTextLabel* d_lblCity;
    int d_mapType;
    int d_alpha;

    QwtText txtIP;
    QwtText txtCity;
    QFont font;
};
