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

		const VECTOR2D  Mover::GetCurentTarget() const
		{
			return(this->target);
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

		void Mover::MoveTowardsTarget()
		{			
			Float choice = RandomNumberGenerator::GetRandomPositiveFloat(0, 1);
			VECTOR2D distanceBetweenTargetAndPosition = this->target - this->position;
			VECTOR2D normalizedDistancetweenTargetAndPosition = distanceBetweenTargetAndPosition;
			normalizedDistancetweenTargetAndPosition.Normalize();

			if (choice < this->probalitityFactor)
			{
				/*auto xdir = (this->target.X - this->position.X);
				auto ydir = (this->target.Y - this->position.Y);

				if (xdir != 0)
				{
					xdir /= abs(xdir);
				}

				if (ydir != 0)
				{
					ydir /= abs(ydir);
				}*/
				/*this->acceleration.X += xdir;
				this->acceleration.Y += ydir;*/
				this->acceleration = normalizedDistancetweenTargetAndPosition * 0.5f;
				CCLOG("Mover target - position Magnitude: %f", distanceBetweenTargetAndPosition.Magnitude());
				CCLOG("Mover target location X: %f Y: %f", this->target.X, this->target.Y);
				CCLOG("Mover position location X: %f Y: %f", this->position.X, this->position.Y);
				CCLOG("Mover distanceBetweenTargetAndPosition location X: %f Y: %f", distanceBetweenTargetAndPosition.X, distanceBetweenTargetAndPosition.Y);
				// Notice that if a targe is specified the mover must move towards that target untill it has reached it then only we can null the target and allow the mover to go on randomly
				if (this->MoveAutomatically && (distanceBetweenTargetAndPosition.Magnitude() <= 10))
				{
					this->target = VECTOR2D::GetZeroVector();
					CCLOG("Mover towards target has been reached. Automatic movement stopped!");
				}
				
				
			}
			else
			{
				this->acceleration.X += RandomNumberGenerator::GetRandomFloat(2);
				this->acceleration.Y += RandomNumberGenerator::GetRandomFloat(2);
			}
			
			if (!this->MoveAutomatically)
				this->target = VECTOR2D::GetZeroVector();

		}

		void Mover::DoCalculations()
		{
			RandomBaseComplete::DoCalculations();
			VECTOR2D emptyVector;
			if (this->target != emptyVector)
			{
				MoveTowardsTarget();
			}
		}

		void Mover::UniformCalculations()
		{
			RandomBaseComplete::UniformCalculations();
		}

		void Mover::GaussianCalculations()
		{
			RandomBaseComplete::GaussianCalculations();
		}

		void Mover::PerlinNoiseCalculations()
		{
			RandomBaseComplete::PerlinNoiseCalculations();
			auto tempX = this->PerlinNoiseCalculator->GetValue(this->perlinNoiseTime_PositionX.X, this->perlinNoiseTime_PositionX.Y, this->perlinNoiseTime_PositionX.Z);
			auto tempY = this->PerlinNoiseCalculator->GetValue(this->perlinNoiseTime_PositionY.X, this->perlinNoiseTime_PositionY.Y, this->perlinNoiseTime_PositionY.Z);

			/*if (tempX < 0)
			{
				tempX *= -1;
			}

			if (tempY < 0)
			{
				tempY *= -1;
			}*/

			this->perlinNoiseTime_PositionX += 0.1f;
			this->perlinNoiseTime_PositionY += 0.1f;


			this->acceleration = VECTOR2D(tempX, tempY);
			this->acceleration.Normalize();
			auto accelerationMultiple = RandomNumberGenerator::GetRandomPositiveFloat(3);
			this->acceleration *= accelerationMultiple;
		}

		void Mover::NormalCalculations()
		{
			RandomBaseComplete::NormalCalculations();
		}

		Mover::Mover(const mRECT &areaSize) : RandomBaseComplete()
		{
			this->SetConstrainsRange(areaSize);
			this->init();
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
			this->init();
		}

		Mover::Mover(Mover &&value) : RandomBaseComplete(std::move(value))
		{
			this->init(std::move(value));
		}

		Mover::~Mover()
		{
			IRandomBaseComplete::~IRandomBaseComplete();
		}

		void Mover::Accelerate()
		{
			//VECTOR2D emptyVector;
			/*if (this->target != emptyVector)
			{
				MoveTowardsTarget();
			}*/
			this->velocity += this->acceleration;
			this->velocity.Limit(this->maximiunVelocity);
			this->position += this->velocity;
		}

		void Mover::Decellerate()
		{
			/*VECTOR2D emptyVector;
			if (this->target != emptyVector)
			{
				MoveTowardsTarget();
			}*/
			this->velocity -= this->acceleration;
			this->velocity.Limit(this->maximiunVelocity);
			this->position -= this->velocity;
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

			/*this->position = std::move(value.position);
			this->probalitityFactor = std::move(value.probalitityFactor);
			
			this->target = std::move(value.target);
			this->velocity = std::move(value.velocity);
			this->acceleration = std::move(value.acceleration);
			this->maximiunVelocity = std::move(value.maximiunVelocity);
			this->minimumVelocity = std::move(value.minimumVelocity);*/
			this->init(std::move(value));

			return(*this);
		}

		void Mover::init()
		{
			this->probalitityFactor = 0.9f;
			this->perlinNoiseTime_PositionX = VECTOR3D(0, 0, 0);
			this->perlinNoiseTime_PositionY = VECTOR3D(10000, 10000, 10000);
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
			this->perlinNoiseTime_PositionX = value.perlinNoiseTime_PositionX;
			this->perlinNoiseTime_PositionY = value.perlinNoiseTime_PositionY;
		}

		void Mover::init(const Mover &&value)
		{
			this->SetConstrainsRange(value.GetConstrainsRange());
			//this->PerlinNoiseCalculator = value.PerlinNoiseCalculator;
			this->position = std::move(value.position);
			this->probalitityFactor = std::move(value.probalitityFactor);

			this->target = std::move(value.target);
			this->velocity = std::move(value.velocity);
			this->acceleration = std::move(value.acceleration);
			this->maximiunVelocity = std::move(value.maximiunVelocity);
			this->minimumVelocity = std::move(value.minimumVelocity);
			this->perlinNoiseTime_PositionX = std::move(value.perlinNoiseTime_PositionX);
			this->perlinNoiseTime_PositionY = std::move(value.perlinNoiseTime_PositionY);
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

			this->init();
		}

		void Mover::SetVelocityRange(const Float moverMaximumVelocity, const Float moverMinimumVelocity)
		{
			this->minimumVelocity = moverMinimumVelocity;
			this->maximiunVelocity = moverMaximumVelocity;
		}

		void Mover::SetPosition(const VECTOR2D &position)
		{
			this->position = position;
		}

		void IMover::Render()
		{

		}

		void IMover::MoveMover()
		{

		}

		
	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora