#include <bits/stdc++.h>

using namespace std;

struct node
{
	int value;
	void* data;
	int height;
	struct node * left;
	struct node * right;
};

int height(struct node* n)
{
	if (n == NULL)
	{
		return 0;
	}
	return n->height;
}

struct node* newNode(struct node* n, int val)
{
	n = (struct node*)malloc(sizeof(struct node));

	n->value = val;
	n->height = 1;
	n->left = NULL;
	n->right = NULL;

	return n;
}

struct node * insertNode(struct node * head, int value)
{
    if (head == NULL)
    {
        return newNode(head, value);
    }

    if (head->left == NULL)
    {
        head->left = insertNode(head->left, value);
    }
    else if (head->right == NULL)
    {
        head->right = insertNode(head->right, value);
    }
    else
    {
        if (height(head->left) >= height(head->right))
        {
            head->right = insertNode(head->right, value);
        }
        else
        {
            head->left = insertNode(head->left, value);
        }
    }

    head->height = (height(head->left) > height(head->right) ? height(head->left) : height(head->right)) + 1;

    return head;
}

void preOrder(struct node *root)
{
    if(root != NULL)
    {
        printf("%d ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}

class Graph
{
    int size;
    list<int> *edges;
    struct node * dFSMark(struct node * node, int vertice, bool visited[]);
public:
    Graph(int size);
    void addEdge(int a, int b);
    struct node * dFS(struct node * node, int start);
};

Graph::Graph(int size)
{
    this->size = size;
    edges = new list<int>[size];
}

void Graph::addEdge(int a, int b)
{
    edges[a].push_back(b);
}

struct node * Graph::dFSMark(struct node * tree, int vertice, bool visited[])
{
    visited[vertice] = true;
    tree = insertNode(tree, vertice);

    list<int>::iterator it;

    for (it = edges[vertice].begin(); it != edges[vertice].end(); ++it)
    {
        if (!visited[*it])
        {
            tree = dFSMark(tree, *it, visited);
        }
    }

    return tree;
}

struct node * Graph::dFS(struct node * tree, int start)
{
    bool *visited = new bool[size];

    for (int i = 0; i < size; i++)
    {
        visited[i] = false;
    }

    return dFSMark(tree, start, visited);
}

int main ()
{
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    cout << "Following is Depth First Traversal (starting from vertex 2) \n";

    struct node * tree = NULL;

    tree = g.dFS(tree, 1);

    preOrder(tree);

    return 0;
}
