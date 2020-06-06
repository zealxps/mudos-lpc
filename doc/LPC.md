# LPC 指导文档 #

主要包括课题内容，思考，及资料。

+ 发展历史。
  - 内容：了解LPC的历史，以及LPC的各个分支语言，LDMUD，FluffOS及Pike等等？
  - 预计: 2周。
  - 思考：
    最早LPC是干什么的？什么是MUDOS?  
    MUDOS诞生时候的硬件环境？ 
    后续发展了什么样的分支？ 
    LPC最早作为游戏语言都实现了什么？其他分支又做了什么发展？why?  
  - 资料：
    http://www.wikiwand.com/zh-sg/MUD
   
+ 数据类型。int, string, mapping, array，class等
  - 内容: 阅读LPC中string,mapping,array,class部分的实现。
  - 预计: 1~2周。
  - 思考: 
    SHARE_STRING和MALLOC_STRING的区别？  
    mapping中如何解决冲突？如何扩展table? array和class有什么区别？table,array,string是否有一些限制？why?

+ 内存管理。
  - 内容：阅读代码，理解MudOs中的malloc/free机制，了解各个数据结构包括mapping, array, object等的内存管理？
  - 预计: 1周。
  - 思考：
    MudOS的gc机制？object如何管理？何时释放？ref是什么？  
    如果将LPC的malloc/free换一套机制？怎么换？流行的内存管理库有哪些？做何区别？

+ timer机制。
  - 内容: callout机制部分的源码，及linux内核timer机制。
  - 预计: 1周。
  - 思考: 
    不同timer机制的原理，及评估性能？ 
    当出现系统逻辑执行过密时，会出现什么现象？是否追帧执行？

+ 对象类型。
  - 内容：阅读LPC中object,program等源码。
  - 预计: 1~2周。
  - 思考：
    LPC中class和object与其他面向对象语言有何不同?继承的原理是怎样的？ 
    object的内存结构是怎样的？如果要做到在线更新，需要做什么？LPC的循环引用是否有解决？如何解决？

+ 虚拟机执行。
  - 内容：LPC opcode执行流程，engine/logic的互调流程，堆栈管理等。
  - 预计: 1周。
  - 思考：
    说明白sp是干啥的？传参的原理是怎样的？堆栈错了怎么办？参数有没有限制？ 
    efun有上限吗？缘何？ 

+ LPC语法分析。
  - 内容：阅读LPC的语法分析源码，了解流程。
  - 预计: 2周。
  - 思考：
    从LPC语言到opcode，bison做了什么？如何改动某处语法？有没有可能把lpc直接编译成执行代码？
