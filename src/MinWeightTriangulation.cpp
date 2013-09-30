//============================================================================
// Name        : MinWeightTriangulation.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
#include <cmath>
using namespace std;




class Coordinate
{
public:
	explicit Coordinate(int x = 0, int y = 0);
	int x;
	int y;
};

Coordinate::Coordinate(int x, int y):x(x),y(y)
{
	cin >> this->x >> this->y;
}


int weight(const Coordinate &, const Coordinate &, const Coordinate &);
int distance(const Coordinate &, const Coordinate &);

int min_weight_triangulation(int n,int **t,int **s,vector<Coordinate> &);
void traceback(int i,int j,int **s);

int main(int argc,char** argv) {
	size_t num = 0;
	cout << "Welcome to try the MinWeightTriangulation program." << endl;
	cout << "Please enter the numbers of vertexes: ";
	cin >> num;
	vector<Coordinate> vec;
	for(size_t i = 0; i < num ; ++i)
	{
		cout << "Please enter the coordinate of v" << i <<": ";
		vec.push_back(Coordinate());
	}

	int **s = new int *[num];
	int **t = new int *[num];

	for(size_t i = 0; i < num; ++i)
	{
		s[i] = new int[num];
		t[i] = new int[num];
	}

	cout<<"min sum of weight is : "<<min_weight_triangulation(num - 1,t,s,vec)<<endl;

	traceback(1, num - 1, s);

	//clear the space for heap memory
	for(size_t i = 0; i < num; ++i)
	{
		delete[] t[i];
		delete[] s[i];
	}
	delete[] t;
	delete[] s;

	system("PAUSE");
	return 0;
}

int weight(const Coordinate &coordinate0, const Coordinate &coordinate1, const Coordinate &coordinate2)
{
	return ::distance(coordinate0,coordinate1) + ::distance(coordinate1, coordinate2) + ::distance(coordinate0, coordinate2);
}

int distance(const Coordinate &coordinate0, const Coordinate &coordinate1)
{
	int dis = (coordinate0.x - coordinate1.x)*(coordinate0.x - coordinate1.x) + (coordinate0.y - coordinate1.y) * (coordinate0.y - coordinate1.y);
	return (int) sqrt(dis);
}

int min_weight_triangulation(int n,int **t,int **s, vector<Coordinate> &vec)
{
	for(int i = 0; i <= n; ++i)
	{
		t[i][i] = 0;
	}
	for(int r = 2; r <= n; ++r)
	{
		for(int i = 1; i <= n - r + 1; ++i)
		{
			int j = i + r - 1;
			t[i][j] = INT_MAX;

			for(int k = i ; k < i + r - 1; ++k)
			{
				int u = t[i][k] + t[k + 1][j] + weight(vec[i - 1], vec[k], vec[j]);
				if(u < t[i][j])
				{
					t[i][j] = u;
					s[i][j] = k;
				}
			}
		}
	}
	return t[1][n];
}

void traceback(int i,int j,int **s)
{
	if(i==j) return;
	traceback(i,s[i][j],s);
	traceback(s[i][j]+1,j,s);
	cout << "the vertex is v" << i - 1 << ", v" << s[i][j] << ", v" << j << endl;
}
