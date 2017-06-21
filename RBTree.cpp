#include<iostream>
using namespace std;

typedef int KeyType;
typedef enum{RED=0,BLACK=1}Color;
typedef struct _RBNode
{
	_RBNode *parent;
	_RBNode *leftchild;
	_RBNode *rightchild;
	KeyType key;
	Color color;
}RBNode;
class RBTree
{
public:
	RBTree() :size(0)
	{
		Init();
	}
	~RBTree()
	{
		if (refnil != 0)
		{
			Freenode(root());
		}
		free(head);
		free(nil);
	}
	void Insert(KeyType &kx)
	{
		RBNode*_X = head;
		RBNode*_Y = head->parent;
		while (_Y != nil&&_Y->key!=kx)
		{
			_X = _Y;
			if (_Y->key < kx)
				_Y = _Y->rightchild;
			else
				_Y = _Y->leftchild;
		}
		if (_Y != nil&&_Y->key == kx)
			return;
		Insert(_X, _Y, kx);
		refnil += 1;
	}
	void Inoder()
	{
		Inoder(head->parent);
		cout << endl;
	}
private:
	void Inoder(RBNode*p)
	{
		if (p == nil)return;
		Inoder(p->leftchild);
		cout << p->color<<" ";
		cout << p->key << " " << endl;;

		Inoder(p->rightchild);
	}
	RBNode *Buynode()
	{
		RBNode*node = (RBNode*)malloc(sizeof(RBNode));
		if (node == NULL)exit(-1);
		memset(node, 0, sizeof(RBNode));
		return node;
	}
	void Freenode(RBNode *node)
	{
		if (node ==nil)
			return;
		Freenode(node->leftchild);
		Freenode(node->rightchild);
		free(node);
	}
	RBNode *root()
	{
		if (head== NULL)
			return NULL;
		return head->parent;
	}
	void Init()
	{
		head = Buynode();
		nil = Buynode();
		nil->color = BLACK;

		head->color = RED;
		head->parent = head->leftchild = head->rightchild = nil;
	}
	void lrotate(RBNode*node)
	{
		RBNode*tmp = node->rightchild;
		tmp->parent = node->parent;
		node->rightchild = tmp->leftchild;
		if (tmp->leftchild != nil)
		{
			node->rightchild->parent = node;
		}
		tmp->leftchild = node;
		if (node == root())
		{
			head->parent = tmp;
		}
		else
		{
			if (node->parent->leftchild == node)
			{
				node->parent->leftchild = tmp;
			}
			else
				node->parent->rightchild = tmp;
		}
		node->parent = tmp;
	}
	void rrotate(RBNode*node)
	{
		RBNode*tmp = node->leftchild;
		tmp->parent = node->parent;
		node->leftchild = tmp->rightchild;
		if (tmp->rightchild != nil)
		{
			node->leftchild->parent = node;
		}
		tmp->rightchild = node;
		//node->parent = tmp;
		if (node == root())
		{
			head->parent = tmp;
		}
		else
		{
			if (node->parent->leftchild == node)
				node->parent->leftchild = tmp;
			else
				node->parent->rightchild = tmp;
		}
		node->parent = tmp;
	}
	void Insert(RBNode *_X, RBNode *_Y, KeyType &kx)
	{
		RBNode *node = Buynode();
		node->color = RED;
		node->key = kx;
		node->leftchild = node->rightchild = nil;
		if (_X == head)
		{
			_X->parent = node;
			_X->leftchild = _X->rightchild = node;
		}
		else
		{
			if (_X->key > node->key)//
			{
				_X->leftchild = node;
				if (_X==head->leftchild)//维护head的指向的最小值
					head->leftchild = node;
			}
			else
			{
				_X->rightchild = node;
				if (_X == head->rightchild)//维护head的指向为最大值
					head->rightchild = node;
			}
		}
		node->parent = _X;
		_X = node;
		for (; _X != root() && _X->parent->color == RED;)
		{
			if (_X->parent->parent->leftchild == _X->parent)
			{
				_Y = _X->parent->parent->rightchild;
				if (_Y->color == RED)
				{
					_X->parent->color = _Y->color = BLACK;
					_Y->parent->color = RED;
					_X = _X->parent->parent;
				}
				else
				{
					if (_X->parent->rightchild == _X)
					{
						_X = _X->parent;
						lrotate(_X);
					}
					_X->parent->color = BLACK;
					_X->parent->parent->color = RED;
					rrotate(_X->parent->parent);
				}
			}
			else
			{
				_Y = _X->parent->parent->leftchild;
				if (_Y->color == RED)
				{
					_Y->color = _X->parent->color = BLACK;
					_Y->parent->color = RED;
					_X = _X->parent->parent;
				}
				else
				{
					if (_X->parent->leftchild == _X)
					{
						_X = _X->parent;
						rrotate(_X);
					}
					_X->parent->color = BLACK;
					_X->parent->parent->color = RED;
					lrotate(_X->parent->parent);
				}
			}
		}
		root()->color = BLACK;
	}
private:
	RBNode*head;
	RBNode*nil;
	int refnil;
	int size;
};
int main()
{
	RBTree t;
	int ar[] = {101,12,23,18,10,34,56,78,90,100,11};
	int len = sizeof(ar) / sizeof(ar[0]);
	for (int i = 0; i < len; i++)
	{
		t.Insert(ar[i]);
	}
	t.Inoder();
	return 0;
}
