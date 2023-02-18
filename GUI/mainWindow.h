#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <sstream>
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
#include "objectButton.h"

class mainWindow : public QWidget {

	Q_OBJECT

	private:
		int getRes() const;
		bool isEqualR(std::ofstream&, std::ifstream&, std::stringstream&, char, char) const;
		bool isEqualT(std::ofstream&, std::ifstream&, std::stringstream&, char, char) const;

	public:
		mainWindow(QWidget* = nullptr);

		QPushButton* _run;
		QPushButton* _view;
		QPushButton* _quit;

		QPushButton* _create_sphere;
		QPushButton* _create_cube;
		std::vector<objectButton*> _modify_buttons;
		std::vector<objectButton*> _delete_buttons;

		QLabel* _objects_list;
		std::vector<QLabel*> _object_labels;

		QGroupBox* _top_panel;
		QGroupBox* _bottom_panel;
		QGroupBox* _left_panel;
		QGroupBox* _right_panel;
		std::vector<QGroupBox*> _rows;

		QScrollArea* _scroll_area;

		QVBoxLayout* _main_layout;
		QHBoxLayout* _top_layout;
		QVBoxLayout* _left_layout;
		QVBoxLayout* _column_layout;
		std::vector<QHBoxLayout*> _rows_layout;
		QHBoxLayout* _bottom_layout;

		QLabel* _res_label;
		QLCDNumber* _res;
		QSlider* _slider;

		void initializeConnections(QApplication*) const;
		void readInput(QVBoxLayout*, std::vector<QHBoxLayout*>, std::vector<QGroupBox*>&);
		void clearInput();
		void updateObjectButtonsConnections() const;

	public slots:
		void executeRayTracer();
		void viewImage();
		void setRes(int);
		void deleteObject(QLabel*);
		void modifyObject(QLabel*);
		void confirmModifyObject(QLabel*, char, char, double, double, double, double, unsigned int, unsigned int, unsigned int, int = 10);
		void createPromptWindowSphere(std::string = "new", QLabel* = nullptr, QWidget* = nullptr);
		void createPromptWindowCube(std::string = "new", QLabel* = nullptr, QWidget* = nullptr);
};

#endif
