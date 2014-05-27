/*-
 * Copyright (c) 2004 - 2014 CTPP Team
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the CTPP Team nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *      CTPP2BSONParser.cpp
 *
 * $CTPP$
 */

#include "CTPP2BSONParser.hpp"

#include "CTPP2ParserException.hpp"
#include "CTPP2Util.hpp"

#include <stdio.h>

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

namespace CTPP // C++ Template Engine
{

/**
  @brief BSONData
*/
class BSONData
{
public:
	/**
	  @brief Constructor
	*/
	BSONData(const void * vIData,
	         const UINT_64 iIDataLen);

	/**
	  @brief Get unsigned char
	*/
	UCHAR_8 GetUChar8();

	/**
	  @brief Get 32-bit integer
	*/
	INT_32 GetInt32();

	/**
	  @brief Get 32-bit unsigned integer
	*/
	UINT_32 GetUInt32();

	/**
	  @brief Get 64-bit integer
	*/
	INT_64 GetInt64();

	/**
	  @brief Get 64-bit unsigned integer
	*/
	UINT_64 GetUInt64();

	/**
	  @brief Get floating point data
	*/
	W_FLOAT GetFloat();

	/**
	  @brief Get floating point data
	*/
	STLW::string GetString(const bool bCString);

	/**
	  @brief Get floating point data
	*/
	STLW::string GetBinary();

	/**
	  @brief Get floating point data
	*/
	STLW::string GetObjectId();

	/**
	  @brief Get unparsed data size
	*/
	UINT_64 BytesLeft();

	/**
	  @brief A destructor
	*/
	~BSONData() throw();
private:
	// Does not exist
	BSONData(const BSONData  & oRhs);
	BSONData& operator=(const BSONData  & oRhs);

