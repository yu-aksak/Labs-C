/*Использовать smart-указатели для созданий программы учета деятельности
издательства. Имеется несколько объектов печатной продукции и некоторое
количество сотрудников издательства, которые работают с издаваемой продукцией.
Печатная продукция считается готовой к изданию, когда с ней не работает ни один
сотрудник издательства. Разработанный набор классов должен иметь параметры типа.
Все классы должны иметь методы получения и изменения своих полей. Реализовать
механизм транзакций, который позволит сотрудникам откатывать изменения, внесенные
в печатную продукцию.*/
#include <iostream>
#include<clocale>
#include <Windows.h>
using namespace std;

#pragma region SmartPointer
template<class T>
struct Status {
	T* ptr;
	int counter = 0;
};

template<class T>
class SmartPointer {
	Status<T>* smartPtr;
public:
	SmartPointer(T* ptr = 0);
	SmartPointer(const SmartPointer&);
	~SmartPointer();
	SmartPointer& operator=(const SmartPointer&);
	T* operator->() const;
	void showCounter() { cout << smartPtr->counter; }
};

template<class T>
SmartPointer<T>::SmartPointer(T* ptr) {
	if (!ptr) smartPtr = NULL;
	else {
		smartPtr = new Status<T>;
		smartPtr->ptr = ptr;
		smartPtr->counter = 1;
	}
}

template <class T>
SmartPointer<T>::SmartPointer(const SmartPointer& obj) {
	smartPtr = obj.smartPtr;
	if (smartPtr)
		smartPtr->counter++;
}

template<class T>
SmartPointer<T>::~SmartPointer() {
	if (smartPtr) {
		smartPtr->counter--;
		if (smartPtr->counter <= 0) {
			delete smartPtr->ptr;
			delete smartPtr;
		}
	}
}

template <class T>
T* SmartPointer<T>::operator->() const {
	if (smartPtr) return smartPtr->ptr;
	else return NULL;
}

template <class T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer& obj) {
	if (smartPtr) {
		smartPtr->counter--;
		if (smartPtr->counter <= 0) {
			delete smartPtr->ptr;
			delete smartPtr;
		}
	}
	smartPtr = obj.smartPtr;
	if (smartPtr) smartPtr->counter++;
	return *this;
}

#pragma endregion

#pragma region Transaction
template<class T1>
class Transaction {
	T1* currentState;
	T1* prevState;
public:
	Transaction();
	Transaction(const Transaction&);
	Transaction& operator=(const Transaction&);
	void show(bool);
	int BeginTransactions(T1&);
	void commit();
	void DeleteTransactions();
	T1* operator->();
	~Transaction();
};

template<class T1>
Transaction<T1>::Transaction() {
	prevState = NULL;
	currentState = new T1;
}

template<class T1>
Transaction<T1>::Transaction(const Transaction& obj) {
	currentState = new T1(*(obj.currentState));
	prevState = NULL;
}

template <class T1>
Transaction<T1>& Transaction<T1>::operator=(const Transaction<T1>& obj) {
	if (this != &obj) {
		delete currentState;
		currentState = new T1(*(obj.currentState));
	}
	return *this;
}

template<class T1>
void Transaction<T1>::show(bool temp) {
	cout << "состояния объекта ";
	if (!temp) cout << "до начала транзакции " << endl;
	else cout << "после выполнения транзакции " << endl;
	if (prevState) {
		cout << "prevState = " << endl;
		prevState->getter();
	}
	else cout << "prevState = NULL" << endl;
	cout << "currentState = " << endl;
	currentState->getter();
}

template <class T1>
int Transaction<T1>::BeginTransactions(T1& obj) {
	delete prevState;
	prevState = currentState;
	currentState = new T1(*prevState);
	if (!currentState) return 0;
	currentState->setter(obj);
	cout << "Транзакция начата успешно" << endl;
	return 1;
}

template <class T1>
void Transaction<T1>::commit() {
	delete prevState;
	prevState = NULL;
	cout << "Транзакция подтверждена успешно" << endl;
}

template <class T1>
void Transaction<T1>::DeleteTransactions() {
	if (prevState != NULL) {
		delete currentState;
		currentState = prevState;
		prevState = NULL;
	}
	cout << "Транзакция откачена назад успешно" << endl;
}

template <class T1>
T1* Transaction<T1>::operator->() {
	return currentState;
}

template<class T1>
Transaction<T1>::~Transaction() {
	delete currentState;
	delete prevState;
}


#pragma endregion

