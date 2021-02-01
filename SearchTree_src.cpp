#include <iostream>
#include <vector>
#include <iomanip>

template <typename Elem>
class BinaryTree {
protected:
    struct Node {
        Elem elem;
        Node* par;
        Node* left;
        Node* right;

        Node() :elem(), par(NULL), left(NULL), right(NULL)
        {}
    };

public:
    class Position {
    private:
        Node* posN;
        Position(Node* posN = NULL) : posN(posN)
        {}
    public:
        Elem& operator*() {
            return posN->elem;
        }
        Position left() const {
            return (Position(posN->left));
        }
        Position right() const {
            return (Position(posN->right));
        }
        Position parent() const {
            return (Position(posN->par));
        }
        bool isRoot() const {
            return posN->par == NULL;
        }
        bool isExternal() const {
            return (posN->left == NULL && posN->right == NULL);
        }

        bool isInternal() const {
            return (posN->left != NULL || posN->right != NULL);
        }

        Elem& element() const
        {
            return posN->elem;
        }

        friend class BinaryTree;
        template <typename E>
        friend class SearchTree;
    };

    typedef std::vector<Position> PositionList;

public:
    BinaryTree() {
        _root = NULL;
        sz = 0;
    }

    unsigned int size() const { return sz; }
    bool empty() const { return sz == 0; }
    Position root() const { return Position(_root); }

    PositionList positions() const {
        PositionList pl;
        preorder(_root, pl);
        return PositionList(pl);
    }

    void addRoot() {
        _root = new Node;
        sz = 1;
    }

    void expendExternal(const Position& p) {
        Node* v = p.posN;

        v->left = new Node;
        v->left->par = v;

        v->right = new Node;
        v->right->par = v;

        sz += 2;
    }

    Position removeAboveExternal(const Position& p) {
        Node* w = p.posN;
        Node* wPar = w->par;
        Node* sib = (w == wPar->left ? wPar->right : wPar->left);

        if (wPar == _root) {
            _root = sib;
            sib->par = NULL;
        }
        else {
            Node* grap = wPar->par;

            if (wPar == grap->left)
                grap->left = sib;
            else
                grap->right = sib;

            sib->par = grap;
        }

        delete w;
        delete wPar;
        sz -= 2;

        return Position(sib);
    }

    void print(PositionList pl) {
        for (unsigned item = 0; item < pl.size(); item++) {
            BinaryTree::Position p = BinaryTree::Position(pl.at(item));

            if (p.isRoot())
                std::cout << "Root: " << *p << std::endl;
            else {
                if (p.isExternal())
                    std::cout << std::setw(11) << *p << std::endl;
                else
                    std::cout << std::setw(9) << *p << std::endl;
            }
        }
    }

    void preorderPrint(const BinaryTree* T, Position& p) {
        std::cout << *p << " ";

        if (!p.isExternal()) {
            Position leftChild = p.left();
            preorderPrint(T, leftChild);

            Position rightChild = p.right();
            preorderPrint(T, rightChild);
        }
    }

    int depth(const BinaryTree* T, const Position& p) {
        if (p.isRoot())
            return 0;
        else
            return 1 + depth(T, p.parent());
    }

protected:
    void preorder(Node* n, PositionList& pl)const {
        pl.push_back(Position(n));

        if (n->left != NULL)
            preorder(n->left, pl);

        if (n->right != NULL)
            preorder(n->right, pl);
    }
private:
    Node* _root;
    unsigned sz;
};


class Pair {
public:
    typedef int Key;
    typedef int Value;
    
    Pair(const Key& k = Key(), const Value& v = Value()) :
        _key(k), _value(v) {}

    const Key& getKey() const { return _key; }
    void setKey(const Key& k) { _key = k; }
    const Value& getValue() const { return _value; }
    void setValue(const Value& v) { _value = v; }
private:
    Key _key;
    Value _value;
};


template <typename E>
class SearchTree {
public:
    typedef typename E::Key K;
    typedef typename E::Value V;
    class Iterator;

    SearchTree():T(),sz(0) { //super root
        T.addRoot();
        T.expendExternal(T.root());
    }
    int size() const{ return sz; }
    bool empty() const { return size() == 0; }
    void erase(const Iterator& p) { eraser(p.v); }

    void erase(const K& k) {
        TPos v = finder(k, root());
        if (v.isExternal()) {
            std::cout << "Erase of nonexistent" << std::endl;
            return;
        }
        eraser(v);
    }

    Iterator find(const K& k) {
        TPos v = finder(k, root());
        if (v.isInternal()) //k is found
            return Iterator(v);
        else //no k
            return end(); //the place for k
    }

    Iterator insert(const K& k, const V& x) {
        TPos v = inserter(k, x);
        return Iterator(v);
    }

    Iterator begin() {//first in inorder traversal
        TPos v = root();
        while (v.isInternal())
            v = v.left();
        return Iterator(v.parent());
    }

    Iterator end() { //super root
        return Iterator(T.root());
    }

protected:
    typedef BinaryTree<E> _BinaryTree;
    typedef typename _BinaryTree::Position TPos;
    TPos root() const { return T.root().left(); } //virtual root

    TPos finder(const K& k, const TPos& v) {
        if (v.isExternal())
            return v;

        if (k < v.element().getKey())
            return finder(k, v.left());
        else if (v.element().getKey() < k)
            return finder(k, v.right());
        else
            return v;
    }

    TPos inserter(const K& k, const V& x) {
        TPos v = finder(k, root());
        while (v.isInternal())
            v = finder(k, v.right());
        T.expendExternal(v);
        v.element().setKey(k);
        v.element().setValue(x);
        sz++; 
        return v;
    }

    TPos eraser(TPos& v) {
        TPos w;
        if (v.left().isExternal())
            w = v.left();
        else if (v.right().isExternal())
            w = v.right();
        else {
            w = v.right();

            do {
                w = w.left();
            } while (w.isInternal());

            TPos u = w.parent();
            v.element().setKey(u.element().getKey());
            v.element().setValue(u.element().getValue());
        }
        sz--;
        return T.removeAboveExternal(w);
    }

private:
    _BinaryTree T;
    int sz;

public:
    class Iterator {
    private:
        TPos v;
    public:
        Iterator(const TPos& vv) :v(vv) {}
        const E& operator*() const { return v.element(); }
        E& operator*() { return v.element(); }
        bool operator ==(const Iterator& p)const { return v = p.v; }

        Iterator& operator++() {
            TPos w = v.right();

            if (w.isInternal()) {
                do {
                    v = w; w = w.left();
                } while (w.isInternal());
            }
            else {
                w = v.parent();
                while (v == w.right()) {
                    v = w; w = w.parent;
                }
                v = w;
            }
            return *this;
        }
        friend class SearchTree;
    };
};
