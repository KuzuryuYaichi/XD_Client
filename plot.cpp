#include <qprinter.h>
#include <qprintdialog.h>
#include <qnumeric.h>
#include <qwt_color_map.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_scale_widget.h>
#include <qwt_scale_draw.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_renderer.h>
#include "plot.h"

class MyZoomer: public QwtPlotZoomer
{
public:
    MyZoomer(QWidget *canvas): QwtPlotZoomer(canvas)
    {
        setTrackerMode(AlwaysOn);
    }

    virtual QwtText trackerTextF(const QPointF &pos) const
    {
        QColor bg(Qt::white);
        bg.setAlpha(200);

        QwtText text = QwtPlotZoomer::trackerTextF(pos);
        text.setBackgroundBrush(QBrush(bg));
        return text;
    }
};

class SpectrogramData: public QwtRasterData
{
public:
    SpectrogramData()
    {
        setInterval(Qt::XAxis, QwtInterval(-1.5, 1.5));
        setInterval(Qt::YAxis, QwtInterval(-1.5, 1.5));
        setInterval(Qt::ZAxis, QwtInterval(0.0, 10.0));
        double cc = 0;
        for (int x = 0; x < 1024; x++)
        {
            for (int j = 0; j < 1024; j++)
            {
                qq[x][j] = cc;
            }
            cc += (double)10/1024;
        }
    }
    
    virtual double value(double x, double y) const
    {
        if (qIsNaN(x) || qIsNaN(y))return 0;
        double XminVal = interval(Qt::XAxis).minValue(), XmaxVal = interval(Qt::XAxis).maxValue();
        double Xlen = XmaxVal - XminVal;
        double YminVal = interval(Qt::XAxis).minValue(), YmaxVal = interval(Qt::XAxis).maxValue();
        double Ylen = YmaxVal - YminVal;
        return qq[(int)(1023 * (x - XminVal) / Xlen)][(int)(1023 * (y - YminVal) / Ylen)];
    }

private:
    double qq[1024][1024];
};

class LinearColorMapRGB: public QwtLinearColorMap
{
public:
    LinearColorMapRGB(): QwtLinearColorMap(Qt::darkCyan, Qt::red, QwtColorMap::RGB)
    {
        addColorStop(0.1, Qt::cyan);
        addColorStop(0.6, Qt::green);
        addColorStop(0.95, Qt::yellow);
    }
};

class LinearColorMapIndexed: public QwtLinearColorMap
{
public:
    LinearColorMapIndexed(): QwtLinearColorMap(Qt::darkCyan, Qt::red, QwtColorMap::Indexed)
    {
        addColorStop(0.1, Qt::cyan);
        addColorStop(0.6, Qt::green);
        addColorStop(0.95, Qt::yellow);
    }
};

class HueColorMap: public QwtColorMap
{
public:
    HueColorMap(): d_hue1(0), d_hue2(359), d_saturation(150), d_value(200)
    {
        updateTable();
    }

    virtual QRgb rgb(const QwtInterval &interval, double value) const
    {
        if (qIsNaN(value))
            return 0u;
        const double width = interval.width();
        if (width <= 0)
            return 0u;
        if (value <= interval.minValue())
            return d_rgbMin;
        if (value >= interval.maxValue())
            return d_rgbMax;

        const double ratio = (value - interval.minValue()) / width;
        int hue = d_hue1 + qRound(ratio * (d_hue2 - d_hue1));
        if (hue >= 360)
        {
            hue -= 360;
            if (hue >= 360)
                hue %= 360;
        }
        return d_rgbTable[hue];
    }

    virtual unsigned char colorIndex(const QwtInterval &, double) const
    {
        // we don't support indexed colors
        return 0;
    }

private:
    void updateTable()
    {
        for (int i = 0; i < 360; i++)
            d_rgbTable[i] = QColor::fromHsv(i, d_saturation, d_value).rgb();
        d_rgbMin = d_rgbTable[d_hue1 % 360];
        d_rgbMax = d_rgbTable[d_hue2 % 360];
    }
    int d_hue1, d_hue2, d_saturation, d_value;
    QRgb d_rgbMin, d_rgbMax, d_rgbTable[360];
};

class AlphaColorMap: public QwtAlphaColorMap
{
public:
    AlphaColorMap()
    {
        //setColor(QColor("DarkSalmon"));
        setColor(QColor("SteelBlue"));
    }
};

