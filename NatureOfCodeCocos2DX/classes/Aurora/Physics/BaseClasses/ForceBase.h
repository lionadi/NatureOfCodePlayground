#ifndef NatureOfCodeCocos2DX_ForceBase_h
#define NatureOfCodeCocos2DX_ForceBase_h



#include "..\..\Math\MathOperations.h"

using namespace Aurora::Math;

namespace Aurora {
	namespace Physics {

		
		class IPhysicsBase 
		{
		protected:
			mRECT areaSize;

			
			
		public:
			IPhysicsBase() = default;
			virtual ~IPhysicsBase() = default;
			virtual void init() = 0;
			
			Aurora::Math::mRECT AreaSize() const { return areaSize; }
			void AreaSize(const Aurora::Math::mRECT &value) { areaSize = value; }
			void AreaSize(Aurora::Math::mRECT &&value) { areaSize = std::move(value); }

		};

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif