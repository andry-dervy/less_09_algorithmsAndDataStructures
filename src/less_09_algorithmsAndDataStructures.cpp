//============================================================================
// Name        : less_09_algorithmsAndDataStructures.cpp
// Author      : andry antonenko
// IDE         : Eclipse IDE
// Description : lesson 7 of the algorithms and data structures
//============================================================================

#include <iostream>
using namespace std;
//----------------------------------------------------------------------------
#define T int
//----------------------------------------------------------------------------
/*
1. Описать очередь с приоритетным исключением
*/

const int NUMBER_PRIORITY = 5;

enum ePriority
{
  NO_PRIORITY = -1,
  PRIORITY_LEV_1 = 0,
  PRIORITY_LEV_2 = 1,
  PRIORITY_LEV_3 = 2,
  PRIORITY_LEV_4 = 3,
  PRIORITY_LEV_5 = 4,
};

struct TItem
{
  T d;
  ePriority p;
};

struct TQueue
{
  TItem *Q;
  int begin = 0;
  int end = -1;
  int cnt = 0;
  int size = 0;
};

TQueue* getQueue(const int aSize)
{
  TQueue* pQueue = nullptr;
  try{
    pQueue = new TQueue;

    if(pQueue != nullptr)
    {
      pQueue->size = aSize;
      pQueue->Q = new TItem[aSize];
      for(int i = 0; i < aSize; i++)
      {
        pQueue->Q[i].d = 0;
        pQueue->Q[i].p = NO_PRIORITY;
      }
    }
  }
  catch (const std::exception&) {
    cout << "No memory allocated." << endl;
  }
  return pQueue;
}

void freeQueue(TQueue* pQueue)
{
  if(pQueue->Q != nullptr)
    delete pQueue->Q;
  if(pQueue != nullptr)
  {
    delete pQueue;
    pQueue = nullptr;
  }
}

TItem* getMaxPriority(TQueue *q)
{
  int begin = q->begin;
  int end = q->end;
  TItem* pItem = &q->Q[begin];
  int maxPriority = pItem->p;
  while(begin != end)
  {
    if(++begin == q->size) begin = 0;
    if(maxPriority < q->Q[begin].p)
    {
      pItem = &q->Q[begin];
      maxPriority = q->Q[begin].p;
    }
  }
  return pItem;
}

bool enqueue(TQueue *q, TItem item)
{
  if(q->cnt == q->size)
  {
    cout << "TQueue is full" << endl;
    return false;
  }
  if(q->end == q->size - 1)
  {
    q->end = -1;
  }
  q->Q[++q->end] = item;
  q->cnt++;
  return true;
}

TItem dequeue(TQueue *q)
{
  TItem item = {0,NO_PRIORITY};
  if(q->cnt == 0)
  {
    cout << "TQueue is empty" << endl;
    return item;
  }
  else
  {
    TItem *pItem = getMaxPriority(q);
    item = *pItem;

    pItem->d = 0;
    pItem->p = NO_PRIORITY;
    //cout << "{" << item.d << ";" << int(item.p) << "} " << endl;
    while(q->Q[q->begin].p == NO_PRIORITY && q->begin != q->end)
    {
      if(++q->begin == q->size) q->begin = 0;
    }
    q->cnt--;
  }
  return item;
}

//----------------------------------------------------------------------------
/*
2. Реализовать перевод из десятичной в двоичную систему счисления
с использованием стека.

Результатом работы должен стать один файл с кодом на языке С,
содержащий функцию main, а также функции,
необходимые для работы приоритетной очереди и перевода систем счисления
*/

struct TStack
{
  T *S;
  //int begin = 0;
  int top = -1;
  int cnt = 0;
  int size = 0;
};

TStack* getStack(const int aSize)
{
  TStack* pStack = nullptr;
  try{
    pStack = new TStack;

    if(pStack != nullptr)
    {
      pStack->size = aSize;
      pStack->cnt = 0;
      pStack->top = -1;
      pStack->S = new T[aSize];
    }
  }
  catch (const std::exception&) {
    cout << "No memory allocated." << endl;
  }
  return pStack;
}

void freeStack(TStack* pStack)
{
  if(pStack->S != nullptr)
    delete pStack->S;
  if(pStack != nullptr)
  {
    delete pStack;
    pStack = nullptr;
  }
}

bool push(TStack* pStack,T d)
{
  if(pStack->cnt == pStack->size)
  {
    cout << "Stack overflow." << endl;
    return false;
  }
  pStack->S[++pStack->top] = d;
  pStack->cnt++;
  return true;
}

T pop(TStack* pStack)
{
  if(pStack->cnt == 0)
  {
    cout << "Stack empty." << endl;
    return 0;
  }
  int d = pStack->S[pStack->top--];
  pStack->cnt--;
  return d;
}

//----------------------------------------------------------------------------
void task_1(void)
{
  cout << "Task 1\n" << endl;

  const int SIZE_QUEUE = 20;
  const int NUMBER_ITEMS = 10;

  TQueue* pQueue = getQueue(SIZE_QUEUE);
  if(pQueue != nullptr)
  {
    int cycle = 5;
    while(cycle-- != 0)
    {
      cout << "Pushed samples:" << endl;
      int cntSmpls = NUMBER_ITEMS;
      while(cntSmpls-- != 0)
      {
        TItem item;
        item.d = rand()%100;
        item.p = (ePriority)(rand()%5);
        cout << "{" << item.d << ";" << int(item.p) << "} ";
        enqueue(pQueue,item);
      }
      cout << endl;

      cout << "Poped samples:" << endl;
      while(pQueue->cnt != 0)
      {
        TItem item = dequeue(pQueue);
        cout << "{" << item.d << ";" << int(item.p) << "} ";
      }
      cout << endl;
    }

    freeQueue(pQueue);
  }
}
//----------------------------------------------------------------------------
void task_2(void)
{
  cout << "Task 2\n" << endl;

  const int SIZE_STACK = 64;

  TStack* pStack = getStack(SIZE_STACK);
  if(pStack != nullptr)
  {
    cout << "Enter a whole number: ";
    int d;
    cin >> d;

    do {
      push(pStack,d%2);
      d /= 2;
    } while(d != 0);

    cout << "Binary representation: " << endl;
    while(pStack->cnt != 0)
    {
      cout << pop(pStack);
    }
    freeStack(pStack);
  }
}
//----------------------------------------------------------------------------
int main() {
//----------------------------------------------------------------------------
  // Task 1
  //*
  task_1();
  //*/
//----------------------------------------------------------------------------
  // Task 2
  //*
  task_2();
  //*/
//----------------------------------------------------------------------------
	return 0;
}
