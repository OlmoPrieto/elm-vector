#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iostream>
#include <memory>
#include <cmath>
#include <cstring>
#include <cassert>

typedef unsigned int uint32;

class Foo 
{
public:
  Foo()
  {
    a = b = c = 0;
  }

  Foo(int a, int b, int c) : a(a), b(b), c(c) {}
  
  Foo operator=(const Foo &other)
  {
    Foo f;
    f.a = other.a;
    f.b = other.b;
    f.c = other.c;
    f.s = other.s;
    //printf("operator=\n");
    return f;
  }

  Foo(const Foo &other)
  {
    //printf("copy\n");
    a = other.a;
    b = other.b;
    c = other.c;
    s = other.s;
  }

  ~Foo()
  {
    
  }

  void printValues() const
  {
    printf("%d %d %d\n%s\n", a, b, c, s.c_str());
  }

  int a;
  int b;
  int c;
  std::string s;
};

namespace elm {
template <class T>
class vector
{
public:
  /*
   *  Allocates size for two elements on creation
   *
   *  Maybe not allocating anything before insering
   *  an element could be an option.
  */
  vector()
  {
    m_uClassSize = sizeof(T);
    printf("Class size: %u bytes\n", m_uClassSize);

    m_uCount = 0;
    m_uCapacity = 2;
    m_uRealCapacity = m_uCapacity + 1;

    m_pVectorBegin = (T*)malloc(m_uRealCapacity * m_uClassSize);
    assert(m_pVectorBegin != nullptr && "couldn't allocate memory. vector()");
    m_pIterator = nullptr;
  }
  
  ~vector()
  {
    if (m_uCount > 0)
    {
      T* pPtr = m_pVectorBegin;
      for (unsigned int i = 0; i < m_uCount; i++)
      {
        pPtr->~T();
        //m_uCount = 0;
        pPtr++;
      }
      m_uCount = 0;
    }
    
    if (m_pVectorBegin != nullptr)
    {
      free(m_pVectorBegin);
    }
  }

  T* data() const
  {
    return m_pVectorBegin;
  }

  uint32 classSize() const
  {
    return m_uClassSize;
  }

  uint32 size() const
  {
    return m_uCount;
  }

  uint32 capacity() const
  {
    return m_uCapacity;
  }

  void push_back(const T& element)
  {
    if (m_uCount == m_uCapacity)
    {
      vector::allocate();
    }

    m_pIterator = m_pVectorBegin + m_uCount;
    //memcpy(m_pIterator, &element, m_uClassSize);
    new(m_pIterator)T(element);
    m_pIterator = nullptr;
    
    m_uCount++;
  }

  /*
   *  Quite costly. Reallocation can happen.
   *
   *  TODO: maybe assert if position >= m_uCount?
  */
  void insert(const T& element, uint32 position)
  {
    if (position < m_uCount)
    {
      if (m_uCount == m_uCapacity)
      {
        vector::allocate();
      }

      vector<T> aux;
      aux.reserve(m_uCapacity);
      for (uint32 i = position; i < m_uCount; i++)
      {
        T e = *(m_pVectorBegin + i);
        aux.push_back(e);
      }

      m_pIterator = m_pVectorBegin + position;
      //memcpy(m_pIterator, &element, m_uClassSize);
      new(m_pIterator)T(element);
      m_uCount++;
      m_pIterator = nullptr;

      for (uint32 i = position + 1; i < m_uCount; i++)
      {
        T e = aux[i - position - 1];
        m_pIterator = m_pVectorBegin + i;
        
        m_pIterator->~T();
        new(m_pIterator)T(e);
      }
      m_pIterator = nullptr;
    }
    else
    {
      printf("Index out of range in vector\n");
    }
  }

  /*
   *
  */
  T erase(uint32 uPosition, bool bKeepOrder = true) {
    if (uPosition < m_uCount)
    {
      // COPY the element
      //T e = *(m_pVectorBegin + uPosition);
      T e((*(m_pVectorBegin + uPosition)));

      if (bKeepOrder == true) {

        vector<T> aux;
        aux.reserve(m_uCapacity);
        
        for (uint32 i = uPosition + 1; i < m_uCount; ++i)
        {
          T e = *(m_pVectorBegin + i);
          aux.push_back(e);
        }

        for (uint32 i = uPosition; i < m_uCount; i++)
        {
          T e = aux[i - uPosition];
          m_pIterator = m_pVectorBegin + i;
          
          m_pIterator->~T();
          new(m_pIterator)T(e);
        }
        m_pIterator = nullptr;
      }
      else {
        swapElements(uPosition, m_uCount - 1);
      }

      e.~T();
      --m_uCount;
      return e;
    }
    else
    {
      printf("Index out of range in vector\n");
      return T();
    }
  }

