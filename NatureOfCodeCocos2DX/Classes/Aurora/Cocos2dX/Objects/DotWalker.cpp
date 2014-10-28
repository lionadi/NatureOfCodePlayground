#include "DotWalker.h"

using namespace cocos2d;
namespace Aurora
{
	namespace Cocos2DX
	{

		

		DotWalker::DotWalker() : PWalker()
		{
			this->viewSize = Director::getInstance()->getVisibleSize();
			this->WalkerObject.SetConstrainsRange(ConvertSizeTo_mRect(this->viewSize));
		}

		DotWalker::DotWalker(const Size &viewSize)
		{
			DotWalker::DotWalker();
			this->WalkerObject.SetConstrainsRange(ConvertSizeTo_mRect(viewSize));
		}

		DotWalker::DotWalker(const Size &viewSize, const Vec2 &position)
		{
			DotWalker::DotWalker(viewSize);
			this->WalkerObject.SetPosition(ConvertVec2Tp_VECTOR2D((position)));
		}

		DotWalker::DotWalker(const Vec2 &position)
		{
			DotWalker::DotWalker();
			this->WalkerObject.SetPosition(ConvertVec2Tp_VECTOR2D((position)));
		}

		DotWalker::~DotWalker()
		{
			PWalker::~PWalker();
		}

		void DotWalker::RenderWalkerByPosition(const VECTOR2D &position)
		{

		}

		void DotWalker::SetWalkerTarget(const Vec2 &target)
		{
			PWalker::SetWalkerTarget(ConvertVec2Tp_VECTOR2D((target)));
			this->TargetForWalker = target;
		}

		void DotWalker::StepWalker()
		{

			if(this->TargetForWalker != Vec2::ZERO)
			{
				this->WalkerObject.SetTarget(ConvertVec2Tp_VECTOR2D(this->TargetForWalker));
			} 

			this->CalculateColor();
			this->WalkerObject.DoCalculations();
			this->RenderWalkerByPosition(this->WalkerObject.GetCurentPosition());
		}

		void DotWalker::Render()
		{
			PWalker::Render();
			DelayTime *delayAction = DelayTime::create(0.0001f);
			//std::function<void(DotWalker&)> makeWalkerStep = &DotWalker::StepWalker;
			// perform the selector call
			CallFunc *callSelectorAction = CallFunc::create(
				std::bind(&DotWalker::StepWalker, this));

			Sequence *actionSequence = Sequence::create(callSelectorAction,delayAction, NULL);

			this->runAction(RepeatForever::create(actionSequence));
		}

		void DotWalker::CalculateColor()
		{
			this->colorCount++;
			if(this->colorCount > this->colorCountLimit)
			{
				auto choice = static_cast<int>(RandomNumberGenerator::GetRandomPositiveFloat(0, 3));

				switch(choice)
				{
				case 0:
					this->mainColor = Color3B::BLUE;
				case 1:
					this->mainColor = Color3B::RED;
				case 2:
					this->mainColor = Color3B::YELLOW;
				case 3:
					this->mainColor = Color3B::GREEN;
				default:
					this->mainColor = Color3B::BLUE;
				}
				this->colorCount = 0;
			}
		}

	};
};

