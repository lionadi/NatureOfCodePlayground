//#include "stdafx.h"
#include "ModelDefines.h"

namespace Aurora
{
	namespace Model
	{

mPOLYGON4D::mPOLYGON4D()
{


}
mPOLYGON4D:: mPOLYGON4D(mVertexList *const VList)
{
	this->VertexList = VList;
}

mPOLYGON4D::~mPOLYGON4D()
{

}


mVertexList::mVertexList()
{
	this->VertexData = 0;
}

mVertexList::mVertexList(int vertexAmount)
{
	this->VertexData = new VECTOR4D[vertexAmount];
	this->vertexAmount = vertexAmount;
}

mVertexList::~mVertexList()
{
	if(this->VertexData)
	{
		delete[] this->VertexData;
	}
}

void mVertexList::AllocateMemoryForVertex(int vertexAmount)
{
	this->VertexData = new VECTOR4D[vertexAmount];
	this->vertexAmount = vertexAmount;
}

mOBJECT4D::mOBJECT4D()
{
	this->PolygonList				= 0;
	this->Local_VertexList			= 0;
	this->Transformed_VertexList	= 0;
}

mOBJECT4D::mOBJECT4D(int VertexAmount, int PolygonAmount)
{
	this->Local_VertexList	= new VERTEX4D[VertexAmount];
	this->PolygonList		= new mPOLYGON4D[PolygonAmount];

	this->VertexAmount = VertexAmount;
	this->PolygonAmount = PolygonAmount;
}
mOBJECT4D::~mOBJECT4D()
{
	if(this->PolygonList)
	{ delete[] this->PolygonList; }

	if(this->Local_VertexList)
	{ delete[] this->Local_VertexList; }

	if(this->Transformed_VertexList)
	{ delete[] this->Transformed_VertexList; }
}

void mOBJECT4D::AllocateMemoryToLocalVertexList(int VertexAmount)
{
	if(this->Local_VertexList)
	{ delete[] this->Local_VertexList; }

	this->Local_VertexList = new VERTEX4D[VertexAmount];
	this->VertexAmount = VertexAmount;
}

void mOBJECT4D::AllocateMemoryToTransformedVertexList(void)
{
	if(this->VertexAmount <= 0) 
	{ return; }

	if(this->Transformed_VertexList)
	{ delete[] this->Transformed_VertexList; }

	this->Transformed_VertexList = new VERTEX4D[this->VertexAmount];

}

void mOBJECT4D::AllocateMemoryToPolygonList(int PolygonAmount)
{
	if(this->PolygonList)
	{ delete[] this->PolygonList; }

	this->PolygonList = new mPOLYGON4D[PolygonAmount];
	this->PolygonAmount = PolygonAmount;
}

void mOBJECT4D::AllocateMemoryToTransformedPolygonList()
{
	if(this->PolygonAmount <= 0) 
	{ return; }

	if(this->TransformedPolygonList)
	{ delete[] this->TransformedPolygonList; }

	this->TransformedPolygonList = new mPOLYGON4D[PolygonAmount];
}

mMODEL4D::mMODEL4D()
{
	this->ObjectList = 0;
}

mMODEL4D::~mMODEL4D()
{
	if(this->ObjectList)
	{ delete[] this->ObjectList; }
}

void mMODEL4D::AllocateMemoryForObjectsList(int ObjectsAmount)
{
	if(this->ObjectList)
	{ delete[] this->ObjectList; }

	this->ObjectList = new mOBJECT4D[ObjectsAmount];
	this->ObjectsAmount = ObjectsAmount;
}

/*void mMODEL4D::AllocateMemoryForTransformedObjectsList(void)
{
	if(this->ObjectsAmount <= 0) 
	{ return; }

	if(this->TransformedObjectList)
	{ delete[] this->TransformedObjectList; }

	this->TransformedObjectList = new mOBJECT4D[ObjectsAmount];
}*/

};
};