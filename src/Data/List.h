#pragma once

#include "Array.h"

NL_NAMESTART

	class Node
	{
    private:
		void* list_lData;
		Node* list_lNext;
		static Memory* list_mManager;
		static INDEX list_iStack;
    public:
        Node(const void* _item, INDEX _index, Node* _next);

		void* getData();
		Node* getNext() const;
		void setData(const void* _data);

		void Clear();

		static void Init(SIZE _object, INDEX _stackSize);
		static Memory* getMemory();

	};

    template <class type>
    class List
    {
    private:
        Node* list_lHead= nullptr;
		INDEX list_iTot = 0;
    public:


        List(INDEX _stacksize = 1024);

        void addItem(const type& _add);

        Node* findByIndex(INDEX needle) const;
        void deleteItem(INDEX _index);
        void editItem(const type& _data, INDEX _index);

        void Clear();

        Array<type>* toArray();
        Memory* toStack();

        type& operator[](INDEX _index) const;

        INDEX getLength() const;
    };

    template <class type>
    List<type>::List(INDEX _stacksize)
    {
        Node::Init(sizeof(type), _stacksize);
    }

    template <class type>
    void List<type>::addItem(const type& _add)
    {
        Node* tmp = new Node(&_add, list_iTot, list_lHead);
        list_lHead = tmp;
        list_iTot++;
    }

    template <class type>
    Node* List<type>::findByIndex(INDEX needle) const
    {
        ASSERT (needle <= list_iTot);

        Node* temp = list_lHead;
        for (int i = list_iTot - 1; i != needle; i--)
            temp = temp->getNext();
        return temp;
    }

    template <class type>
    void List<type>::deleteItem(INDEX _index)
    {
        findByIndex(_index)->Clear();
    }

    template <class type>
    void List<type>::editItem(const type& _data, INDEX _index)
    {
        findByIndex(_index)->setData(&_data);
    }

    template <class type>
    void List<type>::Clear()
    {
        for (int i=0; i < list_iTot; i++)
            findByIndex(i)->Clear();
    }

    template <class type>
    Array<type>* List<type>::toArray()
    {
        Array<type>* output = new Array<type>(*Node::getMemory());
        return output;
    }

    template <class type>
    Memory* List<type>::toStack()
    {
        return Node::getMemory();
    }

    template <class type>
    type& List<type>::operator[](INDEX _index) const
    {
        return *(type*)findByIndex(_index)->getData();
    }

    template <class type>
    INDEX List<type>::getLength() const { return list_iTot; }

NL_NAMECLOSE
