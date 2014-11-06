#ifndef GLOBALOPERATIONS_H
#define GLOBALOPERATIONS_H

#include <string>
#include <vector>
#include <fstream>

/*! \file */ 
/*! A quick define for a debug mode key usage without any big complications. */
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
/*! A quick define for a debug mode key usage without any big complications. */
#define KEY_UP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
/*! This define will initialize a Direct Draw description struct. */
#define DDRAW_INIT_STRUCT(ddstruct) { memset(&ddstruct,0,sizeof(ddstruct)); ddstruct.dwSize=sizeof(ddstruct); }
/*! Used to delete a DirectX component without any memory leaks. */
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
/*! Used to delete a DirectX component without any memory leaks. */
#define SAFE_RELEASE(x) if (x != NULL) {x->Release(); x = NULL;}
/*! A quick Win32 MessageBox function caller. */
#define MSG(msg) MessageBox( NULL, msg, "Application Message", MB_OK )	// An windows message box

/*! \brief This builds a 16 bit color value in 5.5.5 format (1-bit alpha mode) */
#define _RGB16BIT555(r,g,b) ((b & 31) + ((g & 31) << 5) + ((r & 31) << 10))
/*! \brief This builds a 16 bit color value in 5.6.5 format (green dominate mode) */
#define _RGB16BIT565(r,g,b) ((b & 31) + ((g & 63) << 5) + ((r & 31) << 11))
/*! \brief This builds a 24 bit color value in 8.8.8 format */
#define _RGB24BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) )
/*! \brief This builds a 32 bit color value in A.8.8.8 format (8-bit alpha mode) */
#define _RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))
//#define MIN(a, b)  (((a) < (b)) ? (a) : (b)) 
//#define MAX(a, b)  (((a) > (b)) ? (a) : (b)) 
//#define SWAP(a,b,t) {t=a; a=b; b=t;}

extern "C" inline unsigned int RGB16BIT555(unsigned int r, unsigned int g, unsigned int b);
extern "C" inline unsigned int RGB16BIT565(unsigned int r, unsigned int g, unsigned int b);

/*!
 This function will compare two STL string and return true if they are identical or false if not.
 */
extern "C" bool CompareStrings(std::string strOne, std::string strTwo);
/*!
 
 This function will determine if a given STL string is just a number with no ASCII nor UNICODE chars.
 */
extern "C" bool IsStringPlainNumber(std::string str);

#endif