  /*
   *  Returns a copy of the popped element.
  */
  T pop_back()
  {
    if (m_uCount > 0)
    {
      T* e = m_pVectorBegin + (m_uCount - 1);
      e->~T();
      --m_uCount;
      return *e;
    }

    return T();
  }

  /*
   *  If amount is lesser than the actual capacity of the vector,
   *  no reallocation will happen.
  */
  void reserve(uint32 amount)
  {
    if (amount > m_uCapacity)
    {
      vector::allocate(amount);
    } else
    {
      printf("Requested lesser capacity than the current one\n");
      
      // TODO: implement shrink_to_fit()

      // m_uCapacity = amount;
      // m_uRealCapacity = m_uCapacity + 1;
    }
  }

  /*  
   *  Note: Because it returns an object, it has to be destroyed
   *  locally when exiting the function -> CHECK if currently this happens
  */
  T& operator[](uint32 index) const
  {
    return *(m_pVectorBegin + index);
  }

  /*
   *  Should implement exception-throwing system
  */
  T at(uint32 index) const
  {
    if (index < m_uCount)
    {
      return operator[](index);
    } else
    {
      printf("Index out of range in vector\n");
      return T();
    }
  }

  uint32 memorySize()
  {
    return (m_uRealCapacity * m_uClassSize);
  }

  void swapElements(uint32 uFirst, uint32 uSecond)
  {
    new(m_pVectorBegin + m_uRealCapacity - 1)T((*(m_pVectorBegin + uFirst)));
    new(m_pVectorBegin + uFirst)T((*(m_pVectorBegin + uSecond)));
    new(m_pVectorBegin + uSecond)T((*(m_pVectorBegin + m_uRealCapacity - 1)));
  }

private:
  bool allocate(uint32 amount = 0)
  {
    if (amount == 0)
    {
      /* round(cap + log(cap + 1) */
      //double new_cap = (double)m_uCapacity + log(m_uCapacity + 1);
      //uint32 converted_cap = (uint32)round(new_cap) + 1;

      /* cap * 2 */
      //uint32 converted_cap = m_uCapacity * 2;

      /* cap + cap * 2 */
      //uint32 converted_cap = m_uCapacity + m_uCapacity * 2;

      /* round(cap + (cap / 2) + log(cap + 1)) */
      double new_cap = (double)m_uRealCapacity + ((double)m_uRealCapacity / 4.0) + log(m_uRealCapacity + 1);
      uint32 converted_cap = (uint32)round(new_cap);

      amount = converted_cap - 1; // -1 is a hack to avoid an if() below
    }

    m_uRealCapacity = amount + 1;
    m_uCapacity = m_uRealCapacity - 1;

    T* tmp = m_pVectorBegin;
    m_pVectorBegin = nullptr;
    m_pVectorBegin = (T*)malloc(m_uRealCapacity * m_uClassSize);
    if (m_pVectorBegin != nullptr)  // assert(m_pVectorBegin == nullptr && "Failed to allocate new memory");
    {
      memset(m_pVectorBegin, 0, m_uRealCapacity * m_uClassSize);

      memcpy(m_pVectorBegin, tmp, m_uClassSize * m_uCount);
      /*for (uint32 i = 0; i < m_uCount; i++)
      {
        T* e = tmp + i;
        m_pIterator = m_pVectorBegin + i;
        *m_pIterator = *e;
        e->~T();
      }
      m_pIterator = nullptr;*/

      // delete all old copies? Not needed I think.

      free(tmp);
      tmp = nullptr;

      return true;
    } else
    {
      m_pVectorBegin = nullptr;
      m_pIterator = nullptr;
      tmp = nullptr;
      return false;
    }
  }

  T* m_pVectorBegin;
  T* m_pIterator;
  uint32 m_uClassSize;
  uint32 m_uCount;
  uint32 m_uCapacity;
  uint32 m_uRealCapacity;
};
}

#endif // __VECTOR_H__