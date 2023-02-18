#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QFont>
#include <QLabel>
#include "mainWindow.h"

int main(int argc, char** argv) {

	QApplication app(argc, argv);

	mainWindow* w = new mainWindow();
	w->initializeConnections(&app);

	w->show();

	return app.exec();
}
