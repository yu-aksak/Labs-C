/*Создать контейнер, который будет хранить объекты класса по
предметной области, указанной в таблице (класс должен содержать
функционал по предметной области). Для контейнера реализовать
добавление элементов, вывод содержимого элементов на экран,
редактирование элементов. Необходимо использовать меню.
Контейнер - queue, stack, priority_queue 
Тема - туристические услуги*/
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <Windows.h>
#include <iomanip>
#include <algorithm>
using namespace std;

class TouristService {
    string name, type, country;
    int duration;           // количество суток
    double cost;
public:
    TouristService() {
        _new();
    }
    void setName(string);
    void setType(string);
    void setCountry(string);
    void setDuration(int);
    void setCost(double);
    string getName()const;
    string getType()const;
    string getCountry()const;
    int getDuration()const;
    double getCost()const;
    void _new();
    void print()const;
    ~TouristService() {}
};

bool operator< (const TouristService& st1, const TouristService& st2) {
    return st1.getName() > st2.getName();
}

bool operator> (const TouristService& st1, const TouristService& st2) {
    return st1.getName() < st2.getName();
}

void TouristService::setName(string name) {
    this->name = name;
}

void TouristService::setType(string type) {
    this->type = type;
}

void TouristService::setCountry(string country) {
    this->country = country;
}

void TouristService::setDuration(int duration) {
    this->duration = duration;
}

void TouristService::setCost(double cost) {
    this->cost = cost;
}

string TouristService::getName()const {
    return name;
}

string TouristService::getType()const {
    return type;
}

string TouristService::getCountry()const {
    return country;
}

int TouristService::getDuration()const {
    return duration;
}

double TouristService::getCost()const {
    return cost;
}

void TouristService::_new() {
    cout << "Введите название услуги" << endl;
    cin >> name;
    cout << "Введите тип" << endl;
    cin >> type;
    cout << "Введите страну" << endl;
    cin >> country;
    cout << "Введите длительность (в сутках)" << endl;
    cin >> duration;
    cout << "Введите стоимость" << endl;
    cin >> cost;
}

void TouristService::print()const {
    cout << setw(15) << left << name << setw(15) << left << type << setw(10) << left << country
        << setw(14) << left << duration << setw(7) << left << cost << endl;
}

class ControllerQueue {
    queue<TouristService> services;
public:
    ControllerQueue() {}
    void add();
    void del(string, string);
    void print();
    void edit(int, string, string, string);
    ~ControllerQueue() {}
};

void ControllerQueue::add() {
    services.push(TouristService());
    cout << "Добавление в контейнер завершено успешно!" << endl;
}

void ControllerQueue::del(string name, string type) {
    size_t i = 0, size = services.size();
    while (i < size) {
        if (services.front().getName() == name && services.front().getType() == type);
        else
            services.push(services.front());
        services.pop();
        i++;
    }
    cout << "Удаление завершено успешно!" << endl;
}

void ControllerQueue::print() {
    cout << setw(15) << left << "Название" << setw(15) << left << "Тип" << setw(10) << left << "Страна"
        << setw(14) << left << "Длительность" << setw(7) << left << "Цена" << endl;
    size_t i = 0, size = services.size();
    while (i < size) {
        services.front().print();
        services.push(services.front());
        services.pop();
        i++;
    }
}

void ControllerQueue::edit(int e, string name, string type, string temp) {
    size_t i = 0, size = services.size();
    while (i < size) {
        if (services.front().getName() == name && services.front().getType() == type)
            break;
        else
            services.push(services.front());
        services.pop();
        i++;
    }
    switch (e) {
    case 1:
        services.front().setName(temp);
        break;
    case 2:
        services.front().setType(temp);
        break;
    case 3:
        services.front().setCountry(temp);
        break;
    case 4:
        services.front().setDuration(stoi(temp));
        break;
    case 5:
        services.front().setCost(stod(temp));
        break;
    default:
        break;
    }
    while (i < size) {
        services.push(services.front());
        services.pop();
        i++;
    }
    cout << "Редактирование завершено успешно!" << endl;
}

class ControllerPriorQueue {
    priority_queue<TouristService> services;
public:
    ControllerPriorQueue() {}
    void add();
    void del(string, string);
    void print();
    void edit(int, string, string, string);
    ~ControllerPriorQueue() {}
};

void ControllerPriorQueue::add() {
    services.push(TouristService());
    cout << "Добавление в контейнер завершено успешно!" << endl;
}

void ControllerPriorQueue::del(string name, string type) {
   priority_queue<TouristService> servicesCopy;
   size_t i = 0, size = services.size();
    while (i < size) {
        if (services.top().getName() == name && services.top().getType() == type);
        else
            servicesCopy.push(services.top());
        services.pop();
        i++;
    }
    services = servicesCopy;
    cout << "Удаление завершено успешно!" << endl;
}

void ControllerPriorQueue::print() {
   cout << setw(15) << left << "Название" << setw(15) << left << "Тип" << setw(10) << left << "Страна"
        << setw(14) << left << "Длительность" << setw(7) << left << "Цена" << endl;
   
   priority_queue<TouristService> servicesCopy;
   servicesCopy = services;
   size_t i = 0, size = services.size();
    while (i < size) {
        services.top().print();
        services.pop();
        i++;
    }
    services = servicesCopy;
}

void ControllerPriorQueue::edit(int e, string name, string type, string temp) {
    priority_queue<TouristService> servicesCopy;
    size_t i = 0, size = services.size();
    TouristService m = services.top();
    while (i < size) {
        if (services.top().getName() == name && services.top().getType() == type)
            break;
        else
            servicesCopy.push(services.top());
        services.pop();
        i++;
    }
    switch (e) {
    case 1:
        m = services.top();
        services.pop();
        m.setName(temp);
        services.push(m);
        break;
    case 2:
        m = services.top();
        services.pop();
        m.setType(temp);
        services.push(m);
        break;
    case 3:
        m = services.top();
        services.pop();
        m.setCountry(temp);
        services.push(m);
        break;
    case 4:
        m = services.top();
        services.pop();
        m.setDuration(stoi(temp));
        services.push(m);
        break;
    case 5:
        m = services.top();
        services.pop();
        m.setCost(stod(temp));
        services.push(m);
        break;
    default:
        break;
    }
    while (i < size) {
        services.push(services.top());
        services.pop();
        i++;
    }
    cout << "Редактирование завершено успешно!" << endl;
}


class ControllerStack {
    stack<TouristService> services;
public:
    ControllerStack() {}
    void add();
    void del(string, string);
    void print();
    void edit(int, string, string, string);
    ~ControllerStack() {}
};

void ControllerStack::add(){
    services.push(TouristService());
    cout << "Добавление в контейнер завершено успешно!" << endl;
}

void ControllerStack::del(string name, string type) {
    size_t i = 0, size = services.size();
    while (i < size) {
        if (services.top().getName() == name && services.top().getType() == type);
        else
            services.push(services.top());
        services.pop();
        i++;
    }
    cout << "Удаление завершено успешно!" << endl;
}

void ControllerStack::print() {
    cout << setw(15) << left << "Название" << setw(15) << left << "Тип" << setw(10) << left << "Страна"
        << setw(14) << left << "Длительность" << setw(7) << left << "Цена" << endl;
    size_t i = 0, size = services.size();
    while (i < size) {
        services.top().print();
        services.push(services.top());
        services.pop();
        i++;
    }
}

void ControllerStack::edit(int e, string name, string type, string temp) {
    size_t i = 0, size = services.size();
    while (i < size) {
        if (services.top().getName() == name && services.top().getType() == type)
            break;
        else
            services.push(services.top());
        services.pop();
        i++;
    }
    switch (e) {
    case 1:
        services.top().setName(temp);
        break;
    case 2:
        services.top().setType(temp);
        break;
    case 3:
        services.top().setCountry(temp);
        break;
    case 4:
        services.top().setDuration(stoi(temp));
        break;
    case 5:
        services.top().setCost(stod(temp));
        break;
    default:
        break;
    }
    while (i < size) {
        services.push(services.top());
        services.pop();
        i++;
    }
    cout << "Редактирование завершено успешно!" << endl;
}

int ChooseQPS() {
    int i;
    cout << "Выберите, с каким контейнером хотите работать: " << endl;
    cout << "1. Queue" << endl;
    cout << "2. Priority queue" << endl;
    cout << "3. Stack" << endl;
    cin >> i;
    return i;
}

int menu() {
    int i;
    system("pause");
    system("cls");
    cout << "Выберите:" << endl;
    cout << "1. Добавление услуги" << endl;
    cout << "2. Удаление услуги" << endl;
    cout << "3. Редактирование информации об услуге" << endl;
    cout << "4. Просмотр содержимого контейнера" << endl;
    cout << "0. Выход" << endl;
    cin >> i;
    return i;
}

int menuEdit() {
    int i;
    cout << "Выберите поле, которое вы хотите отредактировать:" << endl;
    cout << "1. Название" << endl;
    cout << "2. Тип" << endl;
    cout << "3. Страну" << endl;
    cout << "4. Длительность" << endl;
    cout << "5. Цену" << endl;
    cin >> i;
    return i;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("color B1");

    ControllerQueue servicesQ;
    ControllerPriorQueue servicesP;
    ControllerQueue servicesS;

    int s = ChooseQPS();
    int e = 0;
    string name, type, temp;

    while (true) {
        switch (menu())
        {
        case 1:
            if (s == 1)
                servicesQ.add();
            else if (s == 2)
                servicesP.add();
            else if (s == 3)
                servicesS.add();
            break;
        case 2:
            cout << "Введите название услуги, которую хотите удалить: \t"; cin >> name;
            cout << "Введите тип услуги, которую хотите удалить:\t"; cin >> type;
            if (s == 1)
                servicesQ.del(name, type);
            else if (s == 2)
                servicesP.del(name, type);
            else if (s == 3)
                servicesS.del(name, type);
            break;
        case 3:
            cout << "Введите название услуги, которую хотите редактировать: \t"; cin >> name;
            cout << "Введите тип услуги, которую хотите редактировать:\t"; cin >> type;
            e = menuEdit();
            cout << "Введите новое значение поля:\t"; cin >> temp;
            if (s == 1)
                servicesQ.edit(e, name, type, temp);
            else if (s == 2)
                servicesP.edit(e, name, type, temp);
            else if (s == 3)
                servicesS.edit(e, name, type, temp);
            break;
        case 4:
            if (s == 1)
                servicesQ.print();
            else if (s == 2)
                servicesP.print();
            else if (s == 3)
                servicesS.print();
            break;
        case 0:
            system("pause");
            return 0;
            break;
        default:
            break;
        }
    }
}