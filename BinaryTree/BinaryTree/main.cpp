//
//  main.cpp
//  BinaryTree
//
//  Created by hades on 2022/1/17.
//

#include <iostream>

#include "binaryTree.h"

int main(int argc, const char * argv[]) {
    // insert code here...
//    std::cout << "Hello, World!\n";
    
    vector<int> arr{2,1,4,3,6,7,5};
    
    TreeNode<int> *bt = initBinayTreeFromArray(arr);
    
    pprintBT(bt);
//    preBTOrder(bt);
//    cout<<endl;
//    inBTOrder(bt);
//    cout<<endl;
    postBTOrder(bt);
    cout<<endl;
//
//    preBTTraversal(bt);
//    inBTTraversal(bt);
//    postBTTraversal(bt);
//    cout<<maxWidthBT(bt)<<endl;
//    ReturnInfo<int> * is=isRearchBTV3(bt);
    morrisPostTravesal(bt);
    cout<<endl;
    return 0;
}
