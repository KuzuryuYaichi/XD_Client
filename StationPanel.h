#pragma once

#include <QWidget>
#include <QBoxLayout>

class Plot;

class StationPanel : public QWidget
{
    Q_OBJECT

public:
    explicit StationPanel(QWidget* parent = 0);

private:
    QVBoxLayout* gridLayout;
    Plot* plot;
    QHBoxLayout* toolsLayout;

private Q_SLOTS:
    void InitLayout();

Q_SIGNALS:
    void fullScreen(bool full);
};
