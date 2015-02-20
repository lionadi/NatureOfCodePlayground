#ifndef NatureOfCodeCocos2DX_ErrorMessages_h
#define NatureOfCodeCocos2DX_ErrorMessages_h

#include <string>

namespace Aurora {
	namespace Errors {

		class ErrorMessages
		{
		public:
			static std::string PhysicsForceEmptyObject;
			static std::string DivisionByZero;
			static std::string TypeMismatch;
			static std::string EmptyObjectFound;
		};

	};
};


#endif