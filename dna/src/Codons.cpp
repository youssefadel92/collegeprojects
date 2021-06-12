#include "Codons.h"
#include <string>
#include <iostream>
using namespace std;

int parts(char* array, int start, int end, int steps){
        int i, j;
        char temp [(end-start)/steps + 1];
        for (i = start , j = 0 ; i <= end ; i += steps , ++j)
            temp[j] = array[i];
        for (i = 0 ; i < (end - start)/steps + 1 ; ++i)
            array[i] = temp[i];
        //for ( ; i <= end ; ++i)
        //      array[i] = ' ';
        return (end - start)/steps + 1;
}
CodonsTable::CodonsTable()
{
        fstream x;
        x.open("RNA_codon_table.txt");
        for (int i=0;i<64;i++){
            for(int z=0;z<3;z++){
                x>>codons[i].value[z];
            }
            codons[i].value[3]=' ';
            if(x.peek()==32)codons[i].AminoAcid=' ';
            else x>>codons[i].AminoAcid;
        }
        x.close();
}

CodonsTable::~CodonsTable()
{
}
void CodonsTable::LoadCodonsFromFile(string codonsFileName){
            fstream x;
            x.open(codonsFileName);
            for (int i=0;i<64;i++){
                for(int z=0;z<3;z++){
                    x>>codons[i].value[z];
                }
                codons[i].value[3]=' ';
                if(x.peek()==32)codons[i].AminoAcid=' ';
                else x>>codons[i].AminoAcid;
            }
}
void CodonsTable::print(){
            cout<<endl;
            for (int i=0;i<64;i++){
                cout<<endl;
                for (int y=0;y<4;y++){
                    cout<<codons[i].value[y];
                }
                cout<<"="<<codons[i].AminoAcid;
            }
}
char * CodonsTable::getAminoAcid(char * value1){
int i=0;
            //while(value1[i]!='\0'){cout<<value1[i];i++;}
            int endindex=0;
            while(value1[i]!='\0'&&value1[i+2]!='\0'&&value1[i+1]!='\0'){
                if(value1[i]=='u'&&value1[i+1]=='a'){
                        if(value1[i+2]=='a'||value1[i+2]=='g'){endindex=i;break;}
                        else{i+=3;endindex=i;}
                }
                else if(value1[i+2]=='a'&&value1[i+1]=='g'&&value1[i]=='u'){endindex=i;break;}
                else {i+=3;endindex=i;}
                //cout<<endindex;
            }
            //cout<<endindex<<" ";
            while (endindex%3!=0){
                endindex-1;
            }
            //cout<<endindex;
            //////////////////////////////////////
            //cout<<endl;
            char neww[endindex];
            for(int i=0;i<endindex;i++){
                neww[i]=value1[i];
                //cout<<neww[i];
            }
            //cout<<endl;
            int iterat=0;
            char * temp1=new char[20];
            for (int i=0;i<endindex;i+=3){
                int g=parts(neww,i,i+3,1);
                char temp[4];
                for (int w=0;w<g-1;w++){temp[w]=neww[w];}
                temp[3]=' ';

               // for(int s=0;s<4;s++){cout<<temp[s];}
                for (int z=0;z<64;z++){
                    //cout<<(temp[0]==codons[z].value[0]);
                    if (temp[0]==codons[z].value[0]&&temp[1]==codons[z].value[1]&&temp[2]==codons[z].value[2]){
                            temp1[iterat]=codons[z].AminoAcid;
                            iterat++;
                    }
                }
                temp1[iterat]='\0';

            }
/*
            Codon u[(endindex/3)+1];
            for (int i=0;i<(endindex/3)+1;i++){
                for(int z=0;z<3;z++){
                    u[i].value[z]=neww[i];
                }
                neww[i]=neww[i+3];
            }
            for (int i=0;i<64;i++){
                if(codons[i].value==value1){
                    u.value=codons[i].value;
                    u.AminoAcid=codons[i].AminoAcid;
                    break;
                }

            }
            return u;*/
            return temp1;
}
