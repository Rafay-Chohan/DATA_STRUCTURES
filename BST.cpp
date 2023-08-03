#include <iostream>
#include<stack>
#include<vector>
using namespace std;


int max(int num1, int num2)
{
	return ((num1 > num2) ? num1 : num2);
}
template <typename T>
class Queue
{

public:
	class node
	{
		T  data;
		node* next;
		node(T d, node* p)
		{
			data = d;
			next = p;
		}
		friend class Queue<T>;
	};

	class Queueiterator
	{
	protected:
		node* current;
		friend class Queue<T>;
	public:
		//Default Constructor
		Queueiterator()
		{
			current = nullptr;
		}
		//Parameterized Constructor used in begin and end functions
		Queueiterator(node* p)
		{
			current = p;
		}
		//Dereference operation to provide access of data to user
		T& operator* () const
		{
			return current->data;
		}
		//Move forward Pre-increment
		Queueiterator& operator++ ()
		{
			if (current != nullptr)
				this->current = this->current->next;
			return *this;
		}
		//Move forward Post-increment
		Queueiterator operator++ (int)
		{
			Queueiterator old = *this;
			++(*this);
			return old;
		}
		//If two iterators point to same node
		bool operator== (const Queueiterator& rhs) const { return current == rhs.current; }
		//If two iterators point to different nodes
		bool operator!= (const Queueiterator& rhs) const { return !(*this == rhs); }
	};
	//Iterator returned that points to First Node 
	Queueiterator begin()
	{
		return front;
	}
	//Iterator returned that points to Last Node  
	Queueiterator end()
	{
		return nullptr;
	}

	//Other Functions of Link Queue
	void printQueue();
	void Front(T& element);
	void Enqueue(T value);
	void Dequeue(T& element);
	void Dequeue();
	bool isFull();
	bool isEmpty();

	Queue() { front = nullptr; rear = nullptr; }
	~Queue();
private:
	node* front;
	node* rear;
};
template <typename T>
bool Queue<T>::isFull()
{
	return false;
}
template <typename T>
bool Queue<T>::isEmpty()
{
	if (front == nullptr)
		return true;
	else
		return false;
}
//Erase
template <typename T>
void Queue<T>::Dequeue()
{
	node* curr = front;
	front = front->next;
	delete curr;
}
template <typename T>
void Queue<T>::Dequeue(T& element)
{
	node* curr = front;
	front = front->next;
	element = curr->data;
	delete curr;
}
template <typename T>
void Queue<T>::Front(T& element)
{
	element = front->data;
}
//Enqueuenode at rear
template <typename T>
void Queue<T>::Enqueue(T value)
{
	node* nnode = new node(value, nullptr);
	if (front == NULL)
	{
		front = nnode;
		rear = nnode;
	}
	else
	{
		rear->next = nnode;
		rear = nnode;
	}
}
//Destructor
template <typename T>
Queue<T>::~Queue()
{
	node* temp;
	while (front != nullptr)
	{
		temp = front;
		front = front->next;
		delete temp;
	}

}

//print Queue
template <typename T>
void Queue<T>::printQueue()
{
	node* current;
	current = front;
	while (current != nullptr)
	{
		cout << current->data << " -> ";
		current = current->next;
	}
	cout << "NULL" << endl;
}
struct Node
{
	int data;
	Node* left;
	Node* right;
	int height;
	Node(int userInput, Node* userRight, Node* userLeft)
	{
		data = userInput;
		right = userRight;
		left = userLeft;
		height = 0;
	}
	int getHeight()
	{
		if (this)
		{
			return height;
		}
		else
			return -1;
	}
};

