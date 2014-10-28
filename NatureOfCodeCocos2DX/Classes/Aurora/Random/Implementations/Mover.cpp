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

		Mover::~Mover()
		{
			PRandomBaseComplete::~PRandomBaseComplete();
		}

		void Mover::Accelerate() const
		{
			this->velocity += this->acceleration;
			this->velocity.Limit(this->minimumVelocity, this->maximiunVelocity);
			this->position += this->velocity;
		}

		void Mover::Decellerate() const
		{
			this->velocity = 2 * this->acceleration;
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

		void Mover::init()
		{
			this->probalitityFactor = 0.5f;
		}

		void Mover::init(const Mover &value)
		{
			this->areaSize = value.areaSize;
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


		PMover::PMover(const mRECT &areaSize) : PObjectBaseBasic(), MoverObject(areaSize)
		{
			this->init(areaSize);
		}

		PMover::PMover(const PMover &value) : PObjectBaseBasic(value), MoverObject(value.MoverObject)
		{
			
		}

		PMover::PMover() : PObjectBaseBasic()
		{
			this->init();
		}


		PMover::~PMover()
		{
			PObjectBaseBasic::~PObjectBaseBasic();
		}

		void PMover::Render()
		{

		}

		PMover& PMover::operator=(const PMover& value)
		{
			if(this == &value) { return(*this); }

			PObjectBaseBasic::operator=(value);
			// Do Other initializations
			this->init(value);

			return(*this);
		}

		void PMover::init()
		{
			PObjectBaseBasic::init();
		}

		void PMover::init(const mRECT &areaSize)
		{
			PObjectBaseBasic::init(this->GetRandomNumberMode());
			this->MoverObject.SetConstrainsRange(areaSize);
		}

		void PMover::init(const PMover &value)
		{
			PObjectBaseBasic::init(value.GetRandomNumberMode());
			this->MoverObject = value.MoverObject;
			this->SetRandomNumberMode(value.GetRandomNumberMode());
		}

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora