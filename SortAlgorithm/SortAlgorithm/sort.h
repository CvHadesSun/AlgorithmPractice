//
//  sort.h
//  SortAlgorithm
//
//  Created by hades on 2022/1/6.
//

#ifndef sort_h
#define sort_h

#include<vector>
#include<random>
#include <queue>

using namespace std;


// 选择排序实现 O(N^2) and O(1)

//0 ~ N-1  找到最小值，在哪，放到0位置上
//1 ~ n-1  找到最小值，在哪，放到1 位置上
//2 ~ n-1  找到最小值，在哪，放到2 位置上

template <class T>
void swapArray(vector<T> & arr,int i,int j)
{
    if(arr.size()<1 || i>arr.size() || j>arr.size() || i==j) return;
    
    arr[i]=arr[i]^arr[j];
    arr[j]=arr[i]^arr[j];
    arr[i]=arr[i]^arr[j];
    
}


void selectedSortAlgorithm(vector<int> & arr)
{
    if(arr.size()<2) return;
    
    for(int i=0;i<arr.size();i++)
    {
        int minIndex=i;
        int min=arr[i];
        for(int j=i;j<arr.size();j++)
        {
            if(arr[j]<min) // min
            {
                minIndex=j; //update min index.
                min=arr[j];
            }
        }
        // swap minest to index=i
        swapArray(arr, i, minIndex);
    }
}


// 冒泡排序 O(N^2) and O(1)
// 从前往后，如果大就往后交换
template <class T>
void bubbleSort(vector<T> & arr)
{
    //
    if(arr.size()<2) return;
    
    for(int i=arr.size();i>0;i--)
    {
        for(int j=0;j<i;j++)
        {
            if(arr[j]>arr[j+1]) swapArray(arr, j, j+1);
            
        }
    }
}

// 插入排序 O(N^2) and O(1)

//来到一个位置，i之前都是有序的，然后来到了i位置，将i位置插入到前i-1个数中做到有序

template <class T>
void insertSort(vector<T> & arr)
{
    if(arr.begin()==arr.end() || arr.size()<2) return ;
    
    //
    for(int i=1;i<arr.size();i++) // 到了i位置,前面都是有序的，也就是从i-1位置往前找就行 O(N)
    {
        for(int j=i;j>-1;j--)
        {
            if(arr[j]<arr[j-1]) swapArray(arr, j, j-1);
        }
    }
}


// 归并排序 O(NlogN)? and O(N)

// 归并操作实现：给定L，mid，R，将L-mid以及mid-R上
// 的数有序放置

template <class T>
void mergeOperation(vector<T> & arr,int L,int mid,int R)
{
    if(L==mid && mid==R) return;
    // new a tmp array to save res
    vector<T> res(R-L+1);
    
    // bi-pointer to compare and save the minest value into res
    int l=L;
    int r=mid+1;
    int i=0;
    
    while(l <=mid && r<=R)
    {
        res[i++] = arr[l]<arr[r] ? arr[l++]: arr[r++];
    }
    
    // l<mid
    while(l<=mid){
        res[i++] = arr[l++];
    }
    // r<R
    while(r<=R){
        res[i++] = arr[r++];
    }
    
    for(int i=0;i<res.size();i++){
        arr[L+i]=res[i];
    }
    
}

template <class T>
void mergeSort(vector<T> & arr,int L,int R){
    // base case
    if(L==R) return;
    // left sort
    int mid=L+((R-L)>>1); // mid = R/2
    mergeSort(arr,L,mid);
    mergeSort(arr, mid+1, R);
    mergeOperation(arr, L, mid, R); // merge
}

// 快排 O(NlogN) and O(logN)
// partition 操作： < | == | >

template <class T>
void partition(vector<T> & arr,vector<int> & bound,int L,int R, T num){
    int i=L;
    int l=L;
    int r=R;
    
    while(i<=r){ // i 碰到 r 结束
        if(arr[i]<num){ // 小： 交换
            swapArray(arr, l, i);
            l++;
            i++;
        }
        else if(arr[i]>num){ // 大： 交换
            swapArray(arr, r, i);
            r--;
        }
        else i++;   // 不做操作
    }
    
    bound[0] = l;
    bound[1] = r;
}


// using last value to partition
template <class T>
void quickSortV1(vector<T> & arr,vector<int> & bound,int L,int R){
    // base case
    if(L>=R) return;
    
    // partition operation.
    partition(arr,bound,L, R, arr[R]);  // use last value for partition.
    quickSortV1(arr, bound,L, bound[0]-1);
    quickSortV1(arr, bound,bound[1]+1, R);
}


