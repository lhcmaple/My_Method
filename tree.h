//
#pragma once

/********************
 * tree.h
 * 
 * exception int 
 * 
 * returned value -1:fail to remove
 *                 0:success
 * 
 * interface rawtree:rawtree(),void widecreate(DataType *,int),void predeepvisit(DataType *,int),
 *                   void lastdeepvisit(DataType *,int),void widevisit(DataType *,int),void clear(),
 *                   friend ostream &operator<<(ostream &,Node rawtree),Node *search(DataType),Node *insert(DataType,Node*=NULL)
 *           binarytree:binarytree(),bool isempty(),int length(),
 *                      int height(),void widecreate(DataType *,int),void clear(),
 *                      void predeepvisit(DataType *,int),void middeepvisit(DataType *,int),void lastdeepvisit(DataType *,int),
 *                      void widevisit(DataType *,int)
 *           charactertree:charactertree(),bool insert(char *,DataType),DataType *search(char *),
 *           binarysearchtree:binarysearchtree(),void insert(KeyType,DataType),DataType *search(KeyType),
 *                            int remove(KeyType),friend ostream &operator<<(ostream &,binarysearchtree)
 * 
 * author lhc
 * date 2017.4.14 finished
 *******************/

#include"header.h"
#include"linear_list.h"
#include"stack_queue.h"

namespace tree{
    template<typename T>class rawtree{
    private:
        typedef T DataType;
        struct Node{
            DataType data;
            linear_list::sequencelist<Node *>nodelist;
            Node(){}
            Node(DataType d):nodelist()
            {
                data=d;
            }
        };
        //
        Node *root;
        void clear_(Node *node)
        {
            for(int i=0;i<(node->nodelist).length();++i)
            {
                clear_((node->nodelist)[i]);
            }
            delete node;
        }
        void predeepvisit_(Node *node,DataType *dataarray,int num,int &i)
        {
            if(i==num)
                return;
            dataarray[i++]=node->data;
            for(int j=0;j<(node->nodelist).length();++j)
                predeepvisit_((node->nodelist)[j],dataarray,num,i);
        }
        void lastdeepvisit_(Node *node,DataType *dataarray,int num,int &i)
        {
            for(int j=0;j<(node->nodelist).length();++j)
                lastdeepvisit_((node->nodelist)[j],dataarray,num,i);
            if(i==num)
                return;
            dataarray[i++]=node->data;
        }
        void addbranch(Node *node,int n)
        {
            for(int i=0;i<n;++i)
                (node->nodelist).insert(NULL);
        }
        void clean(Node *node)
        {
            for(int i=0;i<(node->nodelist).length();++i)
            {
                if((node->nodelist)[i]!=NULL)
                {
                    clean((node->nodelist)[i]);
                }
                else
                {
                    (node->nodelist).del(i);
                    --i;
                }
            }
        }
        void copy(Node *node,Node *rnode)
        {
            for(int i=0;i<(rnode->nodelist).length();++i)
            {
                (node->nodelist).insert(new Node((rnode->nodelist)[i]->data));
                copy((node->nodelist)[i],(rnode->nodelist)[i]);
            }
        }
    public:
        rawtree(){root=NULL;}
        rawtree(const rawtree &rtree)
        {
            root=NULL;
            if(rtree.root!=NULL)
            {
                root=new Node((rtree.root)->data);
                copy(root,rtree.root);
            }
        }
        void widecreate(DataType *dataarray,int num)
        {
            int i=0;
            stack_queue::queue<Node *>q;
            root=new Node(dataarray[i++]);
            addbranch(root,rand()%4+2);
            q.enqueue(root);
            while(true)
            {
                Node *node=q.dequeue();
                int j;
                for(j=0;j<(node->nodelist).length();++j)
                {
                    if(i==num)
                        break;
                    (node->nodelist)[j]=new Node(dataarray[i++]);
                    addbranch((node->nodelist)[j],rand()%4+2);
                    q.enqueue((node->nodelist)[j]);
                }
                if(j<(node->nodelist).length())
                    break;
            }
            clean(root);
        }
        void predeepvisit(DataType *dataarray,int num)
        {
            int i=0;
            if(root!=NULL)
                predeepvisit_(root,dataarray,num,i);
        }
        void lastdeepvisit(DataType *dataarray,int num)
        {
            int i=0;
            if(root!=NULL)
                lastdeepvisit_(root,dataarray,num,i);
        }
        void widevisit(DataType *dataarray,int num)
        {
            if(root==NULL)
                return;
            stack_queue::queue<Node *>q;
            q.enqueue(root);
            int i=0;
            do
            {
                Node *node=q.dequeue();
                if(i==num)
                    return;
                dataarray[i++]=node->data;
                for(int j=0;j<(node->nodelist).length();++j)
                    q.enqueue((node->nodelist)[j]);
            }while(!q.isempty());
        }
        void clear()
        {
            if(root!=NULL)
                clear_(root);
        }
        friend ostream &operator<<(ostream &cout,Node *node)
        {
            cout<<"(";
            if(node!=NULL)
            {
                cout<<node->data;
                for(int i=0;i<(node->nodelist).length();++i)
                    cout<<(node->nodelist)[i];
            }
            cout<<")";
            return cout;
        }
        friend ostream &operator<<(ostream &cout,rawtree rtree)
        {
            cout<<rtree.root;
            cout<<endl;
            return cout;
        }
        Node *search(DataType data)
        {
            if(root==NULL)
                return NULL;
            stack_queue::queue<Node *>q;
            q.enqueue(root);
            while(!q.isempty())
            {
                Node *node=q.dequeue();
                if(node->data==data)
                    return node;
                for(int i=0;i<(node->nodelist).length();++i)
                    q.enqueue((node->nodelist)[i]);
            }
            return NULL;
        }
        Node *insert(DataType data,Node *parent=NULL)
        {
            if(parent==NULL)
            {
                root=new Node(data);
                return root;
            }
            else
            {
                (parent->nodelist).insert(new Node(data));
                return (parent->nodelist)[(parent->nodelist).length()-1];
            }
        }
        ~rawtree()
        {
            clear();
        }
    };

    template<typename T>class binarytree{
    private:
        typedef T DataType;
        struct Node{
            DataType data;
            Node *lnode;
            Node *rnode;
            Node(DataType d,Node *l=NULL,Node *r=NULL)
            {
                data=d;
                lnode=l;
                rnode=r;
            }
        };
        //
        Node *root;
        void clear_(Node *node)
        {
            if(node==NULL)
                return;
            clear_(node->lnode);
            clear_(node->rnode);
            delete node;
        }
        void predeepvisit_(DataType *dataarray,int &i,int num,Node *node)
        {
            if(node==NULL)
                return;
            if(i==num)
                return;
            dataarray[i++]=node->data;
            predeepvisit_(dataarray,i,num,node->lnode);
            predeepvisit_(dataarray,i,num,node->rnode);
        }
        void middeepvisit_(DataType *dataarray,int &i,int num,Node *node)
        {
            if(node==NULL)
                return;
            middeepvisit_(dataarray,i,num,node->lnode);
            if(i==num)
                return;
            dataarray[i++]=node->data;
            middeepvisit_(dataarray,i,num,node->rnode);
        }
        void lastdeepvisit_(DataType *dataarray,int &i,int num,Node *node)
        {
            if(node==NULL)
                return;
            lastdeepvisit_(dataarray,i,num,node->lnode);
            lastdeepvisit_(dataarray,i,num,node->rnode);
            if(i==num)
                return;
            dataarray[i++]=node->data;
        }
        void copy(Node *node,Node *bnode)
        {
            if(bnode->lnode!=NULL)
            {
                node->lnode=new Node(bnode->lnode->data);
                copy(node->lnode,bnode->lnode);
            }
            if(bnode->rnode!=NULL)
            {
                node->rnode=new Node(bnode->rnode->data);
                copy(node->rnode,bnode->rnode);
            }
        }
        void length_(Node *node,int &len)
        {
            if(node==NULL)
                return;
            ++len;
            length_(node->lnode,len);
            length_(node->rnode,len);
        }
        int height_(Node *node)
        {
            if(node==NULL)
                return 0;
            int lh=height_(node->lnode),rh=height_(node->rnode);
            return 1+(lh>rh?lh:rh);
        }
    public:
        binarytree()
        {
            root=NULL;
        }
        binarytree(const binarytree &btree)
        {
            root=NULL;
            if(btree.root!=NULL)
            {
                root=new Node(root->data);
                copy(root,btree.root);
            }
        }
        bool isempty()
        {
            return root==NULL;
        }
        int length()
        {
            int len=0;
            length_(root,len);
            return len;
        }
        int height()
        {
            return height_(root);
        }
        void widecreate(DataType *dataarray,int num)
        {
            if(root!=NULL)
                clear();
            int i=0;
            stack_queue::queue<Node *>q;
            root=new Node(dataarray[i++]);
            q.enqueue(root);
            while(true)
            {
                if(i==num)
                    break;
                Node *temp=q.dequeue();
                temp->lnode=new Node(dataarray[i++]);
                q.enqueue(temp->lnode);
                if(i==num)
                    break;
                temp->rnode=new Node(dataarray[i++]);
                q.enqueue(temp->rnode);
            }
        }
        void clear()
        {
            clear_(root);
            root=NULL;
        }
        void predeepvisit(DataType *dataarray,int num)
        {
            int i=0;
            predeepvisit_(dataarray,i,num,root);
        }
        void middeepvisit(DataType *dataarray,int num)
        {
            int i=0;
            middeepvisit_(dataarray,i,num,root);
        }
        void lastdeepvisit(DataType *dataarray,int num)
        {
            int i=0;
            lastdeepvisit_(dataarray,i,num,root);
        }
        void widevisit(DataType *dataarray,int num)
        {
            if(root==NULL)
                return;
            int i=0;
            stack_queue::queue<Node *>q;
            q.enqueue(root);
            while(!q.isempty())
            {
                Node *temp=q.dequeue();
                if(i==num)
                    break;
                dataarray[i++]=temp->data;
                if(temp->lnode!=NULL)
                    q.enqueue(temp->lnode);
                if(temp->rnode!=NULL)
                    q.enqueue(temp->rnode);
            }
        }
    #ifdef EXPAND
        void npredeepvisit(DataType *dataarray,int num)
        {
            if(root==NULL)
                return;
            stack_queue::stack<Node *> stk;
            stk.push(root);
            int i=0;
            do{
                Node *node=stk.pop();
                if(node->rnode!=NULL)
                    stk.push(node->rnode);
                if(node->lnode!=NULL)
                    stk.push(node->lnode);
                if(i==num)
                    return;
                dataarray[i++]=node->data;
            }while(!stk.isempty());
        }
        void nmiddeepvisit(DataType *dataarray,int num)
        {
            if(root==NULL)
                return;
            stack_queue::stack<Node *> stk;
            Node *node=root;
            int i=0;
            do{
                while(node!=NULL)
                {
                    stk.push(node);
                    node=node->lnode;
                }
                node=stk.pop();
                dataarray[i++]=node->data;
                if(i==num)
                    break;
                node=node->rnode;
                for(int i=0;i<10;++i)
                    cout<<dataarray[i]<<' ';
                cout<<endl;
            }while(node!=NULL||!stk.isempty());
        }
        void nlastdeepvisit(DataType *dataarray,int num)
        {
            stack_queue::stack<Node *>stk;
            Node *node=root;
            Node *noder;
            int i=0;
            while(node!=NULL||!stk.isempty())
            {
                while(node!=NULL)
                {
                    stk.push(node);
                    noder=node->rnode;
                    node=node->lnode;
                    if(node==NULL)
                        node=noder;
                }
                node=stk.pop();
                dataarray[i++]=node->data;
                if(i==num)
                    break;
                if(!stk.isempty()&&node==stk.top()->lnode)
                {
                    node=stk.top()->rnode;
                }
                else
                {
                    node=NULL;
                }
            }
        }
    #endif
        ~binarytree()
        {
            clear();
        }
    };

    template<typename T>class charactertree{
    private:
        typedef T DataType;
        struct Node{
            char ch;
            DataType data;
            bool isempty;
            Node *rnode;
            Node *lnode;
            Node(char c)
            {
                ch=c;
                isempty=true;
                rnode=NULL;
                lnode=NULL;
            }
            Node(char c,DataType d)
            {
                ch=c;
                data=d;
                isempty=false;
                rnode=NULL;
                lnode=NULL;
            }
        };
        //
        Node *root;
        void clear(Node *node)
        {
            if(node==NULL)
                return;
            clear(node->lnode);
            clear(node->rnode);
            delete node;
        }
    public:
        charactertree()
        {
            root=NULL;
        }
        bool insert(char *str,DataType data)
        {
            if(str==NULL||*str=='\0')
                return false;
            if(root==NULL)
            {
                root=new Node(*str);
            }
            Node *node=root;
            while(true)
            {
                if(node->ch==*str)
                    if(*(str+1)=='\0')
                    {
                        node->data=data;
                        node->isempty=false;
                        break;
                    }
                    else if(node->lnode==NULL)
                    {
                        while(*(++str)!='\0')
                        {
                            node->lnode=new Node(*str);
                            node=node->lnode;
                        }
                        node->data=data;
                        node->isempty=false;
                        break;
                    }
                    else
                    {
                        node=node->lnode;
                        ++str;
                    }
                else if(node->rnode==NULL)
                {
                    node->rnode=new Node(*str);
                    node=node->rnode;
                    while(*(++str)!='\0')
                    {
                        node->lnode=new Node(*str);
                        node=node->lnode;
                    }
                    node->data=data;
                    node->isempty=false;
                    break;
                }
                else
                    node=node->rnode;
            }
            return true;
        }
        DataType *search(char *str)
        {
            if(root==NULL||str==NULL||*str=='\0')
                return NULL;
            Node *node=root;
            while(true)
            {
                while(node!=NULL&&node->ch!=*str)
                    node=node->rnode;
                if(node==NULL)
                    return NULL;
                if(*(++str)=='\0')
                {
                    if(node->isempty)
                        return NULL;
                    return &(node->data);
                }
                node=node->lnode;
            }
        }
        ~charactertree()
        {
            clear(root);
        }
    };

