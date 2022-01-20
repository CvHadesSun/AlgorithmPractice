//
//  test.h
//  SortAlgorithm
//
//  Created by hades on 2022/1/6.
//

#ifndef test_h
#define test_h

#include<random>
#include<vector>
#include "sort.h"

using namespace std;



// 实现一个对数测试器

// 产生一个随机数组

template <class T>
vector<T> generateRandomArray(int maxSize,int maxValue)
{
    //
    random_device rd; // define random device
    default_random_engine eng(rd()); //define random engine
//    uniform_int_distribution<int> distr(0,1); // define
    uniform_real_distribution<double> distr(0,1);
    
    int arrLen=distr(eng)*maxSize; //random array length
    
    vector<T> arr(arrLen); // new array
    
    for(auto &item:arr)
    {
        item=distr(eng)*maxValue;
    }
    return arr;
}


// 数组复制
template <class T>
vector<T> copyArray(const vector<T> & oriArr)
{
    vector<T> newArr(oriArr.size()); // new arr
    for(int i=0; i<oriArr.size();i++)
    {
        newArr[i]=oriArr[i];
    }
    
    return newArr;
    
}

// 数组相等判断

template <class T>

bool isEqual(const vector<T> & arr1, const vector<T> & arr2)
{
    if(arr1.size()!=arr2.size()) return false;
    
    for(int i=0;i<arr1.size();i++)
    {
        if(arr1[i]!=arr2[i]) return false;
        
    }
    return true;
}

// 标准方法定义

template <class T>
void comparator(vector<T> & arr )
{
    // 对于排序算法来将就是标准的排序方法
    sort(arr.begin(),arr.end());
}


template<class T>
void logarithmicTester(vector<T> & arr,int testTime)
{
    // input arr
    vector<T> arrCopy=copyArray<T>(arr);
    // my function
//    selectedSortAlgorithm(arr);
//    bubbleSort(arr);
//    insertSort(arr);
//    mergeSort(arr,0,arrCopy.size()-1);
//    process(arr);
    heapSort(arr);
    // standard function
    comparator<T>(arrCopy);
    
    int passNum=0;
    
    for(int i=0; i<testTime;i++)
    {
        if(isEqual(arr, arrCopy)) passNum++;
    }
    
    cout<<"----pass---:"<<passNum<<"/"<<testTime<<endl;
    
}

#endif /* test_h */
