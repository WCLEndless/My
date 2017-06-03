#include<iostream>
using namespace std;
#include<time.h>
#include<iomanip>
#include<cmath>
#define NUM 100

#define MAXFLOAT 3.14e38f;

struct Point_X
{
	float x;
	float  y;
	int id;
	operator float()const{ return x; }
};
struct Point_Y
{
	float x;
	float  y;
	int p;
	operator float()const { return y; }
};
/////////////////////////////////////
template<class Type>
void Merge(Type *sd, Type *si, int left, int m, int right)
{
	int i = left, j = m + 1;
	int k = left;
	while (i <= m && j <= right)
	{
		sd[k++] = si[i] < si[j] ? si[i++] : si[j++];
	}
	while (i <= m)
	{
		sd[k++] = si[i++];
	}
	while (j <= right)
	{
		sd[k++] = si[j++];
	}
}
template<class Type>
void Copy(Type *sd, Type *si, int left, int right)
{
	for (int i = left; i <= right; ++i)
	{
		sd[i] = si[i];
	}
}
template<class Type>
void MergePass(Type *br, Type *ar, int left, int right)
{
	if (left < right)
	{
		int m = (right - left) / 2 + left;
		MergePass(br, ar, left, m);
		MergePass(br, ar, m + 1, right);
		Merge(br, ar, left, m, right);
		Copy(ar, br, left, right);
	}

}
template<class Type>
void MergeSort(Type *ar, int n)
{
	Type *br = new Type[n];
	MergePass(br, ar, 0, n - 1);
	delete[]br;
}
///////////////////////////////////


void PrintPoint(Point_X *point, int num)
{
	for (int i = 0; i < NUM; i++)
	{
		cout <<point[i].id<<"=》"<< point[i].x << setw(6) << point[i].y << endl;
	} 
	cout << endl;
}
template<typename type>
float Distance(const type &p1,const type &p2)
{
	float dx = p1.x - p2.x;
	float dy = p1.y - p2.y;
	return sqrt(dx*dx + dy*dy);
}
float Closest(Point_X*X, Point_Y* Y, Point_Y*Z, int left,int right, Point_X&a, Point_X&b)
{
	int num = right - left;
	if (num <= 0)
		return MAXFLOAT;
	if (num == 1)
	{
		
		a = X[left];
		b = X[right];
		return Distance(X[left], X[right]);
	}
	if (num == 2)
	{
		float dis1=Distance(X[left], X[left+1]);
		float dis2 = Distance(X[left + 1], X[left + 2]);
		float dis3 = Distance(X[left + 2], X[left]);
		if (dis1 < dis2&&dis1 < dis3)
		{
			a = X[left];
			b = X[left+1];
			return dis1;
		}
		if (dis2 < dis1&&dis2 < dis3)
		{
			a = X[left+1];
			b = X[left+2];
			return dis2;
		}
		else
		{
			a = X[left];
			b = X[left+2];
			return dis3;
		}
	}
	int m = (right - left) / 2 + left;
	//int z1 = left, m1 = m + 1;
	
	float d1 = Closest(X, Y,Z, left, m, a, b);
	Point_X a1, b1;
	float d2 = Closest(X, Y, Z, m + 1, right, a1, b1);
	float d = MAXFLOAT;
	if (d1 < d2)
		d = d1;
	else
	{
		d = d2;
		a = a1;
		b = b1;
	}
	//Merge(Y, Z, left, m, right);
	int k = left;
	for (int i = left; i < right;i++)
	{
		if (fabs(X[m].x - Y[i].x) < d)
		{
			Z[k++] = Y[i];
		}
	}
	for (int i = left; i < k; i++)
	{
		for (int j = i + 1; j < k; j++)
		{
			if (fabs(Z[i].y - Z[j].y) >= d)//Z中本来就是按照Y排序的，因此一旦遇到比d大的后面也就都比d大
				break;
			float d3 = Distance(Z[i], Z[j]);
			if (d3 > d)
			{
				a = X[Z[i].p];
				b = X[Z[j].p];
				d = d3;
			}
		}
	}
	return d;
}
float Cpair(Point_X*X, int num, Point_X &a, Point_X &b)
{
	MergeSort(X, num);
	Point_Y *Y =new Point_Y[num];
	for (int i = 0; i < num; i++)
	{
		Y[i].p = i;
		Y[i].x = X[i].x;
		Y[i].y = X[i].y;
	}
	Point_Y *Z = new Point_Y[num];
	MergeSort(Y, num);
	float mindis = Closest(X, Y, Z, 0,num-1, a, b);
	return mindis;
}
int main()
{
	srand(time(NULL));
	Point_X point[NUM];
	for (int i = 0; i < NUM; i++)
	{
		point[i].x = rand() % 100 + 1;
		point[i].y = rand() % 100 + 100;
		point[i].id = i;
	}
	point[4].x = 101;
	point[4].y = 101;
	point[90].x = 102;
	point[90].y = 102;
	Point_X a, b;
	PrintPoint(point, NUM);
	cout<<Cpair(point, NUM, a, b)<<endl;
	cout <<a.id<<"=>"<< a.x << "," << a.y << "   " <<b.id<<"=>"<< b.x << "," << b.y << endl;
	return 0;
}