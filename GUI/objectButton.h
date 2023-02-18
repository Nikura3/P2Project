#ifndef OBJECT_BUTTON_H
#define OBJECT_BUTTON_H

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QString>

class objectButton : public QPushButton {

	Q_OBJECT

	public:
		objectButton(QLabel*, QWidget* = nullptr);
		objectButton(const QString&, QLabel*, QWidget* = nullptr);
		objectButton(const QIcon&, const QString&, QLabel*, QWidget* = nullptr);

		QLabel* _l;

	public slots:
		void action();

	signals:
		void act(QLabel*);
};

#endif
