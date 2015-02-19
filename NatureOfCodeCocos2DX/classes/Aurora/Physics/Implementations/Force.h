#ifndef NatureOfCodeCocos2DX_Force_h
#define NatureOfCodeCocos2DX_Force_h


#include "../BaseClasses/PhysicsBase.h"

using namespace Aurora::Math;

namespace Aurora {
	namespace Physics {
		

		class Force : public IPhysicsBase
		{
		protected:

			VECTOR2D velocity;
			
			VECTOR2D acceleration;

			VECTOR2D friction;
			
			Float frictionCoefficient;
			
			Float maximiunVelocity;

			Float normal;

			Float angularVelocity;
			

			Float angularAcceleration;
			
			Float angle;

			Float minimumAngularVelocity;
			
			Float maximumAngularVelocity;

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
			
			Aurora::DataTypes::Float Normal() const { return normal; }
			template<typename T>
			void Normal(T &&value) { normal = std::forward<T>(value); }

			Aurora::DataTypes::Float AngularVelocity() const { return angularVelocity; }
			template<typename T>
			void AngularVelocity(T &&value) { angularVelocity = std::forward<T>(value); }

			Aurora::DataTypes::Float AngularAcceleration() const { return angularAcceleration; }
			template<typename T>
			void AngularAcceleration(T &&value) { angularAcceleration = std::forward<T>(value); }

			Aurora::DataTypes::Float Angle() const { return angle; }
			template<typename T>
			void Angle(T &&value) { angle = std::forward<T>(value); }

			cocos2d::Float MinimumAngularVelocity() const {
				return minimumAngularVelocity;
			}
			template<typename T>
			void MinimumAngularVelocity(T &&value) { minimumAngularVelocity = std::forward<T>(value); }

			cocos2d::Float MaximumAngularVelocity() const {
				return maximumAngularVelocity;
			}
			template<typename T>
			void MaximumAngularVelocity(T &&value) { maximumAngularVelocity = std::forward<T>(value); }


			
#pragma endregion Encapsulated Properties

			void ApplyForce(const VECTOR2D &value);
			
			void Update();

			void UpdateAngular();
			
			
			
		};

		using ForceAlias = std::shared_ptr < Force >;

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora


#endif