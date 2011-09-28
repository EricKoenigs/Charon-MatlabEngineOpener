/*  Copyright (C) 2011 Eric Koenigs

	This file is part of Charon.

	Charon is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Charon is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Charon.  If not, see <http://www.gnu.org/licenses/>.
*/
/** \file MatlabEngineOpener.h
 *  \author <a href="mailto:e.koenigs@stud.uni-heidelberg.de">
 *      Eric Koenigs</a>
 *  \date 20.09.2011
 *  Declaraion of parameter class MatlabEngineOpener.
 */
#ifndef _MATLABENGINEOPENER_H_
#define _MATLABENGINEOPENER_H_

#ifdef _MSC_VER
#ifdef matlabengineopener_EXPORTS
/// Visual C++ specific code
#define matlabengineopener_DECLDIR __declspec(dllexport)
#else
#define matlabengineopener_DECLDIR __declspec(dllimport)
#endif /*Export or import*/
#else
/// Not needed without MSVC
#define matlabengineopener_DECLDIR
#endif

#include <charon-core/ParameteredObject.h>
#include "engine.h"

/// Opens the Matlab engine
/** Open the Matlab engine and return the Engine pointer for other plugins to
 *  use it.
 */
class matlabengineopener_DECLDIR MatlabEngineOpener : public ParameteredObject {
private:
	Engine* _ep;
public:
	/// default constructor
	/// \param name             instance name
	MatlabEngineOpener(const std::string& name = "");

	/// An Engine pointer
	OutputSlot< Engine* > engine;

	/// Only relevant for UNIX. Leave the default on Windows. See Matlab's
	/// help for engOpen().
	Parameter< std::string > startcmd;

	/// Update object.
	virtual void execute();

	/// Close the engine.
	~MatlabEngineOpener();
};

#endif /* _MATLABENGINEOPENER_H_ */
