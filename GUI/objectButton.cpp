#include "objectButton.h"

objectButton::objectButton(QLabel* l, QWidget* parent) : QPushButton(parent), _l(l) {}
objectButton::objectButton(const QString& text, QLabel* l, QWidget* parent) : QPushButton(text, parent), _l(l) {}
objectButton::objectButton(const QIcon& icon, const QString& text, QLabel* l, QWidget* parent) : QPushButton(icon, text, parent), _l(l) {}

void objectButton::action() {
	emit act(_l);
}
