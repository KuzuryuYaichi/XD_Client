#ifndef M_UDPSOCKET
#define M_UPDSOCKET

#include <QtNetwork/QtNetwork>

class QUdpSocket;
class QHostAddress;

class M_UdpSocket : QUdpSocket
{
private:
	//QHostAddress localAddr;
	int localPort;
	//QHostAddress remoteAddr;
	int remotePort;

public:
    void LinkUp();
	void udpDataReceived();
};

#endif
