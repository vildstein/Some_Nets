#include "ServTCP.h"
#include "SocketTCP.h"

ServTCP::ServTCP(QObject* parent) : QTcpServer(parent)
{

}

ServTCP::~ServTCP() = default;

void ServTCP::incomingConnection(qintptr socketDescriptor)
{
	SocketTCP* sock = new SocketTCP(this);
	connect(sock, &SocketTCP::result, this, &ServTCP::result);
	sock->setSocketDescriptor(socketDescriptor);
}
