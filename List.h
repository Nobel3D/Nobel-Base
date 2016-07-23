#pragma once
#include "Array.h"

namespace NobelLib
{
	template<typename Type>
	struct Node {
		Type list_lData;
		int list_iIndex;
		Node* list_lNext;
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

		void addItem(Type& ptrType)
		{
			Node<Type>* n = new Node<Type>();
			n->list_lData = ptrType;
			n->list_lNext = list_lHead;
			n->list_iIndex = list_iTot++;
			list_lHead = n;
		}

		Node<Type>* findByObject(const Type& Object) const
		{
			Node<Type>* temp = list_lHead;
			while (temp->list_lData != Object)
				temp = temp->list_lNext;
			return temp;
		}
		Node<Type>* findByIndex(int needle) const
		{
			if (needle >= list_iTot)
				return nullptr;
			Node<Type>* temp = list_lHead;
			while (temp->list_iIndex != needle && temp->list_lNext != nullptr)
				temp = temp->list_lNext;
			return temp;
		}

		Array<Type> toArray() const
		{
			Array<Type> output(this->getLength());

			for (int i = 0; i < output.Size(); i++)
			{
				output[i] = this->findByIndex(i)->list_lData;
			}
			return output;
		}

		List<Type> Clear()
		{
			int i = 0;
			for (i; i < getLength(); i++)
			{
				findByIndex(i)->list_lData.~Type();
				findByIndex(i)->list_iIndex = 0;
				findByIndex(i)->list_lNext = nullptr;
			}
			return *this;
		}

		void deleteItem(const Type& Compare)
		{
			Node<Type>* temp = list_lHead;
			while (temp->list_lNext->list_lData != Compare)
				temp = temp->list_lNext;
			temp->list_lNext->list_lData.~Type();
			int lastIndex = temp->list_lNext->list_iIndex;
			temp->list_lNext = temp->list_lNext->list_lNext;
			list_iTot--;
			for (lastIndex; lastIndex < list_iTot; lastIndex++)
			{
				temp = list_lHead;
				temp->list_iIndex = lastIndex;
			}

		}

		Type* operator[] (int Index)
		{
			return &findByIndex(Index)->list_lData;
		}

		int getLength() const { return list_iTot; }

	};
	template<typename Type>
	int List<Type>::list_iTot;
}
