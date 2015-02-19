#include "Force.h"
namespace Aurora {
	namespace Physics {

void Force::init()
{
	this->acceleration = VECTOR2D::GetZeroVector();
	this->maximiunVelocity = 2;
	this->mass = 10;
	this->position = VECTOR2D::GetZeroVector();
	this->velocity = VECTOR2D::GetZeroVector();
	this->normal = 1;
	this->frictionCoefficient = 0.01f;
	this->angle = 0;
	this->angularVelocity = 0;
	this->angularAcceleration = 0;
	this->minimumAngularVelocity = -0.5f;
	this->maximumAngularVelocity = 0.5f;
}

void Force::init(const Force &value)
{
	this->acceleration = value.acceleration;
	this->maximiunVelocity = value.maximiunVelocity;
	this->position = value.position;
	this->velocity = value.velocity;
	this->mass = value.mass;
	this->normal = value.normal;
	this->friction = value.friction;
	this->frictionCoefficient = value.frictionCoefficient;
	this->angle = value.angle;
	this->angularAcceleration = value.angularAcceleration;
	this->angularVelocity = value.angularVelocity;
	this->minimumAngularVelocity = value.minimumAngularVelocity;
	this->maximumAngularVelocity = value.maximumAngularVelocity;
}

void Force::init(Force &&value)
{
	this->acceleration = std::move(value.acceleration);
	this->maximiunVelocity = std::move(value.maximiunVelocity);
	this->position = std::move(value.position);
	this->velocity = std::move(value.velocity);
	this->mass = std::move(value.mass);
	this->normal = std::move(value.normal);
	this->friction = std::move(value.friction);
	this->frictionCoefficient = std::move(value.frictionCoefficient);
	this->angle = std::move(value.angle);
	this->angularAcceleration = std::move(value.angularAcceleration);
	this->angularVelocity = std::move(value.angularVelocity);
	this->minimumAngularVelocity = std::move(value.minimumAngularVelocity);
	this->maximumAngularVelocity = std::move(value.maximumAngularVelocity);
}

Force::Force()
{
	this->init();
}

Force::Force(const Force &value) : IPhysicsBase(value)
{
	this->init(value);
}

Force::Force(Force &&value) : IPhysicsBase(std::move(value))
{
	this->init(std::move(value));
}

Force::~Force()
{
	IPhysicsBase::~IPhysicsBase();
}

Force& Force::operator=(const Force& value)
{
	this->init(value);
	return(*this);
}

Force &Force::operator=(Force && value)
{
	this->init(std::move(value));
	return(*this);
}

void Force::ApplyForce(const VECTOR2D &value)
{
	this->acceleration += (value / this->mass);
	//this->acceleration += value;
}

void Force::Update()
{
	//this->ApplyForce(this->callbacks->call(PhysicsConstants::Callbacks_FrictionCalculations_FunctionName, ))
	this->velocity += this->acceleration;
	this->velocity.Limit(maximiunVelocity);
	this->position += velocity;
	this->acceleration = VECTOR2D::GetZeroVector();

	this->ConstrainToAreaSize();
}

void Force::ConstrainToAreaSize()
{
	if (position.X > this->areaSize.Width) {
		position.X = this->areaSize.Width;
		velocity.X *= -1;
	}
	else if (position.X < 0) {
		velocity.X *= -1;
		position.X = 0;
	}

	if (position.Y > this->areaSize.Height) {
		velocity.Y *= -1;
		position.Y = this->areaSize.Height;
	}
	else if (position.Y < 0) {
		velocity.Y *= -1;
		position.Y = 0;
	}
}

void Force::UpdateAngular()
{
	this->angularVelocity += angularAcceleration;
	this->angularVelocity += velocity.Heading();

	if (this->angularVelocity < this->minimumAngularVelocity)
		this->angularVelocity = this->minimumAngularVelocity;

	if (this->angularVelocity > this->maximumAngularVelocity)
		this->angularVelocity = this->maximumAngularVelocity;

	if (this->angularVelocity > 360)
		this->angularVelocity = 360;

	if (this->angularVelocity < -360)
		this->angularVelocity = -360;

	

	this->angle += angularVelocity;
}


	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora