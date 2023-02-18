#ifndef PROMPTWINDOWCUBE_H
#define PROMPTWINDOWCUBE_H

#include "promptWindow.h"

class promptWindowCube : public promptWindow {

	Q_OBJECT

	private:

	public:
		promptWindowCube(mainWindow* = nullptr, std::string = "new", QLabel* = nullptr, QWidget* = nullptr);

		void initializeValues();
		void initializeConnections() const;

		QLabel* _edge_label;

		QDoubleSpinBox* _edge;

	public slots:
		void action();
		void modify();
		void createObject(char, double, double, double, double, unsigned int, unsigned int, unsigned int, int = 10);
		void printErrorMessage();

	signals:
		void act(char, double, double, double, double, unsigned int, unsigned int, unsigned int, int = 10);
		void modifySignal(QLabel*, char, char, double, double, double, double, unsigned int, unsigned int, unsigned int, int = 10);
		void error();
};

#endif
