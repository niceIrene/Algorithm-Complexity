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
};//���ڴ����
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
        //�ж��Ƿ�Ϊ�յ�
        if(pre.turn<3)//ֻ��ת�����С��3�ĵ�ſ��Խ��������ĵ����
        {
            for(int i=pre.x+1;i<x;i++)//ˮƽ����
               {
                   if(Map[i][pre.y]==0||Map[i][pre.y]==Map[terminal.x][terminal.y])
                {
                    temp.x=i;
                    temp.y=pre.y;
                    temp.turn=pre.turn+1;
                    //Map[i][pre.y]=-1;//��ֹ���ʹ����ٴ����,�������������������޷������ʱ�临�Ӷȵ�����
                    q.push(temp);
                }
                else break;
               }
            for(int i=pre.x-1;i>0;i--)//ˮƽ����
               {
                   if(Map[i][pre.y]==0||Map[i][pre.y]==Map[terminal.x][terminal.y])
                {
                    temp.x=i;
                    temp.y=pre.y;
                    temp.turn=pre.turn+1;
                    //Map[i][pre.y]=-1;//��ֹ���ʹ����ٴ����,�������������������޷������ʱ�临�Ӷȵ�����
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
                    //Map[pre.x][j]=-1;//��ֹ���ʹ����ٴ����,�������������������޷������ʱ�临�Ӷȵ�����
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
                    //Map[pre.x][j]=-1;//��ֹ���ʹ����ٴ����,�������������������޷������ʱ�临�Ӷȵ�����
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
    //��ͼ�����ɲ���
    ifstream in;
    string fileName="in.dat";
    in.open(fileName);
    if(!in){cout<<"���ļ�����";return 1;}
    int temp,x,y;
    in>>x;
    in>>y;//����x��y��
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
