#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

/*
io practices - read, write, error handling (perror)

write a function...
    that automatically create file, 
    prompts 2 things as following:
    1. ask filename
    2. ask content input
    finally, automatically closes

understand that ofstream & ifstream instance  .fail() will return boolean
utilize that in if-statement

understand too, getline not only get the whole line of characters, but also return boolean
utilize that in statement as well
** requirement to use getline:
1. include<string>
2. pass string as argument

*** use endl minimally
*** use '\n' instead of "\n"

*/

// global variables
ifstream iFile;
ofstream oFile;

void writeFile(){
    cout << "Writing file...\n";
    cout << "enter filename: ";
    string filename;
    cin >> filename;
    cout << '\n';

    oFile.open(filename);

    // quit function if ofstream opening fails
    if(oFile.fail()){
        perror(filename.c_str()); // only need filename as argument
        return;
    }
    
    // write content to oFile
    cout << "enter content:\n"
            "(press ` to quit)\n";
    
    // '`' = quit-key, since almost noyone uses it
    char quit_key = '`';
    // '\n' = initializer-key, since it is "almost empty"
    char key = '\n'; 

    char buff[100] = {'\r'};
    int buff_ptr = 0;

    while( key != quit_key ){

        switch (key){

            case '\b':
                // backspace response in print-console
                cout << key;

                // reset char in current buffer position to "empty char"
                buff[buff_ptr] = '\0';
                // retrieve previous pointer position
                buff_ptr--;

                break;

            // only enter-key will actually write the buffer to file
            case '\r':
                // print to console, for debugging
                cout << '\n'; 
                buff[buff_ptr] = '\r';

                // using '\r' as terminated-char
                for (int i=0; buff[i] !='\r'; i++){
                    // write to file
                    oFile << buff[i];
                }

                // since for loop stops before enter-key, 
                // hence need to actually write it to file
                oFile << '\n';

                // reset buff ptr
                buff_ptr = 0;
                // reset all char in buff array, 
                // '\r' is chosen, because it is terminated-char
                // so when looping buff-array again, 
                // loop will be terminated immediately, except if other keys are pressed
                buff[100] = '\r';
                
                break;

            default:
                // print to console, for debugging
                cout << key; 
                // storing every keys into buff-array
                buff[buff_ptr] = key;
                buff_ptr++;
        }
        key = getch();
    }
    cin.clear();
    oFile.close();

}

void readFile(){
    cout << "Reading file...\n";
    cout << "enter filename to read: ";
    string filename;
    cin >> filename;
    cout << '\n';

    iFile.open(filename);
}

int main()
{
    writeFile();

    return 0;
}