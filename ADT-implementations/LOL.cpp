#include <iostream>
#include <cassert>
using namespace std;

struct LOLInnerNode {
    int data;
    LOLInnerNode* next;
};

struct LOLOuterNode {
    LOLInnerNode* innerHead;
    LOLOuterNode* next;
    int innerSize;
};

struct LOL {
    LOLOuterNode* head;
    int outerSize;
};

LOLOuterNode* getOuterNode(LOL* lol, int outerIndex) {

}

LOL* createLOL() {

}

void destroyLOL(LOL* lol) {

}

void addList(LOL* lol) {

}

void removeList(LOL* lol, int outerIndex) {

}

void insertToList(LOL* lol, int outerIndex, int value) {

}

void removeFromList(LOL* lol, int outerIndex, int value) {

}

int getElement(LOL* lol, int outerIndex, int innerIndex) {    // returns -1 if not found

}

int getOuterSize(LOL* lol) {

}

int getInnerSize(LOL* lol, int outerIndex) {

}

void print(LOL* lol) {

}

int main() {

    // ── empty LOL ────────────────────────────────────────────────────────────
    cout << "[empty LOL]\n";
    {
        LOL* lol = createLOL();
        assert(lol->head       == nullptr);
        assert(getOuterSize(lol) == 0);
        destroyLOL(lol);
        cout << "  PASSED\n";
    }

    // ── addList creates empty inner lists ────────────────────────────────────
    cout << "[addList]\n";
    {
        LOL* lol = createLOL();
        addList(lol);
        assert(getOuterSize(lol)    == 1);
        assert(getInnerSize(lol, 0) == 0);

        addList(lol);
        assert(getOuterSize(lol)    == 2);
        assert(getInnerSize(lol, 1) == 0);

        addList(lol);
        assert(getOuterSize(lol) == 3);
        destroyLOL(lol);
        cout << "  PASSED\n";
    }

    // ── insertToList and getElement ──────────────────────────────────────────
    cout << "[insertToList and getElement]\n";
    {
        LOL* lol = createLOL();
        addList(lol);
        insertToList(lol, 0, 10);
        insertToList(lol, 0, 20);
        insertToList(lol, 0, 30);

        assert(getInnerSize(lol, 0) == 3);
        assert(getElement(lol, 0, 0) == 10);
        assert(getElement(lol, 0, 1) == 20);
        assert(getElement(lol, 0, 2) == 30);
        destroyLOL(lol);
        cout << "  PASSED\n";
    }

    // ── multiple inner lists independent ────────────────────────────────────
    cout << "[multiple inner lists are independent]\n";
    {
        LOL* lol = createLOL();
        addList(lol);
        addList(lol);
        addList(lol);

        insertToList(lol, 0, 1);
        insertToList(lol, 0, 2);

        insertToList(lol, 1, 10);
        insertToList(lol, 1, 20);
        insertToList(lol, 1, 30);

        insertToList(lol, 2, 99);

        assert(getInnerSize(lol, 0) == 2);
        assert(getInnerSize(lol, 1) == 3);
        assert(getInnerSize(lol, 2) == 1);

        assert(getElement(lol, 0, 0) == 1);
        assert(getElement(lol, 0, 1) == 2);
        assert(getElement(lol, 1, 0) == 10);
        assert(getElement(lol, 1, 1) == 20);
        assert(getElement(lol, 1, 2) == 30);
        assert(getElement(lol, 2, 0) == 99);
        destroyLOL(lol);
        cout << "  PASSED\n";
    }

    // ── getElement out of bounds returns -1 ──────────────────────────────────
    cout << "[getElement out of bounds]\n";
    {
        LOL* lol = createLOL();
        addList(lol);
        insertToList(lol, 0, 42);

        assert(getElement(lol, 0, 1)  == -1);   // inner index OOB
        assert(getElement(lol, 1, 0)  == -1);   // outer index OOB
        assert(getElement(lol, 99, 0) == -1);
        destroyLOL(lol);
        cout << "  PASSED\n";
    }

    // ── removeFromList ────────────────────────────────────────────────────────
    cout << "[removeFromList]\n";
    {
        LOL* lol = createLOL();
        addList(lol);
        insertToList(lol, 0, 5);
        insertToList(lol, 0, 10);
        insertToList(lol, 0, 15);

        removeFromList(lol, 0, 10);              // remove middle
        assert(getInnerSize(lol, 0) == 2);
        assert(getElement(lol, 0, 0) == 5);
        assert(getElement(lol, 0, 1) == 15);

        removeFromList(lol, 0, 5);               // remove head
        assert(getInnerSize(lol, 0) == 1);
        assert(getElement(lol, 0, 0) == 15);

        removeFromList(lol, 0, 15);              // remove last
        assert(getInnerSize(lol, 0) == 0);
        destroyLOL(lol);
        cout << "  PASSED\n";
    }

    // ── removeFromList non-existent value ────────────────────────────────────
    cout << "[removeFromList non-existent value]\n";
    {
        LOL* lol = createLOL();
        addList(lol);
        insertToList(lol, 0, 1);
        insertToList(lol, 0, 2);

        removeFromList(lol, 0, 999);    // not in list — should not crash
        assert(getInnerSize(lol, 0) == 2);
        destroyLOL(lol);
        cout << "  PASSED\n";
    }

    // ── removeList ────────────────────────────────────────────────────────────
    cout << "[removeList]\n";
    {
        LOL* lol = createLOL();
        addList(lol);   // 0
        addList(lol);   // 1
        addList(lol);   // 2
        insertToList(lol, 0, 100);
        insertToList(lol, 1, 200);
        insertToList(lol, 2, 300);

        removeList(lol, 1);                      // remove middle list
        assert(getOuterSize(lol)     == 2);
        assert(getElement(lol, 0, 0) == 100);
        assert(getElement(lol, 1, 0) == 300);   // was index 2, now index 1

        removeList(lol, 0);                      // remove head list
        assert(getOuterSize(lol)     == 1);
        assert(getElement(lol, 0, 0) == 300);

        removeList(lol, 0);                      // remove last list
        assert(getOuterSize(lol) == 0);
        assert(lol->head         == nullptr);
        destroyLOL(lol);
        cout << "  PASSED\n";
    }

    // ── outerSize and innerSize tracking ────────────────────────────────────
    cout << "[size tracking]\n";
    {
        LOL* lol = createLOL();
        for (int i = 0; i < 5; i++) {
            addList(lol);
            assert(getOuterSize(lol) == i + 1);
        }
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 3; j++) {
                insertToList(lol, i, j * 10);
            }
            assert(getInnerSize(lol, i) == 3);
        }
        destroyLOL(lol);
        cout << "  PASSED\n";
    }

    // ── getOuterNode returns correct node ────────────────────────────────────
    cout << "[getOuterNode helper]\n";
    {
        LOL* lol = createLOL();
        addList(lol);
        addList(lol);
        addList(lol);
        insertToList(lol, 0, 7);
        insertToList(lol, 1, 8);
        insertToList(lol, 2, 9);

        LOLOuterNode* node0 = getOuterNode(lol, 0);
        LOLOuterNode* node1 = getOuterNode(lol, 1);
        LOLOuterNode* node2 = getOuterNode(lol, 2);

        assert(node0 != nullptr && node0->innerHead->data == 7);
        assert(node1 != nullptr && node1->innerHead->data == 8);
        assert(node2 != nullptr && node2->innerHead->data == 9);
        assert(getOuterNode(lol, 99) == nullptr);    // OOB returns nullptr
        destroyLOL(lol);
        cout << "  PASSED\n";
    }

    cout << "\n✓ All LOL tests passed.\n";
    return 0;
}
