#include "TextLibrary.h"

int main (){

//------------------Tests-------------------
//    CountOfStringsTest ();
//    CompareTest ();
//    StrcmpWithoutSpaceTest ();
//    FillArrayOfStringsTest ();
//    PrintTextInFileTest ();
//    SortTest ();
//-------------------------------------------

    char *buf = GetTextFromFile (INPUT_FILE);

    size_t nStrings = CountOfStrings (buf);

    char **text = (char **) calloc (nStrings, sizeof(**text));

    FillArrayOfStrings (text, buf, nStrings);

    qsort (text, nStrings, sizeof(char*), Compare);

    PrintTextInFile (OUTPUT_FILE, (const char**)text, nStrings);

    return 0;
}

