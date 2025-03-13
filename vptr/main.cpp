﻿/*
Copyright (c) 2025 better-qi-niu
pointer is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details.
*/

#include <iostream>

using std::cout;
using std::endl;

//! @brief 用于测试虚函数表指针的类。包含三个虚函数和两个数据成员。
class Father {
public:
  virtual void func1() {
    cout << "Father::func1" << endl;
  }
  virtual void func2() {
    cout << "Father::func2" << endl;
  }
  virtual void func3() {
    cout << "Father::func3" << endl;
  }
  void func4() {
    cout << "非虚函数：Father::func4" << endl;
  }
public:
  int x = 200;
  int y = 300;
  static int z;
};
int Father::z = 0;// 初始化静态成员。

//! @brief 虚函数（virtual function）指针。
typedef void(*vfptr_t)(void);
//! @brief 虚函数表（virtual function table）指针。
//! 虚函数表的每个元素是一个虚函数指针。
typedef vfptr_t* vtptr_t;

int main(void) {
  Father father;
  cout << "sizeof(father)==" << sizeof(father) << endl;

  cout << "对象地址：" << &father << endl;
  void* objAddr = &father;               //提取father的地址。
  vtptr_t* vtptrAddr = (vtptr_t*)objAddr;//将father的地址强制类型转换为vtptr_t*类型。

  {// 测试虚函数表指针是否正确。
    vtptr_t vtptr = *vtptrAddr;            //获取虚函数表的地址。

    cout << "调用第1个虚函数：";
    vfptr_t vfunc1 = *vtptr;
    vfunc1();

    cout << "调用第2个虚函数：";
    vfptr_t vfunc2 = *(vtptr + 1);
    vfunc2();

    cout << "调用第3个虚函数：";
    vfptr_t vfunc3 = *(vtptr + 2);
    vfunc3();
  }

  {// 测试虚函数表后的数据成员。
    using std::hex;
    using std::dec;

    cout << "第1个数据成员的地址：" << endl;
    cout << &father.x << endl;
    // 测试x是否在虚函数表之后。
    // 获取 father.x 的地址（vtptrAddr + 1 代表跳过 vtptr ）。
    int* xAddr = (int*)(vtptrAddr + 1);
    cout << hex << xAddr << endl;
    cout << "第1个数据成员的值：" << endl;
    cout << dec << father.x << endl;
    cout << *xAddr << endl;

    cout << "第2个数据成员的地址：" << endl;
    cout << &father.y << endl;
    // 测试y是否在x之后。
    // 获取 father.y 的地址（xAddr + 1 代表跳过 father.x ）。
    int* yAddr = xAddr + 1;
    cout << hex << yAddr << endl;
    cout << "第2个数据成员的值：" << endl;
    cout << dec << father.y << endl;
    cout << *yAddr << endl;
  }

  return 0;
}
