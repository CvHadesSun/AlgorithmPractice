# Link List

[toc]

## 单链表

### Node

```c++
template <class T >
struct ListNode { // link list node define
    T num;  // value
    ListNode * next; // next pointer
    
    // structer func
    ListNode():num(0),next(nullptr){};
    ListNode(T n):num(n),next(nullptr){};
    ListNode(T n,ListNode * ptr):num(n),next(ptr){};
};
```

### 初始化

```c++
// init single link list with arr
template <class T>
ListNode<T> *  initSingleLinkList(const vector<T> & arr){
    //
    if(arr.size()<1) return  nullptr;
    // new head
    ListNode<T> *head = new ListNode<T>(arr[0]);
    ListNode<T> * cur = head;  // define current pointer for next.
    for(int i=1;i<arr.size();i++){
        ListNode<T> *tmp = new ListNode<T>(arr[i]); // new next node
        cur->next = tmp; //
        cur = tmp;
    }
    
    //
    return head;
}
```



### 删除节点

```c++
// single link list delete node

template <class T>
ListNode<T>* delSingleLinkListNode(ListNode<T> *head,int index){
    //
    if(head==nullptr) return head;
    
    ListNode<T> * cur=head;
    ListNode<T> * pre;
    
    if(index==0){
        head = head->next;
        return head;
    }
    
    int i=0;
    while(cur!=nullptr ){
        if(i++==index){
            pre->next=cur->next;
            break;;
        }
        else{
            pre=cur;
            cur=cur->next;
        }
    }
    return head;
}
```

### 节点插入

```c++
// insert node
template <class T>
ListNode<T> * InsertSingleLinkListNode(ListNode<T> * head,int index,T value){
    // insert the value into single link list in location : index.
    if(head==nullptr) return head;
    ListNode<T> * cur=head;
    ListNode<T> * newNode=new ListNode<T> (value);
    if(index==0){
        head=newNode;
        head->next=cur;
        return head;
    }
    int i=0;
    ListNode<T> * pre=head;
    while(cur!=nullptr){
        if(i++==index){
            pre->next=newNode;
            newNode->next=cur;
            break;
        }
        else{
            pre=cur;
            cur=cur->next;
        }
    }
    return head;
    
}
```

### 翻转单链表

```c++
//inverse link list
template <class T>
ListNode<T> * inverseSingleLinkList(ListNode<T>* head){
    //
    if(head==nullptr) return head;
    ListNode<T> * cur=head;
    ListNode<T> * pre=head;
    ListNode<T> * next=cur->next;
    
    while(next!=nullptr){
        cur=next;
        next=cur->next;
        cur->next=pre;
        pre=cur;
    }
    
    head->next=nullptr;
    head=cur;
    return head;
}
```

 

## 双向链表



### Node

```c++
// 双向链表

template <class T>
struct BiListNode{
    int num;
    BiListNode * pre;
    BiListNode * next;
    BiListNode():num(0),pre(nullptr),next(nullptr){};
    BiListNode(T n):num(n),pre(nullptr),next(nullptr){};
};

```



### 初始化

```c++
// init bi link list
template <class T>
vector<BiListNode<T>*> initBiLinkList(vector<T> & arr){
    // return head node and end node
    
    
    vector<BiListNode<T>*> res(2);
    if(arr.size()<1)  return res;
    BiListNode<T> * head;
    BiListNode<T> * end;
    
    
    if(arr.size()>1){
        head = new BiListNode<T>(arr[0]);
    }
    BiListNode<T> * cur=head;
    int i=1;
    for(;i<arr.size();i++){
        BiListNode<T> * newNode = new BiListNode<T> (arr[i]);
        newNode->pre=cur;
        cur->next = newNode;
        cur=newNode; // step cur
    }
    end = cur;
    
    //
    res[0] = head;
    res[1] = end;
    return res;
}
```



### 插入

```c++
// insert

template <class T>
void insertBiLinkListNode(vector<BiListNode<T>*> & biList,int index,T value){
    if(biList.size()!=2) return;
    BiListNode<T> * newNode = new BiListNode<T>(value);
    BiListNode<T> * head= biList[0];
    BiListNode<T> * end = biList[1];
    int i=0;
    BiListNode<T> * cur = head;
    BiListNode<T> * pre = nullptr;
    
    if(index==0){
//        BiListNode<T> * newNode = new BiListNode<T>(value);
        newNode->next=head;
        head->pre=newNode;
        head=newNode;
        biList[0] = head;
        return;
    }
    while(cur!=nullptr){
        if(i++==index){
            
            BiListNode<T> * tmp = pre->next;
            pre->next = newNode;
            newNode->pre = pre;
            newNode->next = tmp;
            tmp->pre = newNode;
            break;
        }
        else{
            pre = cur;
            cur=cur->next;
        }
    }
    if(i==index){
//        BiListNode<T> newNode = new BiListNode<T>(value);
        end->next=newNode;
        newNode->pre = end;
        end=newNode;
        
    }
    biList[1] = end;
}
```



### 删除

```c++
template <class T>
void delBiLinkListNode(vector<BiListNode<T>*> & biList,int index){
    if(biList.size()!=2) return;
    BiListNode<T> * head = biList[0];
    BiListNode<T> * end = biList[1];
    
    BiListNode<T> * cur = head;
    BiListNode<T> * pre = head;
    
    if(index==0){
        BiListNode<T> * tmp = head;
        head=head->next;
        head->pre=nullptr;
        biList[0] = head;
        free(tmp);
        return;
        
    }
    int i=0;
    while(cur->next!=nullptr){
        if(i++==index){
            // del element
            BiListNode<T> * tmp = cur;
            pre->next=cur->next;
            cur->next->pre = pre;
            free(tmp);
        }
        else{
            pre=cur;
            cur = cur->next;
        }
    }
    if(i==index-1){
        // del the end node
        BiListNode<T> * tmp = end;
        end = pre;
        end->next=nullptr;
        biList[1] = end;
        free(tmp);
    }
}
```

