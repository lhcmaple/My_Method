//
#pragma once

/********************
 * linear_list.h
 * 
 * exception int -1:cross the border
 *               1:wrong parameters
 *               2:not matching
 * 
 * returned value -1:fail to insert
 *                0:success
 *                1:empty
 *                2:cross the border
 *                3:fail to delete
 * 
 * interface sequencelist:sequencelist(),int insert(DataType,int=-1),
 *                        DataType &operator[](int),int del(int=-1),
 *                        int length(),bool isempty()
 *           singlelinkedlist:singlelinkedlist(),int length(),
 *                            void push(DataType),Node *searchv(DataType),
 *                            Node *searchpos(int),DataType &operator[](int),
 *                            int preinsertp(DataType,Node*),int nextinsertp(DataType,Node*),
 *                            int insertpos(DataType,int),int delp(Node*),
 *                            int delpos(int)
 *           doublelinkedlist:doublelinkedlist(),void push(DataType),
 *                            Node *searchv(DataType),Node *searchpos(int),
 *                            DataType &operator[](int),int length(),int preinsertp(DataType,Node*),
 *                            int nextinsertp(DataType,Node*),int insertpos(DataType,int),
 *                            int delp(Node*),int delpos(int)
 *           matrix:matrix(int=4,int=4),matrix operator+(const matrix &),
 *                  matrix operator-(const matrix &),matrix operator*(const matrix &),
 *                  DataType *operator[](int),void print(int)
 *           generallist:generallist(),void push(DataType),void push(generallist *),
 *                       friend ostream &operator<<(ostream &,generallist),
 * 
 * author lhc
 * date 2018.3.24 finished
 *******************/

#include"header.h"

namespace linear_list
{
    template<typename T>class sequencelist{
    private:
        typedef T DataType;
        typedef int ListLen;
        typedef int ListNum;
        //
        DataType *list;
        ListLen len;
        ListNum num;
        void excopy()
        {
            DataType *temp=list;
            len*=2;
            list=new DataType[len];
            memcpy(list,temp,num*sizeof(DataType));
            delete[] temp;
        }
    public:
        sequencelist()
        {
            len=4;
            list=new DataType[len];
            num=0;
        }
        sequencelist(const sequencelist &slist)
        {
            len=slist.len;
            num=slist.num;
            list=new DataType[len];
            memcpy(list,slist.list,num*sizeof(DataType));
        }
        sequencelist& operator=(const sequencelist &slist)
        {
            delete[] list;
            num=slist.num;
            len=slist.len;
            list=new DataType[len];
            memcpy(list,slist.list,num*sizeof(DataType));
            return *this;
        }
        int insert(DataType data,int position=-1)
        {
            if(num==len-1) excopy();
            if(position==-1)
            {
                ++num;
                list[num-1]=data;
            }
            else if(position<0||position>num)
                return -1;
            else
            {
                for(int i=num;i>position;--i)
                {
                    list[i]=list[i-1];
                }
                list[position]=data;
                ++num;
            }
            return 0;
        }
        DataType &operator[](int position)
        {
            if(position<0||position>=num)
                throw -1;
            else
                return list[position];
        }
        int del(int position=-1)
        {
            if(num==0)
                return 1;
            if(position==-1)
                --num;
            else if(position<0||position>=num)
                return 2;
            else
            {
                for(int i=position;i<num-1;++i)
                {
                    list[i]=list[i+1];
                }
                --num;
            }
            return 0;
        }
        int length()
        {
            return num;
        }
        bool isempty()
        {
            return num==0;
        }
        ~sequencelist()
        {
            delete[] list;
        }
    };

    template<typename T>class singlelinkedlist{
    private:
        typedef T DataType;
        struct Node{
            DataType data;
            Node *pnode;
            Node(DataType d)
            {
                data=d;
                pnode=NULL;
            }
        };
        //
        Node *head;
    public:
        singlelinkedlist()
        {
            head=NULL;
        }
        singlelinkedlist(const singlelinkedlist &slist)
        {
            if(slist.head==NULL)
                head=NULL;
            else
            {
                Node *temp=slist.head;
                head=new Node(temp->data);
                Node *p=head;
                while(temp->pnode!=NULL)
                {
                    temp=temp->pnode;
                    p->pnode=new Node(temp->data);
                    p=p->pnode;
                }
            }
        }
        int length()
        {
            int counter=0;
            Node *temp=head;
            while(temp!=NULL)
            {
                ++counter;
                temp=temp->pnode;
            }
            return counter;
        }
        void push(DataType data)
        {
            if(head==NULL)
            {
                head=new Node(data);
            }
            else
            {
                Node *temp=head;
                while(temp->pnode!=NULL)
                    temp=temp->pnode;
                temp->pnode=new Node(data);
            }
        }
        Node *searchv(DataType data)
        {
            Node *temp=head;
            while(temp!=NULL)
            {
                if(data==temp->data)
                    return temp;
                temp=temp->pnode;
            }
            return NULL;
        }
        Node *searchpos(int position)
        {
            if(position<0||position>=length())
                return NULL;
            Node *temp=head;
            for(int i=0;i<position;++i)
            {
                temp=temp->pnode;
            }
            return temp;
        }
        DataType &operator[](int position)
        {
            Node *temp=searchpos(position);
            if(temp==NULL)
                throw -1;
            return temp->data;
        }
        int preinsertp(DataType data,Node *p)
        {
            if(p==NULL||head==NULL)
                return -1;
            Node *temp=head;
            if(head==p)
            {
                head=new Node(data);
                head->pnode=temp;
                return 0;
            }
            else
            {
                while(temp->pnode!=p&&temp->pnode!=NULL)
                    temp=temp->pnode;
                if(temp->pnode!=NULL)
                {
                    temp->pnode=new Node(data);
                    temp->pnode->pnode=p;
                    return 0;
                }
            }
            return -1;
        }
        int nextinsertp(DataType data,Node *p)
        {
            if(p==NULL)
                return -1;
            Node *temp=p->pnode;
            p->pnode=new Node(data);
            p->pnode->pnode=temp;
            return 0;
        }
        int insertpos(DataType data,int position)
        {
            Node *temp=searchpos(position);
            if(temp==NULL)
                return -1;
            if(position==0)
            {
                head=new Node(data);
                head->pnode=temp;
            }
            else
            {
                Node *p=searchpos(position-1);
                p->pnode=new Node(data);
                p->pnode->pnode=temp;
            }
            return 0;
        }
        int delp(Node *p)
        {
            if(p==NULL)
                return 3;
            if(p==head)
            {
                head=head->pnode;
                delete p;
                return 0;
            }
            else
            {
                Node *temp=head;
                while(temp->pnode!=p&&temp->pnode!=NULL)
                    temp=temp->pnode;
                if(temp->pnode!=NULL)
                {
                    temp->pnode=p->pnode;
                    delete p;
                    return 0;
                }
            }
            return 3;
        }
        int delpos(int position)
        {
            if(position<0||position>=length())
                return 3;
            if(position==0)
            {
                Node *temp=head;
                head=head->pnode;
                delete temp;
            }
            else
            {
                Node *temp=searchpos(position-1),*p=searchpos(position);
                temp->pnode=p->pnode;
                delete p;
            }
            return 0;
        }
        ~singlelinkedlist()
        {
            Node *temp;
            while(head!=NULL)
            {
                temp=head;
                head=head->pnode;
                delete temp;
            }
        }
    };

