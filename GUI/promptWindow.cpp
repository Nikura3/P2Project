#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <QApplication>
#include <QWidget>
#include <QObject>
#include <QFont>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include "promptWindow.h"

promptWindow::promptWindow(mainWindow* main, std::string type, QLabel* l, QWidget* parent) : QWidget(parent) {

	_main = main;

	_type = type;

	if (_type == "new") {
		_create = new QPushButton(tr("Create"));
	} else {
		_create = new QPushButton(tr("Modify"));
		_modify_label = l;
	}
	_create->setFont(QFont("Lato", 22));

	_cancel = new QPushButton(tr("Cancel"));
	_cancel->setFont(QFont("Lato", 22));

	_centerpoint_panel = new QGroupBox;
	_color_panel = new QGroupBox;
	_light_panel = new QGroupBox;
	_buttons_panel = new QGroupBox;

	_centerpoint_label = new QLabel;
	_centerpoint_label->setText("Center (x, y, z) :");
	_centerpoint_label->setFont(QFont("Lato", 18));
	_centerpoint_label->setMargin(15);

	_color_label = new QLabel;
	_color_label->setText("Color (r, g, b) :");
	_color_label->setFont(QFont("Lato", 18));
	_color_label->setMargin(15);

	_light_label = new QLabel;
	_light_label->setText("Lightning:");
	_light_label->setFont(QFont("Lato", 18));
	_light_label->setMargin(15);

	_centerpoint_x = new QDoubleSpinBox;
	_centerpoint_x->setRange(-500, 500);
	_centerpoint_x->setDecimals(2);
	_centerpoint_x->setSingleStep(0.01);
	_centerpoint_y = new QDoubleSpinBox;
	_centerpoint_y->setRange(-500, 500);
	_centerpoint_y->setDecimals(2);
	_centerpoint_y->setSingleStep(0.01);
	_centerpoint_z = new QDoubleSpinBox;
	_centerpoint_z->setRange(-5000, 0);
	_centerpoint_y->setDecimals(2);
	_centerpoint_z->setSingleStep(0.01);
	_color_r = new QSpinBox;
	_color_r->setRange(0, 255);
	_color_g = new QSpinBox;
	_color_g->setRange(0, 255);
	_color_b = new QSpinBox;
	_color_b->setRange(0, 255);

	_light_realistic = new QRadioButton("Realistic");
	_light_toon = new QRadioButton("Toon");

	// main
	_main_layout = new QVBoxLayout;
	_main_layout->addWidget(_centerpoint_panel);
	for (unsigned int i = 0; i < _size_panel.size(); ++i) {
		_main_layout->addWidget(_size_panel[i]);
	}
	_main_layout->addWidget(_color_panel);
	_main_layout->addWidget(_light_panel);
	_main_layout->addWidget(_buttons_panel);
	setLayout(_main_layout);

	// center point
	_centerpoint_layout = new QHBoxLayout;
	_centerpoint_layout->addWidget(_centerpoint_label);
	_centerpoint_layout->addWidget(_centerpoint_x);
	_centerpoint_layout->addWidget(_centerpoint_y);
	_centerpoint_layout->addWidget(_centerpoint_z);
	_centerpoint_panel->setLayout(_centerpoint_layout);

	// size

	// color
	_color_layout = new QHBoxLayout;
	_color_layout->addWidget(_color_label);
	_color_layout->addWidget(_color_r);
	_color_layout->addWidget(_color_g);
	_color_layout->addWidget(_color_b);
	_color_panel->setLayout(_color_layout);

	// light
	_light_layout = new QHBoxLayout;
	_light_layout->addWidget(_light_label);
	_light_layout->addWidget(_light_realistic);
	_light_layout->addWidget(_light_toon);
	_light_panel->setLayout(_light_layout);

	// buttons
	_buttons_layout = new QHBoxLayout;
	_buttons_layout->addWidget(_create);
	_buttons_layout->addWidget(_cancel);
	_buttons_panel->setLayout(_buttons_layout);

	resize(640, 360);
}

// private

//public

void promptWindow::updateLayout() {
	
	for (unsigned int i = 0; i < _size_panel.size(); ++i) {
		_main_layout->addWidget(_size_panel[i]);
	}
	_main_layout->addWidget(_color_panel);
	_main_layout->addWidget(_light_panel);
	_main_layout->addWidget(_buttons_panel);
}

// public slots

void promptWindow::exit() {
	close();
}
