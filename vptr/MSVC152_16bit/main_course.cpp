/*
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

using namespace std;

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

int Father::z = 0;

typedef void(*func_t)(void);

int main(void) {
  Father father;
  cout << "sizeof(father)==" << sizeof(father) << endl;

  cout << "对象地址：" << (int*)&father << endl;
  int* vptr = (int*)*(int*)(&father);

  cout << "调用第1个虚函数：";
  ((func_t) * (vptr + 0))();

  cout << "调用第2个虚函数：";
  ((func_t) * (vptr + 1))();

  cout << "调用第3个虚函数：";
  ((func_t) * (vptr + 2))();

  cout << "第1个数据成员的地址：" << endl;
  cout << &father.x << endl;
  cout << std::hex << (int)&father + 4 << endl;
  cout << "第1个数据成员的值：" << endl;
  cout << std::dec << father.x << endl;
  cout << *(int*)((int)&father + 4) << endl;

  cout << "第2个数据成员的地址：" << endl;
  cout << &father.y << endl;
  cout << std::hex << (int)&father + 8 << endl;
  cout << "第2个数据成员的值：" << endl;
  cout << std::dec << father.y << endl;
  cout << *(int*)((int)&father + 8) << endl;

  return 0;
}
