#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <assert.h>
#include <ctype.h>

const char INPUT_FILE[] = "text.txt";
const char OUTPUT_FILE[] = "sorted.txt";
const int FILE_ERROR1 = -1;
const char INPUT_FILE_TEST[] = "test_text.txt";
const char OUTPUT_FILE_TEST[] = "test_sorted.txt";


int PrintTextInFile(const char *fileName, const char **text, const size_t numOfStrings);
int PrintTextInFileTest();
int FillArrayOfStrings(char **arrayToFill, char *buffer, size_t numOfStrings);
int FillArrayOfStringsTest();
int Sort(void *arrayForSort, size_t numOfElements, size_t sizeOfElement, int (*compare)(const void *, const void *));
int SortTest();
int StrcmpWithoutSpace(const char *p1, const char *p2);
int StrcmpWithoutSpaceTest();
int CompareTest();
int Compare(const void *left, const void *right);
int StrCnt(FILE *textForProcess, int *NumberOfLines);
char* GetTextFromFile(const char *nameFile);
size_t SizeOfFile(const char *nameFile);
size_t CountOfStrings(char *text);
int CountOfStringsTest();
int main (){

//    CountOfStringsTest();
//    CompareTest();
//    StrcmpWithoutSpaceTest();
//    FillArrayOfStringsTest();
//    PrintTextInFileTest();
//    SortTest();
//printf("\n\n\n\n");
    char *buf = GetTextFromFile(INPUT_FILE);
//    printf("%s", buf);
    size_t nStrings = CountOfStrings(buf);
    char **text = (char **) calloc(nStrings, sizeof(**text));
    FillArrayOfStrings(text, buf, nStrings);

    printf("%zu\n", nStrings);
    for(size_t i = 0; i < nStrings; i++) {
        printf("%s\n", text[1]);
    }

    qsort(text, nStrings, sizeof(char*), Compare);
    PrintTextInFile(OUTPUT_FILE, (const char**)text, nStrings);



    return 0;




/*GetText (fr, nLines, text);
    StraightSort (text);
    ReverseSort (text);
    SourceText  (text);
*/
}

///This function counts the number of strings(number of '\n's) in array of (char)
/// and changes '\n' to '\0'
/*---big function---*/
size_t CountOfStrings(char *text){
    assert(text);

    size_t countc = 0;

    char* tmp = strchr(text, '\n');
    while(tmp /*&& tmp[1] != '\0'*/){
        *tmp = '\0';
        text = tmp + 1;
        countc++;
        tmp = strchr(text, '\n');
    }

    if(tmp = strchr(text, '\0'))
        countc++;

    return countc;

}

///This function fill array *fileBuf with all chars from file
///Return value: count of chars read(count of bytes read), (int) type
/*---big function---*/
char* GetTextFromFile(const char *nameFile){
    FILE *fileToRead = fopen(nameFile, "r");

    assert(fileToRead);

    size_t sizeFile = SizeOfFile(nameFile);

    char * bufFile = (char*)calloc(sizeFile, sizeof(*bufFile));
    fread(bufFile, sizeFile, sizeof(*bufFile), fileToRead);

    fclose(fileToRead);

    return bufFile;
}

size_t SizeOfFile(const char *nameFile){
    assert(nameFile);

    struct stat stbuf;
    stat(nameFile, &stbuf);
    int sizeFile = stbuf.st_size;

    return sizeFile;

}
/*---big function---*/
int CountOfStringsTest(){
    printf("TESTING...");

    char text1[] = "aaaaaaaa\nbbbbbbbbbb\ncccccccccc\ndddddddddd";
    char text2[] = "aaaaaaa\nbbbbbbbbbb\ncccccccccc";
    char text3[] = "aaaaaaaa\nbbbbbbbbbb\ncccccccccc\ndddddddddd\n";

    int tmp = 0;

//---------------------Test 1--------------------
    tmp = CountOfStrings(text1);

    printf("Test 1: ");

    if(tmp == 4)
        printf("[OK]\n");
    else
        printf("[WRONG] : text :\naaaaaaaa\\nbbbbbbbbbb\\ncccccccccc\\ndddddddddd\n, expected : 4, received : %d", tmp);
//-----------------------------------------------

//---------------------Test 2--------------------
    tmp = CountOfStrings(text2);

    printf("Test 2: ");

    if(tmp == 3)
        printf("[OK]\n");
    else
        printf("[WRONG] : text :\naaaaaaa\\nbbbbbbbbbb\\ncccccccccc\n, expected : 1, received : %d", tmp);
//-----------------------------------------------

//---------------------Test 3--------------------
    tmp = CountOfStrings(text3);

    printf("Test 3: ");

    if(tmp == 5)
        printf("[OK]\n");
    else
        printf("[WRONG] : text :\naaaaaaaa\\nbbbbbbbbbb\\ncccccccccc\\ndddddddddd\\n\n, expected : 4, received : %d", tmp);
//-----------------------------------------------

    return 0;
}

int Compare(const void *left, const void *right){
    char *left_char = (char *) left;
    char *right_char = (char*) right;

    int result = StrcmpWithoutSpace(left_char, right_char);
    return result;
}

int CompareTest(){
    char str11[] = "aaaaaaa";
    char str12[] = "bbbbbbb";
    char str21[] = "ddddddd";
    char str22[] = "cccccccc";
    int res = 0;

    printf("\t---Testing of CompareTest()---\n");
//---------------------Test 1--------------------
    printf("Test 1: ");

    if(Compare(str11, str12) < 0)
        printf("[OK]\n");
    else
        printf("[WRONG]");
//-----------------------------------------------

//---------------------Test 2--------------------
    printf("Test 2: ");

    if(Compare(str21, str22) > 0)
        printf("[OK]\n");
    else
        printf("[WRONG]");
//-----------------------------------------------
}

