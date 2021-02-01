#include <iostream>
#include <list>
#include <iomanip>

template<typename K, typename V>
class ListDictionary {
public:
    class Pair {
    private:
        K _key;
        V _value;
    public:
        Pair(const K& k = K(), const V& v = V())
            :_key(k), _value(v)
        {}

        const K& getKey() const {
            return _key;
        }

        void setKey(const K& k) {
            _key = k;
        }

        const V& getValue() const {
            return _value;
        }

        void setValue(const V& v) {
            _value = v;
        }
    };
    typedef typename std::list<Pair>::iterator itD;

    ListDictionary() :sz(0) {}

    unsigned size() const {
        return sz;
    }

    bool empty() const {
        return size() == 0;
    }

    itD begin() {
        return lDict.begin();
    }

    itD end() {
        return lDict.end();
    }

    itD find(const K& k) const;
    itD findAll(const K& k, itD& e);
    itD insert(const K& k, const V& v);
    void erase(const K& k);
    void erase(const itD& i);
    void eraseAll(const K& k);
    void print();

private:
    std::list<Pair> lDict;
    unsigned sz;
};

template<typename K, typename V>
typename ListDictionary<K, V>::itD ListDictionary<K, V>::find(const K& k) const {
    for (itD p = lDict.begin(); p != lDict.end(); p++) {
        Pair currentPair = *p;
        if (currentPair.getKey() == k)
            return p;
    }
    return end();
}

template<typename K, typename V>
typename ListDictionary<K, V>::itD ListDictionary<K, V>::findAll(const K& k, ListDictionary<K, V>::itD& e) {
    typename ListDictionary<K, V>::itD b = lDict.begin();
   
    for (itD p = lDict.begin(); p != lDict.end(); p++) {
        Pair currentPair = *p;
        if (currentPair.getKey() != k) {
            b = p;
            b++;
        }
        else
            e = p;
    }
    e++;
    return b;
}

template<typename K, typename V>
typename ListDictionary<K, V>::itD ListDictionary<K, V>::insert(const K& k, const V& v) {
    Pair newPair;
    newPair.setKey(k);
    newPair.setValue(v);
    itD p = lDict.begin();

    while (p != lDict.end()) {
        Pair currentPair = *p;
        if (currentPair.getKey() == k) {
            lDict.insert(p, newPair);
            sz++;
            return p;
        }
        p++;
    }
    lDict.insert(p, newPair);
    return p;
}

template<typename K, typename V>
void ListDictionary<K, V>::erase(const K& k) {
    for (itD p = lDict.begin(); p != lDict.end(); p++) {
        Pair currentPair = *p;
        if (currentPair.getKey() == k) {
            erase(p);
            sz--;
            return;
        }
    }
}

template<typename K, typename V>
void ListDictionary<K, V>::erase(const itD& i) {
    lDict.erase(i);
    sz--;
}

template<typename K, typename V>
void ListDictionary<K, V>::eraseAll(const K& k) {
    for (itD p = lDict.begin(); p != lDict.end(); p++) {
        Pair currentPair = *p;
        if (currentPair.getKey() == k) {
            erase(p);
            sz--;
        }
    }
}

template<typename K, typename V>
void ListDictionary<K, V>::print() {
    Pair currentPair;
    std::cout << std::setw(6) << "Keys" << std::setw(11) << "Value" << std::endl;
    for (itD p = lDict.begin(); p != lDict.end(); p++) {
        currentPair = *p;
        std::cout << std::setw(6) << currentPair.getKey() << std::setw(11) << currentPair.getValue() << std::endl;
    }
    std::cout << std::endl;
}
