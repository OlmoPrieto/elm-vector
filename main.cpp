#include <iostream>
#include <vector>

#include "vector.h"

void test_push_back() {
  printf("\n============\n");
  printf("Test push back");
  printf("\n============\n");

  elm::vector<Foo> v;
  Foo f;
  f.a = 1; f.b = 2; f.c = 3;

  printf("Elements before push back: %u\n", v.size());
  v.push_back(f);
  printf("Elements after push back: %u\n", v.size());

  v.push_back(f);
  printf("Pushed back same element again\n");
  printf("Elements after pushing the same element twice: %u\n", v.size());
}

void test_pop_back() {
  printf("\n============\n");
  printf("Test pop back");
  printf("\n============\n");

  elm::vector<Foo> v;
  Foo f;
  f.a = 1; f.b = 2; f.c = 3;

  printf("Element to insert: ");
  f.printValues();

  v.push_back(f);
  printf("Elements before pop back: %u\n", v.size());
  printf("Memory used before pop back: %u bytes\n", v.memorySize());
  Foo f2 = v.pop_back();
  printf("Elements after pop back: %u\n", v.size());
  printf("Memory used after pop back: %u bytes\n", v.memorySize());
  printf("Element retrieved on pop back: ");
  f2.printValues();
}

void test_reserve() {
  printf("\n============\n");
  printf("Test reserve");
  printf("\n============\n");

  elm::vector<Foo> v;

  printf("Initial capacity: %u\n", v.capacity());
  v.reserve(10);
  printf("Capacity after having reserved 10 elements: %u\n", v.capacity());
}

void test_memoryUsage() {
  printf("\n============\n");
  printf("Test memory usage");
  printf("\n============\n");

  elm::vector<Foo> v;
  printf("Memory used on construction: %u bytes\n", v.memorySize());
  v.reserve(10);
  printf("Memory used after reserving 10 elements: %u bytes\n", v.memorySize());

  printf("Creating another vector...\n");
  elm::vector<Foo> v2;
  printf("Capacity: %u\n", v2.capacity());

  Foo f;
  v2.push_back(f);
  v2.push_back(f);
  printf("Memory used after pushing two elements back (same # elements as capacity): %u bytes\n", v2.memorySize());
  printf("Capacity after pushing two elements: %u\n", v2.capacity());
  v2.push_back(f);
  printf("Pushing another element back...\n");
  printf("Memory used after inserting another element (forcing reallocation): %u bytes\n", v2.memorySize());
  printf("Capacity after having inserted three elements: %u\n", v2.capacity());
}

void test_insert() {
  printf("\n============\n");
  printf("Test insert");
  printf("\n============\n");

  elm::vector<Foo> v;
  Foo f;
  f.a=1;f.b=2;f.c=3;f.s="F";

  printf("Pushing two elements back...\n");
  v.push_back(f);
  v.push_back(f);

  printf("Elements:\n");
  v[0].printValues();
  v[1].printValues();

  Foo f2;
  f2.a=10;f2.b=11;f2.c=12;f2.s="F2";

  printf("Inserting an element in position 1...\n");
  v.insert(f2, 1);

  printf("Elements after insert:\n");
  v[0].printValues();
  v[1].printValues();
  v[2].printValues();
}

void test_erase() {
  printf("\n============\n");
  printf("Test erase");
  printf("\n============\n");

  elm::vector<Foo> v;
  Foo f;
  f.a=1;f.b=2;f.c=3;
  Foo f2;
  f2.a=10;f2.b=11;f2.c=12;

  printf("Pushing three elements back...\n");
  v.push_back(f);
  v.push_back(f2);
  v.push_back(f);

  printf("Elements:\n");
  v[0].printValues();
  v[1].printValues();
  v[2].printValues();

  printf("Erasing element at position 1...\n");
  Foo f3 = v.erase(1);

  printf("Elements in vector:\n");
  v[0].printValues();
  v[1].printValues();

  printf("Erased element: ");
  f3.printValues();

  printf("Testing erase without keeping order...\n");
  printf("Creating new vector and pushing three elements back...\n");
  elm::vector<Foo> v2;
  f.a=1;f.b=2;f.c=3;
  f2.a=10;f2.b=11;f2.c=12;

  v2.push_back(f);
  v2.push_back(f2);
  v2.push_back(f);

  printf("Elements:\n");
  v2[0].printValues();
  v2[1].printValues();
  v2[2].printValues();

  printf("Erasing element at position 1...\n");
  f3 = v2.erase(1, false);

  printf("Elements in vector 2:\n");
  v2[0].printValues();
  v2[1].printValues();

  printf("Erased element: ");
  f3.printValues();
}

void test_swap() {
  printf("\n============\n");
  printf("Test swap");
  printf("\n============\n");

  elm::vector<Foo> v;
  Foo f;
  f.a=1;f.b=2;f.c=3;
  Foo f2;
  f2.a=10;f2.b=11;f2.c=12;
  Foo f3;
  f3.a=20;f3.b=31;f3.c=13;

  v.push_back(f);
  v.push_back(f2);
  v.push_back(f3);

  printf("Elements before swapping:\n");
  v[0].printValues();
  v[1].printValues();
  v[2].printValues();

  printf("Swapping values...\n");

  v.swapElements(0, 1);
  printf("Elements after swapping:\n");
  v[0].printValues();
  v[1].printValues();
  v[2].printValues();
}

int main() {
  //test_reserve();
  //test_memoryUsage();
  //test_push_back();
  //test_pop_back();
  //test_insert();
  //test_erase();
  test_swap();
  
  return 0;
}
