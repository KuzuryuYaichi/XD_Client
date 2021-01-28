#include "StationPanel.h"
#include "plot.h"
#include "IPAddress.h"
#include <QLabel>
#include <QLineEdit>

StationPanel::StationPanel(QWidget* parent): QWidget(parent)
{
    this->InitLayout();
}

void StationPanel::InitLayout()
{
    gridLayout = new QVBoxLayout(this);
    plot = new Plot(this);
    toolsLayout = new QHBoxLayout(this);
    //toolsLayout->addWidget(new QLabel("Freq", this));
    //toolsLayout->addWidget(new QLineEdit(this));
    //toolsLayout->addWidget(new QLabel("Gate", this));
    //toolsLayout->addWidget(new QLineEdit(this));

    gridLayout->addWidget(plot, 10);
    //gridLayout->addLayout(toolsLayout);
    this->setLayout(gridLayout);
}
