#include "Mover.h"

namespace Aurora {
	namespace Random {



		void Mover::SetTarget(const VECTOR2D &target)
		{
			this->target = target;
		}

		Aurora::Math::VECTOR2D Mover::GetCurentPosition()
		{
			return(this->position);
		}

		void Mover::Constrain()
		{
			if (this->position.X > this->areaSize.Width) {
				this->position.X = 0;
			} else if (this->position.X < 0) {
				this->position.X = this->areaSize.Width;
			}

			if (this->position.Y > this->areaSize.Height) {
				this->position.Y = 0;
			} else if (this->position.Y < 0) {
				this->position.Y = this->areaSize.Height;
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

		}

		Mover::Mover(const mRECT &areaSize) : PRandomBaseComplete()
		{
			this->SetConstrainsRange(areaSize);
		}

		Mover::Mover(const VECTOR2D &position, const VECTOR2D &velocity, const mRECT &areaSize)
		{
			Mover::Mover(areaSize);
			this->position = position;
			this->velocity = velocity;
		}

		Mover::Mover(const VECTOR2D &position, const VECTOR2D &velocity, const VECTOR2D &acceleration, const mRECT &areaSize)
		{
			Mover::Mover(position, velocity, areaSize);
			this->acceleration = acceleration;
		}

		Mover::~Mover()
		{
			PRandomBaseComplete::~PRandomBaseComplete();
		}

		void Mover::Accelerate()
		{
			this->velocity += this->acceleration;
			this->velocity.Limit(this->minimumVelocity, this->maximiunVelocity);
			this->position += this->velocity;
		}

		void Mover::Decellerate()
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


		PMover::PMover(const mRECT &areaSize) : PObjectBaseBasic(), MoverObject(areaSize)
		{

		}

		PMover::~PMover()
		{
			PObjectBaseBasic::~PObjectBaseBasic();
		}

		void PMover::Render()
		{

		}

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora