//
#pragma once

/********************
 * ordering_method.h
 * 
 * requirement arr:[],Datatype:< > <= >= 
 * 
 * author lhc
 * data 2018.4.18 finished
 *******************/

#include"header.h"
#include"stack_queue.h"

namespace ordering_method
{
    #define EXCHANGE(a,b) {a+=b;b=a-b;a=a-b;}
    #define GETNUMBER(number,n) (int(number/pow(10,n))%10)

    template<typename T,typename DataType>void sift1(T &arr,int len)
    {
        int pos=len-1,i=pos;
        DataType data=arr[pos];
        while(pos!=0)
        {
            i=(i-1)/2;
            if(arr[i]>data)
                arr[pos]=arr[i];
            else
                break;
            pos=i;
        }
        arr[pos]=data;
    }

    template<typename T,typename DataType>void sift2(T &arr,int len)
    {
        DataType data=arr[0];
        int now,r,l;
        for(now=0,l=1,r=2;r<len;l=now*2+1,r=now*2+2)
        {
            if(data<=arr[r]&&data<=arr[l])
            {
                arr[now]=data;
                break;
            }
            if(arr[r]<arr[l])
            {
                arr[now]=arr[r];
                now=r;
            }
            else
            {
                arr[now]=arr[l];
                now=l;
            }
        }
        if(r>=len)
        {
            if(l>=len||data<=arr[l])
                arr[now]=data;
            else
            {
                arr[now]=arr[l];
                arr[l]=data;
            }
        }
    }

    template<typename T,typename DataType>void merge(T &arr1,T &arr,int low,int mid,int high)
    {
        int i=low,j=mid+1,k=low;
        while(i<=mid&&j<=high)
        {
            if(arr[i]>arr[j])
            {
                arr1[k++]=arr[i++];
            }
            else
            {
                arr1[k++]=arr[j++];
            }
        }
        while(i<=mid)
        {
            arr1[k++]=arr[i++];
        }
        while(j<=high)
        {
            arr1[k++]=arr[j++];
        }
        for(int i=low;i<=high;++i)
        {
            arr[i]=arr1[i];
        }
    }

    template<typename T,typename DataType>void mergepass(T &arr1,T &arr,int len,int length)
    {
        int i;
        for(i=0;(i+2*length)<=len;i+=2*length)
            merge<T,int>(arr1,arr,i,i+length-1,i+2*length-1);
        if(i+length<=len)
            merge<T,int>(arr1,arr,i,i+length-1,len-1);
        else
            merge<T,int>(arr1,arr,i,len-1,len-1);
    }

    template<typename T,typename DataType>void directinsert_sort(T &arr,int len)
    {
        for(int i=1;i<len;++i)//len
        {
            int j;
            for(j=i-1;j>=0;--j)//len
            {
                if(arr[i]<=arr[j])
                    break;
            }
            DataType temp=arr[i];
            for(int k=i;k>j+1;--k)//len
                arr[k]=arr[k-1];
            if(j+1!=i)
                arr[j+1]=temp;
        }
    }//n^2

    template<typename T,typename DataType>void halfinsert_sort(T &arr,int len)
    {
        for(int i=1;i<len;++i)//len
        {
            int j,k,mid;
            for(j=0,k=i-1;j<=k;)//log2(len)
            {
                mid=(j+k)/2;
                if(arr[i]<=arr[mid])
                    j=mid+1;
                else
                    k=mid-1;
            }
            DataType temp=arr[i];
            for(k=i;k>j;--k)//len
                arr[k]=arr[k-1];
            if(j!=i)
                arr[j]=temp;
        }
    }//n^2

    template<typename T,typename DataType>void shell_sort(T &arr,int len)
    {
        for(int d=len/2;d>=1;d=d/2)
        {
            for(int start=0;start<d;++start)
                for(int i=start+d;i<len;i+=d)
                {
                    int j;
                    for(j=i-d;j>=start;j-=d)
                    {
                        if(arr[i]<=arr[j])
                            break;
                    }
                    DataType temp=arr[i];
                    for(int k=i;k>j+d;k-=d)
                        arr[k]=arr[k-d];
                    if(j+d!=i)
                        arr[j+d]=temp;
                }
        }
    }//n^1.3

    template<typename T,typename DataType>void directselect_sort(T &arr,int len)
    {
        for(int i=0;i<len-1;++i)//len
        {
            int flag=i;
            for(int j=i+1;j<len;++j)//len
            {
                if(arr[flag]<arr[j])
                    flag=j;
            }
            if(flag!=i)
                EXCHANGE(arr[flag],arr[i]);
        }
    }//n^2
    
    template<typename T,typename DataType>void heap_sort(T &arr,int len)
    {
        for(int i=1;i<=len;++i)//len
            sift1<T,DataType>(arr,i);//log2(len)
        for(int i=len-1;i>0;--i)//len
        {
            EXCHANGE(arr[i],arr[0]);
            sift2<T,DataType>(arr,i);//log2(len)
        }
    }//n*log2(n)

    template<typename T,typename DataType>void bubble_sort(T &arr,int len)
    {
        for(int i=len-1;i>0;--i)//len
        {
            for(int j=0;j<i;++j)//len
                if(arr[j]<arr[j+1])
                    EXCHANGE(arr[j],arr[j+1]);
        }
    }//n^2

    template<typename T,typename DataType>void quick_sort(T &arr,int len,int start=0)
    {
        if(len<=1)
            return;
        int left=start+1,right=start+len-1;
        bool flag=true;//left is empty
        DataType temp=arr[start];
        while(left<=right)//len
        {
            if(flag)
            {
                if(arr[left]>=temp)
                {
                    arr[left-1]=arr[left];
                    ++left;
                }
                else if(arr[right]>temp)
                {
                    arr[left-1]=arr[right];
                    --right;
                    flag=false;//right is empty
                }
                else --right;
            }
            else
            {
                if(arr[right]<=temp)
                {
                    arr[right+1]=arr[right];
                    --right;
                }
                else if(arr[left]<temp)
                {
                    arr[right+1]=arr[left];
                    ++left;
                    flag=true;//left is empty
                }
                else ++left;
            }
        }
        if(flag)
        {
            arr[left-1]=temp;
            quick_sort<T,DataType>(arr,left-1-start,start);
            quick_sort<T,DataType>(arr,start+len-left,left);
        }
        else
        {
            arr[right+1]=temp;
            quick_sort<T,DataType>(arr,right+1-start,start);
            quick_sort<T,DataType>(arr,start+len-right-2,right+2);
        }
    }//n*log2(n)

    template<typename T,typename DataType>void base_sort(T &arr,int len)
    {
        stack_queue::queue<int> q[10];
        for(int i=0;i<3;++i)//m
        {
            for(int j=len-1;j>=0;--j)//len
            {
                q[GETNUMBER(arr[j],i)].enqueue(arr[j]);
            }
            for(int count=len,k=0;k<10;++k)//len
            {
                while(!q[k].isempty())
                {
                    arr[--count]=q[k].dequeue();
                }
            }
        }
    }//m*n

    template<typename T,typename DataType>void merge_sort(T &arr1,T &arr,int len)
    {
        int i=1;
        while(i<len)
        {
            mergepass<T,int>(arr1,arr,len,i);
            i*=2;
            mergepass<T,int>(arr,arr1,len,i);
            i*=2;
        }
    }//n*log2(n)
}