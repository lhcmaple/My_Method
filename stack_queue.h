//
#pragma once

/********************
 * stack_queue.h
 * 
 * exception int -1:stack or queue is empty
 * 
 * returned value 
 * 
 * interface stack:bool isempty(),void push(DataType)
 *                 DataType pop(),DataType top()
 *           queue:bool isempty(),void enqueue(DataType data)
 *                 DataType dequeue(),DataType frontqueue()
 *           priorityqueue:priorityqueue(),bool isempty(),void add(DataType),
 *                         DataType removemin(),DataType getmin(),friend ostream &operator<<(ostream &,priorityqueue)
 * 
 * author lhc
 * data 2018.3.28 finished
 *******************/

#include"header.h"
#include"linear_list.h"

namespace stack_queue{
    template<typename T>class stack{
    private:
        typedef T DataType;
        linear_list::singlelinkedlist<DataType> stk;
    public:
        bool isempty()
        {
            return stk.length()==0;
        }
        void push(DataType data)
        {
            stk.push(data);
        }
        DataType pop()
        {
            if(isempty())
                throw -1;
            DataType temp=stk[stk.length()-1];
            stk.delpos(stk.length()-1);
            return temp;
        }
        DataType top()
        {
            return stk[stk.length()-1];
        }
    };

    template<typename T>class queue{
    private:
        typedef T DataType;
        linear_list::singlelinkedlist<DataType> que;
    public:
        bool isempty()
        {
            return que.length()==0;
        }
        void enqueue(DataType data)
        {
            que.push(data);
        }
        DataType dequeue()
        {
            if(isempty())
                throw -1;
            DataType temp=que[0];
            que.delpos(0);
            return temp;
        }
        DataType frontqueue()
        {
            return que[0];
        }
    };

    template<typename T>class priorityqueue{
    private:
        typedef T DataType;
        //
        linear_list::sequencelist<DataType>q;
    public:
        priorityqueue():q(){}
        priorityqueue(const priorityqueue &pq):q(pq.q){}
        priorityqueue &operator=(const priorityqueue &pq)
        {
            q=pq.q;
            return *this;
        }
        bool isempty()
        {
            return q.isempty();
        }
        void add(DataType data)
        {
            int pos=q.length();
            q.insert(data);
            int i=pos;
            while(pos!=0)
            {
                i=(i-1)/2;
                if(q[i]>data)
                    q[pos]=q[i];
                else
                    break;
                pos=i;
            }
            q[pos]=data;
        }
        DataType removemin()
        {
            if(q.length()==0)
                throw -1;
            DataType min=q[0];
            if(q.length()==1)
            {
                q.del();
                return min;
            }
            DataType last=q[q.length()-1];
            q.del();
            int now,r,l;
            for(now=0,l=1,r=2;r<q.length();l=now*2+1,r=now*2+2)
            {
                if(last<=q[r]&&last<=q[l])
                {
                    q[now]=last;
                    break;
                }
                if(q[r]<q[l])
                {
                    q[now]=q[r];
                    now=r;
                }
                else
                {
                    q[now]=q[l];
                    now=l;
                }
            }
            if(r>=q.length())
            {
                if(l>=q.length()||last<=q[l])
                    q[now]=last;
                else
                {
                    q[now]=q[l];
                    q[l]=last;
                }
            }
            return min;
        }
        DataType getmin()
        {
            return q[0];
        }
        friend ostream &operator<<(ostream &cout,priorityqueue pq)
        {
            for(int i=0;i<pq.q.length();++i)
                cout<<pq.q[i]<<" ";
            cout<<endl;
            return cout;
        }
    };
}