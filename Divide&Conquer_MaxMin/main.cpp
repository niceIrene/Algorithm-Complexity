#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
int getMax(int *arr,int a,int b);
int getMin(int *arr,int a,int b);
int compareTimes=0;//��¼�ȽϵĴ���

int getMax(int *arr,int a,int b)
{
	if((b-a)==1) {compareTimes++;return arr[a]>arr[b]?arr[a]:arr[b];}//������ֻ���������ֵ�ʱ��Ĵ���
	else
		{
		 int max1=getMax(arr,a,(b+a)/2);
		 int max2=getMax(arr,(b+a)/2+1,b);
		 compareTimes++;
		 return max1>max2?max1:max2;
		}

}
int getMin(int *arr,int a,int b)
{
	if((b-a)==1) {compareTimes++;return arr[a]<arr[b]?arr[a]:arr[b];}//������ֻ���������ֵ�ʱ��Ĵ���
	else
		{
		 int min1=getMin(arr,a,(b+a)/2);
		 int min2=getMin(arr,(b+a)/2+1,b);
		 compareTimes++;
		 return min1<min2?min1:min2;
		}

}

int main()
{

	srand(time(NULL));
	int n;
	cout<<"Please input a number"<<endl;
	cin>>n;//���û���������Ĺ�ģ
	int *array=new int [n];
	for(int i=0;i<n;i++)
		array[i]=rand();
	//�����㷨�Ŀ�ʼ
	int min,max;
	max=getMax(array,0,n-1);
	min=getMin(array,0,n-1);
	cout<<"The maximum is "<<max<<endl;
	cout<<"The minimum is "<<min<<endl;
	cout<<"The total time is "<<compareTimes<<endl;


	delete [] array;
}
