#pragma once
#include<cassert>

// A general Class Array, which can change size according to the number of elements.
template <class T>
class Array
{
public:
	Array(int sz = 50);
	Array(const Array<T>& a);					// Copy constructor
	~Array();

	Array<T>& operator = (const Array<T>& rhs); // Overloading operator =
	T& operator [] (int i);						// Overloading operator []
	const T& operator [] (int i) const;
	operator T* ();								// Overloading operator T* which used to transit pointer arguments when call a function.
	operator const T* ()const;
	int getSize() const;
	void resize(int sz);
private:
	T* list;
	int size;

};


// The template class's function must define in the same file of the class.
template <class T>
Array<T>::Array(int sz) {
	assert(sz >= 0);
	size = sz;
	list = new T[size];
}
template <class T>
Array<T>::~Array() {
	delete[] list;
}

// Copy constructor
template <class T>
Array<T>::Array(const Array<T>& a) {
	int i = 0;
	size = a.size;
	list = new T[a.size];
	for (T& e : a.list) {
		list[i] = e;
		i++;
	}
}

// Overloading operator =
template <class T>
Array<T>& Array<T>::operator =(const Array<T>& a) {
	if (a.size != size)
	{
		delete[]list;
		size = a.size;
		list = new T[size];
	}
	int i = 0;
	for (T& e : a.list) {
		list[i] = e;
		i++;
	}
}

// Overloading operator [], provide random access to the array. e.g. A[5].
template <class T>
T& Array<T>::operator [](int i) {
	assert(i >= 0 && i < size);
	return list[i];

}
template <class T>
const T& Array<T>::operator [](int i) const {
	assert(i >= 0 && i < size);
	return list[i];

}

// Overloading operator T*.
template<class T>
Array<T>::operator T* () {
	return list;
}
template<class T>
Array<T>::operator const T* () const {
	return list;
}
template<class T>
int Array<T>::getSize()const {
	return size;
}

// According to the argument sz to change the size of the Array.
template<class T>
void Array<T>::resize(int sz) {
	
	assert(sz >= 0);
	if (sz == size)
	{
		return;
	}
	T* newlist = new T[sz];
	int n = (sz < size) ? sz : size;
	for (int i = 0; i < n; i++) {
		newlist[i] = list[i];
	}
	delete[] list;
	list = newlist;
	size = sz;
	return;
}