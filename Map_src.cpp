#include <iostream>
#include <list>
#include <iomanip>

template<typename K, typename V>
class Map {
public:
	class Pair {
	private:
		K _key;
		V _value;
	public:
		Pair(const K& k = K(), const V& v = V()) :
			_key(k), _value(v)
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

		bool operator<(const Pair& p) {
			return _value < p._value;
		}
	};

	typedef typename std::list<Pair>::iterator mIter;

	Map() :sz(0) {}

	int size() const {
		return sz;
	}

	bool empty()const {
		return size() == 0;
	}

	mIter begin() {
		return LMap.begin();
	}

	mIter end() {
		return LMap.end();
	}

	mIter find(const K& k);
	mIter put(const K& k, const V& v);
	void erase(const K& k);
	void erase(const mIter& p);
	void print();
	
private:
	unsigned sz;
	std::list<Pair> LMap;
};

template<typename K, typename V>
typename Map<K,V>::mIter Map<K, V>::find(const K& k) {
	for (mIter p = LMap.begin(); p != LMap.end(); p++) {
		Pair currentPair = *p;
		if (currentPair.getKey() == k)
			return p;
	}
	return end();
}

template<typename K, typename V>
typename Map<K, V>::mIter Map<K, V>::put(const K& k, const V& v) {
	Pair newPair = Pair(k, v);
	mIter p = LMap.begin();

	while (p != LMap.end()) {
		Pair currentPair = *p;
		if (currentPair.getKey() == k) {
			*p = newPair;
			return p;
		}
		p++;
	}

	LMap.insert(p, newPair); //last element
	sz++;
	return p;
}

template<typename K, typename V>
void Map<K, V>::erase(const K& k) {
	for (mIter p = LMap.ebgin(); p != LMap.end(); p++) {
		Pair currentPair = *p;
		if (currentPair.getKey() == k) {
			LMap.erase(p);
			sz--;
		}
	}
}

template<typename K, typename V>
void Map<K, V>::erase(const mIter& p) {
	LMap.erase(p);
}

template<typename K, typename V>
void Map<K, V>::print() {
	Pair currentPair;
	std::cout << std::setw(6) << "Keys" << std::setw(11) << "Value" << std::endl;
	for (mIter p = LMap.begin(); p != LMap.end(); p++) {
		currentPair = *p;
		std::cout << std::setw(6) << currentPair.getKey() << std::setw(11) << currentPair.getValue() << std::endl;
	}
}
