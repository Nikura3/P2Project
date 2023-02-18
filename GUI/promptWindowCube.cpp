#include "promptWindowCube.h"

std::string getwd2() {

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

promptWindowCube::promptWindowCube(mainWindow* main, std::string type, QLabel* l, QWidget* parent) : promptWindow(main, type, l, parent) {

	_size_panel.push_back(new QGroupBox);
	_size_layout.push_back(new QHBoxLayout);

	_edge_label = new QLabel;
	_edge_label->setText("Edge:");
	_edge_label->setFont(QFont("Lato", 18));
	_edge_label->setMargin(15);

	_edge = new QDoubleSpinBox;
	_edge->setRange(0, 500);
	_edge->setDecimals(2);
	_edge->setSingleStep(0.01);

	_size_layout[0]->addWidget(_edge_label);
	_size_layout[0]->addWidget(_edge);

	for (unsigned int i = 0; i < _size_panel.size(); ++i) {
		_size_panel[i]->setLayout(_size_layout[i]);
	}

	if (_type == "new") {
		setWindowTitle("Create Cube");
	} else {
		setWindowTitle("Modify Cube");
		initializeValues();
	}

	updateLayout();
}

// public

void promptWindowCube::initializeValues() {
	
	std::stringstream s;
	s << _modify_label->text().toStdString();

	char c;
	double x;

	s >> c;

	s >> c;
	if (c == 'R') {
		_light_realistic->setChecked(true);
	} else {
		_light_toon->setChecked(true);
	}
	s >> x;
	_centerpoint_x->setValue(x);
	s >> x;
	_centerpoint_y->setValue(x);
	s >> x;
	_centerpoint_z->setValue(x);
	s >> x;
	_edge->setValue(x);
	s >> x;
	_color_r->setValue(x * 255);
	s >> x;
	_color_g->setValue(x * 255);
	s >> x;
	_color_b->setValue(x * 255);
}

void promptWindowCube::initializeConnections() const {

	if (_type == "new") {
		QObject::connect(_create, SIGNAL(clicked()), this, SLOT(action()));
	} else {
		QObject::connect(_create, SIGNAL(clicked()), this, SLOT(modify()));
	}
	QObject::connect(_cancel, SIGNAL(clicked()), this, SLOT(exit()));

	if (_type == "new") {
		QObject::connect(this, SIGNAL(act(char, double, double, double, double, unsigned int, unsigned int, unsigned int, int)), this, SLOT(createObject(char, double, double, double, double, unsigned int, unsigned int, unsigned int, int)));
		QObject::connect(this, SIGNAL(act(char, double, double, double, double, unsigned int, unsigned int, unsigned int, int)), this, SLOT(exit()));
	} else {
		QObject::connect(this, SIGNAL(modifySignal(QLabel*, char, char, double, double, double, double, unsigned int, unsigned int, unsigned int, int)), _main, SLOT(confirmModifyObject(QLabel*, char, char, double, double, double, double, unsigned int, unsigned int, unsigned int, int)));
		QObject::connect(this, SIGNAL(modifySignal(QLabel*, char, char, double, double, double, double, unsigned int, unsigned int, unsigned int, int)), this, SLOT(exit()));
	}
	QObject::connect(this, SIGNAL(error()), this, SLOT(printErrorMessage()));
}

// public slots

void promptWindowCube::createObject(char light, double x, double y, double z, double rad, unsigned int r_int, unsigned int g_int, unsigned int b_int, int i) {

	std::string wd = getwd2();
	std::string output_path = wd + "ray_tracer/input";
	const char* output_file(output_path.c_str());
	std::ofstream ofile(output_file, std::ios_base::app | std::ios_base::out);

	double r = round((r_int/255.) * 1000.) / 1000.;
	double g = round((g_int/255.) * 1000.) / 1000.;
	double b = round((b_int/255.) * 1000.) / 1000.;

	ofile << "C " << light << " " << x << " " << y << " " << z << " " << rad << " " << r << " " << g << " " << b;

	if (light == 'T') {
		ofile << " " << i;
	}

	ofile << std::endl;

	ofile.close();

	_main->clearInput();
	_main->readInput(_main->_column_layout, _main->_rows_layout, _main->_rows);
	_main->updateObjectButtonsConnections();
}

void promptWindowCube::printErrorMessage() {
	QMessageBox* w = new QMessageBox;
	w->setText("Error: choose what kind of lightning should be used for this object");
	w->setWindowTitle("Info");
	w->show();
}

// signals

void promptWindowCube::action() {
	if (_light_realistic->isChecked()) {
		emit act('R', _centerpoint_x->value(), _centerpoint_y->value(), _centerpoint_z->value(), _edge->value(), _color_r->value(), _color_g->value(), _color_b->value());
	} else if (_light_toon->isChecked()) {
		emit act('T', _centerpoint_x->value(), _centerpoint_y->value(), _centerpoint_z->value(), _edge->value(), _color_r->value(), _color_g->value(), _color_b->value());
	} else {
		emit error();
	}
}

void promptWindowCube::modify() {
	if (_light_realistic->isChecked()) {
		emit modifySignal(_modify_label, 'C', 'R', _centerpoint_x->value(), _centerpoint_y->value(), _centerpoint_z->value(), _edge->value(), _color_r->value(), _color_g->value(), _color_b->value());
	} else if (_light_toon->isChecked()) {
		emit modifySignal(_modify_label, 'C', 'T', _centerpoint_x->value(), _centerpoint_y->value(), _centerpoint_z->value(), _edge->value(), _color_r->value(), _color_g->value(), _color_b->value());
	} else {
		emit error();
	}
}
