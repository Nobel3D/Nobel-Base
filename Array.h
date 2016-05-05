#pragma once

#include <cstddef>

namespace NobelLib
{
	template < class Type >
	class Array
	{
	private:
		Type* array_cData;
		int array_iCount;

		int arraySize(const Type* array)
        {
            int i = 0;

            while(*array++) i++;

            return i;
        }

		void expArray(int NewIndex)
		{
			if (Exist() && NewIndex>array_iCount);
			if (array_iCount == 0) {
				this->New(NewIndex);
				return;
			}
			else
			{
                Type* secondArray = new Type[NewIndex + 1];

				for (int i = 0; i<array_iCount; i++)
					secondArray[i] = array_cData[i];



				array_iCount = NewIndex;
				array_cData = secondArray;
			}
		}
		Type* newArray(int Index)
        {
            Type* arrayOffset = new Type[Index + 1];

            for(int i = 0; i<Index; i++)
                arrayOffset[i] = Type();

            return arrayOffset;
		}

		Type* copyArray(const Type* copyArray)
        {
            if(!copyArray)
                return NULL;

            int lengthArray = arraySize(copyArray);
            Type* arrayOffset = newArray(lengthArray);
            while(lengthArray--)
                arrayOffset[lengthArray] = copyArray[lengthArray];

            return arrayOffset;
		}

		void deleteArray()
		{
			if (Exist())
				delete[] array_cData;
            array_cData = NULL;
            array_iCount = 0;
		}

	public:
		/* Constructor and Destructor*/
		Array()
        {
			array_iCount = NULL;
			array_cData = NULL;
		}

		Array(int index)
		{
			this->New(index);
		}

		Array(Array<Type> &Other)
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
				    array_iCount = index;
                    array_cData = newArray(index);
				}
		}

		void New(int Index)
        {
			if (!Exist())
			{
			    array_iCount = Index;
				array_cData = newArray(Index);
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
            int copylength = arraySize(MyArray);
            if(copylength > this->Size())
                return;

            this->Delete();

			array_iCount = copylength;
			array_cData = copyArray(MyArray);

		}

		void Copy(Array<Type> &MyArray)
        {
            if(!MyArray.Exist())
                return;
            if(MyArray.Size() > this->Size())
                return;

            this->Delete();

			array_iCount = MyArray.array_iCount;
			array_cData = MyArray.array_cData;

		}

		/* Operators */
		Type& operator[] (int Index)
		{
			//if (Index >= 0 && Index < array_iCount)
				return array_cData[Index];
		}

		const Type& operator[] (int Index)const
		{
			//if (Index >= 0 && Index < array_iCount)
				return array_cData[Index];
		}

		void operator= (Type* equal)
		{
		    this->Copy(equal);
        }
        /* Operators */

        /* Getters and Setters */
		bool Exist() { return array_iCount > 1; }
		int Size() { return array_iCount; }
		void setArray(Type Element, int Position) { if (Exist()) array_cData[Position] = Element; }
		/* Getters and Setters */

	};
}

