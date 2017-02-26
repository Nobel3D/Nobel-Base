#pragma once

#include <def.h>

NL_NAMESTART

	template <class type>
	class Array
	{
    private:
        type* pMemory = nullptr;
        INDEX iIndex = 0;
	public:
        Array(INDEX index);
        Array(const Array<type> &copy);
		Array(const type* copy, INDEX size);
		~Array();

		void Clear();

        void Expand(INDEX size);

		type& operator[] (INDEX index);
        Array<type>& operator= (const Array<type> &o);

		bool Exist() const;
        INDEX getLength() const;

	};

template <class type>
Array<type>::Array(INDEX index)
{
    ASSERT(index > 0)
    pMemory = new type[index];
    iIndex = index;
}

template <class type>
Array<type>::Array(const Array<type> &copy)
{
    pMemory = new type[copy.iIndex];
    iIndex = copy.iIndex;
}

template <class type>
Array<type>::Array(const type* copy, INDEX index)
{
    ASSERT(index > 0)
    pMemory = new type[index];
    for( int i = 0; i < index; i++ )
        if( &copy[i] != nullptr )
            pMemory[i] = copy[i];
    iIndex = index;
}
template <class type>
Array<type>::~Array()
{
    delete[] pMemory;
}

template <class type>
void Array<type>::Expand(INDEX index)
{
    if( index <= iIndex )
        return;

    type* pNew = new type[index];

    for ( int i = 0; i < iIndex; i++)
        pNew[i] = pMemory[i];

    delete[] pMemory;

    pMemory = pNew;
    iIndex = index;
}

template <class type>
void Array<type>::Clear()
{
    delete[] pMemory;

    pMemory = nullptr;
    iIndex = 0;
}

template <class type>
type& Array<type>::operator[] (INDEX index)
{
    ASSERT( index >= 0 && index < iIndex )
    return pMemory[index];
}
template <class type>
Array<type>& Array<type>::operator= (const Array<type> &o)
{
    if(pMemory != nullptr)
        delete[] pMemory;

    pMemory = new type[o.iIndex];
    for (int i = 0; i < o.iIndex; i++)
        pMemory[i] = o.pMemory[i];

    iIndex = o.iIndex;

    return *this;
}
template <class type>
bool Array<type>::Exist() const { return pMemory != nullptr; }
template <class type>
INDEX Array<type>::getLength() const { return iIndex; }

NL_NAMECLOSE
