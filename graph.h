//
#pragma once

/********************
 * graph.h
 * 
 * exception int 
 * 
 * returned vlaue -1:cross the border
 * 
 * interface graph_mat:graph_mat(int),void create(VertexType *,EdgeType **),int widevisit(int),
 *                     int deepvisit(int),int mintree_prim(int,tree::rawtree<T> *),int mintree_kruskal(int),
 *                     void minpath_dijkstra(int),void minpath_floyd(int)
 *           graph_list:graphlist(int),void create(VertexType *,EdgeType **),bool getaov(int *=NULL),
 *                      void getaoe()
 * 
 * author lhc
 * date 2018.4.14 finished
 *******************/

#include"header.h"
#include"stack_queue.h"
#include"tree.h"
//#define DEBUG

namespace graph
{
    template<typename T>struct Vertex{
        T data;
        bool isvisited;
        int set;
        //
        Vertex()
        {
            isvisited=false;
        }
        Vertex(T d)
        {
            isvisited=false;
            data=d;
        }
        friend ostream &operator<<(ostream &cout,struct Vertex v)
        {
            cout<<v.data;
            return cout;
        }
        bool operator==(Vertex v)
        {
            return data==v.data;
        }
    };

    template<typename T>struct Edge{
        T einfo;
        T e;
        T l;
        bool isimportant;
        //
        Edge(T info)
        {
            einfo=info;
        }
        Edge(){}
    };

