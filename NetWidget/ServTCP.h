#ifndef SERVTCP_H
#define SERVTCP_H

#include <QTcpServer>

class ServTCP : public QTcpServer
{
	Q_OBJECT

public:
	explicit ServTCP(QObject* parent = nullptr);
	virtual ~ServTCP();

signals:
	void result(const QString& str);

protected:
	virtual void incomingConnection(qintptr socketDescriptor) override;

private:


};





#endif // SERVTCP_H
