#include <iostream>

using namespace std;

class Element
{
private:
	int v;
	Element* next;
	Element* prev;

public:
	Element()
	{
		next = nullptr;
		prev = nullptr;
	}

	Element(int x, Element* next, Element* prev)
	{
		v = x;
		this->next = next;
		this->prev = prev;
	}

	int getValue()
	{
		return v;
	}

	void setValue(int v)
	{
		this->v = v;
	}

	Element* getNext()
	{
		return next;
	}

	Element* getPrev()
	{
		return prev;
	}

	void setNext(Element* p)
	{
		next = p;
	}

	void setPrev(Element* p)
	{
		prev = p;
	}
};

class LinkedList
{
protected:
	Element* head;
	Element* tail;
	int size;

public:
	LinkedList()
	{
		size = 0;
		head = nullptr;
		tail = nullptr;
	}

	bool empty()
	{
		return head == nullptr;
	}

	int getSize()
	{
		return size;
	}

	Element* getFirst()
	{
		if (empty())
		{
			cout << "Lista jest pusta!\n";
			return nullptr;
		}
		return head;
	}

	Element* getLast()
	{
		if (empty())
		{
			cout << "Lista jest pusta!\n";
			return nullptr;
		}
		return tail;
	}

	Element* getNext(Element* p)
	{
		if (p == nullptr)
		{
			cout << "Nie ma takiego elementu w liscie!\n";
			return nullptr;
		}
		return p->getNext();
	}

	Element* getPrev(Element* p)
	{
		if (p == nullptr)
		{
			cout << "Nie ma takiego elementu w liscie!\n";
			return nullptr;
		}
		return p->getPrev();
	}

	int retrive(Element* p)
	{
		if (p == nullptr)
		{
			cout << "Nie ma takiego elementu w liscie!\n";
			return -1;
		}
		return p->getValue();
	}

	void append(int x)
	{
		Element* e = new Element(x, nullptr, tail);
		if (empty())
		{
			head = e;
			tail = e;
		}
		else
		{
			tail->setNext(e);
			tail = e;
		}
		size++;
	}

	void preppend(int x)
	{
		Element* e = new Element(x, head, nullptr);
		if (empty())
		{
			head = e;
			tail = e;
		}
		else
		{
			head->setPrev(e);
			head = e;
		}
		size++;
	}

	friend ostream& operator<<(ostream& out, LinkedList* l)
	{
		Element* e = l->head;
		while (e != nullptr)
		{
			out << e->getValue() << " ";
			e = e->getNext();
		}
		return out;
	}

	void insert(Element* p, int x)
	{
		Element* e = new Element(x, nullptr, nullptr);
		if (p == head)
		{
			preppend(x);
		}
		else if(p == nullptr)
		{
			append(x);
		}
		else
		{
			e->setNext(p);
			e->setPrev(p->getPrev());
			p->getPrev()->setNext(e);
			p->setPrev(e);
			size++;
		}
		return;
	}

	void insert(int p, int x)
	{
		if (p <= size)
		{
			Element* e = head;
			for (int i = 0; i < p; i++)
			{
				e = e->getNext();
			}
			insert(e, x);
			return;
		}
		cout << "Lista jest za krotka i nie ma takiej pozycji";
		return;
	}

	void del(int p)
	{
		if (p >= size)
		{
			cout << "Nie ma elementu o takim indeksie";
			return;
		}
		else if (p == 0)
		{
			head = head->getNext();
			head->setPrev(nullptr);
			size--;
			return;
		}
		else if (p == (size - 1))
		{
			tail = tail->getPrev();
			tail->setNext(nullptr);
			size--;
			return;
		}

		Element* e = head;
		for (int i = 0; i <= p; i++)
		{
			e = e->getNext();
		}
		Element* pom = e->getPrev();
		pom = pom->getPrev();
		e->setPrev(pom);
		pom->setNext(e);
		size--;
	}

	void del(Element* p)
	{
		if (p == nullptr)
		{
			cout << "Nie ma takiego elementu w liscie";
			return;
		}
		else if(p == head)
		{
			head = head->getNext();
			head->setPrev(nullptr);
			size--;
			return;
		}
		else if (p == tail)
		{
			tail = tail->getPrev();
			tail->setNext(nullptr);
			size--;
			return;
		}
		Element* e = p;
		e = p->getNext();
		e->setPrev(p->getPrev());
		e = p->getPrev();
		e->setNext(p->getNext());
		size--;
	}

	Element* locate(int x)
	{
		Element* e = head;
		while (e->getNext() != nullptr)
		{
			if (e->getValue() == x)
			{
				return e;
			}
			e = e->getNext();
		}
		return nullptr;
	}

	~LinkedList()
	{
		delete head;
		delete tail;
	}
};

class SortedLinkedList : public LinkedList
{
public:

