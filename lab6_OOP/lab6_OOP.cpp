/*Створити шаблонний клас – послідовність абстрактних символів. 
Тип елементів послідовності (цілі числа, дійсні числа, символи
або символьні рядки) визначається параметром шаблона. Передбачити
функції для виконання таких операцій: введення елементів у послідовність,
відношення < , > , == , != , виведення послідовності на екран.*/

#include <iostream>
#include <string>

using namespace std;

template <class T>
class sequence {
private:
	T* data;
	int size;
public:
	sequence(int = 0);
	~sequence();
	void add(T new_e);
	int get_size() { return size; }
	T get_element(unsigned);
	sequence& operator+(sequence&);
	sequence& operator=(const sequence&);
	template <typename T>friend ostream& operator<<(ostream&, sequence<T>&);
	template <typename T> friend istream& operator>>(istream&, sequence<T>&);
	bool operator==(const sequence&);
	bool operator!=(const sequence&);
	bool operator<(sequence&);
	bool operator>(sequence&);
};

int main() {
	/*sequence<char*> s;
	s.add((char*)"1");
	s.add((char*)"2");
	s.add((char*)"3");
	s.add((char*)"4");
	s.add((char*)"4");
	s.add((char*)"4");
	sequence<char*> s2;
	s2.add((char*)"asd");
	s2.add((char*)"ase");
	s2.add((char*)"3");
	s2.add((char*)"454");*/

	sequence<int> s;
	s.add(1);
	s.add(2);
	s.add(4);
	s.add(4);
	s.add(4);
	s.add(4);
	sequence<int> s2;
	s2.add(8);
	s2.add(9);
	s2.add(10);
	s2.add(11);

	cout << s2 << endl;
	cout << (s2 > s) << endl;
	s2 = s2 + s;
	cout << s2 << endl;
	cout << (s2 > s) << endl;
	cout << (s2 != s) << endl;

	return 0;
}

template <class T>
sequence<T>::sequence(int size) {
	data = new T[this->size = size];
	for (int i = 0; i < size; i++)
		data[i] = T(0);
}

template <class T>
sequence<T>::~sequence() {
	delete[] data;
}

template<class T>
void sequence<T>::add(T new_e)
{
	T* temp = new T[++size];
	try {
		copy(data, data + size, temp);
	}
	catch (...) {
		delete[] temp;
		throw;
	}
	delete[] data;
	data = temp;
	data[size - 1] = new_e;
}

template<class T>
T sequence<T>::get_element(unsigned index)
{
	if (index >= size)
		return data[size - 1];
	return data[index];
}

template<class T>
sequence<T>& sequence<T>::operator+(sequence<T>& s)
{
	T* temp = new T[this->size+s.size];
	try {
		copy(data, data + this->size, temp);
		copy(s.data, s.data + s.size, temp+size);
	}
	catch (...) {
		delete[] temp;
		throw;
	}
	delete[] data;
	data = temp;
	size += s.size;

	/*int i = 0, j = 0;
	while (i < this->size && j < s.size) {
		this->data[i++] += s.data[j++];
	}*/
	return *this;
}

template<class T>
sequence<T>& sequence<T>::operator=(const sequence<T>& s)
{
	T* temp = new T[s.size];
	copy(s.data, s.data + s.size, temp);
	delete[] this->data;
	this->data = new T[s.size];
	copy(temp, temp + s.size, this->data);
	this->size = s.size;
	return *this;
}

template<class T>
bool sequence<T>::operator==(const sequence<T>& s)
{
	if(this->size != s.size)
		return false;
	for (int i = 0; i < this->size; i++) {
		if(this->data[i] != s.data[i])
			return false;
	}
	return true;
}

template<class T>
bool sequence<T>::operator!=(const sequence<T>& s)
{
	if (this->size != s.size)
		return true;
	for (int i = 0; i < this->size; i++) {
		if (this->data[i] != s.data[i])
			return true;
	}
	return false;
}

template<class T>
bool sequence<T>::operator<(sequence<T>& s)
{
	return (this->size < s.size);
}

template<class T>
bool sequence<T>::operator>(sequence<T>& s)
{
	return (this->size > s.size);
}


template <typename T>
ostream& operator<<(ostream& os, sequence<T>& s)
{
	copy(s.data, s.data+s.size, ostream_iterator<T>(os, "  "));
	return os;
}

template<typename T>
istream& operator>>(istream& is, sequence<T>& s)
{
	cout << "Enter " << s.size << " elements\n";
	for (int i = 0; i < s.size; i++)
		is >> s.data[i];
	return is;
}
