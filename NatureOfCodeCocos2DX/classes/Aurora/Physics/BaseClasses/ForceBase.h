#ifndef NatureOfCodeCocos2DX_ForceBase_h
#define NatureOfCodeCocos2DX_ForceBase_h



#include "..\..\Math\MathOperations.h"


namespace Aurora {
	namespace Physics {

		class IForceBase 
		{
		protected:

		public:
			IForceBase() = default;
			virtual ~IForceBase() = default;
			virtual void init() = 0;

			

		};

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif