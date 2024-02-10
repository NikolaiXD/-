#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

// ��������� ��� ������������� ��������
struct Person {
    string name;
    vector<Person*> friends;
};

// ������� ��� ������ ���� ��� ��������� ����� ��� �����������
void findFriendPairs(Person* startPerson) {
    // ���������� ������� ��� ������ � ������
    queue<pair<Person*, int>> bfsQueue;
    bfsQueue.push({ startPerson, 0 });

    // ��������� ��� ������������ ���������� �����
    unordered_set<Person*> visited;

    while (!bfsQueue.empty()) {
        auto current = bfsQueue.front();
        bfsQueue.pop();

        Person* currentPerson = current.first;
        int distance = current.second;

        // ���������� ��� ���������� �����
        if (visited.count(currentPerson) > 0) {
            continue;
        }

        // �������� �������� �������� ��� �����������
        visited.insert(currentPerson);

        // ������������ �������� �������� ��������
        for (Person* friendPerson : currentPerson->friends) {
            // ��������� �������� � ������� � ����������� �����������
            bfsQueue.push({ friendPerson, distance + 1 });

            // ���������, ���� ���������� �� ��������� �� ��������� 3, ������� ����
            if (distance + 1 <= 3) {
                cout << currentPerson->name << " - " << friendPerson->name << endl;
            }
        }
    }
}

int main() {
    // ������ ����� ���������� ������
    // � ������ ������, ���������� ������� ������ ���������
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

    // �������� ����� ��� ���������
    findFriendPairs(&alice);

    return 0;
}
