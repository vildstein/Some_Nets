#include <QDockWidget>
#include <QQuickWidget>
#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QMdiArea>
#include <QSurfaceFormat>
#include <QMetaObject>

#include <iostream>

#include "mainwindow.h"
#include "ServTCP.h"

constexpr const quint16 PORT_NUMBER = 60050;


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	QMdiArea* centralWidget = new QMdiArea(this);

	createServer();
	setDockOptions(QMainWindow::AnimatedDocks);

	auto dock = createLeftDock();
	addDockWidget(Qt::LeftDockWidgetArea, dock);

	textEdit = new QPlainTextEdit(this);

	m_quickView = showSomeQML();

	centralWidget->addSubWindow(textEdit);
	centralWidget->addSubWindow(m_quickView);

	setCentralWidget(centralWidget);

	resize(500, 500);
}

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent* event)
{
	serv->close();
	delete serv;
	serv = nullptr;
	QApplication::quit();
}

QQuickWidget* MainWindow::showSomeQML()
{
	QUrl file(("qrc:/LeftDockWidget/leftDock.qml"));
	//QQmlApplicationEngine* engine = new QQmlApplicationEngine(this);
	//engine->load(file);

	//QSurfaceFormat fmt;
	//fmt.setSamples(4);
	//fmt.setProfile(QSurfaceFormat::CoreProfile);

	QQuickWidget* view = new QQuickWidget;
	view->setAttribute(Qt::WA_DeleteOnClose, true);
	//view->setFormat(fmt);
	view->resize(200, 300);
	view->setResizeMode(QQuickWidget::SizeRootObjectToView);

	view->setSource(file);
	connect(view, &QQuickWidget::destroyed, qApp, QApplication::quit);

	return view;
}

QDockWidget* MainWindow::createLeftDock()
{
	QDockWidget* dockWidget = new QDockWidget(tr("Dock Widget"), this);
	dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
	dockWidget->setFeatures(QDockWidget::DockWidgetClosable);

	QFrame* fr = new QFrame;
	fr->setFrameStyle(QFrame::NoFrame);
	//fr->setLineWidth(3);
	QHBoxLayout* topLay = new QHBoxLayout;
	topLay->addWidget(new QPushButton(tr("Start")));
	topLay->addWidget(new QPushButton(tr("Close")));
	QHBoxLayout* downLay = new QHBoxLayout;
	downLay->addWidget(new QPushButton(tr("3")));

	QPushButton* fuckOffBtn = new QPushButton(tr("fuckOff"));
	downLay->addWidget(fuckOffBtn);
	QVBoxLayout* mainLay = new QVBoxLayout;
	mainLay->addLayout(topLay);
	mainLay->addLayout(downLay);
	mainLay->addStretch();

	fr->setLayout(mainLay);
	dockWidget->setWidget(fr);

	connect(fuckOffBtn, &QPushButton::clicked, this, &MainWindow::fuckOffSlot);

	return dockWidget;
}

void MainWindow::createServer()
{
	serv = new ServTCP(this);
	connect(serv, &ServTCP::result, this, &MainWindow::onResultSlot);
	if (!serv->listen(QHostAddress::Any, PORT_NUMBER)) {
	//if (!serv->listen(QHostAddress("192.168.1.61"), PORT_NUMBER) ) {
		std::cerr << "No Server. FUCK OFF" << std::endl;
		QApplication::quit();
	}
}

void MainWindow::fuckOffSlot()
{
	auto quickItem = m_quickView->rootObject();
	QMetaObject::invokeMethod(quickItem, "fuckOff", Qt::AutoConnection);
}

void MainWindow::onResultSlot(const QString& string)
{
	textEdit->appendPlainText(string);
}
