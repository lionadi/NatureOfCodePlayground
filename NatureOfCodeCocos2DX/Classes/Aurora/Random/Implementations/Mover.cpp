#include "Mover.h"

namespace Aurora {
	namespace Random {



		void Mover::SetTarget(const VECTOR2D &target)
		{
			this->target = target;
		}

		const VECTOR2D Mover::GetCurentPosition() const
		{
			return(this->position);
		}

		void Mover::Constrain()
		{
			if (this->position.X > this->GetConstrainsRange().Width) {
				this->position.X = 0;
			} else if (this->position.X < 0) {
				this->position.X = this->GetConstrainsRange().Width;
			}

			if (this->position.Y > this->GetConstrainsRange().Height) {
				this->position.Y = 0;
			} else if (this->position.Y < 0) {
				this->position.Y = this->GetConstrainsRange().Height;
			}
		}

		void Mover::UniformCalculations()
		{

		}

		void Mover::GaussianCalculations()
		{

		}

		void Mover::PerlinNoiseCalculations()
		{

		}

		void Mover::NormalCalculations()
		{
			this->Accelerate();
		}

		Mover::Mover(const mRECT &areaSize) : RandomBaseComplete()
		{
			this->SetConstrainsRange(areaSize);
		}

		Mover::Mover(const VECTOR2D &position, const VECTOR2D &velocity, const mRECT &areaSize) : RandomBaseComplete()
		{
			this->init(position, velocity, VECTOR2D::GetZeroVector(), areaSize);
		}

		Mover::Mover(const VECTOR2D &position, const VECTOR2D &velocity, const VECTOR2D &acceleration, const mRECT &areaSize) : RandomBaseComplete()
		{
			this->init(position, velocity, acceleration, areaSize);
		}

		Mover::Mover(const Mover &value) : RandomBaseComplete(value)
		{
			this->init(value);
		}

		Mover::Mover() : RandomBaseComplete()
		{

		}

		Mover::Mover(Mover &&value) : RandomBaseComplete(std::move(value))
		{

		}

		Mover::~Mover()
		{
			IRandomBaseComplete::~IRandomBaseComplete();
		}

		void Mover::Accelerate() const
		{
			this->velocity += this->acceleration;
			this->velocity.Limit(this->minimumVelocity, this->maximiunVelocity);
			this->position += this->velocity;
		}

		void Mover::Decellerate() const
		{
			this->velocity -= this->acceleration;
			this->velocity.Limit(this->minimumVelocity, this->maximiunVelocity);
			this->position -= this->velocity;
		}

		void Mover::SetVelocityRange(const Float &maximumVelocity, const Float &minimumVelocity)
		{
			this->minimumVelocity = minimumVelocity;
			this->maximiunVelocity = maximiunVelocity;
		}

		Mover& Mover::operator=(const Mover& value)
		{
			if(this == &value) { return(*this); }

			RandomBaseComplete::operator=(value);
			this->init(value);

			return(*this);
		}

		Mover & Mover::operator=(Mover && value)
		{
			RandomBaseComplete::operator=(std::move(value));

			this->position = std::move(value.position);
			this->probalitityFactor = std::move(value.probalitityFactor);
			
			this->target = std::move(value.target);
			this->velocity = std::move(value.velocity);
			this->acceleration = std::move(value.acceleration);
			this->maximiunVelocity = std::move(value.maximiunVelocity);
			this->minimumVelocity = std::move(value.minimumVelocity);

			return(*this);
		}

		void Mover::init()
		{
			this->probalitityFactor = 0.5f;
		}

		void Mover::init(const Mover &value)
		{
			this->SetConstrainsRange(value.GetConstrainsRange());
			//this->PerlinNoiseCalculator = value.PerlinNoiseCalculator;
			this->position = value.position;
			this->probalitityFactor = value.probalitityFactor;
			this->SetRandomNumberMode(value.GetRandomNumberMode());
			this->target = value.target;
			this->velocity = value.velocity;
			this->acceleration = value.acceleration;
			this->maximiunVelocity = value.maximiunVelocity;
			this->minimumVelocity = value.minimumVelocity;
		}

		void Mover::init(const VECTOR2D &position, const VECTOR2D &velocity, const VECTOR2D &acceleration, const mRECT &areaSize)
		{
			if(!areaSize.IsZero())
				this->SetConstrainsRange(areaSize);

			if(!position.IsZero())
				this->position = position;

			if(!velocity.IsZero())
				this->velocity = velocity;

			if(!acceleration.IsZero())
				this->acceleration = acceleration;
		}

		void IMover::Render()
		{

		}

		void IMover::MoveMover()
		{

		}

		
	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora