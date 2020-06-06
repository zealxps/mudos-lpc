# LPC语言快速指导


## LPC语言简介



  LPC全称Lars Pensjǒ C，是由Lars Pensjǒ在1989年根据C语言开发的编程语言，主要是用
  来编写MUD游戏，使用LPC语言开发的MUD游戏被称为LPMUD。

  LPC类似C语言，语法大致相同，文件扩展名也为“.c”。不过LPC 是一面向对象语言，
  有对象（Object），但又没有类（class）的概念。和C语言相比LPC没有main()函数，但有
  一个create()函数，在对象载入时自动调用以完成初始化。


## LPC语法介绍



#### LPC注释和编码风格


    //LPC编码风格可参考现在的代码，主要标准为C和python的风格

    //单行注释以//开始。
    /*
    多行注释是这个样子
    */

#### LPC 宏和头文件


    //定义宏 #define 关键字
    #define MAXNUM  32767

    //用#include来导入头文件

    #include <rpc.h>

    //尖括号导入的文件是include目录下的文件
    //include目录以外的文件使用""来导入，类似于自定义的头文件
    #include "rc/rpc/gm.h"

#### LPC 继承


    //LPC也存在继承的概念，类似于C++的继承，为LPC提供了继承其他对象的函数和变量
    inherit "/std/object";

#### LPC 函数


    //函数的定义可以在头文件中定义，也可以在.c文件中定义，一般的函数基本和C相似
    返回值类型 函数名（变量类型 变量名）｛｝//函数原型
    int Add(int x, int y)
    {
        return x+y;
    }
    //LPC中函数的参数个数可变，声明一个可变参数的函数，需要使用关键字varargs，
    //在传入参数时，会根据参数的个数依次对参数赋值。
    varargs int Add(int x, int y, int z)
    {
        return x + y + z;
    }
    //如果你这样调用:Add(1, 2),返回值会是 1 + 2 = 3
    //如果你这样调用:Add(1, 2, 3),返回值会是 1 + 2 + 3 = 6

#### LPC 高级字符串处理


    //LPC字符串处理可参考C语言
    explode()返回一个字符串数组
    string s = "adc,def";
    string *arr = explode(s,",");//然后你可以遍历这个字符串数组
    //sscanf是LPC中一个非常重要的函数，类似于C语言
    string a,b;
    int ret;
    ret = sscanf(s,"%s,%s", a, b);
    //ret 为正确分析得到的参数个数，a = "abd",b="def"
    //需要注意的地方在于字符串中"abc" 与"def" 之间使用","隔开，所以参数格式
    //"%s,%s"也是以逗号隔开的，更具体的信息可参考mudOS帮助文档

    // 假设我们声明一个字符串，
    string a = "abcd";
    //我们可以使用下面的语句
    if(a[0] == 'a')
    if(a[0..1] == "ab")

#### LPC 类型


    //LPC的资料资料形态
    //LPC包含很多资料形态，基本和C差不多，这里主要讨论特殊的情况。
    //object是LPC中最重要特色，几乎可以说所有的东西都是一个object，它可以让我们使
    //用其他对象中的函数。
    对象->函数（参数）
    call_other(对象，“函数”，参数);
    object user;
    user->TellMe("");
    //如果要调用其他.c文件中的函数，可以这样
    "cmd/wizcmds/clone_item"->DoCmd(参数)；//若函数有返回值，也可以直接获得，就如
    //平常函数调用一样
    //object 可以作为外部函数的参数。

#### LPC 数据结构

    //阵列array类似于C语言的数组，我们可以声明一个数组
    int *arr = [];//一个空数组，当然可以声明其它类型的数组
    //添加一个元素到arr
    arr += [1];
    //判断一个元素是否在数组中，可以使用member_array函数来判断
    member_array(1, arr);//返回第一次出现时，出现在第几项
    //从一个array中删除元素
    arr -= [1];
    //数组的遍历，假设现在我们有一个整形数组arr，要遍历其中的元素可以这样
    foreach(int _int in arr)
        printf("%d", _int);

    //mapping 是LPC中的映射资料形态，有些类似于STL的map，key-value类型，可以使用
    整形，字符串来作为索引
    //声明一个mapping，必须初始化
    mapping map ={};
    map["int"] = 1;//插入一个值，
    map_delete(map,"int");//以关键字删除一个值对（key,value）
    //遍历一个mapping
    foreach（string _str, int _int in map）
        printf("%s,%d", _str, _int);

#### LPC 流程控制

    //LPC流程控制包括if，for,while,switch,return,continue,break,语法和C语言一样，
    // 可以参考C语言。


