#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

// Структура для представления человека
struct Person {
    string name;
    vector<Person*> friends;
};

// Функция для поиска всех пар знакомств через три рукопожатия
void findFriendPairs(Person* startPerson) {
    // Используем очередь для обхода в ширину
    queue<pair<Person*, int>> bfsQueue;
    bfsQueue.push({ startPerson, 0 });

    // Множество для отслеживания посещенных людей
    unordered_set<Person*> visited;

    while (!bfsQueue.empty()) {
        auto current = bfsQueue.front();
        bfsQueue.pop();

        Person* currentPerson = current.first;
        int distance = current.second;

        // Пропускаем уже посещенных людей
        if (visited.count(currentPerson) > 0) {
            continue;
        }

        // Помечаем текущего человека как посещенного
        visited.insert(currentPerson);

        // Обрабатываем знакомых текущего человека
        for (Person* friendPerson : currentPerson->friends) {
            // Добавляем знакомых в очередь с увеличенным расстоянием
            bfsQueue.push({ friendPerson, distance + 1 });

            // Проверяем, если расстояние до знакомого не превышает 3, выводим пару
            if (distance + 1 <= 3) {
                cout << currentPerson->name << " - " << friendPerson->name << endl;
            }
        }
    }
}

int main() {
    // Пример графа социальных связей
    // В данном случае, используем простой список смежности
    Person alice{ "Alice" };
    Person bob{ "Bob" };
    Person charlie{ "Charlie" };
    Person dave{ "Dave" };
    Person eve{ "Eve" };

    alice.friends = { &bob, &charlie };
    bob.friends = { &alice, &charlie, &dave };
    charlie.friends = { &alice, &bob, &dave };
    dave.friends = { &bob, &charlie, &eve };
    eve.friends = { &dave };

    // Начинаем поиск пар знакомств
    findFriendPairs(&alice);

    return 0;
}
