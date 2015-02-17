#ifndef NatureOfCodeCocos2DX_IPhysicsForceRepresentationBase_h
#define NatureOfCodeCocos2DX_IPhysicsForceRepresentationBase_h



#include "../Implementations/Force.h"


namespace Aurora {
	namespace Physics {


		class IPhysicsForceRepresentationBase
		{
			private:
			std::shared_ptr<Physics::Force> objectPhysics;
			void init();
			void init(const IPhysicsForceRepresentationBase &value);
		public:
#pragma region Constructors and Assigments operators
			IPhysicsForceRepresentationBase();
			virtual ~IPhysicsForceRepresentationBase();
			IPhysicsForceRepresentationBase(const IPhysicsForceRepresentationBase &value);
			IPhysicsForceRepresentationBase(IPhysicsForceRepresentationBase &&value);
			IPhysicsForceRepresentationBase &operator=(IPhysicsForceRepresentationBase && value);
			IPhysicsForceRepresentationBase& operator=(const IPhysicsForceRepresentationBase& value);
#pragma endregion

			

			std::shared_ptr<Physics::Force> ObjectPhysics() const { 
				if (this->objectPhysics == nullptr)
					throw std::bad_function_call("The physics force object is empty you can not use this functionality. Please pass a force object before usage.");

				return objectPhysics; 
			}

			template<typename T>
			void ObjectPhysics(T &&value) { objectPhysics = std::forward<T>(value); }



		};



	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif