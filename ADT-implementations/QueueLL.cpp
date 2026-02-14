#include <iostream>
#include <cassert>
using namespace std;

struct Node {
    int data;
    Node* next;
};

struct Queue {
    Node* head;
    Node* tail;
    int size;
};

bool isEmpty(Queue* q) {
    return q->head == nullptr && q->tail == nullptr && q->size == 0;
}

Queue* createQueue() {
    Queue *q = new Queue{nullptr, nullptr, 0};
    assert(isEmpty(q));
    return q;
}

void destroyQueue(Queue* q) {
    Node *cur = q->head;
    while (cur) {
        Node *temp = cur->next;
        delete cur;
        cur = temp;
    }
    q->head = q->tail = nullptr;
    q->size = 0;
    delete q;
}

void enqueue(Queue* q, int value) {
    Node *n = new Node{value, nullptr};
    if (isEmpty(q)) {
        q->head = q->tail = n;
    } else {
        q->tail->next = n;
        q->tail = q->tail->next;
    }
    q->size++;
}

int dequeue(Queue* q) {
    assert(!isEmpty(q));
    Node *temp = q->head->next;
    int output = q->head->data;
    delete q->head;
    q->head = temp;
    if(!q->head) { q->tail = nullptr; }
    q->size--;
    return output;
}

int peek(Queue* q) {
    assert(!isEmpty(q));
    return q->head->data;
}

void print(Queue* q) {
    Node *cur = q->head;
    while (cur) {
        cout << cur->data;
        if (cur->next) { cout << "->"; }
        cur = cur->next;
    }
    cout << endl;
}

int main() {

    // ── empty queue ──────────────────────────────────────────────────────────
    cout << "[empty queue]\n";
    {
        Queue* q = createQueue();
        assert(isEmpty(q)  == true);
        assert(q->size     == 0);
        assert(q->head     == nullptr);
        assert(q->tail     == nullptr);
        destroyQueue(q);
        cout << "  PASSED\n";
    }

    // ── single enqueue / dequeue ─────────────────────────────────────────────
    cout << "[single enqueue / dequeue]\n";
    {
        Queue* q = createQueue();
        enqueue(q, 42);
        assert(isEmpty(q)  == false);
        assert(q->size     == 1);
        assert(peek(q)     == 42);
        assert(q->head     != nullptr);
        assert(q->tail     != nullptr);
        assert(q->head     == q->tail);   // only one node, head and tail point to same

        int val = dequeue(q);
        assert(val         == 42);
        assert(isEmpty(q)  == true);
        assert(q->size     == 0);
        assert(q->head     == nullptr);
        assert(q->tail     == nullptr);
        destroyQueue(q);
        cout << "  PASSED\n";
    }

    // ── FIFO order ───────────────────────────────────────────────────────────
    cout << "[FIFO order]\n";
    {
        Queue* q = createQueue();
        enqueue(q, 1);
        enqueue(q, 2);
        enqueue(q, 3);
        enqueue(q, 4);
        enqueue(q, 5);

        assert(q->size    == 5);
        assert(peek(q)    == 1);

        assert(dequeue(q) == 1);
        assert(dequeue(q) == 2);
        assert(dequeue(q) == 3);
        assert(dequeue(q) == 4);
        assert(dequeue(q) == 5);

        assert(isEmpty(q) == true);
        assert(q->size    == 0);
        destroyQueue(q);
        cout << "  PASSED\n";
    }

    // ── size tracking ────────────────────────────────────────────────────────
    cout << "[size tracking]\n";
    {
        Queue* q = createQueue();
        for (int i = 0; i < 10; i++) {
            enqueue(q, i);
            assert(q->size == i + 1);
        }
        for (int i = 10; i > 0; i--) {
            assert(q->size == i);
            dequeue(q);
        }
        assert(q->size == 0);
        destroyQueue(q);
        cout << "  PASSED\n";
    }

    // ── peek does not remove ─────────────────────────────────────────────────
    cout << "[peek does not remove]\n";
    {
        Queue* q = createQueue();
        enqueue(q, 99);
        enqueue(q, 100);
        assert(peek(q) == 99);
        assert(peek(q) == 99);
        assert(q->size == 2);
        destroyQueue(q);
        cout << "  PASSED\n";
    }

    // ── interleaved enqueue / dequeue ────────────────────────────────────────
    cout << "[interleaved enqueue / dequeue]\n";
    {
        Queue* q = createQueue();
        enqueue(q, 10);
        enqueue(q, 20);
        assert(dequeue(q) == 10);
        enqueue(q, 30);
        enqueue(q, 40);
        assert(dequeue(q) == 20);
        assert(dequeue(q) == 30);
        enqueue(q, 50);
        assert(dequeue(q) == 40);
        assert(dequeue(q) == 50);
        assert(isEmpty(q) == true);
        destroyQueue(q);
        cout << "  PASSED\n";
    }

    // ── negative and zero values ─────────────────────────────────────────────
    cout << "[negative and zero values]\n";
    {
        Queue* q = createQueue();
        enqueue(q, -5);
        enqueue(q,  0);
        enqueue(q, -1);
        assert(dequeue(q) == -5);
        assert(dequeue(q) ==  0);
        assert(dequeue(q) == -1);
        assert(isEmpty(q) == true);
        destroyQueue(q);
        cout << "  PASSED\n";
    }

    // ── large enqueue then dequeue ───────────────────────────────────────────
    cout << "[large sequential enqueue then dequeue]\n";
    {
        Queue* q = createQueue();
        for (int i = 0; i < 1000; i++) enqueue(q, i);
        assert(q->size == 1000);
        for (int i = 0; i < 1000; i++) {
            assert(peek(q)    == i);
            assert(dequeue(q) == i);
        }
        assert(isEmpty(q) == true);
        destroyQueue(q);
        cout << "  PASSED\n";
    }

    // ── head and tail pointer consistency ────────────────────────────────────
    cout << "[head and tail pointer consistency]\n";
    {
        Queue* q = createQueue();
        enqueue(q, 1);
        enqueue(q, 2);
        enqueue(q, 3);
        assert(q->head->data == 1);
        assert(q->tail->data == 3);
        dequeue(q);
        assert(q->head->data == 2);
        assert(q->tail->data == 3);
        dequeue(q);
        assert(q->head->data == 3);
        assert(q->tail->data == 3);
        assert(q->head == q->tail);
        dequeue(q);
        assert(q->head == nullptr);
        assert(q->tail == nullptr);
        destroyQueue(q);
        cout << "  PASSED\n";
    }

    // ── enqueue after full drain ─────────────────────────────────────────────
    cout << "[enqueue after full drain]\n";
    {
        Queue* q = createQueue();
        enqueue(q, 1);
        enqueue(q, 2);
        dequeue(q);
        dequeue(q);
        assert(isEmpty(q) == true);

        // queue was drained — make sure it still works after
        enqueue(q, 7);
        enqueue(q, 8);
        assert(q->size    == 2);
        assert(peek(q)    == 7);
        assert(dequeue(q) == 7);
        assert(dequeue(q) == 8);
        assert(isEmpty(q) == true);
        destroyQueue(q);
        cout << "  PASSED\n";
    }

    cout << "\n✓ All queue tests passed.\n";
    return 0;
}
