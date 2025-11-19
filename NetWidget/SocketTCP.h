#ifndef SOCKETTCP_H
#define SOCKETTCP_H

#include <QTcpSocket>

class SocketTCP : public QTcpSocket
{
	Q_OBJECT
public:
	explicit SocketTCP(QObject* parent = nullptr);
	virtual ~SocketTCP();

	void read();

signals:
	void result(const QString& resultString);

protected:

private:
};


#endif
