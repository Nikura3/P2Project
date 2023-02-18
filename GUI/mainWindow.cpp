#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <QApplication>
#include <QWidget>
#include <QObject>
#include <QFont>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "promptWindowSphere.h"
#include "promptWindowCube.h"
#include "mainWindow.h"

std::string getwd() {

	char wd[FILENAME_MAX];
	std::string d;

	if (getcwd(wd, sizeof(wd))) {
		d = static_cast<std::string>(wd);
		d.pop_back();
		d.pop_back();
		d.pop_back();
		return d;
	} else {
		return "";
	}
}

mainWindow::mainWindow(QWidget* parent) : QWidget(parent) {

	_run = new QPushButton(tr("Render image"));
	_run->setFont(QFont("Lato", 22));

	_view = new QPushButton(tr("View Rendered Image"));
	_view->setFont(QFont("Lato", 22));

	_quit = new QPushButton(tr("Quit"));
	_quit->setFont(QFont("Lato", 22));

	_res_label = new QLabel;
	_res = new QLCDNumber;
	_slider = new QSlider(Qt::Horizontal);
	_res_label->setText("Change Resolution:");
	_res_label->setFont(QFont("Lato", 18));
	_res_label->setMaximumSize(250, 40);
	_res->display(getRes());
	_res->setMaximumSize(200, 80);
	_slider->setRange(1, 4);
	_slider->setValue(getRes());
	_slider->setPageStep(1);
	_slider->setStyleSheet(" .QSlider::groove:horizontal { height: 200px; } ");

	_create_sphere = new QPushButton(tr("Create Sphere"));
	_create_sphere->setFont(QFont("Lato", 22));
	_create_sphere->setMinimumSize(200, 150);
	_create_cube = new QPushButton(tr("Create Cube"));
	_create_cube->setFont(QFont("Lato", 22));
	_create_cube->setMinimumSize(200, 150);

	_top_panel = new QGroupBox;
	_left_panel = new QGroupBox;
	_right_panel = new QGroupBox;
	_bottom_panel = new QGroupBox;

	// main
	_main_layout = new QVBoxLayout;
	_main_layout->addWidget(_top_panel);
	_main_layout->addWidget(_bottom_panel);
	setLayout(_main_layout);

	// top panel
	_top_layout = new QHBoxLayout;
	_top_layout->addWidget(_run);
	_top_layout->addWidget(_view);
	_top_layout->addWidget(_quit);
	_top_panel->setLayout(_top_layout);

	// bottom-left panel
	_left_layout = new QVBoxLayout;
	_left_layout->addWidget(_res_label);
	_left_layout->addWidget(_res);
	_left_layout->addWidget(_slider);
	_left_layout->addWidget(_create_sphere);
	_left_layout->addWidget(_create_cube);
	_left_panel->setLayout(_left_layout);

	// bottom-right panel
	_column_layout = new QVBoxLayout;
	_objects_list = new QLabel;
	_objects_list->setText("Objects:");
	_objects_list->setFont(QFont("Lato", 22));
	_objects_list->setMargin(15);
	_objects_list->setAlignment(Qt::AlignCenter);
	_column_layout->addWidget(_objects_list);
	readInput(_column_layout, _rows_layout, _rows);
	_right_panel->setLayout(_column_layout);
	_scroll_area = new QScrollArea;
	_scroll_area->setWidgetResizable(true);
	_scroll_area->setWidget(_right_panel);

	// bottom panel
	_bottom_layout = new QHBoxLayout;
	_bottom_layout->addWidget(_left_panel);
	_bottom_layout->addWidget(_scroll_area);
	_bottom_layout->setStretchFactor(_left_panel, 1);
	_bottom_layout->setStretchFactor(_scroll_area, 9);
	_bottom_panel->setLayout(_bottom_layout);

	setWindowTitle("Ray Tracer");
	//resize(1280, 720);
	showMaximized();
}

// private

int mainWindow::getRes() const {

	int res;

	std::string wd = getwd();
	std::string input_path = wd + "ray_tracer/input";
	std::string input_file = input_path.c_str();
	std::ifstream ifile(input_file, std::ifstream::in);

	ifile >> res;

	ifile.close();

	return res;
}

bool mainWindow::isEqualR(std::ofstream& o_f, std::ifstream& i_f, std::stringstream& s, char object1, char light1) const {

	char object2, light2;
	double x1, x2, y1, y2, z1, z2, rad1, rad2, r1, r2, g1, g2, b1, b2;
	
	i_f >> x1 >> y1 >> z1 >> rad1 >> r1 >> g1 >> b1;
	s >> object2 >> light2 >> x2 >> y2 >> z2 >> rad2 >> r2 >> g2 >> b2;

	if (object1 != object2 || light1 != light2 || x1 != x2 || y1 != y2 || z1 != z2 || rad1 != rad2 || r1 != r2 || g1 != g2 || b1 != b2) {
		o_f << object1 << " " << light1 << " " << x1 << " " << y1 << " " << z1 << " " << rad1 << " " << r1 << " " << g1 << " " << b1 << std::endl;
		return false;
	} else {
		return true;
	}
}

bool mainWindow::isEqualT(std::ofstream& o_f, std::ifstream& i_f, std::stringstream& s, char object1, char light1) const {

	char object2, light2;
	double x1, x2, y1, y2, z1, z2, rad1, rad2, r1, r2, g1, g2, b1, b2, i1, i2;
	
	i_f >> x1 >> y1 >> z1 >> rad1 >> r1 >> g1 >> b1 >> i1;
	s >> object2 >> light2 >> x2 >> y2 >> z2 >> rad2 >> r2 >> g2 >> b2 >> i2;

	if (object1 != object2 || light1 != light2 || x1 != x2 || y1 != y2 || z1 != z2 || rad1 != rad2 || r1 != r2 || g1 != g2 || b1 != b2 || i1 != i2) {
		o_f << object1 << " " << light1 << " " << x1 << " " << y1 << " " << z1 << " " << rad1 << " " << r1 << " " << g1 << " " << b1 << " " << i1 << std::endl;
		return false;
	} else {
		return true;
	}
}

// public

void mainWindow::initializeConnections(QApplication* app) const {

	unsigned int i;
	
	QObject::connect(_run, SIGNAL(clicked()), this, SLOT(executeRayTracer()));
	QObject::connect(_view, SIGNAL(clicked()), this, SLOT(viewImage()));
	QObject::connect(_quit, SIGNAL(clicked()), app, SLOT(quit()));
	QObject::connect(_slider, SIGNAL(valueChanged(int)), _res, SLOT(display(int)));
	QObject::connect(_slider, SIGNAL(valueChanged(int)), this, SLOT(setRes(int)));
	QObject::connect(_create_sphere, SIGNAL(clicked()), this, SLOT(createPromptWindowSphere()));
	QObject::connect(_create_cube, SIGNAL(clicked()), this, SLOT(createPromptWindowCube()));

	for (i = 0; i < _delete_buttons.size(); ++i) {
		QObject::connect(_delete_buttons[i], SIGNAL(clicked()), _delete_buttons[i], SLOT(action()));
		QObject::connect(_delete_buttons[i], SIGNAL(act(QLabel*)), this, SLOT(deleteObject(QLabel*)));
		QObject::connect(_modify_buttons[i], SIGNAL(clicked()), _modify_buttons[i], SLOT(action()));
		QObject::connect(_modify_buttons[i], SIGNAL(act(QLabel*)), this, SLOT(modifyObject(QLabel*)));
	}
}

void mainWindow::readInput(QVBoxLayout* column_layout, std::vector<QHBoxLayout*> rows_layout, std::vector<QGroupBox*>& rows) {
	
	char object, light;
	double x, y, z, rad, r, g, b, i;

	std::string wd = getwd();
	std::string input_path = wd + "ray_tracer/input";
	std::string input_file = input_path.c_str();
	std::ifstream ifile(input_file, std::ifstream::in);

	std::stringstream sstr;
	sstr << std::fixed << std::setprecision(2); 

	ifile >> x;

	while ((ifile >> object) && !ifile.eof()) {
		sstr.str(std::string());
		ifile >> light >> x >> y >> z >> rad >> r >> g >> b;
		if (object == 'S') {
			if (light == 'R') {
				_object_labels.push_back(new QLabel());
				sstr << "S R " << x << " " << y << " " << z << " " << rad << " " << std::setprecision(3) << r << " " << g << " " << b << std::setprecision(2);
			} else {
				ifile >> i;
				_object_labels.push_back(new QLabel());
				sstr << "S T " << x << " " << y << " " << z << " " << rad << " " << std::setprecision(3) << r << " " << g << " " << b << " " << std::setprecision(2) << i;
			}
		} else if (object == 'C') {
			if (light == 'R') {
				_object_labels.push_back(new QLabel());
				sstr << "C R " << x << " " << y << " " << z << " " << rad << " " << std::setprecision(3) << r << " " << g << " " << b << std::setprecision(2);
			} else {
				ifile >> i;
				_object_labels.push_back(new QLabel());
				sstr << "C T " << x << " " << y << " " << z << " " << rad << " " << std::setprecision(3) << r << " " << g << " " << b << " " << std::setprecision(2) << i;
			}
		}

		_object_labels[_object_labels.size()-1]->setText(QString::fromStdString(sstr.str()));
		_object_labels[_object_labels.size()-1]->setFont(QFont("Lato", 18));
		_object_labels[_object_labels.size()-1]->setMargin(15);
		_modify_buttons.push_back(new objectButton(tr("Modify"), _object_labels[_object_labels.size()-1]));
		_delete_buttons.push_back(new objectButton(tr("Delete"), _object_labels[_object_labels.size()-1]));

		rows_layout.push_back(new QHBoxLayout);
		rows_layout[rows_layout.size()-1]->addWidget(_object_labels[_object_labels.size()-1]);
		rows_layout[rows_layout.size()-1]->addWidget(_modify_buttons[_modify_buttons.size()-1]);
		rows_layout[rows_layout.size()-1]->addWidget(_delete_buttons[_delete_buttons.size()-1]);
		rows_layout[rows_layout.size()-1]->setStretchFactor(_object_labels[_object_labels.size()-1], 8);
		rows_layout[rows_layout.size()-1]->setStretchFactor(_modify_buttons[_modify_buttons.size()-1], 1);
		rows_layout[rows_layout.size()-1]->setStretchFactor(_delete_buttons[_delete_buttons.size()-1], 1);

		rows.push_back(new QGroupBox);
		rows[rows.size()-1]->setLayout(rows_layout[rows_layout.size()-1]);

		column_layout->addWidget(rows[rows.size()-1]);
	}
	ifile.close();
}

void mainWindow::clearInput() {
	_object_labels.clear();
	_modify_buttons.clear();
	_delete_buttons.clear();
	_rows.clear();
	_rows_layout.clear();

	QLayoutItem *item;
	while ((item = _column_layout->takeAt(1))) {
		delete item->widget();
	}
	delete item;
}

void mainWindow::updateObjectButtonsConnections() const {

	unsigned int i;
	
	for (i = 0; i < _delete_buttons.size(); ++i) {
		QObject::connect(_delete_buttons[i], SIGNAL(clicked()), _delete_buttons[i], SLOT(action()));
		QObject::connect(_delete_buttons[i], SIGNAL(act(QLabel*)), this, SLOT(deleteObject(QLabel*)));
		QObject::connect(_modify_buttons[i], SIGNAL(clicked()), _modify_buttons[i], SLOT(action()));
		QObject::connect(_modify_buttons[i], SIGNAL(act(QLabel*)), this, SLOT(modifyObject(QLabel*)));
	}
}

// public slots

void mainWindow::executeRayTracer() {

	int pid = fork();

	if (pid < 0) {
		return;
	}

	if (pid) {

		QWidget* w = new QWidget;
		QPushButton* b = new QPushButton(tr("Done"));
		b->setFont(QFont("Lato", 22, QFont::Bold));
		QObject::connect(b, SIGNAL(clicked()), w, SLOT(close()));
		QHBoxLayout* layout = new QHBoxLayout(w);
		layout->addWidget(b);
		w->setWindowTitle("Program is running. Please wait...");
		w->resize(400, 150);
		w->setLayout(layout);
		w->show();

		waitpid(pid, NULL, 0);

	} else {

		QCoreApplication::processEvents();
		std::string wd = getwd();
		std::string input_path = wd + "ray_tracer/Ray_tracer";
		execl(input_path.c_str(), input_path.c_str(), NULL);

		exit(0);
	}
}

void mainWindow::viewImage() {

	std::string wd = getwd();
	std::string input_path = "eog " + wd + "ray_tracer/image.ppm";
	int test = std::system(input_path.c_str());
	if (test != 0) {
		std::cout << "Error in mainWindow.cpp:viewImage: test return != 0)" << std::endl;
		exit(test);
	}

	/*
	int pid = fork();

	if (pid < 0) {
		return;
	}

	if (pid) {
		waitpid(pid, NULL, 0);
	} else {
		std::string wd = getwd();
		std::string input_path = "eog " + wd + "ray_tracer/image.ppm";
		execl("usr/bin/eog", "eog", input_path.c_str(), NULL);
		exit(0);
	}
	*/
}