#pragma region PrintProduction
class PrintProduction {
	string typeProd, title, numEdition;
	int countInstance = 0;
public:
	PrintProduction() {}
	PrintProduction(string, string, string, int);
	PrintProduction(const PrintProduction&);
	PrintProduction(SmartPointer<PrintProduction>);
	void set(string, string, string, int);
	void setter(PrintProduction&);
	void setTypeProd(string);
	void setTitle(string);
	void setNumEdition(string);
	void setCountInstance(int);
	void getter();
	PrintProduction get();
	~PrintProduction() {	}
};

PrintProduction::PrintProduction(string typeProd, string title, string numEdition, int countInstance) {
	setTypeProd(typeProd);
	setTitle(title);
	setNumEdition(numEdition);
	setCountInstance(countInstance);
}

PrintProduction::PrintProduction(const PrintProduction& prProd)
{
	typeProd = prProd.typeProd;
	title = prProd.title;
	numEdition = prProd.numEdition;
	countInstance = prProd.countInstance;
}

PrintProduction::PrintProduction(SmartPointer<PrintProduction> obj) {
	this->typeProd = obj->typeProd;
	this->title = obj->title;
	this->numEdition = obj->numEdition;
	this->countInstance = obj->countInstance;
}

void PrintProduction::set(string typeProd, string title, string numEdition, int countInstance) {
	this->typeProd = typeProd;
	this->title = title;
	this->numEdition = numEdition;
	this->countInstance = countInstance;
}

void PrintProduction::setter(PrintProduction& obj) {
	this->typeProd = obj.typeProd;
	this->title = obj.title;
	this->numEdition = obj.numEdition;
	this->countInstance = obj.countInstance;
}

void PrintProduction::setTypeProd(string typeProd) {
	this->typeProd = typeProd;
}

void PrintProduction::setTitle(string title) {
	this->title = title;
}

void PrintProduction::setNumEdition(string numEdition) {
	this->numEdition = numEdition;
}

void PrintProduction::setCountInstance(int countInstance) {
	this->countInstance = countInstance;
}

void PrintProduction::getter() {
	cout << "Тип продукции:\t\t" << typeProd << endl;
	cout << "Название:\t\t" << title << endl;
	cout << "Номер тиража:\t\t" << numEdition << endl;
	cout << "Количество экземпляров:\t" << countInstance << endl << endl;
}

PrintProduction PrintProduction::get() {
	return *this;
}

#pragma endregion

//в PublishingHouse находится 4 класса
#pragma region PublishingHouse
struct Employee {
	string Surname, Name, Patronymic, department, position;
	int age = 0;
};

class PublishingHouse {
protected:
	Employee employee;
public:
	PublishingHouse(Employee employee);
	virtual void setter(Employee) = 0;
	virtual Employee get() = 0;
	virtual void getter() = 0;
	virtual ~PublishingHouse() {}
};

class AdvertisingAndSalesDepartnent :public PublishingHouse {
public:
	AdvertisingAndSalesDepartnent(Employee);
	void setter(Employee);
	Employee get();
	void getter();
	~AdvertisingAndSalesDepartnent() {}
};

class ProductionDepartment :public PublishingHouse {
public:
	ProductionDepartment(Employee);
	void setter(Employee);
	Employee get();
	void getter();
	~ProductionDepartment() {}
};

class EditoralDepartment : public PublishingHouse {
	SmartPointer<Employee> spEmployee;
public:
	EditoralDepartment(Employee);
	void setter(Employee);
	Employee get();
	void getter();
	void editProduction(SmartPointer<PrintProduction>&);
	SmartPointer<Employee> setEm(SmartPointer<Employee>);
	SmartPointer<Employee> getEm();
	~EditoralDepartment() {}
};

PublishingHouse::PublishingHouse(Employee employee) {
	this->employee = employee;
}

AdvertisingAndSalesDepartnent::AdvertisingAndSalesDepartnent(Employee employee) : PublishingHouse(employee) {}

void AdvertisingAndSalesDepartnent::setter(Employee employee) {
	this->employee = employee;
}

Employee AdvertisingAndSalesDepartnent::get() {
	return employee;
}

void AdvertisingAndSalesDepartnent::getter() {
	cout << "ФИО:\t" << employee.Surname << "\t" << employee.Name << "\t" << employee.Patronymic << endl;
	cout << "Возраст:\t" << employee.age << endl;
	cout << "Отдел:\t" << employee.department << endl;
	cout << "Должность:\t" << employee.position << endl;
}

ProductionDepartment::ProductionDepartment(Employee employee) : PublishingHouse(employee) {	}

void ProductionDepartment::setter(Employee) {
	this->employee = employee;
}