    template<typename T,typename D>class graph_mat{
    private:
        typedef T VertexType;
        typedef D EdgeType;
        //
        int num;
        VertexType *vexs;
        EdgeType **edges;
        void init()
        {
            for(int i=0;i<num;++i)
            {
                vexs[i].isvisited=false;
                vexs[i].set=i;
            }
        }
    public:
        graph_mat(int n)
        {
            num=n;
            vexs=new VertexType[n];
            edges=new EdgeType*[n];
            for(int i=0;i<n;++i)
                edges[i]=new EdgeType[n];
        }
        graph_mat(const graph_mat &g)
        {
            num=g.num;
            vexs=new VertexType[num];
            edges=new EdgeType*[num];
            for(int i=0;i<num;++i)
            {   
                edges[i]=new EdgeType[num];
                memcpy(edges[i],g.edges[i],num*sizeof(EdgeType));
            }
            memcpy(vexs,g.vexs,num*sizeof(VertexType));
        }
        void create(VertexType *v,EdgeType **e)
        {
            for(int i=0;i<num;++i)
            {
                vexs[i]=v[i];
                for(int j=0;j<num;++j)
                    edges[i][j]=e[i][j];
            }
        }
        int widevisit(int vpos)
        {
            if(vpos<0||vpos>=num)
                return -1;
            init();
            stack_queue::queue<int>q;
            q.enqueue(vpos);
            vexs[vpos].isvisited=true;
            while(!q.isempty())
            {
                vpos=q.dequeue();
                for(int i=0;i<num;++i)
                    if(edges[vpos][i].einfo>0&&vexs[i].isvisited==false)
                    {
                        q.enqueue(i);
                        vexs[i].isvisited=true;
                    }
                cout<<vexs[vpos]<<" ";
            }
            cout<<endl;
            return 0;
        }
        int deepvisit(int vpos)
        {
            if(vpos<0||vpos>=num)
                return -1;
            cout<<vexs[vpos]<<" ";
            vexs[vpos].isvisited=true;
            for(int i=0;i<num;++i)
                if(edges[vpos][i].einfo>0&&vexs[i].isvisited==false)
                    deepvisit(i);
            return 0;
        }
        int mintree_prim(int infinite,tree::rawtree<T> *rtree)
        {
            struct MST{
                int prepos;
                int pos;
                EdgeType value;
            }mst[num-1];
            int minsum=0;
            for(int i=1;i<num;++i)
            {
                mst[i-1].prepos=0;
                mst[i-1].pos=i;
                mst[i-1].value=edges[0][i];
            }
            rtree->insert(vexs[0]);
            for(int i=0;i<num-1;++i)
            {
                int min=i;
                for(int j=i+1;j<num-1;++j)
                    if(mst[j].value.einfo<mst[min].value.einfo)
                        min=j;
                if(min!=i)
                {
                    MST m=mst[i];
                    mst[i]=mst[min];
                    mst[min]=m;
                }
                rtree->insert(vexs[mst[i].pos],rtree->search(vexs[mst[i].prepos]));
                minsum+=mst[i].value.einfo;
                for(int k=i+1;k<num-1;++k)
                    if(edges[mst[i].pos][mst[k].pos].einfo<mst[k].value.einfo)
                    {
                        mst[k].prepos=mst[i].pos;
                        mst[k].value=edges[mst[i].pos][mst[k].pos];
                    }
            }
            return minsum;
        }
        int mintree_kruskal(int infinite)
        {
            int minsum=0;
            struct MST{
                int prepos;
                int pos;
                EdgeType value;
            };
            MST *mst=new MST[num*num];
            for(int i=0;i<num;++i)
                for(int j=0;j<num;++j)
                {
                    mst[i*num+j].prepos=i;
                    mst[i*num+j].pos=j;
                    mst[i*num+j].value=edges[i][j];
                }
            for(int i=0;i<num*num-1;++i)
            {
                int temp=i;
                for(int j=i+1;j<num*num;++j)
                    if(mst[j].value.einfo<mst[temp].value.einfo)
                        temp=j;
                if(temp!=i)
                {
                    MST m=mst[i];
                    mst[i]=mst[temp];
                    mst[temp]=m;
                }
            }
            init();
            for(int i=0;i<num*num;++i)
                cout<<mst[i].prepos<<","<<mst[i].pos<<":"<<mst[i].value.einfo<<endl;
            int count=num-1;
            int i=0;
            while(true)
            {
                if(vexs[mst[i].prepos].set!=vexs[mst[i].pos].set)
                {
                    for(int j=0;j<num;++j)
                        if(vexs[j].set==vexs[mst[i].prepos].set)
                            vexs[j].set=vexs[mst[i].pos].set;
                    minsum+=mst[i].value.einfo;
                    cout<<count<<endl;
                    if(--count==0)
                        return minsum;
                }
                ++i;
                cin.get();
            }
            delete[] mst;
        }
        void minpath_dijkstra(int start)
        {
            struct MinDistance{
                int prepos;
                int pos;
                int distance;
            }mindist[num-1];
            for(int i=0,j=0;i<num-1;++i,++j)
            {
                if(j==start)
                    ++j;
                mindist[i].prepos=start;
                mindist[i].pos=j;
                mindist[i].distance=edges[start][j].einfo;
            }
            for(int i=0;i<num-1;++i)
            {
                int temp=i;
                for(int j=i+1;j<num-1;++j)
                    if(mindist[j].distance<mindist[temp].distance)
                        temp=j;
                if(temp!=i)
                {
                    MinDistance m=mindist[i];
                    mindist[i]=mindist[temp];
                    mindist[temp]=m;
                }
                for(int j=i+1;j<num-1;++j)
                {
                    if(mindist[i].distance+edges[mindist[i].pos][mindist[j].pos].einfo<mindist[j].distance)
                    {
                        mindist[j].distance=mindist[i].distance+edges[mindist[i].pos][mindist[j].pos].einfo;
                        mindist[j].prepos=mindist[i].pos;
                    }
                }
            }
            for(int i=0;i<num-1;++i)
            {
                int temp=i;
                while(mindist[temp].prepos!=start)
                {
                    cout<<mindist[temp].pos<<"<-";
                    for(int i=0;i<num-1;++i)
                        if(mindist[i].pos==mindist[temp].prepos)
                        {
                            temp=i;
                            break;
                        }
                }
                cout<<mindist[temp].pos<<"<-"<<mindist[temp].prepos<<":"<<mindist[i].distance<<endl;
            }
        }
        void minpath_floyd(int infinite)
        {
            int **mindist=new int*[num],**nextpos=new int*[num];
            for(int i=0;i<num;++i)
            {
                mindist[i]=new int[num];
                nextpos[i]=new int[num];
            }
            for(int i=0;i<num;++i)
                for(int j=0;j<num;++j)
                {
                    if(edges[i][j].einfo!=infinite)
                        nextpos[i][j]=j;
                    else
                        nextpos[i][j]=i==j?i:-1;
                    mindist[i][j]=i==j?0:edges[i][j].einfo;
                }
            for(int k=0;k<num;++k)
                for(int i=0;i<num;++i)
                    for(int j=0;j<num;++j)
                    {
                        if(mindist[i][k]==infinite||mindist[k][j]==infinite)
                            continue;
                        if(mindist[i][j]>mindist[i][k]+mindist[k][j])
                        {
                            mindist[i][j]=mindist[i][k]+mindist[k][j];
                            nextpos[i][j]=nextpos[i][k];
                        }
                    }
            for(int i=0;i<num;++i)
            {
                for(int j=0;j<num;++j)
                    cout<<setw(2)<<mindist[i][j]<<" ";
                cout<<endl;
            }
            cout<<endl;
            for(int i=0;i<num;++i)
            {
                for(int j=0;j<num;++j)
                    cout<<setw(2)<<nextpos[i][j]<<" ";
                cout<<endl;
            }
            for(int i=0;i<num;++i)
            {
                delete[] mindist[i];
                delete[] nextpos[i];
            }
            delete[] nextpos;
            delete[] mindist;
        }
        ~graph_mat()
        {
            delete[] vexs;
            for(int i=0;i<num;++i)
                delete[] edges[i];
            delete[] edges;
        }
    };

    template<typename T,typename D>class graph_list{
    private:
        typedef T VertexType;
        typedef D EdgeType;
        struct ENode{
            EdgeType edge;
            int vex;
            ENode *penode;
            //
            ENode(EdgeType e)
            {
                edge=e;
                penode=NULL;
            }
        };
        struct VNode{
            VertexType vertex;
            int indegree;
            ENode *penode;
            //
            VNode()
            {
                penode=NULL;
            }
        };
        //
        int num;
        VNode *vexs;
        void del(ENode *enode)
        {
            if(enode==NULL)
                return;
            del(enode->penode);
            delete enode;
        }
        void init_indegree()
        {
            for(int i=0;i<num;++i)
                vexs[i].indegree=0;
            for(int i=0;i<num;++i)
            {
                ENode *node=vexs[i].penode;
                while(node!=NULL)
                {
                    ++vexs[node->vex].indegree;
                    node=node->penode;
                }
            }
        }
    public:
        graph_list(int n)
        {
            num=n;
            vexs=new VNode[n];
        }
        graph_list(const graph_list &g)
        {
            num=g.num;
            vexs=new VNode[num];
            memcpy(vexs,g.vexs,num*sizeof(VNode));
            for(int i=0;i<num;++i)
            {
                if(g.vexs[i].penode)
                {
                    vexs[i].penode=new ENode(g.vexs[i].penode->edge);
                    ENode *node1=vexs[i].penode,*node2=g.vexs[i].penode;
                    while(node2->penode)
                    {
                        node1->penode=new ENode(node2->penode->edge);
                        node1=node1->penode;
                        node2=node2->penode;
                    }
                }
                else
                {
                    vexs[i].penode=NULL;
                }
            }
        }
        void create(VertexType *v,EdgeType **e)
        {
            for(int i=0;i<num;++i)
            {
                vexs[i].vertex=v[i];
                del(vexs[i].penode);
                vexs[i].penode=NULL;
                ENode *node;
                int flag=true;
                for(int j=0;j<num;++j)
                {
                    if(e[i][j].einfo>0)
                        if(flag)
                        {
                            vexs[i].penode=new ENode(e[i][j]);
                            vexs[i].penode->vex=j;
                            node=vexs[i].penode;
                            flag=false;
                        }
                        else
                        {
                            node->penode=new ENode(e[i][j]);
                            node->penode->vex=j;
                            node=node->penode;
                        }
                }
            }
        }
        bool getaov(int *topo=NULL)
        {
            int count=0;
            init_indegree();
            int now=-1;
            while(true)
            {
                for(int i=0;i<num;++i)
                {
                    if(vexs[i].indegree==0)
                    {
                        vexs[i].indegree=now;
                        now=i+1;
                    }
                }
                if(now==-1)
                    break;
                ENode *node=vexs[now-1].penode;
                while(node!=NULL)
                {
                    --vexs[node->vex].indegree;
                    node=node->penode;
                }
                if(topo!=NULL)
                    topo[count]=now-1;
                ++count;
                if(topo==NULL)
                    cout<<"->"<<vexs[now-1].vertex;
                now=vexs[now-1].indegree;
            }
            if(topo==NULL)
                cout<<endl;
            return count==num;
        }
        void getaoe()
        {
            int *topo=new int[num];
            if(!getaov(topo))
                return;
            int *ee=new int[num],*le=new int[num];
            //ee
            for(int i=0;i<num;++i)
            {
                ee[topo[i]]=0;
                for(int j=0;j<i;++j)
                {
                    ENode *node=vexs[topo[j]].penode;
                    while(node!=NULL)
                    {
                        if(node->vex==topo[i])
                        {
                            ee[topo[i]]=ee[topo[i]]>ee[topo[j]]+node->edge.einfo?ee[topo[i]]:ee[topo[j]]+node->edge.einfo;
                            break;
                        }
                        node=node->penode;
                    }
                }
            }
            //le
            for(int i=num-1;i>=0;--i)
            {
                le[topo[i]]=ee[topo[num-1]];
                ENode *node=vexs[topo[i]].penode;
                while(node!=NULL)
                {
                    le[topo[i]]=le[topo[i]]<le[node->vex]-node->edge.einfo?le[topo[i]]:le[node->vex]-node->edge.einfo;
                    node=node->penode;
                }
            }
            //l
            //e
            for(int i=0;i<num;++i)
            {
                ENode *node=vexs[i].penode;
                while(node!=NULL)
                {
                    node->edge.e=ee[i];
                    node->edge.l=le[node->vex]-node->edge.einfo;
                    node->edge.isimportant=node->edge.l-node->edge.e==0;
                    if(node->edge.isimportant)
                        cout<<i<<"->"<<node->vex<<endl;
                    node=node->penode;
                }
            }
            delete[]topo;
            delete[]ee;
            delete[]le;
        }
        ~graph_list()
        {
            for(int i=0;i<num;++i)
                del(vexs[i].penode);
            delete[] vexs;
        }
    };
}