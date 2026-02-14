#include <cassert>
#include <iostream>

struct Heap {
    std::vector<int> data;
};

int heapSize(const Heap &h) { return h.data.size(); }

int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }
int parent(int i) { return (i - 1) / 2; }

bool hasLeft(const Heap &h, int i) { return left(i) < heapSize(h); }
bool hasRight(const Heap &h, int i) { return right(i) < heapSize(h); }
bool hasParent(int i) { return i > 0; }

int leftVal(const Heap &h, int i) { return h.data[left(i)]; }
int rightVal(const Heap &h, int i) { return h.data[right(i)]; }
int parentVal(const Heap &h, int i) { return h.data[parent(i)]; }

void swap(Heap &h, int i, int j) {
    int temp = h.data[i];
    h.data[i] = h.data[j];
    h.data[j] = temp;
}

int peek(const Heap &h) {
    assert(heapSize(h) != 0);
    return h.data[0];
}

void heapifyUp(Heap &h, int i) {
    while (hasParent(i) && parentVal(h, i) < h.data[i]) {
        swap(h, parent(i), i);
        i = parent(i);
    }
}

void heapifyDown(Heap &h, int i) {
    while (hasLeft(h, i)) {
        int largerIndex = left(i);
        if (hasRight(h, i) && rightVal(h, i) > leftVal(h, i)) {
            largerIndex = right(i);
        }

        if (h.data[i] >= h.data[largerIndex]) {
            break;
        }

        swap(h, i, largerIndex);
        i = largerIndex;
    }
}

void add(Heap &h, int val) {
    h.data.push_back(val);
    heapifyUp(h, heapSize(h) - 1);
}

int poll(Heap &h) {
    assert(heapSize(h) != 0);

    int maximum = h.data[0];
    h.data[0] = h.data.back();
    h.data.pop_back();

    if (heapSize(h) > 0) {
        heapifyDown(h, 0);
    }

    return maximum;
}

int main() {
    Heap h;
    add(h, 10);
    add(h, 20);
    add(h, 5);
    add(h, 30);
    add(h, 25);
    assert(peek(h) == 30);
    assert(heapSize(h) == 5);
    int max1 = poll(h);
    assert(max1 == 30);
    assert(peek(h) == 25);
    int max2 = poll(h);
    assert(max2 == 25);
    assert(peek(h) == 20);
    int max3 = poll(h);
    assert(max3 == 20);
    assert(peek(h) == 10);
    int max4 = poll(h);
    assert(max4 == 10);
    assert(peek(h) == 5);
    int max5 = poll(h);
    assert(max5 == 5);
    assert(heapSize(h) == 0);
    add(h, 100);
    add(h, 50);
    add(h, 150);
    assert(peek(h) == 150);
    assert(heapSize(h) == 3);
    assert(poll(h) == 150);
    assert(poll(h) == 100);
    assert(poll(h) == 50);
    assert(heapSize(h) == 0);
    add(h, 42);
    assert(peek(h) == 42);
    assert(poll(h) == 42);
    assert(heapSize(h) == 0);
    std::cout << "All heap tests passed!\n";
    return 0;
}
