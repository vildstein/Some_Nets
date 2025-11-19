#include <QDebug>

#include <SocketTCP.h>

SocketTCP::SocketTCP(QObject* parent) : QTcpSocket(parent)
{
	connect(this, &QTcpSocket::readyRead, this, &SocketTCP::read);
	connect(this, &QTcpSocket::disconnected, this, &SocketTCP::deleteLater);
}

void SocketTCP::read()
{
	QDataStream in(this);

	char buffer[120];


	in.readRawData(buffer, 120);

	// for (size_t i = 0; i < 120; ++i) {
	// 	qInfo() << (char)buffer[i];
	// }
	char sym{0};
	size_t count{0};

	QString str;

	while (sym != '\n' && count < 120) {
		sym = (char) buffer[count];
		str.append(sym);
		++count;
	}

	qInfo() << "bytesAvailable() = " << bytesAvailable();

	if (!str.isEmpty()) {
		emit result(str);
	}

	//QByteArray ba;

	close();
}

SocketTCP::~SocketTCP() = default;
