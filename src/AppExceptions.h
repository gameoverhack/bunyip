/*
 *  AppExceptions.h
 *  Bunyip
 *
 *  Created by ollie on 13/07/11. Modified by Gingold 24/08/11
 *  Copyright 2011 Oliver Marriott. All rights reserved.
 *
 */

#ifndef _H_APPEXCEPTIONS
#define _H_APPEXCEPTIONS

#include <string>
#include <vector>
using namespace std;

// Jungle execption super class
class AppException {

public:

	AppException(string message) {
		_message = message;
	}

	string _message;
};

// Thrown when we can't parse the xml for whatever reason
// used to know when we should try a xml rebuild
class GenericXMLParseException : public AppException {

public:

	GenericXMLParseException(string message) : AppException(message) {
		// nothing?
	}
};

// Thrown when metadata (dates,sizes) don't match between the xml and hdd
class MetadataMismatchException : public AppException {

public:

	MetadataMismatchException(string message) : AppException(message) {
		// nothing
	}
};


#endif
