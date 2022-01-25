//
//  main.cpp
//  Graph
//
//  Created by hades on 2022/1/24.
//

#include <iostream>
#include "graph.h"

int main(int argc, const char * argv[]) {
    // insert code here...
//    std::cout << "Hello, World!\n";
    vector<Matrix<int, int>*> mat;
    mat.push_back(new Matrix<int, int> (1,2,1));
    mat.push_back(new Matrix<int, int> (1,4,2));
    mat.push_back(new Matrix<int, int> (1,3,3));
    mat.push_back(new Matrix<int, int> (2,4,4));
    mat.push_back(new Matrix<int, int> (3,4,5));
    
    Graph<int, int>* G = new Graph<int, int>();
    
    initGraphFromMatrix(G, mat);
    
    graphBFS(G);
    graphDFS(G);
    vector<Node<int, int>*> res;
    graphTopologySort(G,res);
    vector<Edge<int, int>*> kRes;
    graphKAlgorithm(G, kRes);
    vector<Edge<int, int>*> pRes;
    graphPrimAlgorithm(G, pRes);
    
    //
    Node<int, int> * beginNode = G->graphNodes.begin()->second;
    map<Node<int, int>*,int> dRes1;
    djikstraAlgorithm(G, beginNode, dRes1);
    for(auto& item:dRes1){
        cout<<item.first->value<<"-"<<item.second<<endl;
    }
    map<Node<int, int>*,int> dRes2;
    
    dijkstraAlgorithmV2(G, beginNode, dRes2);
    cout<<dRes2.size()<<endl;
    for(auto& item:dRes2){
        cout<<item.first->value<<"-"<<item.second<<endl;
    }
    return 0;
}
