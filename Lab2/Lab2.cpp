/*Разработать иерархию классов по предметной области (количество
классов должно быть не менее пяти), в которой должны быть реализованы
следующие связи между классами: агрегация, композиция, обобщение. В
отчете отобразить созданную диаграмму классов.
Сгенерировать минимум пять типов исключительных ситуаций.
Реализовать перенаправление исключительных ситуаций. Сгенерировать
минимум одну исключительную ситуацию с оператором new. Создать
исключительную ситуацию в конструкторе и продемонстрировать вызов
конструкторов и деструкторов. Задать собственную функцию завершения.
Создать собственный (пользовательский) класс исключения, сгенерировать
исключение пользовательского типа и обработать его.
Подготовить минимум один вопрос по теме «Обработка
исключительных ситуаций в языке С++» и запрограммировать его
отображение и фиксацию ответа с выдачей результата.
Предметная область - Цветочный магазин (собрать букет)*/
#include <iostream>
#include <Windows.h>
#include <vector>
#include <exception>

#define red "Красный"
#define yellow "Желтый"
#define pink "Розовый"

#define fresh "Свежий"
#define middle "Средней свежести"
#define old "Старый"

using namespace std;

class MyExeprion {
	string error;
public:
	MyExeprion(string exception) : error(exception) {}
	string returnErr() {
		return error;
	}
};

#pragma region Flowers

class Flower {
protected:
	double price;
	string Freshness, color;
	int count;
public:
	Flower() {
		//cout << "Вызван конструктор класса Flower" << endl;
	}
	virtual double getPrice() { return price; }
	virtual ~Flower() {
		cout << "Вызван деструктор класса Flower" << endl;
	}
};

class Rose : public Flower {

public:
	Rose(string, string, int);
	double getPrice();
	~Rose()
	{
		cout << "Вызван деструктор класса Rose" << endl;
	}
};

Rose::Rose(string Freshness, string color, int count) {
	cout << "Вызван конструктор класса Rose" << endl;
	if (count == 0)
		throw 1;
	this->Freshness = Freshness;
	this->color = color;
	this->count = count;
	this->price = getPrice();
}

double Rose::getPrice() {
	if (color == red)
		price = 5.5;
	else if (color == yellow)
		price = 6.5;
	else if (color == pink)
		price = 6;

	if (Freshness == fresh);
	else if (Freshness == middle)
		price -= 1;
	else if (Freshness == old)
		price -= 2;

	return price * count;
}

class Tupil : public Flower {

public:
	Tupil(string, string, int);
	double getPrice();
	~Tupil()
	{
		cout << "Вызван деструктор класса Tupil" << endl;
	}
};

Tupil::Tupil(string Freshness, string color, int count) {
	cout << "Вызван конструктор класса Tupil" << endl;

	this->Freshness = Freshness;
	this->color = color;
	this->count = count;
	this->price = getPrice();
}

double Tupil::getPrice() {
	if (color == red)
		price = 3;
	else if (color == yellow)
		price = 3.5;
	else if (color == pink)
		price = 4;

	if (Freshness == fresh);
	else if (Freshness == middle)
		price -= 0.5;
	else if (Freshness == old)
		price -= 1;

	return price * count;
}

class Lily : public Flower {

public:
	Lily() {}
	Lily(string, string, int);
	double getPrice();
	~Lily()
	{
		cout << "Вызван деструктор класса Lily" << endl;
	}
};

Lily::Lily(string Freshness, string color, int count) {
	cout << "Вызван конструктор класса Lily" << endl;

	this->Freshness = Freshness;
	this->color = color;
	this->count = count;
	this->price = getPrice();
}

double Lily::getPrice() {
	if (color == red)
		price = 7.5;
	else if (color == yellow)
		price = 6.5;
	else if (color == pink)
		price = 9;

	if (Freshness == fresh);
	else if (Freshness == middle)
		price -= 1.5;
	else if (Freshness == old)
		price -= 2.5;

	return price * count;
}

class Iris : public Flower {

public:
	Iris(string, string, int);
	double getPrice();
	~Iris()
	{
		cout << "Вызван деструктор класса Iris" << endl;
	}
};

Iris::Iris(string Freshness, string color, int count) {
	cout << "Вызван конструктор класса Iris" << endl;

	this->Freshness = Freshness;
	this->color = color;
	this->count = count;
	this->price = getPrice();
}

double Iris::getPrice() {
	if (color == red)
		price = 2.5;
	else if (color == yellow)
		price = 3.5;
	else if (color == pink)
		price = 2;

	if (Freshness == fresh);
	else if (Freshness == middle)
		price -= 0.5;
	else if (Freshness == old)
		price -= 1;

	return price * count;
}

