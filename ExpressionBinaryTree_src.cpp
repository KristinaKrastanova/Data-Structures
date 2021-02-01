#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <sstream>

template<typename Elem>
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

        friend class BinaryTree;
    };

    typedef std::vector<Position> PositionList;

public:
    BinaryTree() {
        _root = NULL;
        sz = 0;
    }

    unsigned int size() const {
        return sz;
    }

    bool empty() const {
        return sz == 0;
    }

    Position root() const {
        return Position(_root);
    }

    PositionList positions() const {
        PositionList pl;
        postorder(_root, pl);
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
        Node* v = w->par;
        Node* sib = (w == v->left ? v->right : v->left);

        if (v == _root) {
            _root = sib;
            sib->par = NULL;
        }
        else {
            Node* grap = v->par;

            if (v == grap->left)
                grap->left = sib;
            else
                grap->right = sib;

            sib->par = grap;
        }

        delete w;
        delete v;
        sz -= 2;

        return Position(sib);
    }

    void preorder(const BinaryTree* T, Position& p, std::string& res) {

        if (!p.isExternal()) {
            Position leftChild = p.left();
            preorder(T, leftChild, res);

            Position rightChild = p.right();
            preorder(T, rightChild, res);
        }
        res += (*p) + " ";
    }

private:
    Node* _root;
    unsigned sz;
};


bool isdigit(std::string st) {
    return isdigit(st[0]);
}

void constructTree(std::vector<std::string> expr, int& pos, BinaryTree<std::string>::Position p, BinaryTree<std::string>* t) {
    if (expr[pos] == "(")
    {
        pos++;
        t->expendExternal(p);
        constructTree(expr, pos, p.left(),t);
        constructTree(expr, pos, p,t);
        return;
    }

    if (isdigit(expr[pos]))
    {
        *p = expr[pos];
        pos++;
        return;
    }

    if (expr[pos] == "+"  || expr[pos] == "-" || expr[pos] == "*" || expr[pos] == "/")
    {
        *p = expr[pos];
        pos++;
        constructTree(expr, pos, p.right(),t);
    }

    if (expr[pos] == ")")
    {
        pos++;
        return;
    }
}

bool isOperator(char C) {
    if (C == '+' || C == '-' || C == '*' || C == '/')
        return true;

    return false;
}


int performOperation(char operation, int n1, int n2) {
    if (operation == '+') return n1 + n2;
    else if (operation == '-') return n1 - n2;
    else if (operation == '*') return n1 * n2;
    else if (operation == '/') return n1 / n2;
    return -1;
}

void evaluate(std::string exp) {
    std::stack<int> S;

    for (int i = 0; i < exp.length(); i++) {

        if (isOperator(exp[i])) {
            int operand2 = S.top(); S.pop();
            int operand1 = S.top(); S.pop();

            int result = performOperation(exp[i], operand1, operand2);
            S.push(result);
        }
        else if (isdigit(exp[i])) {
            int operand = 0;
            while (i < exp.length() && isdigit(exp[i]))
            {
                operand = (operand * 10) + (exp[i] - '0');
                i++;
            }
            i--;

            S.push(operand);
        }
    }
    std::cout << S.top();
}


int main()
{
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> in;
    std::istringstream st(input);
    std::string current;
    while (st >> current)
        in.push_back(current);
    BinaryTree<std::string>* t = new BinaryTree<std::string>;
    t->addRoot();
    BinaryTree<std::string>::Position p = t->root();
    int i = 0;
    constructTree(in, i, p, t);
    std::string exp;
     p = t->root();
     t->preorder(t, p, exp);
    evaluate(exp);
    return 0;
}
