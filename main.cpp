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
  printf("Test push back");
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
  printf("Memory usage");
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
  printf("Capacity after inserting two elements: %u\n", v2.capacity());
  v2.push_back(f);
  printf("Memory used after inserting another element (forcing reallocation): %u bytes\n", v2.memorySize());
  printf("Capacity after having inserted three elements: %u\n", v2.capacity());
}

elm::vector<Foo> s;
void shit() {
  Foo f(2, 2, 5);
  s.push_back(f);
}

int main() {
  //test_reserve();
  //test_memoryUsage();
  //test_push_back();
  //test_pop_back();
  shit();
  s[0].printValues();

  return 0;
}
