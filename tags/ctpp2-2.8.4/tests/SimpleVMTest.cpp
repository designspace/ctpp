/*-
 * Copyright (c) 2004 - 2010 CTPP Team
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
 *      SimpleVMTest.hpp
 *
 * $CTPP$
 */
#include <CDT.hpp>
#include <CTPP2FileLogger.hpp>
#include <CTPP2SimpleVM.hpp>
#include <CTPP2VMFileLoader.hpp>

using namespace CTPP;

// test case
int main(int argc, char ** argv)
{
	if (argc != 2) { fprintf(stderr, "usage: %s file.ct2\n", argv[0]); return EX_USAGE; }

	SimpleVM oSimpleVM;

	// Create data
	CDT oHello;
	oHello["hello"] =  "Hello, World!";

	// Load template file
	VMFileLoader oLoader(argv[1]);

	// Create logger object
	FileLogger oLogger(stderr);

	// Execute template and write data to standard output
	oSimpleVM.Run(oHello, oLoader, stdout, oLogger);

	// Execute template and write data to string
	std::string sResult;
	oSimpleVM.Run(oHello, oLoader, sResult, oLogger);

	// Make Valgrind happy
	fclose(stdin);
	fclose(stdout);
	fclose(stderr);
}
// End.
