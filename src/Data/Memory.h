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
    void* Push();
    void* Push(const void* _data, llint _size);
    void Pull(void* _override, llint _size);
    void Zero(void* _where, llint _size);
    void Zero(llint _size);
    void Zero();
    void Free();

    void Cut(llint _newsize);

    void* Read(const void* _where, llint _size);
    void Write(void* _where, const void* _data, llint _size);

    void Reallocate(INDEX _number, bool _override=false);
    void Reallocate(size_t _object, INDEX _number, bool _override=false);

    void operator<<(const void* _data);
    void operator>>(void* _override);

    llint getSize() const;
    size_t getType() const;
    void* getPointer() const;
    static llint getUsed();
};


NL_NAMECLOSE
