#include <iostream>
#include <cassert>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Enter a num: ";
    int i;
    cin >> i;
    cout << "You entered " << i << flush;
    assert(i > 0);
    cout << " which was actaully positive." << endl;
}
