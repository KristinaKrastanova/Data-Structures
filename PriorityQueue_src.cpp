#include <iostream>
#include <list>

template <class T>
class LexCompare {
public:
    int operator()(const T& a, const T& b) {
        return a < b;
    }
};

template<class E, template<class> class C>
class ListPriorityQueue {
public:
    int size() const;
    bool empty() const;
    void insert(const E& e);
    const E& min();
    void removeMin();
    void print();

private:
    std::list<E> L;
    C<E> isLess;
};

template<class E, template<class> class C>
int ListPriorityQueue<E, C>::size() const {
    return L.size();
}

template<class E, template<class> class C>
bool ListPriorityQueue<E, C>::empty() const {
    return L.empty();
}

template<class E, template<class> class C>
void ListPriorityQueue<E, C>::insert(const E& e) {
    typename std::list<E>::iterator p;

    p = L.begin();
    while (p != L.end() && !isLess(e, *p)) {
        ++p;
    }

    L.insert(p, e);
}

template<class E, template<class> class C>
const E& ListPriorityQueue<E, C>::min() {
    return L.front();
}

template<class E, template<class> class C>
void ListPriorityQueue<E, C>::removeMin() {
    L.pop_front();
}

template<class E, template<class> class C>
void ListPriorityQueue<E, C>::print() {
    typename std::list<E>::iterator p;

    for (p = L.begin(); p != L.end(); ++p)
        std::cout << '\t' << *p;
        std::cout << std::endl; 
}

template<class E, template<class> class C>
std::list<E> PriorityQueueSort(std::list<E>& L, ListPriorityQueue<E, C> p) {
    while (!L.empty()) {
        E e = L.front();
        L.pop_front();
        p.insert(e);
    }

    while (!p.empty()) {
        E e = p.min();
        p.removeMin();
        L.push_back(e);
    }

    return L;
}
