#include <iostream>
#include <string>
#include <cassert>
using namespace std;

struct DictNode {
    string key;
    int value;
    DictNode* next;
};

struct Dict {
    DictNode* head;    // maintained in sorted key order (alphabetical)
    int size;
};

Dict* createDict() {

}

void destroyDict(Dict* dict) {

}

void insert(Dict* dict, const string& key, int value) {

}

void removeKey(Dict* dict, const string& key) {

}

void update(Dict* dict, const string& key, int value) {

}

int get(Dict* dict, const string& key) {    // returns -1 if not found

}

bool contains(Dict* dict, const string& key) {

}

bool isEmpty(Dict* dict) {

}

void print(Dict* dict) {

}

// helper: verify the linked list is in strict ascending key order
void assertSortedKeys(Dict* dict) {
    DictNode* curr = dict->head;
    while (curr != nullptr && curr->next != nullptr) {
        assert(curr->key < curr->next->key);
        curr = curr->next;
    }
}

int main() {

    // ── empty dict ───────────────────────────────────────────────────────────
    cout << "[empty dict]\n";
    {
        Dict* d = createDict();
        assert(isEmpty(d)         == true);
        assert(d->size            == 0);
        assert(d->head            == nullptr);
        assert(contains(d, "hi")  == false);
        assert(get(d, "hi")       == -1);
        destroyDict(d);
        cout << "  PASSED\n";
    }

    // ── single insert / get ──────────────────────────────────────────────────
    cout << "[single insert / get]\n";
    {
        Dict* d = createDict();
        insert(d, "apple", 1);
        assert(isEmpty(d)            == false);
        assert(d->size               == 1);
        assert(contains(d, "apple")  == true);
        assert(get(d, "apple")       == 1);
        assert(contains(d, "banana") == false);
        assert(get(d, "banana")      == -1);
        destroyDict(d);
        cout << "  PASSED\n";
    }

    // ── sorted order maintained ──────────────────────────────────────────────
    cout << "[sorted order maintained on insert]\n";
    {
        Dict* d = createDict();
        // insert out of alphabetical order
        insert(d, "mango",  3);
        insert(d, "apple",  1);
        insert(d, "cherry", 2);
        insert(d, "banana", 5);
        insert(d, "zucchini", 9);

        assertSortedKeys(d);
        assert(d->size == 5);

        // head should be "apple"
        assert(d->head->key == "apple");

        destroyDict(d);
        cout << "  PASSED\n";
    }

    // ── get returns correct values ───────────────────────────────────────────
    cout << "[get returns correct values]\n";
    {
        Dict* d = createDict();
        insert(d, "x", 10);
        insert(d, "y", 20);
        insert(d, "z", 30);

        assert(get(d, "x") == 10);
        assert(get(d, "y") == 20);
        assert(get(d, "z") == 30);
        assert(get(d, "w") == -1);   // not in dict
        destroyDict(d);
        cout << "  PASSED\n";
    }

    // ── update existing key ──────────────────────────────────────────────────
    cout << "[update existing key]\n";
    {
        Dict* d = createDict();
        insert(d, "score", 50);
        assert(get(d, "score") == 50);

        update(d, "score", 99);
        assert(get(d, "score") == 99);
        assert(d->size         == 1);   // no new node added
        assertSortedKeys(d);
        destroyDict(d);
        cout << "  PASSED\n";
    }

    // ── remove key ───────────────────────────────────────────────────────────
    cout << "[remove key]\n";
    {
        Dict* d = createDict();
        insert(d, "a", 1);
        insert(d, "b", 2);
        insert(d, "c", 3);

        removeKey(d, "b");                  // remove middle
        assert(d->size          == 2);
        assert(contains(d, "b") == false);
        assert(get(d, "b")      == -1);
        assertSortedKeys(d);

        removeKey(d, "a");                  // remove head
        assert(d->size          == 1);
        assert(d->head->key     == "c");

        removeKey(d, "c");                  // remove last
        assert(d->size          == 0);
        assert(isEmpty(d)       == true);
        assert(d->head          == nullptr);
        destroyDict(d);
        cout << "  PASSED\n";
    }

    // ── remove non-existent key ──────────────────────────────────────────────
    cout << "[remove non-existent key]\n";
    {
        Dict* d = createDict();
        insert(d, "cat", 5);
        insert(d, "dog", 10);

        removeKey(d, "fish");           // doesn't exist — should not crash
        assert(d->size == 2);
        assertSortedKeys(d);
        destroyDict(d);
        cout << "  PASSED\n";
    }

    // ── duplicate insert ─────────────────────────────────────────────────────
    cout << "[duplicate insert — key already exists]\n";
    {
        Dict* d = createDict();
        insert(d, "key", 1);
        insert(d, "key", 2);            // same key — should overwrite, not duplicate
        assert(d->size         == 1);
        assert(get(d, "key")   == 2);
        assertSortedKeys(d);
        destroyDict(d);
        cout << "  PASSED\n";
    }

    // ── contains ─────────────────────────────────────────────────────────────
    cout << "[contains]\n";
    {
        Dict* d = createDict();
        insert(d, "hello", 1);
        insert(d, "world", 2);
        assert(contains(d, "hello") == true);
        assert(contains(d, "world") == true);
        assert(contains(d, "foo")   == false);
        assert(contains(d, "")      == false);
        destroyDict(d);
        cout << "  PASSED\n";
    }

    // ── insert at head (alphabetically first) ────────────────────────────────
    cout << "[insert at head position]\n";
    {
        Dict* d = createDict();
        insert(d, "mango",  1);
        insert(d, "cherry", 2);
        insert(d, "apple",  3);        // should become new head each time

        assert(d->head->key == "apple");
        assertSortedKeys(d);
        destroyDict(d);
        cout << "  PASSED\n";
    }

    // ── insert at tail (alphabetically last) ─────────────────────────────────
    cout << "[insert at tail position]\n";
    {
        Dict* d = createDict();
        insert(d, "apple",   1);
        insert(d, "banana",  2);
        insert(d, "cherry",  3);
        insert(d, "zucchini",4);       // always tail

        DictNode* curr = d->head;
        while (curr->next != nullptr) curr = curr->next;
        assert(curr->key == "zucchini");
        assertSortedKeys(d);
        destroyDict(d);
        cout << "  PASSED\n";
    }

    // ── large insert and retrieval ────────────────────────────────────────────
    cout << "[large insert and retrieval]\n";
    {
        Dict* d = createDict();
        // insert keys "key000" through "key099"
        for (int i = 0; i < 100; i++) {
            string key = "key" + to_string(i);
            insert(d, key, i * 10);
        }
        assert(d->size == 100);
        assertSortedKeys(d);

        for (int i = 0; i < 100; i++) {
            string key = "key" + to_string(i);
            assert(contains(d, key)  == true);
            assert(get(d, key)       == i * 10);
        }
        assert(contains(d, "key100") == false);
        destroyDict(d);
        cout << "  PASSED\n";
    }

    cout << "\n✓ All ordered dictionary tests passed.\n";
    return 0;
}
