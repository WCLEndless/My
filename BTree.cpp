#if 0
#include<iostream>
using namespace std;

#define M 5
#define  MAX M - 1
#define MIN M/2
typedef char KeyType;

typedef struct {}Record;

typedef struct ElemType
{
	KeyType key;
	Record *recptr;
}ElemType;

typedef struct BNode
{
	int num;
	BNode *parent;
	ElemType data[M+1];
	BNode*sub[M+1];
}BNode,*BTree;

typedef struct Result
{
	bool tag;
	BNode*pnode;
	int index;
}Result;

BNode* BuyNode()
{
	BNode *node = new BNode();
	if (node == NULL)
		exit(-1);
	memset(node, 0, sizeof(BNode));
	return node;
}


Result FindValue(BNode*ptr, KeyType e)
{
	Result res = { false, NULL, -1 };
	while (ptr != NULL)
	{
		int i = ptr->num;
		ptr->data[0].key = e;
		while (ptr->data[i].key > e) --i;
		res.pnode = ptr;
		res.index = i;
		if (i != 0 && ptr->data[i].key == e)
		{
			res.tag = true;
			break;
		}
		else
			ptr = ptr->sub[i];
	}
	return res;
}
Result Findvalue_e(BNode *ptr, KeyType e)
{
	Result res = {false,NULL,-1};
	if (ptr == NULL)
		return res;
	int i = ptr->num;
	while (ptr->data[i].key > e) --i;
	res.index = i;
	res.pnode=ptr;
	if (i != 0 && ptr->data[i].key == e)
	{
		res.tag = true;
	}
	else if (ptr->sub[i] != NULL)//
	{
		res=FindValue(ptr->sub[i], e);
	}
	return res;
}
ElemType MoveItem(BNode*ptr, BNode *s, int pos)
{
	int tmp = ptr->num;
	for (int i = pos + 1, j = 0; i <= tmp; i++, j++)
	{
		s->data[j] = ptr->data[i];
		s->sub[j] = ptr->sub[i];
		if (ptr->sub[i] != NULL)
		{
			s->sub[j]->parent = s;
		}
	}
	s->parent = ptr->parent;
	s->num = ptr->num = MIN;
	return s->data[0];

}
BNode * MakeRoot(ElemType x, BNode *left, BNode *right)
{
	BNode *s = BuyNode();
	s->num = 1;
	s->data[1] = x;
	s->sub[0] = left;
	if (left != NULL)
		left->parent = s;
	s->sub[1] = right;
	if (right != NULL)
		right->parent = s;
	return s;
}
bool InsertItem(BNode*ptr, int pos, ElemType e, BNode*right);
BNode *Splice(BNode*ptr)
{
	BNode *s = BuyNode();
	ElemType e = MoveItem(ptr, s, MIN);
	
	if (ptr->parent == NULL)
	{
		return MakeRoot(e,ptr, s);
	}
	else
	{
		ptr = ptr->parent;
		int i = ptr->num;
		ptr->data[0] = e;//这句很关键，如果ptr->data[0]未设置就会和0位置比较还没有结果，插入位置就会出错
		while (ptr->data[i].key > s->data[0].key) --i;
		InsertItem(ptr, i + 1, s->data[0], s);
		if (ptr->num > MAX)
		{
			return Splice(ptr);
		}
		return NULL;
	}
}
bool InsertItem(BNode*ptr, int pos, ElemType e, BNode*right)//BNode&node
{

	for (int i = ptr->num; i >= pos; --i)
	{
		ptr->data[i + 1] = ptr->data[i];
		ptr->sub[i + 1] = ptr->sub[i];
	}
	//
	ptr->data[pos] = e;
	ptr->sub[pos] = right;
	if (right != NULL)
	{
		right->parent = ptr;
	}//
	ptr->num += 1;
	
	return true;
}
bool Insert(BTree *ptr, ElemType e)
{
	if (ptr == NULL)
		return false;
	if (*ptr == NULL)
	{
		*ptr = MakeRoot(e, NULL, NULL);
		return true;
	}
	Result res=FindValue(*ptr, e.key);
	if (res.pnode == NULL || res.tag) return false;
	InsertItem(res.pnode, res.index+1, e, NULL);
	if (res.pnode->num > MAX)
	{
		BNode*p = Splice(res.pnode);
		if (p != NULL)
		{
			*ptr = p;
		}
	}
	return true;
}

