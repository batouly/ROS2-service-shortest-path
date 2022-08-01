// Cpp program for the above approach
#include <bits/stdc++.h>

using namespace std;

class graph
{
    map<string,int> id;
    map<int,string> who;
    int sz ;
    int n ;
    public:
        graph(int);
        // Function to form edge between two vertices src and dest
        void add_edge(vector<int> [],int , int );
        // Function which finds all the paths
        void find_paths(vector<vector<int> >& ,vector<int>& ,vector<int> [], int );
        // Function which performs bfs from the given source vertex
        void bfs(vector<int> [],vector<int> [],int , int );
        // function to get the id of the node
        int get_id(string);
        // Function which return all the paths from start to end
        pair<string,int> get_paths(vector<int> [], string , string);
};
// to calculate the number of nodes in the graph
int calc_size (string);

pair<string, int>  request_paths(string ,string);

graph::graph(int sz)
        {
            this->sz = sz;
            id.clear();
            who.clear();
            n = 0;
        }
void graph::add_edge(vector<int> adj[],int src, int dest)
        {
            adj[src].push_back(dest);
            adj[dest].push_back(src);
        }

void graph::find_paths(vector<vector<int> >& paths,vector<int>& path,vector<int> parent[],int u)
        {
            // Base Case
            if (u == -1) {
                paths.push_back(path);
                return;
            }
            // Loop for all the parents of the given vertex
            for (int par : parent[u]) {

                // Insert the current vertex in path
                path.push_back(u);
                // Recursive call for its parent
                find_paths(paths, path, parent, par);
                // Remove the current vertex
                path.pop_back();
            }
        }

void graph::bfs(vector<int> adj[],
                vector<int> parent[],
                int n, int start)
        {
            // dist will contain shortest distance from start to every other vertex
            vector<int> dist(n, INT_MAX);
            queue<int> q;
            // Insert source vertex in queue and make its parent -1 and distance 0
            q.push(start);
            parent[start] = { -1 };
            dist[start] = 0;

            // Until Queue is empty
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : adj[u]) {
                    if (dist[v] > dist[u] + 1) {

                        // A shorter distance is found so erase all the previous parents
                        // and insert new parent u in parent[v]
                        dist[v] = dist[u] + 1;
                        q.push(v);
                        parent[v].clear();
                        parent[v].push_back(u);
                    }
                    else if (dist[v] == dist[u] + 1) {

                        // Another candidate parent for shortest path found
                        parent[v].push_back(u);
                    }
                }
            }
        }
int graph::get_id(string nd)
        {
            if(id.find(nd)==id.end())
            {
                who[this->n]=nd;
                id[nd]=this->n++;
            }
            return id[nd];
        }
    
pair<string,int> graph::get_paths(vector<int> adj[], string start, string end)
        {
            vector<vector<int> > paths;
            
            vector<int> path;
            vector<int> parent[this->sz];

            // Function call to bfs
            bfs(adj, parent, this->sz, id[start]);

            // Function call to find_paths
            find_paths(paths, path, parent,id[end]);
            int i =0;
            string* ps = new string[paths.size()];
            string s ;
            int x = 0;

            for (auto v : paths)
            {

                reverse(v.begin(), v.end());

                // store node for the current path
                for (int u : v)
                    s+=who[u]+"-";
                
                s.pop_back();
                s+=" ";
                i++;
                x = v.size()- 1 ;
            }
            
            return make_pair(s,x+1);
        
        }

int calc_size (string input)
        {
            map <char,int> nodes;
                for (int i=0;i<input.length();i++)
                {
                    if (input[i]==' '|| input[i]=='-')
                    continue;
                    nodes[input[i]] = 1;
                }
            return nodes.size();
        }

pair<string, int>  request_paths(string input,string p)
        {
            int sz = calc_size(input);
            graph g(sz);
            vector<int> adj[sz];
            string src(1,p[0]);
            string dest(1,p[2]);
            int first_edge=0;
            string a ;
            string b ;
            for (int i=0;i<input.length();i++)
            {
                if(input[i]=='-')
                {
                    a = string(1,input[i-1]);
                    b = string(1,input[i+1]);
                    int u=g.get_id(a);
                    int v=g.get_id(b);
                    g.add_edge(adj,u,v);
                }

            }
            pair<string, int> pr = g.get_paths(adj,src, dest);
            return pr;
            
        }
