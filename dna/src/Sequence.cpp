#include "Sequence.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
char* Align(Sequence * s1, Sequence * s2){
    int lx,ly;
    lx=0;
    ly=0;
    while(s1->seq[lx]!='\0')lx++;
    while(s2->seq[ly]!='\0')ly++;
    char x[lx],y[ly];
    for(int i=0;i<lx;i++){
        x[i]=s1->seq[i];
        //cout<<x[i];
    }
    //cout<<endl;
    for(int i=0;i<ly;i++){
        y[i]=s2->seq[i];
        //cout<<y[i];
    }
    int LCS[lx][ly];
    for (int i=0;i<lx;i++){
        for (int j=0;j<ly;j++){
            //cout<<x[i]<<y[j];
            //cout<<(x[i]==y[j]);
            //cout<<endl;
            if (x[i]==y[j]){
                if(i==0||j==0)LCS[i][j]=1;
                else LCS[i][j]=1+LCS[i-1][j-1];
            }
            else if (x[i]!=y[j]){
                if(i==0&&j==0)LCS[i][j]=0;
                else if(i==0&&j!=0)LCS[i][j]=LCS[i][j-1];
                else if(j==0&&i!=0)LCS[i][j]=LCS[i-1][j];
                else LCS[i][j]=max(LCS[i-1][j],LCS[i][j-1]);
            }
        }
    }
    //cout<<endl;
    for (int i=0;i<lx;i++){
        for (int j=0;j<ly;j++){
            cout<<LCS[i][j]<<" ";
        }
        cout<<endl;
    }
    //cout<<LCS[lx-1][ly-1];
    char * newseq=new char[1+LCS[lx-1][ly-1]];
    int index=0;
    int xaxix=lx-1;
    int yaxix=ly-1;
    while(true){
        if(xaxix==0&&LCS[xaxix][yaxix-1]<LCS[xaxix][yaxix]){yaxix-=1;newseq[index]=x[xaxix];index++;continue;}
        else if(xaxix==0&&yaxix==0){
            if (LCS[xaxix][yaxix]==0){
                break;
            }
            else if (LCS[xaxix][yaxix]==1){
                newseq[index]=x[xaxix];
                index++;
                break;
            }
        }
        else if(LCS[xaxix][yaxix]==LCS[xaxix-1][yaxix]){xaxix-=1;continue;}
        else if(LCS[xaxix][yaxix]==LCS[xaxix][yaxix-1]){yaxix-=1;continue;}


        else {newseq[index]=x[xaxix];index++;xaxix-=1;yaxix-=1;continue;}
    }

    for (int i=0;i<(LCS[lx-1][ly-1]);i++){
        char temp;
        temp=newseq[i];
        //cout<<newseq[(LCS[lx-1][ly-1])-i];
        newseq[i]=newseq[(LCS[lx-1][ly-1])-i];
        newseq[(LCS[lx-1][ly-1])-i]=temp;
    }
    for (int i=0;i<(LCS[lx-1][ly-1]);i++){
        char temp;
        temp=newseq[i];
        //cout<<newseq[(LCS[lx-1][ly-1])-i];
        newseq[i]=newseq[i+1];
        newseq[i+1]=temp;
    }
    newseq[(LCS[lx-1][ly-1])]='\0';
    /*for(int i=0;i<100;i++){
        if (newseq[i]=='\0'){
            break;
        }
        cout<<newseq[i];
    }*/
    return newseq;


}



