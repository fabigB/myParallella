#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>  

using namespace std;

vector<string> split(string const &input) { 
		vector<string> vecString;
        stringstream   mySstream( input );
        string         tmp;

        while( getline(mySstream, tmp,' ' ) ) {
            vecString.push_back( tmp );
        }

        return vecString;
}

int main(void) {
	ofstream outFile;
	outFile.open("picIn.pgm");  	
	//outFile.open ("picInvert.pgm");
	string line; 
	vector<string> lineVec;
	int counter = 0;
  	ifstream inFile ("in.pgm");
	if (inFile.is_open()) {
		while ( getline (inFile,line) ) {
			if (counter < 3) {
				//Just copy first three lines
				outFile << line << endl;
				counter++;
			}
			else {
				lineVec = split(line);			
				for(unsigned i=0; i < lineVec.size();i++){
					//int invert = 255-stoi(lineVec[i]);					
					if(lineVec[i] != "" && lineVec[i] != " ")					
						outFile << lineVec[i] << endl;
				}
			}						
		}
		inFile.close();
	}
	else cout << "Unable to open file" << endl; 

	outFile.close();
	cout << "Done writing result" << endl;

    return 0;
}


