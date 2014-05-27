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
 *      CTPP2Util.cpp
 *
 * $CTPP$
 */
#ifndef _CTPP2_DATA_BUFFER_HPP__
#define _CTPP2_DATA_BUFFER_HPP__ 1

/**
  @file DataBuffer.hpp
  @brief Growable data buffer
*/

#include "CTPP2Types.h"

namespace CTPP
{

/**
  @class DataBuffer DataBuffer.hpp <DataBuffer.hpp>
  @brief Growable data buffer
*/
class CTPP2DECL DataBuffer
{
public:
	static const UINT_64 BUFSIZE;
	static const UINT_64 npos;

	/**
	  @brief iInitialSize - Initial size of buffer
	*/
	DataBuffer(const UINT_64  iInitialSize = BUFSIZE);

	/**
	  @brief Reserve specified number of bytes
	  @param iBytes - Number of bytes
	  @return reference to self
	*/
	DataBuffer & Reserve(const UINT_64  iBytes);

	/**
	  @brief Force size of buffer to specified value
	  @param iNewSize - New bufer size
	  @return iSize, if internal buffer can fit data, npos - otherwise
	*/
	UINT_64 SetSize(const UINT_64  iNewSize);

	/**
	  @brief Assign character to the buffer
	  @param chData - Character to set
	  @return reference to self
	*/
	DataBuffer & Assign(CHAR_8  chData);

	/**
	  @brief Assign data buffer
	  @param vBuffer - Buffer with data
	  @param iBufferSize - Buffer size
	  @return reference to self
	*/
	DataBuffer & Assign(const void     * vBuffer,
	                    const UINT_64    iBufferSize);

	/**
	  @brief Assign range of characters
	  @param itStart - Start iterator
	  @param itEnd - End iterator
	  @return reference to self
	*/
	template <typename T>DataBuffer & Assign(const T  & itStart,
	                                         const T  & itEnd)
	{
		Clear();

		T  itTMP(itStart);
		while (itTMP != itEnd) { Append(*itTMP++); }

	return *this;
	}

	/**
	  @brief Assign data
	  @param oData - data to assign
	  @return reference to self
	*/
	template <typename T>DataBuffer & Assign(const T  & oData)
	{
		return Assign(oData.data(), oData.size());
	}

	/**
	  @brief Assign ASCIZ string
	  @param szBuffer - ASCIZ string
	  @return reference to self
	*/
	DataBuffer & Assign(CCHAR_P  szBuffer);
	/**
	  @brief Append a character to the buffer
	  @param chData - Character to append
	  @return reference to self
	*/
	DataBuffer & Append(CHAR_8  chData);

	/**
	  @brief Append data buffer
	  @param vBuffer - Buffer with data
	  @param iBufferSize - Buffer size
	  @return reference to self
	*/
	DataBuffer & Append(const void     * vBuffer,
	                    const UINT_64    iBufferSize);

	/**
	  @brief Append data buffer
	  @param vBuffer - Buffer with data
	  @param iBufferSize - Buffer size
	  @return reference to self
	*/
	DataBuffer & Append(const DataBuffer  & oDataBuffer);

	/**
	  @brief Append range of characters
	  @param itStart - Start iterator
	  @param itEnd - End iterator
	  @return reference to self
	*/
	template <typename T>DataBuffer & Append(const T  & itStart,
	                                         const T  & itEnd)
	{
		T  itTMP(itStart);
		while (itTMP != itEnd) { Append(*itTMP++); }

	return *this;
	}

	/**
	  @brief Assign data
	  @param oData - data to assign
	  @return reference to self
	*/
	template <typename T>DataBuffer & Append(const T  & oData)
	{
		return Append(oData.data(), oData.size());
	}

	/**
	  @brief Append ASCIZ string
	  @param szBuffer - ASCIZ string
	  @return reference to self
	*/
	DataBuffer & Append(CCHAR_P  szBuffer);

	/**
	  @brief Get data buffer
	  @param iStartPos - offset from start of buffer
	  @return NON-ASCIZ data buffer started from iStartPos
	*/
	CCHAR_P Data(const UINT_64  iStartPos = 0) const;

	/**
	  @brief Find character
	  @param chChar - char to find
	  @param iPos - start position
	*/
	UINT_64 Find(const UCHAR_8  chChar,
	             const UINT_64  iPos = 0);

	/**
	  @brief Get data size
	  @return Size of data buffer
	*/
	UINT_64 Size() const;

	/**
	  @brief Get reference to specified element
	  @param iPos - element position
	  @return Reference to specified element
	*/
	CHAR_8 &operator[](const UINT_64 iPos);

	/**
	  @brief Get reference to specified element
	  @param iPos - element position
	  @return Reference to specified element
	*/
	const CHAR_8 &operator[](const UINT_64 iPos) const;

	/**
	  @brief Clear buffer
	*/
	void Clear();

	/**
	  @brief Cut buffer
	*/
	void Cut(const UINT_64 iCutBytes);

	/**
	  @brief A destructor
	*/
	~DataBuffer() throw();
private:
	// Does not exist
	DataBuffer(const DataBuffer  & oRhs);
	DataBuffer& operator=(const DataBuffer  & oRhs);

	/** Data buffer        */
	CHAR_P      sData;
	/** Used size          */
	UINT_64     iUsedSize;
	/** Actual buffer size */
	UINT_64     iSize;
};

} // namespace CTPP
#endif // _CTPP2_DATA_BUFFER_HPP__
// End.
