template<typename Object>
class NodeList {
private:
    struct Node
    {
        Object elem;
        Node* next;
        Node* prev;
    };

public:
    class Iterator
    {
    public:
        Node* itN;
        Iterator(Node* itN) :itN(itN)
        {}
    public:
        Object& operator*() {
            return itN->elem;
        }

        bool operator==(const Iterator& iter) const {
            return itN == iter.itN;
        }

        bool operator!=(const Iterator& iter) const {
            return itN != iter.itN;
        }

        Iterator& operator++() {
            itN = itN->next;
            return *this;
        }

        Iterator& operator--() {
            itN = itN->prev;
            return *this;
        }
    };

private:
    int sz;
    Node* header;
    Node* trailer;
public:
    NodeList();
    NodeList(const NodeList& other);
    NodeList& operator=(const NodeList& other);

    int size() const { return sz; }
    bool empty() const { return (sz == 0); }
    Iterator begin() const { return Iterator(header->next); }
    Iterator end() const { return Iterator(trailer); }

    void insertFront(const Object& obj) { insert(begin(), obj); }
    void insertBack(const Object& obj) { insert(end(), obj); }
    void insert(const Iterator& iter, const Object& obj);

    void eraseFront() { erase(begin()); }
    void eraseBack() { erase(--end()); }
    void erase(const Iterator& iter);

    void print();
    ~NodeList();
};

template<typename Object>
NodeList<Object>::NodeList() {
    sz = 0;
    header = new Node;
    trailer = new Node;

    header->next = trailer;
    trailer->prev = header;
}

template<typename Object>
NodeList<Object>::NodeList(const NodeList<Object>& other) {
    sz = other.size();
    header = new Node;
    trailer = new Node;

    header->next = trailer;
    trailer->prev = header;

    Iterator itOther = Iterator(other.begin());
    for (int i = 0; i < other.size(); i++) {
        Node* current = itOther.itN;
        insertBack(current->elem);
        ++itOther;
    }
}

template<typename Object>
NodeList<Object>::~NodeList() {
    Iterator itOther = Iterator(begin());
    for (int i = 0; i < size(); i++) {
        Node* current = itOther.itN;
        delete& current;
        ++itOther;
    }

    sz = 0;
    delete& header;
    delete& trailer;
}

template<typename Object>
NodeList<Object>& NodeList<Object>::operator=(const NodeList<Object>& other)
{
    if (this != &other)
    {
        sz = other.size();

        Iterator itOther = Iterator(other.begin());
        --itOther;
        header = itOther.itN;

        itOther = Iterator(other.end());
        trailer = itOther.itN;
    }

    return *this;
}

template<typename Object>
void NodeList<Object>::insert(const NodeList<Object>::Iterator& iter, const Object& obj) {
    Node* nd2 = iter.itN;
    Node* nd1 = nd2->prev;
    Node* newEl = new Node;

    newEl->elem = obj;
    newEl->next = nd2;
    nd2->prev = newEl;

    newEl->prev = nd1;
    nd1->next = newEl;
    sz++;
}

template<typename Object>
void NodeList<Object>::erase(const NodeList<Object>::Iterator& iter) {
    Node* elToDel = iter.itN;
    Node* nd2 = elToDel->next;
    Node* nd1 = elToDel->prev;

    nd1->next = nd2;
    nd2->prev = nd1;
    delete elToDel;
    sz--;
}

template<typename Object>
void NodeList<Object>::print() {
    std::cout << "Elements in the container: " << std::endl;

    Iterator it = begin();
    for (int i = 0; i < size(); i++) {
        Node* current = it.itN;
        cout << current->elem << " ";
        ++it;
    }

    std::cout << std::endl;
}
