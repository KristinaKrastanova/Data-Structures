#include <vector>

template <typename Object>;
class Tree {
private:
    Node* _root;
    int length;

protected:
    struct Node {
        Object element;
        Node* parent;
        std::vector<Node*>childs;

        Node() {
            element = 0;
            parent = NULL;
        }
    };

public:
    class Position {
    private:
        Node* currentNode;
        Position(Node* startNode) :currentNode(startNode) {}
    public:
        Object& operator*() {
            return currentNode->element;
        }

        Position parent() const {
            return Position(currentNode->parent);
        }

        std::vector<Node*> children()const {
            return currentNode->childs;
        }

        bool isRoot() const {
            return (currentNode->parent == NULL);
        }

        bool isExternal() const {
            return (currentNode->childs.empty());
        }

        friend class Tree;
    };

    typedef std::vector<Position> PositionList;

public:
    Tree() {
        addRoot();
    }

    int size() const {
        return length;
    }

    bool empty() const {
        return size() == 0;
    }

    Position root()const {
        return Position(_root);
    }


    void addRoot() {
        _root = new Node();
        length = 1;
    }

    void insert(const Position& p, const T& obj) { //inserts obj before p
        Node* par = obj.currentNode;
        Node* newNode = new Node();
        newNode->element = obj;
        newNode->parent = par;

        par->childs.push_back(newNode);
        length++;
    }

    std::vector<Position> position() const {
        std::vector<Position> pArr;
        preorder(_root, pArr);
        return pArr;
    }

    void preorderPrint(Tree::Position& p, const Tree* Tr) {
        std::cout << *p;
        std::vector<Node*> ch = p.children();
        for (int i = 0; i < ch.size(); i++) {
            Position currentPos = Position(ch.at(i));
            std::cout << " ";
            preorderPrint(currentPos, Tr);
        }
    }

    void print(std::vector<Position>& pArr) {
        int i = 0;
        while (i < pArr.size()) {
            Position p = pArr.at(i);
            if (p.isRoot())
                std::cout << "Root: " << *p;
            else {
                Position par = p.parent();
                std::cout << "Parent: " << *par;
                std::cout << "     Child: " << *p;
            }
            std::cout << std::endl;
            i++;
        }
    }

protected:
    void preorder(Node* startNode, std::vector<Position>& pArr) const {
        pArr.push_back(Position(startNode));
        int i = 0;
        while (i < startNode->childs.size()) {
            Node* currentNode = startNode->childs.at(i);
            if (currentNode != NULL)
                preorder(currentNode, pArr);
            i++;
        }
    }

};
