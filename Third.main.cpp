#include "train_system.h"

using namespace std;

int main() {
    while (true) {
        cout << "Введите команду (CREATE_TRAIN, TRAINS_FOR_TOWN, TOWNS_FOR_TRAIN, TRAINS или exit для выхода): ";
        string command_input;
        cin >> command_input;

        Command command = parse_command(command_input);

        switch (command) {
            case Command::CREATE_TRAIN: {
                string train;
                int n;
                cout << "Введите имя поезда: ";
                cin >> train;
                cout << "Введите количество городов: ";
                cin >> n;

                vector<string> towns(n);
                cout << "Введите названия городов: ";
                for (int i = 0; i < n; ++i) {
                    cin >> towns[i];
                }

                create_train(train, towns);
                break;
            }
            case Command::TRAINS_FOR_TOWN: {
                string town;
                cout << "Введите название города: ";
                cin >> town;
                trains_for_town(town);
                break;
            }
            case Command::TOWNS_FOR_TRAIN: {
                string train;
                cout << "Введите имя поезда: ";
                cin >> train;
                towns_for_train(train);
                break;
            }
            case Command::TRAINS:
                trains();
                break;
            case Command::EXIT:
                return 0;
            case Command::UNKNOWN:
            default:
                cout << "Неизвестная команда." << endl;
                break;
        }
    }

    return 0;
}
