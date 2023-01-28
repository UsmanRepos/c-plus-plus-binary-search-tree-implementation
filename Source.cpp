#include<iostream>
using namespace std;

struct Node
{
	int key;
	Node *lptr, *rptr, *parent;
};
Node* Search_Node(Node* node, int data);

Node* successor_Node(Node* node, int key)
{
	Node *cc = NULL, *pp = NULL,  *tt = NULL;


	cc = Search_Node(node, key);
	tt = pp = cc;

	if (cc->rptr != NULL)
	{
		pp = cc->rptr;
		while (pp->lptr != NULL)
		{
			pp = pp->lptr;
		}
	}
	else
	{
		pp = cc->parent;
		while (pp != NULL)
		{
			if (cc->key >= pp->key)
			{
				cc = pp;
				pp = pp->parent;
			}
			else
			{
				break;
			}
		}
		if (pp == NULL)
		    pp = tt;
		
		

	}
	return pp;
}

Node* predecessor_Node(Node* node, int key)
{
	Node *cc = NULL, *pp = NULL, *tt = NULL;


	cc = Search_Node(node, key);
	tt = pp = cc;

	if (pp->lptr != NULL)
	{
		pp = pp->lptr;
		while (pp->rptr != NULL)
		{
			pp = pp->rptr;
		}
	}
	else
	{
		cc = cc->parent;
		while (cc != NULL )
		{
			if (pp->key < cc->key)
			{
				pp = cc;
				cc = cc->parent;
			}
			else
				break;
			
		}
		if (cc == NULL)
			pp = tt;



	}
	return pp;
}
Node* Insert_Node(Node* node,int key)
{
	if (node == NULL)
	{
		node = new Node;
		node->lptr = node->rptr = node ->parent = NULL;
		node->key = key;
	}
	else
	{
		if (key < node->key)
		{
			node->lptr = Insert_Node(node->lptr, key);
			node->lptr->parent = node;
		}
		else
		{
			node->rptr = Insert_Node(node->rptr, key);
			node->rptr->parent = node;
		}
	}
	return node;
}
Node* Search_Node(Node* node, int data)
{
	if (node == NULL)
		return NULL;
	if (node->key == data)
		return node;
	if (data < node->key)
		return Search_Node(node->lptr, data);
	else
		return Search_Node(node->rptr, data);
}
Node* Minimum_key(Node* node)
{
	if (node->lptr != NULL)
		Minimum_key(node->lptr);
	return node;
}
Node* Maximum_key(Node* node)
{
	if (node->rptr != NULL)
		Maximum_key(node->rptr);
	return node;
}
void Delete_Node(Node*& node, int data)
{
	Node* cc = NULL;
	cc = Search_Node(node, data);

	if (cc != NULL)
	{
		//case 1: Node to be deleted has no childern i.e Leaf Node
		if (cc->lptr == NULL && cc->rptr == NULL)
		{
			if (cc != node)
			{
				if (cc->parent->lptr == cc)
					cc->parent->lptr = NULL;
				else
					cc->parent->rptr = NULL;
			}
			else
				node = NULL;

			cout << "Delete Data: " << cc->key << endl;
			delete cc;
		}
		//case 2: Node to be Deleted has two children
		else if (cc->lptr && cc->rptr)
		{
			Node* successor = Minimum_key(cc->rptr);

			int value = successor->key;
			cc->key = value;

			//recursively delete successor. 
			// successor have at most one right child
			Delete_Node(node, value);
			

		}
		//case 3: Node to be deleted has only one child
		else
		{
			Node* child = NULL;

			if (cc->lptr != NULL)
				child = cc->lptr;
			else
				child = cc->rptr;

			if (cc != node)
			{
				if (cc == cc->parent->lptr)
					cc->parent->lptr = child;
				else
					cc->parent->rptr = child;
			}
			else
				node = child;

			cout << "Delete Data: " << cc->key << endl;
			delete cc;

		}
		
	}

	

}
void Travrse_preOrder(Node*node)//root Left right
{
	if (node != NULL)
	{
		cout << node->key << " ";
		Travrse_preOrder(node->lptr);

		Travrse_preOrder(node->rptr);
	}
		
}
void Travrse_postOrder(Node*node)//left right root
{
	if (node != NULL)
	{
		Travrse_postOrder(node->lptr);
		Travrse_postOrder(node->rptr);
		cout << node->key << " ";
	}
}
void Travrse_inOrder(Node*node)// left root right
{
	if (node != NULL)
	{
		Travrse_inOrder(node->lptr);
		cout << node->key << " ";
		Travrse_inOrder(node->rptr);
		
	}
}

int main()
{
	Node* root = NULL;
	int key;

	char  ch;
	while (true)
	{
		cout << "----------(MAIN MENU)-----------\n";
		cout << "1) Insertion \n";
		cout << "2) Searching \n";
		cout << "3) Minimum \n";
		cout << "4) Maximum \n";
		cout << "5) Deletion \n";
		cout << "6) Traversing \n";
		cout << "7) Exit \n\n";
		cout << "Enter Choice: ";
		cin >> ch;

		switch (ch)
		{
		case'1':
			cout << "Enter Key of Node: ";
			cin >> key;
			root = Insert_Node(root, key);
			break;
		case'5':
			cout << "Enter Key of Node You Want to Delete: ";
			cin >> key;
			Delete_Node(root, key);
			break;
		case'6':
			cout << "Travrse_inOrder: ";
			Travrse_inOrder(root);
			cout << endl;

			cout << "Travrse_preOrder: ";
			Travrse_preOrder(root);
			cout << endl;

			cout << "Travrse_postOrder: ";
			Travrse_postOrder(root);
			cout << endl;
			
			break;
		case'7':
			exit(-1);
		}
	}




	system("pause");
}