#include<iostream>
using namespace std;
void swap(int* &a,int i,int j )
{
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}
//ȫ���еĵݹ���ʽ
void Perm(int *ar,int k, int m)
{
	if (k == m)
	{
		for (int i = 0; i <= m; i++)
		{
			cout << ar[i] << " ";
		}
		cout << endl;
	}
	else
	{
		int j = k;
		while (j <= m)
		{
			swap(ar,j, k);
			Perm(ar, k + 1, m);//123 132 213 231
			swap(ar,j,k);
			j++;
		}
	}
}
//������a�е��±�i���±�j֮�������Ԫ��������
void reverse(int a[], int i, int j)
{
	for (; i<j; ++i, --j)
	{
		swap(a, i, j);
	}
}

void my_print(int *ar, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << ar[i] << " ";
	}
	cout << endl;
}
//�����ȫ���е�ѭ���㷨�����ڴ�С�����Ź��������
void arrage(int *ar, int len)
{
	if (ar == NULL || len <= 0)return;
	int i, j;
	while (true)
	{
		my_print(ar, len);
		for (i = len - 2; i >= 0; i--)
		{
			if (ar[i + 1] > ar[i])
				break;
			else if (0 == i)return;//�жϽ���������
		}
		for (j = len - 1; j >= 0; j--)
		{
			if (ar[i] < ar[j])
				break;
		}
		swap(ar[i], ar[j]);
		reverse(ar, i + 1, len - 1);
	}
}


//���Ӽ��ĵݹ��㷨
void Subset(int *ar, int *br,int k,int m,int len)
{
	if (ar == NULL || br == NULL)return;
	if (k>m)
	{
		for (int i = 0; i < len; i++)
		{
			if (br[i] == 1)
			{
				cout << ar[i] << " ";
			}
		}
		cout << endl;
	}
	else
	{
		br[k] = 1;
		Subset(ar, br, k + 1, m, len);
		br[k] = 0;
		Subset(ar, br, k + 1, m, len);
	}
}

void print_e(int *ar,int *br, int len)
{
	if (ar == NULL || br==NULL||len < 0)return;
	for (int i = 0; i < len; i++)
	{
		if (br[i] != 0)
		{
			cout << ar[i] << " ";
		}
	}
	cout << endl;
}
//���Ӽ���ѭ��д�����������ö����Ƽ�һ��һ�ε��㷨
void Subset_e(int *ar,int len)//ʱ�临�Ӷȴ�O��2��n�η�
{
	int *br = (int *)malloc(sizeof(int)*len);
	if (br == NULL)exit(-1);
	memset(br, 0, sizeof(int)*len);
	int count = 1;
	for (int i = 0; i < len; i++)
	{
		count *= 2;
	}
	print_e(ar, br, len);
	for (int i = 0; i < count; i++)
	{
		int tmp = len-1;
		
		br[tmp--] = i % 2;
		int a = i / 2;
		while (a!=0)
		{
			br[tmp--] = a % 2;
			a = a / 2;
		}
		print_e(ar, br, len);
	}
}

//�����Ļ���
int split(int n, int m)
{
	if (n < 1 || m < 1)return 0;
	if (n == 1 || m == 1)return 1;
	if (n < m)return split(n, n);
	if (m == n)return split(n, m - 1) + 1;
	if (n > m) return split(n, m - 1) + split(n - m, m);
}
//��������
void QuickSort(int *ar, int len);
void PrintArray(int *ar, int len);
void QuickSort_e(int *ar, int len);
void MergeSort(int *ar, int len);
void MergeSort_e(int *ar, int len);

int main()
{
	int ar[] = { 1,2,3,4};
	int br[] = { 0, 0, 0 };
	//Perm(ar, 0, 2);
	//Subset(ar, br, 0, 2, 3);
	//arrage(ar, 4);
	Subset_e(ar, 4);
	cout << "+++++++++++++++++++++++++++++++++++++++++" << endl;
	//printf("%d ", split(6, 6));
	int cr[] = { 34, 12, 23, 56, 78, 98, 11, 100, 10,12,23 };
	int len = sizeof(cr) / sizeof(cr[0]);
	PrintArray(cr, len);
	//QuickSort_e(cr, len);
	MergeSort_e(cr, len);

	PrintArray(cr, len);
	return 0;
}