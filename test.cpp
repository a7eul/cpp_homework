// Тема: Препроцессор, макросы
#define TAX 0.20

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
    double priceWithTax = item->price * (1 + TAX);  // Тема: Использование макроса
    cout << item->name << " | Цена: " << item->price 
         << " (с НДС: " << priceWithTax << ") | Количество: " 
         << item->quantity << " | Стоимость: " 
         << item->price * item->quantity << "\n";
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

    // Тема: Интерактивное меню
    int choice;
    do {
        cout << "\n1. Показать все товары\n";
        cout << "2. Найти товар и изменить количество\n";
        cout << "3. Показать общую стоимость\n";
        cout << "4. Сохранить и выйти\n";
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Тема: Вывод через указатели
                printAll(items, n);
                break;

            case 2: {
                string searchName;
                cout << "Введите название товара: ";
                cin >> searchName;

                // Тема: Поиск через указатели
                Item* found = findItem(items, n, searchName);
                if (found != nullptr) {
                    cout << "Найден: ";
                    printItem(found);

                    int change;
                    cout << "Изменить количество (+/-): ";
                    cin >> change;
                    found->quantity += change;

                    if (found->quantity < 0) {
                        found->quantity = 0;
                    }

                    cout << "Новое количество: " << found->quantity << "\n";
                    cout << "Новая стоимость: " 
                         << found->price * found->quantity << "\n";
                } else {
                    cout << "Товар не найден\n";
                }
                break;
            }
case 3: {
                // Тема: Расчет с макросом TAX
                double total = calculateTotal(items, n);
                double totalWithTax = total * (1 + TAX);
                cout << "Общая стоимость: " << total << "\n";
                cout << "С НДС (" << TAX * 100 << "%): " << totalWithTax << "\n";
                break;
            }

            case 4:
                // Тема: Сохранение в файл
                saveToFile(items, n, "items.txt");
                break;

            default:
                cout << "Неверный выбор\n";
        }
    } while (choice != 4);

    // Тема: Освобождение динамической памяти
    delete[] items;
}