class BST
{
private:
	Node* root;
	void makeBst(int key1, int key2)
	{
		delete_recursive(key1);
		insert(key2);
	}
	bool copyVLR(Node* curr)//Recursive Helper Function of Copy Constructor
	{
		if (curr == nullptr)
			return false;
		else
		{
			insert(curr->data);
			copyVLR(curr->left);
			copyVLR(curr->right);
		}

	}
	void Printin(Node* curr)//Recursive Helper Function of Print inorder
	{
		if (curr == nullptr)
			return;
		else
		{
			Printin(curr->left);
			cout << curr->data << " ";
			Printin(curr->right);
		}
	}
	void Printpost(Node* curr)//Recursive Helper Function of Print Postorder
	{
		if (curr == nullptr)
			return;
		else
		{
			Printpost(curr->left);
			Printpost(curr->right);
			cout << curr->data << " ";
		}
	}
	void Printpre(Node* curr)//Recursive Helper Function of Print Preorder
	{
		if (curr == nullptr)
			return;
		else
		{
			cout << curr->data << " ";
			Printpre(curr->left);
			Printpre(curr->right);
		}
	}
	bool searchBinary(Node* curr, int key)//Recursive Helper Function of Search
	{
		bool flag;
		if (curr == nullptr)
			return false;
		if (curr->data == key)
			return true;
		else if (curr->data > key)
		{
			flag = searchBinary(curr->left, key);//goes left as key is smaller
			if (flag)
				return flag;
		}
		else
		{
			flag = searchBinary(curr->right, key);//Goes Right as key is larger
			if (flag)
				return flag;
		}
		return false;
	}
	int countNodesHelp(Node* curr) const // Helper Function of CountNode
	{
		int temp = 0;
		if (root == NULL)
			return temp;
		bool lflag = 0;
		bool rflag = 0;
		stack<Node*>stk;
		stk.push(curr);
		temp++;
		while (!stk.empty())
		{
			while (curr->left != NULL)
			{
				stk.push(curr->left);
				curr = curr->left;
				temp++;
				lflag = 0;
			}
			while (true)
			{
				if (curr->right != NULL && (!lflag || !rflag))
				{
					curr = curr->right;
					temp++;
					stk.push(curr);
					rflag = 0;
					lflag = 1;
					break;
				}
				else
				{
					rflag = 1;
					if (stk.empty())
						break;
					stk.pop();
					if (!stk.empty())
						curr = stk.top();
				}
			}
		}
		return temp;
	}
	int leafCountHelp(Node* curr) const//Recursive Helper Function of LeafCount
	{
		int temp;
		if (curr == nullptr)
			return 0;
		if (curr->left == nullptr && curr->right == nullptr)
			return 1;
		else
		{
			temp = leafCountHelp(curr->left);
			temp += leafCountHelp(curr->right);
		}
		return temp;
	}
	void pathSum(vector <int>& sum,Node *n1,int temp=0)
	{
		if (n1->left==NULL&&n1->right==NULL)
		{
			temp += n1->data;
			sum.push_back(temp);
			return;
		}
		else
		{
			temp += n1->data;
			if(n1->left!=NULL)
				pathSum(sum, n1->left, temp);
			if (n1->right != NULL)
				pathSum(sum, n1->right, temp);
		}
		return;
	}
	bool isBst(Node* curr)
	{
		if (curr)
		{
			if (curr->left != NULL && curr->data < curr->left->data)
				return false;
			else if (curr->right != NULL && curr->data > curr->right->data)
				return false;
			else
			{
				return isBst(curr->left) && isBst(curr->right);
			}
		}
		else
			return true;
	}
	void Mirror(Node *curr)
	{
		if (curr)
		{
			Node* temp = curr->left;
			curr->left = curr->right;
			curr->right = temp;
			Mirror(curr->left);
			Mirror(curr->right);
		}
	}
	void rightRotate(Node*& x,Node* y,Node *parent) // This function performs right rotation
	{
		x->left = y->right;
		y->right = x;
		if (parent)
		{
			if (parent->left == x)
				parent->left = y;
			else if (parent->right == x)
				parent->right = y;
		}
		else if (root == x)
			root = y;
		x = y;
		
	}
	void makeSkew(Node *curr)
	{
		Node* prev=NULL;
		while (curr)
		{
			while (curr->left)
			{
				rightRotate(curr, curr->left, prev);
			}
			prev = curr;
			curr = curr->right;
		}

	}
	void findWidth(Node*curr,int *arr)
	{
		if (curr == nullptr)
			return;
		else
		{
			arr[curr->getHeight()] += 1;
			findWidth(curr->left,arr);
			findWidth(curr->right,arr);
		}
	}
	void checkPre(Node* curr, Node* p,Node*& tmp)
	{
		if (!p->right)
		{
			if (p->data > curr->data)
			{
				int temp = curr->data;
				curr->data = p-> data;
				p->data = temp;
			}
			return;
		}
		if (p->right)
		{
			
			checkPre(curr, p->right,tmp);
			if (p->data > p->right->data)
			{
				int temp = p->right->data;
				p->right->data = p->data;
				p->data = temp;
				tmp = p;
			}
			return;
		}
		else
			return;

	}
	void checkSucc(Node* curr, Node* s, Node*& tmp)
	{
		if (!s->left)
		{
			if (s->data < curr->data)
			{
				int temp = curr->data;
				curr->data = s->data;
				s->data = temp;
			}
		}
		if (s->left)
		{
			checkSucc(curr, s->left,tmp);
			if (s->data < s->left->data)
			{
				int temp = s->left->data;
				s->left->data = s->data;
				s->data = temp;
				tmp = s;

			}
		}
		else
			return;
	}	
	void updateKey(int key1,int key2,Node* curr)
	{
		if (curr)
		{
			if (curr->data == key1)
			{
				makeBst(key1, key2);
				return;
			}
			else
			{
				if (key1 < curr->data)
				{
					updateKey(key1, key2, curr->left);
					if (curr->data < curr->left->data)
					{
						int temp = curr->data;
						curr->data = curr->left->data;
						curr->left->data = temp;
						return;
					}
				}
				if (key1 > curr->data)
				{
					updateKey(key1, key2, curr->right);
					if (curr->data > curr->right->data)
					{
						int temp = curr->data;
						curr->data = curr->right->data;
						curr->right->data = temp;
						return;
					}
				}
				Node* temp;
					if (curr->left)
					{
						Node* p = curr->left;
						checkPre(curr, p,temp);
					}
					if (curr->right)
					{
						Node* s = curr->right;
						checkSucc(curr, s,temp);
					}
				

			}
			

		}
	}
	void commonAncestorsHelp(Node* n1, Node* n2,Node* curr)
	{
		if (curr->data == n1->data || curr->data == n2->data)
			return;
		if (curr->data > n1->data && curr->data > n2->data)
		{
			cout << curr->data << " ";
			commonAncestorsHelp(n1, n2, curr->left);
			return;
		}
		else if (curr->data < n1->data && curr->data < n2->data)
		{
			cout << curr->data << " ";
			commonAncestorsHelp(n1, n2, curr->right);
			return;
		}
		cout << curr->data << " ";
		return;
	}
	void updatePrev(Node* prev, Node* curr, Node* next)
	{
		if (curr == prev->left)
			prev->left = next;
		else if (curr == prev->right)
			prev->right = next;
	}
	bool checkEqual(Node* n1, Node* n2)
	{
		if (n1 && n2)
		{
			if (n1->data != n2->data)
				return false;
			else
			{
				return checkEqual(n1->left, n2->left) && checkEqual(n1->right, n2->right);
			}

		}
		else if (!n1 && !n2)
			return true;
		else
			return false;
	}
	bool delete_recursivehelper(Node* curr, Node* prev, int val)//Recursive Helper function of Deletion
	{
		if (curr == NULL)
			return false;
		if (curr->data == val)
		{
			if (curr->left == NULL && curr->right == NULL)//Case 1 Leaf Node
			{
				if (curr != prev)
				{
					updatePrev(prev, curr, NULL);
				}
				delete curr;
			}
			else if ((curr->left != NULL && curr->right == NULL) || (curr->left == NULL && curr->right != NULL))//Case 2: 1 child
			{
				if (curr->left != NULL && curr->right == NULL)//For left child
				{
					updatePrev(prev, curr, curr->left);
				}
				else
					updatePrev(prev, curr, curr->right);//for right child
				delete curr;
			}
			else if (curr->left != NULL && curr->right != NULL)//Case 3 For both child including if root 
			{
				Node* p = curr->left;
				while (p->right != NULL)
				{
					prev = p;
					p = p->right;
				}
				//Swap predecessor and curr
				int temp = curr->data;
				curr->data = p->data;
				p->data = temp;
				updatePrev(prev, p, p->left);
				delete p;
			}
			return true;
		}
		else
		{
			delete_recursivehelper(curr->left, curr, val);
			delete_recursivehelper(curr->right, curr, val);
		}

	}
	void delTree(Node* curr)//Recursive Helper Function for Destructor
	{
		if (curr == nullptr)
			return;
		else
		{
			delTree(curr->left);
			delTree(curr->right);
			delete curr;
			root = NULL;
			return;
		}
	}
public:
	//CONSTRUCTOR
	BST()
	{
		root = nullptr;
	}
	
