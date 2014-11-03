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


		IMover::IMover(const mRECT &areaSize) : IObjectBaseBasic(), MoverObject(areaSize)
		{
			this->init(areaSize);
		}

		IMover::IMover(const IMover &value) : IObjectBaseBasic(value), MoverObject(value.MoverObject)
		{
			
		}

		IMover::IMover() : IObjectBaseBasic()
		{
			this->init();
		}


		IMover::~IMover()
		{
			IObjectBaseBasic::~IObjectBaseBasic();
		}

		void IMover::Render()
		{

		}

		IMover& IMover::operator=(const IMover& value)
		{
			if(this == &value) { return(*this); }

			IObjectBaseBasic::operator=(value);
			// Do Other initializations
			this->init(value);

			return(*this);
		}

		void IMover::init()
		{
			IObjectBaseBasic::init();
		}

		void IMover::init(const mRECT &areaSize)
		{
			IObjectBaseBasic::init(this->GetRandomNumberMode());
			this->MoverObject.SetConstrainsRange(areaSize);
		}

		void IMover::init(const IMover &value)
		{
			IObjectBaseBasic::init(value.GetRandomNumberMode());
			this->MoverObject = value.MoverObject;
			this->SetRandomNumberMode(value.GetRandomNumberMode());
		}

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora