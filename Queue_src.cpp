const int MAX_SIZE = 1000;

template <typename Object>
class Queue {
private:
    int firstEl, lastEl, sz;
    Object* array;

    void copy(const Queue& other) {
        array = new Object[MAX_SIZE];

        for (int i = 0; i < MAX_SIZE; i++)
            array[i] = other.array[i];

        sz = other.sz;
        firstEl = other.firstEl;
        lastEl = other.lastEl;
    }

public:
    Queue() {                    //Constructor
        array = new Object[MAX_SIZE];
        sz = 0;
        firstEl = 0;
        lastEl = 0;
    }

    ~Queue() {                   // Destructor
        delete[] array;
    }

    Queue(const Queue& other) {   // Copy constructor
        copy(other);
    }

    Queue& operator=(const Queue& other) { // Operator Assignment
        if (this != &other) {
            delete[] array;
            copy(other);
        }
        return *this;
    }

    void insert(const Object& obj) {
        if (sz == MAX_SIZE) throw "Error: Queue is full!";
        else {
            array[lastEl] = obj;
            sz++;
            lastEl++;
            lastEl = lastEl % MAX_SIZE;
        }
    }

    int erase(Object& elem) {
        if (sz > 0) {
            elem = array[firstEl];
            sz--;
            firstEl++;
            firstEl = firstEl % MAX_SIZE;
            return 1;
        }
        else return 0;
    }

    void print() {
        Object current;
        while (erase(current))
            std::cout << current << " ";
        std::cout << std::endl;
    }

    Object front() {
        if (isEmpty()) throw "Access to empty queue!";
        return array[firstEl];
    }

    bool isEmpty() const { return (sz == 0); }

    int size() const { return (sz); }
};