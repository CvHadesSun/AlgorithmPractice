//
//  graph.h
//  Graph
//
//  Created by hades on 2022/1/24.
//

#ifndef graph_h
#define graph_h

#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>

using namespace std;
// define graph base structure.

//
template <class T1,class T2>
struct Edge;

template <class T1,class T2>
struct Node;

template <class T1,class T2>
struct Edge{
    //
    T1 weight; // edge's weight
    Node<T1,T2> * begin;
    Node<T1,T2> * end;
    
    // structor
    Edge():weight(0),begin(nullptr),end(nullptr){};
    Edge(T1 w):weight(w),begin(nullptr),end(nullptr){};
    Edge(T1 w,Node<T1,T2> *b,Node<T1,T2> *e):weight(w),begin(b),end(e){};
};


template <class T1,class T2>
struct Node{
    // node symbol
    T2 value;
    // next nodes
    vector<Node<T1,T2>*> nextNodes;
    // edges
    vector<Edge<T1, T2>*> edges;
    // count in
    int countIn;
    int countOut;
    // structor
    Node():value(0),countIn(0),countOut(0){};
    Node(T2 val):value(val),countIn(0),countOut(0){};
    Node(vector<Node<T1,T2>*> nNode,vector<Node<T1,T2>*> e):value(0),nextNodes(nNode),edges(e),countIn(0),countOut(0){};
    Node(T2 val,vector<Node<T1,T2>*> nNode,vector<Node<T1,T2>*> e):value(val),nextNodes(nNode),edges(e),countIn(0),countOut(0){};
    Node(T2 val,vector<Node<T1,T2>*> nNode,vector<Node<T1,T2>*> e,int numIn,int numOut):value(val),nextNodes(nNode),edges(e),countIn(numIn),countOut(numOut){};
};

// graph define.
template <class T1,class T2>
class Graph{
public:
    // nodes set.
    map<T2,Node<T1, T2>*> graphNodes;
    // edges set.
    set<Edge<T1, T2>*> graphEdges;
    
    // constructor
    Graph():graphNodes({}),graphEdges({}){};
};



// init the graph from matrix
/*
 begin  end weight
 1       2    0.1
 ....
 */

template <class T1,class T2>
struct Matrix{
    T1 weight;
    T2 begin;
    T2 end;
    Matrix(T2 b,T2 e,T1 val):weight(val),begin(b),end(e){};
};

template <class T1,class T2>
void initGraphFromMatrix(Graph<T1, T2> * graph,const vector<Matrix<T1, T2>*> mat){
    // add nodes and edge into graph in the same time
    
    if(mat.size()<1) return;
    for(auto &item: mat){
        // add begin node into graph
        if(graph->graphNodes.find(item->begin)== graph->graphNodes.end()){
            // no this node
            graph->graphNodes.insert(make_pair(item->begin,
                                               new Node<T1, T2>(item->begin)));
        }
        // add end node into graph
        if(graph->graphNodes.find(item->end)== graph->graphNodes.end()){
            // no this node
            graph->graphNodes.insert(make_pair(item->end,
                                               new Node<T1, T2>(item->end)));
        }
        
        Node<T1, T2> * begin = graph->graphNodes[item->begin];
        Node<T1, T2> * end = graph->graphNodes[item->end];
        Edge<T1, T2> * edge = new Edge<T1, T2>(item->weight,begin,end);
        
        // end node is begin node next node
        begin->nextNodes.push_back(end);
        begin->edges.push_back(edge);
        
        begin->countOut++;
        end->countIn++;
        
        graph->graphEdges.insert(edge);
    }
}

// graph BFS
/*
 从开始节点，访问的时候不断的将其邻居节点放入队列，
并且要记录已经被访问过的节点，直到图中所有的节点被访问完为止
 */

