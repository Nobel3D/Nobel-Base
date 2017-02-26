#pragma once

#include <def.h>
#include "Array.h"

NL_NAMESTART

    template <class type>
	class Node
	{
    private:
        type tData;
        Node* pNext = nullptr;
    public:

        Node(type _item, Node* _next);
        ~Node();

        type& getData();
		Node* getNext() const;
        void setData(const type& _data);
        void setNext(const Node* _next);

        Node* Clear();

	};

    template <class type>
    Node<type>::Node(type _item, Node* _next)
    {
        tData = _item;
        pNext = _next;
    }

    template <class type>
    Node<type>::~Node()
    {
    }

    template <class type>
    type& Node<type>::getData()
    {
        return tData;
    }

    template <class type>
    Node<type>* Node<type>::getNext() const
    {
        return pNext;
    }

    template <class type>
    void Node<type>::setData(const type& _data)
    {
        tData = _data;
    }

    template <class type>
    void Node<type>::setNext(const Node* _next)
    {
        pNext = _next;
    }

    template <class type>
    Node<type>* Node<type>::Clear()
    {
        Node* tmp = pNext;
        pNext = nullptr;
        this->~Node();
        return tmp;
    }


    template <class type>
    class List
    {
    private:
        Node<type>* pHead = nullptr;
        INDEX iNode = 0;
    public:

        List(){}

        void addItem(const type& _add);

        Node<type>* findByIndex(INDEX index);
        Node<type>* findByObject(const type& obj);
        void deleteItem(INDEX index);

        void Clear();

        Array<type>* toArray();

        type& operator[](INDEX index);

        INDEX getLength() const;
    };

    template <class type>
    void List<type>::addItem(const type& _add)
    {
        pHead = new Node<type>(_add, pHead);
        iNode++;
    }

    template <class type>
    Node<type>* List<type>::findByIndex(INDEX index)
    {
        if ( index > iNode )
            return nullptr;

        Node<type>* temp = pHead;
        int i = 0;
        while( index != i++ )
            temp = temp->getNext();

        return temp;
    }

    template <class type>
    Node<type>* List<type>::findByObject(const type& obj)
    {
        Node<type>* temp = pHead;
        while( obj != temp->getData() )
        {
            if( temp->getNext() == nullptr )
                return nullptr;
            temp = temp->getNext();
        }
        return temp;
    }

    template <class type>
    void List<type>::deleteItem(INDEX index)
    {
        if ( index > iNode )
            return;

        Node<type>* prev = pHead;
        Node<type>* next = nullptr;

        int i = 0;
        while( index - 1 != i++ )
            prev = prev->getNext();

        next = prev->getNext()->Clear();
        if( next != nullptr )
            prev->setNext(next);
    }

    template <class type>
    void List<type>::Clear()
    {
        Node<type>* tmp = pHead;

        for( int i = 0; i < iNode; i++ )
            tmp = tmp->Clear();
    }

    template <class type>
    Array<type>* List<type>::toArray()
    {
        if( iNode < 1 )
            return nullptr;
        Array<type>* output = new Array<type>(iNode);
        Node<type>* tmp = pHead;

        for ( int i = 0; i < iNode; i++)
        {
            (*output)[i] = tmp->getData();
            tmp = tmp->getNext();
        }

        return output;
    }

    template <class type>
    type& List<type>::operator[](INDEX index)
    {
        ASSERT ( index <= iNode )

        return findByIndex(index)->getData();
    }

    template <class type>
    INDEX List<type>::getLength() const { return iNode; }

NL_NAMECLOSE
