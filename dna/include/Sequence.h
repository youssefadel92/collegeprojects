#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <exception>


class Sequence
{
  	protected:
        char * seq;

    public:
 	 	// constructors and destructor
        class wrongseq{};
        Sequence();
        Sequence(char * seq1);
        Sequence(Sequence& rhs);
        virtual ~Sequence();
 	 	// pure virtual function that should be overridden because every
        // type of sequence has its own details to be printed
        virtual void Print();
 	 	// friend function that will find the LCS (longest common
        // subsequence) between 2 sequences of any type, according to
        // polymorphism
        friend char* Align(Sequence * s1, Sequence * s2);
        friend char* GAlign(Sequence * s1, Sequence * s2);
        void loadsequencefromfile();
        void savesequencetofile();
        virtual char * returnseq()const;
        friend char* LAlign(Sequence * s1, Sequence * s2);

};

#endif // SEQUENCE_H
