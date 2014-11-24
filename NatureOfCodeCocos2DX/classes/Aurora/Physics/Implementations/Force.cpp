#include "Force.h"
namespace Aurora {
	namespace Physics {

void Force::init()
{
	this->acceleration = VECTOR2D::GetZeroVector();
	this->maximiunVelocity = 2;
	this->position = VECTOR2D::GetZeroVector();
	this->velocity = VECTOR2D::GetZeroVector();
}

void Force::init(const Force &value)
{
	this->acceleration = value.acceleration;
	this->maximiunVelocity = value.maximiunVelocity;
	this->position = value.position;
	this->velocity = value.velocity;
}

void Force::init(Force &&value)
{
	this->acceleration = std::move(value.acceleration);
	this->maximiunVelocity = std::move(value.maximiunVelocity);
	this->position = std::move(value.position);
	this->velocity = std::move(value.velocity);
}

Force::Force()
{
	this->init();
}

Force::Force(const Force &value) : IForceBase(value)
{
	this->init(value);
}

Force::Force(Force &&value) : IForceBase(std::move(value))
{
	this->init(std::move(value));
}

Force::~Force()
{
	IForceBase::~IForceBase();
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

void Force::applyForce(const VECTOR2D &value)
{
	this->acceleration += value;
}

void Force::Update()
{
	this->velocity += this->acceleration;
	this->velocity.Limit(maximiunVelocity);
	this->position += velocity;
	this->acceleration = VECTOR2D::GetZeroVector();
}


	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora