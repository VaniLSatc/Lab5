#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

map<string, set<string>> friendships;

void addFriends(const string& a, const string& b) {
    friendships[a].insert(b);
    friendships[b].insert(a);
}

int countFriends(const string& person) {
    return friendships.count(person) ? friendships[person].size() : 0;
}

bool areFriends(const string& a, const string& b) {
    return friendships.count(a) && friendships[a].count(b);
}

int main() {
    int N;
    cin >> N;
    cin.ignore(); // Пропускаем оставшийся символ новой строки
    
    vector<string> output;

    for (int i = 0; i < N; ++i) {
        string user_answer;
        cin >> user_answer;

        if (user_answer == "FRIENDS") {
            string a, b;
            cin >> a >> b;
            addFriends(a, b);
        }
        else if (user_answer == "COUNT") {
            string person;
            cin >> person;
            output.push_back(to_string(countFriends(person)));
        }
        else if (user_answer == "QUESTION") {
            string a, b;
            cin >> a >> b;
            output.push_back(areFriends(a, b) ? "YES" : "NO");
        }
    }

    // Выводим все результаты
    for (const auto& result : output) {
        cout << result << endl;
    }

    return 0;
}
