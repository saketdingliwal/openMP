#include <bits/stdc++.h>
#include <omp.h>
#define NUM_THREADS 10
using namespace std;
typedef struct 
{
	int x;
	int y;
}point;

typedef struct 
{
	vector<point> v;
	point p1;
	point p2;
}compute;



double dist(point p1,point p2)
{
	double vall  = pow(1.0*(p1.x-p2.x),2) + pow(1.0*(p1.y-p2.y),2);
	double val = sqrt(vall);
	return val;

}

int pnt_in_eqn(point p,point p1,point p2)
{
	int value= abs((p.y-p1.y)*(p2.x-p1.x) - (p2.y-p1.y) * (p.x - p1.x));
	return value;
}

int sign(point p,point p1,point p2)
{
	 int vall = (p.y-p1.y)*(p2.x-p1.x) - (p2.y-p1.y) * (p.x - p1.x);
	 if(vall>0)
	 	return 1;
	 if(vall==0)
	 	return 0;
	 return -1;
}


void print_comp(vector <compute> comp_list)
{
	for(int i=0;i<comp_list.size();i++)
	{
		cout << "p1 " << comp_list[i].p1.x << " " << comp_list[i].p1.y <<endl;
		cout << "p2 " << comp_list[i].p2.x << " " << comp_list[i].p2.y <<endl;
		for(int j=0;j<comp_list[i].v.size();j++)
		{
			cout << comp_list[i].v[j].x << " " << comp_list[i].v[j].y << ", ";
		}
		cout << endl;
		cout << endl;

	}
}

int main()
{
	vector<compute> comp_list;
	vector<point> points;
	int minn = INT_MAX;
	int maxx = INT_MIN;
	point min_p;
	point max_p;

	string file_headers;
    getline(cin, file_headers);
    getline(cin, file_headers);


    int n,m;
    cin >> n >>m;
    for(int i=0;i<m;i++)
    {
    	for(int j=0;j<n;j++)
    	{
    		int gh;
    		cin >> gh;
    		if(gh)
    		{
    			point bt;
    			bt.x = i;
    			bt.y = j;
    			points.push_back(bt);
    		}
    	}
    }
   
	for(int i=0;i<points.size();i++)
	{
		// cin >> points[i].x >> points[i].y;
		if(points[i].x>maxx)
		{
			maxx = points[i].x;
			max_p = points[i];
		}
		if(points[i].x < minn)
		{
			minn = points[i].x;
			min_p = points[i];
		}
	}
	compute c1;
	c1.p1 = min_p;
	c1.p2 = max_p;
	compute c2;
	c2.p1 = min_p;
	c2.p2 = max_p;
	for(int i=0;i<points.size();i++)
	{
		if(sign(points[i],min_p,max_p)<0)
			c1.v.push_back(points[i]);
		if(sign(points[i],min_p,max_p)>0)
			c2.v.push_back(points[i]);
	}
	comp_list.push_back(c1);
	comp_list.push_back(c2);

	set<pair<int,int> > ans;

	double ans2 = 0.0;

	while(comp_list.size()!=0)
	{
		// print_comp(comp_list);
		// cout << "---------------------------"<<endl;
		vector<compute> new_comp_list;
		for(int i=0;i<comp_list.size();i++)
		{	
			int maxx = -2;
			point p;
			for(int j=0;j<comp_list[i].v.size();j++)
			{
				int dist = pnt_in_eqn(comp_list[i].v[j],comp_list[i].p1,comp_list[i].p2);
				// cout << j << " " << dist<< ",";
				if(maxx < dist)
					p = comp_list[i].v[j];
				maxx = max(maxx,dist);
			}
			if(maxx<=0)
			{
				ans2 += dist(comp_list[i].p1,comp_list[i].p2);
				ans.insert(make_pair(comp_list[i].p1.x,comp_list[i].p1.y));
				ans.insert(make_pair(comp_list[i].p2.x,comp_list[i].p2.y));
			}
			else
			{
				compute c1;
				c1.p1 = comp_list[i].p1;
				c1.p2 = p;
				compute c2;
				c2.p1 = comp_list[i].p2;
				c2.p2 = p;
				for(int j=0;j<comp_list[i].v.size();j++)
				{
					int sign1 = sign(comp_list[i].v[j],c1.p1,c1.p2) * sign(comp_list[i].p2,c1.p1,c1.p2);
					if(sign1<0)
						c1.v.push_back(comp_list[i].v[j]);
					int sign2 = sign(comp_list[i].v[j],c2.p1,c2.p2) * sign(comp_list[i].p1,c2.p1,c2.p2);
					if(sign2<0)
						c2.v.push_back(comp_list[i].v[j]);
				}
				new_comp_list.push_back(c1);
				new_comp_list.push_back(c2);
			}
		}
		comp_list.clear();
		comp_list.resize(new_comp_list.size());
		for(int i=0;i<new_comp_list.size();i++)
		{
			comp_list[i] = new_comp_list[i];
		}
	}
	cout << fixed;
	// cout << setprecision(1);
	cout <<setprecision(1)<< ans2 <<endl;
	cout << "sdf"<<ans.size();
	for (set<pair<int,int> >::iterator i = ans.begin(); i != ans.end(); i++) 
	{
   		int x = i->first;
   		int y = i->second;
   		// cout << x << " "<< y << endl;

	}

}