	//Copy Constructor
	BST(BST& obj)
	{
		root = nullptr;
		copyVLR(obj.root);
	}

	//Insert
	//bool insert(int key)
	//{
	//	Node* n = new Node;
	//	n->data = key;
	//	n->left = nullptr;
	//	n->right = nullptr;
	//	n->height = 0;
	//	if (root == nullptr)
	//	{
	//		root = n;
	//		root->left = nullptr;
	//		root->right = nullptr;
	//		return true;
	//	}
	//	Node* curr = root;
	//	Node* prev = nullptr;
	//	while (curr != nullptr)
	//	{
	//		if (curr->data == key)
	//			return false;
	//		else if (curr->data > key)
	//		{
	//			prev = curr;
	//			curr = curr->left;//goes left as key is smaller
	//		}
	//		else
	//		{
	//			prev = curr;
	//			curr = curr->right;//Goes Right as key is larger
	//		}
	//	}
	//	if (prev->data > key)
	//		prev->left = n;
	//	else
	//		prev->right = n;

	//	return true;
	//}
	void insert(int data) //inserts a new node in the AVL tree and maintains the height property of the AVL tree.
	{
		Insert(root, data);
	}
	void Insert(Node*& r, int userInput)
	{
		if (!r)
			r = new Node(userInput, nullptr, nullptr);
		else
		{
			if (r->data > userInput)
			{
				Insert(r->left, userInput);
			}
			else if (r->data < userInput)
			{
				Insert(r->right, userInput);
			}
			r->height = 1 + max(r->left->getHeight(),r->right->getHeight());
		}
	}
	//Print Using Recurrsion
	void inorderPrint()//LVR
	{
		Printin(root);
		cout << endl;
	}
	void postorderPrint()//LRV
	{
		Printpost(root);
		cout << endl;
	}
	void preorderPrint()//VLR
	{
		Printpre(root);
		cout << endl;
	}
	//Print Iterative
	void PrintinIterative()//Recursive Helper Function of Print inorder
	{
		if (root == NULL)
			return;
		cout << "Iterative InOrder: ";
		Node* curr = root;
		stack<Node*>stk;
		stk.push(curr);
		while (!stk.empty())
		{
			while (curr->left != NULL)
			{
				stk.push(curr->left);
				curr = curr->left;
			}
			curr = stk.top();
			cout << curr->data << " ";
			stk.pop();
			while (true)
			{
				if (curr->right != NULL)
				{
					curr = curr->right;
					stk.push(curr);
					break;
				}
				else
				{
					if (stk.empty())
						break;
					curr = stk.top();
					cout << curr->data << " ";
					stk.pop();

				}
			}
		}
		cout << endl;

	}
	void PrintpostIterative()//Recursive Helper Function of Print Postorder
	{
		if (root == NULL)
			return;
		bool lflag=0;
		bool rflag=0;
		cout << "Iterative PostOrder: ";
		Node* curr = root;
		stack<Node*>stk;
		stk.push(curr);
		while (!stk.empty())
		{
			while (curr->left != NULL)
			{
				stk.push(curr->left);
				curr = curr->left;
				lflag = 0;
			}
			while (true)
			{
				if (curr->right != NULL&&(!lflag||!rflag))
				{
					curr = curr->right;
					stk.push(curr);
					rflag = 0;
					lflag = 1;
					break;
				}
				else
				{
					rflag = 1;
					if (stk.empty())
						break;
					cout << curr->data << " ";
					stk.pop();
					if (!stk.empty())
					curr = stk.top();
				}
			}
		}
		cout << endl;
	}
	void PrintpreIterative()//Recursive Helper Function of Print Preorder
	{
		if (root == NULL)
			return;
		bool lflag = 0;
		bool rflag = 0;
		cout << "Iterative PreOrder: ";
		Node* curr = root;
		stack<Node*>stk;
		stk.push(curr);
		cout << curr->data<<" ";
		while (!stk.empty())
		{
			while (curr->left != NULL)
			{
				stk.push(curr->left);
				curr = curr->left;
				cout << curr->data<<" ";
				lflag = 0;
			}
			while (true)
			{
				if (curr->right != NULL&&(!lflag||!rflag))
				{
					curr = curr->right;
					cout << curr->data << " ";
					stk.push(curr);
					rflag = 0;
					lflag = 1;
					break;
				}
				else
				{
					rflag = 1;
					if (stk.empty())
						break;
					stk.pop();
					if (!stk.empty())
					curr = stk.top();
				}
			}
		}
		cout << endl;
	}

