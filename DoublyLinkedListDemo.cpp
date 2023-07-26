#include <iostream>
#include<conio.h>
using namespace std;

template <typename T>
class list//Doubly Unordered Link List
{
public:
	class node
	{
		T  data;
		node* next;
		node* prev;
		node()
		{
			data = NULL;
			next = prev = nullptr;
		}
		node(T d, node* p)
		{
			data = d;
			next = prev = p;
		}
		friend class list<T>;
	};
	class listiterator
	{
	protected:
		node* current;
		friend class list<T>;
	public:
		//Default Constructor
		listiterator()
		{
			current = nullptr;
		}
		//Parameterized Constructor used in begin and end functions
		listiterator(node* p)
		{
			current = p;
		}
		//Dereference operation to provide access of data to user
		T& operator* () const
		{
			return current->data;
		}
		//Move forward Pre-increment
		listiterator& operator++ ()
		{
			if (current != nullptr)
				this->current = this->current->next;
			return *this;
		}
		//Move forward Post-increment
		listiterator operator++ (int)
		{
			listiterator old = *this;
			++(*this);
			return old;
		}
		listiterator& operator-- ()
		{
			if (current != nullptr)
				this->current = this->current->prev;
			return *this;
		}
		//Move forward Post-decrement
		listiterator operator-- (int)
		{
			listiterator old = *this;
			--(*this);
			return old;
		}
		//If two iterators point to same node
		bool operator== (const listiterator& rhs) const { return current == rhs.current; }
		//If two iterators point to different nodes
		bool operator!= (const listiterator& rhs) const { return !(*this == rhs); }
	};
	//Iterator returned that points to First Node 
	listiterator begin()
	{
		return head->next;
	}
	//Iterator returned that points to Last Node  
	listiterator end()
	{
		return tail->prev;
	}
	bool isEmpty()
	{
		if (head->next->data == NULL)
			return true;
		else
			return false;
	}
	void insert(T value, listiterator &a)
	{
		node* nnode = new node(value, nullptr);
		nnode->prev = a.current;
		nnode->next = a.current->next;
		nnode->next->prev = nnode;
		nnode->prev->next = nnode;
	}
	void insertMultiple(listiterator& a, T value1, T value2)
	{
		insert(value1, a);
		insert(value2, a);
	}
	void del(listiterator& a)
	{
		if (a.current != tail&&a.current!=head)
		{
			node* curr = a.current;
			a++;
			curr->next->prev = curr->prev;
			curr->prev->next = curr->next;
			delete curr;
		}
	}
	void delMultiple(listiterator& a, int values)
	{
		for (int i = 0; i < values; i++)
			del(a);
	}
	void delInRange(listiterator& a, listiterator& b)
	{
		//Another Solution
		/*int temp=0;
		node* curr = a.current->next;
		while (curr != b.current)
		{
			temp++;
			curr = curr->next;
		}
		delMultiple(a, temp);*/
		a++;
		for (; a.current != b.current;)
			del(a);
		--a;
	}
	bool Search(const T &value)
	{
		if (isEmpty())
		{
			cout << "list is empty\n";
			return false;
		}
		bool flag = 0;
		node* curr=head->next;
		while (curr->data != value && curr->data!=NULL)
		{
			curr = curr->next;
		}
		if (curr->data == value)
		{
			cout << value<< " Found";
			flag = 1;
		}
		else
		{
			cout << value<<" Not Found";
			flag = 0;
		}
		return flag;
	}
	list searchAll (const T& value)
	{
		if (isEmpty())
		{
			cout << "list is empty\n";
			return;
		}
		list<listiterator> positions;
		node* curr = head->next;

		while (curr!=tail)
		{
			if (curr->data == value)
			{
				positions.InsertatHead(curr);
			}
			curr = curr->next;
		}
		return positions;
	}

	//Other Functions of Link list
	void  InsertatHead(T value);
	bool deleteFromHead();
	void deleteAll();
	void Swap(int index1,int index2);
	void  printListForward();
	list() 
	{ 
		head = new node;
		tail = new node;
		head->next = tail;
		head->prev = tail->next = nullptr;
		tail->prev = head;
	}
	~list();
private:
	node* head;
	node* tail;
};