	SortedLinkedList()
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	SortedLinkedList(LinkedList l)
	{
		head = l.getFirst();
		tail = l.getLast();
		size = l.getSize();
	}

	void insertSorted(int x)
	{
		Element* e = head;
		while (e->getNext() != nullptr)
		{
			if (e->getValue() >= x)
			{
				insert(e, x); 
				return;
			}
			e = e->getNext();
		}
		insert(e->getNext(), x);
	}

};

int main()
{
	//Zadanie 1
	cout << "Zadanie 1\n\n";

	LinkedList* a = new LinkedList();

	cout << "a->empty() [1]: " << a->empty() << "\n";
	cout << "a->getSize() [0]: " << a->getSize() <<  "\n";
	cout << "a->getFirst() [error]: " << a->getFirst() << "\n";
	cout << "a->getLast() [error]: " << a->getLast() << "\n";
	cout << "a->insert(0, 7) "; a->insert(0, 7);
	cout << "\n" << a << "\n";
	cout << "a->append(5) \n"; a->append(5);
	cout << a << "\n";
	cout << "a->append(6) \n"; a->append(6);
	cout << "a->append(9) \n"; a->append(9);
	cout << "a->preppend(1) \n"; a->preppend(1);
	cout << a << "\n";
	cout << "a->getSize() [4]: " << a->getSize() << "\n";
	cout << "a->insert(2, 10) "; a->insert(2, 10);
	cout << "\n" << a << "\n";
	Element* first = a->getFirst();
	cout << "a->retrive(first) [1]: " << a->retrive(first) << "\n";
	Element* last = a->getLast();
	cout << "a->retrive(last) [9]: " << a->retrive(last) << "\n";
	cout << "a->empty() [0]: " << a->empty() << "\n";
	cout << "a->insert(6,8) "; a->insert(6, 8);
	cout << "\n" << a << "\n";
	cout << "a->getNext(first) [7]: " << a->retrive(a->getNext(first)) << "\n";
	last = a->getLast();
	cout << "a->getPrev(last) [9]: " << a->retrive(a->getPrev(last)) << "\n";
	cout << a << "\n";
	cout << "a->insert(0, 4) "; a->insert(0, 4);
	cout << "\n" << a << "\n";
	last = a->getLast();
	cout << "a->insert(a->getNext(last), 15) "; a->insert(a->getNext(last), 15);
	cout << "\n" << a << "\n";
	cout << "a->getSize() [9]: " << a->getSize() << "\n";

	cout << "a->del(5) "; a->del(5);
	cout << "\n" << a << "\n";
	cout << "a->del(0) "; a->del(0);
	cout << "\n" << a << "\n";
	cout << "a->del(last) (by index) "; a->del(a->getSize()-1);
	cout << "\n" << a << "\n";
	cout << "a->del(last+1) (by index) "; a->del(a->getSize());
	cout << "\n" << a << "\n";
	cout << "a->append(2) \n"; a->append(2);
	cout << "a->append(3) \n"; a->append(3);
	cout << "a->append(4) \n"; a->append(4);
	cout << "a->append(6) \n"; a->append(6);
	cout << "\n" << a << "\n";

	first = a->getFirst();
	last = a->getLast();
	cout << "a->del(first) "; a->del(first);
	cout << "\n" << a << "\n";
	cout << "a->del(last) "; a->del(last);
	cout << "\n" << a << "\n";
	first = a->getFirst();
	cout << "a->del(first->getNext()->getNext()) "; a->del(first->getNext()->getNext());
	cout << "\n" << a << "\n";
	last = a->getLast();
	cout << "a->del(last+1) "; a->del(last->getNext());cout << "\n";

	Element* e;
	cout << "a->locate(9) [9]"; e = a->locate(9); cout << a->retrive(e) << "\n";
	cout << "a->locate(25) [error]"; e = a->locate(25); cout << a->retrive(e) << "\n";

	//Zadanie 2
	cout << "\n\nZadanie2\n\n";
	SortedLinkedList* b = new SortedLinkedList();

	cout << "b->append(1) \n"; b->append(1);
	cout << "b->append(3) \n"; b->append(3);
	cout << "b->append(5) \n"; b->append(5);
	cout << "b->append(6) \n"; b->append(6);
	cout << "b->append(8) \n"; b->append(8);
	cout << "b->append(10) \n"; b->append(10);
	cout << "b->insertSorted(4) "; b->insertSorted(4);
	cout << "\n" << b << "\n";
	cout << "b->insertSorted(0) "; b->insertSorted(0);
	cout << "\n" << b << "\n";
	cout << "b->insertSorted(14) "; b->insertSorted(14);
	cout << "\n" << b << "\n";
	cout << "b->insertSorted(3) "; b->insertSorted(3);
	cout << "\n" << b << "\n";


	return 0;
}