char* GAlign(Sequence * s1, Sequence * s2){
    int lx,ly;
    int gappen=-2;
    int match=5;
    int notmatch=-1;
    lx=1;
    ly=1;
    while(s1->seq[lx]!='\0')lx++;
    while(s2->seq[ly]!='\0')ly++;
    char x[lx],y[ly];
    for(int i=0;i<lx;i++){
        x[i]=s1->seq[i];
    }
    //cout<<endl;
    for(int i=0;i<ly;i++){
        y[i]=s2->seq[i];
    }
    //cout<<endl<<lx<<ly;
    int LCS[lx+1][ly+1];
    LCS[0][0]=0;
    for(int i=1;i<lx+1;i++){LCS[i][0]=LCS[i-1][0]+gappen;}
    for(int i=1;i<ly+1;i++)LCS[0][i]=LCS[0][i-1]+gappen;

    for (int i=1;i<lx+1;i++){
        for (int j=1;j<ly+1;j++){
            int score;
            //cout<<x[i]<<y[j];
            //cout<<(x[i]==y[j]);
            //cout<<endl;
            if (x[i-1]==y[j-1]){
                score=max(max(LCS[i-1][j-1]+match,LCS[i-1][j]+gappen),LCS[i][j-1]+gappen);
                LCS[i][j]=score;
                //cout<<max(max(LCS[i-1][j-1]+match,LCS[i-1][j]+gappen),LCS[i][j-1]+gappen)<<endl;
            }
            else if (x[i-1]!=y[j-1]){
                score=max(max(LCS[i-1][j-1]+notmatch,LCS[i-1][j]+gappen),LCS[i][j-1]+gappen);
                LCS[i][j]=score;
                //cout<<max(max(LCS[i-1][j-1]+notmatch,LCS[i-1][j]+gappen),LCS[i][j-1]+gappen)<<endl;
            }
            /*if (i==1&&j==2){
                cout<<max(max(LCS[i-1][j-1]+notmatch,LCS[i-1][j]+gappen),LCS[i][j-1]+gappen)<<"             "<<LCS[i-1][j]+gappen<<" "<<LCS[i][j-1]+gappen;
            }*/
        }
    }
    cout<<endl;
    for (int i=0;i<lx+1;i++){
        for (int j=0;j<ly+1;j++){
            cout<<setw(5)<<LCS[i][j];
        }
        cout<<endl;
    }
    int xaxix=lx;
    int yaxix=ly;
    char *newseq=new char[lx+ly];

    int index=0;
    while(true){
        if(xaxix==0&&yaxix==0){
            break;
        }
        newseq[index]=x[xaxix-1];
        index++;
        if(LCS[xaxix][yaxix]-match==LCS[xaxix-1][yaxix-1]||LCS[xaxix][yaxix]-notmatch==LCS[xaxix-1][yaxix-1]){xaxix-=1;yaxix-=1;}
        else if(LCS[xaxix][yaxix]-gappen==LCS[xaxix-1][yaxix]){xaxix-=1;}
        else if(LCS[xaxix][yaxix]-gappen==LCS[xaxix][yaxix-1]){yaxix-=1;}


    }
    for (int i=0;i<=index/2;i++){
        char temp;
        temp=newseq[i];
        //cout<<newseq[index-i];
        newseq[i]=newseq[index-i];
        newseq[index-i]=temp;
    }
    for (int i=0;i<=index;i++){
        char temp;
        temp=newseq[i];
        //cout<<newseq[(LCS[lx-1][ly-1])-i];
        newseq[i]=newseq[i+1];
        newseq[i+1]=temp;
    }
    newseq[index]='\0';
    return newseq;


}



