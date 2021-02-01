template <typename Obj>
class NodeList { 
public:
	NodeList(); 
	~NodeList();
	int size() const;
	bool empty() const; 
	const Obj& front() const; 
	const Obj& back() const; 
	void addFront(const Obj& e); 
	void addBack(const Obj& e);
	void removeFront(); 
	void removeBack(); 
private: 
	struct Node {
		Obj  element;				
		Node* prev;				
		Node* next;				
		Node(const Obj& e = Obj(), Node* p = NULL, Node* n = NULL)
			: element(e), prev(p), next(n) { }	
	};
	int size;
	Node* header; 
	Node* trailer;
protected: 
	void add(Node* v, const Obj& e);
	void remove(Node* v); 
};

template <typename Obj>
NodeList<Obj>::NodeList() {
	header = new Node; 
	trailer = new Node;
	header->next = trailer; 
	trailer->prev = header;
}

template <typename Obj>
NodeList<Obj>::~NodeList() {
	while (!empty()) removeFront(); 
	delete header; 
	delete trailer;
}

template <typename Obj>
int NodeList<Obj>::size() const {
	return size;
}

template <typename Obj>
bool NodeList<Obj>::empty() const
{
	return (header->next == trailer);
}

template <typename Obj>
const Obj& NodeList::front() const 
{
	return header->next->element;
}

template <typename Obj>
const Obj& NodeList::back() const 
{
	return trailer->prev->element;
}

template <typename Obj>
void NodeList<Obj>::add(Node* v, const Obj& e) {
	Node* u = new Node; u->elem = e; 
	u->next = v;
	u->prev = v->prev;
	v->prev->next = v->prev = u;
}

template <typename Obj>
void NodeList<Obj>::addFront(const Obj& e)
{
	add(header->next, e);
}

template <typename Obj>
void NodeList<Obj>::addBack(const Obj& e)
{
	add(trailer, e);
}

template <typename Obj>
void NodeList<Obj>::remove(Node* v) {
	Node* u = v->prev;
	Node* w = v->next;
	u->next = w;
	w->prev = u;
	delete v;
}

template <typename Obj>
void NodeList<Obj>::removeFront()
{
	remove(header->next);
}

template <typename Obj>
void NodeList<Obj>::removeBack()
{
	remove(trailer->prev);
}

