#ifndef LIST_H
#define LIST_H

#include "node.h"
#include "smartP.h"

template <class T>
class list {

	private:
		node<T>* _first;

		static node<T>* copy(node<T>*);
		static node<T>* last(node<T>*);

	public:
		list(node<T>* = nullptr);
		list(const list&);
		~list();

		list& operator=(const list&);
		void append(const T&);

		class const_iterator {
			friend class list<T>;
			private:
				node<T>* _ptr;
				bool _past_the_end;
				const_iterator(node<T>* p, bool pte = false): _ptr(p), _past_the_end(pte) {}	// conversione node* => const_iterator
			public:
				const_iterator(): _ptr(nullptr), _past_the_end(false) {}

				const T& operator*() const {
					return (_ptr->_info)._ptr;
				}
	 
				const T* operator->() const {
					return &((_ptr->_info)._ptr);
				}
	 
				const_iterator& operator++() {

					if (_ptr != nullptr && !_past_the_end) {
						if (_ptr->_next == nullptr) {
							++_ptr;
							_past_the_end = true;
						} else {
							_ptr = _ptr->_next;
						}
					}

					return *this;
				}
	 
				bool operator==(const const_iterator& cit) const {
					return _ptr == cit._ptr;
				}

				bool operator!=(const const_iterator& cit) const {
					return _ptr != cit._ptr;
				}
		};

		const_iterator begin() const {
			return static_cast<node<T>*>(_first);
		}
	  
		const_iterator end() const {

			if (_first == nullptr) {
				return nullptr;
			} else {
				return const_iterator(last(_first)+1, true);
			}
		}
};

#endif
