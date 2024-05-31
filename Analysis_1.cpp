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


vector<int> first_algo(int k, double par, int n, double hin, vector<vector<double>> &mfact)
{
	
	vector<pair<int, unordered_set<int>>> u(n);
	
	for(int i = 0; i < n; i++)
	{
		vector<double> f(n, 0);
		f[i] = hin;
		u[i].first = i;
		
		vector<double> final = sec_product(mfact, f, n);
		
		for(int j = 0; j < n; j++)
		{
			if(final[j] >= par)
			u[i].second.insert(j);
		}
		
	}
	
	sort(u.begin(), u.end(), cmp);
	vector<int> ans;
	
	for(int j = 0; j < k; j++)
	{
		ans.push_back(u[j].first);
	}
	
	return ans;
	
}


int main()
{
	// 60 5 2 15 1
	int n, num;
	double par, hin, t;
	cin>>n>>num;
	cin>>par>>hin>>t;
	srand ( time(NULL) );
	
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
	
	for(int k = 1; k < n/4; k++)
	{
		vector<int> vec = first_algo(k, par, n, hin, mfact);
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
		// cout<<k<<endl;
        if(cnt < temp)
        {
        	cnt = temp;
        	max_at_k = k;
		}
	}
	
	//cout<<max_at_k;
	
}
