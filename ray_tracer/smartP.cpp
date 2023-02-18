#include "smartP.h"
#include "node.h"
#include "shape.h"

template <class T>
smartP<T>::smartP(T* p) : _ptr(p->clone()) {}

template <class T>
smartP<T>::smartP(const smartP& p) : _ptr(p._ptr->clone()) {}

template <class T>
smartP<T>::~smartP() {
	delete _ptr;
}

template <class T>
smartP<T>& smartP<T>::operator=(const smartP& p) {
    if (this != &p) {
		delete _ptr;
		_ptr = p._ptr->clone();
	}
	return *this;
}

template <class T>
T& smartP<T>::operator*() const {
	return *_ptr;
}

template <class T>
T* smartP<T>::operator->() const {
	return _ptr;
}

template <class T>
smartP<T>::operator T*() {
	return _ptr;
}

template <class T>
smartP<T>::operator T*() const {
	return _ptr;
}

template class smartP<shape>;
