#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QQuickWidget;
class QDockWidget;
class ServTCP;
class QPlainTextEdit;
//class QTC

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	virtual ~MainWindow();

protected:
	virtual void closeEvent(QCloseEvent *event) override;

private:
	QQuickWidget* showSomeQML();
	QDockWidget* createLeftDock();
	void createServer();

	void fuckOffSlot();
	void onResultSlot(const QString& string);

	ServTCP* serv{nullptr};
	QQuickWidget* m_quickView{nullptr};
	QPlainTextEdit* textEdit{nullptr};
};
#endif // MAINWINDOW_H
