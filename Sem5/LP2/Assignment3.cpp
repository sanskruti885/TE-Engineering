#include <bits/stdc++.h>
using namespace std;

void dijikstra(vector<vector<pair<int,int>>> &adj,int src){
    int adj_size = adj.size();

    //min-heap bring smallest weight element at top
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq; //push weight and node

    // array to store distance intially assign everything with min
    vector<int> dist(adj_size,INT_MAX); 

    dist[src] = 0;
    pq.emplace(0,src); //push weight initially as 0

    int cur_dist,cur_node,new_dis,new_node;

    while(!pq.empty()){
        auto top_ele = pq.top(); //element we are on now
        pq.pop();

        cur_dist = top_ele.first;
        cur_node = top_ele.second;

        if(dist[cur_node]<cur_dist) continue; //bcoz if we already have less distance in array

        for(auto &p : adj[cur_node]){
            new_dis = p.first;
            new_node = p.second;

            if(dist[cur_node]+new_dis<dist[new_node]){
                dist[new_node] = dist[cur_node]+new_dis;
                pq.emplace(dist[new_node],new_node);
            } 
        }
    }
    cout << "\nShortest distances from source:\n";
    for (int i = 0; i < adj_size; i++) {
        if (dist[i] == INT_MAX)
            cout << "Node " << i << " : INF\n";
        else
            cout << "Node " << i << " : " << dist[i] << "\n";
    }

}
int main() {
    int n, m;

    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> m;

    vector<vector<pair<int,int>>> adj(n);

    cout << "Enter edges (u v weight):\n";
    cout << "(0-based indexing)\n";

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({w, v});
        adj[v].push_back({w, u}); // remove if directed graph
    }

    int src;
    cout << "Enter source node: ";
    cin >> src;

    dijikstra(adj, src);

    return 0;
}

