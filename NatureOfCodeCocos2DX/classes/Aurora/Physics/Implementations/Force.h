#ifndef NatureOfCodeCocos2DX_Force_h
#define NatureOfCodeCocos2DX_Force_h


#include "../BaseClasses/PhysicsBase.h"

using namespace Aurora::Math;

namespace Aurora {
	namespace Physics {

		class Force : public IPhysicsBase
		{
		protected:
			VECTOR2D position;
			

			VECTOR2D velocity;
			
			VECTOR2D acceleration;

			VECTOR2D friction;
			
			Float frictionCoefficient;
			
			Float maximiunVelocity;

			Float mass;

			Float normal;
			

			void ConstrainToAreaSize();

			void CalculateFriction();

			

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
			template<typename T>
			void Position(T &&value) { position = std::forward<T>(value); }

			Aurora::Math::VECTOR2D Velocity() const { return velocity; }
			template<typename T>
			void Velocity(T &&value) { velocity = std::forward<T>(value); }

			Aurora::Math::VECTOR2D Acceleration() const { return acceleration; }
			template<typename T>
			void Acceleration(T &&value) { acceleration = std::forward<T>(value); }
			
			Aurora::Math::VECTOR2D Friction() const { return friction; }
			template<typename T>
			void Friction(T &&value) { friction = std::forward<T>(value); }

			
			Aurora::DataTypes::Float FrictionCoefficient() const { return frictionCoefficient; }
			template<typename T>
			void FrictionCoefficient(T &&value) { frictionCoefficient = std::forward<T>(value); }

			
			Aurora::DataTypes::Float MaximiunVelocity() const { return maximiunVelocity; }
			template<typename T>
			void MaximiunVelocity(T &&value) { maximiunVelocity = std::forward<T>(value); }
			
			Aurora::DataTypes::Float Mass() const { return mass; }
			template<typename T>
			void Mass(T &&value) { mass = std::forward<T>(value); }
			
			Aurora::DataTypes::Float Normal() const { return normal; }
			template<typename T>
			void Normal(T &&value) { normal = std::forward<T>(value); }
			
#pragma endregion Encapsulated Properties

			void ApplyForce(const VECTOR2D &value);
			
			void Update();
			
			
			
		};

		

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif