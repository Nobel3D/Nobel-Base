#pragma once

#include "Array.h"

NL_NAMESTART

	class Node
	{
    private:
		void* list_lData;
		Node* list_lNext;
		llint list_iSize;
		static Memory* list_mManager;
		static INDEX list_iStack;
    public:
        Node(const void* _item, llint _size, Node* _next);

		void* getData(llint& _lenght);
		Node* getNext() const;
		void setData(const void* _data);

		void Clear();

		static void Init(int _stackSize);
		static Memory* getMemory();

	};

	class ListManager
	{
	private:
		Node* list_lHead= nullptr;
		INDEX list_iTot = 0;
	public:
		ListManager(int _stackSize = 1024);


		void addItem(const void* _item, llint _size);
		void addItem(const Memory& _memory);
		void editItem(INDEX _index, const void* _data);

		Node* findByIndex(INDEX needle) const;

		Memory* toStack() const;

        void Cut();
		void Clear();
		void deleteItem(INDEX needle);

		INDEX getLength() const;

	};



    template <class type>
    class List
    {
    public:

        ListManager list_lManager;

        List();

        void addItem(const type& _add);
        void deleteItem(INDEX _index);
        void editItem(INDEX _index, const type& _data);

        void Clear();

        Array<type>* toArray();

        type& operator[](INDEX _index) const;

        INDEX getLength() const;
    };

    template <class type>
    List<type>::List(){}

    template <class type>
    void List<type>::addItem(const type& _add)
    {
        list_lManager.addItem(&_add, sizeof(_add));
    }

    template <class type>
    void List<type>::deleteItem(INDEX _index)
    {
        list_lManager.deleteItem(_index);
    }

    template <class type>
    void List<type>::editItem(INDEX _index, const type& _data)
    {
        list_lManager.editItem(_index,&_data);
    }

    template <class type>
    void List<type>::Clear()
    {
        list_lManager.Clear();
    }

    template <class type>
    Array<type>* List<type>::toArray()
    {
        Array<type>* output = new Array<type>(*list_lManager.toStack());
        return output;
    }

    template <class type>
    type& List<type>::operator[](INDEX _index) const
    {
        llint typeLength = sizeof(type);
        return *(type*)list_lManager.findByIndex(_index)->getData(typeLength);
    }

    template <class type>
    INDEX List<type>::getLength() const { return list_lManager.getLength(); }

NL_NAMECLOSE
