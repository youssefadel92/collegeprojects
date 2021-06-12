#include "DNA.h"
#include <iostream>
using namespace std;

DNA::DNA(){
    startIndex=-1;
    endIndex=-1;
}
DNA::DNA(char * seq1, DNA_Type atype,int x,int y){
    int iterat=0;
    while(seq1[iterat]!='\0'){iterat++;}
    bool xXx=0;
    int iterat2=0;
    while(seq1[iterat2]!='\0'){
           if (seq1[iterat2]!='a'&&seq1[iterat2]!='g'&&seq1[iterat2]!='c'&&seq1[iterat2]!='t'&&seq1[iterat2]!='\0'){
                xXx=1;
                break;
           }
           iterat2++;
    }
    if (xXx==0){
    seq=new char[iterat];
    strcpy(seq,seq1);
    //free(seq1);
    //seq1='\0';
    //delete[] seq1;
    type=atype;
    startIndex=x;
    endIndex=y;
    }
    else if (xXx==1){
        wrongseq ww;
        throw ww;
    }
}
char * DNA::returnseq()const{
    return seq;
}
int DNA::getstartindex(){
    return startIndex;
}
int DNA::getendindex(){
    return endIndex;
}
void DNA::setstartindex(int x){
    startIndex=x;

}
void DNA::setendindex(int x){
    endIndex=x;

}
DNA::DNA(int x){
    startIndex=-1;
    endIndex=-1;
    seq=new char[x];
}
DNA::DNA(const DNA& rhs){
    DNA* x=new DNA;
    x->seq=rhs.seq;x->startIndex=rhs.startIndex;x->endIndex=rhs.endIndex;x->complementary_strand=rhs.complementary_strand;
    x->type=rhs.type;
    seq=x->seq;startIndex=x->startIndex;endIndex=x->endIndex;complementary_strand=x->complementary_strand;type=x->type;
}

void DNA::Print(){
    cout<<"Start Index:"<<startIndex<<endl;
    cout<<"End Index:"<<endIndex<<endl;
    cout<<"Type:"<<type<<endl;
    cout<<"DNA Sequence:";
    int ite=0;
    while(seq[ite] != '\0'){
        cout<<seq[ite];
        ite++;
    }
    ite=0;
    cout<<endl<<"Complimentary sequence:";
    while(complementary_strand->seq[ite] == 'g'||complementary_strand->seq[ite] == 'a'||complementary_strand->seq[ite] == 'c'||complementary_strand->seq[ite] == 't'){
        cout<<complementary_strand->seq[ite];
        ite++;
    }

    cout<<endl;
}

void DNA::BuildComplementaryStrand(){

    char *seq2;
    if (startIndex==-1&&endIndex==-1){
        int ite=1;
        while(seq[ite] != '\0'){
            ite++;
        }
        seq2=new char[ite+1];
            for (int i=0;i<ite;i++){
                if (seq[i]=='a')seq2[i]='t';
                else if (seq[i]=='t')seq2[i]='a';
                else if (seq[i]=='c')seq2[i]='g';
                else if (seq[i]=='g')seq2[i]='c';
            }
        seq2[ite]='\0';
        complementary_strand= new DNA(seq2,promoter,-1,-1);

    }

    else {
        seq2=new char[endIndex+1-startIndex];
        for (int i=startIndex;i<endIndex;i++){
            if (seq[i]=='a')seq2[i]='t';
            else if (seq[i]=='t')seq2[i]='a';
            else if (seq[i]=='c')seq2[i]='g';
            else if (seq[i]=='g')seq2[i]='c';
        }
        seq2[endIndex+1-startIndex]='\0';


        complementary_strand= new DNA(seq2,promoter,startIndex,endIndex);

    }
    //cout<<endl<<seq2;

}
RNA DNA::ConvertToRNA(){
    BuildComplementaryStrand();
    int ite=0;
    while(complementary_strand->seq[ite]!='\0'){
        ite++;
    }
    char *seq2;
    seq2=new char[ite+1];
        for (int i=0;i<ite;i++){
            if (complementary_strand->seq[i]=='t')seq2[i]='u';
            else seq2[i]=complementary_strand->seq[i];
        }
    seq2[ite]='\0';
    RNA x(seq2,mRNA);
    return x;
}

DNA::~DNA()
{
    //cout<<"Destructor Called";
    //delete complementary_strand;
    delete seq;
}

bool DNA::operator== (const DNA& other) const
{
    int othlen=0;
    int thislen=0;
    while (seq[thislen]!='\0'){thislen++;}
    while (other.returnseq()[othlen]!='\0'){othlen++;}
    othlen++;thislen++;
    bool s = 1  ;
    if (thislen != othlen)
        return 0 ;
    else
    {

        for (int i = 0 ; i < thislen ; i++ )
        {
            if (seq[i] != other.returnseq()[i])
            {
                s = 0 ;
                break;
            }

        }
    }
    return ( s && type==other.type) ;

}
bool DNA:: operator!= (const DNA& other) const
{

    return !(other == *this) ;
}
DNA DNA:: operator+ (const DNA& other) const
{
    int othlen=0;
    int thislen=0;
    while (seq[thislen]!='\0'){thislen++;}
    while (other.returnseq()!='\0'){othlen++;}
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
            N[i] = other.returnseq()[i-thislen] ;

    }
    DNA X(N,type,-1,-1);
    return X ;
}
