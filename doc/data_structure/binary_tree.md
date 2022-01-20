# [BABEL: Bodies, Action and Behavior with English Labels](https://arxiv.org/pdf/2106.09696.pdf)



[toc]

## node

```c++

template <class T>
struct TreeNode{
    T value;
    TreeNode * left;
    TreeNode * right;
    
    // stucter
    TreeNode():value(0),left(nullptr),right(nullptr){};
    TreeNode(T num):value(num),left(nullptr),right(nullptr){};
};
```



## 二叉树初始化

```c++
template <class T>
// value -1 means null node
TreeNode<T> * initBinayTreeFromArray(const vector<T> & arr){
    if(arr.size()<1) return new TreeNode<T>();
    
    vector<TreeNode<T>*> nodeArr(arr.size());
    for(int i=0;i<arr.size();i++){
        nodeArr[i] = arr[i]==-1 ? nullptr : new TreeNode<T> (arr[i]);
    }
    for(int i=0;i<arr.size();i++){
        if(nodeArr[i]!=nullptr){
            nodeArr[i]->left = i*2+1 < arr.size()? nodeArr[i*2+1]: nullptr;
            nodeArr[i]->right = i*2+2 < arr.size()? nodeArr[i*2+2]: nullptr;
        }
    }
    return  nodeArr[0];
}
```



## 打印二叉树

```c++
// 直观打印二叉树
template <class T>
void pprintBT(TreeNode<T>* root){
    // to visualize the binary tree.
    int h = heightOfBT(root);
    int midLoc = (2+2*(h-1))*h;
    queue<TreeNode<T>*> Q;
    queue<int> index;
    Q.push(root);
    index.push(midLoc);
    
    string row;
    for(int i=0;i<2*midLoc;i++){
        row +=' ';
    }
    int width = 0;
    for(int i=0;i<=h;i++){
        width += i;
    }
    int i=0;
    while(!Q.empty()){
        int levelNum = Q.size();
        string row1 = row;
        
        width -=i++;
//        cout<<width<<endl;
        vector<string> sign(width/2);
        for(int i=0;i<sign.size();i++){
            sign[i] = row;
        }
//        string row2 = row;
        for(int j=0;j<levelNum;j++){
            TreeNode<T> * cur = Q.front();
            Q.pop();
            int loc = index.front();
            index.pop();
            string sValue=to_string(cur->value);
            for(int ii=0;ii<sValue.length();ii++){
                row1[loc-ii] = sValue[ii];
            }
            sign[0]=row1;
            if(cur->left!=nullptr){
                Q.push(cur->left);
                index.push(loc-width/2);
            }
            if(cur->right!=nullptr){
                Q.push(cur->right);
                index.push(loc+width/2);
            }
            
            for(int k=1;k<width/2;k++){
                sign[k][loc-k]= cur->left==nullptr ? ' ': '/';
                sign[k][loc+k]= cur->right==nullptr ? ' ': '\\';
            }
            
          
        }
        
//        // print
        for(auto &item:sign){
            cout<<item<<endl;
        }
        
    }
}
```



## 二叉树高度

```c++
template <class T>
int heightOfBT(TreeNode<T> * root){
    if(root==nullptr) return 0;
    return max(heightOfBT(root->left),heightOfBT(root->right))+1;
    
}

```



## 最大宽度

```c++
// max width
// 返回二叉树最大宽度：节点最多的一层的节点个数

template <class T>
size_t maxWidthBT(TreeNode<T> * root){
    if(root==nullptr) return 0;
    size_t maxW=0;
    size_t levelNum = 0;
    queue<TreeNode<T>* > Q;
    Q.push(root);
    TreeNode<T>* endNode=root;
    TreeNode<T>* nextNode=root;
    while(!Q.empty()){
        TreeNode<T>* cur = Q.front();
        Q.pop();
        
        if(cur->left!=nullptr) {
            Q.push(cur->left);
            levelNum++;
            nextNode =cur->left;
        }
        if(cur->right!=nullptr){
            Q.push(cur->right);
            levelNum++;
            nextNode = cur->right;
        }
        
        if(cur==endNode){
            maxW = max(maxW,levelNum);
            levelNum=0;
            endNode =nextNode;
        }
    }
    return maxW;
}
```



## 二叉树遍历

### 递归

#### 前序：中左右

```c++
// 前序遍历 ： 中左右
template <class T>
void preBTOrder(TreeNode<T>* root){
    if(root==nullptr) return;
    cout<<root->value;
    preBTOrder(root->left);
    preBTOrder(root->right);
}
```

#### 中序：左中右

```c++
// 中序遍历 ： 中左右
template <class T>
void inBTOrder(TreeNode<T>* root){
    if(root==nullptr) return;
    inBTOrder(root->left);
    cout<<root->value;
    inBTOrder(root->right);
}
```

#### 后序：左右中

```c++
// 后序遍历 ： 左右中
template <class T>
void postBTOrder(TreeNode<T>* root){
    if(root==nullptr) return;
    postBTOrder(root->left);
    postBTOrder(root->right);
    cout<<root->value;
}
```



### 非递归

#### 前序

```c++
// 前序
// 按照广度优先遍历二叉树的方式入栈,右孩子先入栈，左孩子后入栈，然后不断弹出，打印
template <class T>
void preBTTraversal(TreeNode<T>* root){
    if(root==nullptr) return;
    stack<TreeNode<T>*> S;
    S.push(root);
    while(!S.empty()){
        TreeNode<T> * cur = S.top();
        S.pop();
        cout<<cur->value<<",";
        if(cur->right!=nullptr) S.push(cur->right);
        if(cur->left!=nullptr) S.push(cur->left);
    }
    cout<<endl;
}
```

#### 后序

```c++
//后续
// 按照广度优先的方式入栈，入栈时：左孩子先入栈，右孩子后入栈，弹出压入另一个栈，结束之后
// 从栈2中弹出

template <class T>
void postBTTraversal(TreeNode<T>* root){
    if(root==nullptr) return;
    stack<TreeNode<T>*> S1;
    stack<TreeNode<T>*> S2;
    
    S1.push(root);
    while(!S1.empty()){
        TreeNode<T>* cur = S1.top();
        S1.pop();
        S2.push(cur);
        if(cur->left!=nullptr) S1.push(cur->left);
        if(cur->right!=nullptr) S1.push(cur->right);
    }
    while(!S2.empty()){
        cout<<S2.top()->value<<",";
        S2.pop();
    }
    cout<<endl;
}
```



#### 中序

```c++
// 中序

// 先将左子树的所有左孩子入栈，然后弹出，弹出时判断节点的右孩子，
// 如果没右孩子，不做操作，如果有右孩子，则将该右孩子的所有左孩子入栈

template <class T>
void inBTTraversal(TreeNode<T>* root){
    if(root==nullptr) return;
    stack<TreeNode<T>*> S;
    TreeNode<T>* cur = root;
    while(cur!=nullptr){
        S.push(cur);
        cur=cur->left;
    }
    
    //
    while(!S.empty()){
        TreeNode<T> * left = S.top();
        S.pop();
        cout<<left->value<<",";
        TreeNode<T> * right = left->right;
        
        while(right!=nullptr){
            S.push(right);
            right = right->left;
        }
    }
    cout<<endl;
    
}
```



## 几种特殊的二叉树

### 搜索二叉树: 左<中<右

左树都比根节点小，右树都比根节点大：中序遍历结果时升序结果

```c++
// 搜索二叉树 : left < mid < right
// 1. 中序遍历的结果时升序排列
// 2. 递归
// 3. 二叉树的一般形式


int  leftMax = -1;
template <class T>
bool isRearchBT(TreeNode<T>* root){
    if(root==nullptr) return true;
    
    if(!isRearchBT(root->left)) return false;
    else{
        if(root->value>leftMax) leftMax = root->value;
        else return false;
    }
    return isRearchBT(root->right);
}
```



```c++
// 一般形式
template <class T>
class ReturnInfo{
public:
    ReturnInfo():isR(false),Min(-1),Max(-1){};
    ReturnInfo(bool b,T n,T m):isR(b),Min(n),Max(m){};
public:
    bool isR;
    T Min;
    T Max;
};

template <class T>
ReturnInfo<T>* isRearchBTV3(TreeNode<T>* root){
    if(root==nullptr){
        return nullptr;
    }
    ReturnInfo<T>* leftInfo = isRearchBTV3(root->left); // 左子树提供的信息
    ReturnInfo<T>* rightInfo = isRearchBTV3(root->right); // 右子树提供的信息
    
    T Max = root->value;
    T Min = root->value;
    bool isR = true;
    // 综合左子树信息
    if(leftInfo!=nullptr){ // 左子树有信息
        Max = max(Max,leftInfo->Max);
        Min = min(Min,leftInfo->Min);
        if(!leftInfo->isR || leftInfo->Max>=root->value){
            isR = false;
        }
    }
    // 综合右子树信息
    if(rightInfo!=nullptr){
        Max = max(Max,rightInfo->Max);
        Min = min(Min,leftInfo->Min);
        if(!rightInfo->isR || rightInfo->Min<=root->value){
            isR = false;
        }
    }
    
    return new ReturnInfo<T>(isR,Min,Max);

}
```



### 完全二叉树

按照广度优先遍历，一层一层，中间不能有空的节点

```c++
// 完全二叉树
// 左右不双全的节点只能是叶节点
// 其孩子不能作为其他节点的父节点
// 按照广度优先遍历，一层一层，不能断了

template <class T>
bool isCompletedBT(TreeNode<T>* root){
    if(root==nullptr) return true;
    queue<TreeNode<T>*> Q;
    Q.push(root);
    bool meetLeaf = false;
    
    while(!Q.empty()){
        TreeNode<T> * cur=Q.front();
        Q.pop();
        // is leaf node?
        if(cur->right==nullptr || cur->left==nullptr) meetLeaf=true;
        // push child node
        if(cur->left!=nullptr) Q.push(cur->left);
        if(cur->right!=nullptr) Q.push(cur->right);
        //
        if((meetLeaf && (cur->left!=nullptr || cur->right !=nullptr) ) || (cur->left==nullptr && cur->right!=nullptr) ){
            return false;
        }
    }
    return true;
}
```



### 满二叉树

满二叉树-高度和节点数满足：$n = 2h-1$

### 平衡二叉树

左右子树的高度差不能超过2

```c++
// 平衡二叉树

template <class T>
class ReturnInfoV2{
public:
    bool isB;
    size_t height;
    ReturnInfoV2():isB(true),height(0){};
    ReturnInfoV2(bool is,size_t h):isB(is),height(h){};
};
    
template <class T>
ReturnInfoV2<T>* isBlanceBT(TreeNode<T>* root){
    if(root==nullptr){
        return new ReturnInfoV2<T> ();
    }
    
    // left
    ReturnInfoV2<T> * leftInfo = isBlanceBT(root->left);
    //right
    ReturnInfoV2<T> * rightInfo = isBlanceBT(root->right);
    
    // process left and right info
    
    auto delta = fabs(leftInfo->height - rightInfo->height);
    
    bool is = leftInfo->isB && rightInfo->isB && (delta<2) ? true: false;
    
    return new ReturnInfoV2<T> (is,max(leftInfo->height,rightInfo->height)+1);
}
```







## Morrisi遍历



### Morrisi遍历


时间复杂度O(N),空间复杂度O(1),需要改动二叉树

 当前来到了cur节点：
 1.如果cur没有左孩子，直接往右孩子跳
 2.如果有左孩子，找到左子树最右的节点 mostRight：
    a.mostRight的右孩子如果为空，则将其右孩子指向cur节点，然后cur左移
    b.mostRight的右孩子如果为cur，则将其右孩子指向空，然后cur右移
 3.如果cur为空，则停止遍历

```c++
// morris 遍历
// 时间复杂度O(N),空间复杂度O(1),需要改动二叉树

/*
 当前来到了cur节点：
 1.如果cur没有左孩子，直接往右孩子跳
 2.如果有左孩子，找到左子树最右的节点 mostRight：
    a.mostRight的右孩子如果为空，则将其右孩子指向cur节点，然后cur左移
    b.mostRight的右孩子如果为cur，则将其右孩子指向空，然后cur右移
 3.如果cur为空，则停止遍历
 */


template <class T>
void morrisTravesal(TreeNode<T>* root){
    if(root==nullptr) return;
    TreeNode<T> *cur = root;
    
    while(cur!=nullptr){
        TreeNode<T> * mostRight = cur->left;
        if(mostRight!=nullptr){
            while(mostRight->right!=nullptr && mostRight->right!=cur){
                mostRight = mostRight->right;
            }
            if(mostRight->right==nullptr){
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else{
                mostRight->right=nullptr;
            }
        }
        cur = cur->right;
        
    }
}
```



### Morrisi遍历-三种遍历

#### 前序

 如果只出现了一次，则直接打印
 如果出现了两次，打印第一次

```c++
// morris :前序遍历
/*
 如果只出现了一次，则直接打印
 如果出现了两次，打印第一次
 */

template <class T>
void morrisPreTravesal(TreeNode<T> * root){
    if(root==nullptr) return;
    TreeNode<T> *cur = root;
    
    while(cur!=nullptr){
        TreeNode<T> * mostRight = cur->left;
        if(mostRight!=nullptr){ // have left child ,will happen 2 times
            while(mostRight->right!=nullptr && mostRight->right!=cur){
                mostRight = mostRight->right;
            }
            if(mostRight->right==nullptr){ // first time find mostRight node, this is first time.
                mostRight->right = cur;
                cout<<cur->value<<",";
                cur = cur->left;
                continue;
            }
            else{
                mostRight->right=nullptr;
            }
        }
        // no left child ,only happen 1 time
        else cout<<cur->value<<","; //
        cur = cur->right;
        
    }
}
```



#### 中序

 如果只出现一次，则直接打印，

 如果出现两次，打印第二次

```c++
// morris 中序
/*
 如果只出现一次，则直接打印，
 如果出现两次，打印第二次
 
 */

template <class T>
void morrisInTravesal(TreeNode<T>* root){
    if(root==nullptr) return;
    TreeNode<T> *cur = root;
    
    while(cur!=nullptr){
        TreeNode<T> * mostRight = cur->left;
        if(mostRight!=nullptr){
            while(mostRight->right!=nullptr && mostRight->right!=cur){
                mostRight = mostRight->right;
            }
            if(mostRight->right==nullptr){
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else{
                mostRight->right=nullptr;
            }
        }
        cout<<cur->value<<",";
        cur = cur->right;
        
    }
}
```



#### 后序

 如果出现一次，不做操作

 如果出现两次，第二次出现时，逆序打印左子树的右边界

 整个遍历结束，逆序打印整个树的右边界

```c++
// morris 后续：
/*
 如果出现一次，不做操作
 如果出现两次，第二次出现时，逆序打印左子树的右边界
 整个遍历结束，逆序打印整个树的右边界
 */

template <class T>
void morrisPostTravesal(TreeNode<T>* root){
    if(root==nullptr) return;
    TreeNode<T> *cur = root;
    stack<TreeNode<T>*> S;
    
    while(cur!=nullptr){
        TreeNode<T> * mostRight = cur->left;
        if(mostRight!=nullptr){
            while(mostRight->right!=nullptr && mostRight->right!=cur){
                mostRight = mostRight->right;
            }
            if(mostRight->right==nullptr){
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else{ // second time happen
                mostRight->right=nullptr;
                TreeNode<T>* p = cur->left;
                
                while(p!=nullptr){
                    S.push(p);
                    p = p->right;
                }
                while(!S.empty()){
                    cout<<S.top()->value<<",";
                    S.pop();
                }
            }
        }
        cur = cur->right;
        
    }
    
    // whole
    TreeNode<T>* p = root;
    
    while(p!=nullptr){
        S.push(p);
        p = p->right;
    }
    while(!S.empty()){
        cout<<S.top()->value<<",";
        S.pop();
    }
}
```



## 公共祖先

```c++
// 两个节点的公共祖先

template <class T>
TreeNode<T> * publicAncester(TreeNode<T> * root,TreeNode<T> * node1,TreeNode<T>* node2){
    if(root==node1 || root==node2 || root==nullptr) return root;
    
    TreeNode<T> * left = publicAncester(root->left, node1, node2);
    TreeNode<T> * right = publicAncester(root->right, node1, node2);
    
    if(left!=nullptr && right!=nullptr) return root; // 已经找到了 ,直接返回
    left = left? left:right; // 只有一边
    return left; // 向上返回非空的一条支路
}
```



## 最大距离

```c++
// 二叉树的最大节点距离

template <class T>
class Info{
public:
    size_t height;
    size_t maxDist;
    Info():height(0),maxDist(0){};
    Info(size_t h,size_t d):height(h),maxDist(d){};
};

template <class T>
Info<T>* maxDistance(TreeNode<T>* root,TreeNode<T>* node1,TreeNode<T> * node2){
    if(root==nullptr) return new Info<T>(0,0);
    
    Info<T> *left =maxDistance(root->left,node1,node2);
    Info<T> *right =maxDistance(root->right,node1,node2);
    
    //
    size_t height  = max(left->height,right->height)+1;
    size_t d1 = left->maxDist;  // 左子树的最大距离
    size_t d2 = right->maxDist; // 右子树的最大距离
    size_t d3 = left->height + right->height +1; // 两个子树组成的二叉树的可能的最大距离
    
    return new Info<T>(height,max(max(d1,d2),d3));
    
}
```





