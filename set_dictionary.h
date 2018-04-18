//
#pragma once

/********************
 * set_dictionary.h
 * 
 * exception int
 * 
 * returned value -1:not found,overflow
 * 
 * interface set:set(),bool ismember(DataType),void insert(DataType),
 *               void del(DataTType),set unite(set),set intersection(set),
 *               set difference(set),bool issubset(set),friend ostream &operator<<(ostream &,set)
 *           dictionary:dictionary(),int search(keyDataType),void insert(keyDataType,valueDataType),
 *                      void del(keyDataType),friend ostream &operator<<(ostream &,dictionary)
 *           hash_dictionary:hash_dictionary(),valueDataType *search(keyDataType),int insert(keyDataType,valueDataType),
 *                           friend ostream &operator<<(ostream &,hash_dictionary)
 * 
 * author lhc
 * date 2018.4.14 finished
 *******************/

#include"header.h"

namespace set_dictionary{
    template<typename T>class set{
    private:
        typedef T DataType;
        //
        linear_list::sequencelist<DataType> seq;
    public:
        set(){}
        set(const set &s):seq(s.seq){}
        bool ismember(DataType data)
        {
            for(int i=0;i<seq.length();++i)
                if(seq[i]==data)
                    return true;
            return false;
        }
        void insert(DataType data)
        {
            if(!ismember(data))
                seq.insert(data);
        }
        void del(DataType data)
        {
            if(ismember(data))
                for(int i=0;i<seq.length();++i)
                    if(seq[i]==data)
                    {
                        seq.del(i);
                        break;
                    }
        }
        set unite(set s)
        {
            set<DataType> temp(s);
            for(int i=0;i<seq.length();++i)
                temp.insert(seq[i]);
            return temp;
        }
        set intersection(set s)
        {
            set<DataType> temp;
            for(int i=0;i<s.seq.length();++i)
                if(ismember(s.seq[i]))
                    temp.insert(s.seq[i]);
            return temp;
        }
        set difference(set s)
        {
            set<DataType> temp(*this);
            for(int i=0;i<s.seq.length();++i)
                if(ismember(s.seq[i]))
                    temp.del(s.seq[i]);
            return temp;
        }
        bool issubset(set s)
        {
            for(int i=0;i<s.seq.length();++i)
                if(!ismember(s.seq[i]))
                    return false;
            return true;
        }
        friend ostream &operator<<(ostream &cout,set s)
        {
            cout<<"{";
            for(int i=0;i<s.seq.length();++i)
                cout<<setw(5)<<s.seq[i]<<" ";
            cout<<"}"<<endl;
            return cout;
        }
    };

    template<typename T,typename D>class dictionary{
    private:
        typedef T keyDataType;
        typedef D valueDataType;
        //
        linear_list::sequencelist<keyDataType> key;
        linear_list::sequencelist<valueDataType> value;
    public:
        dictionary(){}
        dictionary(const dictionary &dic):key(dic.key),value(dic.value){}
        int search(keyDataType k)
        {
            for(int i=0;i<key.length();++i)
                if(key[i]==k)
                    return i;
            return -1;
        }
        void insert(keyDataType k,valueDataType v)
        {
            int pos=search(k);
            if(pos==-1)
            {
                key.insert(k);
                value.insert(v);
            }
            else
            {
                value[pos]=v;
            }
        }
        void del(keyDataType k)
        {
            int pos=search(k);
            if(pos!=-1)
            {
                key.del(pos);
                value.del(pos);
            }
        }
        friend ostream &operator<<(ostream &cout,dictionary dic)
        {
            bool flag=true;
            cout<<"{";
            for(int i=0;i<dic.key.length();++i)
            {
                if(flag)
                    flag=false;
                else
                    cout<<",";
                cout<<dic.key[i]<<":"<<dic.value[i];
            }
            cout<<"}"<<endl;
            return cout;
        }
    };

    template<typename T,typename D>class hash_dictionary{
    private:
        typedef T keyDataType;
        typedef D valueDataType;
        struct Node{
            keyDataType key;
            valueDataType value;
            bool isused;
            Node()
            {
                isused=false;
            }
        };
        //
        Node *hashlist;
        int maxnum;
    public:
        hash_dictionary(int max)
        {
            maxnum=max;
            hashlist=new Node[maxnum];
        }
        hash_dictionary(const hash_dictionary &h)
        {
            maxnum=h.maxnum;
            hashlist=new Node[maxnum];
            memcpy(hashlist,h.hashlist,maxnum*sizeof(Node));
        }
        valueDataType *search(keyDataType key)
        {
            int addr=key%maxnum;
            do{
                if(!hashlist[addr].isused)
                {
                    return NULL;
                }
                if(hashlist[addr].key==key)
                {
                    return &hashlist[addr].value;
                }
                addr=(addr+1)%maxnum;
            }while(addr!=key%maxnum);
            return NULL;
        }
        int insert(keyDataType key,valueDataType value)
        {
            int addr=key%maxnum;
            do{
                if(!hashlist[addr].isused)
                {
                    hashlist[addr].key=key;
                    hashlist[addr].value=value;
                    hashlist[addr].isused=true;
                    return 0;
                }
                if(hashlist[addr].key==key)
                {
                    hashlist[addr].value=value;
                    return 0;
                }
                addr=(addr+1)%maxnum;
            }while(addr!=key%maxnum);
            return -1;
        }
        //This method hasn't been finished,
        /*
        int del(keyDataType key)
        {
            int addr=key%maxnum;
            do{
                if(!hashlist[addr].isused)
                    return -1;
                if(hashlist[addr].key==key)
                {
                    hashlist[addr].isused=false;
                    return 0;
                }
                addr=(addr+1)%maxnum;
            }while(addr!=key%maxnum);
            return 0;
        }
        */
        friend ostream &operator<<(ostream &cout,hash_dictionary h)
        {
            bool flag=true;
            cout<<"{";
            for(int i=0;i<h.maxnum;++i)
            {
                if(flag)
                    flag=false;
                else
                    cout<<",";
                if(h.hashlist[i].isused)
                {
                    cout<<h.hashlist[i].key<<":"<<h.hashlist[i].value;
                }
                else
                {
                    cout<<"*:#";
                }
            }
            cout<<"}"<<endl;
            return cout;
        }
        ~hash_dictionary(){delete[] hashlist;}
    };
}