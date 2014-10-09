
#include "ModelLoad.h"

namespace Aurora
{
	namespace Model
	{

Loader::Loader()
{

}


Loader::~Loader()
{

}

void Loader::LoadModel(char *fileName, mMODEL4D *model)
{
	int Selector = 0;
	std::ifstream inA(fileName, std::ios::binary);

	inA.read((char*)&Selector, sizeof(Selector));
	if(Selector != StartOfData)
	{ return; }

	model->AllocateMemoryForObjectsList(1);
	do 
	{
		inA.read((char*)&Selector, sizeof(Selector));
		switch(Selector)
		{
			case BeginObject:
			{
				this->LoadObjectData(inA, model);
			} break;

			default: { } break;
		};
	} while(Selector!= 0 && Selector != EndOfData);
	/*inA.read((char*)&Selector, sizeof(Selector));

	inA.read((char*)&Selector, sizeof(Selector));
	inA.read((char*)&Selector, sizeof(Selector));

	float fDataA = 0; 
	float fDataB = 0; 
	float fDataC = 0;

	for(int x = 0; x < Selector; ++x)
	{
		inA.read((char*)&fDataA,sizeof(fDataA));
		inA.read((char*)&fDataB,sizeof(fDataB));
		inA.read((char*)&fDataC,sizeof(fDataC));
	}*/


}

void Loader::LoadObjectData(std::ifstream &inA, mMODEL4D *model)
{
	int Selector	= 0;
	int iDataA		= 0;
	int iDataB		= 0;
	int iDataC		= 0;
	float fDataA	= 0;
	float fDataB    = 0;
	float fDataC	= 0;
	do
	{
		inA.read((char*)&Selector, sizeof(Selector));
		switch(Selector)
		{
			case StartVertexList:
			{
				inA.read((char*)&iDataA, sizeof(iDataA));
				model->ObjectList[(model->ObjectsAmount-1)].AllocateMemoryToLocalVertexList(iDataA);
				for(int x = 0; x < iDataA; ++x)
				{
					inA.read((char*)&fDataA, sizeof(fDataA));
					inA.read((char*)&fDataB, sizeof(fDataB));
					inA.read((char*)&fDataC, sizeof(fDataC));
					model->ObjectList[(model->ObjectsAmount-1)].Local_VertexList[x].X = fDataA;
					model->ObjectList[(model->ObjectsAmount-1)].Local_VertexList[x].Y = fDataB;
					model->ObjectList[(model->ObjectsAmount-1)].Local_VertexList[x].Z = fDataC;
					model->ObjectList[(model->ObjectsAmount-1)].Local_VertexList[x].W = 1.0f;
				}
			} break;

			case StartFaceList:
			{
				inA.read((char*)&iDataA, sizeof(iDataA));
				model->ObjectList[(model->ObjectsAmount-1)].AllocateMemoryToPolygonList(iDataA);
				for(int x = 0; x < iDataA; ++x)
				{
					inA.read((char*)&iDataA, sizeof(iDataA));
					inA.read((char*)&iDataB, sizeof(iDataB));
					inA.read((char*)&iDataC, sizeof(iDataC));
					model->ObjectList[(model->ObjectsAmount-1)].PolygonList[x].VertexIndex_1 = iDataA;
					model->ObjectList[(model->ObjectsAmount-1)].PolygonList[x].VertexIndex_2 = iDataB;
					model->ObjectList[(model->ObjectsAmount-1)].PolygonList[x].VertexIndex_3 = iDataC;
				}
			} break;

			default: { } break;
		};
	} while(Selector != EndOfObject);
}

};
};