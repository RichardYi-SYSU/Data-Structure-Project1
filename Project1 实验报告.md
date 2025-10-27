# Project1 实验报告

## 1.程序功能简要说明

本程序实现了针对一元稀疏多项式和算数表达式的求值计算器以及对应的图形化界面。其具体功能如下：

### 1.1 一元稀疏多项式简单计算器的功能

1. **输入并建立多项式：**用户输入多项式的项数和每一项的系数与指数，程序将用户输入的多项式转为链表形式存储，同时完成对原始输入的多项式的同指数项合并与按指数大小降序排列的操作
2. **多项式输出：**采用遍历链表的方式输出多项式，首先输出可读性高的多项式，例如`2x^3+x^2+1`，随后，按照实验文档中的要求输出整数序列，例如`3 2 3 1 2 1 0`
3. **多项式相加：**调用`AddPolynomial`函数，传入要相加的两个多项式A和B，并返回一个新的存储相加后的多项式的链表的头指针
4. **多项式相减：**调用`SubPolynomial`函数，传入要相加的两个多项式A和B，并遍历链表B中的各项系数并取负，构成-B，再将这一各项系数取负的多项式A和多项式-B传入`AddPolynomial`函数，从而得到相减后的多项式的链表，并返回此链表的头指针
5. **计算多项式在x处的值：**调用`Evaluate`函数，传入多项式A和x的值，使用sum变量来存储此值，遍历链表各项的系数与x相乘并结合指数的值得到此项的值，并且在sum中加上此值，最后返回sum
6. **求多项式的导函数：**调用`Derivative`函数，传入一个链表形式的多项式A，计算每一项的导函数值并写入新链表中，最后返回导函数中各项构成的链表的头指针
7. **多项式a和b相乘：**调用`MulPolynomial`函数，传入要相乘的两个多项式A和B，通过二重循环遍历计算两个链表中每一项的乘积，并累加到新链表中，随后为了保证得到的多项式中没有重复的指数的项，调用`removeDuplicates`函数对新链表中相同指数的项进行合并，再调用`mergeSort`函数使新链表的指数项降序排列
8. **错误输入的处理：**程序对于错误的用户输入也有相应的报错输出，比如对式子中存在除0项的检查与报错（如`0^-1`），当执行多项式在x处的值的计算的数据大小溢出时也有报错信息输出，当用户试图在未建立链表的前提下进行计算，输入的项数不为正整数，项的系数与指数的格式错误时，均会报错
### 1.2 算数表达式求值计算器的功能

  1. 用户输入一个以`#`结尾的算数表达式，程序读取这一字符串形式表达式，并在`EvaluateExpression`函数中使用运算数栈和运算符栈进行辅助，对字符串进行扫描的同时，结合`Precede`函数判断算符优先级，调用`Operate`函数执行出栈运算，并在每次操作结束时调用`PrintStates`函数打印当前的两个栈中元素的信息和操作的说明，最后一行给出表达式的计算结果（或错误信息）

  2. 本算数表达式求值计算器支持**加、减、乘、除、乘方、单目减**运算

  3. **错误输入的处理：**若用户输入了带字母的表达式，或其他语法不正确的表达式，如括号未闭合等，程序会传出“表达式错误“的信息并退出，若在对后缀表达式进行求值运算的过程中出现除0的情况，程序会传出“除零错误”的信息并退出。

### 1.3 图形化界面功能

  1. 为了方便用户进行即时的数据输入和输出，使用Qt这一GUI库来实现计算器的图形化界面
  1. 打开程序，首先出现让用户选择计算器模式的窗口，用户进行选择后进入对应计算器
  1. 表达式计算器GUI实现了让用户通过窗口中的数字，运算符来输入算数表达式，并执行运算
  1. 多项式计算器GUI实现了用户输入A和B两个多项式，并根据用户选择的功能进行对应多项式运算

## 2.程序运行截图
//图片内容在本地

## 3.部分关键代码及其说明

### 3.1 稀疏多项式求值计算器

为了实现文档中的七个功能，在polynomialCalc.cpp中分别构建了以下主要函数：

`CreatePolynomial`和`InsertTerm` ，`PrintPolynomial` ，`AddPolynomial`，`SubPolynomial`， `MulPolynomial`，`Derivative` ，`Evaluate`，分别用来实现多项式的创建、输出、相加、相减、相乘、求值、求导。

此外，为了实现去重、排序等功能，还构建了`mergeSort`， `removeDuplicates`等工具函数

#### 3.1.1 链表节点的定义

```c++
// 一元稀疏多项式链表节点定义
struct PolyNode {
    double coef;        // 系数
    int exp;            // 指数
    PolyNode* next;     // 指向下一项
};
```

- **说明：**此链表节点定义写在头文件中，定义了链表的每一个节点中的内容，包含系数与指数和指向下一个节点的指针。

#### 3.1.2 `AddPolynomial`函数

