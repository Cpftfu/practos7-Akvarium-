#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;

class Fish {
private:
    string type;
    int size;
    bool isAgro;

public:
    Fish(const string& t, int s, bool agro) : type(t), size(s), isAgro(agro) {}

    void displayData() const {
        cout << "\nТип: " << type << endl;
        cout << "Размер: " << size << " дюймов" << endl;
        cout << "Хищник: " << (isAgro ? "Да" : "Нет") << endl;
    }

    bool isAgroFish() const {
        return isAgro;
    }

    bool eat(const Fish& otherFish) const {
        if (isAgro && !otherFish.isAgro && size >= otherFish.size) {
            cout << "Рыбка " << type << " съела " << "Рыбку " << otherFish.type << endl;
            return true;
        }
        return false;
    }
};

class Vodorosli {
private:
    int height;

public:
    Vodorosli(int h) : height(h) {}

    void displayData() const {
        cout << "\nВысота водорослей: " << height << " дюймов" << endl;
    }
};

int main() {
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Rus");
    //srand(static_cast<unsigned int>(time(nullptr)));
    vector<Fish> fishList;
    vector<Vodorosli> vodorosliList;
    char choice;
    do {
        cout << "Что вы хотите добавить: (1 - Рыбу, 2 - Водоросли)?" << endl;
        cout << "Ваш выбор: " << endl;
        cout << "==================================================" << endl;
        int option;
        cin >> option;
        cin.ignore();

        if (option == 1) {
            string type;
            int size;
            bool isAgro;
            cout << "Введите тип рыбы: ";
            getline(cin, type);
            cout << "Введите размер рыбы (в дюймах): ";
            cin >> size;
            cout << "Рыба хищная (y/n)? ";
            char agroChoice;
            cin >> agroChoice;
            isAgro = (agroChoice == 'y' || agroChoice == 'Y' || agroChoice == 'н' || agroChoice == 'Н');
            fishList.push_back(Fish(type, size, isAgro));
        }
        else if (option == 2) {
            int height;
            cout << "Введите высоту водорослей (в дюймах): ";
            cin >> height;
            vodorosliList.push_back(Vodorosli(height));
        }
        else {
            cout << "Неверный выбор." << endl;
        }

        cout << "\nХотите добавить ещё элемент? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while (choice == 'y' || choice == 'Y' || choice == 'н' || choice == 'Н');

    cout << "\nСостав аквариума " << endl;
    cout << "===================" << endl;
    int agroCount = 0;
    int kindCount = 0;

    for (auto& agro : fishList) {
        if (agro.isAgroFish()) {
            for (auto& kind : fishList) {
                if (!kind.isAgroFish()) {
                    if (agro.eat(kind)) {
                        kindCount--;
                    }
                }
            }
        }
    }
    for (const auto& fish : fishList) {
        fish.displayData();
        if (fish.isAgroFish()) {
            agroCount++;
        }
        else {
            kindCount++;
        }
    }
    cout << "\nХищных рыб: " << agroCount << endl;
    cout << "Не хищных рыб: " << kindCount << endl;

    cout << "\nВодоросли:" << endl;
    for (const auto& seaweed : vodorosliList) {
        seaweed.displayData();
    }
}