int StrcmpWithoutSpace(const char *p1, const char *p2){

    const unsigned char *s1 = (const unsigned char *) p1;
    const unsigned char *s2 = (const unsigned char *) p2;
    unsigned char c1, c2;

    do
    {
        while(!isdigit(*s1) && !isalpha(*s1))
                *s1++;
        c1 = (unsigned char) *s1++;
        if(isupper(c1)) c1 = tolower(c1);

        while(!isdigit(*s2) && !isalpha(*s2))
            *s2++;
        c2 = (unsigned char) *s2++;
        if(isupper(c2)) c2 = tolower(c2);

        if (c1 == '\0')
            return c1 - c2;
    }
    while (c1 == c2);

    return c1 - c2;
}
/*---big function---*/
int Sort(void *arrayForSort, size_t numOfElements, size_t sizeOfElement, int (*compare)(const void *, const void *)){

    qsort(arrayForSort, numOfElements, sizeOfElement, compare);

    return 0;

}

int SortTest(){
    const size_t nStrings = 5;
    char **text = (char**) calloc(nStrings, sizeof(**text));

    printf("\tTesting Sort() function\n");

    printf("Test 1 :");

    text[0] ="ddddd";
    text[1] ="bbbbb";
    text[2] ="ccccc";
    text[3] ="aaaaa";
    text[4] ="eeeee";
    Sort(text, nStrings, sizeof(char*), Compare);

    printf("function Sort is complete\n");

    bool flag = (strcmp(text[0], "aaaaa") || strcmp(text[1], "bbbbb") || strcmp(text[2], "ccccc") || strcmp(text[3], "ddddd") || strcmp(text[4], "eeeee"));
    if(!flag)
        printf("[OK]");
    else{
        printf("[WRONG] : \n");
        printf("elements :\n\ttext[0] = \"ddddd\"\n\ttext[1] = \"bbbbb\"\n\ttext[2] = \"ccccc\"\n\ttext[3] = \"aaaaa\"\n\ttext[4] = \"eeeee\"\n");
        printf("expected :\n\ttext[0] = \"aaaaa\"\n\ttext[1] = \"bbbbb\"\n\ttext[2] = \"ccccc\"\n\ttext[3] = \"ddddd\"\n\ttext[4] = \"eeeee\"\n");
        printf("received :\n\ttext[0] = \"%s\"\n\ttext[1] = \"%s\"\n\ttext[2] =  \"%s\"\n\ttext[3] = \"%s\"\n\ttext[4] = \"%s\"\n", text[0], text[1], text[2], text[3], text[4]);

    }

}

int StrcmpWithoutSpaceTest(){


    char str11[] = "abc e";
    char str12[] = "abcde";
    char str21[] = "bbbbb";
    char str22[] = "aaaaa";
    int res = 0;

    printf("\t---Testing StrcmpWithoutSpace()---\n");
//---------------------Test 1--------------------
    printf("Test 1: ");

    res = StrcmpWithoutSpace(str11, str12);

    if(res > 0)
        printf("[OK]\n");
    else
        printf("[WRONG] : elements : \"%s\", \"%s\"  expected : res > 0, received : res = %d", res);

//-----------------------------------------------

//---------------------Test 2--------------------
    printf("Test 2: ");

    res = StrcmpWithoutSpace(str21, str22);

    if(res > 0)
        printf("[OK]\n");
    else
        printf("[WRONG] : elements : \"%s\", \"%s\"  expected : res > 0, received : res = %d", res);

//-----------------------------------------------
    return 0;
}

int FillArrayOfStrings(char** arrayToFill, char *buffer, size_t numOfStrings){
    size_t index = 0;/
    char * beginOfStr = buffer;
    while(index < numOfStrings ){
        arrayToFill[index] = beginOfStr;
        beginOfStr = strchr(beginOfStr, '\0') + 1;
        //printf("%s\n", arrayToFill[index]);
        index++;
    }
    return 0;
}

int FillArrayOfStringsTest(){

    char *str = "aaaaaaa\0bbbbbbb\0ccccccccc";
    size_t num = 3;
    char **text = (char**) calloc(num, sizeof(**text));
    int res = FillArrayOfStrings(text, str, num);
    if(strcmp(text[0], "aaaaaaa") == 0 && strcmp(text[1], "bbbbbbb") == 0 && strcmp(text[2], "ccccccccc") == 0)
        printf("[OK]");
    else
        printf("[WRONG] : string = \"aaaaaaa\\0bbbbbbb\\0ccccccccc\", expected text[0] = \"aaaaaaa\", text[1] = \"bbbbbbb\", text[2] = \"ccccccccc\"\nreceived : text[0] = %s, text[1] = %s, text[2] = %s,", text[0], text[1], text[2]);

    return 0;

}

int PrintTextInFile(const char *fileName, const char **text, const size_t numOfStrings){
    assert(fileName);
    assert(text);

    FILE *stream = fopen(fileName, "w");
    size_t printedStrings = 0;
    while(printedStrings < numOfStrings){
        fprintf(stream, "%s\n", text[printedStrings]);
        printedStrings++;
    }
    return 0;
}

int PrintTextInFileTest(){
    const size_t numOfStrs = 5;
    char **text = (char **) calloc(numOfStrs, sizeof(**text));
    text[0] = "aaaaaaaaaa\0";
    text[1] = "bbbbbbbbb\0";
    text[2] = "ccccccccccc\0";
    text[3] = "ddddddddd\0";
    text[4] = "eeeeeeeeee\0";
    PrintTextInFile(OUTPUT_FILE_TEST, (const char**)text, numOfStrs);
    return 0;
}
