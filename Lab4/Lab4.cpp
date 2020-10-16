/*На основе разработанной иерархии классов, реализованной во второй
лабораторной работе, реализовать программу работы с данными, используя
потоки ввода-вывода. Реализовать функций добавления, удаления,
редактирования и просмотра данных, поиска данных по необходимым
параметрам.*/
#include <iostream>
#include <Windows.h>
#include <vector>
#include <iomanip>
#include <fstream>

#define red "Красный"
#define yellow "Желтый"
#define pink "Розовый"

#define fresh "Свежий"
#define middle "Средней_свежести"
#define old "Старый"

#define rose "Роза"
#define tupil "Тюльпан"
#define iris "Ирис"
#define lily "Лилия"

using namespace std;

int menu() {
	int i;
	cout << "Выберите: " << endl;
	cout << "1. Добавить цветок в букет" << endl;
	cout << "2. Удалить последний добавленный цветок" << endl;
	cout << "3. Вывести данные о цветах в букете" << endl;
	cout << "4. Редактировать данные о цветах в букете" << endl;
	cout << "5. Посчитать цену всего букета" << endl;
	cout << "6. Найти информацию о цветке из букета" << endl;
	cout << "7. 'Очистить' букет" << endl;
	cout << "0. Выйти" << endl;
	cin >> i;
	return i;
}

string setFreshness() {
	int i;
	cout << "Выберите свежесть:" << endl;
	cout << "1. Свежий" << endl;
	cout << "2. Средней свежести" << endl;
	cout << "3. Старый" << endl;
	cin >> i;
	switch (i)
	{
	case 1:
		return fresh;
	case 2:
		return middle;
	case 3:
		return old;
	default:
		break;
	}
	return middle;
}

int setCount() {
	int count;
	cout << "Введите количество" << endl;
	cin >> count;
	return count;
}

string setColor() {
	int i;
	cout << "Выберите цвет:" << endl;
	cout << "1. Красный" << endl;
	cout << "2. Желтый" << endl;
	cout << "3. Розовый" << endl;
	cin >> i;
	switch (i)
	{
	case 1:
		return red;
	case 2:
		return yellow;
	case 3:
		return pink;
	default:
		break;
	}
	return red;
}

int menuFlower() {
	int i;
	cout << "1. Роза" << endl;
	cout << "2. Тюльпан" << endl;
	cout << "3. Лилия" << endl;
	cout << "4. Ирис" << endl;
	cout << "0. Назад" << endl;
	cin >> i;
	return i;
}

#pragma region Flowers

class Flower {
protected:
	double price;
	string Freshness, color, name;
	int count;
public:
	Flower() { }
	void setter(string, string, string, int, double);
	double getPrice() {	return price; }
	void printInfo() {
		cout << setw(7) << name << setw(10) << color << setw(20) << Freshness << setw(5) << count << endl;
	}
	virtual ~Flower() { }
	string getName() { return name; }
	string getFreshness() { return Freshness; }
	string getColor() { return color; }
	int getCount() { return count; }
};


void Flower::setter(string name, string Freshness, string color, int count, double price) {
	this->name = name;
	this->Freshness = Freshness;
	this->color = color;
	this->count = count;
	this->price = price;
}

class Rose : public Flower {

public:
	Rose() { }
	Rose(string, string, int);
	double getPrice();
	~Rose() { }
};

Rose::Rose(string Freshness, string color, int count) {
	name = rose;
	this->Freshness = Freshness;
	this->color = color;
	this->count = count;
	this->price = getPrice();
}

double Rose::getPrice() {
	if (color == red)
		price = 4.5;
	else if (color == yellow)
		price = 5.5;
	else if (color == pink)
		price = 5;

	if (Freshness == fresh);
	else if (Freshness == middle)
		price -= 1;
	else if (Freshness == old)
		price -= 1.3;

	return price * count;
}

class Tupil : public Flower {

public:
	Tupil() {}
	Tupil(string, string, int);
	double getPrice();
	~Tupil() {	}
};

