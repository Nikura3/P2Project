#ifndef PROMPTWINDOWSPHERE_H
#define PROMPTWINDOWSPHERE_H

#include "promptWindow.h"

class promptWindowSphere : public promptWindow {

	Q_OBJECT

	private:

	public:
		promptWindowSphere(mainWindow* = nullptr, std::string = "new", QLabel* = nullptr, QWidget* = nullptr);

		void initializeValues();
		void initializeConnections() const;

		QLabel* _radius_label;

		QDoubleSpinBox* _radius;

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
