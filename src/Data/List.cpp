#include "List.h"

NL_NAMESTART

INDEX Node::list_iStack = 1024;
INDEX Node::list_iSlot = 0;
Memory** Node::list_mManager;

    Node::Node(const void* _item, INDEX _index, Node* _next)
    {
        if(_index >= list_iStack * (list_iSlot + 1))
            Init(list_mManager[list_iSlot++]->getType(), list_iStack);
        list_lData = list_mManager[list_iSlot]->Push(_item, _index - list_iStack * list_iSlot);
        list_lNext = _next;
    }
    void* Node::getData()
    {
        return list_mManager[list_iSlot]->Read(list_lData);
    }

    Node* Node::getNext() const
    {
        return list_lNext;
    }

    void Node::setData(const void* _data)
    {
        list_mManager[list_iSlot]->Write(list_lData, _data);
    }

    void Node::Clear()
    {
        list_mManager[list_iSlot]->Zero(list_lData);
    }

    void Node::Init(SIZE _object, INDEX _stackSize)
    {
        ASSERT(_stackSize > 0);
        if(list_mManager == nullptr)
            list_mManager = new Memory*;
        list_iStack = _stackSize;
        list_mManager[list_iSlot] = new Memory(_object,list_iStack);
    }

    Memory* Node::getMemory()
    {
        return list_mManager[list_iSlot];
    }

NL_NAMECLOSE