    template<typename T>class doublelinkedlist{
    private:
        typedef T DataType;
        struct Node{
            DataType data;
            Node *prenode;
            Node *nextnode;
            Node(DataType d)
            {
                data=d;
                prenode=NULL;
                nextnode=NULL;
            }
        };
        //
        Node *head;
    public:
        doublelinkedlist()
        {
            head=NULL;
        }
        doublelinkedlist(const doublelinkedlist &dlist)
        {
            if(dlist.head==NULL)
                head=NULL;
            else
            {
                Node *temp=dlist.head;
                head=new Node(temp->data);
                head->nextnode=head;
                head->prenode=head;
                while(temp->nextnode!=dlist.head)
                {
                    temp=temp->nextnode;
                    push(temp->data);
                }
            }
        }
        void push(DataType data)
        {
            if(head==NULL)
            {
                head=new Node(data);
                head->prenode=head;
                head->nextnode=head;
            }
            else
            {
                Node *temp=head;
                while(temp->nextnode!=head)
                    temp=temp->nextnode;
                temp->nextnode=new Node(data);
                temp->nextnode->nextnode=head;
                head->prenode=temp->nextnode;
                temp->nextnode->prenode=temp;
            }
        }
        Node *searchv(DataType data)
        {
            if(head==NULL)
                return NULL;
            Node *temp=head;
            do{
                if(temp->data==data)
                    return temp;
            }while((temp=temp->nextnode)!=head);
        }
        Node *searchpos(int position)
        {
            if(position<0||position>=length())
                return NULL;
            Node *temp=head;
            for(int i=0;i<position;++i)
                temp=temp->nextnode;
            return temp;
        }
        DataType &operator[](int position)
        {
            Node *temp=searchpos(position);
            if(temp==NULL)
                throw -1;
            return temp->data;
        }
        int length()
        {
            if(head==NULL)
                return 0;
            Node *temp=head;
            int len=0;
            do{
                ++len;
                temp=temp->nextnode;
            }while(temp!=head);
            return len;
        }
        int preinsertp(DataType data,Node *p)
        {
            if(p==NULL||head==NULL)
                return -1;
            Node *temp=head;
            do{
                if(temp==p)
                {
                    p=new Node(data);
                    p->prenode=temp->prenode;
                    temp->prenode=p;
                    p->prenode->nextnode=p;
                    p->nextnode=temp;
                    return 0;
                }
                temp=temp->nextnode;
            }while(temp!=head);
            return -1;
        }
        int nextinsertp(DataType data,Node *p)
        {
            if(p==NULL||head==NULL)
                return -1;
            Node *temp=head;
            do{
                if(temp==p)
                {
                    p=new Node(data);
                    p->nextnode=temp->nextnode;
                    temp->nextnode=p;
                    p->nextnode->prenode=p;
                    p->prenode=temp;
                    return 0;
                }
                temp=temp->nextnode;
            }while(temp!=head);
            return -1;
        }
        int insertpos(DataType data,int position)
        {
            if(position<0||position>=length())
                return -1;
            if(position==0)
            {
                Node *temp=head;
                head=new Node(data);
                head->prenode=temp->prenode;
                temp->prenode=head;
                head->prenode->nextnode=head;
                head->nextnode=temp;
            }
            else
            {
                preinsertp(data,searchpos(position));
            }
            return 0;
        }
        int delp(Node *p)
        {
            if(p==NULL||head==NULL)
                return 3;
            Node *temp=head;
            if(p==head)
            {
                if(length()==1)
                {
                    head=NULL;
                    delete p;
                }
                else
                {
                    head->prenode=temp->prenode;
                    temp->prenode->nextnode=head;
                    delete temp;
                }
                return 0;
            }
            else
            {
                do{
                    if(temp==p)
                    {
                        p=temp->prenode;
                        p->nextnode=temp->nextnode;
                        temp->nextnode->prenode=p;
                        delete temp;
                        return 0;
                    }
                    temp=temp->nextnode;
                }while(temp!=head);
            }
            return 3;
        }
        int delpos(int position)
        {
            if(delp(searchpos(position)))
                return 3;
            return 0;
        }
        ~doublelinkedlist()
        {
            if(head!=NULL)
            {
                Node *temp=head;
                Node *p;
                do{
                    p=temp;
                    temp=temp->nextnode;
                    delete p;
                }while(temp!=head);
            }
        }
    };

