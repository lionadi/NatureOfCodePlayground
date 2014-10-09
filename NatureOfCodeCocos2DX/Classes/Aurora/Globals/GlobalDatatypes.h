#ifndef GLOBALDATATYPES_H
#define GLOBALDATATYPES_H
#include <string>
#include <vector>

/*!
Namespace: Aurora

\brief This namespace is the main package for the engine. It holds all the main classes, namespaces, operations etc... that defines the functionality of this project/engine.
*/
namespace Aurora
{
	/*!
	Namespace: DataTypes

	\brief This namespace holds the engines different datatypes that are used allover the project. It holds datatypes from basic types supported by C/C++ to complex struct, enumerations and STL specific types.
	*/
	namespace DataTypes
	{
		typedef char						Char;			/*!< Char variable: Bit length 8						*/
		typedef unsigned char				UChar, Byte;	/*!< Unsigned char or byte variable: Bit length 8		*/
		typedef short						Int16;			/*!< Int variable: Bit length 16						*/
		typedef unsigned short				UInt16;			/*!< Unsigned Int variable: Bit length 16				*/
		typedef int							Int32;			/*!< Int variable: Bit length 32						*/
		typedef unsigned int				UInt32;			/*!< Unsigned Int variable: Bit length 32				*/
		typedef long						Long;			/*!< Long variable: Bit length 32						*/
		typedef unsigned long				ULong;			/*!< Unsigned Long variable: Bit length 32				*/
		typedef float						Float;			/*!< Float variable: Bit length 32						*/
		typedef double						Double;			/*!< Double variable: Bit length 64						*/
		typedef long double					LDouble;		/*!< Long double variable: Bit length 64				*/
		typedef long long					Int64;			/*!< Int long variable: Bit length 64					*/
		typedef std::string					String;			/*!< String type variable: Bit length N/A				*/
		typedef std::vector<std::string>	vString;		/*!< A vector class array with strings in it variable	*/
		
		//--------------------------------------------------------------------------------------------------------------------------------------
		// Engine specific datatypes
		//______________________________________________________________________________________________________________________________________

		// Datatypes for engine initialization
		//--------------------------------------------------------------------------------------------------------------------------------------

		/*!
		\brief This enumeration is used to define key data within the project and it's configuration files that can be used to tell the engine which keys are used and how are they used.
		*/
		enum engKEYCONF		{	NOKEY,		/*!< This tells that there was an invalid key definition in the configuration file. It also tells that this key should be ignored. */
								KEY_DOWN,	/*!< This is a action for the arrow key down.	*/
								KEY_UP,		/*!< This is a action for the arrow key up.		*/
								KEY_LEFT,	/*!< This is a action for the arrow key left.	*/
								KEY_RIGHT,	/*!< This is a action for the arrow key right.	*/
								KEY_W,		/*!< This is a action for the key w.			*/
								KEY_S,		/*!< This is a action for the key s.			*/
								KEY_D,		/*!< This is a action for the key d.			*/
								KEY_A,		/*!< This is a action for the key a.			*/
								KEY_F1,		/*!< This is a action for the key F1.			*/
								KEY_F2,		/*!< This is a action for the key F2.			*/
								KEY_ESC		/*!< This is a action for the key ESC.			*/
							};
		/*!
		\brief This enumeration is used to define engine specific states which define the engines operation states.
		*/
		enum engENGINECONF	{	UNKNOWNINFO,	/*!< This specifies that this data loaded from an engine configuration file is invalid*/
								RESWIDTH,		/*!< This is the state value that indicates the width resolution. */
								RESHEIGHT,		/*!< This is the state value that indicates the height resolution. */
								WINDOWED,		/*!< Defines the state of windowed or full-screen engine state. */
								BITDEPTH		/*!< The Bit depth that is to be used for rendering. */
							};
		/*!
		\brief This is used to determine which kind of a configuration file is to be processed by the fioENGINEINIT class.
		*/
		enum engCONFIGTYPE	{	UNKNOWN,		/*!< .*/
								ENGINECONFIG,	/*!< .*/
								INPUTCONFIG		/*!< .*/
							};
		/*!
		\brief This enumeration defines the bit-depth that is to be used for rendering.
		*/
		enum engPIXELFORMAT {	INVALID_PF		= 0,	/*!< .*/
								DDRAW_PF8		= 8,	/*!< .*/
								DDRAW_PF555		= 15,	/*!< .*/
								DDRAW_PF565		= 16,	/*!< .*/
								DDRAW_PF888		= 24,	/*!< .*/
								DDRAW_PFA888	= 32	/*!< .*/
							};
		
