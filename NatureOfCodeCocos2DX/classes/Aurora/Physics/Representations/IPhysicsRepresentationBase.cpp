#include "IPhysicsRepresentationBase.h"

namespace Aurora {
	namespace Physics {


		


		IPhysicsRepresentationBase::IPhysicsRepresentationBase() : IPhysicsBase()
		{
			this->init();
		}

		IPhysicsRepresentationBase::~IPhysicsRepresentationBase()
		{
			IPhysicsBase::~IPhysicsBase();
		}


	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora