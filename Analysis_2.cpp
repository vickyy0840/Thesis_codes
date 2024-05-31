#include<bits/stdc++.h>
using namespace std;

static bool cmp(pair<int, unordered_set<int>> a, pair<int, unordered_set<int>> b)
{
	return a.second.size() > b.second.size();
}

void outdeg(vector<int> &d, vector<vector<double>> &mat, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(mat[i][j] != 0)
			d[i]++;
		}
	}
}

void first_product(vector<vector<double>> &res, vector<vector<double>> v, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			double sum = 0;
			
			for(int l = 0; l < n; l++)
			{
				sum += res[i][l]*v[l][j];
			}
			
			res[i][j] = sum;
		}
	}
}

vector<double> sec_product(vector<vector<double>> res, vector<double> f, int n)
{
	vector<double> final(n);
	
	for(int i = 0; i < n; i++)
	{
		double sum = 0;
		
		for(int j = 0; j < n; j++)
		{
			sum += res[i][j]*f[j];
		}
		
		final[i] = sum;
		
	}
	
	return final;
}

vector<vector<double>> calc(vector<vector<double>> &mat, int n, double t, int num)
{
	vector<int> d(n, 0);
	vector<vector<double>> h(n, vector<double>(n, 0));
	
	//outdegree
	outdeg(d, mat, n);
	
	//H calculation
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(i == j)
			{
				if(d[i] != 0)
				{
					double psum = 0;
					for(int l = 0; l < n; l++)
					psum += mat[i][l];
					
					h[i][j] = -psum/(double)d[i];
				}
				else
				h[i][j] = 0;
			}
			
			else if(mat[j][i] != 0)
			{
				h[i][j] = mat[j][i]/(double)d[j];
			}
			
			else
			{
				h[i][j] = 0;
			}
			
		}
	}
		
		
		//V calculation
		vector<vector<double>> res(n, vector<double>(n, 0)), Id(n, vector<double>(n, 0)), newh(n, vector<double>(n, 0)), v(n, vector<double>(n, 0));
		
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if(i == j)
				Id[i][j] = 1;
				else
				Id[i][j] = 0;
				
				newh[i][j] = (t/(double)num)*h[i][j];
				
				v[i][j] = Id[i][j] + newh[i][j];
			}
		}
		
		//Multiplications
		res = v;
		for(int i = 0; i < num-1; i++)
		{
			first_product(res, v, n);
		}
		
		return res;
		
	
}


map<int, unordered_set<int>> first_algo(int k, double par, int n, double hin, vector<vector<double>> &mfact)
{
	
	map<int, unordered_set<int>> u;
	
	for(int i = 0; i < n; i++)
	{
		vector<double> f(n, 0);
		f[i] = hin;
		
		vector<double> final = sec_product(mfact, f, n);
		
		for(int j = 0; j < n; j++)
		{
			if(final[j] >= par)
			u[i].insert(j);
		}
		
	}
	
	return u;
	
}

vector<int> sec_algo(map<int, unordered_set<int>> &u, int k)
{
	unordered_set<int> r;
	vector<int> ans;
	
	for(int i = 0; i < k; i++)
	{
		int prev = -1, pos = -1;
		for(auto it : u)
		{
			int m = it.first;
			auto Im = it.second;
			unordered_set<int> temp;
			
			for(auto itr : Im)
			{
				if(r.find(itr) != r.end())
				temp.insert(itr);
			}
			
			unordered_set<int> t_Im = Im;
			for(auto iter : temp)
			{
				t_Im.erase(iter);
			}
			
			int sz = t_Im.size();
			
			if(sz > prev)
			{
				prev = sz;
				pos = m;
			}
			
		}
		
		unordered_set<int> I = u[pos];
		
		for(auto it : I)
		{
			r.insert(it);
		}
		
		u.erase(pos);
		ans.push_back(pos);
	}
	
	return ans;
	 
}


int main()
{
	int n, k, num;
	double par, hin, t;
	cin>>n>>num;
	cin>>par>>hin>>t;
	
	vector<vector<double>> mat(n, vector<double> (n, 0));
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			double prob;
			cin>>prob;

			mat[i][j] = prob;
            //cout<<mat[i][j]<<"  ";
		}
		//cout<<endl;
	}
	
	vector<vector<double>> mfact;
	mfact = calc(mat, n, t, num);
	int cnt = 0, max_at_k;
	int prev = 0;
	
// 	map<int, unordered_set<int>> u = first_algo(k, par, n, hin, mfact);
// //	for(auto it : u)
// // 	{
// // 	    cout<<it.first<<" ";
// // 	    for(auto itr : it.second)
// // 	    cout<<itr<<" ";
	    
// // 	    cout<<endl;
// // 	}
	
// 	vector<int> ans = sec_algo(u, k);
	
	// for(auto it : ans)
	// cout<<it<<" ";
	
	for(int k = 1; k <= n/6; k++)
	{
		map<int, unordered_set<int>> u = first_algo(k, par, n, hin, mfact);
		vector<int> vec = sec_algo(u, k);
		
		int temp = 0;

        vector<double> fin(n, 0);
        for(auto it : vec)
        {
    	    fin[it] = hin;
        }
	
        vector<double> final = sec_product(mfact, fin, n);
    
        for(int i = 0; i < n; i++)
        {
        	if(final[i] >= par)
        	{
        		temp++;
			}
	    }
	    
	    cout<<(temp/(double)n)*100<<endl;
    
        if(cnt < temp)
        {
        	cnt = temp;
        	max_at_k = k;
		}
	}
	
	//cout<<max_at_k;
	
}