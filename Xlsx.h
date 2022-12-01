#pragma once
#include <iostream>
#include "libxl.h"

libxl::Sheet* getSheetByName(libxl::Book* book, const wchar_t* name);