    template<typename T>class matrix{
    private:
        typedef T DataType;
        //
        DataType** mat;
        int row;
        int column;
    public:
        matrix(int row=4,int column=4)
        {
            this->row=row;
            this->column=column;
            if(row<=0||column<=0)
                throw 1;
            mat=new DataType *[row];
            for(int i=0;i<row;++i)
                mat[i]=new DataType[column];
        }
        matrix(const matrix &matx)
        {
            row=matx.row;
            column=matx.column;
            mat=new DataType *[row];
            for(int i=0;i<row;++i)
                mat[i]=new DataType[column];
            for(int i=0;i<row;++i)
                for(int j=0;j<column;++j)
                    mat[i][j]=matx.mat[i][j];
        }
        matrix operator+(const matrix &matx)
        {
            if(matx.row!=row||matx.column!=column)
                throw 2;
            matrix<DataType>matx_(row,column);
            for(int i=0;i<row;++i)
                for(int j=0;j<column;++j)
                    matx_.mat[i][j]=mat[i][j]+matx.mat[i][j];
            return matx_;
        }
        matrix operator-(const matrix &matx)
        {
            if(matx.row!=row||matx.column!=column)
                throw 2;
            matrix<DataType>matx_(row,column);
            for(int i=0;i<row;++i)
                for(int j=0;j<column;++j)
                    matx_.mat[i][j]=mat[i][j]-matx.mat[i][j];
            return matx_;
        }
        matrix operator*(const matrix &matx)
        {
            if(matx.row!=column)
                throw 2;
            matrix<DataType>matx_(row,matx.column);
            for(int i=0;i<row;++i)
                for(int j=0;j<matx.column;++j)
                {
                    matx_.mat[i][j]=0;
                    for(int k=0;k<column;++k)
                        matx_.mat[i][j]+=matx.mat[i][j]+mat[i][j];
                }
            return matx_;
        }
        /*matrix operator/(const matrix &matx)
        {
            
        }*/
        DataType *operator[](int i)
        {
            return mat[i];
        }
        void print(int n)
        {
            for(int i=0;i<row;++i)
            {
                for(int j=0;j<column;++j)
                {
                    cout<<setw(n)<<mat[i][j]<<" ";
                }
                cout<<endl;
            }
        }
        ~matrix()
        {
            for(int i=0;i<row;++i)
                delete[] mat[i];
            delete[] mat;
        }
    };

    template<typename T>class generallist{
    private:
        typedef T DataType;
        struct Node{
            int atom;
            DataType data;
            Node *nextnode;
            generallist *headnode;
            Node(DataType d)
            {
                atom=1;
                data=d;
                nextnode=NULL;
                headnode=NULL;
            }
            Node(generallist *h)
            {
                atom=0;
                nextnode=NULL;
                headnode=h;
            }
        };
        //
        Node *head;
    public:
        generallist()
        {
            head=NULL;
        }
        generallist(const generallist &glist)
        {
            if(glist.head==NULL)
            {
                head=NULL;
            }
            else
            {
                Node *temp=glist.head;
                head=temp->atom?new Node(temp->data):new Node(temp->headnode);
                Node *p=head;
                while(temp->nextnode!=NULL)
                {
                    temp=temp->nextnode;
                    p->nextnode=temp->atom?new Node(temp->data):new Node(temp->headnode);
                    p=p->nextnode;
                }
            }
        }
        void push(DataType data)
        {
            if(head==NULL)
            {
                head=new Node(data);
            }
            else
            {
                Node *temp=head;
                while(temp->nextnode!=NULL)
                    temp=temp->nextnode;
                temp->nextnode=new Node(data);
            }
        }
        void push(generallist *pglist)
        {
            if(head==NULL)
            {
                head=new Node(pglist);
            }
            else
            {
                Node *temp=head;
                while(temp->nextnode!=NULL)
                    temp=temp->nextnode;
                temp->nextnode=new Node(pglist);
            }
        }
        friend ostream &operator<<(ostream &cout,generallist &glist)
        {
            Node *temp=glist.head;
            cout<<"[";
            bool flag=false;
            while(temp!=NULL)
            {
                if(flag) cout<<",";
                else flag=true;
                if(temp->atom)
                    cout<<temp->data;
                else
                    cout<<*(temp->headnode);
                temp=temp->nextnode;
            }
            cout<<"]";
        }
        ~generallist()
        {
            Node *temp;
            while(head!=NULL)
            {
                temp=head;
                head=head->nextnode;
                delete temp;
            }
        }
    };
}