Plot::Plot(QWidget *parent): QwtPlot(parent), d_alpha(255)
{
    d_spectrogram = new QwtPlotSpectrogram();
    d_spectrogram->setRenderThreadCount( 0 ); // use system specific thread count
    d_spectrogram->setCachePolicy(QwtPlotRasterItem::PaintCache);

    font.setBold(true);
    txtCity.setText(QString::fromLocal8Bit("���"));
    txtCity.setRenderFlags(Qt::AlignLeft | Qt::AlignTop);
    txtCity.setFont(font);

    txtIP.setText(QString("192.168.1.155"));
    txtIP.setRenderFlags(Qt::AlignRight | Qt::AlignBottom);
    txtIP.setFont(font);

    d_lblCity = new QwtPlotTextLabel();
    d_lblCity->setText(txtCity);
    d_lblCity->attach(this);

    d_lblIP = new QwtPlotTextLabel();
    d_lblIP->setText(txtIP);
    d_lblIP->attach(this);

    QList<double> contourLevels;
    for ( double level = 0.5; level < 10.0; level += 1.0 )
        contourLevels += level;
    d_spectrogram->setContourLevels(contourLevels);
    d_spectrogram->setData(new SpectrogramData());
    d_spectrogram->attach(this);

    // A color bar on the right axis
    //QwtScaleWidget *rightAxis = axisWidget( QwtPlot::yRight );
    //rightAxis->setTitle( "Intensity" );
    //rightAxis->setColorBarEnabled( true );
    //const QwtInterval zInterval = d_spectrogram->data()->interval( Qt::ZAxis );
    //setAxisScale( QwtPlot::yRight, zInterval.minValue(), zInterval.maxValue() );
    //enableAxis( QwtPlot::yRight );

    plotLayout()->setAlignCanvasToScales( true );
    setColorMap( Plot::RGBMap );

    QwtPlotZoomer* zoomer = new MyZoomer(canvas());
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect3, Qt::RightButton );

    QwtPlotPanner* panner = new QwtPlotPanner(canvas());
    panner->setAxisEnabled( QwtPlot::yRight, false );
    panner->setMouseButton( Qt::MidButton );

    // Avoid jumping when labels with more/less digits
    // appear/disappear when scrolling vertically
    const QFontMetrics fm(axisWidget(QwtPlot::yLeft)->font());
    QwtScaleDraw *sd = axisScaleDraw(QwtPlot::yLeft);
    sd->setMinimumExtent(fm.width("100.00"));

    const QColor c(Qt::darkBlue);
    zoomer->setRubberBandPen(c);
    zoomer->setTrackerPen(c);
}

void Plot::showContour(bool on)
{
    d_spectrogram->setDisplayMode(QwtPlotSpectrogram::ContourMode, on);
    replot();
}

void Plot::showSpectrogram(bool on)
{
    d_spectrogram->setDisplayMode(QwtPlotSpectrogram::ImageMode, on);
    d_spectrogram->setDefaultContourPen(on ? QPen(Qt::black, 0) : QPen(Qt::NoPen));
    replot();
}

void Plot::setColorMap(int type)
{
    QwtScaleWidget *axis = axisWidget(QwtPlot::yRight);
    const QwtInterval zInterval = d_spectrogram->data()->interval(Qt::ZAxis);
    d_mapType = type;
    int alpha = d_alpha;
    switch( type )
    {
        case Plot::HueMap:
        {
            d_spectrogram->setColorMap(new HueColorMap());
            axis->setColorMap(zInterval, new HueColorMap());
            break;
        }
        case Plot::AlphaMap:
        {
            alpha = 255;
            d_spectrogram->setColorMap(new AlphaColorMap());
            axis->setColorMap(zInterval, new AlphaColorMap());
            break;
        }
        case Plot::IndexMap:
        {
            d_spectrogram->setColorMap(new LinearColorMapIndexed());
            axis->setColorMap(zInterval, new LinearColorMapIndexed());
            break;
        }
        case Plot::RGBMap:
        default:
        {
            d_spectrogram->setColorMap(new LinearColorMapRGB());
            axis->setColorMap(zInterval, new LinearColorMapRGB());
        }
    }
    d_spectrogram->setAlpha(alpha);
    replot();
}

void Plot::setAlpha(int alpha)
{
    d_alpha = alpha;
    if (d_mapType != Plot::AlphaMap)
    {
        d_spectrogram->setAlpha(alpha);
        replot();
    }
}

#ifndef QT_NO_PRINTER

void Plot::printPlot()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOrientation(QPrinter::Landscape);
    printer.setOutputFileName("spectrogram.pdf");

    QPrintDialog dialog(&printer);
    if (dialog.exec())
    {
        QwtPlotRenderer renderer;
        if (printer.colorMode() == QPrinter::GrayScale)
        {
            renderer.setDiscardFlag(QwtPlotRenderer::DiscardBackground);
            renderer.setDiscardFlag(QwtPlotRenderer::DiscardCanvasBackground);
            renderer.setDiscardFlag(QwtPlotRenderer::DiscardCanvasFrame);
            renderer.setLayoutFlag(QwtPlotRenderer::FrameWithScales);
        }
        renderer.renderTo(this, printer);
    }
}

#endif
