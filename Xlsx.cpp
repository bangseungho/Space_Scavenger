#include "Xlsx.h"

libxl::Sheet* getSheetByName(libxl::Book* book, const wchar_t* name)
{
    for (int i = 0; i < book->sheetCount(); ++i)
    {
        if (wcscmp(book->getSheet(i)->name(), name) == 0)
        {
            return book->getSheet(i);
        }
    }
    return 0;
}