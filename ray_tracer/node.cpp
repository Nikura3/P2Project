#include "node.h"
#include "shape.h"

template <class T>
node<T>::node(T t, node* n) : _info(t), _next(n) {}

template <class T>
node<T>::~node() {
	delete _next;
}

template class node<shape*>;
