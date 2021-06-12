#ifndef RNA_H
#define RNA_H
#include "DNA.h"
#include "Sequence.h"
#include "Codons.h"
class DNA;

enum RNA_Type {mRNA, pre_mRNA, mRNA_exon, mRNA_intron};
class RNA : public Sequence
{
  	private:
        RNA_Type type;
  	public:
 	 	// constructors and destructor
        RNA();
        RNA(char * seq1, RNA_Type atype);
        RNA(const RNA& rhs);
        char * getseq()const;
        ~RNA();
 	 	// function to be overridden to print all the RNA information
        void Print();
 	 	// function to convert the RNA sequence into protein sequence
        // using the codonsTable object
     //   Protein ConvertToProtein(const CodonsTable & table);
 	 	// function to convert the RNA sequence back to DNA
        DNA ConvertToDNA();
        char converttoprotien(char * value1,Codon codons);
        bool operator== (const RNA& other)const ;
        bool operator!= (const RNA& other)const ;
        RNA  operator+ (const RNA& other)const ;
};

#endif // RNA_H
