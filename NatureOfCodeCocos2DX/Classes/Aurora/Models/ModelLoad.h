#ifndef MODELLOAD_H
#define MODELLOAD_H

#include <fstream>			// Used for binary file reading 
#include "Transformations.h"

namespace Aurora
{
	namespace Model
	{

int const StartOfData			= 10000;
int const BeginObject			= 11000;
int const StartVertexList		= 11010;
int const StartFaceList         = 11040;
int const EndOfObject			= 12000;
int const EndOfData				= 20000;


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
class Loader
{
	public:
		Loader();
		~Loader();

		/**
		 *
		 * \param *fileName 
		 * \param *model 
		 */
		void LoadModel(char *fileName, mMODEL4D *model);
		
	protected:
		/**
		 *
		 * \param &inA 
		 * \param *model 
		 */
		void LoadObjectData(std::ifstream &inA, mMODEL4D *model);

};
	}; // END OF NAMESPACE MODEL
}; // END OF NAMESPACE AURORA
#endif