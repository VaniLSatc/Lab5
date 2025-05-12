#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Структура для хранения информации о посетителе
struct Visitor {
    string ticket;
    int duration;
};

// Функция для генерации номера талона
string generateTicket() {
    static const char charset[] = "0123456789";
    string ticket = "T";
    for (int i = 0; i < 3; ++i) {
        ticket += charset[rand() % (sizeof(charset) - 1)];
    }
    return ticket;
}

// Функция для распределения очереди по окнам
void distributeVisitors(const vector<Visitor>& queue, int windows) {
    if (queue.empty() || windows <= 0) return;

    // Создаем вектор окон с информацией о времени обработки и списке талонов
    vector<pair<int, vector<string>>> windowList(windows);

    // Копируем очередь для сортировки
    vector<Visitor> Queue = queue;
    
    // Сортируем по убыванию времени обслуживания
    sort(Queue.begin(), Queue.end(), 
        [](const Visitor& a, const Visitor& b) {
            return a.duration > b.duration;
        });

    // Распределяем посетителей по окнам
    for (const auto& visitor : Queue) {
        // Находим окно с минимальным текущим временем
        auto minWindow = min_element(windowList.begin(), windowList.end(),
            [](const pair<int, vector<string>>& a, const pair<int, vector<string>>& b) {
                return a.first < b.first;
            });
        
        // Добавляем посетителя в это окно
        minWindow->first += visitor.duration;
        minWindow->second.push_back(visitor.ticket);
    }

    // Выводим результат распределения
    for (int i = 0; i < windows; ++i) {
        cout << "Окно " << (i + 1) << " (" << windowList[i].first 
             << " минут): ";
        for (size_t j = 0; j < windowList[i].second.size(); ++j) {
            cout << windowList[i].second[j];
            if (j != windowList[i].second.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел

    int windows;
    vector<Visitor> queue;

    cout << ">>> Введите кол-во окон" << endl;
    cout << "<<< ";
    cin >> windows;

    string user_answer;
    while (true) {
        cout << "<<< ";
        cin >> user_answer;

        if (user_answer == "ENQUEUE") {
            int duration;
            cin >> duration;
            
            Visitor visitor;
            visitor.ticket = generateTicket();
            visitor.duration = duration;
            
            queue.push_back(visitor);
            cout << ">>> " << visitor.ticket << endl;
        }
        else if (user_answer == "DISTRIBUTE") {
            distributeVisitors(queue, windows);
            break;
        }
        else {
            cout << ">>> Неизвестная команда" << endl;
        }
    }

    return 0;
}
