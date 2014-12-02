#include "Mover.h"

namespace Aurora {
	namespace Random {

		void Mover::Accelerate()
		{
			this->objectPhysics->Update();
			//VECTOR2D emptyVector;
			/*if (this->target != emptyVector)
			{
			MoveTowardsTarget();
			}*/
			/*this->velocity += this->acceleration;
			this->velocity.Limit(this->maximiunVelocity);
			this->position += this->velocity;*/
		}

		void Mover::Decellerate()
		{
			this->objectPhysics->Update();
			/*VECTOR2D emptyVector;
			if (this->target != emptyVector)
			{
			MoveTowardsTarget();
			}*/
			/*this->velocity -= this->acceleration;
			this->velocity.Limit(this->maximiunVelocity);
			this->position -= this->velocity;*/
		}

		void Mover::SetTarget(const VECTOR2D &target)
		{
			this->target = target;
		}

		const VECTOR2D Mover::GetCurentPosition() const
		{
			return(this->objectPhysics->Position());
		}

		const VECTOR2D  Mover::GetCurentTarget() const
		{
			return(this->target);
		}

		void Mover::Constrain()
		{
			if (this->objectPhysics->Position().X > this->GetConstrainsRange().Width) {
				this->objectPhysics->Position(VECTOR2D(0, this->objectPhysics->Position().Y));
			}
			else if (this->objectPhysics->Position().X < 0) {
				this->objectPhysics->Position(VECTOR2D(this->GetConstrainsRange().Width, this->objectPhysics->Position().Y));
			}

			if (this->objectPhysics->Position().Y > this->GetConstrainsRange().Height) {
				this->objectPhysics->Position(VECTOR2D(this->objectPhysics->Position().X, 0));
			}
			else if (this->objectPhysics->Position().Y < 0) {
				this->objectPhysics->Position(VECTOR2D(this->objectPhysics->Position().X, this->GetConstrainsRange().Height));
			}
		}

		void Mover::MoveTowardsTarget()
		{			
			Float choice = RandomNumberGenerator::GetRandomPositiveFloat(0, 1);
			VECTOR2D distanceBetweenTargetAndPosition = this->target - this->objectPhysics->Position();
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
				
				this->objectPhysics->ApplyForce(normalizedDistancetweenTargetAndPosition * 0.5f);
				CCLOG("Mover target - Address: %X", this);
				CCLOG("Mover target - position Magnitude: %f", distanceBetweenTargetAndPosition.Magnitude());
				CCLOG("Mover target location X: %f Y: %f", this->target.X, this->target.Y);
				CCLOG("Mover position location X: %f Y: %f", this->objectPhysics->Position().X, this->objectPhysics->Position().Y);
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
				this->objectPhysics->Acceleration(VECTOR2D(RandomNumberGenerator::GetRandomFloat(2), RandomNumberGenerator::GetRandomFloat(2)));
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
			// TO BE REMOVED TEST PURPOSES: Adds wind simulation
			
			//std::shared_ptr<CommonCalculations> cc = CommonCalculations::GetInstance();
			PhysicsCalculatorAlias physicsCalculator = PhysicsCalculator::GetInstance()->GetPhysicsCalculatorOption(PhysicsCalculationMode::Normal);
			physicsCalculator->PerformCalculationsOnForce(this->objectPhysics);
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


			this->objectPhysics->Acceleration(VECTOR2D(tempX, tempY));
			//this->moverPhysic->Acceleration(this->moverPhysic->Acceleration().Normalize());
			
			this->objectPhysics->Acceleration().Normalize();
			auto accelerationMultiple = RandomNumberGenerator::GetRandomPositiveFloat(3);
			this->objectPhysics->Acceleration(this->objectPhysics->Acceleration() * accelerationMultiple);
		}

		void Mover::NormalCalculations()
		{
			RandomBaseComplete::NormalCalculations();
		}

		Mover::Mover(const mRECT &areaSize) : RandomBaseComplete()
		{
			this->SetConstrainsRange(areaSize);
			this->init();
			this->objectPhysics->AreaSize(areaSize);
		}

		Mover::Mover(const VECTOR2D &position, const VECTOR2D &velocity, const mRECT &areaSize) : RandomBaseComplete()
		{
			this->init(position, velocity, VECTOR2D::GetZeroVector(), areaSize, 1);
		}

		Mover::Mover(const VECTOR2D &position, const VECTOR2D &velocity, const VECTOR2D &acceleration, const mRECT &areaSize, const float &mass) : RandomBaseComplete()
		{
			this->init(position, velocity, acceleration, areaSize, mass);
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
			this->objectPhysics = std::make_shared<Physics::Force>();
		}

		void Mover::init(const Mover &value)
		{
			this->SetConstrainsRange(value.GetConstrainsRange());
			this->objectPhysics->AreaSize(value.GetConstrainsRange());
			//this->PerlinNoiseCalculator = value.PerlinNoiseCalculator;
			this->objectPhysics = value.objectPhysics;
			this->probalitityFactor = value.probalitityFactor;
			this->SetRandomNumberMode(value.GetRandomNumberMode());
			this->target = value.target;

			this->perlinNoiseTime_PositionX = value.perlinNoiseTime_PositionX;
			this->perlinNoiseTime_PositionY = value.perlinNoiseTime_PositionY;
		}

		void Mover::init(const Mover &&value)
		{
			this->SetConstrainsRange(value.GetConstrainsRange());
			//this->PerlinNoiseCalculator = value.PerlinNoiseCalculator;
			this->objectPhysics = std::move(value.objectPhysics);
			this->probalitityFactor = std::move(value.probalitityFactor);
			this->target = std::move(value.target);
			this->perlinNoiseTime_PositionX = std::move(value.perlinNoiseTime_PositionX);
			this->perlinNoiseTime_PositionY = std::move(value.perlinNoiseTime_PositionY);
		}

		void Mover::init(const VECTOR2D &position, const VECTOR2D &velocity, const VECTOR2D &acceleration, const mRECT &areaSize, const float &mass)
		{
			this->init();

			if (!areaSize.IsZero())
			{
				this->SetConstrainsRange(areaSize);
				this->objectPhysics->AreaSize(areaSize);
			}

			if(!position.IsZero())
				this->objectPhysics->Position(position);

			if(!velocity.IsZero())
				this->objectPhysics->Velocity(velocity);

			if(!acceleration.IsZero())
				this->objectPhysics->Acceleration(acceleration);

			this->objectPhysics->Mass(mass);
		}

		void Mover::SetVelocityRange(const Float moverMaximumVelocity, const Float moverMinimumVelocity)
		{
			this->objectPhysics->MaximiunVelocity(moverMaximumVelocity);
		}

		void Mover::SetPosition(const VECTOR2D &position)
		{
			this->objectPhysics->Position(position);
		}

		const float Mover::GetMoverMass() const
		{
			return(this->objectPhysics->Mass());
		}

		void IMover::Render()
		{

		}

		void IMover::MoveMover()
		{

		}

		
	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora