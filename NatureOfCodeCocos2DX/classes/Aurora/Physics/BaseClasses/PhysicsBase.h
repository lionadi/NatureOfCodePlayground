#ifndef NatureOfCodeCocos2DX_ForceBase_h
#define NatureOfCodeCocos2DX_ForceBase_h



#include "..\..\Math\MathOperations.h"
#include "CalculationsBase.h"

using namespace Aurora::Math;

namespace Aurora {
	namespace Physics {

		
		class IPhysicsBase 
		{
		protected:
			mRECT areaSize;
			VECTOR2D position;
			Float mass;
			
		public:
			IPhysicsBase() = default;
			virtual ~IPhysicsBase() = default;
			virtual void init() = 0;
			
			Aurora::Math::mRECT AreaSize() const { return areaSize; }
			template<typename T>
			void AreaSize(T &&value) { areaSize = std::forward<T>(value); }

			Aurora::Math::VECTOR2D Position() const { return position; }
			template<typename T>
			void Position(T &&value) { position = std::forward<T>(value); }

			Aurora::DataTypes::Float Mass() const { return mass; }
			template<typename T>
			void Mass(T &&value) { mass = std::forward<T>(value); }
		};

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif