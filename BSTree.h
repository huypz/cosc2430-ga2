#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <fstream>

class BSTree {
    private:
        struct Node {
            Node(int val) : left(nullptr), right(nullptr), val(val) { }
            Node* left;
            Node* right;
            int val;
        };

    public:
        BSTree();
        ~BSTree();
        void addNode(const int& e);
        Node* find(const int& e) const;
        void deleteTree(Node* p);
        bool empty() const;
        int size() const;
        int track(Node* start, const int& end) const;
        std::ofstream& traverseAndPrint(Node* start, Node* end, std::ofstream& ofs) const;

    private:
        Node* root;
        int n;
        void addNode(Node* p, const int& e);
        Node* find(Node* p, const int& e) const;
        int track(Node* p, const int& end, int count) const;
};

BSTree::BSTree() : root(nullptr) {
    n = 0;
}

BSTree::~BSTree() {
    if (!empty())
        deleteTree(root);
}

void BSTree::addNode(const int& e) {
    if (empty())
        root = new Node(e);
    else 
        addNode(root, e);
    n += 1;
}

void BSTree::addNode(Node* p, const int& e) {
    if (e < p->val) {
        if (!p->left) 
            p->left = new Node(e);
        else
            addNode(p->left, e);
    }
    else if (e > p->val) {
        if (!p->right) 
            p->right = new Node(e);
        else
            addNode(p->right, e);
    }
}

void BSTree::deleteTree(Node* p) {
    if (p->left)
        deleteTree(p->left);
    if (p->right)
        deleteTree(p->right);
    delete p;
}

bool BSTree::empty() const { return n == 0; }

BSTree::Node* BSTree::find(const int& e) const {
    if (empty()) return nullptr;
    return find(root, e);
}

BSTree::Node* BSTree::find(Node* p, const int& e) const {
    if (p->val == e) {
        return p;
    }
    else if (e < p->val) {
        if (!p->left)
            return nullptr;
        else
            return find(p->left, e);
    }
    else if (e > p->val) {
        if (!p->right)
            return nullptr;
        else
            return find(p->right, e);
    }
    else {
        return nullptr;
    }
}

int BSTree::size() const { return n; }

int BSTree::track(Node* start, const int& end) const {
    return track(start, end, 1);
}

int BSTree::track(Node* p, const int& e, int count) const {
    if (p->val == e) {
        return count;
    }
    if (e < p->val) {
        return track(p->left, e, count + 1);
    }
    else if (e > p->val) {
        return track(p->right, e, count + 1);
    }
    else {
        return -1;
    }
}

std::ofstream& BSTree::traverseAndPrint(Node* start, Node* end, std::ofstream& ofs) const {
    if (start == end) {
        ofs << start->val;
        return ofs;
    }

    ofs << start->val << " -> ";
    if (end->val < start->val) {
        return traverseAndPrint(start->left, end, ofs);
    }
    else if (end->val > start->val) {
        return traverseAndPrint(start->right, end, ofs);
    }
    else {
        return ofs;
    }
}
#endif