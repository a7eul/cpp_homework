// Тема: Файловый ввод/вывод
#include <iostream>
#include <string>
#include <fstream>  // Тема: Файловый ввод/вывод
using namespace std;

// Тема: Структуры
struct Item {
    string name;
    double price;
    int quantity;
};

// Тема: Указатели, арифметика указателей
void printItem(const Item* item) {
    cout << item->name << " | Цена: " << item->price 
         << " | Количество: " << item->quantity 
         << " | Стоимость: " << item->price * item->quantity << "\n";
}

// Тема: Указатели, поиск в массиве
Item* findItem(Item* arr, int n, const string& searchName) {
    Item* end = arr + n;
    for (Item* p = arr; p < end; p++) {
        if (p->name == searchName) {
            return p;  // Тема: возврат указателя
        }
    }
    return nullptr;
}

// Тема: Файловый ввод/вывод (чтение из файла)
int loadFromFile(Item*& arr, const char* filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Файл не найден, создаем новый\n";
        arr = nullptr;
        return 0;
    }

    // Подсчет количества товаров
    int n = 0;
    string line;
    while (getline(in, line)) {
        n++;
    }

    in.clear();
    in.seekg(0);

    // Тема: Динамическая память
    arr = new Item[n];
    Item* end = arr + n;
    for (Item* p = arr; p < end; p++) {
        in >> p->name >> p->price >> p->quantity;
    }

    in.close();
    return n;
}

// Тема: Файловый ввод/вывод (запись в файл)
void saveToFile(Item* arr, int n, const char* filename) {
    ofstream out(filename);
    if (!out.is_open()) {
        cout << "Ошибка записи в файл\n";
        return;
    }

    Item* end = arr + n;
    for (Item* p = arr; p < end; p++) {
        out << p->name << " " << p->price << " " << p->quantity << "\n";
    }

    out.close();
    cout << "Данные сохранены в файл\n";
}

// Тема: Указатели, вывод всех товаров
void printAll(Item* arr, int n) {
    if (n == 0) {
        cout << "Список товаров пуст\n";
        return;
    }

    Item* end = arr + n;
    for (Item* p = arr; p < end; p++) {
        printItem(p);
    }
}

// Тема: Указатели, общая стоимость
double calculateTotal(Item* arr, int n) {
    double total = 0;
    Item* end = arr + n;
    for (Item* p = arr; p < end; p++) {
        total += p->price * p->quantity;
    }
    return total;
}

int main() {
    setlocale(LC_ALL, "RUS");

    Item* items = nullptr;
    int n = 0;

    // Тема: Загрузка из файла
    n = loadFromFile(items, "items.txt");
    cout << "Загружено товаров: " << n << "\n";

    cout << "\n=== Все товары ===\n";
    printAll(items, n);

    cout << "\n=== Поиск товара ===\n";
    string searchName;
    cout << "Введите название товара: ";
    cin >> searchName;

    Item* found = findItem(items, n, searchName);
    if (found != nullptr) {
        cout << "Найден: ";
        printItem(found);
    } else {
        cout << "Товар не найден\n";
    }

    cout << "\n=== Общая стоимость ===\n";
    double total = calculateTotal(items, n);
    cout << "Общая стоимость: " << total << "\n";

    // Тема: Сохранение в файл
    saveToFile(items, n, "items.txt");

    // Тема: Освобождение динамической памяти
    delete[] items;
}