#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
};

TreeNode* createNode(int value) {
    TreeNode *newNode = new TreeNode{};
    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

TreeNode* insert(TreeNode* root, int value) {
    if (root == nullptr) {
        return createNode(value);
    }

    if (value < root->data) { root->left = insert(root->left, value); }
    else if (value > root->data) { root->right = insert(root->right, value); }

    return root;
}

TreeNode* search(TreeNode* root, int value) {
    if (root == nullptr) return nullptr;

    if (value == root->data) { return root; }
    else if (value < root->data) { return search(root->left, value); }
    else { return search(root->right, value); }
}

void inorder(TreeNode* root) {
    if (root == nullptr) { return; }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void collectInorder(TreeNode* root, vector<int> &out) {
    if (root == nullptr) { return; }

    collectInorder(root->left, out);
    out.push_back(root->data);
    collectInorder(root->right, out);
}

int countNodes(TreeNode* root) {
    if (root == nullptr) { return 0; }

    return 1 + countNodes(root->left) + countNodes(root->right);
}

bool isBST(TreeNode* root, TreeNode* minNode, TreeNode* maxNode) {
    if (root == nullptr) { return true; }

    if (minNode && root->data <= minNode->data) { return false; }
    if (maxNode && root->data >= maxNode->data) { return false; }
    return isBST(root->left, minNode, root) && isBST(root->right, root, maxNode);
}

int height(TreeNode* root) {
    if (root == nullptr) { return 0; }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (leftHeight > rightHeight) { return 1 + leftHeight;}
    else { return 1 + rightHeight; }
}

TreeNode* findMin(TreeNode* root) {
    if (root->left == nullptr) { return root; }
    return findMin(root->left);
}

TreeNode* deleteNode(TreeNode* root, int value) {
    if (root == nullptr) { return nullptr; }

    if (value < root->data) { root->left = deleteNode(root->left, value); }
    else if (value > root->data) { root->right = deleteNode(root->right, value); }
    else {
        // no children
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        // one child
        else if (root->right == nullptr) {
            TreeNode *temp = root->left;
            delete root;
            return temp;
        } else if (root->left == nullptr) {
            TreeNode *temp = root->right;
            delete root;
            return temp;
        }
        // both children
        else {
            TreeNode *successor = findMin(root->right);
            root->data = successor->data;
            root->right = deleteNode(root->right, successor->data);
        }
    }

    return root;
}

void assertSorted(TreeNode* root) {
    vector<int> vals;
    collectInorder(root, vals);
    for (size_t i = 1; i < vals.size(); i++) {
        assert(vals[i] > vals[i-1]);
    }
}
void assertFound(TreeNode* root, int value) {
    TreeNode* result = search(root, value);
    assert(result != nullptr);
    assert(result->data == value);
}
void assertNotFound(TreeNode* root, int value) {
    assert(search(root, value) == nullptr);
}
void assertCount(TreeNode* root, int expected) {
    int actual = countNodes(root);
    assert(actual == expected);
}
void assertInorderEquals(TreeNode* root, vector<int> expected) {
    vector<int> actual;
    collectInorder(root, actual);
    assert(actual == expected);
}

void testEmptyTree() {
    cout << "[testEmptyTree]\n";
    TreeNode* root = nullptr;
    assert(search(root, 0)   == nullptr);
    assert(search(root, -1)  == nullptr);
    assert(search(root, 999) == nullptr);
    assert(countNodes(root)  == 0);
    assert(isBST(root, nullptr, nullptr));
    root = deleteNode(root, 42);
    assert(root == nullptr);
    cout << "  PASSED\n";
}

void testSingleNode() {
    cout << "[testSingleNode]\n";
    TreeNode* root = nullptr;
    root = insert(root, 10);
    assertCount(root, 1);
    assertFound(root, 10);
    assertNotFound(root, 0);
    assertNotFound(root, 11);
    assert(isBST(root, nullptr, nullptr));
    assertInorderEquals(root, {10});
    root = deleteNode(root, 10);
    assert(root == nullptr);
    assertCount(root, 0);
    assertNotFound(root, 10);
    cout << "  PASSED\n";
}

void testDuplicateInsert() {
    cout << "[testDuplicateInsert]\n";
    TreeNode* root = nullptr;
    root = insert(root, 5);
    root = insert(root, 5);
    root = insert(root, 5);
    assertCount(root, 1);
    assertFound(root, 5);
    assert(isBST(root, nullptr, nullptr));
    assertInorderEquals(root, {5});
    root = deleteNode(root, 5);
    assert(root == nullptr);
    cout << "  PASSED\n";
}

void testInsertAscending() {
    cout << "[testInsertAscending]\n";
    TreeNode* root = nullptr;
    for (int i = 1; i <= 7; i++) root = insert(root, i);
    assertCount(root, 7);
    assert(isBST(root, nullptr, nullptr));
    assertSorted(root);
    assertInorderEquals(root, {1, 2, 3, 4, 5, 6, 7});
    assert(height(root) == 7);
    for (int i = 1; i <= 7; i++) assertFound(root, i);
    assertNotFound(root, 0);
    assertNotFound(root, 8);
    for (int i = 1; i <= 7; i++) root = deleteNode(root, i);
    assert(root == nullptr);
    cout << "  PASSED\n";
}

void testInsertDescending() {
    cout << "[testInsertDescending]\n";
    TreeNode* root = nullptr;
    for (int i = 7; i >= 1; i--) root = insert(root, i);
    assertCount(root, 7);
    assert(isBST(root, nullptr, nullptr));
    assertSorted(root);
    assertInorderEquals(root, {1, 2, 3, 4, 5, 6, 7});
    assert(height(root) == 7);
    for (int i = 1; i <= 7; i++) assertFound(root, i);
    for (int i = 7; i >= 1; i--) root = deleteNode(root, i);
    assert(root == nullptr);
    cout << "  PASSED\n";
}

void testDeleteLeaf() {
    cout << "[testDeleteLeaf]\n";
    TreeNode* root = nullptr;
    for (int v : {50, 30, 70, 20, 40}) root = insert(root, v);
    root = deleteNode(root, 20);
    assertNotFound(root, 20);
    assertCount(root, 4);
    assert(isBST(root, nullptr, nullptr));
    assertInorderEquals(root, {30, 40, 50, 70});
    root = deleteNode(root, 40);
    assertNotFound(root, 40);
    assertCount(root, 3);
    assertInorderEquals(root, {30, 50, 70});
    root = deleteNode(root, 70);
    assertNotFound(root, 70);
    assertCount(root, 2);
    assertInorderEquals(root, {30, 50});
    for (int v : {30, 50}) root = deleteNode(root, v);
    assert(root == nullptr);
    cout << "  PASSED\n";
}

void testDeleteOneChild() {
    cout << "[testDeleteOneChild]\n";
    TreeNode* root = nullptr;
    for (int v : {50, 30, 10}) root = insert(root, v);
    root = deleteNode(root, 30);
    assertNotFound(root, 30);
    assertFound(root, 10);
    assertFound(root, 50);
    assertCount(root, 2);
    assert(isBST(root, nullptr, nullptr));
    assertInorderEquals(root, {10, 50});
    root = nullptr;
    for (int v : {50, 70, 90}) root = insert(root, v);
    root = deleteNode(root, 70);
    assertNotFound(root, 70);
    assertFound(root, 90);
    assertCount(root, 2);
    assert(isBST(root, nullptr, nullptr));
    assertInorderEquals(root, {50, 90});
    for (int v : {50, 90}) root = deleteNode(root, v);
    assert(root == nullptr);
    cout << "  PASSED\n";
}

void testDeleteTwoChildren() {
    cout << "[testDeleteTwoChildren]\n";
    TreeNode* root = nullptr;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) root = insert(root, v);
    root = deleteNode(root, 30);
    assertNotFound(root, 30);
    assertFound(root, 20);
    assertFound(root, 40);
    assertCount(root, 6);
    assert(isBST(root, nullptr, nullptr));
    assertInorderEquals(root, {20, 40, 50, 60, 70, 80});
    root = deleteNode(root, 50);
    assertNotFound(root, 50);
    assertCount(root, 5);
    assert(isBST(root, nullptr, nullptr));
    assertSorted(root);
    for (int v : {20, 40, 60, 70, 80}) root = deleteNode(root, v);
    assert(root == nullptr);
    cout << "  PASSED\n";
}

void testDeleteNonExistent() {
    cout << "[testDeleteNonExistent]\n";
    TreeNode* root = nullptr;
    for (int v : {50, 30, 70}) root = insert(root, v);
    root = deleteNode(root, 99);
    root = deleteNode(root, -1);
    root = deleteNode(root, 0);
    assertCount(root, 3);
    assert(isBST(root, nullptr, nullptr));
    assertInorderEquals(root, {30, 50, 70});
    for (int v : {30, 50, 70}) root = deleteNode(root, v);
    assert(root == nullptr);
    cout << "  PASSED\n";
}

void testDeleteRootRepeatedly() {
    cout << "[testDeleteRootRepeatedly]\n";
    TreeNode* root = nullptr;
    for (int v : {40, 20, 60, 10, 30, 50, 70}) root = insert(root, v);
    for (int i = 7; i >= 1; i--) {
        assert(isBST(root, nullptr, nullptr));
        assertSorted(root);
        assertCount(root, i);
        int rootVal = root->data;
        root = deleteNode(root, rootVal);
        assertNotFound(root, rootVal);
    }
    assert(root == nullptr);
    cout << "  PASSED\n";
}

void testSearchBoundaries() {
    cout << "[testSearchBoundaries]\n";
    TreeNode* root = nullptr;
    for (int v : {50, 25, 75, 10, 40, 60, 90, 1, 100}) root = insert(root, v);
    assertFound(root, 1);
    assertFound(root, 100);
    assertNotFound(root, 0);
    assertNotFound(root, 101);
    assertNotFound(root, 15);
    assertNotFound(root, 55);
    assertNotFound(root, 80);
    assert(isBST(root, nullptr, nullptr));
    for (int v : {50, 25, 75, 10, 40, 60, 90, 1, 100}) root = deleteNode(root, v);
    assert(root == nullptr);
    cout << "  PASSED\n";
}

void testNegativeValues() {
    cout << "[testNegativeValues]\n";
    TreeNode* root = nullptr;
    for (int v : {0, -10, 10, -20, -5, 5, 20}) root = insert(root, v);
    assertCount(root, 7);
    assert(isBST(root, nullptr, nullptr));
    assertInorderEquals(root, {-20, -10, -5, 0, 5, 10, 20});
    assertFound(root, -20);
    assertFound(root, -5);
    assertFound(root, 0);
    assertNotFound(root, -1);
    assertNotFound(root, 15);
    root = deleteNode(root, -10);
    assertNotFound(root, -10);
    assertCount(root, 6);
    assert(isBST(root, nullptr, nullptr));
    assertInorderEquals(root, {-20, -5, 0, 5, 10, 20});
    for (int v : {-20, -5, 0, 5, 10, 20}) root = deleteNode(root, v);
    assert(root == nullptr);
    cout << "  PASSED\n";
}

void testLargerTree() {
    cout << "[testLargerTree]\n";
    TreeNode* root = nullptr;
    vector<int> vals;
    for (int i = 1; i <= 50; i++) vals.push_back(i);
    vector<int> insertOrder;
    for (int i = 0; i < 50; i += 7) insertOrder.push_back(vals[i]);
    for (int i = 3; i < 50; i += 7) insertOrder.push_back(vals[i]);
    for (int i = 1; i < 50; i += 7) insertOrder.push_back(vals[i]);
    for (int i = 5; i < 50; i += 7) insertOrder.push_back(vals[i]);
    for (int i = 2; i < 50; i += 7) insertOrder.push_back(vals[i]);
    for (int i = 4; i < 50; i += 7) insertOrder.push_back(vals[i]);
    for (int i = 6; i < 50; i += 7) insertOrder.push_back(vals[i]);
    for (int v : insertOrder) root = insert(root, v);
    assertCount(root, 50);
    assert(isBST(root, nullptr, nullptr));
    assertSorted(root);
    for (int i = 1; i <= 50; i++) assertFound(root, i);
    assertNotFound(root, 0);
    assertNotFound(root, 51);
    for (int i = 2; i <= 50; i += 2) {
        root = deleteNode(root, i);
        assertNotFound(root, i);
        assert(isBST(root, nullptr, nullptr));
    }
    assertCount(root, 25);
    for (int i = 1; i <= 50; i += 2) assertFound(root, i);
    for (int i = 2; i <= 50; i += 2) assertNotFound(root, i);
    for (int i = 1; i <= 50; i += 2) root = deleteNode(root, i);
    assert(root == nullptr);

    cout << "  PASSED\n";
}

int main() {
    testEmptyTree();
    testSingleNode();
    testDuplicateInsert();
    testInsertAscending();
    testInsertDescending();
    testDeleteLeaf();
    testDeleteOneChild();
    testDeleteTwoChildren();
    testDeleteNonExistent();
    testDeleteRootRepeatedly();
    testSearchBoundaries();
    testNegativeValues();
    testLargerTree();

    cout << "\n✓ All tests passed.\n";
    return 0;
}