template<class T>
class Bouquet {
	vector<T> bouquet;
	double Price = 0;
public:
	Bouquet() {
		cout << "Вызван конструктор класса Bouquet" << endl;
	}
	Bouquet(int);
	double getPrice();
	void addFlower(T);
	~Bouquet()
	{
		cout << "Вызван деструктор класса Bouquet" << endl;
	}
};

#pragma endregion

#pragma region Bouquet

template<class T>
Bouquet<T>::Bouquet(int i) {
	cout << "Вызван конструктор класса Bouquet" << endl;
	Flower* rose1 = new Rose(middle, red, 7);
	Flower* rose2 = new Rose(old, pink, 3);
	Flower* rose3 = new Rose(fresh, yellow, 5);
	addFlower(*rose1);
	addFlower(*rose2);
	addFlower(*rose3);
}

template<class T>
double Bouquet<T>::getPrice() {
	try {
		if (Price != 0)
			return Price;
		else throw "ERROR";
	}
	catch (const char* s) {
		cout << s << ". Цена равна 0. Выполняется первый обработчик." << endl;
		throw;
	}
}

template<class T>
void Bouquet<T>::addFlower(T flower) {
	bouquet.push_back(flower);
	Price += flower.getPrice();
}

#pragma endregion

void term_func() {
	cout << "term_func() было вызвано terminate().\n";
	exit(-1);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color B1");

	Flower* rose = new Rose(middle, red, 5);
	Flower* iris = new Iris(fresh, yellow, 3);
	Flower* tupil = new Tupil(fresh, red, 7);

	Bouquet<Flower> bouquet;
	bouquet.addFlower(*rose);
	bouquet.addFlower(*iris);
	bouquet.addFlower(*tupil);
	cout << "Цена букета 1: " << bouquet.getPrice() << endl;

	Bouquet<Flower> bouquet1(1);
	cout << "Цена букета 2: " << bouquet1.getPrice() << endl;
	cout << endl;
	cout << " Есть ли ошибки в следующем блоке кода:\n		typedef int type_int;\n	try { ... }\n	catch (type_int error) { ... }\n	catch (int error) { ... }\n	Если есть, то уточните какие." << endl;
	cout << "Ответ на вопрос:" << endl;
	cout << "Неправильной будет следующая запись:\n	typedef int type_int;\n	try { ... }\n	catch (type_int error) { ... }\n	catch (int error) { ... }\nТак, в этом случае type_int и int − это одно и то же.Таким образом, следующий пример верен :" << endl;
	cout << "	class FileException {\n	public:\n	int i;\n	};\n	try { ... }\n	catch (FileException i1) { ... }\n	catch (int i2) { ... }\nВ этом случае FileException – это отдельный тип исключительной	ситуации." << endl;
	cout << endl;

	//ПЕРЕНАПРАВЛЕНИЕ ИСКЛЮЧИТЕЛЬНОЙ СИТУАЦИИ
	Bouquet<Flower> bouquet2;
	try {
		bouquet2.getPrice();
	}
	catch (const char* s) {
		cout << s << ". Цена равна 0. Выполняется второй обработчик." << endl;
	}
	cout << endl;
	//ИСКЛЮЧИТЕЛЬНАЯ СИТУАЦИЯ, ГЕНЕРИРУЕМАЯ	ОПЕРАТОРОМ NEW
	Flower* lily;
	bad_alloc exept;
	try {
		while (1)
			if (!(lily = new Lily[10000000]))//память не выделена, p=NULL
				throw exept;// генерация ошибки выделения памяти
	}
	catch (bad_alloc exept) {
		cout << "Возникло исключение " << exept.what() << endl;
	}
	cout << endl;
	//ГЕНЕРИРОВАНИЕ ИСКЛЮЧЕНИЙ В КОНСТРУКТОРАХ
	try {
		Rose rosE(middle, red, 0);
	}
	catch (int) {
		cout << "Исключение конструктора, count = 0" << endl;
	}
	cout << endl;
	//Создать собственный (пользовательский) класс исключения, сгенерировать исключение пользовательского типа и обработать его
	MyExeprion exception("ERROR");
	try {
		if (exception.returnErr() == "ERROR") throw exception;
	}
	catch (MyExeprion) {
		cout << "Поймано исключение ERROR" << endl;
	}
	cout << endl;
	//ЗАДАНИЕ СОБСТВЕННОЙ ФУНКЦИИ ЗАВЕРШЕНИЯ
	try {
		set_terminate(term_func);
		if (bouquet2.getPrice() == 0) throw "Деление на 0!";
	}
	catch (int) {
		cout << "Поймано некоторе целое исключение.\n";
	}
	system("pause");
	return 0;
}