Tupil::Tupil(string Freshness, string color, int count) {
	name = tupil;
	this->Freshness = Freshness;
	this->color = color;
	this->count = count;
	this->price = getPrice();
}

double Tupil::getPrice() {
	if (color == red)
		price = 1.2;
	else if (color == yellow)
		price = 1.5;
	else if (color == pink)
		price = 1.3;

	if (Freshness == fresh);
	else if (Freshness == middle)
		price -= 0.3;
	else if (Freshness == old)
		price -= 0.5;

	return price * count;
}

class Lily : public Flower {

public:
	Lily() {}
	Lily(string, string, int);
	double getPrice();
	~Lily() { }
};

Lily::Lily(string Freshness, string color, int count) {
	name = lily;
	this->Freshness = Freshness;
	this->color = color;
	this->count = count;
	this->price = getPrice();
}

double Lily::getPrice() {
	if (color == red)
		price = 3.5;
	else if (color == yellow)
		price = 3;
	else if (color == pink)
		price = 4;

	if (Freshness == fresh);
	else if (Freshness == middle)
		price -= 0.7;
	else if (Freshness == old)
		price -= 1.2;

	return price * count;
}
class Iris : public Flower {

public:
	Iris() {}
	Iris(string, string, int);
	double getPrice();
	~Iris() {	}
};

Iris::Iris(string Freshness, string color, int count) {
	name = iris;
	this->Freshness = Freshness;
	this->color = color;
	this->count = count;
	this->price = getPrice();
}

double Iris::getPrice() {
	if (color == red)
		price = 1.5;
	else if (color == yellow)
		price = 1.7;
	else if (color == pink)
		price = 1.3;

	if (Freshness == fresh);
	else if (Freshness == middle)
		price -= 0.4;
	else if (Freshness == old)
		price -= 0.7;

	return price * count;
}
#pragma endregion

#pragma region Bouquet
template<class T>
class Bouquet {
	vector<T> bouquet;
	double Price = 0;
public:
	Bouquet() { }
	Bouquet(int);
	double getPrice();
	void addFlower(T);
	void deleteLast();
	void deleteAll();
	void printInfo();
	void edit(string);
	void search(string);
	~Bouquet() { }
};

template<class T>
double Bouquet<T>::getPrice() {
	Price = 0;
	ifstream File_Data;
	int count; double price; string name, color, freshness;
	File_Data.open("bouquet.txt");
	while (!File_Data.eof())
	{
		File_Data >> name >> color >> freshness >> count >> price;
		Price += price;
	}
	File_Data.close();
	return Price;
}

template<class T>
void Bouquet<T>::addFlower(T flower) {
	ofstream File_Data;
	File_Data.open("bouquet.txt", ios::app);
	File_Data << endl;
	File_Data << flower.getName() << "\t" << flower.getColor() << "\t" << flower.getFreshness() << "\t" << flower.getCount() << "\t" << flower.getPrice();
	File_Data.close();
}

template<class T>
void Bouquet<T>::deleteLast() {
	Flower flower;
	ifstream File_Data;
	int count; double price; string name, color, freshness;
	File_Data.open("bouquet.txt");
	while (!File_Data.eof())
	{
		File_Data >> name >> color >> freshness >> count >> price;
		flower.setter(name, freshness, color, count, price);
		bouquet.push_back(flower);
	}
	File_Data.close();
	bouquet.pop_back();
	ofstream File_Data1;
	File_Data1.open("bouquet.txt");
	for(size_t i = 0; i < bouquet.size(); i++)
		File_Data1 << bouquet[i].getName() << "\t" << bouquet[i].getColor() << "\t" << bouquet[i].getFreshness() << "\t" << bouquet[i].getCount() << "\t" << bouquet[i].getPrice();
	File_Data1.close();
}

template<class T>
void Bouquet<T>::deleteAll() {
	ofstream File_Data;
	File_Data.open("bouquet.txt");
	File_Data.close();
}

template<class T>
void Bouquet<T>::printInfo() {
	ifstream File_Data;
	int count; double price; string name, color, freshness;
	File_Data.open("bouquet.txt");
	while (!File_Data.eof())
	{
		File_Data >> name >> color >> freshness >> count >> price;
		cout << setw(7) << name << setw(10) << color << setw(20) << freshness << setw(5) << count << setw(5) << price <<endl;
	}
	File_Data.close();
}

template <class T>
void Bouquet<T>::edit(string Name) {
	ifstream File_Data;
	int count; double price; string name, color, freshness;
	File_Data.open("bouquet.txt");
	while (!File_Data.eof())
	{
		File_Data >> name >> color >> freshness >> count >> price;
		if (name == rose) {
			bouquet.push_back(Rose(freshness, color, count));
		}
		else if (name == tupil) {
			bouquet.push_back(Tupil(freshness, color, count));
		}
		else if (name == lily) {
			bouquet.push_back(Lily(freshness, color, count));
		}
		else if (name == iris) {
			bouquet.push_back(Iris(freshness, color, count));
		}
	}
	File_Data.close();

	ofstream File_Data1;
	File_Data1.open("bouquet.txt");
	for (size_t i = 0; i < bouquet.size(); i++)
	{
		if (bouquet[i].getName() == Name) {
			bouquet[i].setter(bouquet[i].getName(), setFreshness(), setColor(), setCount(), bouquet[i].getPrice());
		}
		File_Data1 << bouquet[i].getName() << "\t" << bouquet[i].getColor() << "\t" << bouquet[i].getFreshness() << "\t" << bouquet[i].getCount() << "\t" << bouquet[i].getPrice();
	}
	File_Data1.close();
}

template<class T>
void Bouquet<T>::search(string Name) {
	ifstream File_Data;
	int count; double price; string name, color, freshness;
	File_Data.open("bouquet.txt");
	while (!File_Data.eof())
	{
		File_Data >> name >> color >> freshness >> count >> price;
		if(name == Name)
			cout << setw(7) << name << setw(10) << color << setw(20) << freshness << setw(5) << count << setw(5) << price << endl;
	}
	File_Data.close();
}

#pragma endregion

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color B1");

	int i = 0; string name;
	Bouquet<Flower> bouquet;
	while (true) {
		switch (menu())
		{
		case 1:
			switch (menuFlower())
			{
			case 1:
				bouquet.addFlower(Rose(setFreshness(), setColor(), setCount()));
				break;
			case 2:
				bouquet.addFlower(Tupil(setFreshness(), setColor(), setCount()));
				break;
			case 3:
				bouquet.addFlower(Lily(setFreshness(), setColor(), setCount()));
				break;
			case 4:
				bouquet.addFlower(Iris(setFreshness(), setColor(), setCount()));
				break;
			default:
				break;
			}
			break;
		case 2:
			bouquet.deleteLast();
			break;
		case 3:
			bouquet.printInfo();
			break;
		case 4:
			cout << "Выберите цветок, информацию о котором хотите изменить" << endl;
			switch (menuFlower())
			{
			case 1:
				bouquet.edit(rose);
				break;
			case 2:
				bouquet.edit(tupil);
				break;
			case 3:
				bouquet.edit(lily);
				break;
			case 4:
				bouquet.edit(iris);
				break;
			default:
				break;
			}
			break;
		case 5:
			cout << "Цена букета:	" << bouquet.getPrice() << endl;
			break;
		case 6:
			switch (menuFlower())
			{
			case 1:
				name = rose;
				break;
			case 2:
				name = tupil;
				break;
			case 3:
				name = lily;
				break;
			case 4:
				name = iris;
				break;
			default:
				break;
			}
			bouquet.search(name);
			break;
		case 7:
			bouquet.deleteAll();
			break;
		case 0:
			bouquet.deleteAll();
			system("pause");
			return 0;
		default:
			break;
		}
	}
}