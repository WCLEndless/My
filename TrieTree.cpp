#include<iostream>
using namespace std;
#define MAXLINK 27
#define MAXKEY 25
typedef enum{ BRCH = 0, LEAF = 1 }NodeType;
typedef struct
{
	char key[MAXLINK];
	int len;
}Keytype;
typedef struct {}Record;
typedef struct 
{
	Keytype key;
	Record *rec;
}ElemType;
struct TrieNode;
typedef struct
{
	TrieNode *link[MAXLINK];
}BrchType;
typedef struct
{
	NodeType utype;
	union
	{
		ElemType elem;
		BrchType brch;
	};
};

class TrieTree
{
private:
	TrieNode *root;
	static TrieNode *Buynode()
	{
		TrieNode *s = (TrieNode *)malloc(sizeof(TrieNode));
		if (s == NULL)exit(-1);
		memset(s, 0, sizeof(TrieNode));
		return s;
	}
	static TrieNode*Buyleafnode(ElemType e)
	{
		TrieNode *s = Buynode();
		s->utype = LEAF;
		s->elem = e;
		return s;
	}
	static int FinfIndex(Keytype key, int pos)
	{
		int index = 0;
		if (pos < key.len)
		{
			index = key.key[pos] - 'a' + 1;
		}
		return index;
	}
	static TrieNode *Buybrchnode(TrieNode *ptr,int pos)
	{
		TrieNode *s = Buynode();
		s->utype = BRCH;
		int index = FindIndex(ptr->elem.key,pos);
		s->brch.link[index] = ptr;
		return s;
	}
	static void Insert(TrieNode *&ptr, ElemType &e, int pos)
	{
		if (ptr == NULL)
		{
			TrieNode*s = Buyleafnode(e);
			s->elem = e;
			ptr = s;
		}
		else if (ptr->utype == LEAF)
		{
			TrieNode *s = Buybrchnode();
			
			int index = FindIndex(e,pos);

		}
	}
public:
	TrieTree() :root(NULL){}
	~TrieTree(){}
	void Insert(const ElemType &e)
	{
		Insert(root, e, 0);
	}
};
