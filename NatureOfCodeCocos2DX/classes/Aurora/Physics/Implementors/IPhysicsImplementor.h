#ifndef NatureOfCodeCocos2DX_IPhysicsImplementor_h
#define NatureOfCodeCocos2DX_IPhysicsImplementor_h



#include "../Implementations/Force.h"
#include <functional>
#include <type_traits>


namespace Aurora {
	namespace Physics {

		/*!
		 * \class IPhysicsImplementor
		 *
		 * \brief Use this to set a connection to a objects physics data. With this connection you can communicate with the physics data.
		 *
		 * \author Adrian Simionescu
		 * \date February 2015
		 */
		class IPhysicsImplementor
		{
			private:
				std::shared_ptr<Physics::Force> objectPhysics;
			
		public:
			IPhysicsImplementor() = default;
			virtual ~IPhysicsImplementor() = default;

			std::shared_ptr<Physics::Force> ImplementorObjectPhysics() const {
				if (this->objectPhysics == nullptr)
					throw std::bad_function_call(Aurora::Errors::ErrorMessages::PhysicsForceEmptyObject.c_str());

				return objectPhysics;
			}

			template<typename T>
			void ImplementorObjectPhysics(T &&value) { 
				//static_assert(!is_same<objectPhysics, T>::value, Aurora::Errors::ErrorMessages::TypeMismatch.c_str());
				objectPhysics = std::forward<T>(value); 
			}
			
		};



	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif