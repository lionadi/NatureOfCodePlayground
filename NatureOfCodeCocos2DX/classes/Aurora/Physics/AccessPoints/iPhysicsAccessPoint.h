#ifndef NatureOfCodeCocos2DX_iPhysicsAccessPoint_h
#define NatureOfCodeCocos2DX_iPhysicsAccessPoint_h



#include "../Implementations/Force.h"
#include <functional>


namespace Aurora {
	namespace Physics {

		class IPhysicsAccessPoint
		{
		private:

		public:
			IPhysicsAccessPoint() = default;
			virtual ~IPhysicsAccessPoint() = default;

			virtual std::shared_ptr<Physics::Force> AccessObjectPhysics() const = 0;

		};



	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif