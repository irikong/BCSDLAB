#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>

#include "resource.h"
#include "Macro.h"
#include "Types.h"
#include "Flag.h"

#pragma comment(lib, "msimg32")

#define PI 3.141592f

// Path Key
#define ROOT_PATH		"RootPath"
#define TEXTURE_PATH	"TexturePath"

using namespace std;

template <typename T>
void Safe_Delete_VecList(T& p) {
	typename T::iterator iter; // T::iterater iter;
	typename T::iterator iterEnd = p.end(); // T::iterater iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter) {
		SAFE_DELETE((*iter));
	}

	p.clear();
}

template <typename T>
void Safe_Release_VecList(T& p) {
	typename T::iterator iter; // T::iterater iter;
	typename T::iterator iterEnd = p.end(); // T::iterater iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter) {
		SAFE_RELEASE((*iter));
	}

	p.clear();
}

template <typename T>
void Safe_Delete_Map(T& p) {
	typename T::iterator iter; // T::iterater iter;
	typename T::iterator iterEnd = p.end(); // T::iterater iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter) {
		SAFE_DELETE(iter->second);
	}

	p.clear();
}

template <typename T>
void Safe_Release_Map(T& p) {
	typename T::iterator iter; // T::iterater iter;
	typename T::iterator iterEnd = p.end(); // T::iterater iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter) {
		SAFE_RELEASE(iter->second);
	}

	p.clear();
}