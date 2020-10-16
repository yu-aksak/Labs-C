/*Создать контейнеры, которые будут хранить объекты классов по
предметной области, указанной в таблице (класс должен содержать
функционал по предметной области). Для контейнера реализовать
добавление, удаление, редактирование, вывод содержимого контейнера на
экран и в файл, поиск и сортировку элементов. Необходимо создать удобное
пользовательское меню.
Контейнер - list, map
Тема - студенты ВУЗа*/
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <Windows.h>
#include <iomanip>
#include <algorithm>
using namespace std;

class Student {
    int NumStudCard, NumGroup, Year;
    string FirstName, Name, SecondName, Faculty;
public:
    Student() {
        _new();
    }
    Student(string, int, int, string, string, string, int);
    void setFaculty(string);
    void setNumGroup(int);
    void setNumStudCard(int);
    void setFirstName(string);
    void setName(string);
    void setSecondName(string);
    void setYear(int);
    string getFaculty()const;
    int getNumGroup()const;
    int getNumStudCard()const;
    string getFirstName()const;
    string getName()const;
    string getSecondName()const;
    int getYear()const;
    void _new();
    void printInfo()const;
    ~Student() {}
};

Student::Student(string Faculty, int NumGroup, int NumStudCard, string FirstName, string Name, string SecondName, int year) {
    this->Faculty = Faculty;
    this->NumGroup = NumGroup;
    this->NumStudCard = NumStudCard;
    this->FirstName = FirstName;
    this->Name = Name;
    this->SecondName = SecondName;
    this->Year = year;
}

void Student::setFaculty(string Faculty) {
    this->Faculty = Faculty;
}

void Student::setNumGroup(int NumGroup) {
    this->NumGroup = NumGroup;
}

void Student::setNumStudCard(int NumStudCard) {
    this->NumStudCard = NumStudCard;
}

void Student::setFirstName(string FirstName) {
    this->FirstName = FirstName;
}

void Student::setName(string Name) {
    this->Name = Name;
}

void Student::setSecondName(string SecondName) {
    this->SecondName = SecondName;
}

void Student::setYear(int Year) {
    this->Year = Year;
}

string Student::getFaculty()const {
    return Faculty;
}
int Student::getNumGroup() const {
    return NumGroup;
}
int Student::getNumStudCard() const {
    return NumStudCard;
}
string Student::getFirstName() const {
    return FirstName;
}
string Student::getName() const {
    return Name;
}
string Student::getSecondName() const {
    return SecondName;
}
int Student::getYear() const {
    return Year;
}

void Student::printInfo()const {
    cout << setw(11) << left << Faculty << setw(10) << left << NumGroup << setw(12) << left << NumStudCard << setw(15) << left << FirstName
        << setw(15) << left << Name << setw(15) << left << SecondName << setw(11) << left << Year << endl;
}

void Student::_new() {
    cout << "Введите факультет" << endl;
    cin >> Faculty;
    cout << "Введите номер группы" << endl;
    cin >> NumGroup;
    cout << "Введите номер студенческого билета" << endl;
    cin >> NumStudCard;
    cout << "Введите фамилию" << endl;
    cin >> FirstName;
    cout << "Введите имя" << endl;
    cin >> Name;
    cout << "Введите отчество" << endl;
    cin >> SecondName;
    cout << "Введите год поступления" << endl;
    cin >> Year;
}

class ControllerList {
    list<Student*> studentsList;
public:
    ControllerList() {}
    void add();
    void del(string, string);
    void edit(string, string, int, string);
    void print();
    void inFile();
    void search(string, string);
    void sort_(int);
    void clear_();
    ~ControllerList() {}
};

void ControllerList::add() {
    studentsList.push_back(new Student());
    cout << "Добавление в контейнер завершено успешно!" << endl;
}

void ControllerList::del(string FirstName, string Name) {
    for (list<Student*>::iterator i = studentsList.begin(); i != studentsList.end(); i++)
        if ((*i)->getFirstName() == FirstName && (*i)->getName() == Name) {
            studentsList.erase(i);
            break;
        }
    cout << "Удаление завершено успешно!" << endl;
}

void ControllerList::edit(string FirstName, string Name, int k, string temp) {
    list<Student*>::iterator i = studentsList.begin();
    for (i; i != studentsList.end(); i++)
        if ((*i)->getFirstName() == FirstName && (*i)->getName() == Name) {
            break;
        }
    switch (k) {
    case 1:
        (*i)->setFaculty(temp);
        break;
    case 2:
        (*i)->setNumGroup(stoi(temp));
        break;
    case 3:
        (*i)->setFirstName(temp);
        break;
    case 4:
        (*i)->setName(temp);
        break;
    case 5:
        (*i)->setSecondName(temp);
        break;
    default:
        break;
    }
    cout << "Редактирование завершено успешно!" << endl;
}

void ControllerList::print() {
    cout << setw(11) << left << "Факультет" << setw(10) << left << "№Группы" << setw(12) << left << "№студ.бил." << setw(15) << left << "Фамилия"
        << setw(15) << left << "Имя" << setw(15) << left << "Отчество" << setw(11) << left << "Год пост." << endl;
    for (list<Student*>::iterator i = studentsList.begin(); i != studentsList.end(); i++)
        (*i)->printInfo();
}

void ControllerList::inFile() {
    ofstream File_Data;
    File_Data.open("studentsList.txt", ios::app);
    for (list<Student*>::iterator i = studentsList.begin(); i != studentsList.end(); i++)
        File_Data << endl << (*i)->getFaculty() << "\t" << (*i)->getNumGroup() << "\t" << (*i)->getNumStudCard() << "\t" << (*i)->getFirstName()
        << "\t" << (*i)->getName() << "\t" << (*i)->getSecondName() << "\t" << (*i)->getYear();
    File_Data.close();
    cout << "Запись в файл завершена успешно!" << endl;
}

void ControllerList::search(string FirstName, string Name) {
    for (list<Student*>::iterator i = studentsList.begin(); i != studentsList.end(); i++)
        if ((*i)->getFirstName() == FirstName && (*i)->getName() == Name) {
            (*i)->printInfo();
            break;
        }
}

bool sortListFaculty(const Student* a, const Student* b)
{
    return a->getFaculty() < b->getFaculty();
}

bool sortListNumGroup(const Student* a, const Student* b)
{
    return a->getNumGroup() < b->getNumGroup();
}

bool sortListNumStudCard(const Student* a, const Student* b)
{
    return a->getNumStudCard() < b->getNumStudCard();
}

bool sortListFirstName(const Student* a, const Student* b)
{
    return a->getFirstName() < b->getFirstName();
}

bool sortListName(const Student* a, const Student* b)
{
    return a->getName() < b->getName();
}

bool sortListSecondName(const Student* a, const Student* b)
{
    return a->getSecondName() < b->getSecondName();
}

bool sortListYear(const Student* a, const Student* b)
{
    return a->getYear() < b->getYear();
}

void ControllerList::sort_(int s) {
    switch (s)
    {
    case 1:
        studentsList.sort(sortListFaculty);
        break;
    case 2:
        studentsList.sort(sortListNumGroup);
        break;
    case 3:
        studentsList.sort(sortListNumStudCard);
        break;
    case 4:
        studentsList.sort(sortListFirstName);
        break;
    case 5:
        studentsList.sort(sortListName);
        break;
    case 6:
        studentsList.sort(sortListSecondName);
        break;
    case 7:
        studentsList.sort(sortListYear);
        break;
    default:
        break;
    }
    cout << "Сортировка завершена успешно!" << endl;
}

void ControllerList::clear_() {
    studentsList.clear();
    cout << "Очистка контейнера завершена успешно!" << endl;
}

class ControllerMap {
    map<int, Student> studentsMap;
public:
    ControllerMap() {}
    void add();
    void del(string, string);
    void edit(string, string, int, string);
    void print();
    void inFile();
    void search(string, string);
    void clear_();
    ~ControllerMap() {}
};

void ControllerMap::add() {
    Student student;
    studentsMap.insert(make_pair(student.getNumStudCard(), student));
    cout << "Добавление в контейнер завершено успешно!" << endl;
}

void ControllerMap::del(string FirstName, string Name) {
    for (map<int, Student>::iterator i = studentsMap.begin(); i != studentsMap.end(); i++)
        if ((*i).second.getFirstName() == FirstName && (*i).second.getName() == Name) {
            studentsMap.erase(i);
            break;
        }
    cout << "Удаление завершено успешно!" << endl;
}

void ControllerMap::edit(string FirstName, string Name, int k, string temp) {
    map<int, Student>::iterator i = studentsMap.begin();
    for (i; i != studentsMap.end(); i++)
        if ((*i).second.getFirstName() == FirstName && (*i).second.getName() == Name) {
            break;
        }
    switch (k) {
    case 1:
        (*i).second.setFaculty(temp);
        break;
    case 2:
        (*i).second.setNumGroup(stoi(temp));
        break;
    case 3:
        (*i).second.setFirstName(temp);
        break;
    case 4:
        (*i).second.setName(temp);
        break;
    case 5:
        (*i).second.setSecondName(temp);
        break;
    default:
        break;
    }
    cout << "Редактирование завершено успешно!" << endl;

}

void ControllerMap::print() {
    cout << setw(10) << left << "Ключ" << setw(11) << left << "Факультет" << setw(10) << left << "№Группы" << setw(12) << left << "№студ.бил." << setw(15) << left << "Фамилия"
        << setw(15) << left << "Имя" << setw(15) << left << "Отчество" << setw(11) << left << "Год пост." << endl;
    for (map<int, Student>::iterator i = studentsMap.begin(); i != studentsMap.end(); i++) {
        cout << setw(10) << left << (*i).first;
        (*i).second.printInfo();
    }
}

void ControllerMap::inFile() {
    ofstream File_Data;
    File_Data.open("studentsMap.txt", ios::app);
    for (map<int, Student>::iterator i = studentsMap.begin(); i != studentsMap.end(); i++)
        File_Data << endl << (*i).first << "\t" << (*i).second.getFaculty() << "\t" << (*i).second.getNumGroup() << "\t" << (*i).second.getNumStudCard() << "\t" << (*i).second.getFirstName()
        << "\t" << (*i).second.getName() << "\t" << (*i).second.getSecondName() << "\t" << (*i).second.getYear();
    File_Data.close();
    cout << "Запись в файл завершена успешно!" << endl;
}

void ControllerMap::search(string FirstName, string Name) {
    for (map<int, Student>::iterator i = studentsMap.begin(); i != studentsMap.end(); i++)
        if ((*i).second.getFirstName() == FirstName && (*i).second.getName() == Name) {
            (*i).second.printInfo();
            break;
        }
}

void ControllerMap::clear_() {
    studentsMap.clear();
    cout << "Очистка контейнера завершена успешно!" << endl;
}

void viewFileList() {
    ifstream File_Data;
    File_Data.open("studentsList.txt");
    int NumStudCard, NumGroup, Year;
    string FirstName, Name, SecondName, Faculty;
    cout << setw(11) << left << "Факультет" << setw(10) << left << "№Группы" << setw(12) << left << "№студ.бил." << setw(15) << left << "Фамилия"
        << setw(15) << left << "Имя" << setw(15) << left << "Отчество" << setw(11) << left << "Год пост." << endl;
    while (!File_Data.eof()) {
        File_Data >> Faculty >> NumGroup >> NumStudCard >> FirstName >> Name >> SecondName >> Year;
        cout << setw(11) << left << Faculty << setw(10) << left << NumGroup << setw(12) << left << NumStudCard << setw(15) << left << FirstName
            << setw(15) << left << Name << setw(15) << left << SecondName << setw(11) << left << Year << endl;
    }
    File_Data.close();
}

void viewFileMap() {
    ifstream File_Data;
    File_Data.open("studentsMap.txt");
    int key, NumStudCard, NumGroup, Year;
    string FirstName, Name, SecondName, Faculty;
    cout << setw(10) << left << "Ключ" << setw(11) << left << "Факультет" << setw(10) << left << "№Группы" << setw(12) << left << "№студ.бил." << setw(15) << left << "Фамилия"
        << setw(15) << left << "Имя" << setw(15) << left << "Отчество" << setw(11) << left << "Год пост." << endl;
    while (!File_Data.eof()) {
        File_Data >> key >> Faculty >> NumGroup >> NumStudCard >> FirstName >> Name >> SecondName >> Year;
        cout << setw(10) << left << key << setw(11) << left << Faculty << setw(10) << left << NumGroup << setw(12) << left << NumStudCard << setw(15) << left << FirstName
            << setw(15) << left << Name << setw(15) << left << SecondName << setw(11) << left << Year << endl;
    }
    File_Data.close();
}

int ChooseLM() {
    int i;
    cout << "Выберите, с каким контейнером хотите работать: " << endl;
    cout << "1. List" << endl;
    cout << "2. Map" << endl;
    cin >> i;
    return i;
}

int menuEdit() {
    int i;
    cout << "Выберите, что хотите отредактировать:" << endl;
    cout << "1. Факультет" << endl;
    cout << "2. Номер группы" << endl;
    cout << "3. Фамилия" << endl;
    cout << "4. Имя" << endl;
    cout << "5. Отчество" << endl;
    cin >> i;
    return i;
}

int menuSort() {
    int i;
    cout << "Выберите по какому полю произвести портировку:" << endl;
    cout << "1. Факультет" << endl;
    cout << "2. Номер группы" << endl;
    cout << "3. Номер студенческого билета" << endl;
    cout << "4. Фамилия" << endl;
    cout << "5. Имя" << endl;
    cout << "6. Отчество" << endl;
    cout << "7. Год поступления" << endl;
    cin >> i;
    return i;
}

int menu() {
    int i;
    system("pause");
    system("cls");
    cout << "Выберите:" << endl;
    cout << "1. Добавление студента" << endl;
    cout << "2. Удаление студента" << endl;
    cout << "3. Редактирование информации о студенте" << endl;
    cout << "4. Просмотр содержимого контейнера" << endl;
    cout << "5. Запись содержимого контейнера в конец файла" << endl;
    cout << "6. Поиск студента в контейнере" << endl;
    cout << "7. Сортировка контейнера по возрастанию (для list, map изначально отсортирован по ключу (№студ.бил.))" << endl;
    cout << "8. Просмотр содержимого файла" << endl;
    cout << "9. Очистка файла" << endl;
    cout << "10. Очистка контейнера" << endl;
    cout << "0. Выход" << endl;
    cin >> i;
    return i;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("color B1");

    ofstream File_Data;
    ControllerList studentsList;
    ControllerMap studentsMap;

    int k = 0, s = 0;
    int m = ChooseLM();
    string FirstName, Name, temp;

    while (true) {
        switch (menu()) {
        case 1:
            if (m == 1)
                studentsList.add();
            else
                studentsMap.add();
            break;
        case 2:
            cout << "Введите фамилию студента, которого хотите удалить:\t";  cin >> FirstName;
            cout << "Введите имя студента, которого хотите удалить:\t";  cin >> Name;
            if (m == 1)
                studentsList.del(FirstName, Name);
            else
                studentsMap.del(FirstName, Name);
            break;
        case 3:
            cout << "Введите фамилию студента, которого хотите редактировать:\t";  cin >> FirstName;
            cout << "Введите имя студента, которого хотите редактировать:\t";  cin >> Name;

            k = menuEdit();
            cout << "Введите новое значение поля:\t"; cin >> temp;
            if (m == 1)
                studentsList.edit(FirstName, Name, k, temp);
            else
                studentsMap.edit(FirstName, Name, k, temp);
            break;
        case 4:
            if (m == 1)
                studentsList.print();
            else
                studentsMap.print();
            break;
        case 5:
            if (m == 1)
                studentsList.inFile();
            else
                studentsMap.inFile();
            break;
        case 6:
            cout << "Введите фамилию студента, информацию о котором хотите узнать:\t";  cin >> FirstName;
            cout << "Введите имя студента, информацию о котором хотите узнать:\t";  cin >> Name;

            if (m == 1)
                studentsList.search(FirstName, Name);
            else
                studentsMap.search(FirstName, Name);
            break;
        case 7:
            if (m == 1) {
                s = menuSort();
                studentsList.sort_(s);
            }
            break;
        case 8:
            if (m == 1)
                viewFileList();
            else
                viewFileMap();
            break;
        case 9:
            if (m == 1) {
                File_Data.open("studentsList.txt");
                File_Data.close();
                cout << "Очистка файла завершена успешно!" << endl;
            }
            else {
                File_Data.open("studentsMap.txt");
                File_Data.close();
                cout << "Очистка файла завершена успешно!" << endl;
            }
            break;
        case 10:
            if (m == 1)
                studentsList.clear_();
            else
                studentsMap.clear_();
            break;
        case 0:
            system("pause");
            return 0;
        }
    }
}