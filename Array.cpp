#include "Array.h"

using namespace NobelLib;

		template<class Type>
		void Array<Type>::Delete()


		template<class Type>
		bool Array<Type>::Exist()


		template<class Type>
		Array<Type>::Array()


		template<class Type>
		Array<Type>::Array(int index)


		template<class Type>
		Array<Type>::Array(const Array<Type> &Other)


/*		template<class Type>
		void Array<Type>::Clear()
		{
			if (Exist())
			{
				Delete();
			}

		}
*/
		template<class Type>


		template<class Type>
		void Array<Type>::New(int Index)


		template<class Type>
		void Array<Type>::Copy(const Array<Type> &MyArray)


		template<class Type>
		Type& Array<Type>::operator[] (int Index)
		{
			if (Index >= 0 && Index < array_Elements)
				return array_Type[Index];
		}

		template<class Type>
		const Type& Array<Type>::operator[] (int Index)const


		template<class Type>
		void Array<Type>::operator= (Type* equal)


		template<class Type>

