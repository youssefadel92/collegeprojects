#ifndef PROTIEN_H
#define PROTIEN_H
#include "DNA.h"
#include "Sequence.h"
#include "Codons.h"
class DNA;


enum Protein_Type {Hormon, Enzyme, TF, Cellular_Function};

class Protein : public Sequence
{
  	private:
        Protein_Type type;
      public:
 	 	// constructors and destructor
 	 	Protein();
 	 	Protein(char * p);
 	 	~Protein();
 	 	void Print();
 	 	// return an array of DNA sequences that can possibly
        // generate that protein sequence
        DNA * GetDNAStrandsEncodingMe(DNA & bigDNA,CodonsTable CO);
        Protein operator+ (const Protein& other) const;
        bool operator!= (const Protein& other) const;
        bool operator== (const Protein& other) const;


};

#endif // PROTIEN_H
