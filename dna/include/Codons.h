#ifndef CODONS_H
#define CODONS_H
#include <string>
#include <fstream>
using namespace std;
// struct representing a codon of 3 DNA/RNA characters and ‘\0’
struct Codon
{
  	char value[4];    	    // 4th location for null character
    char AminoAcid;  	    // corresponding AminoAcid according to Table
};
int parts(char* array, int start, int end, int steps);

// need to create one object of that class to load the AminoAcids table
// into memory
class CodonsTable
{
  	private:
        Codon codons[64];
   	public:
 	 	// constructors and destructor
        CodonsTable();
        ~CodonsTable();
 	 	// function to load all codons from the given text file
        void LoadCodonsFromFile(string codonsFileName);
        void print();
        char * getAminoAcid(char * value1);
        void setCodon(char * value, char AminoAcid, int index);
};

#endif // CODONS_H
