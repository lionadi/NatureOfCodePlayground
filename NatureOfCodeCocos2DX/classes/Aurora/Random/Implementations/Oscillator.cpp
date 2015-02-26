#include "Oscillator.h"

namespace Aurora {
	namespace Random {
		void Aurora::Random::Oscillator::DoCalculations()
		{
			this->Oscillate();
			this->ImplementorObjectPhysics()->Position(VECTOR2D(this->StartPosition().X + (sin(this->angle.X) * this->amplitude.X), this->StartPosition().Y + cos(this->angle.Y) * this->amplitude.Y));
		}

		Aurora::Random::Oscillator::Oscillator() : RandomBaseComplete()
		{
			this->init();
		}

		Aurora::Random::Oscillator::Oscillator(const Oscillator &value) : RandomBaseComplete(value), angle(value.angle), amplitude(value.amplitude), velocity(value.velocity)
		{
			this->ImplementorObjectPhysics(value.ImplementorObjectPhysics());
		}

		Aurora::Random::Oscillator::Oscillator(Oscillator &&value) : RandomBaseComplete(std::move(value)), angle(std::move(value.angle)), amplitude(std::move(value.amplitude)), velocity(std::move(value.velocity))
		{
			this->ImplementorObjectPhysics(std::move(value.ImplementorObjectPhysics()));
		}

		Aurora::Random::Oscillator::~Oscillator()
		{
			RandomBaseComplete::~RandomBaseComplete();
			IPhysicsImplementor::~IPhysicsImplementor();
		}

		Oscillator & Aurora::Random::Oscillator::operator=(Oscillator && value)
		{
			if (this == &value)
				return *this;

			this->init(std::move(value));

			return *this;
		}

		Oscillator& Aurora::Random::Oscillator::operator=(const Oscillator& value)
		{
			if (this == &value)
				return *this;

			this->init(value);

			return *this;
		}

		void Aurora::Random::IOscillatorImplementor::Render()
		{

		}

		std::shared_ptr<Aurora::Physics::Force> Aurora::Random::IOscillatorImplementor::AccessObjectPhysics() const
		{
			return nullptr;
		}

		void Oscillator::init()
		{
			this->angle = VECTOR2D::GetZeroVector();
			this->velocity = VECTOR2D(RandomNumberGenerator::GetRandomFloat(-0.05, 0.05), RandomNumberGenerator::GetRandomFloat(-0.05, 0.05));
			this->amplitude = VECTOR2D(RandomNumberGenerator::GetRandomFloat(this->GetConstrainsRange().Width / 2), RandomNumberGenerator::GetRandomFloat(this->GetConstrainsRange().Height / 2));
		}

		void Oscillator::init(const Oscillator & value)
		{
			this->angle = value.angle;
			this->amplitude = value.amplitude;
			this->velocity = value.velocity;
			this->ImplementorObjectPhysics(value.ImplementorObjectPhysics());
		}

		void Oscillator::init(Oscillator && value)
		{
			this->angle = std::move(value.angle);
			this->amplitude = std::move(value.amplitude);
			this->velocity = std::move(value.velocity);
			this->ImplementorObjectPhysics(std::move(value.ImplementorObjectPhysics()));
		}

		void Oscillator::Oscillate()
		{
			this->angle += velocity;
		}

		Oscillator::Oscillator(const mRECT &areaSize) : RandomBaseComplete()
		{
			this->SetConstrainsRange(areaSize);
			this->init();
		}

		

	}
}


