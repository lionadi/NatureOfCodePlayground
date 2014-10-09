#ifndef MATRIX_H
#define MATRIX_H
#include "..\Globals\GlobalDatatypes.h"

using namespace Aurora::DataTypes;

/*!
Namespace: Aurora

This namespace is the main package for the engine. It holds all the main classes, namespaces, operations etc... that defines the functionality of this
project/engine.
*/
namespace Aurora
{
	/*!
	Namespace: Math

	This namespace holds needed math operations for the engine.
	*/
	namespace Math
	{

		/*!
		 	\brief The properties of this class are the same as the 4x4 matrix. Please seek guidance from the documentation of the 4x4 matrix
		 	\version 1.0
		  	first version
		 
		  	\date 02-03-2005
		 
		  	\author Lion1
		  
		  	\todo 
		 
		 	\bug 
		 
		*/
		class MATRIX2X2
		{
			public:
				MATRIX2X2();
				MATRIX2X2(Float m00, Float m01, Float m10, Float m11);
				MATRIX2X2(const MATRIX2X2 &mat);
				~MATRIX2X2();
				Float M11, M12;
				Float M21, M22;

				MATRIX2X2 operator+(const Float				&value);
				MATRIX2X2 operator+(const MATRIX2X2			&value);

				MATRIX2X2 operator-(const Float				&value);
				MATRIX2X2 operator-(const MATRIX2X2			&value);

				MATRIX2X2 &operator=(const MATRIX2X2		&value);

				MATRIX2X2 &operator+=(const Float			&value);
				MATRIX2X2 &operator+=(const MATRIX2X2		&value);

				MATRIX2X2 &operator-=(const Float			&value);
				MATRIX2X2 &operator-=(const MATRIX2X2		&value);

				MATRIX2X2 operator*(const Float				&value);
				MATRIX2X2 operator*(const MATRIX2X2			&value);

				MATRIX2X2 &operator*=(const Float			&value);
				MATRIX2X2 &operator*=(const MATRIX2X2		&value);
				
			protected:
		};

		/*!
		 	\brief The properties of this class are the same as the 4x4 matrix. Please seek guidance from the documentation of the 4x4 matrix
		 	\version 1.0
		  	first version
		 
		  	\date 02-03-2005
		 
		  	\author Lion1
		  
		  	\todo 
		 
		 	\bug 
		 
		*/
		class MATRIX3X3
		{
		public:
			MATRIX3X3();
			MATRIX3X3(Float m00, Float m01, Float m02, Float m10, Float m11, Float m12, Float m20, Float m21, Float m22);
			MATRIX3X3(const MATRIX3X3 &mat);
			~MATRIX3X3();
			Float M11, M12, M13;
			Float M21, M22, M23;
			Float M31, M32, M33;

			MATRIX3X3 operator+(const Float				&value);
			MATRIX3X3 operator+(const MATRIX3X3			&value);

			MATRIX3X3 operator-(const Float				&value);
			MATRIX3X3 operator-(const MATRIX3X3			&value);

			MATRIX3X3 &operator=(const MATRIX3X3		&value);

			MATRIX3X3 &operator+=(const Float			&value);
			MATRIX3X3 &operator+=(const MATRIX3X3		&value);

			MATRIX3X3 &operator-=(const Float			&value);
			MATRIX3X3 &operator-=(const MATRIX3X3		&value);

			MATRIX3X3 operator*(const Float				&value);
			MATRIX3X3 operator*(const MATRIX3X3			&value);

			MATRIX3X3 &operator*=(const Float			&value);
			MATRIX3X3 &operator*=(const MATRIX3X3		&value);

		protected:
		};