template <class T1,class T2>
void graphBFS(Graph<T1, T2> * G){
    if(G->graphNodes.size()<1) return;
    queue<Node<T1, T2>*> Q; // to recoder nextNode
    set<Node<T1, T2>*> viewed; // to recoder already viewd nodes
    

    // first node to begin BFS
    auto iter = G->graphNodes.begin();
    Q.push(iter->second);
    viewed.insert(iter->second);

    while(!Q.empty()){
        Node<T1, T2>* cur = Q.front();
        Q.pop();
        cout<<cur->value<<",";
        for(auto &item: cur->nextNodes){
            if(viewed.find(item)==viewed.end()){
                viewed.insert(item);
                Q.push(item);
            }
        }
    }
    cout<<endl;
    
    
}

// graph DFS

/*
 从开始节点，找到一个没有被访问的邻居节点入栈，入栈时先入栈当前节点，然后入栈
邻居节点，直到栈为空为止
 */

template <class T1,class T2>
void graphDFS(Graph<T1, T2> * G){
    if(G->graphNodes.size()<1) return;
    stack<Node<T1, T2>*> S;
    set<Node<T1, T2>*> viewed;
    
    S.push(G->graphNodes.begin()->second);
    viewed.insert(G->graphNodes.begin()->second);
    
    cout<<G->graphNodes.begin()->second->value<<",";
    while(!S.empty()){
        Node<T1, T2> * cur = S.top();
        S.pop();
        for(auto &item: cur->nextNodes){
            if(viewed.find(item)==viewed.end()){
                viewed.insert(item); //recoder
                S.push(cur);
                S.push(item);
                cout<<item->value<<",";
                break;
            }
        }
    }
    cout<<endl;
}

// 拓扑排序
/*
 找到入堵为0的节点，然后作为开始的节点，并且记录到队列中，
 使用一个map来记录所有节点的入度，用于更新入度，去掉队首
 节点(入度为0)和其他节点的联系：就是将它邻居节点的入度减1，然后找
 到入度为0的，作为排序的下一个节点，不断循环直到队列为空
 */

template <class T1,class T2>
void graphTopologySort(Graph<T1, T2>* G,vector<Node<T1,T2>*> & res){
    if(G->graphNodes.size()<1) return;
    
    map<Node<T1, T2>*,int> recoder; // to recoder the countIn
    queue<Node<T1, T2>*> inZeroNodes;
    
    for(auto &item: G->graphNodes){
        recoder.insert(make_pair(item.second, item.second->countIn));
        if(item.second->countIn==0) inZeroNodes.push(item.second);
    }
    
    while(!inZeroNodes.empty()){
        Node<T1, T2>* cur = inZeroNodes.front();
        inZeroNodes.pop();
        res.push_back(cur); // cur's countIn==0
        cout<<cur->value<<",";
        for(auto & item: cur->nextNodes){ // neighbor nodes
            // remove cur node influence
            recoder[item]--;
            if(recoder[item]==0){
                inZeroNodes.push(item);
            }
        }
    }
    cout<<endl;
}

// graph k-algorithm （生成最小生成树）

/*
 初始化每个节点都是一个集合，找到最小权重的边，
 如果边的两个节点是一个集合，则不做操作，否则就
 合并两个节点所在集合为一个合集，并且记录这个边，
 然后找到次小的边，如此类推，直到没有可选择的边为止
 */

// 一个比较容易实现合并与查找操作的结构
template <class T1,class T2>
class UnionFind{
public:
   
    UnionFind():unionSet({}){};
    UnionFind(map<T2,Node<T1, T2>*> nodes){
        for(auto & item:nodes){
            vector<Node<T1, T2>*>* perSet = new vector<Node<T1, T2>*>{};
            perSet->push_back(item.second);
            unionSet.insert(make_pair(item.second,perSet));
        }
    }
    bool isSameSet(Node<T1, T2>* node1,Node<T1, T2>* node2){
        if(unionSet.find(node1)->second == unionSet.find(node2)->second) return true;
        else return false;
        
    }
    void unionNodesSet(Node<T1, T2>* node1,Node<T1, T2>* node2){
        if(isSameSet(node1,node2)) return; // no need to union
        // not in the same set ,need to union
        unionSet.find(node1)->second->push_back(node2);
        unionSet.find(node2)->second =unionSet.find(node1)->second;
    }
private:
    map<Node<T1, T2>*,vector<Node<T1, T2>*>*> unionSet;
    
};


