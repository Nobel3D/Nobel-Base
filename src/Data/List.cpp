#include "List.h"

NL_NAMESTART

INDEX Node::list_iStack = 1024;
Memory* Node::list_mManager;

    Node::Node(const void* _item, INDEX _index, Node* _next)
    {
        list_lData = list_mManager->Push(_item, _index);
		list_lNext = _next;
    }
    void* Node::getData()
    {
        return list_mManager->Read(list_lData);
    }

    Node* Node::getNext() const
    {
        return list_lNext;
    }

    void Node::setData(const void* _data)
    {
        list_mManager->Write(list_lData, _data);
    }

    void Node::Clear()
    {
        list_mManager->Zero(list_lData);
    }

    void Node::Init(SIZE _object, INDEX _stackSize)
    {
        ASSERT(_stackSize > 0);
        list_iStack = _stackSize;
        list_mManager = new Memory(_object,list_iStack);
    }

    Memory* Node::getMemory()
    {
        return list_mManager;
    }

NL_NAMECLOSE
