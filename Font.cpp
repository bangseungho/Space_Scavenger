#include "Font.h"

void Font::Init()
{
//    HFONT   font;     // Windows Font ID
//    HFONT   oldfont;  // Used For Good House Keeping
//
//    base = glGenLists(96);  // Storage For 96 Characters
//
//    font = CreateFont(-size, // Height Of Fonts
//        0,              // Width Of Font
//        0,              // Angle Of Escapement
//        0,              // Orientation Angle
//        FW_BOLD,        // Font Weight
//        FALSE,          // Italic     (취소선)
//        FALSE,          // Underline (밑줄)
//        FALSE,          // Strikeout (취소선)
//        ANSI_CHARSET,   // Character Set Identifier
//        OUT_TT_PRECIS,  // Output Precision
//        CLIP_DEFAULT_PRECIS,        // Clipping Precision
//        ANTIALIASED_QUALITY,        // Output Quality
//        FF_DONTCARE | DEFAULT_PITCH,  // Family And Pitch
//        fileName);         // Font Name
//
//    oldfont = (HFONT)SelectObject(hDC, font); // Selects The Font We Want
//    wglUseFontBitmaps(hDC, 32, 96, base);     // Builds 96 Characters Starting At Character 32
//    SelectObject(hDC, oldfont);               // Selects The Font We Want
//    DeleteObject(font);
}
