#include <iostream>
#include <cassert>

using namespace std;

void hanoi (int numOfRings, int sourceTower, int destinationTower, int otherTower, int &count) {
    if (numOfRings <= 0) {
        return;
    }
    
    hanoi(numOfRings - 1, sourceTower, otherTower, destinationTower, count);
    cout << "Moved from " << sourceTower << " to " << destinationTower << endl;
    count++;
    hanoi(numOfRings - 1, otherTower, destinationTower, sourceTower, count);
}

int main() {
    int numOfRings;
    cout << "Enter number of rings: ";
    cin >> numOfRings;

    int count = 0;
    hanoi(numOfRings, 1, 3, 2, count);
    cout << "Total moves: " << count << endl;
}