void InOder(BNode*root)
{
	if (root != NULL)
	{
		InOder(root->sub[0]);
		for (int i = 1; i <= root->num; i++)
		{
			cout << root->data[i].key;
			InOder(root->sub[i]);
		}
	}
}
BNode *FindPre(BNode*ptr)
{
	while (ptr!=NULL&&ptr->sub[ptr->num] != NULL)
	{
		ptr = ptr->sub[ptr->num];
	}
	return ptr;
}
BNode *FindNext(BNode*ptr)
{
	while (ptr != NULL&&ptr->sub[0] != NULL)
	{
		ptr = ptr->sub[0];
	}
	return ptr;
}
void DelLeafItem(BNode *ptr, int pos)
{
	for (int i = pos; i < ptr->num; i++)
	{
		ptr->data[i] = ptr->data[i + 1];
		ptr->sub[i] = ptr->sub[i + 1];
	}
	ptr->num -= 1;
}
void RightRotateLeaf(BNode *leftbro, BNode*ptr, BNode *parent, int pos)
{
	ptr->data[0] = parent->data[pos];
	for (int i = ptr->num; i >= 0; i--)
	{
		ptr->data[i + 1] = ptr->data[i];
		ptr->sub[i + 1] = ptr->sub[i];
	}
	ptr->num += 1;
	ptr->sub[0] = leftbro->sub[leftbro->num];
	if (ptr->sub[0] != NULL)//
	{
		ptr->sub[0]->parent = ptr;
	}
	parent->data[pos] = leftbro->data[leftbro->num];
	leftbro->num -= 1;
}
void LeftRotateLeaf(BNode *rightbro,BNode *ptr,BNode *parent,int pos)
{
	ptr ->data[ptr->num+1] = parent->data[pos + 1];
	ptr->sub[ptr->num + 1] = rightbro->sub[0];
	if (ptr->sub[ptr->num+1]!=NULL)
	{
		ptr->sub[ptr->num + 1]->parent = ptr;
	}
	ptr->num += 1;
	parent->data[pos + 1] = rightbro->data[1];

	for (int i =0; i < rightbro->num; i++)
	{
		rightbro->data[i] = rightbro->data[i + 1];
		rightbro->sub[i] = rightbro->sub[i + 1];
	}
	rightbro->num -= 1;

}
void LeftMerge(BNode*leftbro, BNode*ptr, BNode*parent, int pos)
{
	ptr->data[0] = parent->data[pos];
	for (int i = 0,j=leftbro->num+1; i <= ptr->num; i++,j++)
	{
		leftbro->data[j] = ptr->data[i];
		leftbro->sub[j] = ptr->sub[i];
		if (leftbro->sub[j] != NULL)
		{
			leftbro->sub[j]->parent = leftbro;
		}
	}
	leftbro->num = leftbro->num + ptr->num + 1;
	free(ptr);
	DelLeafItem(parent, pos);

}
void RightMerge(BNode *ptr, BNode *rightbro, BNode *parent, int pos)
{
	 LeftMerge(ptr, rightbro, parent, pos+1);
}
BNode *AdjusLeaf(BNode*ptr)
{
	BNode*parent = ptr->parent;
	int pos = 0;
	while (parent->sub[pos] != ptr) ++pos;

	BNode*leftbro = pos-1<0?NULL:parent->sub[pos-1];
	BNode*rightbro = pos+1>=MAX?NULL:parent->sub[pos+1];

	if (leftbro!=NULL&&leftbro->num>MIN)
	{
		RightRotateLeaf(leftbro,ptr,parent,pos);
	}
	else if (rightbro!=NULL&&rightbro->num>MIN)
	{
		LeftRotateLeaf(rightbro, ptr,parent, pos);
	}
	else if(leftbro!=NULL)
	{
		LeftMerge(leftbro, ptr, parent, pos);
		ptr = leftbro;
	}
	else if (rightbro != NULL)
	{
		 RightMerge(ptr, rightbro, parent, pos);
		// ptr = rightbro;
	}
	if (parent->parent != NULL&&parent->num < MIN)
	{
		return AdjusLeaf(parent);
	}
	if (parent->parent == NULL&&parent->num <= 0)
	{
		free(parent);
		ptr->parent = NULL;
		return ptr;
	}
	return NULL;

}
void ReMove(BNode*&root, KeyType e)
{
	if (root == NULL)
		return;
	Result res = FindValue(root, e);
	if (res.pnode == NULL || res.tag==false) return;

	BNode *ptr = res.pnode;
	int pos = res.index;
	BNode*pre = FindPre(ptr->sub[pos-1]);
	BNode*next = FindNext(ptr->sub[pos]);
	if (pre != NULL&&pre->num > MIN)
	{
		ptr->data[pos] = pre->data[pre->num];
		ptr = pre;
		pos = pre->num;
	}
	else if (next != NULL&&next->num > MIN)
	{
		ptr->data[pos] = next->data[1];
		ptr = next;
		pos = 1;
	}
	else if (pre != NULL)
	{
		ptr->data[pos] = pre->data[pre->num];
		ptr = pre;
		pos = pre->num;
	}
	else if (next != NULL)
	{
		ptr->data[pos] = next->data[1];
		ptr = next;
		pos = 1;
	}
	DelLeafItem(ptr, pos);//
	if (ptr->parent != NULL&&ptr->num < MIN)
	{
		BNode*newroot = AdjusLeaf(ptr);
		if (newroot != NULL)
		{
			root = newroot;
		}
	}
	else if (ptr->parent == NULL&&ptr->num <= 0)
	{
		free(root);
		root = NULL;
	}
}


