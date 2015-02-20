#ifndef NatureOfCodeCocos2DX_Oscillator_h
#define NatureOfCodeCocos2DX_Oscillator_h

#include "..\BaseClasses\ObjectBase.h"
#include "..\..\Math\MathOperations.h"
#include "..\..\Physics\PhysicsOperations.h"


using namespace Aurora::Math;
using namespace Aurora::Physics;

namespace Aurora {
	namespace Random {
		class Oscillator : public RandomBaseComplete, public IPhysicsImplementor
		{
			private:
				VECTOR2D angle;
				VECTOR2D velocity;
				VECTOR2D amplitude;
				
			public:
				Oscillator();
				virtual ~Oscillator();
				Oscillator(const Oscillator &value);
				Oscillator(Oscillator &&value);
				Oscillator &operator=(Oscillator && value);
				Oscillator& operator=(const Oscillator& value);


				Aurora::Math::VECTOR2D Angle() const {
					return angle;
				}
				template<typename T>
				void Angle(T &&value) { angle = std::forward<T>(value); }

				Aurora::Math::VECTOR2D Velocity() const {
					return velocity;
				}
				template<typename T>
				void Velocity(T &&value) { velocity = std::forward<T>(value); }

				Aurora::Math::VECTOR2D Amplitude() const {
					return amplitude;
				}
				template<typename T>
				void Amplitude(T &&value) { amplitude = std::forward<T>(value); }

				virtual void DoCalculations() override;

				virtual void init() override;
				void init(const Oscillator &&value);
				void init(const Oscillator &value);

				void Oscillate();

		};

		class IOscillatorImplementor : public IObjectBaseBasic, public IPhysicsAccessPoint
		{
			public:
				IOscillatorImplementor() = default;
				virtual ~IOscillatorImplementor() = default;

				virtual void Render() override;

				virtual std::shared_ptr<Physics::Force> AccessObjectPhysics() const override;

		};

	};
}
#endif