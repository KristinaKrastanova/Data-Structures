#include <iostream>
#include <vector>
#include <iomanip>

template <typename E>
class VectorCompleteTree {
private:
    std::vector<E> V; 
public:
    typedef typename std::vector<E>::iterator Position;
protected:
    Position pos(int i)
    {
        return V.begin() + i;
    }
    int idx(const Position& p) const 
    {
        return p - V.begin();
    }
public:
    VectorCompleteTree() : V(1) {} 
    int size() const { return V.size() - 1; }
    Position left(const Position& p) { return pos(2 * idx(p)); }
    Position right(const Position& p) { return pos(2 * idx(p) + 1); }
    Position parent(const Position& p) { return pos(idx(p) / 2); }
    bool hasLeft(const Position& p) const { return 2 * idx(p) <= size(); }
    bool hasRight(const Position& p) const { return 2 * idx(p) + 1 <= size(); }
    bool isRoot(const Position& p) const { return idx(p) == 1; }
    Position root() { return pos(1); }
    Position last() { return pos(size()); }
    void addLast(const E& e) { V.push_back(e); }
    void removeLast() { V.pop_back(); }
    void swap(const Position& p, const Position& q)
    {
        E e = *q; *q = *p; *p = e;
    }
};


template <class T>
class LexCompare {
public:
    int operator()(const T& p1, const T& p2) const
    {
        return p1 < p2;
    }
};

template <class E, template<class> class C>
class HeapPriorityQueue {
public:
    int size() const;
    bool empty() const;
    void insert(const E& e); 
    const E& min(); 
    void removeMin();
    void print(); 
private:
    typedef typename VectorCompleteTree<E>::Position Position;
    void show(Position p, int loc); //show values in heap
private:
    VectorCompleteTree<E> T; 
    C<E> isLess; 
};

template <class E, template<class> class C>
int HeapPriorityQueue<E, C>::size() const
{
    return T.size();
}

template <class E, template<class> class C>
bool HeapPriorityQueue<E, C>::empty() const
{
    return size() == 0;
}

template <class E, template<class> class C>
const E& HeapPriorityQueue<E, C>::min()
{
    return *(T.root());
}

template <class E, template<class> class C>
void HeapPriorityQueue<E, C>::insert(const E& e) {
    T.addLast(e);

    Position v = T.last();

    // Up-heap bubbling
    while (!T.isRoot(v)) {
        Position u = T.parent(v);
        if (!isLess(*v, *u))
            break; 

        T.swap(v, u); // Swap with parent

        v = u;
    }
}


template <class E, template<class> class C>
void HeapPriorityQueue<E, C>::removeMin() {
    if (size() == 1)
        T.removeLast();
    else
    {
        Position u = T.root();

        T.swap(u, T.last()); // Swap last with root
        T.removeLast(); // Remove last

        while (T.hasLeft(u))
        {
            // Down-heap bubbling
            Position v = T.left(u);
            if (T.hasRight(u) && isLess(*(T.right(u)), *v))
                v = T.right(u); // v is u’s smaller child

            // Is u out of order?
            if (isLess(*v, *u))
            {
                T.swap(u, v); 
                u = v;
            }
            else
                break;
        }
    }
}


template <class E, template<class> class C>
void HeapPriorityQueue<E, C>::print()
{
    int loc = 8; // To format the output

    Position p = T.root(); // Root position
    std::cout << "Root: " << *p << std::endl; // Show root

    Position leftChild = T.left(p); //Get root left child
    show(leftChild, loc); // Travers the left subtree
    std::cout << "\n";

    Position rightChild = T.right(p); //Get root right child
    show(rightChild, loc); // Travers the right subtree
}

// Show the values in the heap
template <class E, template<class> class C>
void HeapPriorityQueue<E, C>::show(Position p, int loc)
{
    loc += 2;
    std::cout << std::setw(loc) << *p << std::endl;

    //Check for left child
    if (T.hasLeft(p))
    {
        Position leftChild = T.left(p); //Get left child
        show(leftChild, loc); //Recursive traversal of left subtree
        std::cout << "\n";
    }

    //Check for right child
    if (T.hasRight(p))
    {
        Position rightChild = T.right(p); //Get right child
        show(rightChild, loc); //Recursive traversal of right subtree
    }
}