int main()
{
	KeyType ar[] = { "1qwertyuiop234lkjhgfdsa5678mnbvcxz90" };
	int n = sizeof(ar) / sizeof(ar[0]) - 1;
	BTree root = NULL;
	ElemType item;
	for (int i = 0; i<n; ++i)
	{
		item.key = ar[i];
		item.recptr = NULL;
		cout << Insert(&root, item);
	}
	cout << endl;
	InOder(root);
	KeyType kx;
	while (cin >> kx, kx != '#')
	{
		ReMove(root, kx);
		InOder(root);
		cout << endl;
	}

	return 0;
}
#endif 

//B+树的设计与其实现
#include<iostream>
using namespace std;
#define M 5
#define LeafMAX M
#define LeafMIN (M/2+1)
#define BrchMAX (M-1)
#define BrchMIN (M/2)
typedef char KeyType;
typedef struct {} Record;
typedef enum {Leaf=0,Brch=1}NodeType;
typedef struct BNode
{
	NodeType type;
	BNode *parent;
	int num;
	KeyType  key[M+1];
	union
	{
		struct
		{
			Record *rec[M+1];
			BNode *pre, *next;//每个叶子节点浪费八个字节，但是比B树来说浪费更少
		};
		BNode *sub[M + 1];
	};
}BNode;
typedef struct 
{
	BNode*pnode;
	int index;
	bool tag;
}Result;

struct BTree
{
	BNode *root;
	BNode *first;
};

