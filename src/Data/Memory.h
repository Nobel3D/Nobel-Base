#pragma once

#include <def.h>

NL_NAMESTART

class Memory
{
private:
    static  llint usedMemory;
    size_t  iObject;
    llint   iMemory;
    INDEX   iPushed;
    INDEX   iPulled;
    void*   pMemory;
public:

    Memory(size_t _object, INDEX _number);
    Memory(void* _data, INDEX _number);
    Memory(const Memory& copy);

    void Copy(const void* _from, INDEX _number);
    void Copy(const Memory& _memory);
    void Push();
    void Push(const void* _data, llint _size);
    void Pull(void* _override, llint _size);
    void Zero(INDEX _number);
    void Zero();
    void Free();

    void Reallocate(INDEX _number, bool _override=false);
    void Reallocate(size_t _object, INDEX _number, bool _override=false);

    void operator<<(const void* _data);
    void operator>>(void* _override);

    llint getSize() const;
    void* getPointer() const;
    static llint getUsed();
};


NL_NAMECLOSE
