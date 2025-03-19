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

#include <iostream.h>

class Father {
public:
  Father() :x(200), y(300) {}

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
    cout << "���麯����Father::func4" << endl;
  }
public:
  int x;
  int y;
  static int z;
};

int Father::z = 0;

typedef void(*func_t)(void);

int main(void) {
  Father father;
  cout << "sizeof(father)==" << sizeof(father) << endl;

  cout << "�����ַ��" << (long*)&father << endl;
  long* vptr = (long*)*(long*)(&father);

  cout << "���õ�1���麯����";
  ((func_t) * (vptr + 0))();

  cout << "���õ�2���麯����";
  ((func_t) * (vptr + 1))();

  cout << "���õ�3���麯����";
  ((func_t) * (vptr + 2))();

  cout << "��1�����ݳ�Ա�ĵ�ַ��" << endl;
  cout << &father.x << endl;
  cout << hex << (long)&father + 8 << endl;
  cout << "��1�����ݳ�Ա��ֵ��" << endl;
  cout << dec << father.x << endl;
  cout << *(int*)((long)&father + 8) << endl;

  cout << "��2�����ݳ�Ա�ĵ�ַ��" << endl;
  cout << &father.y << endl;
  cout << hex << (long)&father + 12 << endl;
  cout << "��2�����ݳ�Ա��ֵ��" << endl;
  cout << dec << father.y << endl;
  cout << *(int*)((long)&father + 12) << endl;

  return 0;
}