Employee ProductionDepartment::get() {
	return employee;
}

void ProductionDepartment::getter() {
	cout << "ФИО:\t" << employee.Surname << "\t" << employee.Name << "\t" << employee.Patronymic << endl;
	cout << "Возраст:\t" << employee.age << endl;
	cout << "Отдел:\t" << employee.department << endl;
	cout << "Должность:\t" << employee.position << endl;
}

EditoralDepartment::EditoralDepartment(Employee employee) : PublishingHouse(employee) {	}

void EditoralDepartment::setter(Employee) {
	this->employee = employee;
}

Employee EditoralDepartment::get() {
	return employee;
}

SmartPointer<Employee> EditoralDepartment::setEm(SmartPointer<Employee> spEmployee) {
	this->spEmployee = spEmployee;
	return this->spEmployee;
}

SmartPointer<Employee> EditoralDepartment::getEm() {
	return spEmployee;
}

void EditoralDepartment::getter() {
	cout << "ФИО:\t" << employee.Surname << "\t" << employee.Name << "\t" << employee.Patronymic << endl;
	cout << "Возраст:\t" << employee.age << endl;
	cout << "Отдел:\t" << employee.department << endl;
	cout << "Должность:\t" << employee.position << endl;
}

int menu() {
	int i;
	system("pause");
	system("cls");
	cout << "Выберите" << endl;
	cout << "1. Изменить название" << endl;
	cout << "2. Изменить тип продукции" << endl;
	cout << "3. Изменить номер издания" << endl;
	cout << "4. Изменить количество экземпляров" << endl;
	cout << "5. Изменить все" << endl;
	cout << "6. Подтвердить" << endl;
	cout << "7. Откат" << endl;
	cout << "8. Просмотр" << endl;
	cout << "0. Выход" << endl;
	cin >> i;
	return i;
}

void EditoralDepartment::editProduction(SmartPointer<PrintProduction>& Production) {
	Transaction<PrintProduction> TranProd;
	PrintProduction prod(Production);
	string title, typeProd, numEdition;
	int countInstance;

	while (true) {
		switch (menu()) {
		case 1:
			cout << "Введите новое название" << endl;
			cin >> title;

			prod.setTitle(title);
			TranProd.BeginTransactions(prod);
			break;
		case 2:
			cout << "Введите новый тип продукции" << endl;
			cin >> typeProd;

			prod.setTypeProd(typeProd);
			TranProd.BeginTransactions(prod);
			break;
		case 3:
			cout << "Введите новый номер издания" << endl;
			cin >> numEdition;

			prod.setNumEdition(numEdition);
			TranProd.BeginTransactions(prod);
			break;
		case 4:
			cout << "Введите новое количество экземпляров" << endl;
			cin >> countInstance;

			prod.setCountInstance(countInstance);
			TranProd.BeginTransactions(prod);
			break;
		case 5:
			cout << "Введите новое название" << endl;
			cin >> title;
			cout << "Введите новый тип продукции" << endl;
			cin >> typeProd;
			cout << "Введите новый номер издания" << endl;
			cin >> numEdition;
			cout << "Введите новое количество экземпляров" << endl;
			cin >> countInstance;

			prod.set(title, typeProd, numEdition, countInstance);
			TranProd.BeginTransactions(prod);
			break;
		case 6:
			TranProd.commit();
			break;
		case 7:
			TranProd.DeleteTransactions();
			break;
		case 8:
			TranProd->getter();
			break;
		case 0:
			return;
		default:
			cout << "Попробуйте снова" << endl;
			break;
		}
	}
}

#pragma endregion

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	system("color B1");

	Employee employee1;
	employee1.Name = "Ольга"; employee1.Surname = "Викторова"; employee1.Patronymic = "Александровна"; employee1.age = 34; employee1.department = "Редакционный"; employee1.position = "Главный редактор";
	Employee employee2;
	employee2.Name = "Александр"; employee2.Surname = "Сидоров"; employee2.Patronymic = "Андреевич"; employee2.age = 21; employee2.department = "Редакционный"; employee1.position = "Стажер";

	SmartPointer<PrintProduction> Book(new PrintProduction("Книга", "Мятная сказка", "978-5-17-102745-2", 305));
	SmartPointer<PrintProduction> Magazine(new PrintProduction("Газета", "Правда", "879-9-89-415124-5", 730));

	EditoralDepartment Olga(employee1);
	EditoralDepartment Aleksandr(employee2);

	Book->getter();	
	Olga.editProduction(Book);
	
	system("cls");

	Magazine->getter();
	Aleksandr.editProduction(Magazine);

	system("pause");
	return 0;
}