#include<iostream>
#include<time.h>
#include<stack>
using namespace std;

//快速排序的递归形式
int Partition(int *ar, int left, int right)
{
	if (ar == NULL || left == right) return left;
	srand((unsigned int)time(NULL));
	int position = rand() % (right - left + 1) + left;//避免快速排序的退化（有序）
	int tmp1 = ar[left];
	ar[left] = ar[position];
	ar[position] = tmp1;
	int tmp = ar[left];
	while (left < right)
	{
		while (right>left && ar[right] >= tmp) right--;//这里如果不加等号 就会造成无限循环（两个相等的值不停地交换）
		if (left < right) ar[left] = ar[right];
		while (left<right && ar[left] <= tmp) left++;
		if (left < right) ar[right] = ar[left];
	}
	ar[left] = tmp;
	return left;
}

void Quick(int *ar, int left, int right)
{
	if (ar == NULL || left == right) return;
	int pos = Partition(ar, left, right);
	if (pos>left)
		Quick(ar, left, pos - 1);
	if (pos<right)
		Quick(ar, pos + 1, right);
}

//void QuickSort_e(int *a, int left, int right);
void QuickSort(int *ar, int len)
{
	Quick(ar, 0, len - 1);
	//QuickSort_e(ar, 0, len - 1);
}

//快速排序的非递归形式
void QuickSort_e(int *ar, int left, int right)
{
	if (ar == NULL || left > right ) return;
	stack<int> st;
	st.push(right);
	st.push(left);
	while (!st.empty())
	{
		int i = st.top();
		st.pop();
		int j = st.top();
		st.pop();
		if (i < j)
		{
			int pos = Partition(ar, i, j);
			if (pos > i)
			{
				st.push(pos-1);
				st.push(i);
			}
			if (pos < j)
			{
				st.push(j);
				st.push(pos + 1);
			}
		}
	}
 }
 void QuickSort_e(int *ar, int len)
 {
	 //Quick(ar, 0, len - 1);
	 QuickSort_e(ar, 0, len - 1);
 }

//归并排序的递归形式
 void Merge_e(int *ar, int *br, int aleft, int aright, int bleft, int bright)
 {
	 if (ar == NULL || br == NULL || aleft > aright || bleft > bright)return;
	 int tmp = aleft;
	 int i = aleft;
	 while (aleft <= aright && bleft <= bright)
	 {
		 if (ar[aleft] <= ar[bleft])
			 br[i++] = ar[aleft++];
		 else
			 br[i++] = ar[bleft++];
	 }
	 while (aleft <= aright)
	 {
		 br[i++] = ar[aleft++];
	 }
	 while (bleft <= bright)
	 {
		 br[i++] = ar[bleft++];
	 }
	 for (int i = tmp; i <= bright; i++)
	 {
		 ar[i] = br[i];
	 }
 }
 void MergeSort_e(int *ar,int *br, int left, int right)
 {
	 if (left >= right)return;
	 int m = (right - left + 1) / 2 + left;
	 if (m > left)
		 MergeSort_e(ar,br, left, m - 1);
	 if (m < right)
		 MergeSort_e(ar,br, m, right);
	 Merge_e(ar, br, left, m - 1, m, right);
 }
 void MergeSort_e(int *ar, int len)
 {
	 if (ar == NULL || len < 2)
		 return;
	 int *br = (int *)malloc(sizeof(int)*len);
	 if (br == NULL)exit(-1);
	 memset(br, 0, sizeof(int)*len);
	 MergeSort_e(ar,br, 0, len - 1);
 }
//归并排序的非递归形式
 void  MergeSort1(int *sa, int *da, int s, int left, int right)
 {
	 if (da == NULL || sa == NULL || left > right || s == 0)return;
	 int i = left;
	 for (; i + 2 * s - 1 <= right; i += 2 * s)
	 {
		 Merge_e(sa, da, i, i + s - 1, i + s, i + 2 * s - 1);
	 }
	 if (i + s - 1 < right)
		 Merge_e(sa, da, i, i + s - 1, i + s, right);//如果不够两个s合并又多于一个s，右边界就不是i + 2 * s - 1，而是right
	 else
	 {
		 for (int j = i; j <= right; j++)
		 {
			 da[j] = sa[j];
		 }
	 }
 }
 void MergeSort(int*ar, int *br, int left, int right)
 {
	 if (ar == NULL || br == NULL || left > right)
		 return;

	 int s = 1;
	 while (s < right)
	 {
		 MergeSort1(ar, br, s, left, right);
		 s *= 2;//乘以2是往回倒，如果s>=right MergeSort1函数也会正常运行，如果没有超right还做一次归并，此处很巧妙
		 MergeSort1(br, ar, s, left, right);
		 s *= 2;
	 }
 }
 void MergeSort(int *ar, int len)
 {
	 if (ar == NULL || len <= 0)return;
	 int *br = (int *)malloc(sizeof(int)*len);
	 if (br == NULL)exit(-1);
	 memset(br, 0, sizeof(int)*len);
	 MergeSort(ar, br, 0, len - 1);//len-1很关键，函数要求传递的是下标
 }
 //打印函数
void PrintArray(int *ar, int len)
{
	if (ar == NULL || len <= 0) return;
	for (int i = 0; i < len; i++)
	{
		cout << ar[i] << " ";
	}
	cout << endl;
}