//insert node at Head
template <typename T>
void list<T>::InsertatHead(T value)
{
	node* nnode = new node(value, nullptr);
	nnode->prev = head;
	nnode->next = head->next;
	nnode->next->prev = nnode;
	head->next = nnode;
	
}
//Erase
template <typename T>
bool list<T>::deleteFromHead()
{
	if (isEmpty())
	{
		cout << "list is empty\n";
		return false;
	}
	node* curr = head->next;
	if (curr != nullptr)
	{
		head->next = curr->next;
		curr->next->prev = head;
		delete curr;
		return true;
	}
	return false;
}
//Search and Delete All Entries
template <typename T>
void list<T>::deleteAll()
{
	if (isEmpty())
	{
		cout << "list is empty\n";
		return;
	}
	node* curr = head->next;
	node* temp;
	while (curr != tail)
	{
			temp = curr;
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			curr = curr->next;
			delete temp;	
	}
}

//Swap nodes
template <typename T>
void list<T>::Swap(int index1, int index2)
{
	if (isEmpty())
	{
		cout << "list is empty\n";
		return;
	}
	node* curr1 = head->next;
	node* curr2 = head->next;
	node* temp;
	for (int i = 0; i < index1; i++)
		curr1 = curr1->next;
	for (int i = 0; i < index2; i++)
		curr2 = curr2->next;
	if (index1 + 1 != index2)
	{
		//swaping nodes
		temp = curr1->next;
		curr1->next = curr2->next;
		curr2->next = temp;
		temp = curr1->prev;
		curr1->prev = curr2->prev;
		curr2->prev = temp;

		//linking next and prev of nodes
		curr1->next->prev = curr1;
		curr1->prev->next = curr1;
		curr2->next->prev = curr2;
		curr2->prev->next = curr2;
	}
	else
	{
		curr1->next = curr2->next;
		curr2->next = curr1;
		curr2->prev = curr1->prev;
		curr1->prev = curr2;
		curr1->next->prev = curr1;
		curr2->prev->next = curr2;
	}
}
//print list
template <typename T>
void list<T>::printListForward()
{
	if (isEmpty())
	{
		cout << "list is empty\n";
		return;
	}
	node* current;
	current = head->next;
	while (current != tail)
	{
		cout << current->data << " -> ";
		current = current->next;
	}
	cout << "NULL" << endl;
}
//Destructor
template <typename T>
list<T>::~list()
{
	node* temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}
int main()
{
	list<int> l;
	bool runflag=1;
	int temp,size,swc,temp1,temp2,i;
	i = 0;//checks number of loop runs
	
	while (runflag)
	{
		if (i)
		{
			cout << "\nPress Enter";
			_getch();
		}
		i++;
		system("cls");
		cout << "LINKED LIST DEMO " << endl;
		cout << "Menu of Functions" << endl;
		cout << "1)Enter numbers\n2)Print List\n3)Delete from Head\n4)Search\n5)Swap\n6)Delete ALL\n7)Exit\n";
		cin >> swc;
		switch (swc)
		{
		case 1:
			cout << "Enter number of Integers you wish to Enter:";
			cin >> size;
			for (int i = 0; i < size; i++)
			{
				cout << "Enter Number: ";
				cin >> temp;
				l.InsertatHead(temp);
			}
			break;
		case 2:
			cout << "List: ";
			l.printListForward();
			break;
		case 3:
			l.deleteFromHead();
			break;
		case 4:
			cout << "Enter Number you want to search in List:";
			cin >> temp;
			l.Search(temp);
			break;
		case 5:
			cout << "Enter 2 existing number: \n";
			cin >> temp1;
			cin >> temp2;
			l.Swap(temp1, temp2);
			break;
		case 6:
			l.deleteAll();
			break;
		case 7:
			runflag = 0;
			break;
		}
	}	
	return 0;
}