    template<typename K,typename T>class binarysearchtree{
    private:
        typedef K KeyType;
        typedef T DataType;
        struct Node{
            KeyType key;
            DataType data;
            Node *lnode;
            Node *rnode;
            Node(KeyType k,DataType d)
            {
                key=k;
                data=d;
                lnode=NULL;
                rnode=NULL;
            }
        };
        //
        Node *root;
        void clear(Node *node)
        {
            if(node==NULL)
                return;
            clear(node->lnode);
            clear(node->rnode);
            delete node;
        }
        void copy(Node *node,Node *node1)
        {
            if(node1->lnode!=NULL)
            {
                node->lnode=new Node(node1->lnode->key,node1->lnode->data);
                copy(node->lnode,node1->lnode);
            }
            if(node1->rnode!=NULL)
            {
                node->rnode=new Node(node1->rnode->key,node1->rnode->data);
                copy(node->rnode,node1->rnode);
            }
        }
    public:
        binarysearchtree()
        {
            root=NULL;
        }
        binarysearchtree(const binarysearchtree &bstree)
        {
            root=NULL;
            if(bstree.root!=NULL)
            {
                root=new Node(bstree.root->key,bstree.root->data);
                copy(root,bstree.root);
            }
        }
        void insert(KeyType k,DataType d)
        {
            if(root==NULL)
            {
                root=new Node(k,d);
                return;
            }
            Node *node=root;
            while(true)
            {
                if(node->key==k)
                {
                    node->data=d;
                    break;
                }
                else if(node->key<k)
                {
                    if(node->rnode==NULL)
                    {
                        node->rnode=new Node(k,d);
                        break;
                    }
                    node=node->rnode;
                }
                else
                {
                    if(node->lnode==NULL)
                    {
                        node->lnode=new Node(k,d);
                        break;
                    }
                    node=node->lnode;
                }
            }
        }
        DataType *search(KeyType k)
        {
            Node *node=root;
            while(node!=NULL)
            {
                if(node->key==k)
                    return &(node->data);
                node=node->key>k?node->lnode:node->rnode;
            }
            return NULL;
        }
        int remove(KeyType k)
        {
            if(root==NULL)
                return -1;
            if(root->key==k)
            {
                Node *node=root;
                if(root->lnode==NULL)
                    root=root->rnode;
                else
                {
                    Node *node1=root->lnode;
                    while(node1->rnode!=NULL)
                        node1=node1->rnode;
                    node1->rnode=root->rnode;
                    root=root->lnode;
                }
                delete node;
                return 0;
            }
            Node *pnode=root,*node=root->key>k?root->lnode:root->rnode;
            while(node!=NULL&&node->key!=k)
            {
                pnode=node;
                node=node->key>k?node->lnode:node->rnode;
            }
            if(node==NULL)
                return -1;
            if(node->lnode==NULL)
            {
                if(pnode->lnode==node)
                    pnode->lnode=node->rnode;
                else
                    pnode->rnode=node->rnode;
                delete node;
                return 0;
            }
            Node *node1=node->lnode;
            while(node1->rnode!=NULL)
                node1=node1->rnode;
            node1->rnode=node->rnode;
            if(pnode->lnode==node)
                pnode->lnode=node->lnode;
            else
                pnode->rnode=node->lnode;
            delete node;
            return 0;
        }
        friend ostream &operator<<(ostream &cout,Node *node)
        {
            if(node!=NULL)
            {
                cout<<node->lnode;
                cout<<"("<<node->key<<","<<node->data<<")"<<" ";
                cout<<node->rnode;
            }
            return cout;
        }
        friend ostream &operator<<(ostream &cout,binarysearchtree bstree)
        {
            return cout<<(bstree.root);
        }
        ~binarysearchtree()
        {
            clear(root);
        }
    };
}