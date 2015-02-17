#include "IPhysicsForceRepresentationBase.h"

namespace Aurora {
	namespace Physics {

		Aurora::Physics::IPhysicsForceRepresentationBase::IPhysicsForceRepresentationBase()
		{
			this->init();
		}

		Aurora::Physics::IPhysicsForceRepresentationBase::IPhysicsForceRepresentationBase(const IPhysicsForceRepresentationBase &value) : objectPhysics(value.objectPhysics)
		{
			this->init();
		}

		Aurora::Physics::IPhysicsForceRepresentationBase::IPhysicsForceRepresentationBase(IPhysicsForceRepresentationBase &&value) : objectPhysics(std::move(value.objectPhysics))
		{
			value.objectPhysics = nullptr;
		}

		Aurora::Physics::IPhysicsForceRepresentationBase::~IPhysicsForceRepresentationBase()
		{

		}

		IPhysicsForceRepresentationBase &Aurora::Physics::IPhysicsForceRepresentationBase::operator=(IPhysicsForceRepresentationBase && value)
		{
			if (this == &value)
				return *this;

			this->objectPhysics = std::move(value.objectPhysics);

			value.objectPhysics = nullptr;

			return *this;
		}

		void Aurora::Physics::IPhysicsForceRepresentationBase::init()
		{
			this->objectPhysics = std::make_shared<Physics::Force>();
		}

		IPhysicsForceRepresentationBase& IPhysicsForceRepresentationBase::operator=(const IPhysicsForceRepresentationBase& value)
		{
			if (this == &value) { return(*this); }
			this->init(value);

			return *this;
		}

		void IPhysicsForceRepresentationBase::init(const IPhysicsForceRepresentationBase &value)
		{
			this->objectPhysics = value.objectPhysics;
		}

	}
}
