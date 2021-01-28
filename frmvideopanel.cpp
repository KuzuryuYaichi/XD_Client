#include "panel.h"
#include "plot.h"
#include "videopanel.h"
#include "frmvideopanel.h"

frmVideoPanel::frmVideoPanel(QWidget *parent) : QWidget(parent)
{
    d_panel = new Panel(this);
    d_plot = new VideoPanel(this);

    QHBoxLayout* hLayout = new QHBoxLayout(this);
    hLayout->addWidget(d_panel);
    hLayout->addWidget(d_plot, 10);
}