template <class T1,class T2>
void graphKAlgorithm(Graph<T1, T2>* G,vector<Edge<T1, T2>*> & res){
    UnionFind<T1, T2>* U = new UnionFind<T1, T2>(G->graphNodes);
    auto cmp = [](Edge<T1, T2>* e1,Edge<T1, T2>* e2){return e1->weight>e2->weight;};
    priority_queue<Edge<T1, T2>*,vector<Edge<T1, T2>*>,decltype(cmp)> pQ(cmp);
    
    // push all edges of graph
    for(auto & item: G->graphEdges){
        pQ.push(item);
    }
    
    while(!pQ.empty()){
        Edge<T1, T2> * curEdge = pQ.top();
        pQ.pop();
        
        if(!U->isSameSet(curEdge->begin, curEdge->end)){
            // not the same set
            U->unionNodesSet(curEdge->begin, curEdge->end);
            res.push_back(curEdge);
            cout<<curEdge->weight<<",";
        }
    }
    cout<<endl;
    
    
}

// prim algorithm (生成最小生成树)
/*
 以节点为标准，将所有的节点遍历访问，只访问一次，
 每次访问的下一个节点为边权重最小的那个end节点，
 这样带来的代价是最小的，并且访问节点之后要把其
 所有的边记录用来寻找下一个访问节点。
 */

template <class T1,class T2>
void graphPrimAlgorithm(Graph<T1, T2> * G,vector<Edge<T1, T2>*> & res){
    if(G->graphNodes.size()<1) return;
    set<Node<T1, T2>*> viewed;
    auto cmp = [](Edge<T1, T2>* e1,Edge<T1, T2>* e2){return e1->weight>e2->weight;};
    priority_queue<Edge<T1, T2>*,vector<Edge<T1, T2>*>,decltype(cmp)> pQ(cmp);
    
    Node<T1, T2>* firstNode = G->graphNodes.begin()->second;
    for(auto &item: firstNode->edges)
    {
        pQ.push(item);
    }
    viewed.insert(firstNode);
    
    while(!pQ.empty()){
        Edge<T1, T2> * curEdge = pQ.top();
        pQ.pop();
        
        Node<T1, T2>* end = curEdge->end;
        if(viewed.find(end)==viewed.end()){
            res.push_back(curEdge);
            viewed.insert(end);
            cout<<curEdge->weight<<",";
            for(auto &item: end->edges){
                pQ.push(item);
            }
        }
    }
    cout<<endl;
}

// dijsktra algorithm （最短路径算法）

/*
 算法返回的是开始节点到图中能到达的所有节点的最短路径
 初始化，开始节点到其他节点的距离都是无穷大，开始节点
 到自己距离为0，从节点距离记录中找到没有被锁定的最小的
 记录，用来更新该节点邻居节点的记录，然后锁定这记录直到
 节点都被锁定为止，即所有的节点都被访问了，最短距离都得
 到了
 */
template <class T1,class T2>
Node<T1, T2> * findMinDistNode(map<Node<T1, T2>*,T1> & res,set<Node<T1, T2>*> & lock){
    Node<T1, T2>* minNode = nullptr;
    T1 minDist = 1000;
    for(auto &item: res)
    {
        if(item.second<minDist && lock.find(item.first)==lock.end()){
            minNode = item.first;
            minDist = item.second;
        }
    }
    
    return minNode;
}

template <class T1,class T2>
void djikstraAlgorithm(Graph<T1,T2>* G,Node<T1, T2>* beginNode,map<Node<T1, T2>*,T1> & res){
    if(G->graphNodes.size()<1) return;
    set<Node<T1, T2>*> lock;
    res.insert(make_pair(beginNode, 0)); //
    Node<T1, T2> * minNode  = findMinDistNode(res, lock);
    
    while(minNode!=nullptr){
        // update minNode's neighbor nodes
        T1 minNodeDist = res[minNode];
        for(auto &item:minNode->edges){
            if(res.find(item->end)==res.end()){
                // no recoder
                res.insert(make_pair(item->end, minNodeDist+item->weight));
            }
            else{
                // have recoder
                if(res.find(item->end)->second > item->weight+minNodeDist){
                    res.find(item->end)->second = item->weight+minNodeDist;
                }
            }
            lock.insert(minNode);
            minNode = findMinDistNode(res, lock);
        }
    }
}



// 改写堆来优化

template <class T1,class T2>
class MinHeap{
public:
    MinHeap(){
        heapSize=0;
        vector<Node<T1, T2>*> tmp(100);
        minHeap=tmp;
        set<Node<T1, T2>*> tmp1{};
        locked = tmp1;
        map<Node<T1, T2>*,T1> tmp2{};
        recoder = tmp2;
    }

    
    void heapFiy(int index){
        // down forward
//        if(index>heapSize) return;
        int left = index*2+1; // left child
        while(left<heapSize){ //have left child
            int minestIndex = (left+1 <heapSize) && (recoder.find(minHeap[left+1])->second<recoder.find(minHeap[left])->second)? left+1 :left;
            minestIndex = recoder.find(minHeap[minestIndex])->second < recoder.find(minHeap[index])->second? minestIndex: index;
            if(minestIndex==index) break;
            swap(minHeap,index,minestIndex);
            left = left*2+1;
        }
        
    }
    void swap(vector<Node<T1, T2>*>& arr,int i,int j){
        if(arr.size()<1 || i==j) return;
        Node<T1, T2>* tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
    void heapInsert(Node<T1, T2>* node,int index){
        // up froward
        minHeap[heapSize]=node;
        while(recoder.find(minHeap[index/2])->second>recoder.find(minHeap[index])->second){
            // min
            swap(minHeap,index/2,index);
            index = index/2;
        }
    }
    
    void addOrUpdateOrIgnore(Node<T1, T2>* node,T1 weight){
        if(isNotLocked(node)){
        // add : no recoder
        if(recoder.find(node)==recoder.end()){
            recoder.insert(make_pair(node,weight));
            heapInsert(node, heapSize);
            heapSize++;
        }
        else{ // have recoder
            // upate:
            if(recoder[node]>weight){
                recoder[node] = weight;
                // adjust the min-root heap
                heapFiy(0);
            }
            // ignore:
        }
        }
        
    }
    bool isNotLocked(Node<T1, T2>* node){
        if(locked.find(node)==locked.end()) return true;
        return false;
    }
    
    Node<T1, T2>* pop(){
        // pop root node and adjust heap
        if (heapSize<1) return nullptr;
        swap(minHeap,0,heapSize--);
        heapFiy(0);
        locked.insert(minHeap[heapSize+1]);
        return minHeap[heapSize+1];
    }
    T1 curDist(Node<T1, T2>* node){
        if(recoder.find(node)!=recoder.end()) return recoder.find(node)->second;
        else return -1;
    }
    map<Node<T1, T2>*,T1> getRes(){
        return recoder;
    }
private:
    int heapSize;
    set<Node<T1, T2>*> locked;
    map<Node<T1, T2>*,T1> recoder;
    vector<Node<T1, T2>*> minHeap;
};

template <class T1,class T2>
void dijkstraAlgorithmV2(Graph<T1, T2>* G,Node<T1, T2>* beginNode,map<Node<T1,T2>*,T1> & res){
    if(G->graphNodes.size()<1) return;
    MinHeap<T1, T2> * heap = new MinHeap<T1, T2>();
    heap->addOrUpdateOrIgnore(beginNode, 0);
    
    Node<T1, T2>* minNode = heap->pop();
    
    while(minNode!=nullptr){
        T1 curDist = heap->curDist(minNode);
        for(auto& item:minNode->edges){
            heap->addOrUpdateOrIgnore(item->end, item->weight+curDist);
        }
        minNode = heap->pop();
    }
    res= heap->getRes();
}
#endif /* graph_h */


