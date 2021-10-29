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
private:
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
		if(p == nullptr)
		{
			append(x);
		}
		else
		{
			e->setNext(p);
			e->setPrev(p->getPrev());
			p->getPrev()->setNext(e);
			p->setPrev(e);
		}
		size++;
		return;
	}

	void insert(int p, int x)
	{
		if (p < size)
		{
			Element* e = head;
			for (int i = 0; i < p; i++)
			{
				e = e->getNext();
			}
			insert(e, x);
			return;
		}
		return;
	}

	void del(int p);

	~LinkedList()
	{
		delete head;
		delete tail;
	}




};

int main()
{
	//Zadanie 1

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
	cout << "a->getNext(first) [5]: " << a->retrive(a->getNext(first)) << "\n";
	cout << "a->getPrev(first) [6]: " << a->retrive(a->getPrev(last)) << "\n";
	cout << a << "\n";
	cout << "a->insert(0, 4) "; a->insert(0, 4);
	cout << "\n" << a << "\n";
	last = a->getLast();
	cout << "a->insert(a->getPrev(last), 15) "; a->insert(a->getPrev(last), 15);
	cout << "\n" << a << "\n";
	return 0;
}