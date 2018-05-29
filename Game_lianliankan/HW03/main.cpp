#include <iostream>
#include<fstream>
#include<string>
#include<queue>
using namespace std;
class P
{
    public:
    int x,y,turn;
    void operator=(P & p)
    {
        x=p.x;
        y=p.y;
        turn=p.turn;
    }
};//用于储存点
bool bfs(int **Map,P start,P terminal,int x,int y)
{
    queue <P> q;
    P pre,temp;
    q.push(start);
    while(!q.empty())
    {
        pre=q.front();
        q.pop();
        if (pre.x==terminal.x&&pre.y==terminal.y)return true;
        //判断是否为终点
        if(pre.turn<3)//只有转弯次数小于3的点才可以将接下来的点入队
        {
            for(int i=pre.x+1;i<x;i++)//水平方向
               {
                   if(Map[i][pre.y]==0||Map[i][pre.y]==Map[terminal.x][terminal.y])
                {
                    temp.x=i;
                    temp.y=pre.y;
                    temp.turn=pre.turn+1;
                    //Map[i][pre.y]=-1;//防止访问过的再次入队,但是这样会引发错误，无法避免的时间复杂度的上升
                    q.push(temp);
                }
                else break;
               }
            for(int i=pre.x-1;i>0;i--)//水平方向
               {
                   if(Map[i][pre.y]==0||Map[i][pre.y]==Map[terminal.x][terminal.y])
                {
                    temp.x=i;
                    temp.y=pre.y;
                    temp.turn=pre.turn+1;
                    //Map[i][pre.y]=-1;//防止访问过的再次入队,但是这样会引发错误，无法避免的时间复杂度的上升
                    q.push(temp);
                }
                else break;
               }

            for(int j=pre.y+1;j<y;j++)
            {
                if(Map[pre.x][j]==0||Map[pre.x][j]==Map[terminal.x][terminal.y])
                {
                    temp.x=pre.x;
                    temp.y=j;
                    temp.turn=pre.turn+1;
                    //Map[pre.x][j]=-1;//防止访问过的再次入队,但是这样会引发错误，无法避免的时间复杂度的上升
                    q.push(temp);
                }
                else break;
            }
            for(int j=pre.y-1;j>0;j--)
            {
                if(Map[pre.x][j]==0||Map[pre.x][j]==Map[terminal.x][terminal.y])
                {
                    temp.x=pre.x;
                    temp.y=j;
                    temp.turn=pre.turn+1;
                    //Map[pre.x][j]=-1;//防止访问过的再次入队,但是这样会引发错误，无法避免的时间复杂度的上升
                    q.push(temp);
                }
                else break;
            }

        }

    }
    return false;


}
int main()
{
    //地图的生成部分
    ifstream in;
    string fileName="in.dat";
    in.open(fileName);
    if(!in){cout<<"打开文件出错";return 1;}
    int temp,x,y;
    in>>x;
    in>>y;//输入x行y列
    int** Map;
    Map=new int*[x];
    for(int i=0;i<x;i++)
        Map[i]=new int[y];
    P start,terminal;
    in>>start.x;
    in>>start.y;
    in>>terminal.x;
    in>>terminal.y;
    start.turn=0;
    terminal.turn=0;

    while(in>>temp)
    {
       for(int i=0;i<x;i++)
        for(int j=0;j<y;j++)
       {
           Map[i][j]=temp;
           in>>temp;
       }
    }
    for(int i=0;i<x;i++)
    {
        for(int j=0;j<y;j++) cout<<Map[i][j]<<' ';
        cout<<endl;
    }
    cout<<"The start point is:("<<start.x<<","<<start.y<<")->"<<Map[start.x][start.y]<<endl;
    cout<<"The terminal point is:("<<terminal.x<<","<<terminal.y<<")->"<<Map[terminal.x][terminal.y]<<endl;
    bool flag=bfs(Map,start,terminal,x,y);
    if(flag)
        cout<<"Yes we find it!"<<endl;
    else cout<<"Sorry for not finding it"<<endl;
    return 0;
}
