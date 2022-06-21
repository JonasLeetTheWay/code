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
    cout << "\t enter filename (type \"none\" if dont want to write): ";
    string filename;
    cin >> filename;
    if (filename == "none") return;

    oFile.open(filename);

    // quit function if ofstream opening fails
    if(oFile.fail()){
        perror(filename.c_str()); // only need filename as argument
        return;
    }
    
    // write content to oFile
    cout << "\t enter content:\n"
            "(press ` to quit)\n";
    
    // '`' = quit-key, since almost noyone uses it
    char quit_key = '`';
    // '\n' = initializer-key, since it is "almost empty"
    char key = '\n'; 

    char buff[100] = {'\r'};
    int buff_ptr = 0;

    cout << "--------------------------------------------------";
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

    cout << "Writing File is completed!" << "\n"
                                            "--------------------------------------------------"
                                            "\n\n";
}

void readFile(){
    cout << "Reading file...\n";
    cout << "\t enter filename (can include path, C:\\sample.txt): ";
    string filename;
    cin >> filename;
    cout << '\n';
    iFile.open(filename);

    char chs;

    // read current char and proceed to next char, until end of file
    cout << "--------------------------------------------------";
    while(!iFile.eof()) {
        iFile.get(chs);

        if(!iFile.eof()) {
            // print to console, for debugging
            cout << chs;
            // write to file
            oFile << chs;
        }
    }
    cin.clear();
    iFile.close();

    cout << "Reading File is completed!" << "\n"
                                            "--------------------------------------------------"
                                            "\n\n";
}

void promptRepeat() {

    cin.clear();

    char ch;
    cout << "Do you want to repeat? (y/n)\n";
    cin >> ch;

    while(ch == 'y') {
        cout << "Which operation to repeat?\n";
        switch(ch){
            case '1':
                writeFile();
                return; // end function directly, instead of switch statement
            case '2':
                readFile();
                return; // end function directly, instead of switch statement
            default:
                cout << "1 for writing file, 2 for reading file: ";
                cin >> ch; 
                cout << "You have entered operation: " << ch <<'\n';
        }
    }
    cin.clear();

    cout << "Prompting Repeat is completed!" << "\n"
                                            "--------------------------------------------------"
                                            "\n\n";
}

int main()
{
    writeFile();
    readFile();
    promptRepeat();

    return 0;
}