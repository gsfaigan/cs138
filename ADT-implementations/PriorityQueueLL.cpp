#include <iostream>
#include <cassert>
using namespace std;

struct PQNode {
    int data;
    int priority;    // higher int = higher priority
    PQNode* next;
};

struct PQ {
    PQNode* head;    // highest priority node at front
    int size;
};

PQ* createPQ() {

}

void destroyPQ(PQ* pq) {

}

void insert(PQ* pq, int value, int priority) {

}

int dequeue(PQ* pq) {

}

int peek(PQ* pq) {

}

bool isEmpty(PQ* pq) {

}

void print(PQ* pq) {

}

int main() {

    // ── empty PQ ─────────────────────────────────────────────────────────────
    cout << "[empty PQ]\n";
    {
        PQ* pq = createPQ();
        assert(isEmpty(pq) == true);
        assert(pq->size    == 0);
        assert(pq->head    == nullptr);
        destroyPQ(pq);
        cout << "  PASSED\n";
    }

    // ── single insert / dequeue ──────────────────────────────────────────────
    cout << "[single insert / dequeue]\n";
    {
        PQ* pq = createPQ();
        insert(pq, 100, 5);
        assert(isEmpty(pq)        == false);
        assert(pq->size           == 1);
        assert(peek(pq)           == 100);
        assert(pq->head->priority == 5);

        int val = dequeue(pq);
        assert(val        == 100);
        assert(isEmpty(pq) == true);
        assert(pq->size   == 0);
        assert(pq->head   == nullptr);
        destroyPQ(pq);
        cout << "  PASSED\n";
    }

    // ── highest priority dequeued first ─────────────────────────────────────
    cout << "[highest priority dequeued first]\n";
    {
        PQ* pq = createPQ();
        insert(pq, 10, 1);
        insert(pq, 20, 5);   // highest
        insert(pq, 30, 3);

        assert(pq->size == 3);
        assert(peek(pq) == 20);
        assert(dequeue(pq) == 20);
        assert(dequeue(pq) == 30);
        assert(dequeue(pq) == 10);
        assert(isEmpty(pq) == true);
        destroyPQ(pq);
        cout << "  PASSED\n";
    }

    // ── insert in already-sorted order ───────────────────────────────────────
    cout << "[insert in descending priority order]\n";
    {
        PQ* pq = createPQ();
        insert(pq, 1, 10);
        insert(pq, 2,  8);
        insert(pq, 3,  6);
        insert(pq, 4,  4);
        insert(pq, 5,  2);

        assert(dequeue(pq) == 1);
        assert(dequeue(pq) == 2);
        assert(dequeue(pq) == 3);
        assert(dequeue(pq) == 4);
        assert(dequeue(pq) == 5);
        assert(isEmpty(pq) == true);
        destroyPQ(pq);
        cout << "  PASSED\n";
    }

    // ── insert in reverse-sorted order ──────────────────────────────────────
    cout << "[insert in ascending priority order]\n";
    {
        PQ* pq = createPQ();
        insert(pq, 5, 1);
        insert(pq, 4, 3);
        insert(pq, 3, 5);
        insert(pq, 2, 7);
        insert(pq, 1, 9);   // inserted last but highest priority

        assert(peek(pq)    == 1);
        assert(dequeue(pq) == 1);
        assert(dequeue(pq) == 2);
        assert(dequeue(pq) == 3);
        assert(dequeue(pq) == 4);
        assert(dequeue(pq) == 5);
        assert(isEmpty(pq) == true);
        destroyPQ(pq);
        cout << "  PASSED\n";
    }

    // ── tied priorities maintain insert order (stable) ───────────────────────
    cout << "[tied priorities — stable ordering]\n";
    {
        PQ* pq = createPQ();
        insert(pq, 'A', 5);
        insert(pq, 'B', 5);
        insert(pq, 'C', 5);

        assert(pq->size == 3);
        // all same priority — first inserted should come out first
        assert(dequeue(pq) == 'A');
        assert(dequeue(pq) == 'B');
        assert(dequeue(pq) == 'C');
        assert(isEmpty(pq) == true);
        destroyPQ(pq);
        cout << "  PASSED\n";
    }

    // ── peek does not remove ─────────────────────────────────────────────────
    cout << "[peek does not remove]\n";
    {
        PQ* pq = createPQ();
        insert(pq, 77, 10);
        insert(pq, 88,  2);
        assert(peek(pq) == 77);
        assert(peek(pq) == 77);
        assert(pq->size == 2);
        destroyPQ(pq);
        cout << "  PASSED\n";
    }

    // ── size tracking ────────────────────────────────────────────────────────
    cout << "[size tracking]\n";
    {
        PQ* pq = createPQ();
        for (int i = 1; i <= 10; i++) {
            insert(pq, i, i);
            assert(pq->size == i);
        }
        for (int i = 10; i >= 1; i--) {
            assert(pq->size == i);
            dequeue(pq);
        }
        assert(pq->size == 0);
        destroyPQ(pq);
        cout << "  PASSED\n";
    }

    // ── head always has highest priority ────────────────────────────────────
    cout << "[head always has highest priority]\n";
    {
        PQ* pq = createPQ();
        insert(pq, 1, 3);
        assert(pq->head->priority == 3);
        insert(pq, 2, 7);            // higher — should become new head
        assert(pq->head->priority == 7);
        insert(pq, 3, 5);            // middle — head unchanged
        assert(pq->head->priority == 7);
        insert(pq, 4, 10);           // highest — new head
        assert(pq->head->priority == 10);
        destroyPQ(pq);
        cout << "  PASSED\n";
    }

    // ── interleaved insert / dequeue ─────────────────────────────────────────
    cout << "[interleaved insert / dequeue]\n";
    {
        PQ* pq = createPQ();
        insert(pq, 10, 2);
        insert(pq, 20, 8);
        assert(dequeue(pq) == 20);     // priority 8 out
        insert(pq, 30, 5);
        insert(pq, 40, 1);
        assert(dequeue(pq) == 30);     // priority 5 out
        assert(dequeue(pq) == 10);     // priority 2 out
        assert(dequeue(pq) == 40);     // priority 1 out
        assert(isEmpty(pq) == true);
        destroyPQ(pq);
        cout << "  PASSED\n";
    }

    // ── large insert then dequeue in priority order ──────────────────────────
    cout << "[large insert then dequeue in priority order]\n";
    {
        PQ* pq = createPQ();
        // insert 1..100 with priority = value (so 100 comes out first)
        for (int i = 1; i <= 100; i++) insert(pq, i, i);
        assert(pq->size == 100);
        for (int i = 100; i >= 1; i--) {
            assert(peek(pq)    == i);
            assert(dequeue(pq) == i);
        }
        assert(isEmpty(pq) == true);
        destroyPQ(pq);
        cout << "  PASSED\n";
    }

    cout << "\n✓ All priority queue tests passed.\n";
    return 0;
}