```c++
PolyNode* AddPolynomial(PolyNode* A, PolyNode* B) {
    // 如果两者都为空，返回0多项式
    if (!A && !B) {
        PolyNode* node = new PolyNode{0, 0, nullptr};
        return node;
    }
    
    // 若某一方为空，则返回另一方的拷贝
    if (!A) return CopyPolynomial(B);
    if (!B) return CopyPolynomial(A);
    
    PolyNode*dum = new PolyNode();
    dum->next=nullptr;
    PolyNode*cur=dum;
    // 双指针法，按指数合并
  	// 此处先调用mergeSort函数将两个多项式链表均进行按指数降序排序，方便后续计算
    PolyNode*p1=mergeSort(A);
    PolyNode*p2=mergeSort(B);
    while(p1!=nullptr&&p2!=nullptr)
    {
      	//如果指数不同就单纯将两项连接
        if((p1->exp)>(p2->exp))
        {
            PolyNode* node=new PolyNode();
            node->coef=p1->coef;
            node->exp=p1->exp;
            node->next=nullptr;
            cur->next=node;
            cur=cur->next;
            p1=p1->next;
        }else if((p1->exp)<(p2->exp))
        {
            PolyNode* node=new PolyNode();
            node->coef=p2->coef;
            node->exp=p2->exp;
            node->next=nullptr;
            cur->next=node;
            cur=cur->next;
            p2=p2->next;
        }else{
            //两个式子当前项的指数相同，则将系数相加，指数不变
            double sum=p1->coef+p2->coef;
            if(fabs(sum)>1e-8)
            {
                PolyNode*node=new PolyNode();
                node->coef=sum;
                node->exp=p1->exp;
                node->next=nullptr;
                cur->next=node;
                cur=cur->next;
            }
            p1=p1->next;
            p2=p2->next;
        } 
    }
    //连接剩下的链表
    while(p1!=nullptr)
    {
        PolyNode*node=new PolyNode();
        node->coef=p1->coef;
        node->exp=p1->exp;
        node->next=nullptr;
        cur->next=node;
        cur=cur->next;
        p1=p1->next;
    }
    while(p2!=nullptr)
    {
        PolyNode*node=new PolyNode();
        node->coef=p2->coef;
        node->exp=p2->exp;
        node->next=nullptr;
        cur->next=node;
        cur=cur->next;
        p2=p2->next;
    }

    PolyNode*ans=dum->next;
    delete(dum);//及时删除，避免内存泄漏
    return ans;
}
```

- **说明：**此函数首先对两个多项式是否都为空进行判断，若都空则返回0多项式，随后判断是否仅一个多项式为空（0），这样可以避免进行后续计算而省时。若两个多项式均不为0则进行计算。

  基本逻辑为：用两个指针p1，p2分别指向排序后的链表A和B的第一个节点，并引入一个哨兵头节点，用cur指针进行新链表的建立。当p1，p2所指的节点中的指数不相等时，比较两节点中指数的大小，用较大的指数及对应的系数作为新节点的指数和系数（为了指数降序排列），并使这一新节点接到新链表上。当p1，p2所指的节点中的指数相等时，就让新节点的指数与其相同，系数为两节点中系数相加，再将这一新节点接到新链表上。当一个指针遍历完了对应的链表后，便退出循环，将后续的节点接到新链表上，随后返回这一新链表的头指针（指向第一个项的指针），并删除哨兵节点，避免内存泄漏。

#### 3.1.3 `SubPolynomial`函数

```c++
PolyNode* SubPolynomial(PolyNode* A, PolyNode* B) {
    if (!A && !B) {
        PolyNode* node = new PolyNode{0, 0, nullptr};
        return node;
    }
    if (!A) {
        // 0-B=-B
        PolyNode*negB = nullptr;
        PolyNode*p=B;
      	//此处操作为遍历多项式B，将其每一项的系数取负后放入新链表，并返回其头节点
        while (p) {
            InsertTerm(negB, -p->coef, p->exp);
            p=p->next;
        }
        return negB;
    }
  	//相当于多项式B的值为0，A-0=A，将A拷贝后返回其头指针
    if (!B) return CopyPolynomial(A);

    PolyNode*dum=new PolyNode();
    dum->next=nullptr;
    PolyNode*cur=dum;
    PolyNode*p=B;
  	//此处操作为遍历多项式B，将其每一项的系数取负后放入新链表，并返回其头节点
    while(p!=nullptr)
    {
        PolyNode*node=new PolyNode();
        node->coef=-p->coef;
        node->exp=p->exp;
        node->next=nullptr;
        cur->next=node;
        cur=cur->next;
        p=p->next;

    }
    PolyNode*ans=dum->next;
    delete(dum);//及时删除，避免内存泄漏
    return AddPolynomial(A,ans);
}
```

- **说明：**多项式减法的实现是建立在加法的基础上的。其基本逻辑为，将链表B中的各项的系数取反后构成一个新链表，其头指针为ans，再把A和这一新链表传入`AddPolynomial`函数，即得到多项式减法的结果。

#### 3.1.4 `MulPolynomial`函数

```c++
PolyNode* MulPolynomial(PolyNode* A, PolyNode* B) {
    if (!A || !B) {
        PolyNode* node=new PolyNode{0,0,nullptr};
        return node;
    }
    
    PolyNode*dum = new PolyNode();//最终返回的结果链表
    PolyNode*cur=dum;
    //先排序，保证按指数降序排列
    PolyNode*p1=mergeSort(A);
    PolyNode*p2=mergeSort(B);
    
    while(p1!=nullptr)
    {
        p2=B;
        while(p2!=nullptr)
        {
            PolyNode*node=new PolyNode();
            node->coef=p1->coef*p2->coef;
            node->exp=p1->exp+p2->exp;
            node->next=nullptr;
            
            cur->next=node;
            cur=cur->next;
        
            p2=p2->next;//p2步进
        }
        p1=p1->next;//p1步进
    }
		//保险起见，将结果按指数降序排序下
    dum->next=mergeSort(dum->next);
  	//因为采用两重循环遍历的话会出现指数相同的项，需要removeDuplicates函数来对指数相同的项进行合并
    removeDuplicates(dum);

    PolyNode*ans=dum->next;
    delete(dum);//及时删除，避免内存泄漏
    return ans;
}
```

- **说明：**多项式乘法的实现是基于两个循环遍历链表来进行，这样可以保证两个链表中的每两个项都能被计算到乘积，但这种做法可能会出现结果链表中出现指数相同的项，因此需要`removeDuplicates`函数来对指数相同的项进行合并再返回结果链表

#### 3.1.5 `Derivative`函数

```c++
PolyNode* Derivative(PolyNode* A) {
    // coef*=exp; exp--; 跳过常数项
    PolyNode*dum=new PolyNode();
    dum->next=nullptr;

    PolyNode*cur=dum;
    PolyNode*p=A;
    while(p!=nullptr)
    {
        //若为常数项则跳过
        if(p->exp==0)
        {
    				p=p->next;
        }else{
            PolyNode*node=new PolyNode();
            node->coef=p->exp*p->coef;
            node->exp=p->exp-1;//指数乘系数，指数-1
            node->next=nullptr;
            cur->next=node;
            cur=cur->next;
            p=p->next;
        }
    }
		//若为空链表，则返回0
    if(dum->next==nullptr)
    {
        PolyNode*node=new PolyNode();
        node->coef=0;
        node->exp=0;
        node->next=nullptr;
        dum->next=node;
    }
    PolyNode*ans=dum->next;
    delete(dum);//及时删除，避免内存泄漏
    return ans;
}
```

- **说明：**此函数实现了对多项式的求导运算，即对于每一项，新节点的系数为其指数与其系数相乘，指数为该项的指数-1，再把这一节点接到新链表上，对于常数项，则直接跳过

#### 3.1.6 `Evaluate`函数

```c++
double Evaluate(PolyNode* A, double x) {
    if (!A) {
        cerr << "错误：多项式为空，无法计算。\n";
        return NAN;
    }
    double sum = 0;
    PolyNode* p = A;
    while (p) {
        if (x == 0 && p->exp < 0) {
            cerr << "错误：x=0 时存在除零项 x^" << p->exp << "。\n";
            return NAN;
        }
      
      	//term表示当前项在x处的值
        double term = p->coef * pow(x, p->exp);
      
        if (isnan(term) || isinf(term)) {
            cerr << "错误：计算溢出或非法运算。\n";
            return NAN;
        }
        sum += term;
        p = p->next;
    }
    return sum;
}
```

- **说明：**此函数实现了对多项式在给定x的值下的求值运算，采用对每一项的值进行计算并累加的方法。此外，由于求值过程中可能出现`0^-1`的形式，这是错误的计算结果，因此需要输出错误信息，而且，若求值得到的数过大导致溢出，也应该输出错误信息。

#### 3.1.7 `CreatePolynomial`和`InsertTerm`函数

```c++
void CreatePolynomial(PolyNode*& head) {
    int n;
    cout << "请输入多项式项数：";
    if (!(cin >> n) || n <= 0) {
      	//传出错误信息
        cerr << "输入错误：项数必须为正整数。\n";
        cin.clear(); cin.ignore(1024, '\n');
        return;
    }

    cout << "依次输入每项的系数与指数（空格分隔）：\n";
    for (int i = 0; i < n; i++) {
        double c; int e;
        if (!(cin >> c >> e)) {
          	//传出错误信息
            cerr << "输入错误：第 " << i + 1 << " 项数据格式错误，应为“系数 指数”。\n";
            cin.clear(); cin.ignore(1024, '\n');
            return;
        }
        InsertTerm(head, c, e);
    }
}
```

