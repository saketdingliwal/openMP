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

double distance(point p1,point p2,point p3)
{
	float area =  abs((p1.x-p3.x)*(p2.y-p1.y) - (p1.x-p2.x)*(p3.y-p1.y));
	// float dist = sqrt(1.0* (p2.x-p3.x)**2 + (p2.y-p3.y)**2);
	// if(dist==0)
	// 	return -1;
	// float perpedicular = area/dist;
	return area;
}

int sign(point p,point p1,point p2)
{
	return (p.x-p1.x)*(p2.y-p1.y) - (p.y-p1.y)*(p2.x-p1.x);
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
    			bt.x = j+1;
    			bt.y = i+1;
    			points.push_back(bt);
    		}
    	}
    }

	for(int i=0;i<points.size();i++)
	{
		
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



	while(comp_list.size()!=0)
	{
		// print_comp(comp_list);
		// cout << "---------------------------"<<endl;
		vector<compute> new_comp_list;
		for(int i=0;i<comp_list.size();i++)
		{	
			double maxx = -2;
			point p;
			for(int j=0;j<comp_list[i].v.size();j++)
			{
				double dist = distance(comp_list[i].v[j],comp_list[i].p1,comp_list[i].p2);
				if(maxx < dist)
					p = comp_list[i].v[j];
				maxx = max(maxx,dist);
			}
			if(maxx<=0)
			{
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
					int sign1 = sign(comp_list[i].v[j],comp_list[i].p1,p) * sign(comp_list[i].p2,comp_list[i].p1,p);
					if(sign1<0)
						c1.v.push_back(comp_list[i].v[j]);
					int sign2 = sign(comp_list[i].v[j],comp_list[i].p2,p) * sign(comp_list[i].p1,comp_list[i].p2,p);
					if(sign2<0)
					{	
						c2.v.push_back(comp_list[i].v[j]);
					}

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
	for (set<pair<int,int> >::iterator i = ans.begin(); i != ans.end(); i++) 
	{
   		int x = i->first;
   		int y = i->second;
   		cout << x << " "<< y << endl;

	}

}