# 线程与内核对象的同步 

## 通知/未通知状态

当进程正在运行的时候，进程内核对象处于未通知状态，当进程终止运行的时候，它就变为已通知状态。进程内核对象中是个布尔值，当对象创建时，该值被初始化为 FA L S E（未通知状态）。当进程终止运行时，操作系统自动将对应的对象布尔值改为 T R U E，表示该对象已经得到通知。 与进程内核对象一样，线程内核对象也可以处于已通知状态或未通知状态。 

下面的内核对象可以处于已通知状态或未通知状态：
■ 进程 ■ 文件修改通知
■ 线程 ■ 事件
■ 作业 ■ 可等待定时器 

■ 文件 ■ 信标
■ 控制台输入 ■ 互斥对象 

## 等待函数

等待函数可使线程自愿进入等待状态，直到一个特定的内核对象变为已通知状态为止。这些等待函数中最常用的是WaitForSingleObject :  

```c++
DWORD WINAPI WaitForSingleObject(
   HANDLE hHandle,
   DWORD  dwMilliseconds
);
```

当线程调用该函数时，第一个参数 h O b j e c t标识一个能够支持被通知 /未通知的内核对象（前面列出的任何一种对象都适用）。第二个参数d w M i l l i s e c o n d s允许该线程指明，为了等待该对象变为已通知状态，它将等待多长时间。 

## 成功等待的副作用 

对于有些内核对象来说，成功地调用 Wa i t F o r S i n g l e O b j e c t和Wa i t F o r M u l t i p l e O b j e c t s，实际上会改变对象的状态。成功地调用是指函数发现对象已经得到通知并且返回一个相对于WA I T _ O B J E C T _ 0的值。如果函数返回WA I T _ T I M E O U T或WA I T _ FA I L E D，那么调用就没有成功。如果函数调用没有成功，对象的状态就不可能改变。
当一个对象的状态改变时，我称之为成功等待的副作用。例如，有一个线程正在等待自动清除事件对象（本章后面将要介绍）。当事件对象变为已通知状态时，函数就会发现这个情况，并将WA I T _ O B J E C T _ 0返回给调用线程。但是就在函数返回之前，该事件将被置为未通知状态，这就是成功等待的副作用。

Wa i t F o r S i n g l e O b j e c t的返回值能够指明调用线程为什么再次变为可调度状态。如果线程等待的对象变为已通知状态，那么返回值是 WA I T _ O B J E C T _ 0。如果设置的超时已经到期，则返回值是 WA I T _ T I M E O U T。如果将一个错误的值（如一个无效句柄）传递给 Wa i t F o r S i n g l eO b j e c t，那么返回值将是WA I T _ FA I L E D  。

## 事件内核对象 

在所有的内核对象中，事件内核对象是个最基本的对象。它们包含一个使用计数（与所有内核对象一样），一个用于指明该事件是个自动重置的事件还是一个人工重置的事件的布尔值，另一个用于指明该事件处于已通知状态还是未通知状态的布尔值。

事件能够通知一个操作已经完成。有两种不同类型的事件对象。一种是人工重置的事件，另一种是自动重置的事件。当人工重置的事件得到通知时，等待该事件的所有线程均变为可调度线程。当一个自动重置的事件得到通知时，等待该事件的线程中只有一个线程变为可调度线程。

当一个线程执行初始化操作，然后通知另一个线程执行剩余的操作时，事件使用得最多。事件初始化为未通知状态，然后，当该线程完成它的初始化操作后，它就将事件设置为已通知状态。这时，一直在等待该事件的另一个线程发现该事件已经得到通知，因此它就变成可调度线程。 

下面是C r e a t e E v e n t函数，用于创建事件内核对象： 

```c++
HANDLE WINAPI CreateEvent(
   LPSECURITY_ATTRIBUTES lpEventAttributes,
   BOOL                  bManualReset,
   BOOL                  bInitialState,
   LPCTSTR               lpName
);
```

事件内核对象的其他操作函数，OpentEvent，SetEvent，ResetEvent，OpentEvent。

## 等待定时器内核对象 

等待定时器是在某个时间或按规定的间隔时间发出自己的信号通知的内核对象。它们通常用来在某个时间执行某个操作。
若要创建等待定时器，只需要调用 C r e a t e Wa i t a b l e Ti m e r函数： 

## 信标内核对象 

信标内核对象用于对资源进行计数。它们与所有内核对象一样，包含一个使用数量，但是它们也包含另外两个带符号的 3 2位值，一个是最大资源数量，一个是当前资源数量。最大资源数量用于标识信标能够控制的资源的最大数量，而当前资源数量则用于标识当前可以使用的资源的数量。 

信标的使用规则如下：
• 如果当前资源的数量大于0，则发出信标信号。
• 如果当前资源数量是0，则不发出信标信号。
• 系统决不允许当前资源的数量为负值。
• 当前资源数量决不能大于最大资源数量 

下面的函数用于创建信标内核对象： 

```c++
HANDLE WINAPI CreateSemaphore(
   LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
   LONG                  lInitialCount,
   LONG                  lMaximumCount,
   LPCTSTR               lpName
);
```

通过调用ReleaseSemaphore函数，线程就能够对信标的当前资源数量进行递增：

```c++
BOOL WINAPI ReleaseSemaphore(
   HANDLE hSemaphore,
   LONG   lReleaseCount,
   LPLONG lpPreviousCount
); 
```

## 互斥对象内核对象 

互斥对象（m u t e x）内核对象能够确保线程拥有对单个资源的互斥访问权。实际上互斥对象是因此而得名的。互斥对象包含一个使用数量，一个线程 I D和一个递归计数器。互斥对象的行为特性与关键代码段相同，但是互斥对象属于内核对象，而关键代码段则属于用户方式对象。这意味着互斥对象的运行速度比关键代码段要慢。但是这也意味着不同进程中的多个线程能够访问单个互斥对象，并且这意味着线程在等待访问资源时可以设定一个超时值。 

ID用于标识系统中的哪个线程当前拥有互斥对象，递归计数器用于指明该线程拥有互斥对 象的次数。互斥对象有许多用途，属于最常用的内核对象之一。通常来说，它们用于保护由多个线程访问的内存块。如果多个线程要同时访问内存块，内存块中的数据就可能遭到破坏。互斥对象能够保证访问内存块的任何线程拥有对该内存块的独占访问权，这样就能够保证数据的完整性。 

互斥对象的使用规则如下：
• 如果线程I D是0（这是个无效I D），互斥对象不被任何线程所拥有，并且发出该互斥对象的通知信号。
• 如果I D是个非0数字，那么一个线程就拥有互斥对象，并且不发出该互斥对象的通知信号。
• 与所有其他内核对象不同， 互斥对象在操作系统中拥有特殊的代码，允许它们违反正常的规则（后面将要介绍这个异常情况）。 

若要使用互斥对象，必须有一个进程首先调用 C r e a t e M u t e x，以便创建互斥对象： 

```c++
HANDLE CreateMutex(
LPSECURITY_ATTRIBUTES lpMutexAttributes, // 指向安全属性的指针
BOOL bInitialOwner, // 初始化互斥对象的所有者
LPCTSTR lpName // 指向互斥对象名的指针
);
```

关于互斥量操作函数的使用说明参考：[Windows编程--互斥量Mutex操作函数](http://blog.csdn.net/libing403/article/details/77074986)

通过调用 O p e n M u t e x，另一个进程可以获得它自己进程与现有互斥对象相关的句柄： 

```c++
HANDLE OpenMutex(
DWORD dwDesiredAccess, // access
BOOL bInheritHandle, // inheritance option
LPCTSTR lpName // object name
);
```

一旦线程成功地等待到一个互斥对象，该线程就知道它已经拥有对受保护资源的独占访问权。试图访问该资源的任何其他线程（通过等待相同的互斥对象）均被置于等待状态中。当目前拥有对资源的访问权的线程不再需要它的访问权时，它必须调用 R e l e a s e M u t e x函数来释放该互斥对象： 

```c++
BOOL WINAPI ReleaseMutex(
HANDLE hMutex
);
```

该函数将对象的递归计数器递减 1。如果线程多次成功地等待一个互斥对象，在互斥对象的递归计数器变成 0之前，该线程必须以同样的次数调用 R e l e a s e M u t e x函数。当递归计数器到达0时，该线程I D也被置为0，同时该对象变为已通知状态 。

## 释放问题 

互斥对象不同于所有其他内核对象，因为互斥对象有一个“线程所有权”的概念。本章介绍的其他内核对象中，没有一种对象能够记住哪个线程成功地等待到该对象，只有互斥对象能够对此保持跟踪。互斥对象的线程所有权概念是互斥对象为什么会拥有特殊异常规则的原因，这个异常规则使得线程能够获取该互斥对象，尽管它没有发出通知。这个异常规则不仅适用于试图获取互斥对象的线程， 而且适用于试图释放互斥对象的线程。当一个线程调用R e l e a s e M u t e x函数时，该函数要查看调用线程的 I D是否与互斥对象中的线程I D相匹配。如果两个I D相匹配，递归计数器就会像前面介绍的那样递减。如果两个线程的 I D不匹配，那么R e l e a s e M u t e x函数将不进行任何操作，而是将 FA L S E（表示失败）返回给调用者。此时调用G e t L a s t E r r o r，将返回E R R O R _ N O T _ O W N E R（试图释放不是调用者拥有的互斥对象）。因此，如果在释放互斥对象之前，拥有互斥对象的线程终止运行（使用 E x i t T h r e a d、Te r m i n a t e T h r e a d、 E x i t P r o c e s s或Te r m i n a t e P r o c e s s函数），那么互斥对象和正在等待互斥对象的其他线程将会发生什么情况呢？答案是，系统将把该互斥对象视为已经被放弃——拥有互斥对象的线程决不会释放它，因为该线程已经终止运行。由于系统保持对所有互斥对象和线程内核对象的跟踪，因此它能准确的知道互斥对象何时被放弃。当一个互斥对象被放弃时，系统将自动把互斥对象的 I D复置为0，并将它的递归计数器复置为 0。然后，系统要查看目前是否有任何线程正在等待该互斥对象。如果有，系统将“公平地”选定一个等待线程，将 I D设置为选定的线程的 I D，并将递归计数器设置为 1，同时，选定的线程变为可调度线程。 

## 互斥对象与关键代码段的比较 

就等待线程的调度而言，互斥对象与关键代码段之间有着相同的特性。但是它们在其他属性方面却各不相同。 

![互斥量与关键代码段](image\互斥量与关键代码段比较.png)

## 线程同步对象速查表 

各种内核对象与线程同步之间的相互关系。 

![各种内核对象同步关系1.png](image/各种内核对象同步关系1.png)

![各种内核对象同步关系2.png](image/各种内核对象同步关系2.png)

