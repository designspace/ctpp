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
 *      CTPP2BSONParser.hpp
 *
 * $CTPP$
 */
#ifndef _CTPP2_BSON_PARSER_H__
#define _CTPP2_BSON_PARSER_H__ 1

#include "CDT.hpp"
#include "CTPP2CharIterator.hpp"

#include "STLString.hpp"

/**
  @file CTPP2BSONParser.hpp
  @brief BSON Parser
*/

namespace CTPP // C++ Template Engine
{
// FWD
class BSONData;

/**
  @class CTPP2BSONParser CTPP2BSONParser.hpp <CTPP2BSONParser.hpp>
  @brief BSON source code parser
*/
class CTPP2DECL CTPP2BSONParser
{
public:
	/**
	  @brief Constructor
	*/
	CTPP2BSONParser(CDT & oICDT);

	/**
	  @brief Parse BSON data
	  @param vData - data block
	  @param iDataLen - data size
	  @return 0 if success, -1 if any error occured
	*/
	INT_32 Parse(const void * vData, const UINT_64 iDataLen);

	/**
	  @brief A destructor
	*/
	~CTPP2BSONParser() throw();
private:
	/** Data collector        */
	CDT           & oCDT;

	INT_32 ParseMap(BSONData  & oBSONData, CDT & oData, const bool    bIsArray);
};

} // namespace CTPP
#endif // _CTPP2_BSON_PARSER_H__
// End.
