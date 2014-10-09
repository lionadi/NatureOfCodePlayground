#ifndef MODELDEFINES_H
#define MODELDEFINES_H
#include "..\Math\MathOperations.h"

using namespace Aurora::Math;

namespace Aurora
{
	namespace Model
	{

enum mPOLYGONATTRIBUTES {	INVALID_POLY_ATTRIBUTE	= 0x0001,	/*!< .*/
							POLY_2SIDED				= 0x0002,	/*!< .*/
							POLY_TRANSPARENT		= 0x0004,	/*!< .*/
							POLY_8BITCOLOR			= 0x0006,	/*!< .*/
							POLY_RGB16				= 0x0008,	/*!< .*/
							POLY_RGB24				= 0x0010,	/*!< .*/
							POLY_SHADEMODE_PURE		= 0x0012,	/*!< .*/
							POLY_SHADEMODE_FLAT		= 0x0014,	/*!< .*/
							POLY_SHADEMODE_GOURAUD	= 0x0016,	/*!< .*/
							POLY_SHADEMODE_PHONG	= 0x0018	/*!< .*/
						};

enum mPOLYGONSTATES {	INVALID_POLY_STATE		= 0x0001,	/*!< .*/
						POLY_ACTIVE				= 0x0002,	/*!< .*/
						POLY_CLIPPED			= 0x0004,	/*!< .*/
						POLY_BACKFACE			= 0x0006	/*!< .*/
					};
/**
 * \ingroup modelLoader
 *
 *
 * \par requirements
 * win98 or later\n
 * win2k or later\n
 * MFC\n
 *
 * \version 1.0
 * first version
 *
 * \date 06-30-2005
 *
 * \author Adrian
 *
 * \par license
 * This code is absolutely free to use and modify. The code is provided "as is" with
 * no expressed or implied warranty. The author accepts no liability if it causes
 * any damage to your computer, causes your pet to fall ill, increases baldness
 * or makes your car start emitting strange noises when you start it up.
 * This code has no bugs, just undocumented features!
 * 
 * \todo 
 *
 * \bug 
 *
 */
/* Holds vertexes for a polygon. */
class mVertexList
{
public:
	/**
	 *
	 * \return 
	 */
	mVertexList();
	/**
	 *
	 * \param vertexAmount 
	 * \return 
	 */
	mVertexList(int vertexAmount);
	/**
	 *
	 * \return 
	 */
	~mVertexList();

	/**
	 *
	 * \param vertexAmount 
	 */
	void AllocateMemoryForVertex(int vertexAmount);
	int vertexAmount;		/*!< .*/
	VECTOR4D *VertexData;	/*!< .*/


};

/**
 * \ingroup modelLoader
 *
 *
 * \par requirements
 * win98 or later\n
 * win2k or later\n
 * MFC\n
 *
 * \version 1.0
 * first version
 *
 * \date 06-30-2005
 *
 * \author Adrian
 *
 * \par license
 * This code is absolutely free to use and modify. The code is provided "as is" with
 * no expressed or implied warranty. The author accepts no liability if it causes
 * any damage to your computer, causes your pet to fall ill, increases baldness
 * or makes your car start emitting strange noises when you start it up.
 * This code has no bugs, just undocumented features!
 * 
 * \todo 
 *
 * \bug 
 *
 */
/* Holds a single polygons data as a vertexlist. */
class mPOLYGON4D
{
	public:
		/**
		 *
		 * \return 
		 */
		mPOLYGON4D();
		/**
		 *
		 * \param VList 
		 * \return 
		 */
		mPOLYGON4D(mVertexList *const VList);
		/**
		 *
		 * \return 
		 */
		~mPOLYGON4D();

		mPOLYGONATTRIBUTES	PolygonAttributes;	/*!< .*/
		mPOLYGONSTATES		PolygonStates;		/*!< .*/
		int Color;								/*!< .*/

		mVertexList *VertexList;				/*!< .*/
		int VertexIndex_1;						/*!< .*/
		int VertexIndex_2;						/*!< .*/
		int VertexIndex_3;						/*!< .*/
	private:

};

/**
 * \ingroup modelLoader
 *
 *
 * \par requirements
 * win98 or later\n
 * win2k or later\n
 * MFC\n
 *
 * \version 1.0
 * first version
 *
 * \date 06-30-2005
 *
 * \author Adrian
 *
 * \par license
 * This code is absolutely free to use and modify. The code is provided "as is" with
 * no expressed or implied warranty. The author accepts no liability if it causes
 * any damage to your computer, causes your pet to fall ill, increases baldness
 * or makes your car start emitting strange noises when you start it up.
 * This code has no bugs, just undocumented features!
 * 
 * \todo 
 *
 * \bug 
 *
 */
/* Holds a single object data as multiple polygons. */
class mOBJECT4D
{
	public:
		/**
		 *
		 * \return 
		 */
		mOBJECT4D();									
		/**
		 *
		 * \param VertexAmount 
		 * \param PolygonAmount 
		 * \return 
		 */
		mOBJECT4D(int VertexAmount, int PolygonAmount);	
		/**
		 *
		 * \return 
		 */
		~mOBJECT4D();									

		int Identification;								/*!< .*/
		VERTEX4D WorldPosition;							/*!< .*/

		VECTOR4D Dir;									/*!< .*/

		VECTOR4D ux, uy, uz;							/*!< .*/

		int VertexAmount;								/*!< .*/

		VERTEX4D	*Local_VertexList;					/*!< .*/
		VERTEX4D	*Transformed_VertexList;			/*!< .*/

		int PolygonAmount;								/*!< .*/

		mPOLYGON4D *PolygonList;						/*!< .*/
		mPOLYGON4D *TransformedPolygonList;				/*!< .*/

		/**
		 *
		 * \param VertexAmount 
		 */
		void AllocateMemoryToLocalVertexList(int VertexAmount);
		/**
		 *
		 * \param void 
		 */
		void AllocateMemoryToTransformedVertexList(void);
		/**
		 *
		 * \param PolygonAmount 
		 */
		void AllocateMemoryToPolygonList(int PolygonAmount);
		/**
		 *
		 * \param void 
		 */
		void AllocateMemoryToTransformedPolygonList(void);
};

/**
 * \ingroup modelLoader
 *
 *
 * \par requirements
 * win98 or later\n
 * win2k or later\n
 * MFC\n
 *
 * \version 1.0
 * first version
 *
 * \date 06-30-2005
 *
 * \author Adrian
 *
 * \par license
 * This code is absolutely free to use and modify. The code is provided "as is" with
 * no expressed or implied warranty. The author accepts no liability if it causes
 * any damage to your computer, causes your pet to fall ill, increases baldness
 * or makes your car start emitting strange noises when you start it up.
 * This code has no bugs, just undocumented features!
 * 
 * \todo 
 *
 * \bug 
 *
 */
class mMODEL4D
{
	public:
		/**
		 *
		 * \return 
		 */
		mMODEL4D();
		/**
		 *
		 * \return 
		 */
		~mMODEL4D();

		int ObjectsAmount;						/*!< .*/
		mOBJECT4D *ObjectList;					/*!< .*/
		//mOBJECT4D *TransformedObjectList;		/*!< .*/

		/**
		 *
		 * \param ObjectsAmount 
		 */
		void AllocateMemoryForObjectsList(int ObjectsAmount);
		//void AllocateMemoryForTransformedObjectsList(void);

};

};
};

#endif