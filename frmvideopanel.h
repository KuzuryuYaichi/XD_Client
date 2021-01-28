#pragma once

#include <QWidget>
#include <QHBoxLayout>

class VideoPanel;
class Panel;
class QLabel;
class QHBoxLayout;

class frmVideoPanel : public QWidget
{
    Q_OBJECT

public:
    explicit frmVideoPanel(QWidget *parent = 0);

private:
    VideoPanel* d_plot;
    Panel* d_panel;
    QLabel* d_frameCount;
};
