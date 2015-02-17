#include "IPhysicsRepresentationBase.h"

namespace Aurora {
	namespace Physics {


		


		IPhysicsRepresentationBase::IPhysicsRepresentationBase() : IPhysicsBase()
		{
			this->init();
		}

		IPhysicsRepresentationBase::IPhysicsRepresentationBase(const IPhysicsRepresentationBase &value) : IPhysicsBase()
		{
			this->objectPhysics = value.objectPhysics;
		}

		IPhysicsRepresentationBase::IPhysicsRepresentationBase(IPhysicsRepresentationBase &&value) : IPhysicsBase(), objectPhysics(std::move(value.objectPhysics))
		{
			value.objectPhysics = nullptr;
		}

		IPhysicsRepresentationBase::~IPhysicsRepresentationBase()
		{
			IPhysicsBase::~IPhysicsBase();
		}

		IPhysicsRepresentationBase & IPhysicsRepresentationBase::operator=(IPhysicsRepresentationBase && value)
		{
			if (this == &value)
				return *this;

			this->objectPhysics = std::move(value.objectPhysics);

			value.objectPhysics = nullptr;

			return *this;
		}

		IPhysicsRepresentationBase& IPhysicsRepresentationBase::operator=(const IPhysicsRepresentationBase& value)
		{
			if (this == &value) { return(*this); }

			this->objectPhysics = value.objectPhysics;

			return *this;
		}


	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora