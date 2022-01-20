# c++ generate random number

C++中没有自带的random函数，要实现随机数的生成就需要使用rand()和srand()。

不过，由于rand()的内部实现是用线性同余法做的，所以生成的并不是真正的随机数，而是在一定范围内可看为随机的伪随机数。

### **rand（）**

rand()会返回一随机数值, 范围在0至RAND_MAX 间。RAND_MAX定义在stdlib.h, 其值为2147483647。

```c++
#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    for (int i = 0; i < 10; i++)
    {
        cout << rand()%100<< " ";
    }
    return 0;
}83 86 77 15 93 35 86 92 49 21   在100中产生随机数， 但是因为没有随机种子所以，下一次运行也是这个数，因此就要引出srand
```







### srand

**srand()可用来设置rand()产生随机数时的随机数种子。通过设置不同的种子，我们可以获取不同的随机数序列。**

**可以利用srand((int)(time(NULL))的方法，利用系统时钟，产生不同的随机数种子。不过要调用time()，需要加入头文件< ctime >。**

```c++
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand((int)time(0));  // 产生随机种子  把0换成NULL也行
    for (int i = 0; i < 10; i++)
    {
        cout << rand()%100<< " ";
    }
    return 0;
}13 8 99 28 43 84 34 24 72 19 11 90 27 79 94 4 9 42 84 26   两次产生的数据就不一样了
```





c++ 示例

```c++
#include <iostream>
#include <random>

using std::cout;
using std::endl;

constexpr int MIN = 1;
constexpr int MAX = 100;

constexpr int RAND_NUMS_TO_GENERATE = 10;

int main()
{
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(MIN, MAX);

    for (int n = 0; n < RAND_NUMS_TO_GENERATE; ++n) {
        cout << distr(eng) << "; ";
    }
    cout << endl;

    return 0;
}

```



可以指定不用的engine

```c++
std::random_device rd;
std::mt19937 eng(rd());
std::uniform_int_distribution<int> distr(MIN, MAX);
```





随机小数

```c++
std::random_device rd;
std::mt19937 eng(rd());
std::uniform_real_distribution<double> distr(MIN, MAX);
```