BNode *BuyNode()
{
	BNode*node = (BNode*)malloc(sizeof(BNode));
	if (node == NULL) exit(-1);
	memset(node, 0, sizeof(BNode));
	return node;
}
BNode *BuyLeafNode()
{
	BNode *node = BuyNode();
	node->type = Leaf;
	return node;
}
BNode * BuyBrchNode() 
{
	BNode*p = BuyNode();
	p->type = Brch;
	return p;
}
Result FindFirst(BNode *ptr, KeyType k)
{
	Result res = { NULL, -1, false };
	while (ptr != NULL&&ptr->next != NULL&&ptr->key[ptr->num-1]<k)
	{
		ptr = ptr->next;
	}
	if (ptr == NULL) return res;
	int i = ptr->num-1;
	while (ptr->key[i] > k) --i;
	if (i < 0 && ptr->pre != NULL)
	{
		res.pnode = ptr->pre;
		res.index = ptr->pre->num-1;
	}

	res.pnode = ptr;
	res.index = i;
	if (i>=0&&ptr->key[i] == k)
	{
		res.tag = true;
	}
	return res;
}
Result FindRoot(BNode *ptr, KeyType k)
{
	Result res = { NULL, -1, false };
	while (ptr != NULL&&ptr->type == Brch)
	{
		int i = ptr->num;
		ptr->key[0] = k;
		while (ptr->key[i] > k) --i;
		ptr = ptr->sub[i];
	}
	if (ptr == NULL)
		return res;
	int pos = ptr->num-1;
	while (ptr->key[pos] > k) --pos;
	if (pos < 0&&ptr->pre!=NULL)
	{
		res.pnode = ptr->pre;
		res.index = ptr->pre->num-1;
	}
	res.pnode = ptr;
	res.index = pos;
	if (pos >= 0 && ptr->key[pos] == k)
	{
		res.tag = true;
	}

	return res;
}

void InsertLeafItem(BNode *ptr,int pos , KeyType k, Record*rec)
{
	for (int i = ptr->num-1; i >=pos; i--)
	{
		ptr->key[i + 1] = ptr->key[i];
		ptr->rec[i + 1] = ptr->rec[i];
	}
	ptr->key[pos] = k;
	ptr->rec[pos] = rec;
	ptr->num += 1;
}
bool InsertBrchItem(BNode*ptr, int pos, KeyType e, BNode*right)//BNode&node
{

	for (int i = ptr->num; i >= pos; --i)
	{
		ptr->key[i + 1] = ptr->key[i];
		ptr->sub[i + 1] = ptr->sub[i];
	}
	//
	ptr->key[pos] = e;
	ptr->sub[pos] = right;
	if (right != NULL)
	{
		right->parent = ptr;
	}//
	ptr->num += 1;
	return true;
}

BNode *MakeRoot(BNode *left, BNode *right, KeyType k)
{
	BNode *node = BuyBrchNode();
	node->key[1] = k;
	node->num = 1;
	node->sub[0] = left;
	node->sub[1] = right;
	left->parent = right->parent = node;
	return node;
}

KeyType MoveLeafItem(BNode*ptr, BNode*s, int pos)
{
	for (int i = pos, j = 0; i < ptr->num; i++, j++)
	{
		s->key[j] = ptr->key[i];
		s->rec[j] = ptr->rec[i];
	}
	s->num = ptr->num = LeafMIN;
	s->next = ptr->next;
	s->pre = ptr;
	ptr->next = s;
	if (s->next != NULL)
	{
		s->next->pre = s;
	}
	return s->key[0];
}
KeyType MoveBrchItem(BNode*ptr, BNode *s, int pos)
{
	int tmp = ptr->num;
	for (int i = pos + 1, j = 0; i <= tmp; i++, j++)
	{
		s->key[j] = ptr->key[i];
		s->sub[j] = ptr->sub[i];
		if (ptr->sub[i] != NULL)
		{
			s->sub[j]->parent = s;
		}
	}
	s->parent = ptr->parent;
	s->num = ptr->num = BrchMIN;
	return s->key[0];

}

