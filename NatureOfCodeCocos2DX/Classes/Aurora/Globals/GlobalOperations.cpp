#include "GlobalOperations.h"


extern "C" inline unsigned int RGB16BIT555(unsigned int r, unsigned int g, unsigned int b)
{
	return((b & 31) + ((g & 31) << 5) + ((r & 31) << 10));
}

extern "C" inline unsigned int RGB16BIT565(unsigned int r, unsigned int g, unsigned int b)
{
	return((b & 31) + ((g & 63) << 5) + ((r & 31) << 11));	
}


extern "C" bool CompareStrings(std::string strOne, std::string strTwo)
{
	// here we loop through every letter in our STL string parameter and insert the values in cString type char
	std::string::iterator i = strOne.begin();
	if(strOne != "" && strTwo!="")
	{
		for(std::string::iterator j = strTwo.begin(); j != strTwo.end(); j++)
		{

			if(!(*i == *j))
				return(false);
			else
				i++;
		}
	}
	else
		return(false);

	return(true);
}

extern "C" bool IsStringPlainNumber(std::string str)
{
	std::string num = "0123456789";
	bool IsNumber = false;

	for(std::string::iterator j = str.begin(); j != str.end(); j++)
	{
		IsNumber = false;
		for(std::string::iterator n = num.begin(); n != num.end(); n++)
		{
			if(*n == *j) { IsNumber = true; break; }
		}
		if(!IsNumber) { return(false); }
		
	}

	return(true);
}