		/*!
		 	\brief A matrix class that can be used for mathematical purposes. The dimension is 4x4. Notice the functionalities that are in this class can be founded also in the matrix classes  MATRIX3X3 and MATRIX2X2, the only difference are the dimensions.
		 	\version 1.0
		  	first version
		 
		  	\date 02-03-2005
		 
		  	\author Lion1
		  
		  	\todo 
		 
		 	\bug 
		 
		*/
		class MATRIX4X4
		{
		public:
			/*!
				\brief Basic class constructor. This will format the matrix as an Identity matrix.
			*/
			MATRIX4X4();
			/*!
				\brief Use this constructor to format the matrix with the wanted values. The are as follows:
				
					| column |  column |column |column
				------------------------------------
				row |	m00		m01		m02		m03
				row	|	m10		m11		m12		m13
				row	|	m20		m21		m22		m23
				row	|	m30		m31		m32		m33
			*/
			MATRIX4X4(Float m00, Float m01, Float m02, Float m03, Float m10, Float m11, Float m12, Float m13, Float m20, Float m21, Float m22, Float m23, Float m30, Float m31, Float m32, Float m33);
			/*!
				\brief This is this classes copy-constructor.
				\param &mat Another 4x4 matrix.
			*/
			MATRIX4X4(const MATRIX4X4 &mat);
			/*!
				\brief Class destructor.
			*/
			~MATRIX4X4();
			Float M11, M12, M13, M14;	/*!< First row of the matrix.	*/
			Float M21, M22, M23, M24;	/*!< Second row of the matrix.	*/
			Float M31, M32, M33, M34;	/*!< Third row of the matrix.	*/
			Float M41, M42, M43, M44;	/*!< Fourth row of the matrix.	*/

			/*!
				\brief Adds a scalar value into every element of the matrix.
				\param &value The scalar value to be added.
				\return A copy of this matrix with the added scalar value. Notice the is not added directly into the class, but it is copyed to the assigned to the place needed. If you need to add and assign the data into this class, then use the += operator.
			*/
			MATRIX4X4 operator+(const Float				&value);
			/*!
				\brief Adds another 4x4 matrix with this class and returns a copy.
				\param &value The other 4x4 matrix to be added with this class.
				\return A copy of the added matrixes.
			*/
			MATRIX4X4 operator+(const MATRIX4X4			&value);

			/*!
				\brief Same properties as the addition but in this case it is negation.
			*/
			MATRIX4X4 operator-(const Float				&value);
			/*!
			\brief Same properties as the addition but in this case it is negation.
			*/
			MATRIX4X4 operator-(const MATRIX4X4			&value);

			/*!
				\brief This is the assignment operator, it will assign the values of another 4x4 matrix into this one and returns an reference to *this.
				\param &value Another 4x4 matrix whos values needs to be assigned into this class.
				\return An reference to *this.
			*/
			MATRIX4X4 &operator=(const MATRIX4X4		&value);

			/*!
				\brief This will add the given scalar value directly into the class and returns an reference to *this.
				\param &value The scalar value to be added.
				\return An reference to *this.
			*/
			MATRIX4X4 &operator+=(const Float			&value);
			/*!
				\brief This will add the values of another 4x4 matrix directly into this class and returns an reference to *this.
				\param &value Another 4x4 matrix.
				\return Returns an reference to *this.
			*/
			MATRIX4X4 &operator+=(const MATRIX4X4		&value);

			/*!
				\brief Same as addition assignment but negation in this case.
			*/
			MATRIX4X4 &operator-=(const Float			&value);
			/*!
			\brief Same as addition assignment but negation in this case.
			*/
			MATRIX4X4 &operator-=(const MATRIX4X4		&value);

			/*!
				\brief This operator will multiply every component of this class by the given scalar value and then return the result as a copy.
				\param &value The scalar to be multiplyed.
				\return Returns an copy of the result.
			*/
			MATRIX4X4 operator*(const Float				&value);
			/*!
				\brief This will multiply an another 4x4 matrix and return the result as a copy.
				\param &value Another 4x4 matrix.
				\return The result copy.
			*/
			MATRIX4X4 operator*(const MATRIX4X4			&value);

			/*!
				\brief Same as normal multiplication but in this case the result will be inserted into the class and the operator will return an reference to *this.
			*/
			MATRIX4X4 &operator*=(const Float			&value);
			/*!
			\brief Same as normal multiplication but in this case the result will be inserted into the class and the operator will return an reference to *this.
			*/
			MATRIX4X4 &operator*=(const MATRIX4X4		&value);

		protected:
		};

	}; // END OF NAMESPACE
}; // END OF NAMESPACE

#endif