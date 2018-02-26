#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
typedef struct 
{
	int x;
	int y;
}point;

typedef struct 
{
	// vector<point> v;
	int side;
	point p1;
	point p2;
}compute;

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
		cout << endl;
		cout << endl;

	}
}


vector<pair<int , int> > calcConvexHull ( vector<vector<int> > image, int num_threads)
{
	vector<pair<int,int> >  answer;
	vector<compute> comp_list;
	vector<point> points;
	int minn = INT_MAX;
	int maxx = INT_MIN;
	point min_p;
	point max_p;
	int core_count = num_threads;
	int m = image.size();
	int n = image[0].size();
	omp_set_num_threads(core_count);
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(image[i][j])
			{
				point pt;
				pt.x = i;
				pt.y = j;
				points.push_back(pt);
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
	answer.push_back(make_pair(min_p.x,min_p.y));
	answer.push_back(make_pair(max_p.x,max_p.y));
	compute c1;
	c1.p1 = min_p;
	c1.p2 = max_p;
	c1.side = 1;
	compute c2;
	c2.p1 = min_p;
	c2.p2 = max_p;
	c2.side = -1;
	comp_list.push_back(c1);
	comp_list.push_back(c2);
	while(comp_list.size()!=0)
	{
		// print_comp(comp_list);
		vector<compute> new_comp_list;
		#pragma omp parallel for
		for(int i=0;i<comp_list.size();i++)
		{	
			int maxx = -2;
			point p;
			for(int j=0;j<points.size();j++)
			{
				if(sign(points[j],comp_list[i].p1,comp_list[i].p2)*comp_list[i].side>0)
				{
					int dist = pnt_in_eqn(points[j],comp_list[i].p1,comp_list[i].p2);
					if(maxx < dist)
						p = points[j];
					maxx = max(maxx,dist);
				}
				
			}
			if(maxx<=0)
			{}
			else
			{
				compute c1;
				c1.p1 = comp_list[i].p1;
				c1.p2 = p;
				c1.side = -1* sign(comp_list[i].p2,comp_list[i].p1,p);
				compute c2;
				c2.p1 = comp_list[i].p2;
				c2.p2 = p;
				c2.side = -1 *sign(comp_list[i].p1,comp_list[i].p2,p);
				#pragma omp critical
				{
					answer.push_back(make_pair(p.x,p.y));
					new_comp_list.push_back(c1);
					new_comp_list.push_back(c2);
				}
			}
		}
		comp_list.clear();
		comp_list.resize(new_comp_list.size());
		#pragma omp parallel for
		for(int i=0;i<new_comp_list.size();i++)
		{
			comp_list[i] = new_comp_list[i];
		}
	}
	return answer;
}

int main(int argc,char *argv[]) {
    string file_headers;
    getline(cin, file_headers);
    getline(cin, file_headers);

    int num_threads;
    num_threads = atoi(argv[1]);
    // cin >> num_threads;
    int m, n;
    cin >> m >> n;
    // m = atoi(argv[1]);
    // n = m;
    // m = 1000;
    // n=1000;
    vector< vector<int> > image;
    image.resize(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int a;
            cin >> a;
           	// a = rand() % 2;
            // a = 1;
            image[i].push_back(a);
            // cout << m;
        }
    }
    // cout << "sd";
    vector< pair<int, int> > convexHull;
    double start_time = omp_get_wtime();
    convexHull = calcConvexHull(image, num_threads);
    double time_taken = omp_get_wtime() - start_time;

    // Printing stats and results
    cout<< time_taken << endl;
    cout<< convexHull.size() << endl;

    for (int i = 0; i < convexHull.size(); i++){
        cout << convexHull[i].first << " " << convexHull[i].second << endl;
    }

    return 0;
}