		/*!
		\brief This enumeration BITMAP image specific properties or states.
		*/
		enum g_ipBITMAPDEF {	BITMAP_ID					= 0x4D42,	/*!< Global Bitmap file ID.*/
								BITMAP_STATE_DEAD			= 0,		/*!< .*/
								BITMAP_STATE_ALIVE			= 1,		/*!< .*/
								BITMAP_STATE_DYING			= 2,		/*!< .*/
								BITMAP_ATTR_LOADED			= 128,		/*!< .*/
								BITMAP_EXTRACT_MODE_CELL	= 0,		/*!< .*/
								BITMAP_EXTRACT_MODE_ABS		= 1,		/*!< .*/
								BITMAP_8BITPF				= 8,		/*!< .*/
								BITMAP_555BITPF				= 15,		/*!< .*/
								BITMAP_565BITPF				= 16,		/*!< .*/
								BITMAP_888BITPF				= 24		/*!< .*/
						  };

		/*!
		\brief This struct is used to keep temporary data that is loaded from a configuration file. Notice that this struct can be used for two different configuration files.
		*/
		extern "C" struct engCONFIGDATA
		{
			String			Data;			/*!< Here goes the data that loaded from the configuration file. This value tells the engine what kind of action it need to take for this configuration. For example if this where a key configuration this could be used to tell what action should a specific key do whitin the engine rendering loop. */
			engKEYCONF		KeyData;		/*!< The key id. */
			engENGINECONF	EngineData;		/*!< The engine state to which we must assign this value. */
		};
		/*!
		\brief This is a STL vector array holding engine configuration data that is not yet processed for the engine.
		*/
		typedef std::vector<engCONFIGDATA> vaENGINECONFIGDATA;

		/*!
		\brief This struct defines the state of the gGRAPHICSPAINTER class. In other words the states that are required to define the Direct Draw interface so that the engine can draw.
		*/
		extern "C" struct gPAINTERSTATES
		{
				UInt32	WindowHeight;		/*!< The height of the drawing surface. */
				UInt32	WindowWidth;		/*!< The width of the drawing surface. */
				bool	IsWindowed;			/*!< The state that indicates to the engine in which mode to draw. */
				engPIXELFORMAT	BitDepth;	/*!< The bit-depth for the rendering surface */
				UInt32 MinClipX;
				UInt32 MaxClipX;
				UInt32 MinClipY;
				UInt32 MaxClipY;
		};

		/*!
		\brief The struct is a Direct Draw surface data holder. It is used for a quick "addressing" to a Direct Draw surface properties. This clears code and save it.
		*/
		extern "C" struct gDDRAWSURFACESTATE
		{
			Byte *SurfaceBuffer;	/*!< Holds an address of a linear VRAM memory. */
			UInt32 SurfacePitch;	/*!< .*/
		};

		/*!
		\brief Holds SIN/COS values for 360 degrees(these are lookup tables).
		*/
		extern "C" struct lSINCOSTABLES
		{
			Float SinTable[361];		/*!< Sin lookup table. */
			Float CosTable[361];		/*!< Cos lookup table. */
		};

		/*!
		\brief This is the main state struct that holds and defines the whole engines basic functionality: such as a palette for a possible 8-Bit rendering mode, the primary and secondary drawing surfaces linear memory address etc...
		*/
		class lENGINESTATES
		{
			public:
				gPAINTERSTATES PainterState;				/*!< This struct holds all the important data that defines how the engine will work. */
				//PALETTEENTRY Engine8BitPalette[256];		/*!< \brief A basic palette for a possible 8-Bit rendering mode. */
				bool IsEnded;								/*!< Determines if the engine has been ended. This state is used to determine if there is a need to render in the main loop. Notice after the engine received the kill signal. Normally this should be true so that the will not be an extra rendering loop. That may cause the engine to crash. */

				gDDRAWSURFACESTATE PrimarySurfaceState;		/*!< \brief A state holder to the primary surface. Use this for a quick access to the main needed components from this surface. */
				gDDRAWSURFACESTATE SecondarySurfaceState;	/*!< \brief A state holder to the secondary surface. Use this for a quick access to the main needed components from this surface. */
				//RECT WindowClipperRectangle;
				lSINCOSTABLES SinCosTables;					/*!< This is will hold the SIN/COS values as a lookup table(for 360 degrees).*/
		};

		/*!
		\brief Enumeration for 2D polygon states that defines how an 2D polygon should behave.
		*/
		enum gPOLYGON2DSTATES
		{
			POLY2D_INVISIBLE,				/*!< Determines that a 2D polygon is not to be seen or drawn.	*/
			POLY2D_VISIBLE					/*!< The polygon can be drawn or set visible.					*/
		};

		const Float PI				= 3.141592654f;		/*!< .*/
		const Float PI2				= 6.283185307f;		/*!< .*/
		const Float PI_DIV_2		= 1.570796327f;		/*!< .*/
		const Float PI_DIV_4		= 0.785398163f;		/*!< .*/
		const Float PI_INV			= 0.318309886f;		/*!< .*/


	}; // END OF NAMESPACE DATATYPES
}; // END OF NAMESPACE Aurora

#endif