#include <stdlib.h>
#include <string.h>

#include "Memory.h"

NL_NAMEUSING

Memory::Memory(SIZE _object, INDEX _number)
{
    iObject = _object;
    iMemory = iObject * _number;
    pMemory = malloc(iMemory);
}
Memory::Memory(const void* _data, SIZE _object, INDEX _number)
{
    iObject = _object;
    iMemory = iObject * _number;
    pMemory = memcpy(malloc(iMemory), _data, iMemory);
}

Memory::Memory(const Memory& copy)
{
    iObject = copy.iObject;
    iMemory = copy.iMemory;
    pMemory = memcpy(malloc(iMemory), copy.pMemory, iMemory);
}



void* Memory::Push(const void* _data, INDEX _index)
{
    ASSERT(_data != nullptr && iMemory > iObject * _index);
    void* pData = pMemory + iObject * _index;
    memcpy(pData,_data, iObject);
    return pData;
}

void Memory::Pull(void* _override, INDEX _index)
{
    ASSERT(_override != nullptr && iMemory > iObject * _index);
    memcpy(_override, pMemory + iObject * _index , iObject);
}


void Memory::Copy(const void* _from, INDEX _number)
{
    ASSERT(_from != nullptr);
    if(_number * iObject <= iMemory)
        memcpy(pMemory,_from, iObject * _number);
    else
    {
        Reallocate(iObject,_number, true);
        memcpy(pMemory,_from, iMemory);
    }
}

void Memory::Copy(const Memory& _memory)
{
    if(_memory.iMemory <= iMemory)
        memcpy(pMemory,_memory.pMemory, _memory.iMemory);
    else
    {
        Reallocate(_memory.iObject, _memory.iMemory / _memory.iObject, true);
        memcpy(pMemory,_memory.pMemory, _memory.iMemory);
    }
}

void Memory::Zero(void* _where, INDEX _size)
{
    ASSERT(_where != nullptr);
    memset(_where, 0, _size);
}

void Memory::Zero(void* _where)
{
    ASSERT(_where != nullptr);
    memset(_where, 0, iObject);
}

void Memory::Zero(SIZE _size)
{
    ASSERT(pMemory != nullptr && iMemory > 0);
    memset(pMemory, 0, _size);
}
void Memory::Zero()
{
    ASSERT(pMemory != nullptr && iMemory > 0);
    memset(pMemory, 0, iMemory);
}
void Memory::Free()
{
    free(pMemory);
    iMemory = 0;
}

void Memory::Cut(INDEX _newsize)
{
    Zero(pMemory + _newsize, (iMemory - _newsize ));
    iMemory = _newsize;
}

void Memory::Reallocate(INDEX _number,bool _override)
{
    if(_override)
    {
        Free();
        iMemory = iObject * _number;
        pMemory = malloc(iMemory);
    }
    else
    {
        llint iNew = iObject * _number;
        void* pNew = memcpy(malloc(iNew), pMemory, iNew);
        Free();
        pMemory = pNew;
        iMemory = iNew;
    }
}

void Memory::Reallocate(SIZE _object, INDEX _number, bool _override)
{
    if(_override)
    {
        Free();
        iMemory = _object * _number;
        pMemory = malloc(iMemory);
    }
    else
    {
        llint iNew = _object * _number;
        void* pNew = memcpy(malloc(iNew), pMemory, iNew);
        Free();
        pMemory = pNew;
        iMemory = iNew;
    }
}

void* Memory::Read(const void* _where, INDEX _size)
{
    void* output = malloc(_size);
    memcpy(output, _where, _size);
    return output;
}

void* Memory::Read(const void* _where)
{
    void* output = malloc(iObject);
    memcpy(output, _where, iObject);
    return output;
}

void* Memory::Read(INDEX _index, INDEX _size)
{
    void* output = malloc(_size);
    memcpy(output, pMemory + (_index * iObject), _size);
    return output;
}

void* Memory::Read(INDEX _index)
{
    void* output = malloc(iObject);
    memcpy(output, pMemory + (_index * iObject), iObject);
    return output;
}

void Memory::Write(void* _where, const void* _data, INDEX _size)
{
    ASSERT(_where != nullptr && _data != nullptr)
    memcpy(_where, _data, _size);
}

void Memory::Write(void* _where, const void* _data)
{
    ASSERT(_where != nullptr && _data != nullptr)
    memcpy(_where, _data, iObject);
}

void Memory::Write(const void* _data, INDEX _index, INDEX _size)
{
    ASSERT(_data != nullptr)
    memcpy(pMemory + (_index * iObject), _data, _size);
}

void Memory::Write(const void* _data, INDEX _index)
{
    ASSERT(_data != nullptr)
    memcpy(pMemory + (_index * iObject), _data, iObject);
}

void* Memory::operator[](INDEX _index)
{
    void* output = malloc(iObject);
    memcpy(output, pMemory + (_index * iObject), iObject);
    return output;
}

bool Memory::operator==(const Memory& compare)
{
    if(iMemory == compare.iMemory)
        return memcmp(pMemory, compare.pMemory, iMemory) == 0;
    else
        return false;
}

bool Memory::operator!=(const Memory& compare)
{
    if(iMemory == compare.iMemory)
        return memcmp(pMemory, compare.pMemory, iMemory) != 0;
    else
        return true;
}



INDEX Memory::getSize() const { return iMemory; }
SIZE Memory::getType() const { return iObject; }
void* Memory::getPointer() const { return pMemory; }


void* Memory::memCpy(void *dest, const void *src, INDEX len)
{
    ASSERT(src != nullptr && len > 0);

    if(dest == nullptr)
        return dest = memcpy(malloc(len), src, len);
    else
        return memcpy(dest, src, len);
}
