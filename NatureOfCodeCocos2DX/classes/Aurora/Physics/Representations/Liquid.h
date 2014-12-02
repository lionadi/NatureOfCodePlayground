#ifndef NatureOfCodeCocos2DX_Liquid_h
#define NatureOfCodeCocos2DX_Liquid_h


#include "../Implementations/Force.h"
#include "../../Random/BaseClasses/ObjectBase.h"

using namespace Aurora::Math;

namespace Aurora {
	namespace Physics {
		//class Liquid : public IPhysicsBase
		//{
		//	private:
		//		virtual void init() override;
		//		float coefficientDrag;
		//		VECTOR4D liquidArea;
		//		

		//public:
		//	Liquid() = default;
		//	virtual ~Liquid() = default;

		//	Liquid(const VECTOR4D &liquidArea, float coefficientDrag);

		//	
		//	bool IsInside(const VECTOR2D &value);

		//	float CoefficientDrag() const { return coefficientDrag; }
		//	template<typename T>
		//	void CoefficientDrag(T &&value) { coefficientDrag = std::forward<T>(value); }
		//	
		//	Aurora::Math::VECTOR4D LiquidArea() const { return liquidArea; }
		//	template<typename T>
		//	void LiquidArea(T &&value) { liquidArea = std::forward<T>(value); }

		//};

		//class ILiquid : public Aurora::Random::IObjectBaseBasic
		//{
		//public:
		//	ILiquid() = default;
		//	virtual ~ILiquid() = default;

		//	virtual void init() override;

		//	virtual void Render() override;



		//	//virtual void SetMoverTarget(const VECTOR2D &target);
		//};
	};
};

#endif