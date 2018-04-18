//
#pragma once

/********************
 * mystring.h
 * 
 * exception int -1:cross the border
 * 
 * returned value -1:not found
 *                0:success
 *                1:fail to insert
 *                2:fail to delete
 * 
 * interface mstring:mstring(),mstring &operator=(const mstring&)
 *                   bool isempty(),int length()
 *                   mstring substr(int,int),int index(mstring)
 *                   int index_(mstring),int insert(int,mstring)
 *                   int del(int,int),mstring operator+(mstring)
 *                   bool operator<(mstring),bool operator>(mstring)
 *                   bool operator==(mstring),char &operator[](int)
 *                   friend ostream &operator<<(ostream &,mstring)
 * 
 * author lhc
 * data 2018.3.28 finished
 *******************/

#include"header.h"
#include"linear_list.h"

namespace mystring
{
    class mstring{
    private:
        linear_list::sequencelist<char> str;
        void getnext(int *next,int len)
        {
            int k=-1;
            next[0]=k;
            for(int i=1;i<len;++i)
            {
                while(k>=0&&str[i-1]!=str[k]) k=next[k];
                ++k;
                next[i]=k;
            }
        }
    public:
        mstring()
        {
            str.insert('\0');
        }
        mstring(const mstring &mstr):str(mstr.str){}
        mstring(const char *chstr)
        {
            do{
                str.insert(*chstr);
            }while(*(chstr++)!='\0');
        }
        mstring &operator=(const mstring &mstr)
        {
            str=mstr.str;
            return *this;
        }
        bool isempty()
        {
            return str.isempty();
        }
        int length()
        {
            return str.length()-1;
        }
        mstring substr(int begin,int end)
        {
            mstring mstr;
            if(begin>=end||begin<0||end>length())
                return mstr;
            for(int i=begin;i<end;++i)
                mstr.str.insert(str[i],mstr.length());
            return mstr;
        }
        int index(mstring mstr)
        {
            for(int i=0;i<length()-mstr.length()+1;++i)
            {
                int j;
                for(j=0;j<mstr.length();++j)
                    if(str[i+j]!=mstr[j])
                        break;
                if(j==mstr.length())
                    return i;
            }
            return -1;
        }
        int index_(mstring mstr)
        {
            if(mstr.length()==0)
                return -1;
            int *next=new int[mstr.length()];
            mstr.getnext(next,mstr.length());
            int i,j;
            for(i=0,j=0;i<length()&&j<mstr.length();++i,++j)
            {
                if(str[i]!=mstr[j])
                {
                    if(next[j]==-1)
                    {
                        j=-1;
                    }
                    else
                    {
                        --i;
                        j=next[j]-1;
                    }
                }
            }
            delete[] next;
            if(j==mstr.length())
                return i-j;
            return -1;
        }
        int insert(int begin,mstring mstr)
        {
            if(begin<0||begin>length())
                return 1;
            for(int i=0;i<mstr.length();++i)
                str.insert(mstr[i],length());
            return 0;
        }
        int del(int begin,int end)
        {
            if(begin<0||end>length()||begin>=end)
                return 2;
            for(int i=begin;i<end;++i)
                str.del(begin);
            return 0;
        }
        mstring operator+(mstring mstr)
        {
            mstring mstr_(*this);
            for(int i=0;i<mstr.length();++i)
                mstr_.str.insert(mstr[i],mstr_.length());
            return mstr_;
        }
        bool operator<(mstring mstr)
        {
            int i,j,len1=length(),len2=mstr.length();
            for(i=0,j=0;i<len1&&j<len2;++i,++j)
            {
                if(str[i]<mstr[j])
                    return true;
                if(str[i]>mstr[j])
                    return false;
            }
            if(len1<len2)
                return true;
            return false;
        }
        bool operator>(mstring mstr)
        {
            int i,j,len1=length(),len2=mstr.length();
            for(i=0,j=0;i<len1&&j<len2;++i,++j)
            {
                if(str[i]>mstr[j])
                    return true;
                if(str[i]<mstr[j])
                    return false;
            }
            if(len1>len2)
                return true;
            return false;
        }
        bool operator==(mstring mstr)
        {
            int len1=length(),len2=mstr.length();
            if(len1!=len2)
                return false;
            for(int i=0;i<len1;++i)
                if(str[i]!=mstr[i])
                    return false;
            return true;
        }
        char &operator[](int i)
        {
            if(i<0||i>=length())
                throw -1;
            return str[i];
        }
        friend ostream &operator<<(ostream &cout,mstring mstr)
        {
            cout<<&(mstr.str[0]);
            return cout;
        }
    };
}