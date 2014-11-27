#ifndef NatureOfCodeCocos2DX_CalculationsBase_h
#define NatureOfCodeCocos2DX_CalculationsBase_h



#include "..\..\Math\MathOperations.h"

using namespace Aurora::Math;

namespace Aurora {
	namespace Physics {


		class ICalculationsBase
		{
		protected:
			

		public:
			ICalculationsBase() = default;
			virtual ~ICalculationsBase() = default;
			virtual void init() = 0;
			std::shared_ptr<Global::Callbacks> Calculations;
			
			
		};

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif