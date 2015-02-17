#ifndef NatureOfCodeCocos2DX_IPhysicsImplementor_h
#define NatureOfCodeCocos2DX_IPhysicsImplementor_h



#include "../Implementations/Force.h"
#include <functional>


namespace Aurora {
	namespace Physics {

		class IPhysicsImplementor
		{
			private:
				std::shared_ptr<Physics::Force> objectPhysics;
			
		public:
			IPhysicsImplementor() = default;
			virtual ~IPhysicsImplementor() = default;

			std::shared_ptr<Physics::Force> ImplementorObjectPhysics() const {
				if (this->objectPhysics == nullptr)
					throw std::bad_function_call("The physics force object is empty you can not use this functionality. Please pass a force object before usage.");

				return objectPhysics;
			}

			template<typename T>
			void ImplementorObjectPhysics(T &&value) { objectPhysics = std::forward<T>(value); }
			
		};



	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif