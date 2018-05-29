#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;
//储存楼房的结构
struct Building
{

    int R;
    int H;
    int L;
};
//只有两栋楼房的情况
vector<int>MergeTwo(Building &b1,Building &b2)
{
    Building first,second;
    if(min(b1.L,b2.L)==b1.L)
    {
        first=b1;
        second=b2;
    }
    else
    {
        first=b2;
        second=b1;
    }
    vector <int> outline;
    if(first.R<second.L)
    {
        outline.push_back(first.L);
        outline.push_back(first.H);
        outline.push_back(first.R);
        outline.push_back(0);
        outline.push_back(second.L);
        outline.push_back(second.H);
        outline.push_back(second.R);
        outline.push_back(0);
    }
    if(first.R==second.L)
    {
        outline.push_back(first.L);
        outline.push_back(first.H);
        outline.push_back(first.R);
        outline.push_back(second.H);
        outline.push_back(second.R);
        outline.push_back(0);
    }
    if(first.R>second.L&&first.R<second.R&&first.H>second.H)
    {
        outline.push_back(first.L);
        outline.push_back(first.H);
        outline.push_back(first.R);
        outline.push_back(second.H);
        outline.push_back(second.R);
        outline.push_back(0);
    }
    if(first.R>second.L&&first.R<second.R&&first.H<second.H)
    {
        outline.push_back(first.L);
        outline.push_back(first.H);
        outline.push_back(second.L);
        outline.push_back(second.H);
        outline.push_back(second.R);
        outline.push_back(0);
    }
    if(first.R>second.L&&first.R<second.R&&first.H==second.H)
    {
        outline.push_back(first.L);
        outline.push_back(first.H);
        outline.push_back(second.R);
        outline.push_back(0);
    }
    if(first.R>second.R&&first.H>=second.H)
    {
        outline.push_back(first.L);
        outline.push_back(first.H);
        outline.push_back(first.R);
        outline.push_back(0);
    }
    if(first.R>second.R&&first.H<second.H)
    {
        outline.push_back(first.L);
        outline.push_back(first.H);
        outline.push_back(second.L);
        outline.push_back(second.H);
        outline.push_back(second.R);
        outline.push_back(first.H);
        outline.push_back(first.R);
        outline.push_back(0);
    }
    return outline;
}
vector<int> SingleBuilding(Building one)
{
    vector<int> outline;
    outline.push_back(one.L);
    outline.push_back(one.H);
    outline.push_back(one.R);
    outline.push_back(0);
    return outline;
}
//合并两个轮廓线
vector<int> MergeTwoOutline(vector<int> L,vector<int> R)
{
    int cursorL=0;
    int cursorR=0;
    vector <int> outline;
    int currentHigh=0;
    while(cursorL<L.size()&&cursorR<R.size())
    {
        if(L[cursorL]<R[cursorR])
        {
            if(L[cursorL+1]>currentHigh)
           {
               outline.push_back(L[cursorL]);
               cursorL++;
               outline.push_back(L[cursorL]);
               cursorL++;
               currentHigh=L[cursorL-1];
               if(cursorL==L.size()){cursorL-1;}
           }
            if (L[cursorL+1]<currentHigh)
            {
               outline.push_back(L[cursorL]);
               cursorL++;
               if(L[cursorL]>R[cursorR-1])
               {
                   outline.push_back(L[cursorL]);
                   cursorL++;
                   currentHigh=L[cursorL-1];
               }
               else
               {
                   outline.push_back(R[cursorR-1]);
                   cursorL++;
                   currentHigh=R[cursorR-1];
               }
            }

           else
            cursorL+=2;
        }
         if(R[cursorR]<L[cursorL])
        {
            if(R[cursorR+1]>currentHigh)
            {
                outline.push_back(R[cursorR]);
                cursorR++;
                outline.push_back(R[cursorR]);
                cursorR++;
                currentHigh=R[cursorR-1];
                if(cursorR==R.size()){cursorR-1;}
            }
           if (R[cursorR+1]<currentHigh)
            {
               outline.push_back(R[cursorR]);
               cursorR++;
               if(R[cursorR]>L[cursorL-1])
               {
                   outline.push_back(R[cursorR]);
                   cursorR++;
                   currentHigh=R[cursorR-1];
               }
               else
               {
                   outline.push_back(L[cursorL-1]);
                   cursorR++;
                   currentHigh=L[cursorL-1];
               }
            }

            else
                cursorR+=2;

        }
        if(L[cursorL]==R[cursorR])
           {
            if(L[cursorL+1]>currentHigh||R[cursorR+1]>currentHigh)
                {
                 outline.push_back(L[cursorL]);
                 cursorL++;cursorR++;
                 if(L[cursorL]>=R[cursorR])   {outline.push_back(L[cursorL]);currentHigh=L[cursorL];}
                 else {outline.push_back(R[cursorR]);currentHigh=R[cursorR];}
                 cursorL++;cursorR++;
                }
            else {cursorL+=2;cursorR+=2;}
           }


    }
    if(cursorL==L.size()) for(int i=cursorR;i<R.size();i++) outline.push_back(R[i]);
    else for(int i=cursorL;i<L.size();i++) outline.push_back(L[cursorL]);
    return outline;
}
//总的分治函数
vector<int> MergeBuildings(Building building[],int leftIndex,int rightIndex)
{
    if(rightIndex-leftIndex<=1)
    {
        if(rightIndex-leftIndex==0)
            return SingleBuilding(building[rightIndex]);
        else
        return MergeTwo(building[leftIndex],building[rightIndex]);
        //递归终止条件
    }
    else
    {
        int middle=(leftIndex+rightIndex)/2;
        vector<int> left=MergeBuildings(building,leftIndex,middle);
        vector<int> right=MergeBuildings(building,middle+1,rightIndex);
        return MergeTwoOutline(left,right);
    }
}
int main()
{
    //读入并储存数据的部分
    ifstream in;
    string fileName="in.dat";
    in.open(fileName);
    if(!in){cout<<"打开文件出错";return 1;}
    int temp,number;
    in>>number;
    Building *building = new Building [number];
    int index=0;
    while(in>>temp)
    {
        building[index].L=temp;cout<<building[index].L;
        in>>temp;
        building[index].H=temp;cout<<building[index].H;
        in>>temp;
        building[index].R=temp;cout<<building[index].R;
        index++;
    }


    vector <int> mergeResult;
    mergeResult=MergeBuildings(building,0,number-1);
    if(mergeResult.empty())
        cout<<"It is empty";
    else{
        vector<int>::const_iterator itr,itre;
        itr=mergeResult.begin();
        itre=mergeResult.end();
        ofstream outfile("out.dat",ios::out);
        if(!outfile){cerr<<"open error"<<endl;return(-1);}
        do{
            cout<<*itr<<' ';
            outfile<<*itr<<' ';
            itr++;
        }while(itr!=itre);
        outfile.close();
    }
    cout<<endl;

    return 0;
}
