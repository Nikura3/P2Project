#ifndef PROMPTWINDOW_H
#define PROMPTWINDOW_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <unistd.h>
#include <QApplication>
#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QLCDNumber>
#include <QSlider>
#include <QDoubleSpinBox>
#include <QString>
#include <QRadioButton>
#include <QMessageBox>
#include "mainWindow.h"

class promptWindow : public QWidget {

	Q_OBJECT

	private:

	public:
		promptWindow(mainWindow* = nullptr, std::string = "new", QLabel* = nullptr, QWidget* = nullptr);

		virtual void initializeValues() = 0;
		virtual void initializeConnections() const = 0;
		void updateLayout();

		mainWindow* _main;

		std::string _type;

		QPushButton* _create;
		QPushButton* _cancel;

		QGroupBox* _centerpoint_panel;
		std::vector<QGroupBox*> _size_panel;
		QGroupBox* _color_panel;
		QGroupBox* _light_panel;
		QGroupBox* _buttons_panel;

		QVBoxLayout* _main_layout;
		QHBoxLayout* _centerpoint_layout;
		std::vector<QHBoxLayout*> _size_layout;
		QHBoxLayout* _color_layout;
		QHBoxLayout* _light_layout;
		QHBoxLayout* _buttons_layout;

		QLabel* _centerpoint_label;
		QLabel* _color_label;
		QLabel* _light_label;

		QLabel* _modify_label;

		QDoubleSpinBox* _centerpoint_x;
		QDoubleSpinBox* _centerpoint_y;
		QDoubleSpinBox* _centerpoint_z;
		QSpinBox* _color_r;
		QSpinBox* _color_g;
		QSpinBox* _color_b;

		QRadioButton* _light_realistic;
		QRadioButton* _light_toon;

	public slots:
		void exit();
		virtual void action() = 0;
};

#endif
