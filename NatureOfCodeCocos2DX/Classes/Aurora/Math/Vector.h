#ifndef VECTOR_H
#define VECTOR_H

#include "Matrix.h"
#include "cocos2d.h"

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
		 	\brief A class that can hold vector data and perform vector sepecific operations. For a more specific documentation see VECTOR4D text. Both classes work in the same way(same as VECTOR3D). The only difference are the scalar values in the vector classes.
		 	\version 1.0
		  	first version
		 
		  	\date 01-27-2005
		 
		  	\author Adrian Simionescu
		  
		 
		*/
		class VECTOR2D
		{
			public:
				/*!
					\brief 
					\return 
				*/
				VECTOR2D();
				/*!
					\brief 
					\param x 
					\param y 
					\return 
				*/
				VECTOR2D(Float x, Float y);
				/*!
					\brief 
					\param &value 
					\return 
				*/
				VECTOR2D(const VECTOR2D &value);
				~VECTOR2D();

				float X;
				float Y;
				// ADDITION - OPERATIONS
				//--------------------------------------------------------
				/*!
					\brief 
					\param &value 
					\return 
				*/
				VECTOR2D operator+(const Float			&value);
				/*!
					\brief 
					\param &value 
					\return 
				*/
				VECTOR2D operator+(const VECTOR2D		&value);

				// NEGATION - OPERATIONS
				//--------------------------------------------------------
				/*!
					\brief 
					\param &value 
					\return 
				*/
				VECTOR2D operator-(const Float			&value);
				/*!
					\brief 
					\param &value 
					\return 
				*/
				VECTOR2D operator-(const VECTOR2D		&value);

				// ASSIGNMENT - OPERATIONS
				//--------------------------------------------------------
				/*!
					\brief 
					\param &value 
					\return 
				*/
				VECTOR2D &operator=(const Float			&value);
				/*!
					\brief 
					\param &value 
					\return 
				*/
				VECTOR2D &operator=(const VECTOR2D		&value);

				/*!
					\brief 
					\param &value 
					\return 
				*/
				VECTOR2D &operator+=(const Float		&value);
				/*!
					\brief 
					\param &value 
					\return 
				*/
				VECTOR2D &operator+=(const VECTOR2D		&value);

				/*!
					\brief 
					\param &value 
					\return 
				*/
				VECTOR2D &operator-=(const Float		&value);
				/*!
					\brief 
					\param &value 
					\return 
				*/
				VECTOR2D &operator-=(const VECTOR2D		&value);

				/*!
					\brief 
					\param &value 
					\return 
				*/
				VECTOR2D operator*(const Float		&value);

				/*!
					\brief 
					\param &value 
					\return 
				*/
				Float operator*(const VECTOR2D		&value);

				/*!
					\brief 
					\param &value 
					\return 
				*/
				VECTOR2D &operator*=(const Float		&value);
            
                VECTOR2D operator/(const Float		&value);

                VECTOR2D &operator*=(const MATRIX2X2		&value);
            
                VECTOR2D operator*(const MATRIX2X2		&value);

				bool operator==(const VECTOR2D		&value);

				bool operator!=(const VECTOR2D		&value);

				/*!
					\brief Zeros a vector
					\param void 
				*/
				void ZeroVector(void);
            
                void Limit(	const Float &lowerLimit, const Float &upperLimit);

			protected:

		};

		/*!
		\brief A class that can hold vector data and perform vector sepecific operations. For a more specific documentation see VECTOR4D text. Both classes work in the same way(same as VECTOR2D). The only difference are the scalar values in the vector classes.
		\version 1.0
		first version

		\date 01-27-2005

		\author Adrian Simionescu

		*/
		class VECTOR3D
		{
		public:
			/*!
				\brief 
				\return 
			*/
			VECTOR3D();
			/*!
				\brief 
				\param x 
				\param y 
				\param z 
				\return 
			*/
			VECTOR3D(Float x, Float y, Float z);
			/*!
				\brief 
				\param &value 
				\return 
			*/
			VECTOR3D(const VECTOR3D &value);
			~VECTOR3D();

			float X;
			float Y;
			float Z;

			// ADDITION - OPERATIONS
			//--------------------------------------------------------
			/*!
				\brief 
				\param &value 
				\return 
			*/
			VECTOR3D operator+(const Float			&value);
			/*!
				\brief 
				\param &value 
				\return 
			*/
			VECTOR3D operator+(const VECTOR3D		&value);

			// SUBSTRACTION - OPERATIONS
			//--------------------------------------------------------
			/*!
				\brief 
				\param &value 
				\return 
			*/
			VECTOR3D operator-(const Float			&value);
			/*!
				\brief 
				\param &value 
				\return 
			*/
			VECTOR3D operator-(const VECTOR3D		&value);

			// ASSIGNMENT - OPERATIONS
			//--------------------------------------------------------
			/*!
				\brief 
				\param &value 
				\return 
			*/
			VECTOR3D &operator=(const Float			&value);
			/*!
				\brief 
				\param &value 
				\return 
			*/
			VECTOR3D &operator=(const VECTOR3D		&value);

			VECTOR3D &operator+=(const Float		&value);
			/*!
				\brief 
				\param &value 
				\return 
			*/
			VECTOR3D &operator+=(const VECTOR3D		&value);

			/*!
				\brief 
				\param &value 
				\return 
			*/
			VECTOR3D &operator-=(const Float		&value);
			/*!
				\brief 
				\param &value 
				\return 
			*/
			VECTOR3D &operator-=(const VECTOR3D		&value);

			/*!
				\brief 
				\param &value 
				\return 
			*/
			VECTOR3D operator*(const Float		&value);

			/*!
				\brief 
				\param &value 
				\return 
			*/
			Float operator*(const VECTOR3D		&value);

			/*!
				\brief 
				\param &value 
				\return 
			*/
			VECTOR3D &operator*=(const Float		&value);

            VECTOR3D operator/(const Float		&value);
            
            VECTOR3D &operator*=(const MATRIX3X3		&value);
            
            VECTOR3D operator*(const MATRIX3X3		&value);
            
			bool operator==(const VECTOR3D		&value);

			bool operator!=(const VECTOR3D		&value);

			/*!
			\brief Zeros a vector
			\param void 
			*/
			void ZeroVector(void);
            
            void Limit(	const Float &lowerLimit, const Float &upperLimit);

		protected:

		};

		/*!
		\brief A class that can hold vector data and perform vector sepecific operations.
		\version 1.0
		first version

		\date 01-27-2005

		\author Adrian Simionescu


		*/
		class VECTOR4D
		{
		public:
			/*!
				\brief An empty constructor. Call it when you want a vector on a vertex to start at position 0,0,0,0 for parameter x,y,z,w.
				\return None
			*/
			VECTOR4D();
			/*!
				\brief Use this constructor to define stating values by you. The values are x,y,z,w in the order presented. Notice float are used here.
				\param x The X value representing the x value in a coordinate system.
				\param y The Y value representing the y value in a coordinate system.
				\param z The Z value representing the z value in a coordinate system.
				\param w The W value representing the w value in a coordinate system.
				\return None
			*/
			VECTOR4D(Float x, Float y, Float z, Float w);
			/*!
				\brief Use this copy constructor to make a simple copy of another vector given to this constructor by you.
				\param &value Another VECTOR4D class.
				\return None
			*/
			VECTOR4D(const VECTOR4D &value);
			~VECTOR4D();

			float X; /*!< The X value representing the x value in a coordinate system. */
			float Y; /*!< The Y value representing the y value in a coordinate system. */
			float Z; /*!< The Z value representing the z value in a coordinate system. */
			float W; /*!< The W value representing the w value in a coordinate system. */

			// ADDITION - OPERATIONS
			//--------------------------------------------------------
			/*!
				\brief Use this operator to add a given scalar value to every component of this vector.
				\param &value A float scalar value.
				\return An reference to this class. This property can be use for chaining vectors. If you need a copy of a vector use the copy constructor for such operation.
			*/
			VECTOR4D operator+(const Float			&value);
			/*!
				\brief Use this operator to add a given vector classes components to the components in this class.
				\param &value The wanted class that components needs to be added into this class.
				\return An reference to this class.
			*/
			VECTOR4D operator+(const VECTOR4D		&value);

			// NEGATION - OPERATIONS
			//--------------------------------------------------------
			/*!
				\brief Use this operator to negate a given scalar value to every component of this vector.
				\param &value A float scalar value.
				\return An reference to this class. 
			*/
			VECTOR4D operator-(const Float			&value);
			/*!
				\brief Use this operator to negate a given vector classes components to the components in this class.
				\param &value The wanted class that components needs to be negated into this class.
				\return An reference to this class.
			*/
			VECTOR4D operator-(const VECTOR4D		&value);

			// ASSIGNMENT - OPERATIONS
			//--------------------------------------------------------
			/*!
				\brief Use this operator to assign a given scalar value to every component of this vector.
				\param &value A float scalar value.
				\return An reference to this class.
			*/
			VECTOR4D &operator=(const Float			&value);
			/*!
				\brief Use this operator to assign a given vector classes components to the components in this class.
				\param &value The wanted class that components needs to be assigned into this class.
				\return An reference to this class. This property can be use for chaining vectors. If you need a copy of a vector use the copy constructor for such operation.
			*/
			VECTOR4D &operator=(const VECTOR4D		&value);

			/*!
				\brief Use this operator to add a given scalar value to every component of this vector.
				\param &value A float scalar value.
				\return An reference to this class. This property can be use for chaining vectors. If you need a copy of a vector use the copy constructor for such operation.
			*/
			VECTOR4D &operator+=(const Float		&value);
			/*!
				\brief Use this operator to add a given vector classes components to the components in this class.
				\param &value The wanted class that components needs to be assigned into this class.
				\return An reference to this class. This property can be use for chaining vectors. If you need a copy of a vector use the copy constructor for such operation.
			*/
			VECTOR4D &operator+=(const VECTOR4D		&value);

			/*!
				\brief Use this operator to negate a given scalar value to every component of this vector.
				\param &value A float scalar value.
				\return An reference to this class. This property can be use for chaining vectors. If you need a copy of a vector use the copy constructor for such operation.
			*/
			VECTOR4D &operator-=(const Float		&value);
			/*!
				\brief Use this operator to negate a given vector classes components to the components in this class.
				\param &value The wanted class that components needs to be assigned into this class.
				\return An reference to this class. This property can be use for chaining vectors. If you need a copy of a vector use the copy constructor for such operation.
			*/
			VECTOR4D &operator-=(const VECTOR4D		&value);

			/*!
				\brief 
				\param &value 
				\return 
			*/
			VECTOR4D operator*(const Float		&value);

			/*!
				\brief 
				\param &value 
				\return 
			*/
			Float operator*(const VECTOR4D		&value);

			/*!
				\brief 
				\param &value 
				\return 
			*/
			VECTOR4D &operator*=(const Float		&value);

			/*!
				\brief 
				\param &value 
				\return 
			*/
			VECTOR4D operator*(const MATRIX4X4		&value);

			/*!
				\brief 
				\param &value 
				\return 
			*/
			VECTOR4D &operator*=(const MATRIX4X4		&value);

            VECTOR4D operator/(const Float		&value);
            
			bool operator==(const VECTOR4D		&value);

			bool operator!=(const VECTOR4D		&value);

			/*!
			\brief Zeros a vector
			\param void 
			*/
			void ZeroVector(void);
            
            void Limit(	const Float &lowerLimit, const Float &upperLimit);
		protected:

		};

		typedef VECTOR2D VERTEX2D;	/*!< An alias for the VECTOR2D class so that use may use it to give you a better representation of a vertex or a point if needed. */
		typedef VECTOR3D VERTEX3D;	/*!< An alias for the VECTOR3D class so that use may use it to give you a better representation of a vertex or a point if needed. */
		typedef VECTOR4D VERTEX4D;	/*!< An alias for the VECTOR4D class so that use may use it to give you a better representation of a vertex or a point if needed. */
	}; // END OF NAMESPACE MATH
}; // END OF NAMESPACE Aurora


#endif