const int MAX_SIZE = 1000; 

template <typename Object>
class ArrayStack {
private:
    int length; 
    int topElem;
    Object* arr; 

    void copy(const ArrayStack& other) {
        arr = new Object[length];

        for (int i = 0; i <= topElem; i++) {
            arr[i] = other.arr[i];
        }
        length = other.length;
        topElem = other.topElem;
    }

public:
    ArrayStack(int length = size):length(length){
        arr = new Object[length];
        topElem = -1;
    }

    ArrayStack(const ArrayStack& other) {
        copy(other);
    }

    ArrayStack& operator=(const ArrayStack& other) {
        if (this != &other) {		
            delete[] arr;		
            copy(other);
        }
        return *this;
    }

    ~ArrayStack() {
        delete[] arr;
    }


    void push(const Object& obj) {
        if (size == length) throw "Error: Stack overflow";
        topElem++;
        arr[topElem] = obj;
    }

    Object pop() {
        if (isEmpty()) throw "Erorr: Access to empty stack";
        return arr[topElem--];
    }

    Object& top() const {
        return arr[topElem];
    }

    bool isEmpty() const {
        return (topElem < 0);
    }

    int size() const{
        return (topElem + 1);
    }

    void print()
    {
        while (!isEmpty()) {
            std::cout << top() << " ";
            pop();
        }
        std::cout << std::endl;
    }

    ArrayStack<Object> reversStack(ArrayStack<Object> other) { //not always neccesary!!!!
        ArrayStack<Object> resultSt;
        while (!other.isEmpty()) {
            resultSt.push(other.top());
            other.pop();
        }
        return resultSt;
    }
};

