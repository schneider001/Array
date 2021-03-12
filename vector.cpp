#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include "D:\Txlib\TX\TXlib.h"


int depth = 0;


class Depth {

public:
	Depth()
	{
		depth++;
	}

	~Depth()
	{
		depth--;
	}
};

template < typename T >

class Vector {
public:

	int size_;
	T *data_;

	T& operator [] (int n) {
		assert(0 <= n && n < size_);
		return data_[n];
	}


	Vector& operator = (const Vector& that) {
		Depth dep;
        printf("%*s", depth * 10, "");
        printf("[%p] %s\n\n", this, "copy assignment");


		Vector temp = that;
		swap_(temp);
		return *this;
	}


	Vector& operator = (Vector&& that) {
		Depth dep;
        printf("%*s", depth * 10, "");
        printf("[%p] %s\n\n", this, "move assignment");


		swap_(that);
		return *this;
	}


	void swap_(Vector& that) {
		std::swap(data_, that.data_);
		std::swap(size_, that.size_);
	}


	Vector(int n) {
		Depth dep;
        printf("%*s", depth * 10, "");
        printf("[%p] %s\n\n", this, "constructor with parameters");


		assert(0 <= n);

		size_ = n;
		data_ = new T[size_];
	}


	Vector():
		size_(0),
		data_(nullptr)
	{
		Depth dep;
        printf("%*s", depth * 10, "");
        printf("[%p] %s\n\n", this, "default constructor");

	}


	Vector(const Vector& that):
		data_(new T[that.size_]),
		size_(that.size_)
		{
			Depth dep;
			printf("%*s", depth * 10, "");
			printf("[%p] %s\n\n", this, "copy constructor");


			std::copy(that.data_, that.data_ + that.size_, data_);
		}


	Vector(Vector&& that) {
		Depth dep;
        printf("%*s", depth * 10, "");
        printf("[%p] %s\n\n", this, "move constructor");


		Vector();
		swap_(that);
	}


	~Vector() {
		Depth dep;
        printf("%*s", depth * 10, "");
        printf("[%p] %s\n\n", this, "destructor");


		delete[] data_;
	}
};


Vector<int> evil_function(Vector<int> that);

Vector<double> evil_function(Vector<double> that);




int main() {
	Vector<double> a(1000);
	for (int i = 0; i < 1000; i++) {
		a[i] = i;
	}

	Vector<double> b = a;
	b = evil_function(b);
}



Vector<int> evil_function(Vector<int> that) {
	that[10] = 12;
	return that;
}

Vector<double> evil_function(Vector<double> that) {
	that[10] = 12;
	return that;
}









