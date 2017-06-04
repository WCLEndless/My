#include<iostream>
using namespace std;

int **Get2Array(int row ,int clo)
{
	int **ar = (int**)malloc(sizeof(int *)*row);
	for (int i = 0; i < row; i++)
	{
		ar[i] = (int *)malloc(sizeof(int)*clo);
		memset(ar[i], 0, sizeof(int)*clo);
	}
	
	return ar;
}
void Print2Array(int **ar,int row,int clo)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < clo; j++)
		{
			cout << ar[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

//最长公共子序
int count1 = 0;
int LCSLength(int *ar, int *ar1, int n, int m,int ** c,int **s)
{
	count1++;
	if (n == 0 || m == 0)
		return 0;
	else if (c[n][m] > 0) return c[n][m];
	if (ar[n] == ar1[m])
	{
		c[n][m] = LCSLength(ar, ar1, n - 1, m - 1, c,s) + 1;
		s[n][m] = 1;
	}
	else
	{
		int a=LCSLength(ar, ar1, n - 1, m,c,s);
		int b=LCSLength(ar, ar1, n, m - 1,c,s);
		if (a > b)
		{
			c[n][m] = a;
			s[n][m] = 2;
		}
		else
		{
			c[n][m] = b;
			s[n][m] = 3;
		}
	}
	return c[n][m];
}
int count2 = 0;
int LCSLength(int *ar, int *ar1, int n, int m)
{
	count2++;
	if (n == 0 || m == 0)
		return 0;
	if (ar[n] == ar1[m])
		return  LCSLength(ar, ar1, n - 1, m - 1) + 1;
	else
	{
		int a = LCSLength(ar, ar1, n - 1, m);
		int b = LCSLength(ar, ar1, n, m - 1);
		return a > b ? a : b;
	}
}
void TraceBack(int **s,int *c, int n, int m)
{
	if (n == 0 || m == 0)return;
	if (s[n][m] == 1)
	{
		TraceBack(s, c,n - 1, m - 1);
		cout << c[n] << " ";
	}
	else if (s[n][m] == 2)
	{
		TraceBack(s, c, n - 1, m);
	}
	else
		TraceBack(s, c, n, m - 1);
}
int main()
{
	int ar[] = { 0,1, 3, 5,7 };
	int ar1[] = { 0,3, 4, 5, 6 };
	int len_n = sizeof(ar) / sizeof(ar[0]);
	int len_m = sizeof(ar1) / sizeof(ar1[0]);
	int **c = Get2Array(len_n , len_m );
	int **s = Get2Array(len_n, len_m);
	Print2Array(c, len_n , len_m );
	cout << LCSLength(ar, ar1, len_n-1, len_m-1,c,s) << endl;
	Print2Array(c, len_n , len_m );
	//Print2Array(s, len_n, len_m);
	cout << count1 << endl;
	TraceBack(s, ar, len_n - 1, len_m - 1);
	
	//cout << LCSLength(ar, ar1, len_n - 1, len_m - 1) << endl;
	//cout << count2 << endl;
	return 0;
}