	//Print Using Level Order
	void levelOrderPrint()
	{
		Node* curr = root;
		Queue<Node*> Q;
		Q.Enqueue(curr);
		while (!(Q.isEmpty()))
		{
			Q.Front(curr);
			cout << curr->data << " ";

			if (curr->left != NULL)
				Q.Enqueue(curr->left);
			if (curr->right != NULL)
				Q.Enqueue(curr->right);
			Q.Dequeue();
		}
		cout << endl;
	}

	//Search With Recurrsion
	bool search(int key)
	{
		return searchBinary(root, key);
	}

	//Counting Nodes With Iterative
	int countNodes() const
	{
		return countNodesHelp(root);
	}

	//Leaf Count VLR
	int leafCount() const
	{
		return leafCountHelp(root);
	}

	//Path Sum
	void pathSum(vector <int>& sum)
	{
		pathSum(sum, root);
	}

	//Common Ancestor
	void commonAncestors(Node* n1, Node* n2)
	{
		commonAncestorsHelp(n1, n2, root);
	}

	//Update Width
	void updateKey(int key1, int key2)
	{
		if (search(key2))
			cout << "Key 2 already exists in Tree";
		else
			updateKey(key1, key2, root);
	}
	//Find Width
	int findWidth()
	{
		int* arr = new int[root->getHeight() + 1];
		for (int i = 0; i <= root->getHeight(); i++)
		{
			arr[i] = 0;
		}
		findWidth(root,arr);
		int max = arr[0];
		for (int i = 1; i <= root->getHeight(); i++)
		{
			if (max < arr[i])
				max = arr[i];
		}
		return max;
	}

