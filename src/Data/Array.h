#pragma once

#include <def.h>

namespace NobelLib
{
	template < class Type >
	class Array
	{
	private:
		Type* array_cData;
		index array_iCount;
        bool array_bStart = false;

		index arraySize(const Type* array)
        {
            int i = 0;

            while(*array++) i++;

            return i;
        }

		void expArray(index arrayIndex)
		{
			if (arrayIndex<array_iCount)
                return;
			if (!Exist()) {
				this->New(arrayIndex);
				return;
			}

			Type* arrayOffset = new Type[arrayIndex];
            for(int i=0; i < this->array_iCount; i++)
                arrayOffset[i] = array_cData[i];

            this->Clear();
            this->array_cData = arrayOffset;
            this->array_iCount = arrayIndex;
		}
		Type* newArray(index Index)
        {
            Type* arrayOffset = new Type[Index];

            for(int i = 0; i<Index; i++)
                arrayOffset[i] = Type();

            return arrayOffset;
		}

		Type* copyArray(const Type* copyArray, int copyElements)
        {
            Type* arrayOffset = newArray(copyElements);
            while(copyElements--)
                arrayOffset[copyElements] = copyArray[copyElements];

            return arrayOffset;
		}

		void deleteArray()
		{
			if (Exist())
				delete[] array_cData;
            array_cData = NULL;
            array_iCount = 0;
            array_bStart = false;
		}

	public:
		/* Constructor and Destructor*/
		Array()
        {
			array_iCount = NULL;
			array_cData = NULL;
		}

		Array(index index)
		{
			this->New(index);
		}
		Array(const Array<Type> &Other)
		{
			Copy(Other);
		}
		Array(const Type* Other)
		{
			Copy(Other);
		}

		~Array()
		{
		    deleteArray();
        }
        /* Constructor and Destructor*/
        void Delete()
        {
            deleteArray();
        }

		void Clear()
		{
			if (Exist())
				{
				    int index = array_iCount;
				    deleteArray();
				    New(index);
				}
		}

		void New(index Index)
        {
			if (!Exist())
			{
			    array_bStart = true;
			    array_iCount = Index;
                array_cData = new Type[array_iCount];

                for(int i = 0; i<array_iCount; i++)
                    array_cData[i] = Type();
			}
		}

        void Expand(int newIndex)
        {
            expArray(newIndex);
        }

		void Copy(const Type* MyArray)
        {
            if(!MyArray)
                return;
            int arrayLength = arraySize(MyArray);

            if(Exist())
            {
                if(arrayLength > this->array_iCount)
                    return;
                this->Clear();
            }
			for(int i=0; i < arrayLength; i++)
                array_cData[i] = MyArray[i];


		}

		void Copy(const Array<Type> &MyArray)
        {
            if(!MyArray.Exist())
                return;

            if(Exist())
            {
                if(MyArray.array_iCount > this->array_iCount)
                    return;
                this->Clear();
            }
            for(int i=0; i < MyArray.array_iCount; i++)
                array_cData[i] = MyArray.array_cData[i];

		}

		Type* toStd()
        {
            if(!this->Exist())
                return nullptr;

            Type* arrayOffset = new Type[this->array_iCount];

            for(int i=0; i < this->array_iCount; i++)
                arrayOffset[i] = this->array_cData[i];

            return arrayOffset;
		}

        static Type* toStd(const Array<Type> &MyArray)
        {
            if(!MyArray.Exist())
                return nullptr;

            Type* arrayOffset = new Type[MyArray.array_iCount];

            for(int i=0; i < MyArray.array_iCount; i++)
                arrayOffset[i] = MyArray.array_cData[i];

            return arrayOffset;
		}

		/* Operators */
		Type& operator[] (index Index)
		{
			if (Index >= 0 && Index < array_iCount && Exist())
				return array_cData[Index];
		}

		void operator= (Type* equal)
		{
		    this->Copy(equal);
        }
		/* Operators */
        /* Getters and Setters */
		bool Exist() const { return array_bStart; }
		int Size() const { return array_iCount; }
		void setArray(Type Element, int Position) { if (Exist()) array_cData[Position] = Element; }
		Type* getArray() { return array_cData; }
		/* Getters and Setters */

	};
}

