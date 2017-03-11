#pragma once

#include <def.h>

NL_NAMESTART

class Memory
{
private:
    SIZE  iObject;
    INDEX   iMemory;
    void*   pMemory;
public:

    Memory(SIZE _object, INDEX _number);
    Memory(const void* _data, SIZE _object, INDEX _number);
    Memory(const Memory& copy);

    static void* memCpy(void* dest, const void* src, INDEX len);
    void Copy(const void* _from, INDEX _number);
    void Copy(const Memory& _memory);
    void* Push(const void* _data, INDEX _index);
    void Pull(void* _override, INDEX _index);
    void Zero(void* _where, INDEX _size);
    void Zero(void* _where);
    void Zero(SIZE _size);
    void Zero();
    void Free();

    void Cut(INDEX _newsize);

    void* Read(const void* _where, INDEX _size);
    void* Read(const void* _where);
    void* Read(INDEX _index, INDEX _size);
    void* Read(INDEX _index);

    void Write(void* _where, const void* _data, INDEX _size);
    void Write(void* _where, const void* _data);
    void Write(const void* _data, INDEX _index, INDEX _size);
    void Write(const void* _data, INDEX _index);

    void Reallocate(INDEX _number, bool _override=false);
    void Reallocate(SIZE _object, INDEX _number, bool _override=false);

    void* operator[](INDEX _index);

    bool operator==(const Memory& compare);
    bool operator!=(const Memory& compare);


    INDEX getSize() const;
    SIZE getType() const;
    void* getPointer() const;
};


NL_NAMECLOSE
