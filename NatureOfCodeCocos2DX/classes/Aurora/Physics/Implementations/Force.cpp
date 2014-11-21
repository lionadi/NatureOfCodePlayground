#include "Force.h"
namespace Aurora {
	namespace Physics {

void Force::init()
{
	throw std::logic_error("The method or operation is not implemented.");
}

Force::Force()
{

}

Force::Force(const Force &value)
{

}

Force::Force(Force &&value)
{

}

Force::~Force()
{

}

Force& Aurora::Physics::Force::operator=(const Force& value)
{
	return(*this);
}

Force & Aurora::Physics::Force::operator=(Force && value)
{
	return(*this);
}

void Aurora::Physics::Force::applyForce(const VECTOR2D &value)
{

}
	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora