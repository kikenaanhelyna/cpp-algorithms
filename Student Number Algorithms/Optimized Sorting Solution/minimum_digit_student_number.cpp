/*
This program reads student numbers from a text file.
First, it counts the number of lines in the file, then returns to the beginning 
to read the content again and store each line as a string.
Next, it uses nested loops: the first loop iterates through every line, the second
compares it with line that follows, and the third loop checks the uniqueness of 
the digits within those lines.
This code is slover, with a time complexity of O(N^2 * M), 
it requires very not much memory and therefore operates under strict constant space 
conditions.
*/


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

class FileReader {

public:
    FileReader(const string& filename) {
        file.open(filename, ios::in);
        if (!file) {
            cout << "Sorry, I can’t open your file\n";
            lines = nullptr;
            lineCount = 0;
            return;
        }

        string temp;
        lineCount = 0;
        while (getline(file, temp))
            lineCount++;

        file.clear();
        file.seekg(0, ios::beg);

        lines = new string[lineCount];

        int i = 0;
        while (getline(file, temp) && i < lineCount) {
           lines[i] = temp;
            i++;
        }

        file.close();
    }

    ~FileReader() {
        delete[] lines;  
    }
    const string* StudentNumbers() {
        
        for (int i = 0; i < lineCount; i++) {
            reverse(lines[i].begin(), lines[i].end());
        }

        int minCount = 0;


            for (int l = 0; l < lineCount; l++) {
                for (int n = l + 1; n < lineCount; n++) {

                    const string& a = lines[l];
                    const string& b = lines[n];
                    int count = 0;
                 //   int len = min((int)a.size(), (int)b.size());
                    
                    for (int i = 0; i < 9; i++) {
                        if (a[i] == b[i]) {
                           
                            count++;
                        }
                        else {  
                      
                            break;
                        } 

                    }
                    if (count + 1 > minCount)
                        minCount = count + 1;
                }
             }


            cout << "\nDstinqtCount" << "\n";
            cout << minCount << "\n\n";

            cout << "DistinqtNumberas" << "\n";
            for (int i = 0; i < lineCount; i++) {
                int take = min((int)lines[i].size(), minCount);
                cout << lines[i].substr(0, take) << "\n";
            }
        return lines;
    }    
private:
    
    fstream file;
    string* lines;
    int lineCount;
};



int main() {
    FileReader reader("Text.txt");

    reader.StudentNumbers();
    return 0;
}
