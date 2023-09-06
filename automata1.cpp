#include <iostream>
#include <chrono>    
#include <iomanip>
#include <stdio.h>
using namespace std;
using namespace std::chrono;

// This program receives a protein sequence in an aligned FASTA file, encodes the sequence 
//according to the chosen binary code, and uses the cellular automaton evolution rule to generate the cellular automaton.




int main(int argc, char** argv)
{   
	auto start = steady_clock::now(); 
	int n,i,k,j;
	char palavra[10000];
	FILE  *arquivo,*arquivo1;               
	
	
		n=148; //protein size
	
	
	
	//READ A FILE WITH THE PROTEIN SEQUENCE IN BINARY
	arquivo1 = fopen("protein_aligned.txt", "rt");    
	

	//This command lists each letter typed in a position of a word
	for(i=0; i<n; i++)
	{
		fscanf(arquivo1," %c", &palavra[i]);
	}
		
	fclose(arquivo1);
	
	
	for(k=0 ; k<n ; k++)
	{
	 cout << palavra[k] ;
	}
	cout << endl;
	
	//CREATE A FILE WITH EACH LINE AN AMINO ACID
	arquivo = fopen("protein_lines.txt", "w");    
	for(j=0; j<n; j++)
	{

	fprintf(arquivo,"%c\n ", palavra[j]);
	}
	fclose(arquivo);
//_____________________PART 2- SEQUENCE CODING_____________________________________________________________________________________________
	int s,r,seq[10000], vetor[10000];
	FILE *arquivo2;



// This command turns each amino acid into an ASCII table number.
	for(int l=0; l<n; l++)
	{	
		char ascChar = toupper(palavra[l]);  // the asChar variable is getting capital letters from the word [i]
		
		seq[l]= ascChar-0;  // turns the typed letter into an ascii table number
	
	}
	
// Changing amino acids to ASCII code

cout << "The numerical sequence of the protein, in the ASCII table, is:";

for(int l=0 ; l<n ; l++)
	{
	 cout << seq[l];
	}
cout << endl;

//Changing ASCII table numbers to Chaudhuri decimal hydrophobicity
for(int f=0 ; f<n ; f++)
	{
	 if(seq[f]==65)//A
	 seq[f]=4;
	 if(seq[f]==67)//C
	 seq[f]=68;
	 if(seq[f]==68)//D
	 seq[f]=116;
	 if(seq[f]==69)//E
	 seq[f]=118;
	 if(seq[f]==70)//F
	 seq[f]=132;
	 if(seq[f]==71)//G
	 seq[f]=0;
	 if(seq[f]==72)//H
	 seq[f]=126;
	 if(seq[f]==73)//I
	 seq[f]=30;
	 if(seq[f]==75)//K
	 seq[f]=55;
	 if(seq[f]==76)//l
	 seq[f]=23;
	 if(seq[f]==77)//m
	 seq[f]=54;
	 if(seq[f]==78)//n
	 seq[f]=46;
	 if(seq[f]==80)//p
	 seq[f]=38;
	 if(seq[f]==81)//q
	 seq[f]=47;
	 if(seq[f]==82)//r
	 seq[f]=127;
	 if(seq[f]==83)//s
	 seq[f]=36;
	 if(seq[f]==84)//t
	 seq[f]=52;
	 if(seq[f]==86)//v
	 seq[f]=22;
	 if(seq[f]==89)//y
	 seq[f]=164;
	 if(seq[f]==87)//w
	 seq[f]=182;
	 if(seq[f]==45)//-
	 seq[f]=255;
	 if(seq[f]==63)//?
	 seq[f]=254;
	}


cout << "The numerical sequence of the protein, using the decimal code, is:";
for(int o=0 ; o<n ; o++)
	{
	 cout << seq[o];
	}
cout << endl;

// CREATE A FILE WITH THE PROTEIN SEQUENCE IN BINARY
	arquivo2 = fopen("initial_1.txt", "wt");    
	
		if(arquivo2==NULL){
		cout << "Unable to open the program" << endl;
		exit(0);
		}


cout << "The binary sequence of the protein is:";
for(int e=0; e<n ;e++){
 for(int l = 7; l >= 0; l--) {
    s=seq[e];
    r = s >> l;
     if(r & 1) {
		 vetor[7-l]=1;
       cout<<"1";
     } else {
		 vetor[7-l]=0;
       cout << "0";
     }
		fprintf(arquivo2,"%d \n", vetor[7-l] );	
 }
}
	fclose(arquivo2);
//____________________________3 AUTOMATO PART__________________________________________________________

int colunas,linhas, regra,rest,m,a,N,lin, bin[8], anterior[100000],atual[100000];
FILE *arquivo3, *arquivo4;           
  


/* Get input data */
       colunas=1184; //columns
       linhas=10000; //automaton lines
       regra=84; //rules

//Changes the rule from decimal to 8-digit binary.
	
	for(int l = 7; l >= 0; l--) {
	rest = regra >> l;
	if(rest & 1) {
       bin[7-l]=1;
     } 
     else {
        bin[7-l]=0;
     }
	 cout << bin[7-l];
	}
	
	cout << endl;

//READ A FILE WITH THE PROTEIN SEQUENCE IN BINARY
	arquivo3 = fopen("initial_1.txt", "rt");    
	


	for(m=0; m<colunas;m++){
		
		fscanf(arquivo3," %d \n", &atual[m]);
		cout << "the entrace" << m<< "is "<< atual[m]<< endl;
	
		}
	
fclose(arquivo3);

//CREATE A FILE WITH THE PROTEIN SEQUENCE IN BINARY
	arquivo4 = fopen("automato_1.txt", "wt");    
	
	
// Shows the first line that was typed
		for(m=0; m<colunas;m++){
		cout << atual[m];
		fprintf(arquivo4,"%d \t", atual[m]);
		}
		fprintf(arquivo4,"\n");
		
// Swap the current line for the old one
	for(m=0; m<colunas;m++){
		anterior[m]=atual[m];
		}
		cout << endl;
		
// Neighborhood analysis and use of the evolution rule
for(lin=2;lin<=linhas;lin++){
	N=colunas;
	for(a=0; a<N;a++){
		if(a==0){
			if((anterior[N-1]==1 && anterior[a]==1) && anterior[a+1]==1){
				atual[a]=bin[0];
				
				}
			else if((anterior[N-1]==1 && anterior[a]==1) && anterior[a+1]==0){
				atual[a]=bin[1];
				
				}
			else if((anterior[N-1]==1 && anterior[a]==0) && anterior[a+1]==1){
				atual[a]=bin[2];
				
				}
			else if((anterior[N-1]==1 && anterior[a]==0) && anterior[a+1]==0){
				atual[a]=bin[3];
			
				}
			else if((anterior[N-1]==0 && anterior[a]==1) && anterior[a+1]==1){
				atual[a]=bin[4];
				
				}
			else if((anterior[N-1]==0 && anterior[a]==1) && anterior[a+1]==0){
				atual[a]=bin[5];
				
				}
			else if((anterior[N-1]==0 && anterior[a]==0) && anterior[a+1]==1){
				atual[a]=bin[6];
				
				}
			 else if((anterior[N-1]==0 && anterior[a]==0) && anterior[a+1]==0){
				atual[a]=bin[7];
				
				}
				
			}
		else if(a==N-1){
			if((anterior[a-1]==1 && anterior[a]==1 )&& anterior[0]==1){
				atual[a]=bin[0];
				}
			else if((anterior[a-1]==1 && anterior[a]==1) && anterior[0]==0){
				atual[a]=bin[1];
				}
			else if((anterior[a-1]==1 && anterior[a]==0) && anterior[0]==1){
				atual[a]=bin[2];
				}
			else if((anterior[a-1]==1 && anterior[a]==0) && anterior[0]==0){
				atual[a]=bin[3];
				}
			else if((anterior[a-1]==0 && anterior[a]==1) && anterior[0]==1){
				atual[a]=bin[4];
				}
			else if((anterior[a-1]==0 && anterior[a]==1) && anterior[0]==0){
				atual[a]=bin[5];
				}
			else if((anterior[a-1]==0 && anterior[a]==0) && anterior[0]==1){
				atual[a]=bin[6];
				}
			else if((anterior[a-1]==0 && anterior[a]==0) && anterior[0]==0){
				atual[a]=bin[7];
				}
				
			}
		else {
			if((anterior[a-1]==1 && anterior[a]==1) && anterior[a+1]==1){
				atual[a]=bin[0];
				}
			else if((anterior[a-1]==1 && anterior[a]==1) && anterior[a+1]==0){
				atual[a]=bin[1];
				}
			else if((anterior[a-1]==1 && anterior[a]==0) && anterior[a+1]==1){
				atual[a]=bin[2];
				}
			else if((anterior[a-1]==1 && anterior[a]==0) && anterior[a+1]==0){
				atual[a]=bin[3];
				}
			else if((anterior[a-1]==0 && anterior[a]==1) && anterior[a+1]==1){
				atual[a]=bin[4];
				}
			else if((anterior[a-1]==0 && anterior[a]==1) && anterior[a+1]==0){
				atual[a]=bin[5];
				}
			else if((anterior[a-1]==0 && anterior[a]==0) && anterior[a+1]==1){
				atual[a]=bin[6];
				}
			else if(anterior[a-1]==0 && anterior[a]==0 && anterior[a+1]==0){
				atual[a]=bin[7];
				}
	
			}
		
	}
// prints the current line that was obtained with the rule
	for(m=0; m<N;m++){
	cout << atual[m];
	fprintf(arquivo4,"%d \t", atual[m]);
	}
	
	fprintf(arquivo4,"\n");	
// swap the current line with the previous one

	for(m=0; m<N;m++){
	anterior[m]=atual[m];
	}
	cout << endl;
}
fclose(arquivo4);
  auto end = steady_clock::now(); 
  auto elapsed = end-start;  // CALCULATE RUN TIME
  //cout << elapsed.count() << "ns\n"; // CALCULATE RUN TIME IN NANOSECONDS
   cout << duration<double>{elapsed}.count();



return 0;
}
