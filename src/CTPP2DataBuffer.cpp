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
#include "CTPP2DataBuffer.hpp"
#include "CTPP2Exception.hpp"

#include <stdlib.h>
#include <string.h>

namespace CTPP
{

//
// Initial buffer size
//
const UINT_64 DataBuffer::BUFSIZE = 131072;
const UINT_64 DataBuffer::npos = (UINT_64)(-1);

//
// Constructor
//
DataBuffer::DataBuffer(const UINT_64 iInitialSize): sData(NULL), iUsedSize(0), iSize(iInitialSize)
{
	if (iSize != 0) { sData = (CHAR_P)malloc(iSize); }
}

//
// Reserve specified number of bytes
//
DataBuffer & DataBuffer::Reserve(const UINT_64  iBytes)
{
	if (iBytes > iSize)
	{
		const UINT_64 iNewSize = iBytes;
		CHAR_P sTMP = (CHAR_P)realloc(sData, iNewSize);
		if (sTMP == NULL)
		{
			// Handle error
			throw CTPPNoMemoryError();
			// Never happened
			return *this;
		}
		iSize = iNewSize;
		sData = sTMP;
	}
return *this;
}

//
// Force size of buffer to specified value
//
UINT_64 DataBuffer::SetSize(const UINT_64  iNewSize)
{
	if (iNewSize > iSize) { return DataBuffer::npos; }
	iUsedSize = iNewSize;

return iNewSize;
}

//
// Append a character to the buffer
//
DataBuffer & DataBuffer::Assign(CHAR_8  chData)
{
	Clear();

return Append(chData);
}

//
// Append data buffer
//
DataBuffer  & DataBuffer::Assign(const void     * vBuffer,
                                 const UINT_64    iBufferSize)
{
	Clear();

return Append(vBuffer, iBufferSize);
}

//
// Append ASCIZ string
//
DataBuffer  & DataBuffer::Assign(CCHAR_P  szBuffer)
{
	Clear();

return Append(szBuffer);
}

//
// Append a character to the buffer
//
DataBuffer  & DataBuffer::Append(CHAR_8  chData)
{
	if (iUsedSize == iSize)
	{
		const UINT_64 iNewSize = iSize * 2;
		CHAR_P sTMP = (CHAR_P)realloc(sData, iNewSize);
		if (sTMP == NULL)
		{
			// Handle error
			return *this;
		}
		iSize = iNewSize;
		sData = sTMP;
	}
	sData[iUsedSize++] = chData;
return *this;
}

//
// Append data buffer
//
DataBuffer  & DataBuffer::Append(const void     * vBuffer,
                                 const UINT_64    iBufferSize)
{
	const UINT_64 iNewSize = iUsedSize + iBufferSize;
	if (iNewSize > iSize)
	{
		CHAR_P sTMP = (CHAR_P)realloc(sData, iNewSize);
		if (sTMP == NULL)
		{
			// Handle error
			return *this;
		}
		iSize = iNewSize;
		sData = sTMP;
	}

	memcpy(sData + iUsedSize, vBuffer, iBufferSize);
	iUsedSize = iNewSize;

return *this;
}

//
// Append data buffer
//
DataBuffer & DataBuffer::Append(const DataBuffer  & oDataBuffer) { return Append(oDataBuffer.Data(), oDataBuffer.Size()); }

//
// Append ASCIZ string
//
DataBuffer  & DataBuffer::Append(CCHAR_P  szBuffer)
{
	return Append((void*)szBuffer, strlen(szBuffer));
}

//
// Get data buffer
//
CCHAR_P DataBuffer::Data(const UINT_64  iStartPos) const { return sData + iStartPos; }

//
// Find character
//
UINT_64 DataBuffer::Find(const UCHAR_8  chChar,
                         const UINT_64  iStartPos)
{
	if (iStartPos >= iUsedSize) { return DataBuffer::npos; }

	for (UINT_64 iPos = iStartPos; iPos < iUsedSize; ++iPos)
	{
		if (sData[iPos] == chChar) { return iPos; }
	}

return DataBuffer::npos;
}

//
// Get data size
//
UINT_64 DataBuffer::Size() const { return iUsedSize; }

//
// Get reference to specified element
//
CHAR_8 & DataBuffer::operator[](const UINT_64 iPos) { return sData[iPos]; }

//
// Get reference to specified element
//
const CHAR_8 & DataBuffer::operator[](const UINT_64 iPos) const { return sData[iPos]; }

//
// Clear buffer
//
void DataBuffer::Clear() { iUsedSize = 0; }

//
// Cut buffer
//
void DataBuffer::Cut(const UINT_64 iCutBytes)
{
	if (iCutBytes <= iUsedSize) { iUsedSize -= iCutBytes; }
}

//
// Constructor
//
DataBuffer::~DataBuffer() throw() { free(sData); }

} // namespace CTPP
// End.
