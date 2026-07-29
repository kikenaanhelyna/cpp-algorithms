/*
This program reads student numbers from a text file.
First, it counts the number of lines in the file, then returns to the beginning 
to read the content again and store each line as a string.
Next, it uses sort function from the library to sort the lines.
Main for loop iterates through every line, and the inner loop checks the uniqueness of 
the digits within those lines.
This code is faster, with a time complexity of O(N log N * M), but it requires much 
more memory and therefore operates under relaxed constant space conditions.
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

        sort(lines, lines + lineCount);

        cout << "SortedLines" << "\n";
        for (int i = 0; i < lineCount; i++) {
            cout << lines[i] << "\n";
        }

        int minCount = 0;
        for (int l = 0; l < lineCount -1; l++) {
            
                int count = 0;

                for (int i = 0; i < 9; i++) {
                    if (lines[l][i] == lines[l+1][i]) {

                        count++;
                    }
                    else {
                        count++;
                        break;
                    }

                }
                if (count +1 > minCount) minCount = count;
            
        }


        cout << "\nDstinqtCount" << "\n";
        cout << minCount << "\n\n";

        cout << "DistinqtNumberas" << "\n";
        for (int i = 0; i < lineCount; i++) {
            newString = lines[i].substr(0, minCount);
            cout << newString << "\n";
        }
        return lines;
    }
private:


    string newString;
    fstream file;
    string* lines;
    int lineCount;
};



int main() {
    FileReader reader("Text.txt");

    reader.StudentNumbers();
    return 0;
}