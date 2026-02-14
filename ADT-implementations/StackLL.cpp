#include <iostream>
#include <cassert>
using namespace std;

struct Node {
    int data;
    Node* next;
};

struct Stack {
    Node* top;
    int size;
};

bool isEmpty(Stack* s) {
    return s->top == nullptr && s->size == 0;
}

Stack* createStack() {
    Stack *newStack = new Stack{nullptr, 0};
    assert(isEmpty(newStack));
    return newStack;
}

void destroyStack(Stack* s) {
    if (isEmpty(s)) { return; }

    Node *cur = s->top;
    while (cur) {
        Node *temp = cur->next;
        delete cur;
        cur = temp;
    }
    s->top = nullptr;
    s->size = 0;
}

void push(Stack* s, int value) {
    Node *newNode = new Node{value, s->top};
    s->top = newNode;
    s->size++;
}

int pop(Stack* s) {
    assert(!isEmpty(s));
    Node *temp = s->top->next;
    int output = s->top->data;
    delete s->top;
    s->top = temp;
    s->size--;
    return output;
}

int peek(Stack* s) {
    assert(!isEmpty(s));
    return s->top->data;
}

void print(Stack* s) {
    Node *cur = s->top;
    while(cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}

int main() {

    // ── empty stack ──────────────────────────────────────────────────────────
    cout << "[empty stack]\n";
    {
        Stack* s = createStack();
        assert(isEmpty(s) == true);
        assert(s->size    == 0);
        assert(s->top     == nullptr);
        destroyStack(s);
        cout << "  PASSED\n";
    }

    // ── single push / pop ────────────────────────────────────────────────────
    cout << "[single push / pop]\n";
    {
        Stack* s = createStack();
        push(s, 42);
        assert(isEmpty(s)    == false);
        assert(s->size       == 1);
        assert(peek(s)       == 42);
        assert(s->top        != nullptr);
        assert(s->top->next  == nullptr);

        int val = pop(s);
        assert(val        == 42);
        assert(isEmpty(s) == true);
        assert(s->size    == 0);
        assert(s->top     == nullptr);
        destroyStack(s);
        cout << "  PASSED\n";
    }

    // ── LIFO order ───────────────────────────────────────────────────────────
    cout << "[LIFO order]\n";
    {
        Stack* s = createStack();
        push(s, 1);
        push(s, 2);
        push(s, 3);
        push(s, 4);
        push(s, 5);

        assert(s->size  == 5);
        assert(peek(s)  == 5);   // last in, first out

        assert(pop(s)   == 5);
        assert(pop(s)   == 4);
        assert(pop(s)   == 3);
        assert(pop(s)   == 2);
        assert(pop(s)   == 1);

        assert(isEmpty(s) == true);
        destroyStack(s);
        cout << "  PASSED\n";
    }

    // ── size tracking ────────────────────────────────────────────────────────
    cout << "[size tracking]\n";
    {
        Stack* s = createStack();
        for (int i = 0; i < 10; i++) {
            push(s, i);
            assert(s->size == i + 1);
        }
        for (int i = 10; i > 0; i--) {
            assert(s->size == i);
            pop(s);
        }
        assert(s->size == 0);
        destroyStack(s);
        cout << "  PASSED\n";
    }

    // ── peek does not remove ─────────────────────────────────────────────────
    cout << "[peek does not remove]\n";
    {
        Stack* s = createStack();
        push(s, 7);
        push(s, 8);
        assert(peek(s) == 8);
        assert(peek(s) == 8);
        assert(s->size == 2);
        destroyStack(s);
        cout << "  PASSED\n";
    }

    // ── top pointer tracks correctly ─────────────────────────────────────────
    cout << "[top pointer tracking]\n";
    {
        Stack* s = createStack();
        push(s, 10);
        assert(s->top->data == 10);
        push(s, 20);
        assert(s->top->data == 20);
        push(s, 30);
        assert(s->top->data == 30);
        pop(s);
        assert(s->top->data == 20);
        pop(s);
        assert(s->top->data == 10);
        pop(s);
        assert(s->top == nullptr);
        destroyStack(s);
        cout << "  PASSED\n";
    }

    // ── interleaved push / pop ───────────────────────────────────────────────
    cout << "[interleaved push / pop]\n";
    {
        Stack* s = createStack();
        push(s, 1);
        push(s, 2);
        assert(pop(s) == 2);
        push(s, 3);
        push(s, 4);
        assert(pop(s) == 4);
        assert(pop(s) == 3);
        push(s, 5);
        assert(pop(s) == 5);
        assert(pop(s) == 1);
        assert(isEmpty(s) == true);
        destroyStack(s);
        cout << "  PASSED\n";
    }

    // ── negative and zero values ─────────────────────────────────────────────
    cout << "[negative and zero values]\n";
    {
        Stack* s = createStack();
        push(s, -10);
        push(s,   0);
        push(s,  -1);
        assert(pop(s) == -1);
        assert(pop(s) ==  0);
        assert(pop(s) == -10);
        assert(isEmpty(s) == true);
        destroyStack(s);
        cout << "  PASSED\n";
    }

    // ── large push then pop ──────────────────────────────────────────────────
    cout << "[large push then pop]\n";
    {
        Stack* s = createStack();
        for (int i = 0; i < 1000; i++) push(s, i);
        assert(s->size == 1000);
        for (int i = 999; i >= 0; i--) {
            assert(peek(s) == i);
            assert(pop(s)  == i);
        }
        assert(isEmpty(s) == true);
        destroyStack(s);
        cout << "  PASSED\n";
    }

    // ── push after full drain ────────────────────────────────────────────────
    cout << "[push after full drain]\n";
    {
        Stack* s = createStack();
        push(s, 1);
        push(s, 2);
        pop(s);
        pop(s);
        assert(isEmpty(s) == true);

        push(s, 99);
        assert(s->size  == 1);
        assert(peek(s)  == 99);
        assert(pop(s)   == 99);
        assert(isEmpty(s) == true);
        destroyStack(s);
        cout << "  PASSED\n";
    }

    cout << "\n✓ All stack tests passed.\n";
    return 0;
}