	//IsBST
	bool isBst()
	{
		return isBst(root);
	}

	//Mirror
	void Mirror()
	{
		Mirror(root);
	}

	//Make Skew
	void makeSkew()
	{
		makeSkew(root);
	}

	//Deletion
	bool delete_recursive(int val)
	{
		if (root == NULL || !search(val))
			return false;
		else
		{
			delete_recursivehelper(root, root, val);
			return true;
		}

	}

	//Overloaded Assignment operator

	BST& operator =(const BST& obj)
	{
		if (root != NULL)
			delTree(root);
		
		copyVLR(obj.root);
		return *this;
	}

	//Overloaded == operator

	bool operator ==(const BST& obj)
	{
		return checkEqual(root, obj.root);
	}
	
	//Destructor VLR
	~BST()
	{
		delTree(root);
	}
};
int main()
{
	BST tree;
	BST tree2;
	vector<int> sum;
	Node* n1 = new Node(0, nullptr, nullptr);
	Node* n2 = new Node(0, nullptr, nullptr);
	int data, option = 1, size;;
	bool t2 = 0;
	cout << "How Many elements you wish to enter: ";
	cin >> size;
	cout << "Enter (Unique) numbers in Tree: \n";
	for(int i=0 ; i < size ; i++)
	{
		cin >> data;
		tree.insert(data);
	}
	system("cls");
	cout << "Data Entered Successfully\n";

	BST tree3(tree);
	while (option)
	{
		cout << "Which sub-Program Do you want to run:\n1)InOrder Print\t\t\t\t2)PostOrder Print\n3)PreOrder Print\t\t\t4)Level Order Print\n5)tree by CopyConstructor\t\t6)tree by Overloaded(=)\n7)Make Skew\t\t\t\t8)Deletion\n9)Check Equality\t\t\t10)Common Ancestors\n11)Path Sum\t\t\t\t12)Total Nodes\n13)Total leaf Nodes\t\t\t14)Search\n15)Nodes in the fullest level\t\t16)Update tree\n17)Check is BST\t\t\t\t18)Mirror tree\n0 to Exit\n";
		cin >> option;
		system("cls");
		switch (option)
		{
		case 0:
			break;
		case 1:
			cout << "Tree (Inorder): ";
			tree.inorderPrint();
			tree.PrintinIterative();
			break;
		case 2:
			cout << "\nTree (Post order): ";
			tree.postorderPrint();
			tree.PrintpostIterative();
			break;
		case 3:
			cout << "\nTree (Pre order): ";
			tree.preorderPrint();
			tree.PrintpreIterative();
			break;
		case 4:
			cout << "\nTree 1 by level order: ";
			tree.levelOrderPrint();
			break;
		case 5:
			//Initialized in Start
			cout << "Tree 3, made using copy constructor: ";
			tree3.preorderPrint();
			break;
		case 6:
			tree2 = tree;
			t2 = 1;
			cout << "Tree 2 using Overloaded(=):";
			tree2.preorderPrint();
			break;
		case 7:
			cout << "Tree after using makeSkew: ";
			tree.makeSkew();
			tree.preorderPrint();
			break;
		case 8:
			cout << "Enter Element you wish to delete from tree: ";
			cin >> data;
			tree.delete_recursive(data);
			cout << "Tree after deleting " << data << " :";
			tree.preorderPrint();
			break;
		case 9:
			if (t2)
				cout << "\nChecking Equality of tree 1 and 2 using == : " << (tree2 == tree);
			else
				cout << "first make tree 2\n";
			break;
		case 10:
			cout << "Enter 2 node of which u want the common Ancestors: ";
			cin >> data;
			n1->data = data;
			cin >> data;
			n2->data = data;
			cout << "\nCommon Ancestors ";
			tree.commonAncestors(n1, n2);
			break;
		case 11:
			cout << "\nPath Sum of tree 1: ";
			tree.pathSum(sum);
			for (int i = 0; i < sum.size(); i++)
				cout << sum.at(i) << " ";
			break;
		case 12:
			cout << "\nTotal Nodes of tree 1: " << tree.countNodes() << endl;
			break;
		case 13:
			cout << "\nTotal Leaf Nodes tree 1: " << tree.leafCount() << endl;
			break;
		case 14:
			cout << "\nEnter element which you wish to search: ";
			cin >> data;
			cout << "Search for" << data << " in tree 1: " << tree.search(data) << endl;
			break;
		case 15:
			cout << "\nNumber of nodes in the fullest level of the tree: " << tree.findWidth();
			break;
		case 16:
			int key1, key2;
			cout << "Enter element you wish to update: ";
			cin >> key1;
			cout << "Enter updated value: ";
			cin >> key2;
			cout << "\nAfter updating "<<key1<<" with "<<key2<<" in tree1: ";
			tree.updateKey(key1, key2);
			tree.preorderPrint();
			break;
		case 17:
			cout << "\nIs Tree 1 Bst? " << tree.isBst();
			break;
		case 18:
			tree.Mirror();
			cout << "\nTree 1 after mirror: ";
			tree.inorderPrint();
			break;
		}
		cout << "\nDo you wish to Run another program?\n 0 for No\n 1 for yes\n";
		cin >> option;
	}
	system("pause");
	return 0;
}