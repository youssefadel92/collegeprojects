#include "Protien.h"
#include <iostream>
using namespace std;

Protein::Protein(){
    type=Cellular_Function;
}

Protein::~Protein()
{
    delete[] seq;
}
Protein::Protein(char * seq1){
    int iterat=0;
    while(seq1[iterat]!='\0'){iterat++;}
    iterat++;
    seq=new char[iterat];
    strcpy(seq,seq1);
    free(seq1);
    seq1='\0';
    delete[] seq1;
    type=Cellular_Function;
}
void Protein::Print(){
    cout<<"AminoAcids:";
    int i=0;
    while(seq[i]!='\0'){
        cout<<seq[i];
        i++;
    }
    cout<<endl;
}
DNA* Protein::GetDNAStrandsEncodingMe(DNA & bigDNA,CodonsTable CO){
    /*for (int i=0;i<500;i++){
        if(seq[i]=='\0')break;
        cout<<seq[i];
    }
    cout<<bigDNA.getstartindex()<<" "<<bigDNA.getendindex();
    cout<<endl;
    for (int i=0;i<500;i++){
        if(bigDNA.returnseq()[i]=='\0')break;
        cout<<bigDNA.returnseq()[i];
    }
    cout<<endl;*/
    //
    int iterat=0;
    int iterat2=0;
    while(seq[iterat]!='\0'){
        iterat++;
    }
    iterat*=3;
    //cout<<iterat<<endl;
    while(bigDNA.returnseq()[iterat2]!='\0'){
        iterat2++;
    }
    char *y = NULL;
    DNA *x;
    for (int i=0;i<=iterat2-iterat;i++){
        //cout<<i;
        y=(char*)realloc(y,iterat*sizeof(char)+1);
        int h=i;
        for (int j=i;j<i+iterat;j++){
            y[j-h]=bigDNA.returnseq()[j];
            //if (j==i+iterat){}
            //cout<<y[j-h];
        }
        y[iterat]='\0';
        //cout<<"DONE";
        /*for(int f=0;f<1000;f++){
            if (y[f]=='\0')break;
            cout<<y[f];
        }*/
        //cout<<endl;
        x=new DNA(y,motif,-1,-1);
        x->BuildComplementaryStrand();
        RNA NN(x->ConvertToRNA());
        CodonsTable CO;
        Protein PR(CO.getAminoAcid(NN.getseq()));
        bool state=1;
        for(int l=0;l<iterat/3;l++){
                if (PR.returnseq()[l]!=seq[l])state=0;
            }
        if (state==1){
            return x;
        }
        delete x;
        //delete[] NN.getseq();
        //delete[] PR.returnseq();

        /*for (int j=i+1;j<=bigDNA.getendindex();j++)
        {
        char *seq2=new char [j-i+1];
        //seq2 = (char*) malloc((j-i+1)*sizeof(char));

        //seq2=new char[j-i+1];
        int index=0;
        for (int y=i;index<j-i;y++){
            if (bigDNA.returnseq()[y]=='a')seq2[index]='u';
            else if (bigDNA.returnseq()[y]=='t')seq2[index]='a';
            else if (bigDNA.returnseq()[y]=='c')seq2[index]='g';
            else if (bigDNA.returnseq()[y]=='g')seq2[index]='c';
            index++;
        }
        seq2[j-i]='\0';
        cout<<"done";
        cout<<i<<" "<<j;
        for (int i=0;i<500;i++){
        if(seq2[i]=='\0')break;
        cout<<seq2[i];
        }
        //cout<<"amino:"<<CO.getAminoAcid(seq2);
        cout<<endl;
            //PR->Print();
            //char *z=CO.getAminoAcid(seq2);
            if(CO.getAminoAcid(seq2)==seq){
                NEWDNA[iterat]=DNA(seq2,promoter,i,j);
                iterat++;
            }
            free(seq2);
            delete seq2;
            //delete z;
//            delete PR;
            //delete x.returnseq();
            //delete x.ConvertToRNA().getseq();
            //delete NN.getseq();
            //delete PR.seq;

            }
            cout<<"WOW";
*/
        }


//    return NEWDNA;
}

bool Protein::operator== (const Protein& other) const
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
            if (seq[i] != other.seq[i])
            {
                s = 0 ;
                break;
            }

        }
    }
    return ( s && type==other.type) ;

}
bool Protein:: operator!= (const Protein& other) const
{

    return !(other == *this) ;
}
Protein Protein:: operator+ (const Protein& other) const
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
    Protein X(N);
    return X ;
}

