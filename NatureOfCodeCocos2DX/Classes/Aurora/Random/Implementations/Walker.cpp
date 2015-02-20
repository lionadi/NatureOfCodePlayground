#include "Walker.h"

namespace Aurora {
	namespace Random {

		void Walker::Constrain()
		{
			RandomBaseComplete::Constrain();
			if(this->position.X < 0)
			{
				this->position.X = 0;
			}
			if(this->position.X > this->GetConstrainsRange().Width)
			{
				this->position.X = this->GetConstrainsRange().Width;
			}
			if(this->position.Y < 0)
			{
				this->position.Y = 0;
			}

			if(this->position.Y > this->GetConstrainsRange().Height)
			{
				this->position.Y = this->GetConstrainsRange().Height;
			}
		}

		void Walker::UniformCalculations()
		{
			RandomBaseComplete::UniformCalculations();
			VECTOR2D emptyVector;

			if(this->target == emptyVector)
			{
				auto choice = static_cast<int>(RandomNumberGenerator::GetRandomPositiveFloat(0,4));
				auto randomMovementMagnitude = RandomNumberGenerator::GetRandomPositiveFloat(4);
				switch(choice)
				{
				case 0:
				{
						  this->position.X += randomMovementMagnitude;
				} break;
				case 1:
				{
						  this->position.Y += randomMovementMagnitude;
				} break;
				case 2:
				{
						  this->position.X -= randomMovementMagnitude;
				} break;
				case 3:
				{
						  this->position.Y -= randomMovementMagnitude;
				} break;
				default:
				{
						   this->position.X++;
				} break;
				}
			} else
			{
				MoveWalkerTowardsTarget();
			}
		}

		void Walker::GaussianCalculations()
		{
			RandomBaseComplete::GaussianCalculations();
		}

		void Walker::PerlinNoiseCalculations()
		{
			RandomBaseComplete::PerlinNoiseCalculations();
			auto tempX = this->perlinNoiseCalculator->GetValue(this->perlinNoiseTime_PositionX.X, this->perlinNoiseTime_PositionX.Y, this->perlinNoiseTime_PositionX.Z);
			auto tempY = this->perlinNoiseCalculator->GetValue(this->perlinNoiseTime_PositionY.X, this->perlinNoiseTime_PositionY.Y, this->perlinNoiseTime_PositionY.Z);

			if(tempX < 0)
			{
				tempX *= -1;
			}

			if(tempY < 0)
			{
				tempY *= -1;
			}
			
			this->position.X = PerlinNoiseTool::Map(tempX, 0, 1, 0, this->GetConstrainsRange().Width);
			this->position.Y = PerlinNoiseTool::Map(tempY, 0, 1, 0, this->GetConstrainsRange().Height);

			this->perlinNoiseTime_PositionX += 0.1f;
			this->perlinNoiseTime_PositionY += 0.1f;

			VECTOR2D emptyVector;

			if(this->target != emptyVector)
			{
				this->MoveWalkerTowardsTarget();
			}
		}

		void Walker::NormalCalculations()
		{
			RandomBaseComplete::NormalCalculations();
		}

		Walker::Walker(const mRECT &areaSize) : RandomBaseComplete()
		{
			this->init(areaSize, VECTOR2D::GetZeroVector());
		}

		Walker::Walker(const mRECT &areaSize, const VECTOR2D &walkerStartPosition) : RandomBaseComplete(), position(walkerStartPosition)
		{
			this->init(areaSize, walkerStartPosition);
		}

		Walker::Walker() : RandomBaseComplete()
		{
			this->init();
		}

		Walker::Walker(const Walker &value) : RandomBaseComplete(value)
		{
			this->init(value);
		}

		Walker::Walker(Walker &&value) : RandomBaseComplete(std::move(value))
		{
			this->position = std::move(value.position);
			this->probalitityFactor = value.probalitityFactor;
			this->perlinNoiseTime_PositionX = std::move(value.perlinNoiseTime_PositionX);
			this->perlinNoiseTime_PositionY = std::move(value.perlinNoiseTime_PositionY);
			this->target = std::move(value.target);
		}


		Walker::~Walker()
		{
			RandomBaseComplete::~RandomBaseComplete();
			IPhysicsImplementor::~IPhysicsImplementor();
		}

