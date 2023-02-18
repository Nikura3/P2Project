#ifndef SMART_POINTER
#define SMART_POINTER

template <class T>
class smartP {

	public:
		T* _ptr;
		smartP(T*);
		smartP(const smartP&);
		~smartP();
		smartP& operator=(const smartP&);
		T& operator*() const;
		T* operator->() const;
		operator T*();
		operator T*() const;
};

#endif
