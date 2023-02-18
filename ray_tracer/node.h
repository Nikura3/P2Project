#ifndef NODE_H
#define NODE_H

#include "smartP.h"
#include "shape.h"

template <class T>
class smartP;

template <class T>
class node {
	public:
		smartP<shape> _info;
		node<T>* _next;
		node(T = nullptr, node* = nullptr);
		~node();
};

#endif
