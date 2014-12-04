#include "LiquidContainer.h"

namespace Aurora
{
	namespace Cocos2DX
	{


		void LiquidContainer::init()
		{
			Liquid::init();
		}

		void LiquidContainer::init(const Size &areaSize, float coefficientDrag)
		{
			this->objectDrawNode = cocos2d::DrawNode::create();
			this->objectDrawNode->setAnchorPoint(Vec2(0, 0));
			this->AreaSize(ConvertSizeTo_mRect(areaSize));
			this->CoefficientDrag(coefficientDrag);
			this->AddEdgePoint(VECTOR2D(0, 0));
			this->AddEdgePoint(VECTOR2D(0, areaSize.height / 2));
			this->AddEdgePoint(VECTOR2D(areaSize.width, areaSize.height / 2));
			this->AddEdgePoint(VECTOR2D(areaSize.width, 0));
			this->Render();
		}


		void LiquidContainer::Render()
		{
			if (this->objectDrawNode == nullptr)
				return;

			this->mainColor = cocos2d::Color4F(0,0,1.0f,0.5f);
			Vec2 *vecs = new Vec2[this->LiquidArea().size()];
			Point origin = Director::getInstance()->getVisibleOrigin();
			vecs[0].x = 0;
			vecs[0].y = 0;
			vecs[1].x = 0;
			vecs[1].y = this->AreaSize().Height / 2;
			vecs[2].x = this->AreaSize().Width;
			vecs[2].y = this->AreaSize().Height /2;
			vecs[3].x = this->AreaSize().Width;
			vecs[3].y = 0;
			vecs[0] += origin;
			vecs[1] += origin;
			vecs[2] += origin;
			vecs[3] += origin;
			auto polygonData = ConvertVECTOR2DListTp_Vec2(this->LiquidArea());
			for (auto &singlePoly : polygonData)
			{
				singlePoly += origin;
			}

			this->objectDrawNode->drawPolygon(&polygonData[0], this->LiquidArea().size(), this->mainColor, 1, this->mainColor);
		}

		LiquidContainer::LiquidContainer() : Liquid()
		{

		}

		LiquidContainer::LiquidContainer(const Size &viewSize)
		{
			this->init(viewSize, 0.1f);
		}

		LiquidContainer::LiquidContainer(const Size &viewSize, float coefficientDrag)
		{
			this->init(viewSize, coefficientDrag);
		}

		LiquidContainer::~LiquidContainer()
		{
			Liquid::~Liquid();
		}

		DrawNode * LiquidContainer::GetDrawNode()
		{
			return this->objectDrawNode;
		}

	};
};