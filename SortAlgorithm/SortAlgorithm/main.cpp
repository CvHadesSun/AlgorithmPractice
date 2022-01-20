//
//  main.cpp
//  SortAlgorithm
//
//  Created by hades on 2022/1/6.
//

#include <iostream>

# include "sort.h"
# include "test.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // sort algorithm test.
    // random arr params
    int testTime=500000;
    int maxLength=100;
    int maxValue=100;
    
    
    vector<int> arr=generateRandomArray<int>(maxLength,maxValue);  // max length and max value. random arr
    
    
//    logarithmicTester<int>(arr,testTime);
//    int res=getNumberDigit(100,3,10);
//    cout<<res<<endl;
    
    vector<int> test{100,101,99,77};
    bucketSort(test);


 // print result to test.
    for(auto &item :test)
    {
        cout<<item<<",";
    }
    cout<<endl;
    return 0;
}



