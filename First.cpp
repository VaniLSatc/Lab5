#include <iostream>
#include <iomanip>
#include <string>
#include <map>

using namespace std;

const int ZONE = 2; // Количество зон хранения
const int RACK = 6; // Количество стеллажей в каждой зоне
const int SECTION = 4; // Количество вертикальных секций стеллажа
const int SHELVE = 4; // Количество полок
const int MAX_ITEMS = 10; // Максимальное количество товара в ячейке

struct CellContent {
    map<string, int> items; // Наименование товара - количество
    int total = 0; // Общее количество товаров в ячейке
};

CellContent warehouse[ZONE][RACK][SECTION][SHELVE]; // Склад
int totalCapacity = ZONE * RACK * SECTION * SHELVE * MAX_ITEMS; // Общая вместимость

void add(string address, string item, int count) {
    if (count <= 0) {
        cout << "Количество должно быть положительным." << endl;
        return;
    }

    int zone = address[0] - 'A'; // Зона (A=0, B=1)
    int rack = stoi(address.substr(1, 2)) - 1; // Стеллаж (1-6)
    int section = address[3] - '0'; // Вертикальная секция (0-3)
    int shelf = address[4] - '0'; // Полка (0-3)

    if (zone < 0 || zone >= ZONE || rack < 0 || rack >= RACK || section < 0 || section >= SECTION || shelf < 0 || shelf >= SHELVE) {
        cout << "Некорректный адрес." << endl;
        return;
    }

    CellContent& cell = warehouse[zone][rack][section][shelf];
    
    if (cell.total + count > MAX_ITEMS) {
        cout << "Нельзя добавить товар. Ячейка переполнена." << endl;
        return;
    }

    cell.items[item] += count;
    cell.total += count;
    cout << "Товар '" << item << "' добавлен." << endl;
}

void remove(string address, string item, int count) {
    if (count <= 0) {
        cout << "Количество должно быть положительным." << endl;
        return;
    }

    int zone = address[0] - 'A'; // Зона (A=0, B=1)
    int rack = stoi(address.substr(1, 2)) - 1; // Стеллаж (1-6)
    int section = address[3] - '0'; // Вертикальная секция (0-3)
    int shelf = address[4] - '0'; // Полка (0-3)

    if (zone < 0 || zone >= ZONE || rack < 0 || rack >= RACK || section < 0 || section >= SECTION || shelf < 0 || shelf >= SHELVE) {
        cout << "Некорректный адрес." << endl;
        return;
    }

    CellContent& cell = warehouse[zone][rack][section][shelf];
    
    if (cell.items.find(item) == cell.items.end() || cell.items[item] < count) {
        cout << "Недостаточно товара '" << item << "' для удаления." << endl;
        return;
    }

    cell.items[item] -= count;
    cell.total -= count;
    
    // Если товара этого типа больше нет, удаляем запись
    if (cell.items[item] == 0) {
        cell.items.erase(item);
    }
    
    cout << "Товар '" << item << "' удален." << endl;
}

void info() {
    int totalItems = 0;
    int zoneItems[ZONE] = {0};
    
    // Подсчет общего количества товаров
    for (int z = 0; z < ZONE; ++z) {
        for (int r = 0; r < RACK; ++r) {
            for (int s = 0; s < SECTION; ++s) {
                for (int sh = 0; sh < SHELVE; ++sh) {
                    totalItems += warehouse[z][r][s][sh].total;
                    zoneItems[z] += warehouse[z][r][s][sh].total;
                }
            }
        }
    }

    // Вывод статистики
    float totalPercent = (static_cast<float>(totalItems) / totalCapacity) * 100;
    cout << "Общая загруженность склада: " << fixed << setprecision(2) << totalPercent << "%" << endl;
    for (int z = 0; z < ZONE; ++z) {
        float zonePercent = (static_cast<float>(zoneItems[z]) / (RACK * SECTION * SHELVE * MAX_ITEMS)) * 100;
        cout << "Зона " << char('A' + z) << ": " << zonePercent << "%" << endl;
    }

    // Вывод содержимого ячеек
    cout << "Содержимое ячеек:" << endl;
    for (int z = 0; z < ZONE; ++z) {
        for (int r = 0; r < RACK; ++r) {
            for (int s = 0; s < SECTION; ++s) {
                for (int sh = 0; sh < SHELVE; ++sh) {
                    const CellContent& cell = warehouse[z][r][s][sh];
                    if (cell.total > 0) {
                        cout << char('A' + z) << r + 1 << s << sh << ": ";
                        cout << "Всего " << cell.total << " единиц (";
                        for (const auto& item : cell.items) {
                            cout << item.first << " - " << item.second << ", ";
                        }
                        cout << "\b\b)" << endl;
                    }
                }
            }
        }
    }

    // Вывод пустых ячеек
    cout << "Пустые ячейки:" << endl;
    for (int z = 0; z < ZONE; ++z) {
        for (int r = 0; r < RACK; ++r) {
            for (int s = 0; s < SECTION; ++s) {
                for (int sh = 0; sh < SHELVE; ++sh) {
                    if (warehouse[z][r][s][sh].total == 0) {
                        cout << char('A' + z) << r + 1 << s << sh << endl;
                    }
                }
            }
        }
    }
}

int main() {
    string user_answer, address, item;
    int count;

    while (true) {
        cout << "Введите команду (ADD, REMOVE, INFO, EXIT): ";
        cin >> user_answer;

        if (user_answer == "ADD") {
            cout << "Введите адрес ячейки: ";
            cin >> address;
            cout << "Введите наименование товара: ";
            cin >> item;
            cout << "Введите количество товара: ";
            cin >> count;
            add(address, item, count);
        } else if (user_answer == "REMOVE") {
            cout << "Введите адрес ячейки: ";
            cin >> address;
            cout << "Введите наименование товара: ";
            cin >> item;
            cout << "Введите количество товара: ";
            cin >> count;
            remove(address, item, count);
        } else if (user_answer == "INFO") {
            info();
        } else if (user_answer == "EXIT") {
            break;
        } else {
            cout << "Неизвестная команда." << endl;
        }
    }

    return 0;
}