void mainWindow::setRes(int res) {

	std::string wd = getwd();
	std::string input_path = wd + "ray_tracer/input";
	std::string output_path = wd + "ray_tracer/input.tmp";
	const char* input_file(input_path.c_str());
	const char* output_file(output_path.c_str());
	std::ifstream ifile(input_file);
	std::ofstream ofile(output_file);
	std::string line;
	bool changed = false;

	while (std::getline(ifile, line)) {
		if (changed == false) {
			ofile << res << std::endl;
			changed = true;
		} else {
			ofile << line << std::endl;
		}
	}

	ifile.close();
	ofile.close();
	std::remove(input_file);
	std::rename(output_file, input_file);
}

void mainWindow::deleteObject(QLabel* l) {
	
	std::string wd = getwd();
	std::string input_path = wd + "ray_tracer/input";
	std::string output_path = wd + "ray_tracer/input.tmp";
	const char* input_file(input_path.c_str());
	const char* output_file(output_path.c_str());
	std::ifstream ifile(input_file);
	std::ofstream ofile(output_file);
	char object1,light1;
	unsigned int res;

	ifile >> res;
	ofile << res << std::endl;

	while (ifile >> object1) {
		ifile >> light1;
		std::stringstream* s = new std::stringstream;
		*s << l->text().toStdString();
		if (light1 == 'R') {
			isEqualR(ofile, ifile, *s, object1, light1);
		} else {
			isEqualT(ofile, ifile, *s, object1, light1);
		}
		delete s;
	}

	ifile.close();
	ofile.close();
	std::remove(input_file);
	std::rename(output_file, input_file);

	clearInput();
	readInput(_column_layout, _rows_layout, _rows);
	updateObjectButtonsConnections();
}

void mainWindow::modifyObject(QLabel* l) {
	
	char type = (l->text().toStdString())[0];

	if (type == 'S') {
		createPromptWindowSphere("modify", l);
	} else if (type == 'C') {
		createPromptWindowCube("modify", l);
	}
}

void mainWindow::confirmModifyObject(QLabel* l, char object, char light, double x, double y, double z, double rad, unsigned int r_int, unsigned int g_int, unsigned int b_int, int i) {

	std::string wd = getwd();
	std::string input_path = wd + "ray_tracer/input";
	std::string output_path = wd + "ray_tracer/input.tmp";
	const char* input_file(input_path.c_str());
	const char* output_file(output_path.c_str());
	std::ifstream ifile(input_file);
	std::ofstream ofile(output_file);
	char object1,light1;
	unsigned int res;

	double r = round((r_int/255.) * 1000.) / 1000.;
	double g = round((g_int/255.) * 1000.) / 1000.;
	double b = round((b_int/255.) * 1000.) / 1000.;

	ifile >> res;
	ofile << res << std::endl;

	while (ifile >> object1) {
		ifile >> light1;
		std::stringstream* s = new std::stringstream;
		*s << l->text().toStdString();
		if (light1 == 'R') {
			if (isEqualR(ofile, ifile, *s, object1, light1)) {
				if (light == 'R') {
					ofile << object << " " << light << " " << x << " " << y << " " << z << " " << rad << " " << r << " " << g << " " << b << std::endl;
				} else {
					ofile << object << " " << light << " " << x << " " << y << " " << z << " " << rad << " " << r << " " << g << " " << b <<  " " << i << std::endl;
				}
			}
		} else {
			if (isEqualT(ofile, ifile, *s, object1, light1)) {
				if (light == 'R') {
					ofile << object << " " << light << " " << x << " " << y << " " << z << " " << rad << " " << r << " " << g << " " << b << std::endl;
				} else {
					ofile << object << " " << light << " " << x << " " << y << " " << z << " " << rad << " " << r << " " << g << " " << b <<  " " << i << std::endl;
				}
			}
		}
		delete s;
	}

	ifile.close();
	ofile.close();
	std::remove(input_file);
	std::rename(output_file, input_file);

	clearInput();
	readInput(_column_layout, _rows_layout, _rows);
	updateObjectButtonsConnections();
}

void mainWindow::createPromptWindowSphere(std::string type, QLabel* l, QWidget* parent) {

	promptWindow* w = new promptWindowSphere(this, type, l, parent);
	w->show();
	w->initializeConnections();
}

void mainWindow::createPromptWindowCube(std::string type, QLabel* l, QWidget* parent) {

	promptWindow* w = new promptWindowCube(this, type, l, parent);
	w->show();
	w->initializeConnections();
}
