#include <iostream>
#include <vector>

#include "vector.h"

typedef unsigned int uint32;
typedef unsigned char byte;

int main() {

  bool do_log = false;

  uint32 elements = 100;

  vector<Foo> v;
  printf("Class size: %u\n", v.classSize());
  uint32 v_cap = v.capacity();
  uint32 count = 0;
  //v.reserve(10000);

  for (uint32 i = 0; i < elements; i++)
  {
    Foo tmp;
    tmp.a = i;
    tmp.b = i + 1;
    tmp.c = i + 2;

    v.pushBack(tmp);
    if (v_cap != v.capacity())
    {
      count++;
      v_cap = v.capacity();
    }
    //v[i].printValues();
  }

  std::vector<Foo> vv;
  uint32 vv_cap = vv.capacity();
  uint32 count2 = 0;
  //vv.reserve(10000);
  
  for (uint32 i = 0; i < elements; i++)
  {
    Foo tmp;
    tmp.a = i;
    tmp.b = i + 1;
    tmp.c = i + 2;

    vv.push_back(tmp);
    if (vv_cap != vv.capacity())
    {
      count2++;
      vv_cap = vv.capacity();
    }
  }
  
  printf("Cap changes: v -> %u  vv -> %u\n", count, count2);

  printf("Elements inserted: %u\n", elements);

  Foo ff;
  ff.a = 1000;
  ff.b = 1001;
  ff.c = 1002;
  
  v.insert(ff, 50);
  printf("Size elm::vector: %u\n", v.size());
  printf("Element 49: "); v[49].printValues();
  printf("Element 50: "); v[50].printValues();
  printf("Element 51: "); v[51].printValues();

  //printf("Size std::vector: %u\n", vv.size());
  printf("MemorySize elm::vector: %u\n", v.memorySize());
  printf("MemorySize std::vector: %u\n", vv.capacity() * sizeof(Foo));

  getchar();
  return 0;
}