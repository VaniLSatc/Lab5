#include "train_system.h"

using namespace std;

map<string, set<string>> train_to_towns; // Поезд -> города
map<string, set<string>> town_to_trains; // Город -> поезда

Command parse_command(const string& input) {
    if (input == "CREATE_TRAIN") return Command::CREATE_TRAIN;
    if (input == "TRAINS_FOR_TOWN") return Command::TRAINS_FOR_TOWN;
    if (input == "TOWNS_FOR_TRAIN") return Command::TOWNS_FOR_TRAIN;
    if (input == "TRAINS") return Command::TRAINS;
    if (input == "exit") return Command::EXIT;
    return Command::UNKNOWN;
}

void create_train(const string& train, const vector<string>& towns) {
    for (const auto& town : towns) {
        train_to_towns[train].insert(town);
        town_to_trains[town].insert(train);
    }
}

void trains_for_town(const string& town) {
    if (town_to_trains.find(town) != town_to_trains.end()) {
        cout << "Поезда, проходящие через город " << town << ": ";
        for (const auto& train : town_to_trains[town]) {
            cout << train << " ";
        }
        cout << endl;
    } else {
        cout << "Нет поездов для города " << town << endl;
    }
}

void towns_for_train(const string& train) {
    if (train_to_towns.find(train) != train_to_towns.end()) {
        cout << "Города, которые проезжает поезд " << train << ": ";
        for (const auto& town : train_to_towns[train]) {
            cout << town << " ";
        }
        cout << endl;
    } else {
        cout << "Поезд " << train << " не найден." << endl;
    }
}

void trains() {
    cout << "Все поезда и их остановки:" << endl;
    for (const auto& [train, towns] : train_to_towns) {
        cout << "Поезд: " << train << ", Остановки: ";
        for (const auto& town : towns) {
            cout << town << " ";
        }
        cout << endl;
    }
}