BNode *BrchSplice(BNode*ptr)
{
	BNode *s = BuyBrchNode();//必须购买分支的节点
	KeyType e = MoveBrchItem(ptr, s, BrchMIN);//必须做分支的移动，主要区别在于孩子的维护
	if (ptr->parent == NULL)
	{
		return MakeRoot( ptr, s,e);
	}
	else
	{
		ptr = ptr->parent;
		int i = ptr->num;
		ptr->key[0] = e;//这句很关键，如果ptr->data[0]未设置就会和0位置比较还没有结果，插入位置就会出错
		while (ptr->key[i] > s->key[0]) --i;
		InsertBrchItem(ptr, i + 1, s->key[0], s);//
		if (ptr->num > BrchMAX)
		{
			return BrchSplice(ptr);
		}
		return NULL;
	}
}
BNode *Splice(BNode *ptr)//叶子结点的分裂
{
	BNode *s = BuyLeafNode();
	KeyType k=MoveLeafItem(ptr, s, LeafMIN);
	if (ptr->parent == NULL)
	{
		return MakeRoot(ptr, s, k);
	}

	BNode *parent = ptr->parent;
	int pos = parent->num;
	parent->key[0] = k;
	while (parent->key[pos] > k) --pos;
	InsertBrchItem(parent, pos+1, k, s);
	if (parent->num > BrchMAX)
		return BrchSplice(parent);//调用分支的分裂
	return NULL;
}
void Insert(BTree*root, KeyType k,Record*rec)
{
	if (root == NULL) return;
	if (root->root == NULL)
	{
		BNode *node = BuyLeafNode();
		node->key[0] = k;
		node->rec[0] = rec;
		root->root = node;
		root->first = node;
		root->root->num = 1;
		return;
	}
	Result res=FindRoot(root->root, k);
	//Result res=FindFirst(root->first, k);
	if (res.pnode == NULL || res.tag)	return;

	BNode *ptr = res.pnode;
	int pos = res.index;
	InsertLeafItem(ptr, pos+1, k, rec);
	if (ptr->num > LeafMAX)
	{
		BNode*newroot = Splice(ptr);
		if (newroot != NULL)
		{
			root->root = newroot;
		}
	}
}
void Order(BTree *ptr)
{
	if ( ptr == NULL || ptr->root == NULL) return;
	BNode *p = ptr->first;
	while (p != NULL)
	{
		for (int i = 0; i < p->num; i++)
		{
			cout << p->key[i];
		}
		p = p->next;
	}
}
Result FindBrchValue(BNode*ptr, KeyType e)//找分支的元素
{
	Result res = { NULL, -1,false };
	while (ptr != NULL&&ptr->type==Brch)
	{
		int i = ptr->num;
		ptr->key[0] = e;
		while (ptr->key[i] > e) --i;
		res.pnode = ptr;
		res.index = i;
		if (i != 0 && ptr->key[i] == e)
		{
			res.tag = true;
			break;
		}
		else
			ptr = ptr->sub[i];
	}
	return res;
}
BNode *FindPre(BNode*ptr)
{
	while (ptr != NULL && ptr->type==Brch && ptr->sub[ptr->num] != NULL)
	{
		ptr = ptr->sub[ptr->num];
	}
	return ptr;
}
BNode *FindNext(BNode*ptr)
{
	while (ptr != NULL&&ptr->type==Brch&&ptr->sub[0] != NULL)
	{
		ptr = ptr->sub[0];
	}
	return ptr;
}
void DelLeafItem(BNode *ptr, int pos)
{
	for (int i = pos; i < ptr->num-1; i++)
	{
		ptr->key[i] = ptr->key[i + 1];
		ptr->rec[i] = ptr->rec[i + 1];
	}
	ptr->num -= 1;
}
void RightRotateLeaf(BNode *leftbro, BNode*ptr, BNode *parent, int pos)
{
	InsertLeafItem(ptr, 0, leftbro->key[leftbro->num-1], leftbro->rec[leftbro->num-1]);
	parent->key[pos] = leftbro->key[leftbro->num - 1];
	DelLeafItem(leftbro, leftbro->num - 1);
}
void LeftRotateLeaf(BNode *rightbro, BNode *ptr, BNode *parent, int pos)
{
	InsertLeafItem(ptr, ptr->num, rightbro->key[0], rightbro->rec[0]);
	parent->key[pos + 1] = rightbro->key[0];
	DelLeafItem(rightbro, 0);
}
void LeftMerge(BNode*leftbro, BNode*ptr, BNode*parent, int pos)
{
	for (int i = leftbro->num, j = 0; j < ptr->num; i++, j++)
	{
		InsertLeafItem(leftbro, i, ptr->key[j], ptr->rec[j]);
	}
	for (int i = pos; i < parent->num; i++)
	{
		parent->key[i] = parent->key[i + 1];
		parent->sub[i] = parent->sub[i + 1];
	}
	parent->num -= 1;
	leftbro->next = ptr->next;
	if (ptr->next != NULL)
	{
		leftbro->next->pre = leftbro;
	}
	free(ptr);
}
void RightMerge(BNode *ptr, BNode *rightbro, BNode *parent, int pos)
{
	LeftMerge(ptr, rightbro, parent, pos + 1);
}
//这部分是分支的删除的部分，跟b树的删除完全一样
void DelBrchItem(BNode *ptr, int pos)
{
	for (int i = pos; i < ptr->num; i++)
	{
		ptr->key[i] = ptr->key[i + 1];
		ptr->sub[i] = ptr->sub[i + 1];
	}
	ptr->num -= 1;
}
void RightRotateBrch(BNode *leftbro, BNode*ptr, BNode *parent, int pos)
{
	ptr->key[0] = parent->key[pos];
	for (int i = ptr->num; i >= 0; i--)
	{
		ptr->key[i + 1] = ptr->key[i];
		ptr->sub[i + 1] = ptr->sub[i];
	}
	ptr->num += 1;
	ptr->sub[0] = leftbro->sub[leftbro->num];
	if (ptr->sub[0] != NULL)//
	{
		ptr->sub[0]->parent = ptr;
	}
	parent->key[pos] = leftbro->key[leftbro->num];
	leftbro->num -= 1;
}
void LeftRotateBrch(BNode *rightbro, BNode *ptr, BNode *parent, int pos)
{
	ptr->key[ptr->num + 1] = parent->key[pos + 1];
	ptr->sub[ptr->num + 1] = rightbro->sub[0];
	if (ptr->sub[ptr->num + 1] != NULL)
	{
		ptr->sub[ptr->num + 1]->parent = ptr;
	}
	ptr->num += 1;
	parent->key[pos + 1] = rightbro->key[1];

	for (int i = 0; i < rightbro->num; i++)
	{
		rightbro->key[i] = rightbro->key[i + 1];
		rightbro->sub[i] = rightbro->sub[i + 1];
	}
	rightbro->num -= 1;

}
void LeftMergeBrch(BNode*leftbro, BNode*ptr, BNode*parent, int pos)
{
	ptr->key[0] = parent->key[pos];
	for (int i = 0, j = leftbro->num + 1; i <= ptr->num; i++, j++)
	{
		leftbro->key[j] = ptr->key[i];
		leftbro->sub[j] = ptr->sub[i];
		if (leftbro->sub[j] != NULL)
		{
			leftbro->sub[j]->parent = leftbro;
		}
	}
	leftbro->num = leftbro->num + ptr->num + 1;
	free(ptr);
	DelBrchItem(parent, pos);
}
void RightMergeBrch(BNode *ptr, BNode *rightbro, BNode *parent, int pos)
{
	LeftMergeBrch(ptr, rightbro, parent, pos + 1);
}
BNode *AdjusBrch(BNode*ptr)
{
	BNode*parent = ptr->parent;
	int pos = 0;
	while (parent->sub[pos] != ptr) ++pos;

	BNode*leftbro = pos - 1<0 ? NULL : parent->sub[pos - 1];
	BNode*rightbro = pos + 1 >= BrchMAX ? NULL : parent->sub[pos + 1];

	if (leftbro != NULL&&leftbro->num>BrchMIN)
	{
		RightRotateBrch(leftbro, ptr, parent, pos);
	}
	else if (rightbro != NULL&&rightbro->num>BrchMIN)
	{
		LeftRotateBrch(rightbro, ptr, parent, pos);
	}
	else if (leftbro != NULL)
	{
		LeftMergeBrch(leftbro, ptr, parent, pos);
		ptr = leftbro;
	}
	else if (rightbro != NULL)
	{
		RightMergeBrch(ptr, rightbro, parent, pos);
		// ptr = rightbro;
	}
	if (parent->parent != NULL&&parent->num < BrchMIN)
	{
		return AdjusBrch(parent);
	}
	if (parent->parent == NULL&&parent->num <= 0)
	{
		free(parent);
		ptr->parent = NULL;
		return ptr;
	}
	return NULL;
}
/////////////////////////
BNode *AdjusLeaf(BNode*ptr)
{
	BNode*parent = ptr->parent;
	int pos = 0;
	while (parent->sub[pos] != ptr) ++pos;

	BNode*leftbro = pos - 1<0 ? NULL : parent->sub[pos - 1];
	BNode*rightbro = pos + 1 >= LeafMAX ? NULL : parent->sub[pos + 1];

	if (leftbro != NULL&&leftbro->num>LeafMIN)
	{
		RightRotateLeaf(leftbro, ptr, parent, pos);
	}
	else if (rightbro != NULL&&rightbro->num>LeafMIN)
	{
		LeftRotateLeaf(rightbro, ptr, parent, pos);
	}
	else if (leftbro != NULL)
	{
		LeftMerge(leftbro, ptr, parent, pos);
		ptr = leftbro;
	}
	else if (rightbro != NULL)
	{
		RightMerge(ptr, rightbro, parent, pos);
		// ptr = rightbro;
	}
	if (parent->parent != NULL&&parent->num < BrchMIN)
	{
		return AdjusBrch(parent);
	}
	if (parent->parent == NULL&&parent->num <= 0)
	{
		free(parent);
		ptr->parent = NULL;
		return ptr;
	}
	return NULL;

}
//B+树的删除
void ReMove(BTree *ptr, KeyType k)
{
	if (ptr == NULL || ptr->root == NULL) return;
	Result res_leaf = FindFirst(ptr->first, k);
	Result res_brch = FindBrchValue(ptr->root, k);
	if (res_leaf.pnode == NULL || res_leaf.tag == false) return;
	BNode *pb = NULL;
	int posb = -1;
	if (res_brch.pnode != NULL&&res_brch.tag)
	{
		pb = res_brch.pnode;
		posb = res_brch.index;
		BNode*pre = FindPre(res_brch.pnode->sub[res_brch.index - 1]);//////////////
		BNode*next = FindNext(res_brch.pnode->sub[res_brch.index]);
		if (pre != NULL&&pre->num > LeafMIN)
		{
			pb->key[posb] = pre->key[pre->num - 1];
			next->key[0] = pre->key[pre->num - 1];
			next->rec[0] = pre->rec[pre->num - 1];
			pb = pre;
			posb = pre->num - 1;
		}
		else if (next != NULL&&next->num > LeafMIN)
		{
			pb->key[posb] = next->key[1];
			pb = next;
			posb = 0;
		}
		else if (pre != NULL)
		{
			pb->key[posb] = pre->key[pre->num - 1];
			next->key[0] = pre->key[pre->num - 1];
			next->rec[0] = pre->rec[pre->num - 1];
			pb = pre;
			posb = pre->num - 1;
		}
		else if (next != NULL)
		{
			pb->key[posb] = next->key[1];
			pb = next;
			posb = 0;
		}
	}
	else
	{
		pb = res_leaf.pnode;
		posb = res_leaf.index;
	}
	DelLeafItem(pb, posb);//
	if (pb->parent != NULL&&pb->num < LeafMIN)
	{
		BNode*newroot = AdjusLeaf(pb);
		if (newroot != NULL)
		{
			ptr->root = newroot;
		}
	}
	else if (pb->parent == NULL&&pb->num <= 0)
	{
		free(ptr->root);
		ptr->root = NULL;
		ptr->first = NULL;
	}
}
int main()
{
	BTree root;
	root.root = NULL;
	root.first = NULL;
	Record *rec = NULL;

	KeyType ar[] = { "02345678910zxcvbnmasdfghjklqwertyuiop" };
	int n = sizeof(ar) / sizeof(ar[0]) - 1;

	for (int i = 0; i<n; ++i)
	{
		Insert(&root,ar[i],rec);
		cout<<"Order:";
		Order(&root);
		cout << endl;
	}
	KeyType kx;
	while (cin >> kx, kx != '#')
	{
		ReMove(&root, kx);
		cout << "remove:";
		Order(&root);
		cout << endl;
	}
	return 0;
}