#include "M_UdpSocket.h"
#include "ThreadSafeQueue.h"

void M_UdpSocket::LinkUp()
{
    connect(this, SIGNAL(readyRead()), this, SLOT(udpDataReceived()));
    /*lhAddr.setAddress(ui->lEditIpAddr->text());
    lhPort = ui->lEditIpPort->text().toInt();
    rmtAddr.setAddress(ui->lEditUdpIP->text());
    rmtPort = ui->lEditUdpPort->text().toInt();*/
    bool result = bind(localPort);
    if (!result)
    {
        //QMessageBox::information(this, QString::fromLocal8Bit("´íÎó"), QString::fromLocal8Bit("UDP°ó¶¨¶Ë¿ÚÊ§°Ü!"));
        return;
    }
}

void M_UdpSocket::udpDataReceived()
{
    QHostAddress address;
    quint16 port;
    int rcvDataCnt = 0;
    const int MAX_LEN = 1024;

    while (hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(pendingDatagramSize());
        readDatagram(datagram.data(), datagram.size(), &address, &port);
        rcvDataCnt += datagram.size();
    }
}