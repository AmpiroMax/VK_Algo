#include <iostream>
#include <string>

using namespace std;

struct Node
{
    int value;
    int height;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(int _value)
    {
        value = _value;
        height = 1;
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

    int get_balance(Node *vert)
    {
        return height(vert->right) - height(vert->left);
    }

    Node *fix(Node *curr)
    {
        int hl = height(curr->left);
        int hr = height(curr->right);
        curr->height = max(hl, hr) + 1;
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

    bool _exists(Node *curr, int value)
    {
        if (!curr)
            return false;

        if (curr->value > value)
            return _exists(curr->left, value);

        if (curr->value < value)
            return _exists(curr->right, value);

        return true;
    }

    void _printTree(Node *curr)
    {
        if (!curr)
            return;
        _printTree(curr->left);
        cout << "( " << curr->value << " | " << curr->height << " )"
             << " ";
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

    bool exists(int value)
    {
        return _exists(root, value);
    }

    Node *next(int value)
    {
        Node *curr = root;
        Node *vnext = nullptr;

        while (curr)
        {
            if (curr->value > value)
            {
                vnext = curr;
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }
        }

        return vnext;
    }

    Node *prev(int value)
    {
        Node *curr = root;
        Node *vprev = nullptr;

        while (curr)
        {
            if (curr->value < value)
            {
                vprev = curr;
                curr = curr->right;
            }
            else
            {
                curr = curr->left;
            }
        }

        return vprev;
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
    string command;
    int value;

    AVL tree;

    for (; cin >> command >> value;)
    {
        if (command == "insert")
            tree.insert(value);

        if (command == "delete")
            tree.delete_elem(value);

        if (command == "exists")
            if (tree.exists(value))
                cout << "true" << endl;
            else
                cout << "false" << endl;

        if (command == "next")
        {
            Node *next = tree.next(value);
            if (!next)
                cout << "none" << endl;
            else
                cout << next->value << endl;
        }

        if (command == "prev")
        {
            Node *prev = tree.prev(value);
            if (!prev)
                cout << "none" << endl;
            else
                cout << prev->value << endl;
        }

        if (command == "print")
        {
            tree.printTree();
        }
    }
    return 0;
}