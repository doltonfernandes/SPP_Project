#include<bits/stdc++.h>
#include<stdint.h>

using namespace std;

struct Slice{
	uint8_t size;
	char * data;
};

class Node
{
	public:
	Slice key,value;
	Node *left,*right;
	int height,cnt;
};

Node *globalroot = NULL;

int comp(Slice &a,Slice &b)
{
	int tmp = strncmp(a.data,b.data,min(a.size,b.size));
	if(tmp == 0)
	{
		if(a.size > b.size)
		{
			return (1);
		}
		else if(a.size == b.size)
		{
			return (0);
		}
		else
		{
			return (-1);
		}
	}
	else
		return (tmp);
}

inline int height(Node *N)
{
	if(N == NULL)
		return (0);
	return (N->height);
}

inline int count(Node *N)
{
	if(N == NULL)
		return (0);
	return (N->cnt);
}

Node* newNode(Slice key, Slice value)
{
	Node* node = new Node();
	node->key = key;
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	node->cnt = 1;
	return(node);
}

Node *rightRotate(Node *y)
{
	Node *x = y->left;
	Node *T2 = x->right;
	register int cnt2 = count(x);
	register int cnt3 = count(T2);
	y->cnt += (cnt3 - cnt2);
	x->cnt += (y->cnt - cnt3);
	x->right = y;
	y->left = T2;
	y->height = max(height(y->left),
					height(y->right)) + 1;
	x->height = max(height(x->left),
					height(x->right)) + 1;
	return x;
}

Node *leftRotate(Node *x)
{
	Node *y = x->right;
	Node *T2 = y->left;
	register int cnt1 = count(y);
	register int cnt3 = count(T2);
	x->cnt += (cnt3 - cnt1);
	y->cnt += (x->cnt - cnt3);
	y->left = x;
	x->right = T2;
	x->height = max(height(x->left),
					height(x->right)) + 1;
	y->height = max(height(y->left),
					height(y->right)) + 1;
	return y;
}

inline int getBalance(Node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

void print_it(Slice k)
{
	for(int i=0;i<k.size;i++)
	{
		cout<<k.data[i];
	}
	cout<<"\n";
}

Node* insert(Node* node, Slice key, Slice value)
{
	if (node == NULL)
		return(newNode(key,value));
	register int tmpvar = comp(key,node->key);
	if (tmpvar<0)
		node->left = insert(node->left, key, value);
	else if (tmpvar>0)
		node->right = insert(node->right, key, value);
	else
	{
		node->value = value;
		return node;
	}

	node -> cnt = count(node->left) + count(node->right) + 1;

	node->height = 1 + max(height(node->left),
						height(node->right));

	int balance = getBalance(node);

	if (balance > 1 && comp(key,node->left->key)<0)
		return rightRotate(node);

	if (balance < -1 && comp(key,node->right->key)>0)
		return leftRotate(node);

	if (balance > 1 && comp(key,node->left->key)>0)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && comp(key,node->right->key)<0)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

inline Node * minValueNode(Node* node)
{
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return (current);
}

Node* deleteNode(Node* root, Slice key)
{
	if (root == NULL)
		return root;
	register int tmpvar = comp(key,root->key);
	if ( tmpvar<0 )
		root->left = deleteNode(root->left, key);
	else if( tmpvar>0)
		root->right = deleteNode(root->right, key);
	else
	{
		if( (root->left == NULL) ||
			(root->right == NULL) )
		{
			Node *temp = root->left ?
						root->left :
						root->right;
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
			*root = *temp;
			free(temp);
		}
		else
		{
			Node* temp = minValueNode(root->right);
			root->key = temp->key;
            root->value = temp->value;
			root->right = deleteNode(root->right,
									temp->key);
		}
	}

	if(root!=NULL)
	root->cnt = count(root->left) + count(root->right) + 1;

	if (root == NULL)
	return root;

	root->height = 1 + max(height(root->left),
						height(root->right));
	int balance = getBalance(root);

	if (balance > 1 &&
		getBalance(root->left) >= 0)
		return rightRotate(root);

	if (balance > 1 &&
		getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 &&
		getBalance(root->right) <= 0)
		return leftRotate(root);

	if (balance < -1 &&
		getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

Node* findNode(Node* root, Slice key)
{
	Node* tmproot = root;
	int tmpvar;
	while(1)
	{
		if(tmproot==NULL)
		{
			return tmproot;
		}
		tmpvar = comp(key,tmproot->key);
		if ( tmpvar<0 )
			tmproot = tmproot->left;
		else if( tmpvar>0 )
			tmproot = tmproot->right;
		else
			return (tmproot);
	}
}

void preOrder(Node *root)
{
	if(root != NULL)
	{
		preOrder(root->left);
		cout<<"key: ";
		print_it(root->key);
		cout<<"value: ";
		print_it(root->value);
		preOrder(root->right);
	}
}

inline Node *getnth(Node *root,int index)
{
	if(root == NULL)
	{
		return root;
	}
	if(count(root->left) == index)
	{
		return root;
	}
	if(count(root->left) < index)
	{
		return getnth(root->right,index - count(root->left) - 1);
	}
	else
	{
		return getnth(root->left,index);
	}
}

pthread_mutex_t lock1;

class kvStore{

public:

	kvStore(uint64_t max_entries){};

	bool get(Slice &key,Slice &value){
		pthread_mutex_lock(&lock1);
		Node* ret = findNode(globalroot,key);
		pthread_mutex_unlock(&lock1);
		if(ret==NULL)
			return false;
		else
		{
			value = ret->value;
			return true;
		}
	}

	bool put(Slice &key, Slice &value){
		pthread_mutex_lock(&lock1);
		Node *ret = findNode(globalroot,key);
		globalroot = insert(globalroot, key, value);
		pthread_mutex_unlock(&lock1);
		if(ret==NULL)
			return false;
		return true;
	}

	bool del(Slice &key){
		pthread_mutex_lock(&lock1);
		globalroot = deleteNode(globalroot,key);
		pthread_mutex_unlock(&lock1);
		return true;
	}

	bool get(int N,Slice& key, Slice& value){
		pthread_mutex_lock(&lock1);
		Node *tempkey = getnth(globalroot,N);
		pthread_mutex_unlock(&lock1);
		if(tempkey == NULL)
		{
			return false;
		}
		key = tempkey->key;
		value = tempkey->value;
		return true;
	}

	bool del(int N){
		pthread_mutex_lock(&lock1);
		Node *l = getnth(globalroot,N);
		pthread_mutex_unlock(&lock1);
		if(l==NULL)
		{
			return false;
		}
		this->del(l->key);
		return true;
	}

};