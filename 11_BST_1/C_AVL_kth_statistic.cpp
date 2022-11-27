#include <iostream>
#include <string>

using namespace std;

struct Node
{
    int value;
    int height;
    int size;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(int _value)
    {
        value = _value;
        height = 1;
        size = 1;
        left = nullptr;
        right = nullptr;
    }
};

class AVL
{
private:
    Node *root = nullptr;

    Node *findMax(Node *curr)
    {
        while (curr->right != nullptr)
            curr = curr->right;
        return curr;
    }

    int height(Node *vert)
    {
        if (!vert)
            return 0;
        return vert->height;
    }

    int size(Node *vert)
    {
        if (!vert)
            return 0;
        return vert->size;
    }

    int get_balance(Node *vert)
    {
        return height(vert->right) - height(vert->left);
    }

    Node *fix(Node *curr)
    {
        int hl = height(curr->left);
        int hr = height(curr->right);
        curr->height = max(hl, hr) + 1;

        int sl = size(curr->left);
        int sr = size(curr->right);
        curr->size = sl + sr + 1;

        return curr;
    }

    Node *balance(Node *curr)
    {
        if (!curr)
            return nullptr;
        curr = fix(curr);
        if (get_balance(curr) == 2)
            return rotate_left(curr);

        if (get_balance(curr) == -2)
            return rotate_right(curr);
        return curr;
    }

    // -------- Rotations --------

    Node *small_right(Node *curr)
    {
        Node *left = curr->left;
        curr->left = left->right;
        left->right = curr;
        curr = fix(curr);
        left = fix(left);
        return left;
    }

    Node *small_left(Node *curr)
    {
        Node *right = curr->right;
        curr->right = right->left;
        right->left = curr;
        curr = fix(curr);
        right = fix(right);
        return right;
    }

    Node *big_right(Node *curr)
    {
        Node *left = curr->left;
        curr->left = small_left(left);
        return small_right(curr);
    }

    Node *big_left(Node *curr)
    {
        Node *right = curr->right;
        curr->right = small_right(right);
        return small_left(curr);
    }

    Node *rotate_right(Node *curr)
    {
        if (get_balance(curr->left) == 2)
            return big_right(curr);
        return small_right(curr);
    }

    Node *rotate_left(Node *curr)
    {
        if (get_balance(curr->right) == -2)
            return big_left(curr);
        return small_left(curr);
    }

    // ---------------------------

    Node *_insert(Node *curr, int value)
    {
        if (!curr)
            return new Node(value);

        if (curr->value > value)
            curr->left = _insert(curr->left, value);
        else if (curr->value < value)
            curr->right = _insert(curr->right, value);

        return balance(curr);
    }

    Node *_delete(Node *curr, int value)
    {
        if (!curr)
            return nullptr;

        if (curr->value > value)
        {
            curr->left = _delete(curr->left, value);
        }
        else if (curr->value < value)
        {
            curr->right = _delete(curr->right, value);
        }
        else if (!curr->left)
        {
            Node *old_curr = curr;
            curr = curr->right;
            delete old_curr;
            old_curr = nullptr;
        }
        else if (!curr->right)
        {
            Node *old_curr = curr;
            curr = curr->left;
            delete old_curr;
            old_curr = nullptr;
        }
        else
        {
            curr->value = findMax(curr->left)->value;
            curr->left = _delete(curr->left, curr->value);
        }
        return balance(curr);
    }

    Node *_find_kth_statistics(Node *curr, int k)
    {
        int curr_ind = 0;
        if (curr->right)
            curr_ind = size(curr->right);

        if (curr_ind > k)
            return _find_kth_statistics(curr->right, k);

        if (curr_ind < k)
            return _find_kth_statistics(curr->left, k - curr_ind - 1);

        return curr;
    }

    void _printTree(Node *curr)
    {
        if (!curr)
            return;
        _printTree(curr->left);
        cout << "( "
             << curr->value << " | "
             << curr->height << " | "
             << curr->size
             << " ) ";

        _printTree(curr->right);
    }

public:
    void insert(int value)
    {
        root = _insert(root, value);
    }

    void delete_elem(int value)
    {
        root = _delete(root, value);
    }

    Node *find_kth_statistics(int k)
    {
        return _find_kth_statistics(root, k);
    }

    void printTree()
    {
        if (!root)
            cout << "NO ROOT" << endl;
        _printTree(root);
        cout << endl;
    }
};

int main()
{
    int command;
    int k;
    int n;
    AVL tree;

    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> command >> k;
        if (command == 1)
            tree.insert(k);

        if (command == -1)
            tree.delete_elem(k);

        if (command == 0)
            cout << tree.find_kth_statistics(k - 1)->value << endl;

        if (command == 2)
        {
            tree.printTree();
        }
    }
    return 0;
}