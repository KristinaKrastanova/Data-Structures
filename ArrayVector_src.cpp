template <typename Object>
class ArrayVector {
private:
    int length;			// length of array
    int numOfElem;	   // number of elements in vector
    Object* array;			
protected:
    void overflow();				// resizing
    void copy(const ArrayVector& other);
public:

    ArrayVector(int cap = 16) {		
        length = cap;
        numOfElem = 0;
        array = new Object[length];
    }

    ArrayVector(const ArrayVector& other) {
        copy(other);
    }

    ArrayVector& operator=(const ArrayVector& other) {
        if (this != &other) {
            delete[] array;
            copy(other);
        }
        return *this;
    }

    int size() const  		
    {
        return numOfElem;
    }

    bool isEmpty() const  			
    {
        return size() == 0;
    }

    Object& elemAtRank(int r)  			
    {
        return array[r];
    }

    void replaceAtRank(int r, const Object& e)  	
    {
        array[r] = e;
    }

    void push_back(const Object& e) { insertAtRank(numOfElem, e); }
    void pop_back() { removeAtRank(numOfElem - 1); }
    void removeAtRank(int r);			
    void insertAtRank(int r, const Object& e);
    void print();

    ~ArrayVector() { delete[] array; length = 0; numOfElem = 0; }
};

template <typename Object>
void ArrayVector<Object>::
removeAtRank(int r) {				
    for (int i = r; i < numOfElem - 1; i++)
        array[i] = array[i + 1];				
    numOfElem--;
}

template <typename Object>
void ArrayVector<Object>::
insertAtRank(int r, const Object& e) {	
    if (numOfElem == length) overflow();	
    for (int i = numOfElem - 1; i >= r; i--)
        array[i + 1] = array[i];				
    array[r] = e;
    numOfElem++;
}

template <typename Object>
void ArrayVector<Object>::
overflow() {					
    length *= 2;		
    Object* b = new Object[length];
    for (int i = 0; i < numOfElem; i++) {	
        b[i] = array[i];
    }
    delete[] array;				
    array = b;				
}

template<typename Object>
void ArrayVector<Object>::
copy(const ArrayVector& other) {
    length = other.length;
    numOfElem = other.numOfElem;
    array = new Object[length];
    for (int i = 0; i < numOfElem; i++) {
        array[i] = other.array[i];
    }
}

template<typename Object>
void ArrayVector<Object>::print() {
    std::cout << "Elements in the array: ";
    for (int i = 0; i < numOfElem; i++) {
        std::cout << array[i] << ", ";
    }
    std::cout << std::endl;
}
