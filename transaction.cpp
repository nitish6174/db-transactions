#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>

typedef struct 
{
	char op;
	int trans;
	char attr;
} action;

void printGraph(vector<vector<int> > &graph);
bool isCyclicUtil(vector<vi> &graph, int v, bool visited[], bool *recStack);
bool isCyclic(vector<vi> &graph);
void topologicalSortUtil(vector<vi> &graph, int v, bool visited[], stack<int> &Stack);
void topologicalSort(vector<vi> &graph);

int main(int argc, char const *argv[])
{
	char filename[100];
	strcpy(filename, argv[1]);
	FILE *fp = freopen(filename, "r", stdin);
	string s;
	int n,i,j,a,b,ntrans=0;
	char var;
	vector<action> v;
	action temp;
	while(cin >> s)
	{
		if(s=="r" || s=="w")
		{
			cin >> n >> var;
			temp.op = s[0];
			temp.trans = n;
			temp.attr = var;
			ntrans = max(ntrans, n);
			v.push_back(temp);
		}
		else if(s == "commit")
			cin >> n;
		else
			break;
	}

	vector<vector<int> > graph(ntrans+1);

	for(i=0;i<v.size();i++)
	{
		for(j=0;j<i;j++)
		{
			if(v[i].attr == v[j].attr && v[i].trans != v[j].trans)
			{
				a = v[i].trans;
				b = v[j].trans;
				if((v[i].op=='r' && v[j].op=='w') || (v[i].op=='w' && v[j].op=='r') || (v[i].op=='w' && v[j].op=='w'))
					graph[b].push_back(a);
			}
		}
	}
	// printGraph(graph);

	if(isCyclic(graph))
		cout << "Not CS";
	else
		topologicalSort(graph);
	cout << endl;
	return 0;
}

void printGraph(vector<vector<int> > &graph)
{
	int i,j;
	for(i=0;i<graph.size();i++)
	{
		cout << i << " -> ";
		for(j=0;j<graph[i].size();j++)
			cout << graph[i][j] << " ";
		cout << endl;
	}
}


bool isCyclicUtil(vector<vi> &graph, int v, bool visited[], bool *recStack)
{
	if(visited[v] == false)
	{
		visited[v] = true;
		recStack[v] = true;
 
		vi::iterator i;
		for(i = graph[v].begin(); i != graph[v].end(); ++i)
		{
			if ( !visited[*i] && isCyclicUtil(graph, *i, visited, recStack) )
				return true;
			else if (recStack[*i])
				return true;
		}
	}
	recStack[v] = false;
	return false;
}
 
bool isCyclic(vector<vi> &graph)
{
	int V = graph.size();
	bool *visited = new bool[V];
	bool *recStack = new bool[V];
	for(int i = 0; i < V; i++)
	{
		visited[i] = false;
		recStack[i] = false;
	}

	for(int i = 0; i < V; i++)
		if (isCyclicUtil(graph, i, visited, recStack))
			return true;
 
	return false;
}

void topologicalSortUtil(vector<vi> &graph, int v, bool visited[], stack<int> &Stack)
{
	visited[v] = true;
 
	vi::iterator i;
	for (i = graph[v].begin(); i != graph[v].end(); ++i)
		if (!visited[*i])
			topologicalSortUtil(graph, *i, visited, Stack);
	Stack.push(v);
}

void topologicalSort(vector<vi> &graph)
{
	stack<int> Stack;
	int V = graph.size();
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
 
	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			topologicalSortUtil(graph, i, visited, Stack);
 
	while (Stack.empty() == false)
	{
		cout << Stack.top() << " ";
		Stack.pop();
	}
}