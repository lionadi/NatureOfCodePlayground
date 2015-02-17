#include "DotWalker.h"

using namespace cocos2d;
namespace Aurora
{
	namespace Cocos2DX
	{

		

		DotWalker::DotWalker() : Walker()
		{
			this->viewSize = Director::getInstance()->getVisibleSize();
			this->SetConstrainsRange(ConvertSizeTo_mRect(this->viewSize));
			this->init();
		}

		DotWalker::DotWalker(const Size &viewSize) : Walker(ConvertSizeTo_mRect(viewSize))
		{
			//DotWalker::DotWalker();
			//this->SetConstrainsRange(ConvertSizeTo_mRect(viewSize));
			this->init(viewSize);
		}

		DotWalker::DotWalker(const Size &viewSize, const Vec2 &position) : Walker(ConvertSizeTo_mRect(viewSize), ConvertVec2Tp_VECTOR2D((position)))
		{
			//DotWalker::DotWalker(viewSize);
			//this->SetPosition(ConvertVec2Tp_VECTOR2D((position)));			
			this->init(viewSize);
			//this->dotWalkerDrawNode->setPosition(position);
		}

		DotWalker::DotWalker(const Vec2 &position) : Walker(mRECT(0, 0), ConvertVec2Tp_VECTOR2D((position)))
		{
			//DotWalker::DotWalker();
			//this->SetPosition(ConvertVec2Tp_VECTOR2D((position)));
			this->init();
			//this->dotWalkerDrawNode->setPosition(position);
		}

		DotWalker::~DotWalker()
		{
			IWalkerImplementor::~IWalkerImplementor();
			Walker::~Walker();
		}

		void DotWalker::RenderWalkerByPosition(const VECTOR2D &position)
		{
			this->dotWalkerDrawNode->drawDot(ConvertVECTOR2DTp_Vec2(position), 10, this->mainColor);
		}

		void DotWalker::SetWalkerTarget(const Vec2 &target)
		{
			this->TargetForWalker = target;
			this->SetTarget(ConvertVec2Tp_VECTOR2D(target));
			this->TargetForWalker = Vec2::ZERO;
		}

		void DotWalker::StepWalker()
		{

			if(this->TargetForWalker != Vec2::ZERO)
			{
				this->SetTarget(ConvertVec2Tp_VECTOR2D(this->TargetForWalker));
			} 

			this->CalculateColor();
			this->DoCalculations();
			this->RenderWalkerByPosition(this->GetCurentPosition());
		}

		void DotWalker::Render()
		{
			if (this->dotWalkerDrawNode == nullptr)
				return;

			IWalkerImplementor::Render();
			DelayTime *delayAction = DelayTime::create(0.0001f);
			//std::function<void(DotWalker&)> makeWalkerStep = &DotWalker::StepWalker;
			// perform the selector call
			CallFunc *callSelectorAction = CallFunc::create(
				std::bind(&DotWalker::StepWalker, this));
			
			Sequence *actionSequence = Sequence::create(callSelectorAction,delayAction, NULL);

			this->dotWalkerDrawNode->runAction(RepeatForever::create(actionSequence));
		}

		void DotWalker::CalculateColor()
		{
			this->colorCount++;
			if(this->colorCount > this->colorCountLimit)
			{
				auto choice = static_cast<int>(RandomNumberGenerator::GetRandomPositiveFloat(0, 4));

				switch(choice)
				{
				case 0:
					this->mainColor = Color4F::BLUE;
					break;
				case 1:
					this->mainColor = Color4F::RED;
					break;
				case 2:
					this->mainColor = Color4F::YELLOW;
					break;
				case 3:
					this->mainColor = Color4F::GREEN;
					break;
				default:
					this->mainColor = Color4F::BLUE;
					break;
				}				
			}
			else
			{
				this->colorCount = 0;
			}

		}

		DrawNode * DotWalker::GetWalkerDrawNode()
		{
			return(this->dotWalkerDrawNode);
		}

		void DotWalker::init()
		{
			this->dotWalkerDrawNode = DrawNode::create();
			this->Render();
			this->ImplementorObjectPhysics(this->ObjectPhysics());
		}

		void DotWalker::init(const Size &areaSize)
		{
			this->viewSize = areaSize;
			this->dotWalkerDrawNode = DrawNode::create();
			this->Render();
			this->ImplementorObjectPhysics(this->ObjectPhysics());
		}

		void DotWalker::init(const IWalkerImplementor &value)
		{
			throw std::logic_error("The method or operation is not implemented.");
		}

		void DotWalker::SetWalkerDrawNodeStartPosition(const Vec2& startPosition)
		{
			this->dotWalkerDrawNode->setPosition(startPosition);
		}

		void DotWalker::SetWalkerRandomNumberMode(RandomNumberMode randomNumberMode)
		{
			this->SetRandomNumberMode(randomNumberMode);
		}

		std::shared_ptr<Physics::Force> DotWalker::AccessObjectPhysics() const
		{
			return this->ObjectPhysics();
		}

	};
};

