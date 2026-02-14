#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

struct NaryNode {
    int data;
    vector<NaryNode*> children;
};

struct NaryTree {
    NaryNode* root;
    int n;           // max children per node
};

// ─── Helpers ─────────────────────────────────────────────────────────────────

NaryNode* searchHelper(NaryNode* node, int value) {

}

void preorderHelper(NaryNode* node) {

}

void postorderHelper(NaryNode* node) {

}

int heightHelper(NaryNode* node) {

}

int countHelper(NaryNode* node) {

}

void destroyHelper(NaryNode* node) {

}

// ─── Core ─────────────────────────────────────────────────────────────────────

NaryNode* createNaryNode(int value) {

}

NaryTree* createNaryTree(int n) {

}

void destroyNaryTree(NaryTree* tree) {

}

NaryNode* insert(NaryTree* tree, NaryNode* parent, int value) {    // returns new node, nullptr if parent full

}

NaryNode* search(NaryTree* tree, int value) {

}

void removeNode(NaryTree* tree, int value) {

}

int height(NaryTree* tree) {

}

int countNodes(NaryTree* tree) {

}

void printPreorder(NaryTree* tree) {

}

void printPostorder(NaryTree* tree) {

}

void printLevelOrder(NaryTree* tree) {

}

// ─── Test helpers ─────────────────────────────────────────────────────────────

void collectPreorder(NaryNode* node, vector<int>& out) {
    if (node == nullptr) return;
    out.push_back(node->data);
    for (NaryNode* child : node->children) collectPreorder(child, out);
}

void collectPostorder(NaryNode* node, vector<int>& out) {
    if (node == nullptr) return;
    for (NaryNode* child : node->children) collectPostorder(child, out);
    out.push_back(node->data);
}

