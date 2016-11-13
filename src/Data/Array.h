#pragma once

#include "Memory.h"

NL_NAMESTART

	template <class type>
	class Array
	{
    private:
		Memory* array_mStack;
		INDEX array_iCount  = 0;
		INDEX array_iUsed   = 0;
        bool array_bStart   = false;
        static int array_iStack;
	public:
	    Array(){};
		Array(INDEX size);
		Array(Array<type> &copy);
		Array(const Memory& _memory);
		Array(const type* copy, INDEX size);
		~Array();

		void Add();
		void Add(const type& item);
        void Delete();
		void Clear();
		void New(INDEX index, bool force=false);

        void Expand(INDEX size);

		void Copy(const type* copy, INDEX size);
		void Copy(Array<type> &copy);

		type& operator[] (INDEX index);
		Array<type>& operator= (Array<type> &equal);

		bool Exist() const;
		int getSize() const;
		static void setStack(int _stack);
	};

template <class type>
int Array<type>::array_iStack = 16;

template <class type>
Array<type>::Array(INDEX size)
{
    New(size);
}
template <class type>
Array<type>::Array(Array<type> &copy)
{
    if(copy.array_bStart)
    {
        array_mStack = new Memory(copy.array_mStack);
        array_iCount = copy.array_iCount;
        INDEX array_iUsed = copy.array_iUsed;
        bool array_bStart = true;
    }
}

template <class type>
Array<type>::Array(const Memory& _memory)
{
    array_iCount = _memory.getSize() / sizeof(type);
    array_mStack = new Memory(_memory);
    array_bStart = true;
}

template <class type>
Array<type>::Array(const type* copy, INDEX size)
{
    array_iCount = size;
	array_mStack = new Memory((void*)copy, sizeof(type), size);
	array_bStart = true;
}
template <class type>
Array<type>::~Array()
{
	Delete();
}

template <class type>
void Array<type>::New(INDEX size, bool force)
{
    ASSERT(size > 0);

    if(array_bStart)
    {
        if(force)
            Clear();
        else
            return;
    }

    array_mStack = new Memory(sizeof(type),size);

    array_iCount = size;
    array_bStart = true;
}
template <class type>
void Array<type>::Add()
{
    if(array_iCount <= array_iUsed)
        Expand(array_iStack);

    array_mStack->Zero(array_iUsed);
    array_iUsed++;
}

template <class type>
void Array<type>::Add(const type& item)
{
    if(array_iCount <= array_iUsed)
        Expand(array_iStack);

    array_mStack->Push(&item,array_iUsed);
    array_iUsed++;
}

template <class type>
void Array<type>::Copy(Array<type> &copy)
{
    if(!copy.array_bStart)
        return;

    array_mStack->Copy(copy.array_mStack);
    array_iCount = copy.array_iCount;
}
template <class type>
void Array<type>::Copy(const type* copy, INDEX size)
{
    ASSERT(copy != nullptr);

    array_mStack->Copy(copy,size);

    array_iCount = size;
}
template <class type>
void Array<type>::Expand(INDEX size)
{
    if (!array_bStart)
    {
        New(size);
        return;
    }
    ASSERT(size>array_iCount);

    array_mStack->Reallocate(size);

    this->array_iCount = size;
}
template <class type>
void Array<type>::Delete()
{
    if(!array_bStart)
        return;
    array_mStack->Free();
    array_iCount = 0;
    array_bStart = false;
}
template <class type>
void Array<type>::Clear()
{
	if (!array_bStart)
        return;
    array_mStack->Zero();
}
template <class type>
type& Array<type>::operator[] (INDEX index)
{
    ASSERT(index >= 0 && index < array_iCount && array_bStart);
    return ((type*)array_mStack->getPointer())[index];
}
template <class type>
Array<type>& Array<type>::operator= (Array<type>& equal)
{
	Copy(equal);
	return *this;
}
template <class type>
bool Array<type>::Exist() const { return array_bStart; }
template <class type>
int Array<type>::getSize() const { return array_iCount; }
template <class type>
void Array<type>::setStack(int _stack) { array_iStack = _stack; }

NL_NAMECLOSE
