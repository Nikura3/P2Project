#include "list.h"
#include "shape.h"

template <class T>
node<T>* list<T>::copy(node<T>* n) {

	if (n == nullptr) {
		return nullptr;
	}

	node<T>* aux = new node<T>(n->_info, copy(n->_next));

	return aux;
}

template <class T>
node<T>* list<T>::last(node<T>* n) {

	if (n == nullptr) {
		return nullptr;
	} else if (n->_next == nullptr) {
		return n;
	} else {
		return last(n->_next);
	}
}

template <class T>
list<T>::list(node<T>* n) : _first(n) {}

template <class T>
list<T>::list(const list& l) : _first(copy(l._first)) {}

template <class T>
list<T>::~list() {
	delete _first;
}
template <class T>
list<T>& list<T>::operator=(const list& l) {
	if (this != &l) {
		delete _first;
		_first = copy(l._first);
	}
	return *this;
}

template <class T>
void list<T>::append(const T& t) {

	node<T>* n = last(_first);
	if (n == nullptr) {
		_first = new node<T>(t, nullptr);
	} else {
		n->_next = new node<T>(t, nullptr);
	}
}

template class list<shape*>;
