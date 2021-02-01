#include <iostream>

template<typename Object>
class LinkedList {
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
    LinkedList();

    int size() const { return sz; }
    bool empty() const { return (sz == 0); }
    Iterator begin() const { return Iterator(header->next); }
    Iterator end() const { return Iterator(trailer); }

    void insertFront(const Object& obj) { insert(begin(), obj); }
    void insertBack(const Object& obj) { insert(end(), obj); }
    void insert(const Iterator& iter, const Object& obj);

    void eraseFront() { erase(begin()); }
    void eraseBack() { erase(--end()); }
    void erase(Iterator& iter);

    Object at(Iterator iter);
    void set(Iterator iter, const Object& obj);

    void print();
    ~LinkedList();
};

template<typename Object>
LinkedList<Object>::LinkedList() {
    sz = 0;
    header = new Node;
    trailer = new Node;

    header->next = trailer;
    trailer->prev = header;
}

template<typename Object>
void LinkedList<Object>::insert(const LinkedList<Object>::Iterator& iter, const Object& obj) {
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
void LinkedList<Object>::erase(LinkedList<Object>::Iterator& iter) {
    Node* elToDel = iter.itN;
    Node* nd2 = elToDel->next;
    Node* nd1 = elToDel->prev;

    nd1->next = nd2;
    nd2->prev = nd1;
    sz--;
    ++iter;
}

template <typename Object>
Object LinkedList<Object>::at(Iterator iter){
    return *iter;
}

template <typename Object>
void LinkedList<Object>::set(Iterator iter, const Object& obj){
    iter.itN->elem = obj;
}

template<typename Object>
void LinkedList<Object>::print() {
    std::cout << "Elements in the container: " << std::endl;
    Iterator it = begin();

    for (int i = 0; i < size(); i++) {
        std::cout << it.itN->elem << " ";
        ++it;
    }
    std::cout << std::endl;
}

template<typename Object>
LinkedList<Object>::~LinkedList() {
    Iterator it = begin();

    for (int i = 0; i < size(); i++) {
        Node* current = it.itN;
        delete& current;
        ++it;
    }
    sz = 0;
    delete& header;
    delete& trailer;
}
