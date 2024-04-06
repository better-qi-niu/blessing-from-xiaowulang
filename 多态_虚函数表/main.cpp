﻿#include <iostream>

using namespace std;

class Father {
public:
  virtual void func1() { cout << "Father::func1" << endl; }
  virtual void func2() { cout << "Father::func2" << endl; }
  virtual void func3() { cout << "Father::func3" << endl; }
  void func4() { cout << "非虚函数：Father::func4" << endl; }
public:
  int x = 200;
  int y = 300;
  static int z;
};

int Father::z = 0;

typedef void(*func_t)(void);
typedef func_t* vptr_t;

int main(void) {
  Father father;
  cout << "sizeof(father)==" << sizeof(father) << endl;

  cout << "对象地址：" << &father << endl;
  vptr_t vptr = *(vptr_t*)&father;//提取father的地址，由于father第一个成员类型是vptr_t，所以father的地址可以当作虚函数表的地址，所以强制类型转换为(vptr_t*)。

  cout << "调用第1个虚函数：";
  (*(vptr + 0))();

  cout << "调用第2个虚函数：";
  (*(vptr + 1))();

  cout << "调用第3个虚函数：";
  (*(vptr + 2))();

  cout << "第1个数据成员的地址：" << endl;
  cout << &father.x << endl;
  void* firstMemberAddr = (vptr_t*)&father + 1;//vptr_t*类型+1，代表跳过一个vptr_t类型的成员。
  cout << std::hex << firstMemberAddr << endl;
  cout << "第1个数据成员的值：" << endl;
  cout << std::dec << father.x << endl;
  cout << *(int*)firstMemberAddr << endl;

  cout << "第2个数据成员的地址：" << endl;
  cout << &father.y << endl;
  void* secondMemberAddr = (int*)firstMemberAddr + 1;//int*类型+1，代表跳过一个int类型的成员。
  cout << std::hex << secondMemberAddr << endl;
  cout << "第2个数据成员的值：" << endl;
  cout << std::dec << father.y << endl;
  cout << *(int*)secondMemberAddr << endl;

  return 0;
}
