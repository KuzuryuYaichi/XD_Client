#ifndef _PANEL_H_
#define _PANEL_H_

#include "settings.h"
#include <QTabWidget>
#include <QDateTimeEdit>

class QComboBox;
class SpinBox;
class CheckBox;
class QDateEdit;

class Panel: public QTabWidget
{
    Q_OBJECT

public:
    Panel( QWidget * = NULL );

    Settings settings() const;
    void setSettings( const Settings & );

Q_SIGNALS:
    void settingsChanged( const Settings & );

private Q_SLOTS:
    void edited();

private:
    //QWidget* Panel::addStationInfo(QWidget*, QGridLayout*, QWidget*);

    QWidget* createStationTab(QWidget*);
    QWidget* createControlTab(QWidget*);
    QWidget* createDisplayTab(QWidget*);
    QWidget* createPlotTab(QWidget *);
    QWidget* createCanvasTab(QWidget *);
    QWidget* createCurveTab(QWidget *);

    SpinBox *d_midFreq;
    QDateEdit *d_date;
    SpinBox *d_taskNum;
    QComboBox* d_filterOpt;
    CheckBox* d_rectFilter;
    CheckBox* d_gate;

    QComboBox* d_displayControl;
    CheckBox* d_direct;
    CheckBox* d_rect;

    SpinBox *d_numPoints;
    SpinBox *d_updateInterval;
    QComboBox *d_updateType;

    QComboBox *d_gridStyle;
    CheckBox *d_paintCache;
    CheckBox *d_paintOnScreen;
    CheckBox *d_immediatePaint;
#ifndef QWT_NO_OPENGL
    CheckBox *d_openGL;
#endif

    QComboBox *d_curveType;
    CheckBox *d_curveAntialiasing;
    CheckBox *d_curveClipping;
    CheckBox *d_curveFiltering;
    CheckBox *d_lineSplitting;
    SpinBox  *d_curveWidth;
    QComboBox *d_curvePen;
    CheckBox *d_curveFilled;
};

#endif
