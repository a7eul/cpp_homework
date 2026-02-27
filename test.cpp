// Тема: Базовая структура и указатели
#include <iostream>
#include <string>
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

    // Тема: Динамическая память
    int n = 3;
    Item* items = new Item[n];

    // Инициализация тестовыми данными
    items[0] = {"Молоко", 89.99, 10};
    items[1] = {"Хлеб", 45.50, 20};
    items[2] = {"Яйца", 120.00, 15};

    cout << "=== Все товары ===\n";
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

    // Тема: Освобождение динамической памяти
    delete[] items;
}