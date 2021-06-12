#ifndef DNA_H
#define DNA_H
#include "Sequence.h"
#include "RNA.h"
#include "string.h"
class RNA;

enum DNA_Type{promoter, motif, tail, noncoding};


class DNA : public Sequence
{
  	protected:
        DNA_Type type;
        DNA * complementary_strand;
        int startIndex;
        int endIndex;
    public:
 	 	// constructors and destructor
        DNA();
        char *returnseq()const;
        int getstartindex();
        int getendindex();
        void setstartindex(int x);
        void setendindex(int x);
        DNA(int x);
        DNA(char * seq1, DNA_Type atype,int x,int y);
        DNA(const DNA& rhs);
        ~DNA();
 	 	// function printing DNA sequence information to user
        void Print();
        // function to convert the DNA sequence to RNA sequence
        // It starts by building the complementary_strand of the current
        // DNA sequence (starting from the startIndex to the endIndex), then,
        // it builds the RNA corresponding to that complementary_strand.
        RNA ConvertToRNA();
 	 	// function to build the second strand/pair of DNA sequence
	    // To build a complementary_strand (starting from the startIndex to
        // the endIndex), convert each A to T, each T to A, each C to G, and
        // each G to C. Then reverse the resulting sequence.
        void BuildComplementaryStrand();
        bool operator== (const DNA& other)const ;
        bool operator!= (const DNA& other)const ;
        DNA  operator+ (const DNA& other)const ;

  };

#endif // DNA_H
