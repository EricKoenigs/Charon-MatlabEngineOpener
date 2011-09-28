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
/** \file MatlabEngineOpener.cpp
 *  Implementation of parameter class MatlabEngineOpener.
 *  \author <a href="mailto:e.koenigs@stud.uni-heidelberg.de">
 *      Eric Koenigs</a>
 *  \date 20.09.2011
 */

#include <charon-core/ParameteredObject.hxx>
#include "MatlabEngineOpener.h"

MatlabEngineOpener::MatlabEngineOpener(const std::string& name) :
		ParameteredObject(
			"MatlabEngineOpener", name,
			"<h2>Opens the Matlab engine</h2><br>"
			"Open the Matlab engine and return the Engine pointer for other "
			"plugins to use it. Also closes the engine when all plugins are "
			"unloaded."
		)
{

	ParameteredObject::_addOutputSlot(
		engine, "engine",
		"A Matlab Engine pointer",
		"Engine*");

	ParameteredObject::_addParameter< std::string >(
		startcmd, "startcmd",
		"Only relevant for UNIX. Leave the default on Windows. See Matlab's "
		"help for engOpen().",
		"NULL", "string");

	_ep = NULL;


}

void MatlabEngineOpener::execute() {
	PARAMETEREDOBJECT_AVOID_REEXECUTION;
	ParameteredObject::execute();
	
	Engine* ep;

	std::string cmd = startcmd();

	if (cmd == "NULL") {
		ep = engOpen(NULL);
	}
	else {
		ep = engOpen(cmd.c_str());
	}

	if (ep == NULL) {
		throw std::runtime_error("Failed to open Matlab engine. "
				"engOpen() returned NULL.");
	};
	engine() = ep;
	// Set the private engine pointer.
	_ep = ep;
	
}

MatlabEngineOpener::~MatlabEngineOpener() {
	// Check if the plugin was actually used in a workflow
	// or just constructed and destroyed by the plugin loader.
	if (!executed()) {
		return;
	}
	if (_ep == NULL) {
		sout	<<	"Warning: The engine pointer is NULL. You might "
					"have a Matlab Zombie now."
				<< 	std::endl;
	}
	else {
		if (engClose(_ep) != 0) {
			sout	<<	"Warning: MatlabEngineOpener failed to close "
						"the Matlab engine."
					<<	std::endl;
		}
		else {
			sout	<<	"Successfully exterminated "
						"the evil Matlab Zombie."
					<< 	std::endl;
		}
	}
}

// the following functions are needed
// for class MatlabEngineOpener to work as a charon plugin.
extern "C" matlabengineopener_DECLDIR ParameteredObject*
		create(const std::string& name, template_type) {
	return new MatlabEngineOpener(name);
}

extern "C" matlabengineopener_DECLDIR void destroy(ParameteredObject* b) {
	delete b;
}
