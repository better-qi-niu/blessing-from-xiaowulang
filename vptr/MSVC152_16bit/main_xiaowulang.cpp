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

//! @brief ���ڲ����麯����ָ����ࡣ���������麯�����������ݳ�Ա��
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
    cout << "non-virtual function: Father::func4" << endl;
  }
public:
  int x;
  int y;
  static int z;
};
int Father::z = 0;// ��ʼ����̬��Ա��

//! @brief �麯����virtual function��ָ�롣
typedef void(*vfptr_t)(void);
//! @brief �麯����virtual function table��ָ�롣
//! �麯�����ÿ��Ԫ����һ���麯��ָ�롣
typedef vfptr_t* vtptr_t;

int main(void) {
  Father father;
  cout << "sizeof(father) = " << sizeof(father) << endl;

  cout << "Object addr:" << &father << endl;
  void* objAddr = &father;               //��ȡfather�ĵ�ַ��
  vtptr_t* vtptrAddr = (vtptr_t*)objAddr;//��father�ĵ�ַǿ������ת��Ϊvtptr_t*���͡�

  {// �����麯����ָ���Ƿ���ȷ��
    vtptr_t vtptr = *vtptrAddr;            //��ȡ�麯����ĵ�ַ��

    cout << "Call func1: ";
    vfptr_t vfunc1 = *vtptr;
    vfunc1();

    cout << "Call func2: ";
    vfptr_t vfunc2 = *(vtptr + 1);
    vfunc2();

    cout << "Call func3: ";
    vfptr_t vfunc3 = *(vtptr + 2);
    vfunc3();
  }

  {// �����麯���������ݳ�Ա��
    cout << "Addr of father.x: " << endl;
    cout << &father.x << endl;
    // ����x�Ƿ����麯����֮��
    // ��ȡ father.x �ĵ�ַ��vtptrAddr + 1 �������� vtptr ����
    int* xAddr = (int*)(vtptrAddr + 1);
    cout << hex << xAddr << endl;
    cout << "father.x = " << endl;
    cout << dec << father.x << endl;
    cout << *xAddr << endl;

    cout << "Addr of father.y: " << endl;
    cout << &father.y << endl;
    // ����y�Ƿ���x֮��
    // ��ȡ father.y �ĵ�ַ��xAddr + 1 �������� father.x ����
    int* yAddr = xAddr + 1;
    cout << hex << yAddr << endl;
    cout << "father.y = " << endl;
    cout << dec << father.y << endl;
    cout << *yAddr << endl;
  }

  return 0;
}