```c++
void InsertTerm(PolyNode*& head, double coef, int exp) {//按指数降序插入新项
    if (fabs(coef) < 1e-8) return;

    PolyNode* prev = nullptr;
    PolyNode* curr = head;

    // 找到插入位置
    while (curr && curr->exp > exp) {
        prev = curr;
        curr = curr->next;
    }

    if (curr && curr->exp == exp) {
        // 同指数项合并
        curr->coef += coef;
        if (fabs(curr->coef) < 1e-8) {
            // 删除该节点
            if (prev) prev->next = curr->next;
            else head = curr->next;
            delete curr;
        }
    } else {
        // 创建新节点
        PolyNode* node = new PolyNode;
        node->coef = coef;
        node->exp = exp;
        node->next = curr;

        if (prev) prev->next = node;
        else head = node;
    }
}
```

- **说明：**这两个函数彼此配合，`CreatePolynomial`函数读取各项的系数与指数，在对其做异常输入的处理后，将其传入`InsertTerm`函数，按指数降序排列各项。实现了以链表形式存储多项式的功能。

#### 3.1.8 `PrintPolynomial`函数

```c++
void PrintPolynomial(PolyNode* head) {
    if (!head) {
        cout << "0" << endl;
        cout << "输出序列：0" << endl;
        return;
    }

    // 第一行：标准格式输出
    PolyNode* p = head;
    int count = 0;
    while (p) {
        if (p->exp == 0)
            cout << p->coef;
        else
            cout << p->coef << "x^" << p->exp;

        if (p->next && p->next->coef >= 0)
            cout << " +";
        else if (p->next)
            cout << " ";
        count++;
        p = p->next;
    }
    cout << endl;

    // 第二行：整数序列输出（项数 + 系数指数）
    cout << "输出序列：" << count;
    p = head;
    while (p) {
        cout << " " << p->coef << " " << p->exp;
        p = p->next;
    }
    cout << endl;
}
```

- **说明：**这一函数的输出为两行，第一行为标准的多项式形式，如`2x^3+x^1+7`这种形式，便于用户阅读。此外，为了满足文档中输出整数序列的要求，在第二行进行整数序列的输出，对于上面的例子，其整数序列就为`3 2 3 1 1 7 0`

以上便是稀疏多项式计算器的部分关键代码的内容及说明，除此之外的一些工具函数的功能则在源代码中以注释的形式写出。

### 3.2 算数表达式求值计算器

为了实现算数表达式计算器的功能，在expressionCalc.cpp中，首先使用线性表的朴素编码方式，在数组基础上实现了栈的定义和操作，并构建了以下主要函数：

`Precede`，`Operate`，`EvaluateExpression`，分别用来实现算符优先级的判断，对指定运算符和运算数的运算，表达式的解析及同时利用字符、运算数辅助栈来实现求值。

此外，还构建了`PrintStates`函数来打印利用辅助栈进行运算中的每一步的操作及运算数栈和运算符栈中的内容。

#### 3.2.1 栈的实现

```c++
//栈定义
struct charStack { int top; char data[MAX_SIZE]; };
struct numStack  { int top; double data[MAX_SIZE]; };
//栈初始化
void InitCharStack(charStack *s){ s->top = -1; }
void InitNumStack (numStack  *s){ s->top = -1; }
//栈判空
bool IsCharStackEmpty(charStack *s){ return s->top == -1; }
bool IsNumStackEmpty (numStack  *s){ return s->top == -1; }
//压栈
bool PushCharStack(charStack *s, char x){
    if(s->top == MAX_SIZE - 1) return false;
    s->data[++(s->top)] = x;
    return true;
}
bool PushNumStack(numStack *s, double x){
    if(s->top == MAX_SIZE - 1) return false;
    s->data[++(s->top)] = x;
    return true;
}
//弹栈
bool PopCharStack(charStack *s, char &x){
    if(s->top == -1) return false;
    x = s->data[(s->top)--];
    return true;
}
bool PopNumStack(numStack *s, double &x){
    if(s->top == -1) return false;
    x = s->data[(s->top)--];
    return true;
}
//获取栈顶
char   GetCharStackTop(charStack *s){ return s->top == -1 ? '\0' : s->data[s->top]; }
double GetNumStackTop (numStack  *s){ return s->top == -1 ? 0.0  : s->data[s->top]; }
```

- **说明：**使用数组作为栈的内部存储结构，构建了charStack结构体和numStack结构体，分别用来当作运算符辅助栈和运算数辅助栈，并实现了栈的对应操作。

#### 3.2.2 `Precede`函数

```c++
//运算符优先级的判断，基于文档中的运算符优先级表
char Precede(char op1, char op2) {
    const char prec[8][8] = {
    //       +    -    *    /    ^    (    )    #
    /*+*/   '>', '>', '<', '<', '<', '<', '>', '>',
    /*-*/   '>', '>', '<', '<', '<', '<', '>', '>',
    /***/   '>', '>', '>', '>', '<', '<', '>', '>',
    /*/*/   '>', '>', '>', '>', '<', '<', '>', '>',
    /*^*/   '>', '>', '>', '>', '<', '<', '>', '>',   // 乘方为右结合
    /*(*/   '<', '<', '<', '<', '<', '<', '=', 'e',
    /*)*/   '>', '>', '>', '>', '>', 'e', '>', '>',
    /*#*/   '<', '<', '<', '<', '<', '<', 'e', '='
    };

    int i, j;
    switch(op1){
        case '+': i=0; break; case '-': i=1; break;
        case '*': i=2; break; case '/': i=3; break;
        case '^': i=4; break; case '(': i=5; break;
        case ')': i=6; break; case '#': i=7; break;
        default: return 'e';
    }
    switch(op2){
        case '+': j=0; break; case '-': j=1; break;
        case '*': j=2; break; case '/': j=3; break;
        case '^': j=4; break; case '(': j=5; break;
        case ')': j=6; break; case '#': j=7; break;
        default: return 'e';
    }
    return prec[i][j];
}
```

- **说明：**此函数在文档中的运算符优先级表的基础上实现了乘方的优先级判断，op1代表运算符栈顶的元素，op2代表从表达式中读取到的元素，其具体比较结果意义及对应的操作如下：

| 比较结果 | 意义                                                  | 操作                     |
| -------- | ----------------------------------------------------- | ------------------------ |
| `<`      | 栈顶运算符优先级 **低于** 当前运算符                  | **入栈** 当前运算符      |
| `=`      | 表示匹配的括号或结束符（例如 `(` 对 `)`、`#` 对 `#`） | **弹出左括号或结束标志** |
| `>`      | 栈顶运算符优先级 **高于或等于** 当前运算符            | **弹栈并进行一次运算**   |
| `e`      | 表示比较非法或不支持                                  | 报错                     |

#### 3.2.3 `Operate`函数

```c++
//计算函数
double Operate(double a, char theta, double b) {
    switch (theta) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                cout << "错误：除数为零！" << endl;
                exit(ERROR);
            }
            return a / b;
        case '^': 
            if(a==0&&b<0.0)
            {
                cout<<"错误：除数为零！"<<endl;
                exit(ERROR);
            }
            return pow(a, b);
    }
    return 0;
}
```

- **说明：**此函数实现了**乘方、加、减、乘、除**的运算。此外，由于除法在除0的情况下，乘方在底数为0，指数为负数的情况下会出现异常，因此为其增加了报错信息的输出，并在报错后退出程序。

#### 3.2.4 `EvaluateExpression`函数

```c++
//表达式求值
double EvaluateExpression() {
    charStack OPTR;
    numStack  OPND;
    InitCharStack(&OPTR);
    InitNumStack(&OPND);
    PushCharStack(&OPTR, '#');

    bool negFlag[MAX_SIZE];   // 标记每个括号是否为取反括号
    int flagTop = -1;

    cout << "请输入一个以'#'结尾的整数算术表达式: ";
    
    //输入字符串
    string expr;
    getline(cin, expr);

    if (expr.empty()) getline(cin, expr);
    expr += '#';

    cout << "------------------------------------------------------------------\n";
    cout << "| 运算符栈\t| 运算数栈\t| 输入字符\t| 主要操作\n";
    cout << "------------------------------------------------------------------\n";
    PrintStates(&OPTR, &OPND, expr[0], "初始化");

    int i = 0;

    // 用 token 类型来区分单目 / 二元运算符
    enum LastTok { START, OPERAND, OPERATOR, LPAREN, RPAREN };
    LastTok last = START;

    while (expr[i] != '#' || GetCharStackTop(&OPTR) != '#') {
        char c = expr[i];
        if (isspace(c)) { i++; continue; }

        //单目减号判断
        if (c == '-' && (last == START || last == OPERATOR || last == LPAREN)) {
            i++;
            // -(...) 情况
            if (expr[i] == '(') {
                PushCharStack(&OPTR, '(');
                negFlag[++flagTop] = true;  // 记录这是取反括号
                PrintStates(&OPTR, &OPND, expr[i], "单目负号 + '(' → 标记为取反括号");
                i++;
                last = LPAREN;
                continue;
            }
            // -数字 情况
            else if (isdigit(expr[i])) {
                double num = 0;
                string num_str;
              	//将连续数字字符转为整数
                while (isdigit(expr[i])) {
                    num = num * 10 + (expr[i] - '0');
                    num_str += expr[i];
                    i++;
                }
                num = -num;
                PushNumStack(&OPND, num);
                PrintStates(&OPTR, &OPND, expr[i], ("检测到单目负号 → 压入 " + to_string(num)).c_str());
                last = OPERAND;
                continue;
            }
        }

        //数字
        if (isdigit(c)) {
            double num = 0;
            string num_str;
            //实现连续数字字符转整数
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                num_str += expr[i];
                i++;
            }
            PushNumStack(&OPND, num);
            PrintStates(&OPTR, &OPND, expr[i], ("操作数 " + num_str + " 入栈").c_str());
            last = OPERAND;
            continue;
        }

        //运算符优先级处理
        char top = GetCharStackTop(&OPTR);
        switch (Precede(top, c)) {
            case '<': {
                PushCharStack(&OPTR, c);
                if (c == '(') {
                    negFlag[++flagTop] = false;  // 普通左括号标记
                    last = LPAREN;
                } else last = OPERATOR;
                PrintStates(&OPTR, &OPND, c, "栈顶运算符优先级低, 当前运算符入栈");
                i++;
                break;
            }

            case '=': {
                char op;
                PopCharStack(&OPTR, op); // 弹出 '('
                PrintStates(&OPTR, &OPND, c, "脱括号");
                i++;

                // 若该括号为取反括号，则取反
                if (flagTop >= 0 && negFlag[flagTop--]) {
                    double val;
                    PopNumStack(&OPND, val);
                    PushNumStack(&OPND, -val);
                    PrintStates(&OPTR, &OPND, c, "取反括号生效：结果变号");
                }
                last = OPERAND;
                break;
            }

            case '>': {
                char theta;
                double a, b;
                PopCharStack(&OPTR, theta);
                PopNumStack(&OPND, b);
                PopNumStack(&OPND, a);
                //进行计算
                double result = Operate(a, theta, b);
                PushNumStack(&OPND, result);
                char op_buf[60];
                snprintf(op_buf, sizeof(op_buf), "归约: %.4f %c %.4f = %.4f", a, theta, b, result);
                PrintStates(&OPTR, &OPND, c, op_buf);
                last = OPERAND;
                break;
            }

            case 'e':
                cout << "语法错误！" << endl;
                return ERROR;
        }
    }

    double final_result;
    PopNumStack(&OPND, final_result);
    cout << "------------------------------------------------------------------\n";
    return final_result;
}

```