int main() {

    // ── empty tree ───────────────────────────────────────────────────────────
    cout << "[empty tree]\n";
    {
        NaryTree* tree = createNaryTree(3);
        assert(tree->root    == nullptr);
        assert(tree->n       == 3);
        assert(countNodes(tree) == 0);
        assert(height(tree)     == 0);
        assert(search(tree, 1)  == nullptr);
        destroyNaryTree(tree);
        cout << "  PASSED\n";
    }

    // ── insert root ──────────────────────────────────────────────────────────
    cout << "[insert root]\n";
    {
        NaryTree* tree = createNaryTree(3);
        NaryNode* root = insert(tree, nullptr, 1);  // nullptr parent = insert as root
        assert(root             != nullptr);
        assert(root->data       == 1);
        assert(tree->root       == root);
        assert(countNodes(tree) == 1);
        assert(height(tree)     == 1);
        destroyNaryTree(tree);
        cout << "  PASSED\n";
    }

    // ── insert children ──────────────────────────────────────────────────────
    cout << "[insert children]\n";
    {
        NaryTree* tree = createNaryTree(3);
        NaryNode* root = insert(tree, nullptr, 1);
        NaryNode* c1   = insert(tree, root, 2);
        NaryNode* c2   = insert(tree, root, 3);
        NaryNode* c3   = insert(tree, root, 4);

        assert(countNodes(tree)      == 4);
        assert(root->children.size() == 3);
        assert(root->children[0]     == c1);
        assert(root->children[1]     == c2);
        assert(root->children[2]     == c3);
        destroyNaryTree(tree);
        cout << "  PASSED\n";
    }

    // ── insert returns nullptr when parent is full ───────────────────────────
    cout << "[insert returns nullptr when parent full]\n";
    {
        NaryTree* tree = createNaryTree(2);        // max 2 children
        NaryNode* root = insert(tree, nullptr, 1);
        insert(tree, root, 2);
        insert(tree, root, 3);

        NaryNode* overflow = insert(tree, root, 4); // parent already has 2 children
        assert(overflow == nullptr);
        assert(countNodes(tree)      == 3);
        assert(root->children.size() == 2);
        destroyNaryTree(tree);
        cout << "  PASSED\n";
    }

    // ── search found and not found ───────────────────────────────────────────
    cout << "[search]\n";
    {
        NaryTree* tree = createNaryTree(3);
        NaryNode* root = insert(tree, nullptr, 10);
        NaryNode* c1   = insert(tree, root, 20);
        NaryNode* c2   = insert(tree, root, 30);
                         insert(tree, c1,   40);
                         insert(tree, c1,   50);
                         insert(tree, c2,   60);

        assert(search(tree, 10) == root);
        assert(search(tree, 20) == c1);
        assert(search(tree, 60) != nullptr);
        assert(search(tree, 60)->data == 60);

        assert(search(tree, 99)  == nullptr);
        assert(search(tree, -1)  == nullptr);
        assert(search(tree, 0)   == nullptr);
        destroyNaryTree(tree);
        cout << "  PASSED\n";
    }

    // ── height ────────────────────────────────────────────────────────────────
    cout << "[height]\n";
    {
        NaryTree* tree = createNaryTree(3);
        NaryNode* root = insert(tree, nullptr, 1);
        assert(height(tree) == 1);

        NaryNode* c1 = insert(tree, root, 2);
        assert(height(tree) == 2);

        NaryNode* gc1 = insert(tree, c1, 3);
        assert(height(tree) == 3);

        insert(tree, gc1, 4);
        assert(height(tree) == 4);

        // sibling branch — doesn't increase height
        insert(tree, root, 5);
        assert(height(tree) == 4);
        destroyNaryTree(tree);
        cout << "  PASSED\n";
    }

    // ── countNodes ────────────────────────────────────────────────────────────
    cout << "[countNodes]\n";
    {
        NaryTree* tree = createNaryTree(4);
        assert(countNodes(tree) == 0);

        NaryNode* root = insert(tree, nullptr, 1);
        assert(countNodes(tree) == 1);

        NaryNode* c1 = insert(tree, root, 2);
        NaryNode* c2 = insert(tree, root, 3);
        assert(countNodes(tree) == 3);

        insert(tree, c1, 4);
        insert(tree, c1, 5);
        insert(tree, c2, 6);
        assert(countNodes(tree) == 6);
        destroyNaryTree(tree);
        cout << "  PASSED\n";
    }

    // ── removeNode leaf ───────────────────────────────────────────────────────
    cout << "[removeNode leaf]\n";
    {
        NaryTree* tree = createNaryTree(3);
        NaryNode* root = insert(tree, nullptr, 1);
        insert(tree, root, 2);
        insert(tree, root, 3);
        insert(tree, root, 4);

        removeNode(tree, 3);
        assert(countNodes(tree)      == 3);
        assert(search(tree, 3)       == nullptr);
        assert(root->children.size() == 2);
        destroyNaryTree(tree);
        cout << "  PASSED\n";
    }

    // ── removeNode non-existent ───────────────────────────────────────────────
    cout << "[removeNode non-existent value]\n";
    {
        NaryTree* tree = createNaryTree(3);
        NaryNode* root = insert(tree, nullptr, 1);
        insert(tree, root, 2);
        insert(tree, root, 3);

        removeNode(tree, 99);               // not in tree — should not crash
        assert(countNodes(tree) == 3);
        destroyNaryTree(tree);
        cout << "  PASSED\n";
    }

    // ── n=1 (degenerate linked list) ─────────────────────────────────────────
    cout << "[n=1 degenerate case (linear chain)]\n";
    {
        NaryTree* tree = createNaryTree(1);
        NaryNode* n1 = insert(tree, nullptr, 10);
        NaryNode* n2 = insert(tree, n1, 20);
        NaryNode* n3 = insert(tree, n2, 30);
        NaryNode* n4 = insert(tree, n3, 40);

        assert(countNodes(tree) == 4);
        assert(height(tree)     == 4);

        // try adding second child to n1 — should fail
        assert(insert(tree, n1, 99) == nullptr);

        vector<int> pre;
        collectPreorder(tree->root, pre);
        assert(pre == vector<int>({10, 20, 30, 40}));
        destroyNaryTree(tree);
        cout << "  PASSED\n";
    }

    // ── preorder traversal ────────────────────────────────────────────────────
    cout << "[preorder traversal]\n";
    {
        //        1
        //      / | \
        //     2  3  4
        //    / \
        //   5   6
        NaryTree* tree = createNaryTree(3);
        NaryNode* root = insert(tree, nullptr, 1);
        NaryNode* c1   = insert(tree, root, 2);
                         insert(tree, root, 3);
                         insert(tree, root, 4);
                         insert(tree, c1,   5);
                         insert(tree, c1,   6);

        vector<int> pre;
        collectPreorder(tree->root, pre);
        assert(pre == vector<int>({1, 2, 5, 6, 3, 4}));
        destroyNaryTree(tree);
        cout << "  PASSED\n";
    }

    // ── postorder traversal ───────────────────────────────────────────────────
    cout << "[postorder traversal]\n";
    {
        //        1
        //      / | \
        //     2  3  4
        //    / \
        //   5   6
        NaryTree* tree = createNaryTree(3);
        NaryNode* root = insert(tree, nullptr, 1);
        NaryNode* c1   = insert(tree, root, 2);
                         insert(tree, root, 3);
                         insert(tree, root, 4);
                         insert(tree, c1,   5);
                         insert(tree, c1,   6);

        vector<int> post;
        collectPostorder(tree->root, post);
        assert(post == vector<int>({5, 6, 2, 3, 4, 1}));
        destroyNaryTree(tree);
        cout << "  PASSED\n";
    }

    // ── large tree count and height ───────────────────────────────────────────
    cout << "[large tree — count and height]\n";
    {
        // 4-ary tree: root has 4 children, each of those has 4 children
        // total: 1 + 4 + 16 = 21 nodes, height = 3
        NaryTree* tree = createNaryTree(4);
        NaryNode* root = insert(tree, nullptr, 0);
        for (int i = 1; i <= 4; i++) {
            NaryNode* child = insert(tree, root, i);
            for (int j = 1; j <= 4; j++) {
                insert(tree, child, i * 10 + j);
            }
        }
        assert(countNodes(tree) == 21);
        assert(height(tree)     == 3);
        destroyNaryTree(tree);
        cout << "  PASSED\n";
    }

    cout << "\n✓ All N-ary tree tests passed.\n";
    return 0;
}
