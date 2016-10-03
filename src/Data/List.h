#pragma once
#include "Array.h"

namespace NobelLib
{
	template<typename Type>
	struct Node {
		Type* list_lData;
		bool list_bStart = false;
		int list_iIndex;
		Node* list_lNext;
		Node* nodeClear()
		{
		    delete[] list_lData;
		    list_bStart = false;
		    list_iIndex = 0;
		    return list_lNext;
		}
	};
	template<typename Type>
	class List
	{
	private:
		Node<Type>* list_lHead;
		static int list_iTot;
	public:
		List()
		{
			list_lHead = nullptr;
			list_iTot = 0;
		}

		List(const Type& ptrType)
		{
			addItem(ptrType);
		}

		void addItem(const Type& ptrType)
		{
			Node<Type>* n = new Node<Type>();
			n->list_lData = new Type(ptrType);
			n->list_lNext = list_lHead;
			n->list_iIndex = list_iTot++;
			n->list_bStart = true;
			list_lHead = n;
		}

        Type& findByObject(const Type& object) const
		{
			Node<Type>* temp = list_lHead;
			while (*temp->list_lData != object)
            {
				temp = temp->list_lNext;
            }
			return *temp->list_lData;
		}
		Node<Type>* findByIndex(int needle) const
		{
			if (needle >= list_iTot)
				return nullptr;
			Node<Type>* temp = list_lHead;
			while (temp->list_iIndex != needle && temp->list_bStart)
				temp = temp->list_lNext;
			return temp;
		}

		Array<Type>* toArray() const
		{
			Array<Type>* output = new Array<Type>(this->getLength());

			for (int i = 0; i < output->getSize(); i++)
			{
				(*output)[i] = *this->findByIndex(i)->list_lData;
			}
			return output;
		}

		void Clear()
		{
			for (int i=0; i < getLength(); i++)
				findByIndex(i)->nodeClear();
		}

		void deleteItem(const Type& Compare)
		{
			Node<Type>* temp = list_lHead;
			while (temp->list_lNext->list_lData != Compare)
            {
                if(temp->list_lNext == NULL)
                    return; //TODO MANAGE EXCEPTION!!!
				temp = temp->list_lNext;
            }
			temp->list_lNext->list_lData.~Type();
			temp->list_lNext->list_bStart = false;
			int lastIndex = temp->list_lNext->list_iIndex;
			temp->list_lNext = temp->list_lNext->list_lNext;
			list_iTot--;
			for (lastIndex; lastIndex < list_iTot; lastIndex++)
			{
				temp = list_lHead;
				temp->list_iIndex = lastIndex;
			}

		}
		Type& operator[] (int Index)
		{
		    Node<Type>* temp = findByIndex(Index);
			return *temp->list_lData; //TODO MANAGE EXCEPTION!!!!
		}

		int getLength() const { return list_iTot; }

	};
	template<typename Type>
	int List<Type>::list_iTot;
}