char* LAlign(Sequence * s1, Sequence * s2){
    int lx,ly;
    int gappen=-4;
    int match=5;
    int notmatch=-3;
    lx=1;
    ly=1;
    while(s1->seq[lx]!='\0')lx++;
    while(s2->seq[ly]!='\0')ly++;
    char x[lx],y[ly];
    for(int i=0;i<lx;i++){
        x[i]=s1->seq[i];
    }
    //cout<<endl;
    for(int i=0;i<ly;i++){
        y[i]=s2->seq[i];
    }
    //cout<<endl<<lx<<ly;
    int LCS[lx+1][ly+1];
    LCS[0][0]=0;
    for(int i=1;i<lx+1;i++){LCS[i][0]=0;}
    for(int i=1;i<ly+1;i++)LCS[0][i]=0;

    for (int i=1;i<lx+1;i++){
        for (int j=1;j<ly+1;j++){
            int score;
            //cout<<x[i]<<y[j];
            //cout<<(x[i]==y[j]);
            //cout<<endl;
            if (x[i-1]==y[j-1]){
                score=max(max(LCS[i-1][j-1]+match,LCS[i-1][j]+gappen),LCS[i][j-1]+gappen);
                LCS[i][j]=score;
                //cout<<max(max(LCS[i-1][j-1]+match,LCS[i-1][j]+gappen),LCS[i][j-1]+gappen)<<endl;
            }
            else if (x[i-1]!=y[j-1]){
                score=max(max(LCS[i-1][j-1]+notmatch,LCS[i-1][j]+gappen),LCS[i][j-1]+gappen);
                LCS[i][j]=score;
                //cout<<max(max(LCS[i-1][j-1]+notmatch,LCS[i-1][j]+gappen),LCS[i][j-1]+gappen)<<endl;
            }
        }
    }
    cout<<endl;
    for (int i=0;i<lx+1;i++){
        for (int j=0;j<ly+1;j++){
            cout<<setw(5)<<LCS[i][j]<<" ";
        }
        cout<<endl;
    }
    int xaxix=lx;
    int yaxix=ly;
    char *newseq=new char[lx+ly];
    int index=0;
    //newseq[index]=x[xaxix-1];
    while(true){
        if(xaxix==0||yaxix==0){
            break;
        }
        newseq[index]=x[xaxix-1];index++;
        if(LCS[xaxix][yaxix]-match==LCS[xaxix-1][yaxix-1]||LCS[xaxix][yaxix]-notmatch==LCS[xaxix-1][yaxix-1]){xaxix-=1;yaxix-=1;}
        else if(LCS[xaxix][yaxix]-gappen==LCS[xaxix-1][yaxix]){xaxix-=1;}
        else if(LCS[xaxix][yaxix]-gappen==LCS[xaxix][yaxix-1]){yaxix-=1;}


    }
    for (int i=0;i<=index/2;i++){
        char temp;
        temp=newseq[i];
        //cout<<newseq[index-i];
        newseq[i]=newseq[index-i];
        newseq[index-i]=temp;
    }
    for (int i=0;i<=index;i++){
        char temp;
        temp=newseq[i];
        //cout<<newseq[(LCS[lx-1][ly-1])-i];
        newseq[i]=newseq[i+1];
        newseq[i+1]=temp;
    }
    newseq[index]='\0';
    return newseq;


}





Sequence::Sequence(){
            seq= new char;
}
Sequence::Sequence(char * seq1){
            seq=seq1;
}
Sequence::Sequence(Sequence& rhs){
            char * neww= new char;
            neww=rhs.seq;
            seq=neww;
}
Sequence::~Sequence(){
            delete[] seq;
}
void Sequence::Print(){
            int x=sizeof(seq);
            for (int i=0;i<x;i++){
                cout<<seq[i];
            }
}
void Sequence::loadsequencefromfile(){
            fstream x;
            string Filename;
            cout<<"Enter File Name:";
            cin>>Filename;
            Filename+=".txt";
            cout<<Filename;
            x.open(Filename);
            if (x.fail())cout<<"Open File Failed"<<endl;
            else {
                char c;
                int i=0;
                while(x.get(c)){
                    i++;
                }
                seq=new char[i];
                x.close();
                x.open(Filename);
                x.getline(seq,i);
                x.close();
            }
}
void Sequence::savesequencetofile(){
        int iterat =0;
        while (seq[iterat]!='\0'){
            iterat++;
        }
        iterat++;
        ofstream myfile;
        string Filename;
        cout<<Filename;
        cout<<"Enter File Name:";
        cin>>Filename;
        Filename+=".txt";
        myfile.open (Filename);
        if (myfile.fail())cout<<"File Open Failed"<<endl;
        else {
            for(int i=0;i<iterat;i++){
                myfile<<seq[i];
            }
        myfile.close();
        }

}
class wrongseq:public exception
{
public:
    virtual const char* what() const throw()
    {
        return "Wrong Sequence";
    }
};


char * Sequence::returnseq()const{
    return seq;
}
