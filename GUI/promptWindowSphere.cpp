#include "promptWindowSphere.h"

std::string getwd1() {

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

promptWindowSphere::promptWindowSphere(mainWindow* main, std::string type, QLabel* l, QWidget* parent) : promptWindow(main, type, l, parent) {

	_size_panel.push_back(new QGroupBox);
	_size_layout.push_back(new QHBoxLayout);

	_radius_label = new QLabel;
	_radius_label->setText("Radius:");
	_radius_label->setFont(QFont("Lato", 18));
	_radius_label->setMargin(15);

	_radius = new QDoubleSpinBox;
	_radius->setRange(0, 500);
	_radius->setDecimals(2);
	_radius->setSingleStep(0.01);

	_size_layout[0]->addWidget(_radius_label);
	_size_layout[0]->addWidget(_radius);

	for (unsigned int i = 0; i < _size_panel.size(); ++i) {
		_size_panel[i]->setLayout(_size_layout[i]);
	}

	if (_type == "new") {
		setWindowTitle("Create Sphere");
	} else {
		setWindowTitle("Modify Sphere");
		initializeValues();
	}

	updateLayout();
}

// public

void promptWindowSphere::initializeValues() {
	
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
	_radius->setValue(x);
	s >> x;
	_color_r->setValue(x * 255);
	s >> x;                    
	_color_g->setValue(x * 255);
	s >> x;                    
	_color_b->setValue(x * 255);
}

void promptWindowSphere::initializeConnections() const {

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

void promptWindowSphere::createObject(char light, double x, double y, double z, double rad, unsigned int r_int, unsigned int g_int, unsigned int b_int, int i) {

	std::string wd = getwd1();
	std::string output_path = wd + "ray_tracer/input";
	const char* output_file(output_path.c_str());
	std::ofstream ofile(output_file, std::ios_base::app | std::ios_base::out);

	double r = round((r_int/255.) * 1000.) / 1000.;
	double g = round((g_int/255.) * 1000.) / 1000.;
	double b = round((b_int/255.) * 1000.) / 1000.;

	ofile << "S " << light << " " << x << " " << y << " " << z << " " << rad << " " << r << " " << g << " " << b;

	if (light == 'T') {
		ofile << " " << i;
	}

	ofile << std::endl;

	ofile.close();

	_main->clearInput();
	_main->readInput(_main->_column_layout, _main->_rows_layout, _main->_rows);
	_main->updateObjectButtonsConnections();
}

void promptWindowSphere::printErrorMessage() {
	QMessageBox* w = new QMessageBox;
	w->setText("Error: choose what kind of lightning should be used for this object");
	w->setWindowTitle("Info");
	w->show();
}

// emit signals

void promptWindowSphere::action() {
	if (_light_realistic->isChecked()) {
		emit act('R', _centerpoint_x->value(), _centerpoint_y->value(), _centerpoint_z->value(), _radius->value(), _color_r->value(), _color_g->value(), _color_b->value());
	} else if (_light_toon->isChecked()) {
		emit act('T', _centerpoint_x->value(), _centerpoint_y->value(), _centerpoint_z->value(), _radius->value(), _color_r->value(), _color_g->value(), _color_b->value());
	} else {
		emit error();
	}
}

void promptWindowSphere::modify() {
	if (_light_realistic->isChecked()) {
		emit modifySignal(_modify_label, 'S', 'R', _centerpoint_x->value(), _centerpoint_y->value(), _centerpoint_z->value(), _radius->value(), _color_r->value(), _color_g->value(), _color_b->value());
	} else if (_light_toon->isChecked()) {
		emit modifySignal(_modify_label, 'S', 'T', _centerpoint_x->value(), _centerpoint_y->value(), _centerpoint_z->value(), _radius->value(), _color_r->value(), _color_g->value(), _color_b->value());
	} else {
		emit error();
	}
}
