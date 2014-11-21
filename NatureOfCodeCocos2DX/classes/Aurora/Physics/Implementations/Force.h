#ifndef NatureOfCodeCocos2DX_Force_h
#define NatureOfCodeCocos2DX_Force_h


#include "../BaseClasses/ForceBase.h"

using namespace Aurora::Math;

namespace Aurora {
	namespace Physics {

		class Force : public IForceBase
		{
		protected:
			VECTOR2D position;
			VECTOR2D velocity;			
			VECTOR2D acceleration;
			Float maximiunVelocity;
			
		public:
			Force();
			virtual ~Force();
			Force(const Force &value);
			Force& operator=(const Force& value);
			Force(Force &&value);
			Force & operator=(Force && value);

			virtual void init() override;
			void applyForce(const VECTOR2D &value);

			VECTOR2D Position() const { return position; }
			void Position(const VECTOR2D &value) { position = value; }

			VECTOR2D Velocity() const { return velocity; }
			void Velocity(const VECTOR2D &value) { velocity = value; }

			VECTOR2D Acceleration() const { return acceleration; }
			void Acceleration(const VECTOR2D &value) { acceleration = value; }

			Aurora::DataTypes::Float MaximiunVelocity() const { return maximiunVelocity; }
			void MaximiunVelocity(const Aurora::DataTypes::Float &value) { maximiunVelocity = value; }

		};

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif