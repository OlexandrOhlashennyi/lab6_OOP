/*Створити шаблонний клас – послідовність абстрактних символів. 
Тип елементів послідовності (цілі числа, дійсні числа, символи
або символьні рядки) визначається параметром шаблона. Передбачити
функції для виконання таких операцій: введення елементів у послідовність,
відношення < , > , == , != , виведення послідовності на екран.*/

#include <iostream>
#include <cstdlib>
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
	system("chcp 1251"); system("cls");
	sequence<int> s1;
	sequence<int> s2;
	sequence<int> s3;
	
	cout << "Введіть першу послідовність(q -- кінець):\n";
	cin >> s1;
	cout << "Введіть другу послідовність(q -- кінець):\n";
	cin >> s2;

	cout << "\n\tПерша послідовність:\n";
	cout << s1 << endl;
	cout << "\n\tДруга послідовність:\n";
	cout << s2 << endl;

	cout << "\nперша > друга?\n" << ((s1 > s2) ? "Так" : "Ні") << endl;
	cout << "\nперша < друга?\n" << ((s1 < s2) ? "Так" : "Ні") << endl;
	cout << "\nперша == друга?\n" << ((s1 == s2) ? "Так" : "Ні") << endl;
	cout << "\nперша != друга?\n" << ((s1 != s2) ? "Так" : "Ні") << endl;

	s3 = s1 + s2;
	cout << "\nперша + друга:\n" << s3 << endl;

	return 0;
}

/*
1
2
3
4
5
q
6
7
8
9
q
*/

template <class T>
sequence<T>::sequence(int size) {
	data = new T[this->size = size];
	for (int i = 0; i < size; i++)
		data[i] = T(0);
}

template <class T>
sequence<T>::~sequence() {
	delete[] data;
	data = NULL;
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
	is.clear();
	is.seekg(0);
	T temp;
	while (is >> temp)
		s.add(temp);
	return is;
}
