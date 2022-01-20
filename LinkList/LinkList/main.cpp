//
//  main.cpp
//  LinkList
//
//  Created by hades on 2022/1/15.
//

#include <iostream>
#include <vector>
#include "linklist.h"

using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
//    std::cout << "Hello, World!\n";
    vector<int> arr{1,3,4,5};

// single link list
//    ListNode<int> *head=initSingleLinkList(arr);
//    pprintLinkList(head);
//    head = delSingleLinkListNode(head,2);
//    head = InsertSingleLinkListNode(head,2,8);
//    head = inverseSingleLinkList(head);
//    pprintLinkList(head);
    
    
// bi link list
    
    vector<BiListNode<int>*> biList = initBiLinkList(arr);
    pprintBiLinkList(biList);
    insertBiLinkListNode(biList,4,0);
    pprintBiLinkList(biList);
    delBiLinkListNode(biList,1);
    pprintBiLinkList(biList);
    
    
    return 0;
}
