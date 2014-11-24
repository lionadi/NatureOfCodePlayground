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

#pragma region Initializations and Constructs
			Force();
			virtual ~Force();
			Force(const Force &value);
			Force& operator=(const Force& value);
			Force(Force &&value);
			Force & operator=(Force && value);

			virtual void init() override;
			virtual void init(const Force &value);
			virtual void init(Force &&value);
#pragma endregion Initializations and Constructs

#pragma region Encapsulated Properties

			Aurora::Math::VECTOR2D Position() const { return position; }
			void Position(const Aurora::Math::VECTOR2D &value) { position = value; }
			void Position(Aurora::Math::VECTOR2D &&value) { position = std::move(value); }


			Aurora::Math::VECTOR2D Velocity() const { return velocity; }
			void Velocity(const Aurora::Math::VECTOR2D &value) { velocity = value; }
			void Velocity(Aurora::Math::VECTOR2D &&value) { velocity = std::move(value); }


			Aurora::Math::VECTOR2D Acceleration() const { return acceleration; }
			void Acceleration(const Aurora::Math::VECTOR2D &value) { acceleration = value; }
			void Acceleration(Aurora::Math::VECTOR2D &&value) { acceleration = std::move(value); }


			Aurora::DataTypes::Float MaximiunVelocity() const { return maximiunVelocity; }
			void MaximiunVelocity(const Aurora::DataTypes::Float &value) { maximiunVelocity = value; }
			void MaximiunVelocity(Aurora::DataTypes::Float &&value) { maximiunVelocity = std::move(value); }
#pragma endregion Encapsulated Properties

			void applyForce(const VECTOR2D &value);
			
			void Update();
		};

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif