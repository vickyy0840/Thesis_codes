#include<bits/stdc++.h>
using namespace std;

void compp(vector<pair<int, double>> adj[], vector<vector<double>> &ap, vector<vector<double>> &apn, int n)
{
	for(int i = 0; i < n; i++)
	{
		vector<int> vis(n, 0);
		vis[i] = 1;
		
		while(1)
		{
			int cnt, head;
			cnt = 0, head = i;
			double prob = 1;
			
			while(1)
			{
				double curr;
				curr = 0;
				int node = -1;
				
				for(auto it : adj[head])
				{
					int tempn = it.first;
					double wt = it.second;
					
					if(!vis[tempn] && abs(curr) <= wt)
					{
						node = tempn;
						curr = wt;
					}
				}
				
				if(node == -1)
				break;
				
				cnt++;
				vis[node] = 1;
				prob *= curr;
				
                if(prob >= 0)
				ap[i][node] = prob;
                else
                apn[i][node] = prob;

				head = node;
			}
			
			if(cnt == 0)
			break;
		}
	}
}

void findSeed(int n, vector<pair<int, double>> adj[], vector<double> &ppi, vector<double> &gp, vector<double> &gn, map<int, double> &mp, vector<vector<double>> &ap, vector<vector<double>> &apn, int k)
{
	for(int i = 0; i < n; i++)
	{
		double s1=0, s2 = 0;
		
		for(int j = 0; j < n; j++)
		{
			s1 += ap[i][j];
            s2 += apn[i][j];
		}
		
		ppi[i] = s1+s2;
	}
	
	int cnt = 0;
	
	while(cnt < k)
	{
		int x;
		double temp = -1e12;
		
		for(int i = 0; i < n; i++)
		{
			if(ppi[i] > temp && mp.find(i) == mp.end())
			{
				temp = ppi[i];
				x = i;
			}
		}
		
		for(int i = 0 ; i < n; i++)
		{
			if(mp.find(i) != mp.end())
			continue;
			
			gp[i] += ap[x][i]*(1.0 - gp[x]) + apn[x][i]*gn[x];
			
            gn[i] += -apn[x][i]*(1 - gn[x]) - ap[x][i]*gp[x];
		}
		
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				ap[i][j] += -ap[i][x] * ap[x][j] - apn[i][x] * apn[x][j];
                apn[i][j] += ap[i][x] * apn[x][j] + apn[i][x] * ap[x][j];
			}   
		}
		
		mp.insert({x, temp});
		
		for(int i = 0; i < n; i++)
		{
			if(mp.find(i) != mp.end())
			{
				continue;
			}
			double s1 = 0, s2 = 0;
			
			for(int j = 0; j < n; j++)
			{
				s1 += ap[i][j];
                s2 += apn[i][j];
			}
			
			ppi[i] = (1.0 - gp[i])*s1 + gn[i]*s2;
		}
		
		cnt++;
	}
}


int main()
{
	int n, k;
	cin>>n;

	
	vector<vector<double>> mat(n, vector<double> (n, 0));
	//set<pair<int, int>> tset;
	//srand(time(NULL));
	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			double eprob;
            cin>>eprob;
            mat[i][j] = eprob;
		}
	}
	
	vector<pair<int, double>> adj[n];
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(mat[i][j] != 0.0)
			adj[i].push_back({j, mat[i][j]});
		}
	}
	

// 	for(int i = 0; i < n; i++)
// 	{
// 	    cout<<i<<" ";
// 	    for(auto it : adj[i])
// 	    {
// 	        cout<<it.first<<","<<it.second<<" ";
// 	    }
// 	    cout<<endl;
// 	}
	
	vector<vector<double>> ap(n, vector<double>(n, 0.0));
    vector<vector<double>> apn(n, vector<double>(n, 0.0));
	
	compp(adj, ap, apn, n);
	
// 	for(int i = 0; i < n; i++)
// 	{
// 	    for(int j = 0; j < n; j++)
// 	    {
// 	        cout<<ap[i][j]<<" ";
// 	    }
// 	    cout<<endl;
// 	}
    for(k = 3; k < n/3; k = k+3)
	{
		vector<double> ppi(n, 0.0);
		vector<double> gp(n, 0.0);
        vector<double> gn(n, 0.0);
		map<int, double> mp;

		
		findSeed(n, adj, ppi, gp, gn, mp, ap, apn, k);
		double mini = 1e7;
		double maxi = -1e7;
		
		for(auto it : mp)
		{
			//cout<<it.first<<" "<<it.second;
		// long long val = it.second;
		// cout<<val;
		if(mini > it.second)
		mini = it.second;
		if(maxi < it.second)
		maxi = it.second;
			//cout<<endl;
		}
		
		//cout<<mp.size()<<endl;
		cout<<k<<" "<<mini<<" "<<maxi<<endl;
		//cout<<(long long)mini<<" "<<(long long)maxi;
	
    }

}