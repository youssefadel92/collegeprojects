#include "RNA.h"
#include <iostream>
using namespace std;

RNA::RNA()
{
    type=mRNA;
}
void RNA::Print(){
    cout<<"RNA Sequence:";
    int ite=0;
    while(seq[ite] != '\0'){
        cout<<seq[ite];
        ite++;
    }
    cout<<endl<<"Type:"<<type;
}
RNA::~RNA()
{
    delete[] seq;
}
char * RNA::getseq()const{
    return seq;
}
RNA::RNA(const RNA& rhs){
    RNA* x=new RNA;
    x->seq=rhs.seq;x->type=rhs.type;
    seq=x->seq;type=x->type;
}
RNA::RNA(char * seq1,RNA_Type atype){
    type=atype;
    int iterat=0;
    while(seq1[iterat]!='\0'){iterat++;}
    iterat++;
    bool xXx=0;
    int iterat2=0;
    while(seq1[iterat2]!='\0'){
           if (seq1[iterat2]!='a'&&seq1[iterat2]!='g'&&seq1[iterat2]!='c'&&seq1[iterat2]!='u'){
                xXx=1;
                break;
           }
           iterat2++;
    }
    if (xXx==0){
        seq=new char[iterat];
        strcpy(seq,seq1);
        free(seq1);
        seq1='\0';
        delete[] seq1;
    }
    else if(xXx==1){
        wrongseq ww;
        throw ww;
    }
}
DNA RNA::ConvertToDNA(){
    int ite=0;
    while(seq[ite]!='\0'){
        ite++;
    }
    char *seq2;
    seq2=new char[ite+1];
        for (int i=0;i<ite;i++){
            if (seq[i]=='u')seq2[i]='a';
            else if (seq[i]=='a')seq2[i]='t';
            else if (seq[i]=='g')seq2[i]='c';
            else if (seq[i]=='c')seq2[i]='g';
        }
    seq2[ite]='\0';
    DNA x(seq2,motif,-1,-1);
    return x;

}
bool RNA::operator== (const RNA& other) const
{
    int othlen=0;
    int thislen=0;
    while (seq[thislen]!='\0'){thislen++;}
    while (other.getseq()[othlen]!='\0'){othlen++;}
    othlen++;thislen++;
    bool s = 1  ;
    if (thislen != othlen)
        return 0 ;
    else
    {

        for (int i = 0 ; i < thislen ; i++ )
        {
            if (seq[i] != other.getseq()[i])
            {
                s = 0 ;
                break;
            }

        }
    }
    return ( s && type==other.type) ;

}
bool RNA:: operator!= (const RNA& other) const
{
    return !(other == *this) ;
}
RNA RNA:: operator+ (const RNA& other) const
{
    int othlen=0;
    int thislen=0;
    while (seq[thislen]!='\0'){thislen++;}
    while (other.getseq()!='\0'){othlen++;}
    othlen++;thislen++;
    int g=othlen+thislen;
    char *N=new char[g];
    for (int i = 0 ; i < g ; i++)
    {
        if (i < thislen)
        {
            N[i] = seq[i] ;
        }
        else
            N[i] = other.getseq()[i-thislen] ;

    }
    RNA X(N,type);
    return X ;
}