long getRandomIndex(int L,int R){
    //
    if(L==R) return L;
    random_device rd; // define random device
    default_random_engine eng(rd()); //define random engine
//    uniform_int_distribution<int> distr(0,1); // define
    uniform_int_distribution<long> distr(L,R);
    
    return distr(eng);
}
// another version ,using random num in [L,R] for partition not the last value.
template <class T>
void quickSortV2(vector<T> & arr, vector<int> & bound, int L, int R ){
    // base case
    if(L>=R) return;
    
    long randomIndex=getRandomIndex(L, R);
    // partition operation.
    partition(arr,bound,L, R, arr[randomIndex]);  // use last value for partition.
    quickSortV2(arr, bound,L, bound[0]-1);
    quickSortV2(arr, bound,bound[1]+1, R);
    
    
}
// test api
template <class T>
void process(vector<T> &arr){
    vector<int> bound(2);
    quickSortV2(arr, bound, 0,arr.size()-1);
}


// 堆排(大根堆) O(NlogN) and O(N)

// heapinsert: 插入到堆中，大根堆则将大的值一直往上，直到交换到不能再交换了
// heapinsert 是一个向上的过程，可以在任意的位置插入一个新的值，然后调整为大根堆的形式

template <class T>
void heapInsert(vector<T> & arr,int index)
{
    //
    while (arr[(index-1)/2]< arr[index]) {
        swapArray(arr, index, (index-1)/2);
        index = (index-1)/2;
    }
}

// heapify: 同样也是插入堆元素的操作，但这个过程是向下的过程：
// 在堆内插入一个元素，如果是大根堆的话，那就是如果小的就一直向下调整
// 调整的时候和较大的那个孩子交换，然后一直往下，直到碰界,如果左右孩子都小
// 则不需要调整了，结束

template <class T>
void heapFiy(vector<T> & arr,int index,int heapSize ){
    // index have the left child, otherwise return
    int leftIndex=index*2+1;
    while (leftIndex<heapSize) {
        int largestIndex = ((leftIndex+1)<heapSize) && (arr[leftIndex+1] > arr[leftIndex]) ? leftIndex+1 : leftIndex;
        largestIndex = arr[index] > arr[largestIndex] ? index: largestIndex;
        if(largestIndex==index) break; // no need to ajust
        swapArray(arr, index, largestIndex);
        index=largestIndex;
        leftIndex=index*2+1;
        
    }
    //
}

template <class T>
void heapSort(vector<T> & arr){
    if(arr.size()<2) return;
    
    // init heap
    int heapSize=0;
    
    // O(N)
    for(int i=arr.size()-1;i>-1;i--){
        heapFiy(arr, i, ++heapSize);
        
    }
    while(heapSize>0){ // O(N)
        swapArray(arr, 0, --heapSize); // O(1)
        heapFiy(arr, 0, heapSize); // O(logN)
    }
}

/*
 堆排序扩展题目
 已知一个几乎有序的数组，几乎有序是指，
 如果把数组排好顺序的话，每个元素移动的距离可以不超过k，
 并且k相对于数组来说比较小。请选择一个合适的排序算法针对这个数据进行排序。
 */

template <class T>
void lessKSort(vector<T> & arr,int k){
    // using priority queue as heap
    if(arr.size()>2) return;
    // new queue
    priority_queue<T,vector<T>,greater<T>> q;
    
    int i=0;
    for(;i<=min(arr.size(),k);i++){
        // push into q
        q.push(arr[i]);
    }
    int j=0;
    while(i<arr.size()){
        // pop
        arr[j++] = q.top();
        q.pop();
        q.push(arr[i++]);
        
    }
    // pop q
    while(!q.empty()){
        arr[j++]=q.top();
        q.pop();
    }
}

// 桶排序
// 按照最长的位数用0补全，然后按照个十百千...依次
// 排序，最终得到结果


int getNumberDigit(int num,int index,int base){
    //
    int res= num /pow(base,index);
    return res % base;
}


void bucketSort(vector<int> & arr){
    //
    if(arr.size()<2) return;
    auto maxIter = max_element(arr.begin(), arr.end());
    int maxV= * maxIter;
    int numDig=0;
    
    while (maxV>0) { // O(K)
        maxV /=10;
        numDig++;
    }
    // new bucket
    vector<queue<int>> bucket(10);

    for(int i=0;i<=numDig;i++){ // O(K * N )

        for(int j=0;j<arr.size();j++){ // O(N)
            int res = getNumberDigit(arr[j],i, 10);
            bucket[res].push(arr[j]);
        }
        // pop data from bucket

        int index=0;
        for(int ii=0;ii<10;ii++){ //O(N)
            while(!bucket[ii].empty()){
                arr[index++] = bucket[ii].front();
                bucket[ii].pop();
            }
        }
    }
}
 



#endif /* sort_h */