- **说明：**此函数是表达式求值计算器的主要函数，其执行逻辑为：
  1. 函数分别创建运算数栈和运算符栈用于辅助存储运算数和运算符，并向运算符栈中压入#来初始化，还构建了一个bool类型的negFlag数组用来判断当前括号是否为取反括号，以及一个枚举类型LastTok用来判断当前输入的是数字、运算符还是括号，并在正确的时机进行运算或调整运算符栈和操作数栈
  2. 函数提示用户输入字符串expr，随后打印初始化相关信息，并进入主循环
  3. 在主循环中，首先判断当前减号是否为单目减号。由于单目减仅可能出现在字符串头、前一个字符为运算符、前一个字符为左括号的情况，所以在单目减判断时增加对前一个字符的判断。随后对单目减的施加对象进行分别处理：
     - 当减号被识别为单目算符，并且其后出现左括号时，将其压入栈，并标记为取反括号（即在negFlag中将其标记为True），并打印对应的操作信息和栈信息，将枚举变量设为左括号
     - 当减号被识别为单目算符，并且其后出现数字时，继续遍历字符串，直到该整数的末位，并用循环得到这一整数的值，把它取负后压入运算数栈，并打印对应的操作信息和栈信息，将枚举变量设为运算数
  4. 随后若读取到数字，则遍历至该整数的末尾，并得到该整数的值，压栈，打印对应操作信息和栈信息，将枚举变量设为运算数
  5. 若读取到运算符，则调用`Precede`函数，将当前读取的运算符与栈顶元素相比较
     - 若栈顶算符优先级低于当前算符，则压入运算符栈，并将枚举变量设为运算符。此外，若扫描到左括号，则此时的左括号为普通括号（不为取反括号），并将枚举变量设为左括号。随后打印操作信息和栈信息
     - 若栈顶算符与当前算符优先级相同，则说明左右括号相遇，执行脱括号操作，打印对应操作。此外，若negFlag此时记录的该括号为取反括号，则将运算数栈顶元素弹出取负后再压栈（相当于将括号内的运算结果取负，因为是单目减），再将枚举变量设为操作数后，打印对应操作
     - 若栈顶运算符低于当前算符，则从运算数栈中先后弹出两个数，命名为b和a，再调用`Operate`函数，将其计算出的值压入运算数栈，并打印对应操作信息及栈信息
     - 若比较优先级时出现错误（比如括号未闭合，Precede返回'e'）则输出语法错误的信息，并返回ERROR值
  6. 最后运算数栈顶存储的数字便是表达式计算的结果，将其弹出并输出

以上就是表达式计算器中的部分关键代码的内容，此外的工具函数的功能则在源代码中以注释的形式写出。

### 3.3 Qt GUI界面

在图形化界面中，用户输入到文本框中的是String类型的字符串，对于表达式求值计算器而言，将此字符串传入expressionCalcGUI.cpp中的`EvaluateExpression`函数即可得到对应的结果（与上文中的此函数不同之处仅在于将字符串由函数内输入改为参数传入，以及取消了详细操作内容的打印）。但由于多项式计算器是基于链表来实现的，因此需要对字符串进行解析，将其转为链表形式存储，还需要将结果链表解析为字符串，显示在GUI的文本框中，核心代码为poly_adapter.cpp中的`fromString`和`toString`，如下所示。

####  3.3.1`fromString`函数

```c++
// fromString：支持形如  -2.5x^3 + 7x - 1 、 x^2-1 、 -x 、 3  等，将多项式字符串解析为链表后返回其头指针
PolyNode* fromString(const std::string& src) {
    PolyNode* head = nullptr;
    const std::string s = removeSpaces(src);
    const double EPS = 1e-12;
    if (s.empty()) return head; // 视为空多项式
    size_t i = 0, n = s.size();
    while (i < n) {
        // 1) 读取项的符号
        int sign = +1;
        if (s[i] == '+') { sign = +1; ++i; }
        else if (s[i] == '-') { sign = -1; ++i; }
        // 注意：第一个项若没写符号，默认正
        // 2) 读取系数（可省略；若后面紧跟 x 则系数默认 1）
        double coef = 0.0;
        bool hasCoef = false;
        if (i < n && (std::isdigit(static_cast<unsigned char>(s[i])) || s[i]=='.')) {
            if (parseSignedDouble(s, i, coef)) hasCoef = true;
        }
        // 3) 看是否有 x / X
        bool hasX = false;
        int exp = 0;
        if (i < n && (s[i]=='x' || s[i]=='X')) {
            hasX = true;
            ++i;
            exp = 1; // 默认 x^1
            // 3.1) 看是否有 ^ 指数
            if (i < n && s[i] == '^') {
                ++i;
                // 指数允许写 +/- 号（如 x^-2），否则默认正
                int eSign = +1;
                if (i < n && (s[i]=='+' || s[i]=='-')) {
                    eSign = (s[i]=='-') ? -1 : +1;
                    ++i;
                }
                int e = 0;
                if (!parseSignedInt(s, i, e)) {
                    // 没有合法整数指数，回退为 1
                    e = 1;
                }
                exp = eSign * e;
            }
            // 若未显式给系数，则系数为 1
            if (!hasCoef) coef = 1.0;
        } else {
            // 没有 x：这就是常数项；如果也没读到数字，且不是末尾，视为输入异常——此处直接跳过该字符以避免死循环
            if (!hasCoef) {
                // 容错：跳过一个字符（避免无限循环），也可选择直接返回当前已解析内容
                ++i;
                continue;
            }
            exp = 0;
        }
        coef *= sign;
        if (std::fabs(coef) > EPS) {
            // 传给多项式计算器中的插入链表的函数，实现指数降序排列
            InsertTerm(head, coef, exp);
        }
        // 4) 下一项必须从 + 或 - 继续；如果遇到其他字符，就让循环继续处理（上面的容错会推进 i）
        if (i < n && s[i] != '+' && s[i] != '-' && s[i] != 'x' && s[i] != 'X' && !std::isdigit(static_cast<unsigned char>(s[i])) && s[i] != '.') {
            ++i; // 容错推进，防止卡死
        }
    }
    return head;
}
```

- **说明：**其使用到的链表节点的定义与部分调用的函数仍然来自polynomialCalc.cpp，其流程为：

  1. 首先去除字符串中的空格，确保解析时不受影响。
  2. 解析每一项
     - 对于每一项，首先判断符号（正负号）。默认第一个项为正号。
     - 解析系数，如果没有显式给出系数，默认为 `1` 或 `-1`。
     - 解析 `x` 和指数 `^`，如果没有给出指数，则默认指数为 `1`，如果指数未给出，默认为 `0`。
  3. 根据解析的系数和指数，将每一项插入到链表中（调用了`InsertTerm`函数）。链表会按指数降序排序，并合并同指数项。
  4. 容错处理：在遇到无效字符或格式时，会跳过当前字符继续解析，避免死循环。


#### 3.3.2 `toString`函数

```c++
// toString：把链表变回如 3x^2 - 5x + 1 的形式
std::string toString(PolyNode* head) {
    if (!head) return "0";
		//创建一个输出流对象，后续将往里输入内容
    std::ostringstream out;
    const double EPS = 1e-12;
    bool first = true;
		//遍历多项式链表中的每个节点
    for (PolyNode* p = head; p; p = p->next) {
        double c = p->coef;
        int e = p->exp;
        if (std::fabs(c) <= EPS) continue;

        // 确定符号
        if (first) {
            if (c < 0) out << "-";
        } else {
            out << (c >= 0 ? " + " : " - ");
        }

        double a = std::fabs(c);

        if (e == 0) {
            // 常数项
            out << fmtDouble(a);
        } else {
            // 非常数项：系数为1时省略“1”
            if (std::fabs(a - 1.0) > 1e-12) out << fmtDouble(a);
            out << "x";
            if (e != 1) out << "^" << e;
        }

        first = false;
    }

    std::string s = out.str();
    if (s.empty()) return "0";
  	//返回一个字符串，用于GUI的显示
    return s;
}
```

- **说明：**此函数实现了将存储多项式的链表中的每个节点的指数与系数转为字符串形式存储，具体逻辑为：
  1. 循环遍历链表中各个节点，将每一项的指数与系数存储起来，若系数为0，则跳过该项
  2. 确定符号，如果第一项为负号则直接输出`-`；若为正则不输出符号。对于后续项，根据符号输出 `+` 或 `-`，`first` 用于标记是否是第一项
  3. 每一项的输出，若指数为0，说明为常数项，否则输出类似`x^e`形式的项至输出流中
  4. 将输出流对象存储字符串并返回

以上是计算器的GUI实现的部分关键代码。除此之外，为了构建GUI界面，还需要.ui文件以及对应的按钮的逻辑实现的mainwindow.cpp等文件，这些文件已放在“源代码（GUI版本）”的文件夹中，此处就不再赘述。

## 4.程序运行方式简要说明

### 4.1 命令行版本

1. 首先，程序显示一个选择界面，引导用户选择对应功能：选择1则执行算术表达式求值计算器功能，选择2则执行稀疏多项式计算功能，选择0则退出程序
2. 若用户选择1，程序执行`ExpressionEvaluator`函数，提示用户输入以`#`结尾的整数表达式，并执行`EvaluateExpression`函数，命令行中会显示每一步的栈的元素的信息及对应的入栈或出战操作信息，并在最后输出结果或错误信息。随后，程序回到选择界面。
3. 若用户选择2，程序执行`polynomialCalculator`函数，其包含9个选项，对应创建多项式A，创建多项式B，输出多项式A和B，A+B，A-B，A*B，求A导函数，求A在x处的值，退出。
   - **创建多项式A，B：**调用`CreatePolynomial`函数，输入项数，每项的系数、指数建立多项式链表
   - **输出多项式A，B：**调用`PrintPolynomial`函数，第一行输出多项式形式，第二行输出整数序列形式，且按指数降序排列
   - **A+B：**调用`AddPolynomial`函数，并输出相加后的结果
   - **A-B：**调用`SubPolynomial`函数，并输出相减后的结果
   - **A*B：**调用`MulPolynomial`函数，并输出相乘后的结果
   - **求A导函数：**若A尚未建立，则输出错误，否则调用`Derivative`函数，并输出求导后的结果
   - **求A在x处的值：**若A尚未建立，则输出错误，否则提示用户输入x，再调用`Evaluate`函数，并输出结果
4. 若用户选择0，则直接退出程序

### 4.2 GUI版本

> 本人使用MacOS进行Qt的计算器GUI的开发，因此构建出来的可执行文件为MacOS下的.app文件，而非Windows操作系统中的.exe文件。理论上也可用相同的Qt项目代码在Windows的环境中构建出功能界面相同的.exe版本（Qt为跨平台软件）

1. 首先显示一个窗口，输出”请选择要使用的计算器模式“引导用户选择对应的计算器，通过点击窗口中的两个不同按钮来实现窗口跳转
2. 当用户点击“表达式求值计算器”的按钮，进入表达式求值计算器的主界面，其包含数字输入按钮、加、减、乘、除、乘方、左右括号、退格、清零和求值按钮，用户根据自己需求按下对应按钮输入表达式，输入完成后点击Evaluate Expression按钮，随后程序将输入的表达式字符串传递到expressionCalcGUI.cpp中的`EvaluateExpression`函数，并返回错误信息或运算结果，显示在文本框中
3. 当用户点击“多项式求值计算器”的按钮，进入多项式求值计算器的主界面，其包含数字输入按钮、小数点、加、减、乘方、$x$的键入、退格、清零按钮，以及用于计算的A+B、A-B、A*B、dA/dx、dB/dx按钮，和编辑多项式的Edit A/B、Save A/B按钮。
   - 首先，用户点击Edit A，输入A的多项式，类似`x^2+x+1`的形式，并点击Save A保存，这样多项式A就会显示在A= 的文本框中。同理，输入并创建多项式B
   - 随后，用户选择想要执行的操作，按下对应按钮，结果就会显示在最上方文本框中。此外，对于求值的操作，需要用户从键盘输入数字到Eval A at x：这一文本框中，并点击Go执行求值计算，结果或报错信息同样会显示在最上方文本框中
   - 若用户想更改多项式A或B的值，只需重新Edit、Save即可
4. 当用户点击左上角红叉即可退出程序

