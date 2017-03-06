#include <bits/stdc++.h>
using namespace std;

#define foreach(v,it) for(typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define resource_list std::vector< std::pair<int,char> >
#define resources std::map< char , std::vector< std::pair<int,char> > >

class Graph
{
    int n;
    list<int> *adj;
    bool isCyclicUtil(int v, bool visited[], bool *rs);
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);
    public:
    Graph(int n);
    void addEdge(int u, int v);
    bool isCyclic();
    void topologicalSort();
};

void makeGraph(Graph g,resources v);
void print(resources v);
void print(resource_list v);


int main(int argc, char **argv)
{
    char filename[100],line[20];
    string s;
    fstream f;
    char mode, r_id;
    int n, t_id, max_t_id;
    resources v;

    if(argc!=2)
        cout<<"Usage:"<<endl<<"./executable <input file>"<<endl;
    else
    {
        strcpy(filename, argv[1]);
        f.open(filename,ios::in);
        max_t_id = 0;
        while(getline(f,s))
        {
            strcpy(line,s.c_str());
            sscanf(line,"%c %d %c",&mode,&t_id,&r_id);
            v[r_id].push_back(make_pair(t_id,mode));
            if(t_id>max_t_id)
                max_t_id = t_id;
        }
        // print(v);

        Graph g(max_t_id+1);
        makeGraph(g,v);

        if(g.isCyclic())
        {
            cout<<"Not conflict serializable"<<endl;
        }
        else
        {
            cout<<"Conflict serializable"<<endl;
            cout<<"Order of transactions :"<<endl;
            g.topologicalSort();
        }
    }

    return 0;
}


/* Graph class functions */

Graph::Graph(int n)
{
    this->n = n;
    adj = new list<int>[n];
}
 
void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
}
 
bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack)
{
    if(visited[v] == false)
    {
        // Mark the current node as visited and part of recursion stack
        visited[v] = true;
        recStack[v] = true;
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) )
                return true;
            else if (recStack[*i])
                return true;
        }
    }
    recStack[v] = false;  // remove the vertex from recursion stack
    return false;
}

// Returns true if the graph contains a cycle, else false.
bool Graph::isCyclic()
{
    // Mark all the vertices as not visited and not part of recursion stack
    bool *visited = new bool[n];
    bool *recStack = new bool[n];
    for(int i = 0; i < n; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }
    // Call the recursive helper function to detect cycle in different DFS trees
    for(int i = 0; i < n; i++)
    {
        if (isCyclicUtil(i, visited, recStack))
            return true;
    }
    return false;
}

// A recursive function used by topologicalSort
void Graph::topologicalSortUtil(int v, bool visited[], stack<int> &Stack)
{
    // Mark the current node as visited.
    visited[v] = true;
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if (!visited[*i])
            topologicalSortUtil(*i, visited, Stack);
    }
    // Push current vertex to stack which stores result
    Stack.push(v);
}
 
// The function to do Topological Sort. It uses recursive topologicalSortUtil()
void Graph::topologicalSort()
{
    stack<int> Stack;
    // Mark all the vertices as not visited
    bool *visited = new bool[n];
    for (int i = 0; i < n; i++)
        visited[i] = false;
    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);
    }
    // Print contents of stack
    while (Stack.empty() == false)
    {
        cout<<Stack.top()<<" ";
        Stack.pop();
    }
    cout<<endl;
}


/* Processing */

void makeGraph(Graph g,resources v)
{
    int l,tid1,tid2,i,j;
    char mode1,mode2;

    foreach(v,it)
    {
        l = (it->second).size();
        for(i=0;i<l-1;i++)
        {
            tid1 = (it->second)[i].first;
            mode1 = (it->second)[i].second;
            for(j=i+1;j<l;j++)
            {
                mode2 = (it->second)[j].second;
                if(mode1!='R' || mode2!='R')
                {
                    tid2 = (it->second)[j].first;
                    if(tid1!=tid2)
                        g.addEdge(tid1,tid2);
                }
            }
        }
    }
}

/* Print functions */

void print(resources v)
{
    foreach(v,i)
    {
        cout<<i->first<<":"<<endl;
        print(i->second);
    }
}

void print(resource_list v)
{
    foreach(v,i)
    {
        cout<<"("<<i->first<<","<<i->second<<")"<<endl;
    }
}