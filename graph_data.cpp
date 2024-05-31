#include<bits/stdc++.h>
using namespace std;

bool find_cycle(int node, vector<int> adj[], vector<int> &vis)
{
    vis[node] = 1;

    for(auto it : adj[node])
    {
        if(vis[it] == 1)
        return true;

        else if(vis[it] == 0)
        {
            if(find_cycle(it, adj, vis) == true)
            return true;
        }
    }

    vis[node] = 2;
    return false;
}

bool is_cycle(vector<vector<double>> &mat, int n)
{
    vector<int> adj[n];

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(mat[i][j] != 0)
            {
                adj[i].push_back(j);
            }
        }
    } 

    vector<int> vis(n, 0);
    
    for(int i = 0; i < n; i++)
    {
        if(!vis[i])
        {
            if(find_cycle(i, adj, vis) == true)
            return true;
        }
    }

    return false;
}

int main()
{
    int n;
    cin>>n;
    int cnt = 0;
    srand ( time(NULL) );

    vector<int> v(n);
    for(int i = 0; i < n; i++)
    v[i] = i;

    random_device rd;
    mt19937 gen(rd());
    shuffle(v.begin(), v.end(), gen);

    vector<vector<double>> mat(n, vector<double> (n, 0));
	for(int k = 0; k < n; k++)
	{
        int i = v[k];

        for(int j = 0; j < n; j++)
        {
            if(rand() % 2 == 0 && i != j)
            {
                double prob = rand()/(double)RAND_MAX;
                mat[i][j] = prob;

                if(is_cycle(mat, n) == true)
                mat[i][j] = 0;

                if(mat[i][j] != 0)
                cnt++;


            }

           cout<<mat[i][j]<<"  ";
        }
       cout<<endl;
	}
    // cout<<endl<<cnt;

}