		void Walker::MoveWalkerTowardsTarget()
		{
			Float choice = RandomNumberGenerator::GetRandomPositiveFloat(0,1);

			if(choice < this->probalitityFactor)
			{
				auto xdir = (this->target.X - this->position.X);
				auto ydir = (this->target.Y - this->position.Y);

				if(xdir != 0)
				{
					xdir /= abs(xdir);
				}

				if(ydir != 0)
				{
					ydir /= abs(ydir);
				}

				this->position.X += xdir;
				this->position.Y += ydir;
			} else
			{
				this->position.X += RandomNumberGenerator::GetRandomFloat(2);
				this->position.Y += RandomNumberGenerator::GetRandomFloat(2);
			}
			this->target = VECTOR2D::GetZeroVector();
		}

		void Walker::SetTarget(const VECTOR2D &target)
		{
			this->target = target;
		}

		const VECTOR2D  Walker::GetCurentPosition() const
		{
			return(this->position);
		}

		void Walker::SetProbalitiyFactor(Float probalitityFactor)
		{
			this->probalitityFactor = probalitityFactor;
		}

		void Walker::SetPosition(const VECTOR2D &position)
		{
			this->position = position;
		}

		Walker& Walker::operator=(const Walker& value)
		{
			if(this == &value) { return(*this); }
			RandomBaseComplete::operator=(value);

			this->init(value);
			
			return(*this);
		}

		Walker & Walker::operator=(Walker && value)
		{
			if (this == &value)
				return *this;

			
			this->position = std::move(value.position);
			this->probalitityFactor = value.probalitityFactor;
			this->perlinNoiseTime_PositionX = std::move(value.perlinNoiseTime_PositionX);
			this->perlinNoiseTime_PositionY = std::move(value.perlinNoiseTime_PositionY);
			this->target = std::move(value.target);
			
			RandomBaseComplete::operator=(std::move(value));
			return(*this);
		}

		void Walker::init()
		{
			this->SetConstrainsRange(mRECT(0,0));
			this->target.ZeroVector();
			this->perlinNoiseTime_PositionX = VECTOR3D(0,0,0);
			this->perlinNoiseTime_PositionY = VECTOR3D(10000,10000,10000);
			this->probalitityFactor = 0.9f;
			this->position.ZeroVector();
			this->SetRandomNumberMode(RandomNumberMode::Uniform);
		}

		void Walker::init(const Walker &value)
		{
			this->SetConstrainsRange(value.GetConstrainsRange());
			//this->PerlinNoiseCalculator = value.PerlinNoiseCalculator;
			this->position = value.position;
			this->probalitityFactor = value.probalitityFactor;
			this->SetRandomNumberMode(value.GetRandomNumberMode());
			this->perlinNoiseTime_PositionX = value.perlinNoiseTime_PositionX;
			this->perlinNoiseTime_PositionY = value.perlinNoiseTime_PositionY;
			this->target = value.target;
		}

		void Walker::init(const mRECT &areaSize, const VECTOR2D &walkerStartPosition)
		{
			this->target.ZeroVector();
			this->perlinNoiseTime_PositionX = VECTOR3D(0,0,0);
			this->perlinNoiseTime_PositionY = VECTOR3D(10000,10000,10000);
			this->probalitityFactor = 0.9f;

			if(!areaSize.IsZero())
				this->SetConstrainsRange(areaSize);

			if(!walkerStartPosition.IsZero())
				this->position = walkerStartPosition;

			this->SetRandomNumberMode(RandomNumberMode::Uniform);
		}


		void IWalkerImplementor::Render()
		{

		}

		void IWalkerImplementor::SetWalkerRandomNumberMode(RandomNumberMode randomNumberMode)
		{

		}

		void IWalkerImplementor::RenderWalkerByPosition(const VECTOR2D &position)
		{

		}

		void IWalkerImplementor::SetWalkerTarget(const VECTOR2D &target)
		{

		}

		void IWalkerImplementor::StepWalker()
		{

		}

		std::shared_ptr<Physics::Force> IWalkerImplementor::AccessObjectPhysics() const
		{
			return nullptr;
		}


	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora