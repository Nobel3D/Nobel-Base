#include "List.h"

NL_NAMESTART

INDEX Node::list_iStack = 1024;
Memory* Node::list_mManager;

    Node::Node(const void* _item, llint _size, Node* _next)
    {
        list_lData = list_mManager->Push(_item, _size);
        list_iSize = _size;
		list_lNext = _next;
    }
    void* Node::getData(llint& _lenght)
    {
        _lenght = list_iSize;
        return list_mManager->Read(list_lData, list_iSize);
    }

    Node* Node::getNext() const
    {
        return list_lNext;
    }

    void Node::setData(const void* _data)
    {
        list_mManager->Write(list_lData, _data, list_iSize);
    }

    void Node::Clear()
    {
        list_mManager->Zero(list_lData,list_iSize);
    }

    void Node::Init(int _stackSize)
    {
        ASSERT(_stackSize > 0);
        list_iStack = _stackSize;
        list_mManager = new Memory(1,list_iStack);
    }

    Memory* Node::getMemory()
    {
        return list_mManager;
    }

    ListManager::ListManager(int _stackSize)
    {
        Node::Init(_stackSize);
    }

    void ListManager::addItem(const void* _item, llint _size)
    {
        Node* tmp = new Node(_item, _size, list_lHead);
        list_lHead = tmp;
        list_iTot++;
    }

    void ListManager::addItem(const Memory& _memory)
    {
        Node* tmp = new Node(_memory.getPointer(), _memory.getSize(), list_lHead);
        list_lHead = tmp;
        list_iTot++;
    }

    void ListManager::editItem(INDEX _index, const void* _data)
    {
        findByIndex(_index)->setData(_data);
    }

    Node* ListManager::findByIndex(INDEX needle) const
    {
        ASSERT (needle <= list_iTot);

        Node* temp = list_lHead;
        for (int i = list_iTot - 1; i != needle; i--)
            temp = temp->getNext();
        return temp;
    }

    Memory* ListManager::toStack() const
    {
        return Node::getMemory();
    }

    void ListManager::Cut()
    {
        Node::getMemory()->Cut(list_iTot);
    }

    void ListManager::Clear()
    {
        for (int i=0; i < list_iTot; i++)
            findByIndex(i)->Clear();
    }

    void ListManager::deleteItem(INDEX needle)
    {
        findByIndex(needle)->Clear();
    }

    INDEX ListManager::getLength() const { return list_iTot; }

NL_NAMECLOSE
