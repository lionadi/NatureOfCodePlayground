#include "Walker.h"

namespace Aurora {
	namespace Random {




		void PWalker::SetRandomNumberMode(RandomNumberMode randomNumberMode)
		{
			PObjectBaseBasic::SetRandomNumberMode(randomNumberMode);
			this->WalkerObject.SetRandomNumberMode(randomNumberMode);
		}

		PWalker::PWalker(const mRECT &areaSize) : WalkerObject(areaSize)
		{
			
		}

		PWalker::PWalker() : PObjectBaseBasic()
		{

		}

		PWalker::~PWalker()
		{
			PObjectBaseBasic::~PObjectBaseBasic();
		}

		void PWalker::Render()
		{

		}

		void PWalker::RenderWalkerByPosition(const VECTOR2D &position)
		{

		}

		void PWalker::SetWalkerTarget(const VECTOR2D &target)
		{
			this->WalkerObject.SetTarget(target);
		}

		void PWalker::StepWalker()
		{

		}

		void PWalker::StepWalkerByTarget(const VECTOR2D &target)
		{

		}



		void Walker::Constrain()
		{
			RandomBaseComplete::Constrain();
			if(this->position.X < 0)
			{
				this->position.X = 0;
			}
			if(this->position.X > this->areaSize.Width)
			{
				this->position.X = this->areaSize.Width;
			}
			if(this->position.Y < 0)
			{
				this->position.Y = 0;
			}

			if(this->position.Y > this->areaSize.Height)
			{
				this->position.Y = this->areaSize.Height;
			}
		}

		void Walker::UniformCalculations()
		{
			RandomBaseComplete::UniformCalculations();
			VECTOR2D emptyVector;

			if(this->target == emptyVector)
			{
				auto choice = static_cast<int>(RandomNumberGenerator::GetRandomPositiveFloat(0,3));
				auto randomMovementMagnitude = RandomNumberGenerator::GetRandomPositiveFloat(2);
				switch(choice)
				{
				case 0:
					this->position.X += randomMovementMagnitude;
				case 1:
					this->position.X -= randomMovementMagnitude;
				case 2:
					this->position.Y += randomMovementMagnitude;
				case 3:
					this->position.Y -= randomMovementMagnitude;
				default:
					this->position.X++;
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
			auto tempX = this->PerlinNoiseCalculator.GetValue(this->perlinNoiseTime_PositionX.X, this->perlinNoiseTime_PositionX.Y, this->perlinNoiseTime_PositionX.Z);
			auto tempY = this->PerlinNoiseCalculator.GetValue(this->perlinNoiseTime_PositionY.X, this->perlinNoiseTime_PositionY.Y, this->perlinNoiseTime_PositionY.Z);

			if(tempX < 0)
			{
				tempX *= -1;
			}

			if(tempY < 0)
			{
				tempY *= -1;
			}
			
			this->position.X = PerlinNoiseTool::Map(tempX, 0, 1, 0, this->areaSize.Width);
			this->position.Y = PerlinNoiseTool::Map(tempY, 0, 1, 0, this->areaSize.Height);

			this->perlinNoiseTime_PositionX += 0.1;
			this->perlinNoiseTime_PositionY += 0.1;

			VECTOR2D emptyVector;

			if(this->target == emptyVector)
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
			Walker::Walker();
			this->target.ZeroVector();
			this->perlinNoiseTime_PositionX = VECTOR3D(0,0,0);
			this->perlinNoiseTime_PositionY = VECTOR3D(10000,10000,10000);
			this->probalitityFactor = 0.9f;
			this->SetConstrainsRange(areaSize);
			this->position.X = this->areaSize.Width / 2;
			this->position.Y = this->areaSize.Height / 2;
			this->SetRandomNumberMode(RandomNumberMode::Uniform);
		}

		Walker::Walker(const mRECT &areaSize, const VECTOR2D &walkerStartPosition) : RandomBaseComplete()
		{
			Walker::Walker(areaSize);
			this->position = walkerStartPosition;
		}

		Walker::Walker() : PRandomBaseComplete()
		{

		}

		Walker::~Walker()
		{
			RandomBaseComplete::~RandomBaseComplete();
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
		}

		void Walker::SetTarget(VECTOR2D target)
		{
			this->target = target;
		}

		Aurora::Math::VECTOR2D Walker::GetCurentPosition()
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

	}; // END OF NAMESPACE Random
}; // END OF NAMESPACE Aurora