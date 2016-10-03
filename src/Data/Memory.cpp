#include <stdlib.h>
#include <string.h>

#include "Memory.h"

NL_NAMEUSING

Memory::Memory(size_t _object, INDEX _number)
{
    iPushed = 0;
    iPulled = 0;
    iObject = _object;
    iMemory = iObject * _number;
    pMemory = malloc(iMemory);
    usedMemory += iMemory;
}
Memory::Memory(void* _data, INDEX _number)
{
    iPushed = 0;
    iPulled = 0;
    iObject = sizeof(_data);
    iMemory = iObject * _number;
    pMemory = memcpy(malloc(iMemory), _data, _number);
    usedMemory += iMemory;
}

Memory::Memory(const Memory& copy)
{
    iPushed = copy.iPushed;
    iPulled = copy.iPulled;
    iObject = copy.iObject;
    iMemory = copy.iMemory;
    pMemory = memcpy(malloc(iMemory), copy.pMemory, iMemory);
    usedMemory += iMemory;
}


void Memory::Push()
{
    memset(pMemory + iPushed, 0, iObject);
    iPushed += iObject;
}

void Memory::Push(const void* _data, llint _size)
{
    ASSERT(_data != nullptr && iMemory > _size);
    memcpy(pMemory + iPushed,_data, _size);
    iPushed += _size;
}

void Memory::Pull(void* _override, llint _size)
{
    ASSERT(_override != nullptr && iMemory > _size);
    memcpy(_override, pMemory + iPulled, _size);
    iPulled += _size;
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

void Memory::Zero(INDEX _number)
{
    ASSERT(pMemory != nullptr && iMemory > 0);
    memset(pMemory, 0, iObject * _number);
}
void Memory::Zero()
{
    ASSERT(pMemory != nullptr && iMemory > 0);
    memset(pMemory, 0, iMemory);
}
void Memory::Free()
{
    free(pMemory);
    usedMemory -= iMemory;
    iMemory = 0;
}

void Memory::Reallocate(INDEX _number,bool _override)
{
    if(_override)
    {
        Free();
        iMemory = iObject * _number;
        pMemory = malloc(iMemory);
        usedMemory += iMemory;
    }
    else
    {
        llint iNew = iObject * _number;
        void* pNew = memcpy(malloc(iNew), pMemory, iNew);
        usedMemory += iNew;
        Free();
        pMemory = pNew;
        iMemory = iNew;
    }
}

void Memory::Reallocate(size_t _object, INDEX _number, bool _override)
{
    if(_override)
    {
        Free();
        iMemory = _object * _number;
        pMemory = malloc(iMemory);
        usedMemory += iMemory;
    }
    else
    {
        llint iNew = _object * _number;
        void* pNew = memcpy(malloc(iNew), pMemory, iNew);
        usedMemory += iNew;
        Free();
        pMemory = pNew;
        iMemory = iNew;
    }
}

void Memory::operator<<(const void* _data)
{
    Push(_data,iObject);
}
void Memory::operator>>(void* _override)
{
    Pull(_override,iObject);
}

llint Memory::getSize() const { return iMemory; }
void* Memory::getPointer() const { return pMemory; }
llint Memory::getUsed() { return usedMemory; }
llint Memory::usedMemory = 0;
