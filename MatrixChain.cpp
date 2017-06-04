#include<iostream>
using namespace std;
#include<iomanip>

#define SIZE 6

int ** Get2Array(int n, int m)
{
	int **s = (int**)malloc(sizeof(int*)*n);
	for (int i = 0; i<n; ++i)
	{
		s[i] = (int*)malloc(sizeof(int)*m);
		memset(s[i], 0, sizeof(int)*m);
	}
	return s;
}

void Free2Array(int **p, int n)
{
	for (int i = 0; i<n; ++i)
	{
		free(p[i]);
	}
	free(p);
}

void Print2Array(int **s, int n, int m)
{
	for (int i = 0; i<n; ++i)
	{
		for (int j = 0; j<m; ++j)
		{
			cout << setw(6) << s[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
//没有消除重复计算
int num = 0;
int MatrixChain(int* p, int i, int j)
{
	num++;
	if (i == j)
		return 0;
	else
	{
		int count = MatrixChain(p, i + 1, j) + p[i - 1] * p[i] * p[j];
		for (int k = i + 1; k < j; k++)
		{
			int t = MatrixChain(p, k + 1, j) + MatrixChain(p, i, k) + p[i - 1] * p[k] * p[j];
			if (t < count)
			{
				count = t;
			}
		}
		return count;
	}
}
int num1 = 0;
int MatrixChain(int *p, int i, int j, int **c, int **s)
{
	num1++;
	if (i == j)
		return 0;
	else if (c[i][j]>0)return c[i][j];
	else
	{
		c[i][j] = MatrixChain(p, i + 1, j, c, s) + p[i - 1] * p[i] * p[j];
		s[i][j] = i;
		for (int k = i + 1; k < j; k++)
		{
			int t = MatrixChain(p, i, k, c, s) + MatrixChain(p, k + 1, j, c, s) + p[i - 1] * p[k] * p[j];
			if (t < c[i][j])
			{
				c[i][j] = t;
				s[i][j] = k;
			}
		}
		return c[i][j];
	}
}
void TraceBack(int **s,int i,int j)
{
	if (i == j) return;
	TraceBack(s, i, s[i][j]);
	TraceBack(s, s[i][j] + 1, j);
	cout << "Matrix A " << i << " * " << s[i][j] << " and ";
	cout << "Matrix A " << s[i][j] + 1 << " * " << j << endl;
}
int MatrixChain2(int *p, int **c, int n)
{
	int i, j;
	for (i = 1; i <= n; ++i) c[i][i] = 0;
	for (int len = 2; len <= n; ++len)
	{
		for (i = 1; i <= n - len + 1; ++i)
		{
			j = i + len - 1;
			c[i][j] = c[i][i] + c[i + 1][j] + p[i - 1] * p[i] * p[j];
			for (int k = i + 1; k<j; ++k)
			{
				int t = c[i][k] + c[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (c[i][j] > t)
				{
					c[i][j] = t;
				}
			}
			Print2Array(c, n + 1, n + 1);
		}
		cout << endl;
	}
	return c[1][n];
}
/*
//最长字段和简单实现
int MaxSum(int *a, int n)
{
	if (a == NULL || n == 0)
		return 0;
	int num = 0;
	int b = 0;
	for (int i = 0; i < n; i++)
	{
		if (b > 0)
			b += a[i];
		else
			b = a[i];
		if (b > 0)num = b;
	} 
	return num;
}*/

int main()
{
	int p[SIZE + 1] = { 30, 35, 15, 5, 10, 20,-9};

	int ** c = Get2Array(SIZE + 1, SIZE + 1);
	int **s = Get2Array(SIZE + 1, SIZE + 1);
	
	cout <<"没有消除重复计算："<< MatrixChain(p, 1, SIZE) << endl;
	cout << num << endl;

	cout << "消除了重复计算：" << MatrixChain(p, 1, SIZE, c, s) << endl;
	cout << num1 << endl;
	TraceBack(s, 1, SIZE);

	//cout << "最大字段和：" << MaxSum(p, SIZE + 1) << endl;
	return 0;
}