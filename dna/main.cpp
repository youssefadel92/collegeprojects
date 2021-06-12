#include <iostream>
#include "Sequence.h"
#include "DNA.h"
#include "RNA.h"
#include <string>
#include <fstream>
#include "Protien.h"
#include "Codons.h"
/////////////////////
using namespace std;
/////////////////////
int main(){
    while(true){
        int choice;
        cout<<"*************************************"<<endl;
        cout<<"1-convert DNA Sequence To Protien"<<endl<<"2-Convert Protien To Dna Sequence"<<endl<<"3-Convert RNA to DNA"<<endl<<"4-LCS alignment"<<endl<<"5-Global Alignment"<<endl<<"6-Local Alignment"<<endl<<"7-exit"<<endl;
        cin>>choice;
        if (choice==1){
            cout<<"Enter DNA Sequence:";
            //char* y={"tcggatacagagtagaatt"};
            char *y = new char[65];
            //Sequence t;
            //t.loadsequencefromfile();
            cin>>y;
            //DNA x(y,motif,-1,-1);
            try {

            DNA x(y,motif,-1,-1);
            x.BuildComplementaryStrand();
            x.Print();
            RNA NN(x.ConvertToRNA());
            NN.Print();
            CodonsTable CO;
            CO.print();
            //CO.getAminoAcid(NN.getseq());
            cout<<"done";
            Protein PR(CO.getAminoAcid(NN.getseq()));
            PR.Print();
            }
            catch (DNA::wrongseq) {
                cout << "Wrong Seq" << endl;
                exit(1) ;
            }
            delete []y;

        }
        else if(choice==2){
            cout<<"Enter Protien Sequence:";
            char *y = new char[65];
            cin>>y;
            cout<<"Enter DNA Sequence:";
            char *x = new char[100];
            cin>>x;
            Protein AM(y);
            DNA ST(x,promoter,-1,-1);
            CodonsTable co;
            //cout<<"DONE";

            DNA* NEWW=AM.GetDNAStrandsEncodingMe(ST,co);
            NEWW->Print();
        }
        else if(choice==3){
            cout<<"Enter Sequence:";
            char *y = new char[65];
            cin>>y;
            try {
                RNA x(y,mRNA);
                DNA NN(x.ConvertToDNA());
                NN.BuildComplementaryStrand();
                NN.Print();
                NN.savesequencetofile();
                cout<<*y;
                cout<<NN.returnseq();
                memset(y, 0, sizeof(y));
                memset(NN.returnseq(), 0, sizeof(NN.returnseq()));
                free(y);
                free(NN.returnseq());
            }
            catch (RNA::wrongseq) {
                cout << "Wrong Seq" << endl;
                exit(1) ;
            }


        }
        else if(choice==4){
            //int lx,ly;
            //cout<<"length of Sequence1:";
            //cin>>lx;
            //cout<<"length of Sequence2:";
            //cin>>ly;
            char *x = new char[61];
            char *y = new char[61];
            cout<<"*Enter The Long Sequence First*"<<endl;
            cout<<"Enter First sequence:";
            cin>>x;
            cout<<"Enter Second sequence:";
            cin>>y;
            Sequence *seq1=new Sequence(x);
            Sequence *seq2=new Sequence(y);
            char * newseq=Align(seq1,seq2);
            int iterat=0;
            while(newseq[iterat]!='\0'){
                cout<<newseq[iterat];
                iterat++;
            }
            cout<<endl;
            delete seq1;
            delete seq2;
            delete[] x;
            delete[] y;

        }
        else if(choice==5){
            //int lx,ly;
            //cout<<"length of Sequence1:";
            //cin>>lx;
            //cout<<"length of Sequence2:";
            //cin>>ly;
            char *x = new char[61];
            char *y = new char[61];
            cout<<"*Enter The Long Sequence First*"<<endl;
            cout<<"Enter First sequence:";
            cin>>x;
            cout<<"Enter Second sequence:";
            cin>>y;
            Sequence *seq1=new Sequence(x);
            Sequence *seq2=new Sequence(y);
            //GAlign(seq1,seq2);
            char * newseq=GAlign(seq1,seq2);
            int iterat=0;
            while(newseq[iterat]!='\0'){
                cout<<newseq[iterat];
                iterat++;
            }
            cout<<endl;
            delete seq1;
            delete seq2;
            delete[] x;
            delete[] y;

        }
        else if(choice==6){
            char *x = new char[61];
            char *y = new char[61];
            cout<<"*Enter The Long Sequence First*"<<endl;
            cout<<"Enter First sequence:";
            cin>>x;
            cout<<"Enter Second sequence:";
            cin>>y;
            Sequence *seq1=new Sequence(x);
            Sequence *seq2=new Sequence(y);
            //GAlign(seq1,seq2);
            char * newseq=LAlign(seq1,seq2);
            int iterat=0;
            while(newseq[iterat]!='\0'){
                cout<<newseq[iterat];
                iterat++;
            }
            cout<<endl;
            delete seq1;
            delete seq2;
            delete[] x;
            delete[] y;

        }
        else if(choice==7)break;
    }


    return 0;
}