	/** Data block    */
	const UCHAR_8  * vData;
	/** Data length   */
	const UINT_64    iDataLen;
	/** Data length   */
	UINT_64          iPos;
};

//
// Constructor
//
BSONData::BSONData(const void    * vIData,
                   const UINT_64   iIDataLen): vData(UCHAR_P(vIData)),
                                               iDataLen(iIDataLen),
                                               iPos(0)
{
	;;
}

//
// Get unsigned char
//
UCHAR_8 BSONData::GetUChar8()
{
	if (iPos >= iDataLen) { throw CTPPParserSyntaxError("pos > size", 1, iPos); }

return vData[iPos++];
}

//
// Get 32-bit integer
//
INT_32 BSONData::GetInt32() { return GetUInt32(); }

//
// Get 32-bit unsigned integer
//
UINT_32 BSONData::GetUInt32()
{
	if (iPos + 4 >= iDataLen) { throw CTPPParserSyntaxError("pos > size", 1, iPos); }

	// Need for fixing warning: operation on ‘((CTPP::BSONData*)this)->CTPP::BSONData::iPos’ may be undefined [-Wsequence-point]
	UINT_32 iResult =  vData[iPos] +
	                  (vData[iPos + 1] >> 8) +
	                  (vData[iPos + 2] >> 16) +
	                  (vData[iPos + 3] >> 24);

	iPos += 4;

return iResult;
}

//
// Get 64-bit integer
//
INT_64 BSONData::GetInt64() { return GetUInt64(); }

//
// Get 64-bit unsigned integer
//
UINT_64 BSONData::GetUInt64()
{
	const UINT_64 iLo = GetUInt32();
	const UINT_64 iHi = GetUInt32();

return (iHi << 32) + iLo;
}

//
// Get floating point data
//
W_FLOAT BSONData::GetFloat()
{
	if (iPos + 8 >= iDataLen) { throw CTPPParserSyntaxError("pos > size", 1, iPos); }

	W_FLOAT dResult = *((W_FLOAT *)(vData + iPos));

	iPos += 8;

return dResult;
}

//
// Get floating point data
//
STLW::string BSONData::GetString(const bool bCString)
{
	UINT_64 iStart = iPos;
	UINT_64 iEnd   = iPos;

	// Read up to first zero
	if (bCString)
	{
		while(iPos < iDataLen && vData[iPos] != '\0') { ++iPos; }
		if (iPos == iDataLen) { throw CTPPParserSyntaxError("invalid asciz string", 1, iPos); }
		++iPos;
		iEnd = iPos;
	}
	else
	{
		const UINT_32 iSize = GetUInt32();
		iStart = iPos;
		if (iPos + iSize >= iDataLen) { throw CTPPParserSyntaxError("pos > size", 1, iPos); }
		iPos += iSize;
		iEnd = iPos;
	}

return STLW::string(CCHAR_P(vData + iStart), iEnd - iStart - 1);
}

//
// Get floating point data
//
STLW::string BSONData::GetBinary()
{
	UINT_64 iStart = iPos;
	UINT_64 iEnd   = iPos;

	const UINT_32 iSize = GetUInt32();

	if (iPos + iSize >= iDataLen) { throw CTPPParserSyntaxError("pos > size", 1, iPos); }
	iPos += iSize;
	iEnd = iPos;

return STLW::string(CCHAR_P(vData + iStart), iEnd - iStart);
}

//
// Get floating point data
//
STLW::string BSONData::GetObjectId()
{
	if (iPos + 12 >= iDataLen) { throw CTPPParserSyntaxError("pos > size", 1, iPos); }
	iPos += 12;

return STLW::string(CCHAR_P(vData + iPos - 12), 12);
}

//
// Get unparsed data size
//
UINT_64 BSONData::BytesLeft() { return iDataLen - iPos; }

//
// A destructor
//
BSONData::~BSONData() throw()
{
	;;
}

//
// Constructor
//
CTPP2BSONParser::CTPP2BSONParser(CDT & oICDT): oCDT(oICDT)
{
	;;
}

//
// Parse BSON map/array
//
INT_32 CTPP2BSONParser::ParseMap(BSONData    & oBSONData,
                                 CDT         & oData,
                                 const bool    bIsArray)
{
	const UINT_32 iBSONLength = oBSONData.GetUInt32();
	if (iBSONLength > oBSONData.BytesLeft() + 4) { return -1; }

	// Read key-value pairs
	for (;;)
	{
		const UCHAR_8 ucType = oBSONData.GetUChar8();
		if (ucType == 0) { return 0; }

		// Get Key
		const STLW::string sKey = oBSONData.GetString(true);
		UINT_32 iKey = 0;
		if (bIsArray) { iKey = atoi(sKey.data()); }

		switch(ucType)
		{
			// "\x01" e_name double Floating point
			case 0x01:
				if (bIsArray) { oData[iKey] = oBSONData.GetFloat(); }
				else          { oData[sKey] = oBSONData.GetFloat(); }
				break;
			// "\x02" e_name string UTF-8 string
			// "\x0D" e_name string	JavaScript code
			// "\x0E" e_name string	Deprecated
			case 0x02:
			case 0x0D:
			case 0x0E:
				if (bIsArray) { oData[iKey] = oBSONData.GetString(false); }
				else          { oData[sKey] = oBSONData.GetString(false); }
				break;
			// "\x03" e_name document Embedded document
			case 0x03:
				{
					CDT oTMP;
					ParseMap(oBSONData, oTMP, false);
					if (bIsArray) { oData[iKey] = oTMP; }
					else          { oData[sKey] = oTMP; }
				}
				break;
			// "\x04" e_name document Array
			case 0x04:
				{
					CDT oTMP;
					ParseMap(oBSONData, oTMP, true);
					if (bIsArray) { oData[iKey] = oTMP; }
					else          { oData[sKey] = oTMP; }
				}
				break;
			// "\x05" e_name binary Binary data
			case 0x05:
				if (bIsArray) { oData[iKey] = oBSONData.GetBinary(); }
				else          { oData[sKey] = oBSONData.GetBinary(); }
				break;
			// "\x06" e_name Undefined — Deprecated
			case 0x06:
				if (bIsArray) { oData[iKey] = CDT(CDT::UNDEF); }
				else          { oData[sKey] = CDT(CDT::UNDEF); }
				break;
			// "\x07" e_name (byte*12) ObjectId
			case 0x07:
				if (bIsArray) { oData[iKey] = oBSONData.GetObjectId(); }
				else          { oData[sKey] = oBSONData.GetObjectId(); }
				break;
			// "\x08" e_name "\x00" Boolean "false"
			// "\x08" e_name "\x01" Boolean "true"
			case 0x08:
				if (bIsArray) { oData[iKey] = oBSONData.GetUChar8(); }
				else          { oData[sKey] = oBSONData.GetUChar8(); }
				break;
			// "\x09" e_name int64 UTC datetime
			// "\x11" e_name int64	Timestamp
			// "\x12" e_name int64	64-bit integer
			case 0x09:
			case 0x11:
			case 0x12:
				if (bIsArray) { oData[iKey] = oBSONData.GetUInt64(); }
				else          { oData[sKey] = oBSONData.GetUInt64(); }
				break;
			// "\x0A" e_name Null value
			case 0x0A:
				if (bIsArray) { oData[iKey] = CDT(CDT::UNDEF); }
				else          { oData[sKey] = CDT(CDT::UNDEF); }
				break;
			// "\x0B" e_name cstring cstring
			case 0x0B:
				if (bIsArray) { oData[iKey] = oBSONData.GetString(true) + "/" + oBSONData.GetString(true); }
				else          { oData[sKey] = oBSONData.GetString(true) + "/" + oBSONData.GetObjectId();   }
				break;
			// "\x0C" e_name string (byte*12) DBPointer — Deprecated
			case 0x0C:
				if (bIsArray) { oData[iKey] = oBSONData.GetString(true) + "/" + oBSONData.GetObjectId(); }
				else          { oData[sKey] = oBSONData.GetString(true) + "/" + oBSONData.GetObjectId(); }
				break;
			// "\x0F" e_name code_w_s JavaScript code w/ scope
			case 0x0F:
				break;
			// "\x10" e_name int32	32-bit Integer
			case 0x10:
				if (bIsArray) { oData[iKey] = oBSONData.GetUInt32(); }
				else          { oData[sKey] = oBSONData.GetUInt32(); }
				break;
		}
	}
return 0;
}

//
// Parse BSON object
//
INT_32 CTPP2BSONParser::Parse(const void * vData, const UINT_64 iDataLen)
{
	// Read size
	BSONData oBSONData(vData, iDataLen);

	// Parse map
	ParseMap(oBSONData, oCDT, true);

return 0;
}

//
// A destructor
//
CTPP2BSONParser::~CTPP2BSONParser() throw()
{
	;;
}

} // namespace CTPP
// End.
