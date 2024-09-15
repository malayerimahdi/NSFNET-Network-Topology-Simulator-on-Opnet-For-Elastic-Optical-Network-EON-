/* Process model C++ form file: malayeryprocess2.pr.cpp */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char malayeryprocess2_pr_cpp [] = "MIL_3_Tfile_Hdr_ 145A 30A modeler 7 5E1D9022 5E1D9022 1 ali-PC ali 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1e80 8                                                                                                                                                                                                                                                                                                                                                                                                               ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */

#define release_pk ((op_intrpt_type ()== OPC_INTRPT_SELF) && (op_intrpt_code () < 20000000))//interupt haye state diagram
#define rcv_pk   ((op_intrpt_type () == OPC_INTRPT_STRM )  && (op_intrpt_code () == -1))
#define end_ls  (op_intrpt_type () == OPC_INTRPT_ENDSIM)
#define reserv ((op_intrpt_type () == OPC_INTRPT_STRM ) && (op_intrpt_code () == -2))
//#define defrag  ((op_intrpt_type () == OPC_INTRPT_SELF) &&  (op_intrpt_code () >= 30000000))
#include <fstream>
#include <iostream>
#include <cmath>
#include <iostream>
//#include <fstream>
#include <string> 
#include <vector>
#include <windows.h>
#include <math.h> 
using namespace std;
int adrescounter=0;
int classes[7][3];
int BVTNO=50;
int trtr=0;
//int LINKFSs=1000;
short int KSP[14][14][3][10];// My Path_Nodes
int linkss[14][14];
//int paths_node[15][15][4][3][15];
//int links_fs[44][1001];// 44 linke rafto bargasht ke harkodoom 1000 fs daran
//int PATH[14][14][5][2][10];// [src][dest][k-shortest path][node/link][index of path]
int BOK,BNOK;
long int number_of_req;
long int number_of_nack;
long int number_of_ack; 
long int pktnom=0;
long int defragcounter=0;
long int bw_ack;//BW dade shode
long int bw_nack;// BW block shode
long int bw_req;// BW darkhasti
int defc=2;
//defcc=2;
int transmitter[15][11];//14 ta transmiter va 14 receiver  darim
int reciever[15][11];//harkodoom 10 ta BVT daran

int ff_rr;
char fname[40]="e:/malayeri/results/res.txt";

//int linkk_numbers[14][14]; // this will keep links number!
int link_number_counter=0;


///////////////////////////////////////////
//////////////////////////////////////////
///////////MY CODES BEGIN ///////////////
bool Transmitter_BVTs[14][50];
bool Receiver_BVTs[14][50];
long int Slots[9][42][1020];
long int TEslots[9][42][1020];
double times[9][42][1020];

///////////////////////////////////////////
//////////////////////////////////////////
/////////END oF MY CODES/////////////////

//////////////////////////////////////////
/////////new codes!!!////////////////////
///////////////////////////////////////
//slots_size=1000;
struct node {
	long  int id;
	double begin_time;
	double end_time;
	float holdingtime;
	int k;
	short int reroute_to_k;
	int path[10];
	int path_length;
	int start;
	int finish;
	int size;
	node *next, *previous;
	int source, destination;
	int bvt;
	int pre_free,post_free;
	float remaining_time;
	int dakhil;
	int label;// ==>Not Assigned yet:0 DM:1 Reroutable:2 Moved2Extra:3 Moveable:4 , Not Movable:5 , Transfer:6, untransferable:7 , rerouted: 8...
	int action_code;
	int situation;
	int available_reroutes[3][2];
	int available_reroutes_counter;
	int free_left[10];// for each link there are how many free slots on the left
	int free_right[10];
	int interfere_to[100][2];
	float pathcompression[10];
	float compression;
	int newfsstart;
	 int tbvt,rbvt;
	 short int lastreroutedk;
	short int core;
};
node *first,*end,*pp;

int defcc;
const int extra=30;
const int slots_size=250;
int temparray[1020];
double matrix[1000][9];
double normal_matrix[1000][9];
double move_weights[8];//={0.15,0.12,0.08,0.12,0.12,0.15,0.12,0.15};
double reroute_weights[6];//={0.25,0.13,0.13,0.06,0.25,0.18};
double transfer_weights[5];//={0.19,0.19,0.25,0.12,0.25};
double bestfit_weights[4];
double path_weights[6];
int move2extraindex[100];
int move2extracounter=0;

int untransferable[1000];
int lastpkno=0;
int arr[100][2];// this keeps the free blocks. first dimention is starting index in temparray and second is its size!
int temp_path[3][14];
struct packett {
    float simtime;
    short int source;
    short int dest;
    short int needed;
    float holding_time;
};


/* End of Header Block */

#if !defined (VOSD_NO_FIN)
#undef	BIN
#undef	BOUT
#define	BIN		FIN_LOCAL_FIELD(_op_last_line_passed) = __LINE__ - _op_block_origin;
#define	BOUT	BIN
#define	BINIT	FIN_LOCAL_FIELD(_op_last_line_passed) = 0; _op_block_origin = __LINE__;
#else
#define	BINIT
#endif /* #if !defined (VOSD_NO_FIN) */



/* State variable definitions */
class malayeryprocess2_state
	{
	private:
		/* Internal state tracking for FSM */
		FSM_SYS_STATE

	public:
		malayeryprocess2_state (void);

		/* Destructor contains Termination Block */
		~malayeryprocess2_state (void);

		/* State Variables */
		Distribution *	         		deftime                                         ;
		int	                    		matrix_counter                                  ;
		int	                    		linkk_numbers[14][14]                           ;
		int	                    		untransferable_counter                          ;
		double	                 		timeclass[7][2]                                 ;

		/* FSM code */
		void malayeryprocess2 (OP_SIM_CONTEXT_ARG_OPT);
		/* Diagnostic Block */
		void _op_malayeryprocess2_diag (OP_SIM_CONTEXT_ARG_OPT);

#if defined (VOSD_NEW_BAD_ALLOC)
		void * operator new (size_t) throw (VOSD_BAD_ALLOC);
#else
		void * operator new (size_t);
#endif
		void operator delete (void *);

		/* Memory management */
		static VosT_Obtype obtype;
	};

VosT_Obtype malayeryprocess2_state::obtype = (VosT_Obtype)OPC_NIL;

#define deftime                 		op_sv_ptr->deftime
#define matrix_counter          		op_sv_ptr->matrix_counter
#define linkk_numbers           		op_sv_ptr->linkk_numbers
#define untransferable_counter  		op_sv_ptr->untransferable_counter
#define timeclass               		op_sv_ptr->timeclass

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	malayeryprocess2_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((malayeryprocess2_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


/* Function Block */

#if !defined (VOSD_NO_FIN)
enum { _op_block_origin = __LINE__ + 2};
#endif


node * get_connection_by_id(int idx){
FIN (get_connection_by_id());


	int c=1;
	pp=first;
	while(pp){
	/*if(idx==2564){
	printf("\n****************\n %d -- %f",pp->id,pp->id);
	}*/
	if(pp->id == idx){
	//printf("\n FOUND idx:%d, id:%d",idx,pp->id);	
	break;
		
		}
	c++;
	//printf("\n pp->id:%d",pp->id);
	pp=pp->next;}
	if(pp==NULL){
		printf("\nERROR! Cannot Find the connection by ID! %d ==>cis%d",idx,c);
		
		
		//shows();
		printf("\n\n\n\nshowing TEslots[0]!!!\n\n\n");
		//show_TEslots[0]();
		return NULL;
	}
	
	return pp;
	FRET (pp);
}









int firstfit(int size,int from,int last){
FIN (firstfit());
	int res1=-1;
	int counter=0;
	bool flag=true;
	for (int i=from;i<=last-size+1;i++){
		flag=true;
		for (int j=0;j<size && i+j <=last;j++){
		
			if(temparray[i+j]!=0)
			{
				res1=-1;
				flag=false;
				counter=0;
				break;
			}
			else {
				counter++;
			}
		
		}
			if((flag) && (counter>=size)){
				res1=i;
			break;
			}
			else{
				counter=0;
				res1=-1;
			}
			
	}
	return res1;
	FRET (res1);
}

void update_time(node *p){
FIN (update_time());
	if (p->end_time>op_sim_time()){
		p->remaining_time=p->end_time - op_sim_time(); 
		for(int i=0;i<p->path_length;i++){
			for(int j=p->start;j<=p->finish;j++){
			times[0][p->path[i]][j]=p->remaining_time;
			if(p->remaining_time<0){
				times[0][p->path[i]][j]=0.0;
			printf("\n negative==>id=%d",p->id);}
			}
		}
	}
FOUT;
}


void update_time2(node *p){
FIN (update_time2());
	if (p->end_time>op_sim_time()){
		p->remaining_time=p->end_time - op_sim_time(); 
		for(int i=0;i<p->path_length;i++){
			for(int j=p->start;j<=p->finish;j++){
			times[p->core][p->path[i]][j]=p->remaining_time;
			if(p->remaining_time<0){
				times[p->core][p->path[i]][j]=0.0;
			printf("\n negative==>id=%d",p->id);}
			}
		}
	}
FOUT;
}


int get_BVT(bool sndorrcv,int index)// shomare BVT Ekhtesas midahad!
	{
	FIN (get_BVT());
	short int result=-1;
	if (sndorrcv)//Transmitter
		{
		for(int i=0;i<50;i++)
		if(Transmitter_BVTs[index][i]==false)
			{
		
			result=i;
			break;
		}
		}
		else//Receiver
		{
		for(int i=0;i<50;i++)
		if(Receiver_BVTs[index][i]==false)
			{
		
			result=i;
			break;
		}
		
		}
		//printf("\n its BVT get snd or rcs = %d , BVT=%d , index=%d",sndorrcv,result,index);
	return (result);
	FRET(result);
	
	}

int get_link_number(int src,int dest){// returns links number between src and dest
FIN(get_link_number());
return (linkk_numbers[src][dest]);
FRET(linkk_numbers[src][dest]);
}

int get_all_links_number(int *a,int src,int dest,int k){// returns all links of source and dest in Kth Path!
FIN(get_all_links_number());
//int result[10]={0,0,0,0,0,0,0,0,0,0};
int i=0;
while(KSP[src][dest][k][i+1]>-1){
a[i]=linkk_numbers[KSP[src][dest][k][i]][KSP[src][dest][k][i+1]];
i++;

}

return (i);
FRET (i) ;

}

int get_path_length2(int src,int dest,int k){// returns all links of source and dest in Kth Path!
FIN(get_path_length2());
//int result[10]={0,0,0,0,0,0,0,0,0,0};
int i=0;
int ll=0;
while(KSP[src][dest][k][i+1]>-1){
ll+=linkss[KSP[src][dest][k][i]][KSP[src][dest][k][i+1]];
i++;
}

return (ll);
FRET (ll) ;

}

 void shows(){
 FIN(shows());
	for (int g=0;g<42;g++)
	{
			printf("\n____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
		for(int h=0;h<slots_size+extra;h++){
		

	
		printf("|%7d",Slots[0][g][h]);}
		printf("|***%d",g);
		
	}
		printf("\n____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
		FOUT;
}
 
 
 
 
 
void zero_matrix(){
FIN(zero_matrix());
	for(int i=0;i<1000;i++)
	for (int j=0;j<9;j++)
	matrix[i][j]=0.0;
FOUT;
}

void zero_normal_matrix(){
FIN (zero_normal_matrix());
	for(int i=0;i<1000;i++)
	for (int j=0;j<9;j++)
	normal_matrix[i][j]=0.0;
FOUT;
}

void zero_temparray(int size){
FIN (zero_temparray());
	for(int i=0;i<size;i++)
	temparray[i]=0;
FOUT;
}

void show_TEslots(){
FIN (show_TEslots());
	for (int g=0;g<42;g++)
	{
			printf("\n___________________________________________________________________________________________________________________________________________________________________________________________________\n");
		for(int h=0;h<slots_size + extra;h++){
		

	
		printf("|%3d",TEslots[0][g][h]);}
		printf("|");
		
	}
		printf("\n___________________________________________________________________________________________________________________________________________________________________________________________________\n");
		FOUT;
}



void get_situation(int links[], int link_number,int size){
	FIN (get_situation());
	for(int i=0;i<link_number;i++){
		for(int j=0;j<size;j++){
				if ((temparray[j]==0) && (Slots[0][links[i]][j]==0)){
					temparray[j]=0;
				}
				else
				temparray[j]=1;
			
		}
	
		
}
	FOUT;
	
}


void get_situation2(int links[], int link_number,int size,int core){
	FIN (get_situation2());
	for(int i=0;i<link_number;i++){
		for(int j=0;j<size;j++){
				if ((temparray[j]==0) && (Slots[core][links[i]][j]==0)){
					temparray[j]=0;
				}
				else
				temparray[j]=1;
			
		}
	
		
}
	FOUT;
	
}


int pre_free(node *p){
FIN(pre_free());
	int result=0;
	int temp=0;
	for (int i=0;i<p->path_length;i++){
		for (int j=(p->start)- 1;j>=0;j--){
			if (Slots[0][p->path[i]][j]==0){
			
			temp++;}
			else{
					
					break;
			}
		
			
		}
		result+=temp;
		p->free_left[i]=temp;
		temp=0;
	}
	return result;
	FRET (result);
	
}


int pre_free2(node *p){
FIN(pre_free2());
	
	int result=0;
	int temp=0;
	for (int i=0;i<p->path_length;i++){
	p->free_left[i]=0;
		for (int j=(p->start)- 1;j>=0;j--){
			if (Slots[p->core][p->path[i]][j]==0){
			
			temp++;}
			else{
					
					break;
			}
		
			
		}
		result+=temp;
		p->free_left[i]=temp;
		temp=0;
	}
	return result;
	FRET (result);
	
}


int post_free(node *p){
FIN (post_free());
	int result=0;
	int temp=0;
	for (int i=0;i<p->path_length;i++){
		for (int j=(p->finish)+ 1;j<slots_size;j++){
			if (Slots[0][p->path[i]][j]==0)
			temp++;
			else{
					
					break;
			}
		
			
		}
		result+=temp;
		p->free_right[i]=temp;
		temp=0;
	}
	return result;
	FRET (result);
}





void generate_temparray_by_k(int src,int dest,int k){
FIN (generate_temparray_by_k());	
int link[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
//printf("\n ITS 	generate_temparray_by_k src is:%d dest is:%d k is: %d",src,dest,k);
short int c;
	int t1;
	t1=src;
	//link[0]=links[src][KSP[src][dest][k][1]];
	for(int i=1;i<10;i++){
		if(KSP[src][dest][k][i]<0){
		c=i;
		break;
		
		}
		
		else{
		if(get_link_number(KSP[src][dest][k][i-1],KSP[src][dest][k][i])<0)
			printf("\nERRRRROOOOOOOOOOOR111==>src:%d des:%d k:%d i-1 :%d , i: %d",src,dest,k,i-1,i);
			
			link[i-1]=get_link_number(KSP[src][dest][k][i-1],KSP[src][dest][k][i]);
			//printf("\n k is:%d link [%d]=%d",k,i-1,link[i-1]);
		}
	}
	zero_temparray(slots_size+extra);
	get_situation(link,c-1,slots_size+extra);
	FOUT;
}


int pathlength(int src,int dest,int k){
FIN (pathlength());
	int i=1;
	int counter=0;

if(k<0){
	printf("\n==> ERROR!!! K is negative! :%d",k);
	return (-1);
	FRET (-1);
}
	while((KSP[src][dest][k][i])>=0){
	  	i++;
		counter++;
	}
	//printf("\n ==> path src: %d , dest: %d ,k:%d,length:%d",src,dest,k,counter);
	return counter;
	FRET (counter);
}


void zero_TEslots(){
FIN (zero_TEslots());
	for(int i=0;i<42;i++)
		for(int j=0;j<slots_size +extra ;j++)
			TEslots[0][i][j]=0;
FOUT;
}

void initiate_TEslots(){
FIN (initiate_TEslots());
zero_TEslots();
	for(int i=0;i<42;i++)
		for(int j=0;j<slots_size+extra;j++)
			TEslots[0][i][j]=Slots[0][i][j];
FOUT;
}

double TEslots_compression(int link){
FIN (TEslots_compression());
	double res1=0.0;
	 int sum=0;
	 int counter=0;
	for(int i=0;i<slots_size;i++){
		if(TEslots[0][link][i]==0){
			sum++;
		}else{
			if(sum>0){
				res1+=(double) 1/sum;
				sum=0;
				counter++;
			}
		}
	}
	if(sum>0){
				res1+=(double) 1/sum;
				sum=0;
				counter++;
			}
	return (res1 * counter)/((slots_size/2)*(slots_size/2));
	FRET ((res1 * counter)/((slots_size/2)*(slots_size/2)));
}	

double set_TEslots(node *p,int start, int size,int src, int dest,int k){// this is for moving connections to get new compression after moveing!
	FIN (set_TEslots());
	initiate_TEslots();
	for(int i=0;i<p->path_length;i++){
		for(int j=p->start;j<=p->finish;j++){
			TEslots[0][p->path[i]][j]=0;
		}
	}
	// set new FSs in new place and route!
	int l=pathlength(src,dest,k);
	double tmp=0.0;
	
	int t=src;
	for (int x=1;x<l;x++){
		int ll=get_link_number(t,KSP[src][dest][k][x]);
		if(ll<0)
			printf("\nERRRRROOOOOOOOOOOR444");
		for(int y=start;y<=start+(p->size);y++){
			TEslots[0][ll][y]=p->id;
		}
		tmp+=TEslots_compression(ll);
		
		t=KSP[src][dest][k][x];
	}
	return (double) tmp/l;
	FRET ((double) tmp/l);
}



bool check4reroutable(node *p){// shoud be checked every time!
FIN (check4reroutable());
bool res1=false;
		
	if(p==NULL){
	printf("\n *********\n ERROR!");
	return false;}
	if ((p->label==3) || (p->label==1) || (p->label==8)){
		return false;
	}
	short int c=0;
	p->available_reroutes_counter=0;
	for(int i=0;i<3;i++){
		p->available_reroutes[i][0]=-1;
		p->available_reroutes[i][1]=-1;
		if(i!=p->k){
			int s;
			zero_temparray(slots_size+extra);
			generate_temparray_by_k(p->source,p->destination,i);
			s=firstfit(p->size +1 ,0,slots_size);
			if(s>=0){
				p->available_reroutes[c][0]=i;
				p->available_reroutes[c][1]=s;
				c++;
				
			}
		}
	}
	p->available_reroutes_counter=c;
	if(c>0){
	if(c>2)
	printf("ERROR in check4reroutable");
	if (c==2){// checking for min route be on 0 index of p->available_reroutes!!!
	
		int min=pathlength(p->source,p->destination,p->available_reroutes[0][0]);
		if (pathlength(p->source,p->destination,p->available_reroutes[1][0])<min){
		if(p->lastreroutedk!=p->available_reroutes[0][0]){
			int tmp=0;
			int tmp2=0;
			tmp=p->available_reroutes[0][0];
			tmp2=p->available_reroutes[0][1];
			p->available_reroutes[0][0]=p->available_reroutes[1][0];
			p->available_reroutes[0][1]=p->available_reroutes[1][1];
			p->available_reroutes[1][0]=tmp;
			p->available_reroutes[1][1]=tmp2;
		}
		}
	}
	p->label=2;
	res1=true;}
	else
	res1=false;
	if(p->lastreroutedk==p->available_reroutes[0][0])
		res1=false;
	return res1;
	FRET (res1);
}


bool chk4rr2(node *p){// shoud be checked every time!
FIN (chk4rr2());
bool res1=false;
		
	if(p==NULL){
	printf("\n *********\n ERRORchk4rr2!");
	return false;}
	if ((p->label==3) || (p->label==1) || (p->label==8)){
		return false;
	}
	short int c=0;
	p->available_reroutes_counter=0;
	for(int i=0;i<3;i++){
		p->available_reroutes[i][0]=-1;
		p->available_reroutes[i][1]=-1;
		if(i!=p->k){
			int s;
			zero_temparray(slots_size+extra);
			generate_temparray_by_k(p->source,p->destination,i);
			s=firstfit(p->size +1 ,0,slots_size);
			if(s>=0){
				p->available_reroutes[c][0]=i;
				p->available_reroutes[c][1]=s;
				c++;
				
			}
		}
	}
	p->available_reroutes_counter=c;
	if(c>0){
	if(c>2)
	printf("ERROR in check4reroutable");
	if (c==2){// checking for min route be on 0 index of p->available_reroutes!!!
	
		
		if ((p->lastreroutedk==p->available_reroutes[0][0])||(set_TEslots(p,p->available_reroutes[0][1],p->size,p->source,p->destination,p->available_reroutes[0][0]))<(set_TEslots(p,p->available_reroutes[1][1],p->size,p->source,p->destination,p->available_reroutes[1][0]))){// or get_compression < get_compression
		
			int tmp=0;
			int tmp2=0;
			tmp= p->available_reroutes[0][0];
			tmp2=p->available_reroutes[0][1];
			p->available_reroutes[0][0]=p->available_reroutes[1][0];
			p->available_reroutes[0][1]=p->available_reroutes[1][1];
			p->available_reroutes[1][0]=tmp;
			p->available_reroutes[1][1]=tmp2;
			
			}
		
	}
	p->label=2;
	res1=true;}
	else
	res1=false;
	if(p->lastreroutedk==p->available_reroutes[0][0])
		res1=false;
	return res1;
	FRET (res1);
}



int interfere_right(node *p){// how many connections on the right cant move to left because of this
FIN (interfere_right());
int interfercounter=0;
for(int g=0;g<100;g++){
	p->interfere_to[g][0]=0;
	p->interfere_to[g][1]=0;
}
int lf=pre_free(p);
int rf=post_free(p);
int icounter=0;
for(int i=0;i<p->path_length;i++){
	
	for (int j=p->finish +1;j<slots_size;j++){
		
		if(Slots[0][p->path[i]][j] !=0){
		
			node *q=get_connection_by_id(Slots[0][p->path[i]][j]);
			if (q==NULL){
			printf("\n Error in interefere right!!!==> %d\n pathlength:%d , i:%d , j:%d src:%d , des:%d, k:%d",Slots[0][p->path[i]][j],p->path_length,i,j,p->source,p->destination,p->k);
			return 0;
			}
			int interfer=0;
			if((q->label!=1) || (q->label == 5)){ // **************** should be checked by other labels too!!!
				
					for(int y=0;y<q->path_length;y++){
						if(p->path[i]==q->path[y]){ // if this link is shared 
							if(p->free_left[i] >= q->size){ // then this connection dekhalat nadare too in link!
						//	printf("\n***the connection %d does not interfere connection %d on link %d from left side!\n***\n",p->id,q->id,p->path[i]);
								//continue;
							}
							else if(p->free_left[i] + p->size + p->free_right[i] >=q->size){
								interfer++;
							//	printf("\n###\nthe connection %d  interferes connection %d on link %d from left side!\n###\n",p->id,q->id,p->path[i]);
						bool flag=false;
							for( int e=0;e<icounter;e++){
								if(p->interfere_to[e][0]==(q->id)){
									p->interfere_to[e][1]++;
									flag=true;
								}
							}
							if(!flag){
								p->interfere_to[icounter][0]=(q->id);
								p->interfere_to[icounter][1]=1;
								icounter++;
							}
							}
						}
					}
				
				if(interfer>0){
						interfercounter++;
					//	printf("\n&&&&&&&&&&the connection %d  interferes connection %d from left side!\n&&&&&&&&&&&\n",p->id,q->id);

				}
				
		}
		j+=q->size;
	}
	
	
	
}
}
//printf("\n\n********************************\n\n");
//printf("the connection %d has %d interferes with %d connections\n",p->id,interfercounter,icounter);
//printf("\n the interferes:\n");
for (int v=0;v<interfercounter;v++){
	//printf("connection %d in %d links!\n",p->interfere_to[v][0],p->interfere_to[v][1]);
}
p->dakhil=icounter;
return icounter;
FRET (icounter);
}


void shortenadd2reroutematrix(node *p){
	FIN(shortenadd2reroutematrix());
	
//printf("\n Cid: %d,src:%d , dest:%d , k:%d , available reroute:%d\n",p->id,p->source,p->destination,p->k,p->available_reroutes[0][0]);
int newrt=pathlength(p->source,p->destination,p->available_reroutes[0][0]);	
if(newrt<p->path_length){
double ii=0.0;
int xc=0;
xc=(p->id);
ii=(double) xc;
	matrix[matrix_counter][0]=(p->path_length - newrt );// should be checked that new route is smaller???
	matrix[matrix_counter][1]=p->path_length;// it seems its better to consider new length!!!
	matrix[matrix_counter][2]=p->size;
	matrix[matrix_counter][3]=p->remaining_time;
	matrix[matrix_counter][4]=interfere_right(p);
	matrix[matrix_counter][5]=pre_free(p) + post_free(p);
	matrix[matrix_counter][8]= ii;
	
	matrix_counter++;
	
}
	FOUT;
}

bool exists(int idx){
FIN (exists());
node *o;
o=first;
bool f=false;
while(o){
if(o->id==idx)
	{
	f=true;
	break;
	}
o=o->next;
}
return (f);

FRET (f);

}

void shortencheck_and_mark_reroute(){// size is number of connections!
FIN (shortencheck_and_mark_reroute());
zero_matrix();
matrix_counter=0;

node *p=first;
while (p){

if(check4reroutable(p)){
		
			//f=fopen("log.txt","a+");
			
			//fprintf(f,"\nthe connection %d added to the matrix!\n",i);
				shortenadd2reroutematrix(p);
		//	fclose(f);
		}
p=p->next;

}



	//show_matrix();
	FOUT;
}


void show_normal_matrix(){
	FIN (show_normal_matrix());
			for(int i=0;i<matrix_counter;i++)
	{
		for (int j=0;j<9;j++)
		printf("|%5.2f",normal_matrix[i][j]);
		printf("\n________________________________________________\n");
	}
	FOUT;
}


void normal4move(int size){
FIN (normal4move());
	if(matrix_counter==0)
	return;
	int minmax[8]={0,0,0,0,0,0,0,0};
	for (int i=0;i<8;i++){// finding max and min for each param!
		if((i==1) || (i==4) || (i==7)){ // negative parameters! shoul find min
			for(int j=0; j<size; j++){ //finding min!
				if (matrix[j][i]<matrix[minmax[i]][i]){
					minmax[i]=j;
				}
			}
			
		} 
		else {  // positive parameters! should find max!
			for(int j=0; j<size; j++){ //finding max!
				if (matrix[j][i]>matrix[minmax[i]][i]){
					minmax[i]=j;
				}
			}
		}
		
		
	}// now max and min for each param is found!
	
	for (int i=0;i<8;i++){
		if((i==1) || (i==4) || (i==7)){// negative parameters!
			for(int j=0;j<size;j++){
				normal_matrix[j][8]=matrix[j][8];
				if(matrix[j][i]!=0)
			normal_matrix[j][i]=(double) (matrix[minmax[i]][i]/matrix[j][i]);	
			else
			normal_matrix[j][i]=1.0;//?????????? or 1????
			}
			
		}
		else{
			for (int j=0;j<size;j++){
				normal_matrix[j][8]=matrix[j][8];
				if(matrix[minmax[i]][i]==0){
					normal_matrix[j][i]=0.0;
				}else
				{
				
				if (matrix[j][i] !=0)
				normal_matrix[j][i]=(double) (matrix[j][i]/matrix[minmax[i]][i] );
				else
				normal_matrix[j][i]=0; //????? or 1 ?
			}
			}
			
		}
	}
//printf("\n notmal matrix is:\n");
//show_normal_matrix();
FOUT;
}

long int best4move(int size){
FIN (best4move());
	double max=0.0;
	int max_index=-1;
	double tmp=0.0;
	for (int i=0;i<size;i++){
		tmp=0.0;
		for (int j=0;j<8;j++){
			tmp+=(normal_matrix[i][j]*move_weights[j]);
		}
		if (tmp>max){
			max=tmp;
			max_index=i;
		}
	}
	//printf("\n\n ========> best 4 move max is:%f",max);
	return (( int) normal_matrix[max_index][8]);
	FRET  (( int) normal_matrix[max_index][8]);
}

void normal4reroute(int size){
FIN (normal4reroute());
	int minmax[6]={0,0,0,0,0,0};
	for (int i=0;i<6;i++){// finding max and min for each param!
		if((i==2)){ // negative parameters! shoul find min
			for(int j=0; j<size; j++){ //finding min!
				if (matrix[j][i]<matrix[minmax[i]][i]){
					minmax[i]=j;
				}
			}
			
		} 
		else {  // positive parameters! should find max!
			for(int j=0; j<size; j++){ //finding max!
				if (matrix[j][i]>matrix[minmax[i]][i]){
					minmax[i]=j;
				}
			}
		}
		
		
	}// now max and min for each param is found!
	
	for (int i=0;i<6;i++){
		if((i==2)){// negative parameters!
			for(int j=0;j<size;j++){
				normal_matrix[j][8]=matrix[j][8];
				if(matrix[j][i]!=0.0)
			normal_matrix[j][i]=(double) (matrix[minmax[i]][i]/matrix[j][i]);	
			else
			normal_matrix[j][i]=1.0;//?????????? or 1????
			}
			
		}
		else{
			for (int j=0;j<size;j++){
				normal_matrix[j][8]=matrix[j][8];
				if(matrix[minmax[i]][i]==0){//its false!
					normal_matrix[j][i]=0.0;
				}else{
				
				if (matrix[j][i] !=0.0)
				normal_matrix[j][i]=(double) (matrix[j][i]/matrix[minmax[i]][i] );
				else
				normal_matrix[j][i]=0.0; //????? or 1 ?
			}
			
		}
		}
	}
	FOUT;
}

int best4reroute(int size){
FIN (best4reroute());
	double max=0.0;
	int max_index=-1;
	double tmp=0.0;
	for (int i=0;i<size;i++){
		tmp=0.0;
		for (int j=0;j<6;j++){
			tmp+=(normal_matrix[i][j]*reroute_weights[j]);
		}
		if (tmp>max){
			max=tmp;
			max_index=i;
		}
	}
	return ((int) normal_matrix[max_index][8]);
	FRET  ( (int) normal_matrix[max_index][8]);
}


void normal4transfer(int size){
FIN (normal4transfer());
	int minmax[5]={0,0,0,0,0};
	for (int i=0;i<5;i++){// finding max and min for each param!
		if((i==3)){ // negative parameters! shoul find min
			for(int j=0; j<size; j++){ //finding min!
				if (matrix[j][i]<matrix[minmax[i]][i]){
					minmax[i]=j;
				}
			}
			
		} 
		else {  // positive parameters! should find max!
			for(int j=0; j<size; j++){ //finding max!
				if (matrix[j][i]>matrix[minmax[i]][i]){
					minmax[i]=j;
				}
			}
		}
		
		
	}// now max and min for each param is found!
	
	for (int i=0;i<5;i++){
		if((i==3)){// negative parameters!
			for(int j=0;j<size;j++){
				normal_matrix[j][8]=matrix[j][8];
				if(matrix[j][i]!=0)
			normal_matrix[j][i]=(double) (matrix[minmax[i]][i]/matrix[j][i]);	
			else
			normal_matrix[j][i]=1.0;//?????????? or 1????
			}
			
		}
		else{
			for (int j=0;j<size;j++){
				normal_matrix[j][8]=matrix[j][8];
				if(matrix[minmax[i]][i]==0){
					normal_matrix[j][i]=0.0;
				}else{
				
				
				if (matrix[j][i] !=0)
				normal_matrix[j][i]=(double) (matrix[j][i]/matrix[minmax[i]][i] );
				else
				normal_matrix[j][i]=0; //????? or 1 ?
			
		}
			
		}
	}
}
FOUT;
}

int best4transfer(int size){
FIN (best4transfer());
	double max=0.0;
	int max_index=-1;
	double tmp=0.0;
	for (int i=0;i<size;i++){
		tmp=0.0;
		for (int j=0;j<5;j++){
			tmp+=(normal_matrix[i][j]*transfer_weights[j]);
		}
		if (tmp>max){
			max=tmp;
			max_index=i;
		}
	}
	return ((int) normal_matrix[max_index][8]);
	FRET ((int) normal_matrix[max_index][8]);
}

double getdistance(node *p,int start,bool mode){// mode=true Slots mode=false : TEslots[0]
FIN (getdistance());	
//show_TEslots[0]();
	if(start==0)
	return 0.0;
	int res1=0.0;
	if((!mode) && (p->path_length>0)){
		for(int i=0;i<(p->path_length);i++){
		for(int j=start-1;j>=0;j--){
			if((TEslots[0][p->path[i]][j]==0) )
			res1++;
			else if ((TEslots[0][p->path[i]][j]>0) && (p->path[i]>=0)){
				node *q;
				
				
				int srch=(int) TEslots[0][p->path[i]][j];
				q=get_connection_by_id(srch);
				if(q==NULL){
				printf("\n Error in getdistance==>%d",srch);
				return 0;
				
				}
				if(q->label==1)//q is DM!
				break;
				else{
					res1+=q->size;
					j-=q->size;
					j++;// it is because of j-- in the loop!!! should be considered in the other functions too!
				}
			}
		}
	}
	}else if ((p->path_length>0)){
		for(int i=0;i<(p->path_length);i++){
		for(int j=start-1;j>=0;j--){
		if(p->path[i]<0)
			{
			printf("\n\n\n ERROR!!! in GETDISTANCE!\n PID:%d, i is :%d , P->path[i]:%d",p->id,i,p->path[i]);
			return -10;
			}
			if(Slots[0][p->path[i]][j]==0)
			res1++;
			else if ((Slots[0][p->path[i]][j]>0) && (p->path[i]>=0)){
				node *q;
				int srch=(int) Slots[0][p->path[i]][j] /1;
				q=get_connection_by_id(srch);
				if(q==NULL){
				printf("\n Error in getdistance222==>%d",srch);
				return 0;
				
				}
				if(q->label==1)//q is DM!
				break;
				else{
					res1+=q->size;
					j-=q->size;
					j++;// it is because of j-- in the loop!!! should be considered in the other functions too!
				}
			}
		}
	}
	}
	return (double) res1/p->path_length;
	FRET ((double) res1/p->path_length);
}


void reroute(node *p,int k,int s){
FIN (reroute());
	if(p->available_reroutes_counter>0){
		for(int i=0;i<p->path_length;i++){
			for(int j=p->start;j<=p->finish;j++){
			//if	(p->path[i]>0)
			Slots[0][p->path[i]][j]=0;
				
			}
			p->path[i]=-1;
		}
			int t=p->source;
			int l=pathlength(p->source,p->destination,k);
			p->path_length=l;
			for (int x=1;x<=l;x++){
		int ll=get_link_number(t,KSP[p->source][p->destination][k][x]);
		
		if(ll<0)
			printf("\nERRRRROOOOOOOOOOOR222");
		p->path[x-1]=ll;
		for(int y=s;y<=s+p->size;y++){
			Slots[0][ll][y]=p->id;
		}
	
		t=KSP[p->source][p->destination][k][x];
	}
		p->start=s;
		p->finish=s+(p->size);
		p->lastreroutedk=p->k;
		p->k=k;
		p->label=8;
		double ttt=getdistance(p,p->start,true);
		if(ttt==1)
		p->label=1;
	}
	else
	printf("\nCannot RERoute!!!\n");
	FOUT;
}


bool shortenlengthes(){
FIN(shortenlengthes());
	zero_matrix();
	zero_normal_matrix();
	matrix_counter=0;
	bool flag=false;
	shortencheck_and_mark_reroute();
	
	if(matrix_counter>0){
		normal4reroute(matrix_counter);
		 int res1=best4reroute(matrix_counter);
		if(res1==2564)
			printf("\nsalam 2564 shortend!");
	node *p;
		
		
		
		
	p=get_connection_by_id(res1);
		if(p!=NULL){
	reroute(p,p->available_reroutes[0][0],p->available_reroutes[0][1]);
	flag=true;}
		else {
		
				printf("\n Error in shorten==>%d",res1);
				
		}
	}
	return flag;
	FRET (flag);
}

void removelabel(){
FIN (removelabel());
	node *p;
	p=first;
	while (p){
		if((p->label!=3)){// && (p->label!=1))
		p->label=0;}
		double dis=getdistance(p,p->start,true);
		if(dis==1){
		p->label=1;
		}
		p=p->next;
		}
FOUT;
}










void show_matrix(){
FIN (show_matrix());
	for(int i=0;i<matrix_counter;i++)
	{
		for (int j=0;j<slots_size;j++)
		printf("|%5.2f",matrix[i][j]);
		printf("\n________________________________________________\n");
	}
FOUT;
}



void transfer2extrabyk(node *p,int k){
FIN(transfer2extrabyk());
//printf("\n this is 	transfer2extrabyk!");		
int s=0;
			zero_temparray(slots_size + extra);
			generate_temparray_by_k(p->source,p->destination,k);
			s=firstfit(p->size+1,slots_size,slots_size + extra -1);
			if(s>=slots_size){
				for(int i=0;i<p->path_length;i++){
					for(int j=p->start;j<=p->finish;j++){
						Slots[0][p->path[i]][j]=0;
					}
					p->path[i]=-1;
				}
				
			int t=p->source;
			int l=pathlength(p->source,p->destination,k);
			p->path_length=l;
			for (int x=1;x<=l;x++){
		int ll=get_link_number(t,KSP[p->source][p->destination][k][x]);
		
		if(ll<0)
			printf("\nERRRRROOOOOOOOOOOR333");
		//printf("\n k is %d, length is :%d link[%d]:%d",k,l,x-1,ll);
		p->path[x-1]=ll;
		for(int y=s;y<=s+p->size;y++){
			Slots[0][ll][y]=p->id;
		}
	
		t=KSP[p->source][p->destination][k][x];
		}
		p->start=s;
		p->finish=s+(p->size) ;
				p->label=3;// label to moved2extra!
			
		}
FOUT;
}

int check4transferable(node *p){// if positive: transferable on this links. if negative transferable on rerout -k, if zero, not transferable!!!
	FIN (check4transferable());
		int res1=0;
		zero_temparray(slots_size + extra);
		get_situation(p->path, p->path_length,slots_size + extra);
		int fs=firstfit(p->size+1,slots_size,slots_size + extra -1);
	//printf("\n in check4 : p is : %d , size is : %d , new fs is : %d  , src: %d , des:%d . k:%d , remaintime: %f",p->id,p->size, fs,p->source,p->destination,p->k,p->remaining_time);
		if(fs>slots_size -1){
		res1=fs;}
		else{
			
			for(int i=0;i<3;i++){
				if(i!=p->k){
			int s=0;
			zero_temparray(slots_size + extra);
			generate_temparray_by_k(p->source,p->destination,i);
			s=firstfit(p->size+1,slots_size,slots_size + extra -1);
			if(s>=slots_size){
			//printf("\n in check4 for K!!!: p is : %d , size is : %d , new fs is : %d  , src: %d , des:%d . k:%d , remaintime: %f",p->id,p->size, s,p->source,p->destination,i,p->remaining_time);
	
			res1=-1*(i+1);
			break;
			}
		}
	}
			
			
			
		}	
		
		return res1;
		FRET (res1);
	}


void transfer2extrabystart(node *p,int fs){
FIN (transfer2extrabystart());
	for(int i=0;i<p->path_length;i++){
		
			for(int j=p->start;j<=p->finish;j++)
					Slots[0][p->path[i]][j]=0; // zero current place!
			
			for(int z=0;z<=p->size;z++)
			Slots[0][p->path[i]][fs+z]=p->id;

}
	p->start=fs;
	p->finish=fs+(p->size );
	p->label=3;
	FOUT;
}

void add2untransferable(int x){
FIN (add2untransferable());
	bool f=false;
	for(int i=0;i<untransferable_counter;i++){
		if (untransferable[i]==x){
		
		f=true;
		break;}
	}
	if (!f){
			untransferable[untransferable_counter]=x;
			untransferable_counter++;
	}
	FOUT;
}


bool transfer2extra(int rt){
FIN (transfer2extra());
	bool lk=false;
	node* p;

	p=get_connection_by_id(rt);
if(p==NULL){
printf("\n Error intransfer2extra==>%d",rt);
return false;
}
	int x=check4transferable(p);
	if(x>0){
		transfer2extrabystart(p,x);
		lk=true;
		//printf("\n transfer by start %d ",idx);
	}
	else if (x<0){
	int nk=(x+1);
	if(nk!=0)
		nk*=-1;
	
		transfer2extrabyk(p,nk);
		lk=true;
		//printf("\n transfer by k %d ",idx);
	}
	else{
		lk=false;
		add2untransferable(rt);
		//printf("\n ===============> \n ERROR!!! in transfer2extra!!! %d \n",idx);
		p->label=7;
	
	}
	
return lk;
FRET (lk);
}




// going to code!!!
bool move2extra1(int re){
FIN (move2extra1());
		zero_temparray(slots_size+extra);
	bool res1=false;	
	node *p;
	p=first;
	while ((p->id) != re){
	p=p->next;	
	}
if(p==NULL){
printf("\n Error in move2extra1!!!");
return false;

}
	get_situation(p->path, p->path_length,slots_size+extra);
	int fs=firstfit(p->size+1,slots_size+extra,slots_size+extra -1);
	if(fs>-1){
	//	printf("\n new FSs found in Extra Space:%d\n",fs);
		for(int i=0;i<p->path_length;i++){
		
			for(int j=p->start;j<=p->finish;j++)
					Slots[0][p->path[i]][j]=0; // zero current place!
			
			for(int z=0;z<=p->size;z++)
			Slots[0][p->path[i]][fs+z]=re;
				
	
			}
		p->start=fs;
		p->finish=fs+(p->size );
		p->label=3;
		res1=true;
	}else{
		//try to reroute in extra space!!!
		//printf("\n need to reroute connection %d in Extra Area!",idx);
		
	bool ree=transfer2extra(re);
			
		res1=ree;
	}

	//show();
	return res1;
	FRET (res1);
}

void finddying4move2extra(){
FIN (finddying4move2extra());
	node *q;
	q=first;
	for(int i=0;i<100;i++)
	move2extraindex[i]=-1;
	move2extracounter=0;
	while(q!=NULL){
	
	if (q->remaining_time<1){
		move2extraindex[move2extracounter]=q->id; // behtare in araye az noe node bashe va toosh ro az esharegar ha por konim na id!
		move2extracounter++;
	}
	q=q->next;
}
FOUT;
}

bool check4untransferable(int x){
FIN (check4untransferable());
bool r=false;
	for(int i=0;i<untransferable_counter;i++){
	if(untransferable[i]==x){
		r=true;
	break;
	}
		
	}
	return r;
	FRET (r);
}


void add2transfermatrix(node *p){
FIN (add2transfermatrix());
//	printf("\n adding to transfer matrix!\n Cid: %d,src:%d , dest:%d , k:%d , size:%d, new FS start:%d\n",p->id,p->source,p->destination,p->k,p->size,nfs);
double ii=0.0;
int xc=0;
xc=(p->id);
ii=(double) xc;	
	matrix[matrix_counter][0]=p->size;
	matrix[matrix_counter][1]=p->path_length;// it seems its better to consider new length!!!
	matrix[matrix_counter][2]=interfere_right(p);
	matrix[matrix_counter][3]=p->remaining_time;
	matrix[matrix_counter][4]=pre_free(p) + post_free(p);
	matrix[matrix_counter][8]=ii;
	
	
	matrix_counter++;
	
	FOUT;
}




void finddying4move2extra2(){
FIN (finddying4move2extra2());
	node *q;
	q=first;
	for(int i=0;i<100;i++)
	move2extraindex[i]=-1;
	move2extracounter=0;
	while(q!=NULL){
	
	if ((q->remaining_time<2) && (q->label!=3) && (!check4untransferable(q->id))){
		add2transfermatrix(q);
	}
	q=q->next;
}
FOUT;
}

void move_dyings(){
	FIN (move_dyings());

	
	
	for(int i=0;i<move2extracounter;i++){
		move2extra1(move2extraindex[i]);
	}
	FOUT;
}




bool check4reroutable2(int idx){// shoud be checked every time!
FIN (check4reroutable2());	
bool res1=false;
	node *p;

		

	p=get_connection_by_id(idx);
	
	if(p==NULL){
	printf("\n *********\n ERROR!");
	return false;}
	if ((p->label==3) || (p->label==1) || (p->label==8)){
		return false;
	}
	short int c=0;
	p->available_reroutes_counter=0;
	for(int i=0;i<3;i++){
		p->available_reroutes[i][0]=-1;
		p->available_reroutes[i][1]=-1;
		if(i!=p->k){
			int s;
			zero_temparray(slots_size+extra);
			generate_temparray_by_k(p->source,p->destination,i);
			s=firstfit(p->size+1,slots_size,slots_size+extra -1);
			//printf("\n its check4reroutable2!");
			//printf("new fs is :%d , id : %d",s,idx);
			if(s>=slots_size){
				p->available_reroutes[c][0]=i;
				p->available_reroutes[c][1]=s;
				c++;
				
			}
		}
	}
	p->available_reroutes_counter=c;
	if(c>0){
	if(c>2)
	printf("ERROR in check4reroutable");
	if (c==2){// checking for min route be on 0 index of p->available_reroutes!!!
		int min=pathlength(p->source,p->destination,p->available_reroutes[0][0]);
		if (pathlength(p->source,p->destination,p->available_reroutes[1][0])<min){
			int tmp=0;
			int tmp2=0;
			tmp=p->available_reroutes[0][0];
			tmp2=p->available_reroutes[0][1];
			p->available_reroutes[0][0]=p->available_reroutes[1][0];
			p->available_reroutes[0][1]=p->available_reroutes[1][1];
			p->available_reroutes[1][0]=tmp;
			p->available_reroutes[1][1]=tmp2;
		}
	}
	p->label=2;
	res1=true;}
	else
	res1=false;
	return res1;
	FRET (res1);
}


void add2reroutematrix(node *p){
	FIN(add2reroutematrix());
	
//printf("\n Cid: %d,src:%d , dest:%d , k:%d , available reroute:%d\n",p->id,p->source,p->destination,p->k,p->available_reroutes[0][0]);
int newrt=pathlength(p->source,p->destination,p->available_reroutes[0][0]);	
	double ii=0.0;
int xc=0;
xc=(p->id);
ii=(double) xc;
	matrix[matrix_counter][0]=(p->path_length - newrt );// should be checked that new route is smaller???
	matrix[matrix_counter][1]=p->path_length;// it seems its better to consider new length!!!
	matrix[matrix_counter][2]=p->size;
	matrix[matrix_counter][3]=p->remaining_time;
	matrix[matrix_counter][4]=interfere_right(p);
	matrix[matrix_counter][5]=pre_free(p) + post_free(p);
	matrix[matrix_counter][8]=ii;
	
	matrix_counter++;
	
	FOUT;
}


void check_and_mark_reroute(){// size is number of connections!
FIN (check_and_mark_reroute());
zero_matrix();
matrix_counter=0;
node *p=first;
while(p){

if(chk4rr2(p)){
		
			
			add2reroutematrix(p);
			
		}
p=p->next;
}

	//show_matrix();
	FOUT;
}







int interfere_left(node *p){ // how many connections on the left on current connection cant move because of this!
FIN(interfere_left());	
int interfercounter=0;
	for(int g=0;g<100;g++){
	p->interfere_to[g][0]=0;
	p->interfere_to[g][1]=0;
}
	int lf=pre_free(p);
int rf=post_free(p);
for(int i=0;i<p->path_length;i++){
	
	for (int j=0;j<p->start;j++){
		
		if(Slots[0][p->path[i]][j] !=0){
		
			node *q=get_connection_by_id(Slots[0][p->path[i]][j]);
			int interfer=0;
			if((q->label!=1) || (q->label == 5)){ // **************** should be checked by other labels too!!!
				for (int x=0;x<p->path_length;x++){
					for(int y=0;y<q->path_length;y++){
						if(p->path[x]==q->path[y]){ // if this link is shared 
							if((p->free_right[x]) >= (q->size)){ // then this connection dekhalat nadare too in link!
							//printf("\n***the connection %d does not interfere connection %d on link %d from right side!\n***\n",p->id,q->id,p->path[i]);
								//continue;
							}
							else if(p->free_right[x] + p->size >=q->size){
								interfer++;
								//printf("\n###the connection %d  interferes connection %d on link %d from right side!\n###\n",p->id,q->id,p->path[i]);
							
							}
						}
					}
				}
				if(interfer>0){
						interfercounter++;
						//printf("\n&&&&&&&&&&the connection %d  interferes connection %d from right side!\n&&&&&&&&&&&\n",p->id,q->id);

				}
				
		}
		j+=q->size;
	}
	
	
	
}
}
return interfercounter;
FRET(interfercounter);
}



	



double get_compression(int link){
FIN (get_compression());
	double res1=0.0;
	 int sum=0;
	 int counter=0;
	for(int i=0;i<slots_size;i++){
		if(Slots[0][link][i]==0){
			sum++;
		}else{
			if(sum>0){
				res1+=(double) 1/sum;
				sum=0;
				counter++;
			}
		}
	}
	if(sum>0){
				res1+=(double) 1/sum;
				sum=0;
				counter++;
			}
	return (res1 * counter)/((slots_size/2)*(slots_size/2));
	FRET ((res1 * counter)/((slots_size/2)*(slots_size/2)));
}	
	
void set_connection_compression(node *p){
FIN (set_connection_compression());
double tmp=0.0;
	for(int i=0;i<p->path_length;i++){
		p->pathcompression[i]=get_compression(p->path[i]);
		tmp+=p->pathcompression[i];
	}
	p->compression=(double) tmp/(p->path_length);
	FOUT;
}	







int check4moveable(node *p){
	FIN (check4moveable());
	int res1=-1;
	zero_temparray(slots_size + extra);
	get_situation(p->path,p->path_length,slots_size);
	res1=firstfit(p->size+1,0,p->start);
	if(res1==-1){
		p->label=5;
	}
	return res1;
	FRET (res1);
}


int check4moveable2(node *p){
	FIN (check4moveable2());
	int res1=-1;
	zero_temparray(slots_size + extra);
	get_situation(p->path,p->path_length,slots_size);
	res1=firstfit(p->size+1,0,slots_size);
	if(res1==-1){
		p->label=5;
	}
	return res1;
	FRET (res1);
}


void add2movematrix(node *p,int nfs){
FIN (add2movematrix());
//	printf("\n adding to move matrix!\n Cid: %d,src:%d , dest:%d , k:%d , size:%d, new FS start:%d\n",p->id,p->source,p->destination,p->k,p->size,nfs);
	//printf("\n matrix counter is :%d",matrix_counter);
double ii=0.0;
int xc=0;
xc=(p->id);
ii=(double) xc;	
matrix[matrix_counter][0]=pre_free(p) + post_free(p);// should be checked that new route is smaller???
	matrix[matrix_counter][1]=p->size;// it seems its better to consider new length!!!
	matrix[matrix_counter][2]=p->start;
	matrix[matrix_counter][3]=p->remaining_time;
	matrix[matrix_counter][4]=p->path_length;
	set_connection_compression(p);
	matrix[matrix_counter][5]=(p->compression) - (set_TEslots(p,nfs,p->size,p->source,p->destination,p->k));
	matrix[matrix_counter][6]=interfere_right(p);
	matrix[matrix_counter][7]= getdistance(p,nfs,false);
	matrix[matrix_counter][8]=ii;
	//for(int i=0;i<=8;i++)
		//printf("\n matrix [%d][%d]=%f",matrix_counter,i,matrix[matrix_counter][i]);
	
	matrix_counter++;
	
	FOUT;
}


void check_and_mark_move(){
FIN(check_and_mark_move());
zero_matrix();
zero_normal_matrix();
matrix_counter=0;
node *p;
p=first;
while (p){
p->newfsstart=-1;
if((p->label!=1) && (p->label!=3)){
int newfs=check4moveable(p);
		if(newfs>=0){
			add2movematrix(p,newfs);
			p->newfsstart=newfs;
			}
}

p=p->next;
}



FOUT;
}

void checkmovefromextra(){
FIN(checkmovefromextra());
zero_matrix();
zero_normal_matrix();
matrix_counter=0;
node *p;
p=first;
while (p){
p->newfsstart=-1;
if((p->label==3) && (p->remaining_time>2)){
int newfs=check4moveable2(p);
		if(newfs>=0){
			add2movematrix(p,newfs);
			p->newfsstart=newfs;
			}
}

p=p->next;
}



FOUT;
}

void move(node *p){
FIN (move());
//	if((nfs==0)|| dmneighbor)==> dm(p)
if(p->newfsstart>=0){
	for(int i=0;i<p->path_length;i++){
	for(int j=p->start;j<=p->finish;j++){
		Slots[0][p->path[i]][j]=0;
		Slots[0][p->path[i]][(p->newfsstart) +j-(p->start)]=p->id;
	}
	}
p->start=p->newfsstart;
p->finish=p->newfsstart + (p->size);
p->newfsstart=-1;
if(p->label!=3){
double d=getdistance(p,p->start,true);
if(d==1)
p->label=1;}
}else
printf("\n ERROR!!! there is no New Slots for connection %d!!!",p->id);


//if(get_distance(p,nfs)==0)// DM it!
//p->label=1;
FOUT;
}


void movefromextra(node *p){
FIN (movefromextra());
//	if((nfs==0)|| dmneighbor)==> dm(p)
if(p->newfsstart>=0){
	for(int i=0;i<p->path_length;i++){
	for(int j=p->start;j<=p->finish;j++){
		Slots[0][p->path[i]][j]=0;
		Slots[0][p->path[i]][(p->newfsstart) +j-(p->start)]=p->id;
	}
}
p->start=p->newfsstart;
p->finish=p->newfsstart + (p->size);
p->newfsstart=-1;
p->label=33;
if(p->label!=3){
double d=getdistance(p,p->start,true);
if(d==1)
p->label=1;}
}else
printf("\n ERROR!!! there is no New Slots[0] for connection %d!!!",p->id);


//if(get_distance(p,nfs)==0)// DM it!
//p->label=1;
FOUT;
}

void ckeck4transfer(){
FIN (ckeck4transfer());
zero_matrix();
zero_normal_matrix();
matrix_counter=0;
node *p=first;
while(p){

if ((p->label==5) || (p->label==6)){// or p->remaining_time<2 and p->interfere_right >1
	int tmp=0;
	tmp=check4transferable(p);
	if(tmp!=0)
	add2transfermatrix(p);
	}
p=p->next;
}





	FOUT;
}









void zero_untransferable(){
FIN (zero_untransferable());
	for(int i=0;i<1000;i++){
		untransferable[i]=-1;
	}
	untransferable_counter=0;
	FOUT;
}

void addnode(long int id, int k,int paths[], int path_length, int start,int finish, int size, int src,int dest, int tranmitterbvt,int receiverbvt,double hltime,double endtime){
FIN (addnode());



		node* node1;
		node1 = new node;
		node1->size=size;
		node1->id=id;
		node1->source=src;
		node1->destination=dest;
		node1->k=k;
		node1->lastreroutedk=k;
		node1->tbvt=tranmitterbvt;
		node1->rbvt=receiverbvt;
		node1->start=start;
		node1->finish=finish;
		node1->holdingtime=hltime;
		node1->path_length=path_length;
		node1->next = NULL;
		node1->remaining_time=endtime-op_sim_time();
		node1->end_time=endtime;
node1->core=0;
		//node1->nd=nx;?????
		//node1->core=core;
		node1->available_reroutes[0][0]=-1;
		node1->available_reroutes[1][0]=-1;
		node1->available_reroutes[2][0]=-1;
		node1->available_reroutes[0][1]=-1;
		node1->available_reroutes[1][2]=-1;
		node1->available_reroutes[2][3]=-1;
		node1->newfsstart=-1;
	
		node1->compression=0.0;
		for(int j=0;j<10;j++){
			node1->free_left[j]=0;
			node1->free_right[j]=0;
			node1->pathcompression[j]=0.0;
		}

		node1->label=0;

		for(int i=0;i<path_length;i++)
			node1->path[i]=paths[i];
		
		
		
		if(first == NULL)
			{
			
				first = node1;
				end=node1;
			}
		else
			{
				end->next=node1;
				end=node1;
			}
		
		




FOUT;
}



void addnode2(long int id, int k,int paths[], int path_length, int start,int finish, int size, int src,int dest, int tranmitterbvt,int receiverbvt,double hltime,double endtime,short int core){
FIN (addnode2());



		node* node1;
		node1 = new node;
		node1->size=size;
		node1->id=id;
		node1->source=src;
		node1->destination=dest;
		node1->k=k;
		node1->lastreroutedk=k;
		node1->tbvt=tranmitterbvt;
		node1->rbvt=receiverbvt;
		node1->start=start;
		node1->finish=finish;
		node1->holdingtime=hltime;
		node1->path_length=path_length;
		node1->next = NULL;
		node1->remaining_time=endtime-op_sim_time();
		node1->end_time=endtime;
		//node1->nd=nx;?????
		node1->core=core;
		node1->available_reroutes[0][0]=-1;
		node1->available_reroutes[1][0]=-1;
		node1->available_reroutes[2][0]=-1;
		node1->available_reroutes[0][1]=-1;
		node1->available_reroutes[1][2]=-1;
		node1->available_reroutes[2][3]=-1;
		node1->newfsstart=-1;
	
		node1->compression=0.0;
		for(int j=0;j<10;j++){
			node1->free_left[j]=0;
			node1->free_right[j]=0;
			node1->pathcompression[j]=0.0;
		}

		node1->label=0;

		for(int i=0;i<path_length;i++)
			node1->path[i]=paths[i];
		
		
		
		if(first == NULL)
			{
			
				first = node1;
				end=node1;
			}
		else
			{
				end->next=node1;
				end=node1;
			}
		
		




FOUT;
}



bool shift(node *p){
FIN (shift());
bool flag=false;
	if( (p->label!=3)){
	
	int pf=pre_free(p);
	//printf("\n id is %d and prefree is: %d ",p->id,pf);
	int min=1000;
	for (int i=0;i<p->path_length;i++){
		//printf("\n free[%d]=%d",i,p->free_left[i]);
		if(p->free_left[i]<min){
			min=p->free_left[i];
		}
	}
	//printf("\n min is:%d",min);
	if(min>0){
	flag=true;
	for(int i=0;i<p->path_length;i++){
		for(int j=p->start;j<=p->finish;j++){
			Slots[0][p->path[i]][j]=0;
			Slots[0][p->path[i]][j-min]=p->id;
		}
		}
	p->start-=min;
	p->finish-=min;}
	//shows();
	}
	return (flag);
	FRET (flag);
}


bool shift2(node *p){
FIN (shift2());
bool flag=false;
	
	
	int pf=pre_free2(p);
	//printf("\n id is %d and prefree is: %d ",p->id,pf);
	int min=1000;
	for (int i=0;i<p->path_length;i++){
		//printf("\n free[%d]=%d",i,p->free_left[i]);
		if(p->free_left[i]<min){
			min=p->free_left[i];
		}
		}
	//printf("\n min is:%d",min);
	if(min>0){
	flag=true;
	for(int i=0;i<p->path_length;i++){
		for(int j=p->start;j<=p->finish;j++){
			Slots[p->core][p->path[i]][j]=0;
			Slots[p->core][p->path[i]][j-min]=p->id;
			times[p->core][p->path[i]][j]=0;
			times[p->core][p->path[i]][j-min]=p->remaining_time;
		}
		}
	p->start-=min;
	p->finish-=min;}
	//shows();
	
	return (flag);
	FRET (flag);
	}



void defrags(int s){
		
FIN (defrags());
shows();
//removelabel();
node *t;
t=first;
while (t){
update_time(t);
t=t->next;
}
zero_untransferable();
	int actioncode=1;
do{
		matrix_counter=0;
		zero_matrix();
		zero_normal_matrix();
		finddying4move2extra2();
	normal4transfer(matrix_counter);
	int bst=(int)best4transfer(matrix_counter);
	if(bst>0){
	//printf("\nbest for move dying is: %d",bst);
			transfer2extra(bst);
	//shows();
	}

	}while(matrix_counter>0);




		zero_untransferable();
// MOVING DYING CONNECTIONS!!!	
	//move_dyings();
	//printf("\n End of moving dyings!");
	//printf("\n\n\n %$$$$$$$$$$$$$$$$$$$$$$$$\n\n");
	//shows();
	//printf("\n shorting!\n");
	bool x=false;
	//SHORTING THE CONNECTIONS!
	do{
	
	x=shortenlengthes();	
	}while (x);
    //SHORTING THE CONNECTIONS!
    //show();
    //printf("\n End of shorting!\n");
    
    removelabel();
    
    
    // this is the main loop!
    
    int llo=0;
	int lastrerouted=0;
    do{
	llo++;
    actioncode=0;
		
		
		
		//printf("\n Moving!");
    
	do{
		
		matrix_counter=0;
		zero_matrix();
		zero_normal_matrix();
		check_and_mark_move();
		normal4move(matrix_counter);
		int bst= (int) best4move(matrix_counter);
		//printf("\n best for move is:%d",bst );
		if(bst>0){
		//printf("\n want to move %d",bst);
		node *ol=get_connection_by_id(bst);
		if(ol!=NULL){
		//printf("\n want to move %d to %d pathlength is:%d",ol->id,ol->newfsstart,ol->path_length);
		move(ol);
		//printf("\n moved %d",bst);
		actioncode=1;	}
		else{
		printf("\n Error inmoving! ==>%d",bst);
		break;
		}
	}
	} while (matrix_counter>0);
	
	//printf("\n End of Moving!");
	//printf("\n Rerouting!");
	
	int looper=0;
	int rrt=0;
	int res1=-1;
	//node *p=NULL;
	do{
		//show();
		matrix_counter=0;
		zero_matrix();
		check_and_mark_reroute();
		zero_normal_matrix();
		normal4reroute(matrix_counter);
		res1=(int) best4reroute(matrix_counter);
		//printf("\n Best Connection for reroute is: %d",res1);
		if((res1!=rrt) && (res1>0)){
		
				pp=get_connection_by_id(res1);
				if(pp!=NULL){
		reroute(pp,pp->available_reroutes[0][0],pp->available_reroutes[0][1]);
		actioncode=2;
		rrt=res1;}
				else{
				printf("\n Error in rerouting1!=>%d",res1);
				break;
				
				}
		}		
		looper++;
	
	} while ((matrix_counter>0)&&(looper<2*s)&&(res1!=rrt));// looper is a guard for exiting the loop!
	lastrerouted=rrt;
	//printf("\n End of Rerouting!");
	

	
	//printf("\n Transfering to Extra!");
	zero_untransferable();
	
	do{
		matrix_counter=0;
		zero_matrix();
		zero_normal_matrix();
		ckeck4transfer();
		normal4transfer(matrix_counter);
		int bst=(int)best4transfer(matrix_counter);
	if(bst>0){
			if(transfer2extra(bst))
		//show();
		actioncode=3;
			else (actioncode=0);
	}
	}while (matrix_counter>0);
	
		
	/*do{
		
		matrix_counter=0;
		zero_matrix();
		zero_normal_matrix();
		check_and_mark_move();
		normal4move(matrix_counter);
		int bst= (int) best4move(matrix_counter);
		printf("\n best for move is:%d",bst );
		if(bst>0){
		printf("\n want to move %d",bst);
		node *ol=get_connection_by_id(bst);
		printf("\n want to move %d to %d pathlength is:%d",ol->id,ol->newfsstart,ol->path_length);
		move(ol);
		printf("\n moved %d",bst);
		actioncode=1;	
		}
		} while (matrix_counter>0);*/
	
	
	
		
		//break;
		//printf("\n****************\n***************\n");
	//printf("now shifting!");
	
	 int lastshifted=0;
	int shft=0;
		do{
			lastshifted=0;
			//node *r;
			pp=first;
			while(pp){
				if(shift(pp)){
				shft++;
				lastshifted=pp->id;
				actioncode=4;
				}
				pp=pp->next;
			}
		}while(lastshifted!=0);
    //printf("\n end of shifting!!!==>$d\n",shft);
//shows();
	
	
	
	
	
	}while((actioncode!=0) && (llo<50));
   
    	//node *g;
	//pp=first;
/*	//printf("\n the Dont Move Connections are:");
	//printf("\n*********************\n");
	while(pp){
		if((pp->label==1))
		printf("\n*        %3d DM!        *",pp->id);
		else if (pp->label==3)
			printf("\n*        %3d Extra!        *",pp->id);
		pp=pp->next;
	}
	printf("\n*********************\nFINISHED!!!\n\n");
	shows();*/
	FOUT;
	}

void defrags2(int s){
		
FIN (defrags2());
//shows();
//removelabel();
node *t;
t=first;
while (t){
update_time(t);
t=t->next;
}

zero_untransferable();






	int actioncode=0;

		actioncode=1;
do{
		matrix_counter=0;
		zero_matrix();
		zero_normal_matrix();
		finddying4move2extra2();
	normal4transfer(matrix_counter);
	int bst=(int)best4transfer(matrix_counter);
	if(bst>0){
	//printf("\nbest for move dying is: %d",bst);
			transfer2extra(bst);
	//shows();
	}

	}while(matrix_counter>0);




		zero_untransferable();
// MOVING DYING CONNECTIONS!!!	
	//move_dyings();
	//printf("\n End of moving dyings!");
	//printf("\n\n\n %$$$$$$$$$$$$$$$$$$$$$$$$\n\n");
	//shows();
	


//printf("\n shorting!\n");
	bool x=false;
	//SHORTING THE CONNECTIONS!
int shrt=0;	
do{
	shrt++;
	x=shortenlengthes();	
	}while (x);
    //SHORTING THE CONNECTIONS!
    //show();
    printf("\n End of shorting!==>%d times\n",shrt);
    









    removelabel();
    
    
    // this is the main loop!
    
    int llo=0;
	int lastrerouted=0;
    do{
	llo++;
    actioncode=0;
		
		
		
		//printf("\n Moving!");
    
	do{
		
		matrix_counter=0;
		zero_matrix();
		zero_normal_matrix();
		check_and_mark_move();
		normal4move(matrix_counter);
		int bst= (int) best4move(matrix_counter);
		//printf("\n best for move is:%d",bst );
		if(bst>0){
		//printf("\n want to move %d",bst);
		
		node *ol=get_connection_by_id(bst);
		if (ol!=NULL){
		move(ol);
		//printf("\n moved %d",bst);
		actioncode=1;}
		else {
		
		printf ("\n Error in moving!!!==>%d",bst);
		}
	}
	} while (matrix_counter>0);
	
	//printf("\n End of Moving!");
	
	
	
	
	int shft=0;
	 int lastshifted=0;
		do{
			lastshifted=0;
			//node *r;
			pp=first;
			while(pp){
				if(shift(pp)){
				shft++;
				lastshifted=pp->id;
				actioncode=4;
				}
				pp=pp->next;
			}
		}while(lastshifted!=0);
	
	
	
	
	//printf("\n Transfering to Extra!");
	zero_untransferable();
	
	do{
		matrix_counter=0;
		zero_matrix();
		zero_normal_matrix();
		ckeck4transfer();
		normal4transfer(matrix_counter);
		int bst=(int)best4transfer(matrix_counter);
	if(bst>0){
	
			if(transfer2extra(bst))
		//show();
		actioncode=3;
			else (actioncode=0);
	}
	}while (matrix_counter>0);
	
	
	
	/*
	int shft=0;
	 int lastshifted=0;
		do{
			lastshifted=0;
			//node *r;
			pp=first;
			while(pp){
				if(shift(pp)){
				shft++;
				lastshifted=pp->id;
				actioncode=4;
				}
				pp=pp->next;
			}
		}while(lastshifted!=0);
	*/
	
	
	/*
	
	//printf("\n Rerouting!");
	
	int looper=0;
	int rrt=0;
	int res1=-1;
	//node *p=NULL;
	do{
		//show();
		matrix_counter=0;
		zero_matrix();
		check_and_mark_reroute();
		zero_normal_matrix();
		normal4reroute(matrix_counter);
		res1=(int) best4reroute(matrix_counter);
		if(res1==2564)
			printf("\nsalam 2564 rerouted!");
		if((res1!=rrt) && (res1>0)){
		//printf("\n Best Connection for reroute is: %d",res1);
				pp=get_connection_by_id(res1);
				if(pp!=NULL){
		reroute(pp,pp->available_reroutes[0][0],pp->available_reroutes[0][1]);
		actioncode=2;
		rrt=res1;}
				else{
				printf("\n Error in rerouting==>%d",res1);
				}
		}		
		looper++;
	
	} while ((matrix_counter>0)&&(looper<2*s)&&(res1!=rrt));// looper is a guard for exiting the loop!
	lastrerouted=rrt;
	//printf("\n End of Rerouting!");
	
	
	*/

	
	
	
		
	
	
	
	
	
	
	
	
	
	
	
		
		//break;
		//printf("\n****************\n***************\n");
	//printf("now shifting!");
	 
	
	shft=0;
	   lastshifted=0;
		do{
			lastshifted=0;
			//node *r;
			pp=first;
			while(pp){
				if(shift(pp)){
				if(pp->id==2564)
			printf("\nsalam 2564 shifted!");
				shft++;
				lastshifted=pp->id;
				actioncode=4;
				}
				pp=pp->next;
			}
		}while(lastshifted!=0);
	
	
	
	

	
	
	
	}while((actioncode!=0) && (llo<50));
   
 
/*

do{
		
		matrix_counter=0;
		zero_matrix();
		zero_normal_matrix();
		checkmovefromextra();
		normal4move(matrix_counter);
		int bst= (int) best4move(matrix_counter);
		//printf("\n best for move is:%d",bst );
		if(bst>0){
		//printf("\n want to move %d",bst);
		
		node *ol=get_connection_by_id(bst);
		if (ol!=NULL){
		movefromextra(ol);
		//printf("\n moved %d",bst);
		actioncode=7;}
		else {
		
		printf ("\n Error in movingfromextra!!!==>%d",bst);
		}
	}
	} while (matrix_counter>0);
	
	
	
	
	
	
	int shft=0;
	   int lastshifted=0;
		do{
			lastshifted=0;
			//node *r;
			pp=first;
			while(pp){
				if(shift(pp)){
				if(pp->id==2564)
			printf("\nsalam 2564 shifted!");
				shft++;
				lastshifted=pp->id;
				actioncode=4;
				}
				pp=pp->next;
			}
		}while(lastshifted!=0);


*/



	FOUT;
	}


void assign(long int id,int src,int dest,double hlt,double endtime,int size,Packet *pkptr1){
FIN (assign());
//FILE *F=fopen("e:/out1/packets.txt","a");
if (id>lastpkno)
	lastpkno=id;
int gap_start=-1;
int gap_end=-1;
bool BVT_OK=false;
int TransmitterBVT=-1;
int ReceiverBVT=-1;
TransmitterBVT=get_BVT(1,src);
if ((TransmitterBVT>=0) && (TransmitterBVT<50)){
ReceiverBVT=get_BVT(0,dest);
if ((ReceiverBVT>=0) && (ReceiverBVT<50)){

BVT_OK=true;
}
}

short int selected_k=-1;
if (BVT_OK){//bvtok

BOK++;
int Len=0;
int a[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};


//fprintf(F,"\n ID:%d, src:%d , Des:%d , needed:%d",id,src,dest,size);
					
short int k=0;
while(k<3){
for(int x=0;x<10;x++)
	a[x]=-1;
zero_temparray(slots_size + extra);
Len=get_all_links_number(a,src,dest,k);// now len is path length and all link numbers are in a
get_situation(a, Len,slots_size);

 gap_start=firstfit(size+1,0,slots_size);// change it to 3 !!!!!!!!!!!!!!!!!!

		if (gap_start>=0)//there is a gap!
			{	
				 gap_end=gap_start + size;// ebteda va entehaye slot ha
				if (gap_end == slots_size)//agar por nashode bashad
					{
					gap_end--;
					}
					selected_k=k;
				break;
					
					}





k++;
}

if ((gap_start>=0) && (gap_end>=0) && selected_k<3)
					{
						//add to ls , applying
					 //fprintf(F," K:%d , Path_lngth:%d ",selected_k,Len);
								
					 for (  int i=0; i< Len ; i++)
						 {
						 	 int lnk=a[i];
										
							for (  int j=gap_start ; j<=gap_end; j++)
								{
									Slots[0][lnk][j]=id;
												
								}
							}
					 
					 Transmitter_BVTs[src][TransmitterBVT]=true;//yani in  estefade shod
					 Receiver_BVTs[dest][ReceiverBVT]=true;
					 
					 addnode(id, selected_k,a, Len, gap_start,gap_end,  size,  src, dest, TransmitterBVT,ReceiverBVT,hlt,endtime);
					
					 
					 pktnom++;
						number_of_ack+=1;
						bw_ack= bw_ack + size;
					// fprintf(F," ==>OK");
						op_intrpt_schedule_self(op_sim_time ()+ hlt,id);
						op_pk_destroy(pkptr1);
					 }
				else
					{
						number_of_nack=number_of_nack+1;
						bw_nack= bw_nack + size;
						//fprintf(F," ==>NOK1");
						op_pk_destroy(pkptr1);
					}







				}

				else{// there is no BVT
			number_of_nack=number_of_nack+1;
			bw_nack= bw_nack + size;
			//fprintf(F," ==>NOK2");
			op_pk_destroy(pkptr1);
			BNOK++;
}


//fclose(F);
FOUT;
}




void assign2(long int id,int src,int dest,double hlt,double endtime,int size,Packet *pkptr1){
FIN (assign2());
//FILE *F=fopen("e:/out1/packets.txt","a");
if (id>lastpkno)
	lastpkno=id;
int gap_start=-1;
int gap_end=-1;
bool BVT_OK=false;
int TransmitterBVT=-1;
int ReceiverBVT=-1;
TransmitterBVT=get_BVT(1,src);
if ((TransmitterBVT>=0) && (TransmitterBVT<50)){
ReceiverBVT=get_BVT(0,dest);
if ((ReceiverBVT>=0) && (ReceiverBVT<50)){

BVT_OK=true;
}
}

short int selected_k=-1;
if (BVT_OK){//bvtok

BOK++;
int Len=0;
int a[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};


//fprintf(F,"\n ID:%d, src:%d , Des:%d , needed:%d",id,src,dest,size);
					
short int k=0;
while(k<3){
for(int x=0;x<10;x++)
	a[x]=-1;
zero_temparray(slots_size + extra);
Len=get_all_links_number(a,src,dest,k);// now len is path length and all link numbers are in a
get_situation(a, Len,slots_size);

 gap_start=firstfit(size+1,0,slots_size);// change it to 3 !!!!!!!!!!!!!!!!!!

		if (gap_start>=0)//there is a gap!
			{	
				 gap_end=gap_start + size;// ebteda va entehaye slot ha
				if (gap_end == slots_size)//agar por nashode bashad
					{
					gap_end--;
					}
					selected_k=k;
				break;
					
					}





k++;
}

if ((gap_start>=0) && (gap_end>=0) && selected_k<3)
					{
						//add to ls , applying
					 //fprintf(F," K:%d , Path_lngth:%d ",selected_k,Len);
								
					 for (  int i=0; i< Len ; i++)
						 {
						 	 int lnk=a[i];
										
							for (  int j=gap_start ; j<=gap_end; j++)
								{
									Slots[0][lnk][j]=id;
												
								}
							}
					 
					 Transmitter_BVTs[src][TransmitterBVT]=true;//yani in  estefade shod
					 Receiver_BVTs[dest][ReceiverBVT]=true;
					 
					 addnode(id, selected_k,a, Len, gap_start,gap_end,  size,  src, dest, TransmitterBVT,ReceiverBVT,hlt,endtime);
					
					 
					 pktnom++;
						number_of_ack+=1;
						bw_ack= bw_ack + size;
					// fprintf(F," ==>OK");
						op_intrpt_schedule_self(op_sim_time ()+ hlt,id);
						op_pk_destroy(pkptr1);
					 }
				else
					{
						number_of_nack=number_of_nack+1;
						bw_nack= bw_nack + size;
						//fprintf(F," ==>NOK1");
						op_pk_destroy(pkptr1);
					}







				}

				else{// there is no BVT
			number_of_nack=number_of_nack+1;
			bw_nack= bw_nack + size;
			//fprintf(F," ==>NOK2");
			op_pk_destroy(pkptr1);
			BNOK++;
}


//fclose(F);
FOUT;
}

void defmove(){
FIN(defmove());
int moved=-1;
do{
		moved=-1;		
		int fs=-1;
		pp=first;
		while(pp){
		fs=-1;
		fs=check4moveable(pp);
		if(fs>=0){
		moved=pp->id;
		pp->newfsstart=fs;
		move(pp);
		}
		pp=pp->next;
		
		
		}
	
}while(moved>0);
FOUT;
}


void defshift(){
FIN(defshift());
int lastshifted=0;
int actioncode=0;
do{
		int shft=0;
		actioncode=0;
		do{
			lastshifted=0;
			//node *r;
			pp=first;
			while(pp){
				if(shift(pp)){
				shft++;
				lastshifted=pp->id;
				actioncode=1;
				}
				pp=pp->next;
			}
		}while(lastshifted!=0);
		printf("\nshift:%d",shft);
		}while(actioncode>0);
printf("\n*****************************\n");
FOUT;
}















void free_arr(){
FIN (free_arr());
for(int i=0;i<100;i++)
	{
	arr[i][0]=-1;
	arr[i][1]=-1;
	arr[i][2]=-1;
	}
FOUT;
}


int getfirstfit(int size,int from,int last){
	FIN(getfirstfit());
	int cc=0;
	int res1=-1;
	int counter=0;
	free_arr();
	bool flag=true;
	for (int i=from;i<=last-size+1;i++){
		flag=true;
		for (int j=0;temparray[i+j]==0 && i+j <last;j++){
		
			if(temparray[i+j]!=0)
			{
				res1=-1;
				flag=false;
				counter=0;
				break;
			}
			else {
				counter++;
			}
		
			}
			if((flag) && (counter>=size)){
				arr[cc][0]=i;
				arr[cc][1]=counter;
				cc++;
			i+=counter-1;
			counter=0;
			}
			else{
				counter=0;
				res1=-1;
			}
			
	}
	return cc;
	FRET (cc);
}

double get_connection_time(int dx){
	FIN(get_connection_time());
	double t=0.0;
	node *p=get_connection_by_id(dx);
	if (p)
		t=p->remaining_time;
	else
		printf("\n not found get connection time!");
	return (t);
	FRET ((t));
}

double leftneighbortime(int links[],int size,int index,int core){// returns average times of left connections on all links
	FIN(leftneighbortime);	
if(arr[index][0]==0)
	return 0.0;
	double t=0.0;
	if(arr[index][0]>0){
	int j=arr[index][0]-1;
	for(int i=0;i<size;i++){
	
	if(Slots[core][links[i]][j]>0)
		
	
		t+=times[core][links[i]][j];
	
	}
	
	}
	else
		printf("\n not found in leftneghbir!");
	return ((double) t/size);
	FRET((double) t/size);
}
double rightneighbortime(int links[],int size,int index,int core){
	FIN(rightneighbortime());	
	/*double t=0.0;
	node *p=get_connection_by_id(temparray[arr[index][0] + arr[index][1]]);
	if (p)
		t=p->remaining_time;
	else printf("\n not found in rightneighbor!");*/
	if((arr[index][0]==slots_size)||(arr[index][0]+arr[index][1]>=slots_size))
		return 0.0;
	double t=0.0;
	if(arr[index][0]>0){
	int j=arr[index][0]+arr[index][1];
	for(int i=0;i<size;i++){
	
	if(Slots[core][links[i]][j]>0)
		
	
		t+=times[core][links[i]][j];
	
	}
	
	}
	return ((double) t/size);
	FRET ((double) t/size);
}






double get_temp_compression(){
FIN (get_temp_compression());
	double res1=0.0;
	 int sum=0;
	 int counter=0;
	for(int i=0;i<slots_size;i++){
		if(temparray[i]==0){
			sum++;
		}else{
			if(sum>0){
				res1+=(double) 1/sum;
				sum=0;
				counter++;
			}
		}
	}
	if(sum>0){
				res1+=(double) 1/sum;
				sum=0;
				counter++;
			}
	if(counter==1) {
	
	return 0;
	FRET (0);
	} 
	return (res1 * counter)/((slots_size/2)*(slots_size/2));
	FRET ((res1 * counter)/((slots_size/2)*(slots_size/2)));
}	

void set_tempp(int index,int size){
FIN (set_tempp());
for(int i=index;i<index + size;i++)
	temparray[i]=1;

FOUT;
}

void unset_tempp(int index,int size){
FIN (unset_tempp());
for(int i=index;i<index + size;i++)
	temparray[i]=0;
FOUT;
}


double get_temp_compression2(){
FIN (get_temp_compression2());
double res1=0.0;
	 int sum=0;
	 int counter=0;
	for(int i=0;i<slots_size;i++){
		if(temparray[i]==0){
			sum++;
		}else{
			if(sum>0){
				res1+=(double) 1/sum;
				sum=0;
				counter++;
			}
		}
	}
	if(sum>0){
				res1+=(double) 1/sum;
				sum=0;
				counter++;
			}
	return (res1 * counter)/((slots_size/2)*(slots_size/2));
	FRET ((res1 * counter)/((slots_size/2)*(slots_size/2)));

}

double get_fragmentation_rate(int index,int neededsize){
FIN (get_fragmentation_rate());
double before=get_temp_compression();
set_tempp(arr[index][0],neededsize);
double after=get_temp_compression();
unset_tempp(arr[index][0],neededsize);
return (before-after);
FRET (before-after);
}


void add2bestfit(int links[],int linksize,int index,int neededsize, double neededtime,int core){
FIN (add2bestfit());
matrix[matrix_counter][0]=(double) arr[index][1];//distance from begining! or free block space!
//matrix[matrix_counter][1]=(double) arr[index][1];//size of free block!
double left,right;
left=leftneighbortime(links,linksize,index,core);
if(left!=0)
	left-= neededtime;
if (left<0)
	left*=-1;
right=rightneighbortime(links,linksize,index,core);
if(right!=0)
	right-= neededtime;
if (right<0)
	right*=-1;
matrix[matrix_counter][1]=left;
matrix[matrix_counter][2]=right;
matrix[matrix_counter][3]=get_fragmentation_rate(index,neededsize);
matrix[matrix_counter][7]=arr[index][0];

matrix_counter++;

FOUT;


}

void normal4bestfit(int size){
FIN (normal4bestfit());
/*if(matrix_counter==0)
	return;
	int minmax[8]={0,0,0,0,0,0,0,0};
	for (int i=0;i<8;i++){// finding max and min for each param!
		if(i==3){//positive
		for(int j=0; j<size; j++){ //finding max!
				if (matrix[j][i]>matrix[minmax[i]][i]){
					minmax[i]=j;
				}
			}
		}
		else{
		 // negative parameters! should find min!
			for(int j=0; j<size; j++){ //finding max!
				if (matrix[j][i]<matrix[minmax[i]][i]){
					minmax[i]=j;
				}
			}
			}
		
		
	}// now max and min for each param is found!
	
	for (int i=0;i<8;i++){
		if (i==3){
		for(int j=0;j<size;j++){
				normal_matrix[j][8]=matrix[j][8];
				if(matrix[minmax[i]][i]>0.0){
			normal_matrix[j][i]=(double) (matrix[j][i]/matrix[minmax[i]][i]);
				if (normal_matrix[j][i]<0)
					normal_matrix[j][i]=0;}
			else  {
			normal_matrix[j][i]=0.0;
			normal_matrix[minmax[i]][i]=1.0;
			}
			
				//?????????? or 1????
				}
		
		}
		else{
			for(int j=0;j<size;j++){
				normal_matrix[j][8]=matrix[j][8];
				if(matrix[j][i]!=0)
			normal_matrix[j][i]=(double) (matrix[minmax[i]][i]/matrix[j][i]);	
			else
			normal_matrix[j][i]=1.0;//?????????? or 1????
			}
			
			
			}
			}
//printf("\n notmal matrix is:\n");
//show_normal_matrix();
*/



if(matrix_counter<=1)
	return;
	int minmax[8]={0,0,0,0,0,0,0,0};
	for (int i=0;i<4;i++){// finding max and min for each param!
		if(i==3){//positive
		for(int j=0; j<size; j++){ //finding max!
		
				if (matrix[j][i]>=matrix[minmax[i]][i]){
					minmax[i]=j;
				}
			}
		}
		else{
		 // negative parameters! should find min!
			for(int j=0; j<size; j++){ //finding max!
				if (matrix[j][i]<=matrix[minmax[i]][i]){
					minmax[i]=j;
				}
			}
			}
		
		
	}// now max and min for each param is found!
	
	for (int i=0;i<4;i++){
		if (i==3){
		for(int j=0;j<size;j++){
				normal_matrix[j][7]=matrix[j][7];
				if(matrix[minmax[i]][i]>0.0){
			normal_matrix[j][i]=(double) (matrix[j][i]/matrix[minmax[i]][i]);
				if (normal_matrix[j][i]<0)
					normal_matrix[j][i]=0;}
			else  {
			normal_matrix[j][i]=0.0;
			normal_matrix[minmax[i]][i]=1.0;
			}
			
				//?????????? or 1????
				}
		
		}
		else{
			for(int j=0;j<size;j++){
				normal_matrix[j][7]=matrix[j][7];
				if(matrix[j][i]!=0)
			normal_matrix[j][i]=(double) (matrix[minmax[i]][i]/matrix[j][i]);	
			else
			normal_matrix[j][i]=1.0;//?????????? or 1????
			}
			
			
			}
			}


FOUT;

}



int findbestplace(int size){
FIN (findbestplace());

	double max=0.0;
	int max_index=-1;
	double tmp=0.0;
	for (int i=0;i<size;i++){
		tmp=0.0;
		for (int j=0;j<4;j++){
			tmp+=(normal_matrix[i][j]*bestfit_weights[j]);
		}
		//cout<<endl<<" value of " << i<<"is : "<< tmp;
		if (tmp>max){
			max=tmp;
			max_index=i;
		}
	}
	//printf("\n\n ========> best 4 move max is:%f",max);
	return (normal_matrix[max_index][7]);
	FRET(normal_matrix[max_index][7]);


	}


void zero_arr(){
FIN(zero_arr());
for(int i=0;i<100;i++){
		arr[i][0]=-1;
		arr[i][1]=-1;
		
		}
FOUT;
}

void update(){
FIN (update());
node *t;
t=first;

while (t){
update_time(t);
t=t->next;
}
FOUT;

}

void update2(){
FIN (update2());
node *t;
t=first;

while (t){
update_time2(t);
t=t->next;
}
FOUT;

}


void bestfitassign(long int id,int src,int dest,double hlt,double endtime,int size,Packet *pkptr1){
FIN (bestfitassign());
//FILE *F=fopen("e:/out1/packets.txt","a");
if (id>lastpkno)
	lastpkno=id;
int gap_start=-1;
int gap_end=-1;
bool BVT_OK=false;
int TransmitterBVT=-1;
int ReceiverBVT=-1;
TransmitterBVT=get_BVT(1,src);
if ((TransmitterBVT>=0) && (TransmitterBVT<50)){
ReceiverBVT=get_BVT(0,dest);
if ((ReceiverBVT>=0) && (ReceiverBVT<50)){

BVT_OK=true;
}
}

short int selected_k=-1;
if (BVT_OK){//bvtok

BOK++;
int Len=0;
int a[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};


//fprintf(F,"\n ID:%d, src:%d , Des:%d , needed:%d",id,src,dest,size);
					
short int k=0;
while(k<3){
for(int x=0;x<10;x++)
	a[x]=-1;
zero_temparray(slots_size + extra);
Len=get_all_links_number(a,src,dest,k);// now len is path length and all link numbers are in a
get_situation(a, Len,slots_size);


zero_arr();
int free_size=getfirstfit( size+1,0,slots_size);
if(free_size>1){
zero_matrix();
zero_normal_matrix();
update();
matrix_counter=0;

for(int z=0;z<free_size;z++){
add2bestfit(a,Len,z,size+1,hlt,0);
}
normal4bestfit(free_size);
gap_start=findbestplace(free_size);
printf("\ngap_start:%d",gap_start);
}
else if (free_size==1){
gap_start=arr[0][0];

}
else{
	k++;
continue;}
 //gap_start=firstfit(size+1,0,slots_size);// change it to 3 !!!!!!!!!!!!!!!!!!

		if (gap_start>=0)//there is a gap!
			{	
				 gap_end=gap_start + size;// ebteda va entehaye slot ha
				if (gap_end == slots_size)//agar por nashode bashad
					{
					gap_end--;
					}
					selected_k=k;
				break;
					
					}





k++;
}

if ((gap_start>=0) && (gap_end>=0) && selected_k<3)
					{
						//add to ls , applying
					 //fprintf(F," K:%d , Path_lngth:%d ",selected_k,Len);
								
					 for (  int i=0; i< Len ; i++)
						 {
						 	 int lnk=a[i];
										
							for (  int j=gap_start ; j<=gap_end; j++)
								{
									Slots[0][lnk][j]=id;
									times[0][lnk][j]=hlt;		
								}
							}
					 
					 Transmitter_BVTs[src][TransmitterBVT]=true;//yani in  estefade shod
					 Receiver_BVTs[dest][ReceiverBVT]=true;
					 
					 addnode(id, selected_k,a, Len, gap_start,gap_end,  size,  src, dest, TransmitterBVT,ReceiverBVT,hlt,endtime);
					
					 
					 pktnom++;
						number_of_ack+=1;
						bw_ack= bw_ack + size;
					// fprintf(F," ==>OK");
						op_intrpt_schedule_self(op_sim_time ()+ hlt,id);
						op_pk_destroy(pkptr1);
					 }
				else
					{
						number_of_nack=number_of_nack+1;
						bw_nack= bw_nack + size;
						//fprintf(F," ==>NOK1");
						op_pk_destroy(pkptr1);
					}







				}

				else{// there is no BVT
			number_of_nack=number_of_nack+1;
			bw_nack= bw_nack + size;
			//fprintf(F," ==>NOK2");
			op_pk_destroy(pkptr1);
			BNOK++;
}


//fclose(F);
FOUT;
}

void zero_temp_path(){
FIN (zero_temp_path());
for(int i=0;i<14;i++){
temp_path[0][i]=-1;
temp_path[1][i]=-1;
temp_path[2][i]=-1;}
FOUT;
}

void get_paths(int src, int dest, int size){
FIN (get_paths());
zero_temp_path();
for(int k=0;k<3;k++){
int a[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

zero_temparray(slots_size + extra);
int Len=get_all_links_number(a,src,dest,k);// now len is path length and all link numbers are in a
get_situation(a, Len,slots_size);

 int gap_start=firstfit(size+1,0,slots_size);// change it to 3 !!!!!!!!!!!!!!!!!!

		if (gap_start>=0){
		for(int x=0;x<Len;x++)
			temp_path[k][x]=a[x];//copy this path to the temp_path!
			temp_path[k][13]=Len;// size of this path!
		}
			

}




FOUT;
}


void get_paths2(int src, int dest, int size,int core){
FIN (get_paths2());
zero_temp_path();
for(int k=0;k<3;k++){
int a[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

zero_temparray(slots_size + extra);
int Len=get_all_links_number(a,src,dest,k);// now len is path length and all link numbers are in a
get_situation2(a, Len,slots_size,core);

 int gap_start=firstfit(size+1,0,slots_size);// change it to 3 !!!!!!!!!!!!!!!!!!

		if (gap_start>=0){
		for(int x=0;x<Len;x++)
			temp_path[k][x]=a[x];//copy this path to the temp_path!
			temp_path[k][13]=Len;// size of this path!
		}
			

}




FOUT;
}



void get_paths_modul(int src, int dest, int size,int core){
FIN (get_paths_modul());
zero_temp_path();
for(int k=0;k<3;k++){
int a[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

zero_temparray(slots_size + extra);
int Len=get_all_links_number(a,src,dest,k);// now len is path length and all link numbers are in a
get_situation2(a, Len,slots_size,core);
int ptlen=get_path_length2(src,dest,k);
double mod=0;
if (ptlen<1200)
	mod=4;
else if(ptlen<1800)
	mod=3;
else if (ptlen<2400)
	mod=2;
else
	mod=1;


double s;
s=size;
s=ceil(s/mod);
int ss;
ss=s;
//if((src==0) &&(dest==1))
	//printf("\n pathlen:%d , size:%d and moduled: %f , ss=>%d",ptlen,size,s,ss);


 int gap_start=firstfit(s+1,0,slots_size);// change it to 3 !!!!!!!!!!!!!!!!!!

		if (gap_start>=0){
		for(int x=0;x<Len;x++)
			temp_path[k][x]=a[x];//copy this path to the temp_path!
			temp_path[k][13]=Len;// size of this path!
		}
			

}




FOUT;
}


double get_path_compression(int links[],int pathsize,int fssize){
FIN (get_path_compression());
zero_temparray(fssize+extra);
get_situation(links,pathsize,fssize);
return (get_temp_compression());
FRET (get_temp_compression());
}


double get_path_compression2(int links[],int pathsize,int fssize,int core){
FIN (get_path_compression2());
zero_temparray(fssize+extra);
get_situation2(links,pathsize,fssize,core);
return (get_temp_compression());
FRET (get_temp_compression());
}
//void add2path(int pat[][],double pathcomps[],


double get_path_times(int links[],int linksize){// returns average time of the connections!
FIN (get_path_times());
update();//may be sangin!!!
double t=0.0;
int c=0;
for (int i=0;i<linksize;i++){
for(int j=0;j<slots_size;j++){
	if((Slots[0][links[i]][j]>0) && (Slots[0][links[i]][j]!=Slots[0][links[i]][j+1])){
			 t+=times[0][links[i]][j];
			 c++;
			 
			 }
	
	}
}
double res=0.0;
if(c>0)
	res=( double) t/c;
else
	res=0;
return (res);
FRET (res);


}


double get_path_times2(int links[],int linksize,int core){// returns average time of the connections!
FIN (get_path_times2());
update2();//may be sangin!!!
double t=0.0;
int c=0;
for (int i=0;i<linksize;i++){
for(int j=0;j<slots_size;j++){
	if((Slots[core][links[i]][j]>0) && (Slots[core][links[i]][j]!=Slots[core][links[i]][j+1])){
			 t+=times[core][links[i]][j];
			 c++;
			 
			 }
	
	}
}
double res=0.0;
if(c>0)
	res=( double) t/c;
else
	res=0;
return (res);
FRET (res);


}



int get_path_cons(int links[],int linksize){// returns average time of the connections!
FIN (get_path_cons());
int c=0;
for (int i=0;i<linksize;i++){
for(int j=0;j<slots_size;j++){
	if((Slots[0][links[i]][j]>0) && (Slots[0][links[i]][j]!=Slots[0][links[i]][j+1])){
			
			 c++;
			 
			 }
	
	}
}
return (c);
FRET (c);


}

int get_path_cons2(int links[],int linksize,int core){// returns average time of the connections!
FIN (get_path_cons2());
int c=0;
for (int i=0;i<linksize;i++){
for(int j=0;j<slots_size;j++){
	if((Slots[core][links[i]][j]>0) && (Slots[core][links[i]][j]!=Slots[core][links[i]][j+1])){
			
			 c++;
			 
			 }
	
	}
}
return (c);
FRET (c);


}


int get_free_gaps(int links[],int linksize,int fssize,int needed){// returns number of suitable places for needed FS
FIN (get_free_gaps());
zero_temparray(fssize+extra);
get_situation(links,linksize,fssize);
int r=getfirstfit(needed,0,fssize);
return (r);
FRET (r);
}

int get_free_gaps2(int links[],int linksize,int fssize,int needed,int core){// returns number of suitable places for needed FS
FIN (get_free_gaps2());
zero_temparray(fssize+extra);
get_situation2(links,linksize,fssize,core);
int r=getfirstfit(needed,0,fssize);
return (r);
FRET (r);
}

void add2path(int k,int pathlength,int linksize, int freegaps,double avg_times,double fr_rate,int con_num){
FIN (add2path());
matrix[matrix_counter][0]=(double) pathlength;
matrix[matrix_counter][1]=(double) linksize;
matrix[matrix_counter][2]=(double) freegaps;
matrix[matrix_counter][3]=avg_times;
matrix[matrix_counter][4]=fr_rate;
matrix[matrix_counter][5]=(double) con_num;
matrix[matrix_counter][7]=(double) k; 
matrix_counter++;
FOUT;
}

void normalpath(int size){
FIN (normalpath());
if(matrix_counter==0)
	return;
/*printf("\n********************* matrix************\n");
for(int e=0;e<size;e++)
	{
	for(int r=0;r<8;r++){
	printf("|%f",matrix[e][r]);
	}
	printf("\n");
	}
*/

	int minmax[8]={0,0,0,0,0,0,0,0};
	for (int i=0;i<6;i++){// finding max and min for each param!
		if((i==2)){//positive
		for(int j=0; j<size; j++){ //finding max!
				if (matrix[j][i]>=matrix[minmax[i]][i]){
					minmax[i]=j;
				}
			}
		}
		else{
		 // negative parameters! should find min!
			for(int j=0; j<size; j++){ //finding max!
				if (matrix[j][i]<=matrix[minmax[i]][i]){
					minmax[i]=j;
				}
			}
			}
		
		
		}// now max and min for each param is found!
	
	for (int i=0;i<6;i++){
		if ((i==2)){
		for(int j=0;j<size;j++){
				normal_matrix[j][7]=matrix[j][7];
				if(matrix[minmax[i]][i]>0.0){
			normal_matrix[j][i]=(double) (matrix[j][i]/matrix[minmax[i]][i]);
				if (normal_matrix[j][i]<0)
					normal_matrix[j][i]=0;}
			else  {
			normal_matrix[j][i]=1.0;
			normal_matrix[minmax[i]][i]=1.0;
			}
			
				//?????????? or 1????
				}
		
		}
		else{
			for(int j=0;j<size;j++){
				//normal_matrix[j][8]=matrix[j][8];
				if(matrix[j][i]!=0)
			normal_matrix[j][i]=(double) (matrix[minmax[i]][i]/matrix[j][i]);	
			else
			normal_matrix[j][i]=1.0;//?????????? or 1????
			}
			
			
			}
			}
/*printf("\n********************* normal matrix************\n");
for(int e=0;e<size;e++)
	{
	for(int r=0;r<8;r++){
	printf("|%f",normal_matrix[e][r]);
	}
	printf("\n");
	}
*/

FOUT;

}
int findbestpath(int size){
FIN (findbestpath());


	double max=0.0;
	int max_index=-1;
	double tmp=0.0;
	for (int i=0;i<size;i++){
		tmp=0.0;
		for (int j=0;j<6;j++){
			tmp+=(normal_matrix[i][j]*path_weights[j]);
		}
		//cout<<endl<<" value of " << i<<"is : "<< tmp;
		if (tmp>max){
			max=tmp;
			max_index=i;
		}
	}
	//printf("\n\n ========> best 4 move max is:%f",max);
	return (normal_matrix[max_index][7]);
	FRET(normal_matrix[max_index][7]);
	}

void checkpath(int src,int dest,int needed){
FIN (checkpath());
zero_matrix();
zero_normal_matrix();
matrix_counter=0;
//printf("getting path");
get_paths(src,dest,needed);
//printf("finish getting path");
for(int k=0;k<3;k++){
if(temp_path[k][13]>0){
int frees= get_free_gaps(temp_path[k],temp_path[k][13],slots_size, needed);
//printf("freees=%d",frees);
double fr= get_path_compression(temp_path[k],temp_path[k][13],slots_size);
//printf("fr=%f",fr);
double tim= get_path_times(temp_path[k],temp_path[k][13]);
//printf("time=%f",tim);
int cons=get_path_cons(temp_path[k],temp_path[k][13]);
//printf("cons=%d",cons);
int pl=get_path_length2(src,dest,k);
//printf("pl=%d",pl);
add2path(k,pl,temp_path[k][13], frees,tim,fr,cons);



}


}


	FOUT;

}



void checkpath2(int src,int dest,int needed,int core){
FIN (checkpath2());
zero_matrix();
zero_normal_matrix();
matrix_counter=0;
//printf("getting path");
get_paths2(src,dest,needed,core);
//printf("finish getting path");
for(int k=0;k<3;k++){
if(temp_path[k][13]>0){
int frees= get_free_gaps2(temp_path[k],temp_path[k][13],slots_size, needed,core);
//printf("freees=%d",frees);
double fr= get_path_compression2(temp_path[k],temp_path[k][13],slots_size,core);
//printf("fr=%f",fr);
double tim= get_path_times2(temp_path[k],temp_path[k][13],core);
//printf("time=%f",tim);
int cons=get_path_cons2(temp_path[k],temp_path[k][13],core);
//printf("cons=%d",cons);
int pl=get_path_length2(src,dest,k);
//printf("pl=%d",pl);
add2path(k,pl,temp_path[k][13], frees,tim,fr,cons);



}


}


	FOUT;

}

void checkpathmodul(int src,int dest,int needed,int core){
FIN (checkpathmodul());
zero_matrix();
zero_normal_matrix();
matrix_counter=0;
//printf("getting path");
get_paths_modul(src,dest,needed,core);

//printf("finish getting path");
for(int k=0;k<3;k++){
int pl=get_path_length2(src,dest,k);

if(temp_path[k][13]>0){
double s;
s=needed;
if(pl<1200)
	s=ceil(s/4);
else if (pl<1800)
	s=ceil(s/3);
else if(pl<2400)
s=ceil(s/2);



int frees= get_free_gaps2(temp_path[k],temp_path[k][13],slots_size, s,core);
//printf("freees=%d",frees);
double fr= get_path_compression2(temp_path[k],temp_path[k][13],slots_size,core);
//printf("fr=%f",fr);
double tim= get_path_times2(temp_path[k],temp_path[k][13],core);
//printf("time=%f",tim);
int cons=get_path_cons2(temp_path[k],temp_path[k][13],core);
//printf("cons=%d",cons);

//printf("pl=%d",pl);
add2path(k,pl,temp_path[k][13], frees,tim,fr,cons);



}


}


	FOUT;

}



void bestpathassign(long int id,int src,int dest,double hlt,double endtime,int size,Packet *pkptr1){
FIN (bestpathassign());
//FILE *F=fopen("e:/out1/packets.txt","a");
if (id>lastpkno)
	lastpkno=id;
int gap_start=-1;
int gap_end=-1;
bool BVT_OK=false;
int TransmitterBVT=-1;
int ReceiverBVT=-1;
TransmitterBVT=get_BVT(1,src);
if ((TransmitterBVT>=0) && (TransmitterBVT<50)){
ReceiverBVT=get_BVT(0,dest);
if ((ReceiverBVT>=0) && (ReceiverBVT<50)){

BVT_OK=true;
}
}

short int selected_k=-1;
if (BVT_OK){//bvtok

BOK++;
//printf("start to check");
checkpath( src, dest, size);
//printf("finish to check");
normalpath(matrix_counter);
//printf("finish normal");
selected_k=findbestpath(matrix_counter);
//printf("\nbest k is %d", selected_k);
int a[10];
int Len=0;
if((selected_k>=0) && (selected_k<3)){


for(int x=0;x<10;x++)
	a[x]=-1;
zero_temparray(slots_size + extra);
Len=get_all_links_number(a,src,dest,selected_k);// now len is path length and all link numbers are in a
get_situation(a, Len,slots_size);

 gap_start=firstfit(size+1,0,slots_size);// change it to 3 !!!!!!!!!!!!!!!!!!

		if (gap_start>=0)//there is a gap!
			{	
				 gap_end=gap_start + size;// ebteda va entehaye slot ha
				if (gap_end == slots_size)//agar por nashode bashad
					{
					gap_end--;
					}
				
					
					}


}


if ((gap_start>=0) && (gap_end>=0) && (selected_k<3) && (selected_k>=0))
					{
						//add to ls , applying
					 //fprintf(F," K:%d , Path_lngth:%d ",selected_k,Len);
								
					 for (  int i=0; i< Len ; i++)
						 {
						 	 int lnk=a[i];
										
							for (  int j=gap_start ; j<=gap_end; j++)
								{
									Slots[0][lnk][j]=id;
									times[0][lnk][j]=hlt;
												
								}
							}
					 
					 Transmitter_BVTs[src][TransmitterBVT]=true;//yani in  estefade shod
					 Receiver_BVTs[dest][ReceiverBVT]=true;
					 
					 addnode(id, selected_k,a, Len, gap_start,gap_end,  size,  src, dest, TransmitterBVT,ReceiverBVT,hlt,endtime);
					
					 
					 pktnom++;
						number_of_ack+=1;
						bw_ack= bw_ack + size;
					// fprintf(F," ==>OK");
						op_intrpt_schedule_self(op_sim_time ()+ hlt,id);
						op_pk_destroy(pkptr1);
					 }
				else
					{
						number_of_nack=number_of_nack+1;
						bw_nack= bw_nack + size;
						//fprintf(F," ==>NOK1");
						op_pk_destroy(pkptr1);
					}







				}

				else{// there is no BVT
			number_of_nack=number_of_nack+1;
			bw_nack= bw_nack + size;
			//fprintf(F," ==>NOK2");
			op_pk_destroy(pkptr1);
			BNOK++;
}


//fclose(F);
FOUT;
}




bool newassign(long int id,int src,int dest,double hlt,double endtime,int size,Packet *pkptr1,int core){
FIN (newassign());
//FILE *F=fopen("e:/out1/packets.txt","a");
if (id>lastpkno)
	lastpkno=id;
int gap_start=-1;
bool ress=false;
int gap_end=-1;
bool BVT_OK=true;
int TransmitterBVT=-1;
int ReceiverBVT=-1;
/*TransmitterBVT=get_BVT(1,src);
if ((TransmitterBVT>=0) && (TransmitterBVT<50)){
ReceiverBVT=get_BVT(0,dest);
if ((ReceiverBVT>=0) && (ReceiverBVT<50)){

BVT_OK=true;
}
}*/

short int selected_k=-1;
if (BVT_OK){//bvtok

BOK++;
//printf("start to check");
checkpath2( src, dest, size,core);
//printf("finish to check");
normalpath(matrix_counter);
//printf("finish normal");
selected_k=findbestpath(matrix_counter);
//printf("\nbest k is %d", selected_k);
int a[10];
int Len=0;
if((selected_k>=0) && (selected_k<3)){


for(int x=0;x<10;x++)
	a[x]=-1;
zero_temparray(slots_size + extra);
Len=get_all_links_number(a,src,dest,selected_k);// now len is path length and all link numbers are in a
get_situation2(a, Len,slots_size,core);

 gap_start=firstfit(size+1,0,slots_size);// change it to 3 !!!!!!!!!!!!!!!!!!

		if (gap_start>=0)//there is a gap!
			{	
				 gap_end=gap_start + size;// ebteda va entehaye slot ha
				if (gap_end == slots_size)//agar por nashode bashad
					{
					gap_end--;
					}
				
					
					}


}


if ((gap_start>=0) && (gap_end>=0) && (selected_k<3) && (selected_k>=0))
					{
						//add to ls , applying
					 //fprintf(F," K:%d , Path_lngth:%d ",selected_k,Len);
								
					 for (  int i=0; i< Len ; i++)
						 {
						 	 int lnk=a[i];
										
							for (  int j=gap_start ; j<=gap_end; j++)
								{
									Slots[core][lnk][j]=id;
									times[core][lnk][j]=hlt;
												
								}
							}
					 
					 Transmitter_BVTs[src][TransmitterBVT]=true;//yani in  estefade shod
					 Receiver_BVTs[dest][ReceiverBVT]=true;
					 
					 addnode2(id, selected_k,a, Len, gap_start,gap_end,  size,  src, dest, TransmitterBVT,ReceiverBVT,hlt,endtime,core);
					
					 ress=true;
					 pktnom++;
						number_of_ack+=1;
						bw_ack= bw_ack + size;
					// fprintf(F," ==>OK");
						op_intrpt_schedule_self(op_sim_time ()+ hlt,id);
						op_pk_destroy(pkptr1);
					 }
				else
					{
						//number_of_nack=number_of_nack+1;
						//bw_nack= bw_nack + size;
						ress=false;
						//fprintf(F," ==>NOK1");
						//op_pk_destroy(pkptr1);
					}







				}

				else{// there is no BVT
			//number_of_nack=number_of_nack+1;
			//bw_nack= bw_nack + size;
			ress=false;
			//fprintf(F," ==>NOK2");
			//op_pk_destroy(pkptr1);
			BNOK++;
}


return (ress);
FRET(ress);
}









bool bestassign(long int id,int src,int dest,double hlt,double endtime,int size,Packet *pkptr1,int core){
FIN (bestassign());
//FILE *F=fopen("e:/out1/packets.txt","a");
if (id>lastpkno)
	lastpkno=id;
int gap_start=-1;
bool ress=false;
int gap_end=-1;
bool BVT_OK=true;
int TransmitterBVT=-1;
int ReceiverBVT=-1;
/*TransmitterBVT=get_BVT(1,src);
if ((TransmitterBVT>=0) && (TransmitterBVT<50)){
ReceiverBVT=get_BVT(0,dest);
if ((ReceiverBVT>=0) && (ReceiverBVT<50)){

BVT_OK=true;
}
}*/

short int selected_k=-1;
if (BVT_OK){//bvtok

BOK++;
//printf("start to check");
checkpath2( src, dest, size,core);
//printf("finish to check");
normalpath(matrix_counter);
//printf("finish normal");
selected_k=findbestpath(matrix_counter);
//printf("\nbest k is %d", selected_k);
int a[10];
int Len=0;
if((selected_k>=0) && (selected_k<3)){





for(int x=0;x<10;x++)
	a[x]=-1;
zero_temparray(slots_size + extra);
Len=get_all_links_number(a,src,dest,selected_k);// now len is path length and all link numbers are in a
get_situation2(a, Len,slots_size,core);




zero_arr();
int free_size=getfirstfit( size+1,0,slots_size);
if(free_size>1){
zero_matrix();
zero_normal_matrix();
update2();
matrix_counter=0;

for(int z=0;z<free_size;z++){
add2bestfit(a,Len,z,size+1,hlt,core);
}
normal4bestfit(free_size);
gap_start=findbestplace(free_size);
//printf("\ngap_start:%d",gap_start);
}
else if (free_size==1){
gap_start=arr[0][0];

}
else{
gap_start=-1;
	ress=false;}


if (gap_start>=0)//there is a gap!
			{	
				 gap_end=gap_start + size;// ebteda va entehaye slot ha
				if (gap_end == slots_size)//agar por nashode bashad
					{
					gap_end--;
					}
				
					
				 }


}
		
		
		


if ((gap_start>=0) && (gap_end>=0) && (selected_k<3) && (selected_k>=0))
					{
						//add to ls , applying
					 //fprintf(F," K:%d , Path_lngth:%d ",selected_k,Len);
								
					 for (  int i=0; i< Len ; i++)
						 {
						 	 int lnk=a[i];
										
							for (  int j=gap_start ; j<=gap_end; j++)
								{
									Slots[core][lnk][j]=id;
									times[core][lnk][j]=hlt;
												
								}
							}
					 
					 Transmitter_BVTs[src][TransmitterBVT]=true;//yani in  estefade shod
					 Receiver_BVTs[dest][ReceiverBVT]=true;
					 
					 addnode2(id, selected_k,a, Len, gap_start,gap_end,  size,  src, dest, TransmitterBVT,ReceiverBVT,hlt,endtime,core);
					
					 ress=true;
					 pktnom++;
						number_of_ack+=1;
						bw_ack= bw_ack + size;
					// fprintf(F," ==>OK");
						op_intrpt_schedule_self(op_sim_time ()+ hlt,id);
						op_pk_destroy(pkptr1);
					 }
				else
					{
						//number_of_nack=number_of_nack+1;
						//bw_nack= bw_nack + size;
						ress=false;
						//fprintf(F," ==>NOK1");
						//op_pk_destroy(pkptr1);
					}







				}

				else{// there is no BVT
			//number_of_nack=number_of_nack+1;
			//bw_nack= bw_nack + size;
			ress=false;
			//fprintf(F," ==>NOK2");
			//op_pk_destroy(pkptr1);
			BNOK++;
}


return (ress);
FRET(ress);
}



bool bestassignmodul(long int id,int src,int dest,double hlt,double endtime,int size,Packet *pkptr1,int core){
FIN (bestassignmodul());
//FILE *F=fopen("e:/out1/packets.txt","a");
if (id>lastpkno)
	lastpkno=id;
int gap_start=-1;
bool ress=false;
int gap_end=-1;
bool BVT_OK=true;
int TransmitterBVT=-1;
int ReceiverBVT=-1;
/*TransmitterBVT=get_BVT(1,src);
if ((TransmitterBVT>=0) && (TransmitterBVT<50)){
ReceiverBVT=get_BVT(0,dest);
if ((ReceiverBVT>=0) && (ReceiverBVT<50)){

BVT_OK=true;
}
}*/

short int selected_k=-1;
if (BVT_OK){//bvtok

BOK++;
//printf("start to check");
checkpathmodul( src, dest, size,core);
//printf("finish to check");
normalpath(matrix_counter);
//printf("finish normal");
selected_k=findbestpath(matrix_counter);
//printf("\nbest k is %d", selected_k);
int a[10];
int Len=0;
double s;
s=size;
if((selected_k>=0) && (selected_k<3)){
int patlen=get_path_length2(src,dest,selected_k);

if(patlen<1200)
	s=ceil(s/4);
else if (patlen<1800)
	s=ceil(s/3);
else if (patlen<2400)
	s=ceil(s/2);





for(int x=0;x<10;x++)
	a[x]=-1;
zero_temparray(slots_size + extra);
Len=get_all_links_number(a,src,dest,selected_k);// now len is path length and all link numbers are in a
get_situation2(a, Len,slots_size,core);


if((src==0) &&(dest==1))
printf("\n patlen:%d ==> size:%d s:%f",patlen,size,s);
zero_arr();
int free_size=getfirstfit( s+1,0,slots_size);
if(free_size>1){
zero_matrix();
zero_normal_matrix();
update2();
matrix_counter=0;

for(int z=0;z<free_size;z++){
add2bestfit(a,Len,z,s+1,hlt,core);
}
normal4bestfit(free_size);
gap_start=findbestplace(free_size);
//printf("\ngap_start:%d",gap_start);
}
else if (free_size==1){
gap_start=arr[0][0];

}
else{
gap_start=-1;
	ress=false;}


if (gap_start>=0)//there is a gap!
			{	
				 gap_end=gap_start + s;// ebteda va entehaye slot ha
				if (gap_end == slots_size)//agar por nashode bashad
					{
					gap_end--;
					}
				
					
				 }


}
		
		
		


if ((gap_start>=0) && (gap_end>=0) && (selected_k<3) && (selected_k>=0))
					{
						//add to ls , applying
					 //fprintf(F," K:%d , Path_lngth:%d ",selected_k,Len);
								
					 for (  int i=0; i< Len ; i++)
						 {
						 	 int lnk=a[i];
										
							for (  int j=gap_start ; j<=gap_end; j++)
								{
									Slots[core][lnk][j]=id;
									times[core][lnk][j]=hlt;
												
								}
							}
					 
					 Transmitter_BVTs[src][TransmitterBVT]=true;//yani in  estefade shod
					 Receiver_BVTs[dest][ReceiverBVT]=true;
					 
					 addnode2(id, selected_k,a, Len, gap_start,gap_end,  s,  src, dest, TransmitterBVT,ReceiverBVT,hlt,endtime,core);
					
					 ress=true;
					 pktnom++;
						number_of_ack+=1;
						bw_ack= bw_ack + size;
					// fprintf(F," ==>OK");
						op_intrpt_schedule_self(op_sim_time ()+ hlt,id);
						op_pk_destroy(pkptr1);
					 }
				else
					{
						//number_of_nack=number_of_nack+1;
						//bw_nack= bw_nack + size;
						ress=false;
						//fprintf(F," ==>NOK1");
						//op_pk_destroy(pkptr1);
					}







				}

				else{// there is no BVT
			//number_of_nack=number_of_nack+1;
			//bw_nack= bw_nack + size;
			ress=false;
			//fprintf(F," ==>NOK2");
			//op_pk_destroy(pkptr1);
			BNOK++;
}


return (ress);
FRET(ress);
}









bool change (node *p,short int core){
FIN (change());


bool ch=false;
short int selected_k=-1;

checkpath2( p->source, p->destination, p->size,core);

normalpath(matrix_counter);
//printf("finish normal");
selected_k=findbestpath(matrix_counter);
//printf("\nbest k is %d", selected_k);
int a[10];
int Len=0;
int gap_start=-1;
int gap_end=-1;
if((selected_k>=0) && (selected_k<3)){


for(int x=0;x<10;x++)
	a[x]=-1;
zero_temparray(slots_size + extra);
Len=get_all_links_number(a,p->source,p->destination,selected_k);// now len is path length and all link numbers are in a
get_situation2(a, Len,slots_size,core);






zero_arr();
int free_size=getfirstfit( p->size+1,0,slots_size);
if(free_size>1){
zero_matrix();
zero_normal_matrix();
update();
matrix_counter=0;

for(int z=0;z<free_size;z++){
add2bestfit(a,Len,z,p->size+1,p->remaining_time,core);
}
normal4bestfit(free_size);
gap_start=findbestplace(free_size);
//printf("\ngap_start:%d",gap_start);
}
else if (free_size==1){
gap_start=arr[0][0];

}
else{
gap_start=-1;
	ch=false;}


if (gap_start>=0)//there is a gap!
			{	
				 gap_end=gap_start + p->size;// ebteda va entehaye slot ha
				if (gap_end == slots_size)//agar por nashode bashad
					{
					gap_end--;
					}
				
					
				 }


}
		
		
		



if ((gap_start>=0) && (gap_end>=0) && (selected_k<3) && (selected_k>=0))
					{
						//add to ls , applying
					 //fprintf(F," K:%d , Path_lngth:%d ",selected_k,Len);
						
					for(int i=0;i<p->path_length;i++){
					
					for(int j=p->start;j<=p->finish;j++){
					Slots[p->core][p->path[i]][j]=0;	
					times[p->core][p->path[i]][j]=0;
					
					}
					p->path[i]=-1;
					
					
					}
					
					
					
					 for (  int i=0; i< Len ; i++)
						 {
						 	 int lnk=a[i];
									p->path[i]=lnk;	
							for (  int j=gap_start ; j<=gap_end; j++)
								{
									//Slots[p->core][lnk][j]=0;	
									Slots[core][lnk][j]=p->id;
									//times[p->core][lnk][j]=0;
									times[core][lnk][j]=p->remaining_time;
												
								}
							}
					 ch=true;
					 p->core=core;
					 p->path_length=Len;
					 p->k=selected_k;
					 p->start=gap_start;
					 p->finish=gap_end;
					 }
				
return (ch);
FRET(ch);
}




void changecore(){
FIN (changecore());
update2();
bool cnt=false;
node* p=first;
short int cc=-1;
int chng=0;
while (p){
if((p->remaining_time<2)&&(p->core!=0))
cc=0;

else if ((p->remaining_time<4)&&(p->core!=1))
	cc=1;
else if ((p->remaining_time<6)&&(p->core!=2))
	cc=2;
else if ((p->remaining_time<8)&&(p->core!=3))
	cc=3;
else if ((p->remaining_time<10)&&(p->core!=4))
	cc=4;
else if ((p->remaining_time<20)&&(p->core!=5))
	cc=5;
else 
	cc=6;

if((cc>=0)&&(cc!=p->core)){
cnt=change(p,cc);
if(cnt)
chng++;
else if((!cnt)&&(cc>0)){
cnt=change(p,cc-1);
if(cnt)
chng++;
}
}
cnt=false;
p=p->next;
}
printf("\n change finished! time is :%f and changes are:%d",op_sim_time(),chng);
FOUT;

}

int changecore2(int core){
FIN (changecore2());
update2();
int cc=0;
for(int i=0;i<42;i++){
for(int j=0;j<slots_size;j++){
	//if((Times[core][i][j]>0) &&(Times[core][i][j]>=timeclass[0][0])&&(Times[core][i][j]<timeclass[0][1]))
if(Slots[core][i][j]>0){

node *p=get_connection_by_id(Slots[core][i][j]);
							 if(p->core==core){
							 if((p->remaining_time<timeclass[core][0])){
							 if(change(p,core-1))
								 cc++;
							 }
							 }
							 else j+=p->size;
							 }
}


}
return (cc);
FRET(cc);
}




int changecore3(int core){
FIN (changecore3());
update2();
int cc=0;
for(int i=0;i<42;i++){
for(int j=0;j<slots_size;j++){
	//if((Times[core][i][j]>0) &&(Times[core][i][j]>=timeclass[0][0])&&(Times[core][i][j]<timeclass[0][1]))
if(Slots[core][i][j]>0){

node *p=get_connection_by_id(Slots[core][i][j]);
							 if(p->core==core){
							 if((p->remaining_time<1)){
							 bool flag=false;
							 short int gaurd=0;
							 short int ccd=0;
							 
							 while ((gaurd<2)&&(!flag)){
							 gaurd++;
							 if(gaurd==1)
								 ccd=6;
							 flag=change(p,ccd);
							 ccd=0;
							 if(ccd<0)
								 break;
							 }
							 if(flag)
								 cc++;
							 }
							 }
							 else j+=p->size;
							 }
}


}
return (cc);
FRET(cc);
}







int compare(double x,int a,int b){
FIN(compare());
double s,ss;
int res=0;
s=x-a;
ss=x-b;
if(s<0)
	s*=-1;
if(ss<0)
	ss*=-1;
if(s<ss)
	res=a;
else res=b;
return (res);
FRET(res);
}



bool assigncore(long int id,int src,int dest,double hlt,double endtime,int size,Packet *pkptr1,int core){
FIN (assigncore());
bool ress=false;

if (id>lastpkno)
	lastpkno=id;
int gap_start=-1;
int gap_end=-1;
bool BVT_OK=true;
int TransmitterBVT=0;
int ReceiverBVT=0;


short int selected_k=-1;
if (BVT_OK){//bvtok

BOK++;
int Len=0;
int a[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};


//fprintf(F,"\n ID:%d, src:%d , Des:%d , needed:%d",id,src,dest,size);
					
short int k=0;
while(k<3){
for(int x=0;x<10;x++)
	a[x]=-1;
zero_temparray(slots_size + extra);
Len=get_all_links_number(a,src,dest,k);// now len is path length and all link numbers are in a
get_situation2(a, Len,slots_size,core);





 gap_start=firstfit(size+1,0,slots_size);// change it to 3 !!!!!!!!!!!!!!!!!!

		if (gap_start>=0)//there is a gap!
			{	
				 gap_end=gap_start + size;// ebteda va entehaye slot ha
				if (gap_end == slots_size)//agar por nashode bashad
					{
					gap_end--;
					}
					selected_k=k;
				break;
					
					}





k++;
}

if ((gap_start>=0) && (gap_end>=0) && (selected_k<3))
					{
						//add to ls , applying
					 //fprintf(F," K:%d , Path_lngth:%d ",selected_k,Len);
								
					 for (  int i=0; i< Len ; i++)
						 {
						 	 int lnk=a[i];
										
							for (  int j=gap_start ; j<=gap_end; j++)
								{
									Slots[core][lnk][j]=id;
												
								}
							}
					 
					 Transmitter_BVTs[src][TransmitterBVT]=true;//yani in  estefade shod
					 Receiver_BVTs[dest][ReceiverBVT]=true;
					 
					 addnode2(id, selected_k,a, Len, gap_start,gap_end,  size,  src, dest, TransmitterBVT,ReceiverBVT,hlt,endtime,core);
					ress=true;
					 
					 pktnom++;
						number_of_ack+=1;
						bw_ack= bw_ack + size;
					// fprintf(F," ==>OK");
						op_intrpt_schedule_self(op_sim_time ()+ hlt,id);
						op_pk_destroy(pkptr1);
					 }
				else
					{
						
						ress=false;
					}







				}

				else{
			ress=false;
}


//fclose(F);
return (ress);
FRET (ress);
}



bool assigncoremodul(long int id,int src,int dest,double hlt,double endtime,int size,Packet *pkptr1,int core){
FIN (assigncoremodul());
bool ress=false;

if (id>lastpkno)
	lastpkno=id;
int gap_start=-1;
int gap_end=-1;
bool BVT_OK=true;
int TransmitterBVT=0;
int ReceiverBVT=0;


short int selected_k=-1;
if (BVT_OK){//bvtok

BOK++;
int Len=0;
int a[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};


//fprintf(F,"\n ID:%d, src:%d , Des:%d , needed:%d",id,src,dest,size);
					
short int k=0;
double s=0;

while(k<3){
for(int x=0;x<10;x++)
	a[x]=-1;
zero_temparray(slots_size + extra);
Len=get_all_links_number(a,src,dest,k);// now len is path length and all link numbers are in a
get_situation2(a, Len,slots_size,core);



int patlen=get_path_length2(src,dest,k);
s=(double) size;
if(patlen<1200)
	s=ceil(s/4);
else if (patlen<1800)
	s=ceil(s/3);
else if (patlen<2400)
	s=ceil(s/2);



 gap_start=firstfit(s+1,0,slots_size);// change it to 3 !!!!!!!!!!!!!!!!!!

		if (gap_start>=0)//there is a gap!
			{	
				 gap_end=gap_start + s;// ebteda va entehaye slot ha
				if (gap_end == slots_size)//agar por nashode bashad
					{
					gap_end--;
					}
					selected_k=k;
				break;
					
					}





k++;
}

if ((gap_start>=0) && (gap_end>=0) && (selected_k<3))
					{
						//add to ls , applying
					 //fprintf(F," K:%d , Path_lngth:%d ",selected_k,Len);
								
					 for (  int i=0; i< Len ; i++)
						 {
						 	 int lnk=a[i];
										
							for (  int j=gap_start ; j<=gap_end; j++)
								{
									Slots[core][lnk][j]=id;
												
								}
							}
					 
					 Transmitter_BVTs[src][TransmitterBVT]=true;//yani in  estefade shod
					 Receiver_BVTs[dest][ReceiverBVT]=true;
					 
					 addnode2(id, selected_k,a, Len, gap_start,gap_end,  s,  src, dest, TransmitterBVT,ReceiverBVT,hlt,endtime,core);
					ress=true;
					 
					 pktnom++;
						number_of_ack+=1;
						bw_ack= bw_ack + size;
					// fprintf(F," ==>OK");
						op_intrpt_schedule_self(op_sim_time ()+ hlt,id);
						op_pk_destroy(pkptr1);
					 }
				else
					{
						
						ress=false;
					}







				}

				else{
			ress=false;
}


//fclose(F);
return (ress);
FRET (ress);
}
/*
*
*
*
*
Malayrti: Data Mining Code!
*
*
*
*
**
***
*
*
**
*
*/
/*
vector<packett> df_filter(vector<packett> const &df, short int source, short int dest) {
	FIN(df_filter());
	vector<packett> v;
	
	for (auto &i : df) {
		if (i.source == source && i.dest == dest) {
			v.push_back(i);
		}
	}
	
	return v;
	FRET (v);
}

vector<packett> df_filter2(vector<packett> const &df, short int needed) {
	FIN(df_filter2());
	vector<packett> v;
	
	for (auto &i : df) {
		if (i.needed == needed) {
			v.push_back(i);
		}
	}
	
	return v;
	FRET (v);
}


float get_diff(vector<packet> const &df) {
	FIN(get_diff());
	float diff = df.at(1).simtime - df.at(0).simtime;
	float diff2;
	
	for(vector<int>::size_type i = 2; i != df.size(); i++) {
		
		diff2 = df.at(i).simtime - df.at(i-1).simtime;
		
		if (!cmpf(diff2, diff)) {
			return -1.0;
			FRET (-1.0);
		}
		}
	
	float value = (int)(diff * 10 + 0.5); 
    return (float)value / 10; 
	FRET ( (float)value / 10);
}*/

/* End of Function Block */

/* Undefine optional tracing in FIN/FOUT/FRET */
/* The FSM has its own tracing code and the other */
/* functions should not have any tracing.		  */
#undef FIN_TRACING
#define FIN_TRACING

#undef FOUTRET_TRACING
#define FOUTRET_TRACING

/* Undefine shortcuts to state variables because the */
/* following functions are part of the state class */
#undef deftime
#undef matrix_counter
#undef linkk_numbers
#undef untransferable_counter
#undef timeclass

/* Access from C kernel using C linkage */
extern "C"
{
	VosT_Obtype _op_malayeryprocess2_init (int * init_block_ptr);
	VosT_Address _op_malayeryprocess2_alloc (VosT_Obtype, int);
	void malayeryprocess2 (OP_SIM_CONTEXT_ARG_OPT)
		{
		((malayeryprocess2_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr))->malayeryprocess2 (OP_SIM_CONTEXT_PTR_OPT);
		}

	void _op_malayeryprocess2_svar (void *, const char *, void **);

	void _op_malayeryprocess2_diag (OP_SIM_CONTEXT_ARG_OPT)
		{
		((malayeryprocess2_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr))->_op_malayeryprocess2_diag (OP_SIM_CONTEXT_PTR_OPT);
		}

	void _op_malayeryprocess2_terminate (OP_SIM_CONTEXT_ARG_OPT)
		{
		/* The destructor is the Termination Block */
		delete (malayeryprocess2_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr);
		}


} /* end of 'extern "C"' */




/* Process model interrupt handling procedure */


void
malayeryprocess2_state::malayeryprocess2 (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (malayeryprocess2_state::malayeryprocess2 ());
	try
		{


		FSM_ENTER ("malayeryprocess2")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (st_0) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (0, "st_0", "malayeryprocess2 [st_0 enter execs]")
				FSM_PROFILE_SECTION_IN ("malayeryprocess2 [st_0 enter execs]", state0_enter_exec)
				{
						ff_rr=22;
						
						/*
						timeclass[0][0]=0;
						timeclass[0][1]=5;//5
						timeclass[1][0]=5;
						timeclass[1][1]=12;//10
						timeclass[2][0]=12;
						timeclass[2][1]=20;//15
						timeclass[3][0]=20;
						timeclass[3][1]=1000;//25
						timeclass[4][0]=0;
						timeclass[4][1]=1000;//1000
						//timeclass[5][0]=50;
						//timeclass[5][1]=1000;//30//1000
						//timeclass[6][0]=0;
						//timeclass[6][1]=1000;*/
						
						
						timeclass[0][0]=0;
						timeclass[0][1]=3.65;//5//3.65
						timeclass[1][0]=3.65;
						timeclass[1][1]=8.11;//10//8.11
						timeclass[2][0]=8.11;
						timeclass[2][1]=13.86;//15//1.86
						timeclass[3][0]=13.86;
						timeclass[3][1]=21.97;//25//21.97
						timeclass[4][0]=21.97;
						timeclass[4][1]=35.84;//50//35.84
						timeclass[5][0]=35.84;
						timeclass[5][1]=1000;//1000
						timeclass[6][0]=0;
						timeclass[6][1]=1000;//1000
						
						transfer_weights[0]=0.12;//0.19
						transfer_weights[1]=0.11;//0.19
						transfer_weights[2]=0.40;//0.25
						transfer_weights[3]=0.12;
						transfer_weights[4]=0.25;//0.25
						
				
						
						reroute_weights[0]=0.25;//0.25
						reroute_weights[1]=0.13;
						reroute_weights[2]=0.13;
						reroute_weights[3]=0.06;
						reroute_weights[4]=0.25;//0.25
						reroute_weights[5]=0.18;//0.18
						
						
						
				
						move_weights[0]=0.15;
						move_weights[1]=0.12;
						move_weights[2]=0.08;
						move_weights[3]=0.12;//0.12
						move_weights[4]=0.12;//0.12
						move_weights[5]=0.15;//0.15
						move_weights[6]=0.12;//0.12
						move_weights[7]=0.15;
						
						
						
						bestfit_weights[0]=0.0; //- or +??? size
						bestfit_weights[1]=0.25;//- left
						bestfit_weights[2]=0.25;//- right
						bestfit_weights[3]=0.5;//+ before - after
						
						
						path_weights[0]=0.00;//0.00
						path_weights[1]=0.35;//0.3 path length
						path_weights[2]=0.4;//0.35 free spaces
						path_weights[3]=0.0;//0.1  average times
						path_weights[4]=0.15;//0.15  FR rate
						path_weights[5]=0.1;//0.1  cons number
						
						
						
						for(int i=0;i<100;i++){
						arr[i][0]=-1;
						arr[i][1]=-1;
						
						}
						
				//////////////////////////////////////////////////
				deftime=op_dist_load ("uniform_int", 1, 5);
				//defcc=2;
				defc=2;
				
				BOK=0;
				BNOK=0;
				
						first=NULL;
						end=NULL;
				pp=first;
				number_of_req=0;
				number_of_nack=0;
				number_of_ack=0;
				bw_req=0;
				bw_ack=0;
				bw_nack=0;
				
				/*
				 for (int i=0; i<44; i++)
						  {
						    for (int j=0; j<=slots_size; j++)
								{
								
								  links_fs[i][j]=0;
								}// 1000 ta fs 
						  
						  }
				 
				
				 
				 for ( int i=0; i<=14; i++) //K shortest path
					 {
					 	for (int j=0; j<=14; j++)
							{
								for ( int k=0; k<=3; k++)// k=3
									{
										for ( int p=0; p<=2; p++)
											{
												for ( int l=0; l<=14; l++)
													{
														paths_node[i][j][k][p][l]=0;
													}
											}
									}
							}
					 }
						*/
						
						for (int i=0;i<14;i++)
					for(int j=0;j<50;j++)
					{
					Transmitter_BVTs[i][j]=false;
					Receiver_BVTs[i][j]=false;
					}
				for(int b=0;b<7;b++)
				for(int i=0;i<42;i++)
					for(int j=0;j<slots_size;j++){
					Slots[b][i][j]=0;
					TEslots[b][i][j]=0;
					times[b][i][j]=-1.0;
					}
						for (int i=0;i<7;i++)
					for(int j=0;j<3;j++)
						classes[i][j]=0;
						
				linkss[0][0]=0;
				linkss[0][1]=1100;
				linkss[0][2]=1600;
				linkss[0][3]=9999;
				linkss[0][4]=9999;
				linkss[0][5]=9999;
				linkss[0][6]=9999;
				linkss[0][7]=2800;
				linkss[0][8]=9999;
				linkss[0][9]=9999;
				linkss[0][10]=9999;
				linkss[0][11]=9999;
				linkss[0][12]=9999;
				linkss[0][13]=9999;
				linkss[1][0]=1100;
				linkss[1][1]=0;
				linkss[1][2]=600;
				linkss[1][3]=1000;
				linkss[1][4]=9999;
				linkss[1][5]=9999;
				linkss[1][6]=9999;
				linkss[1][7]=9999;
				linkss[1][8]=9999;
				linkss[1][9]=9999;
				linkss[1][10]=9999;
				linkss[1][11]=9999;
				linkss[1][12]=9999;
				linkss[1][13]=9999;
				linkss[2][0]=1600;
				linkss[2][1]=600;
				linkss[2][2]=0;
				linkss[2][3]=9999;
				linkss[2][4]=9999;
				linkss[2][5]=2000;
				linkss[2][6]=9999;
				linkss[2][7]=9999;
				linkss[2][8]=9999;
				linkss[2][9]=9999;
				linkss[2][10]=9999;
				linkss[2][11]=9999;
				linkss[2][12]=9999;
				linkss[2][13]=9999;
				linkss[3][0]=9999;
				linkss[3][1]=1000;
				linkss[3][2]=9999;
				linkss[3][3]=0;
				linkss[3][4]=600;
				linkss[3][5]=9999;
				linkss[3][6]=9999;
				linkss[3][7]=9999;
				linkss[3][8]=9999;
				linkss[3][9]=9999;
				linkss[3][10]=2400;
				linkss[3][11]=9999;
				linkss[3][12]=9999;
				linkss[3][13]=9999;
				linkss[4][0]=9999;
				linkss[4][1]=9999;
				linkss[4][2]=9999;
				linkss[4][3]=600;
				linkss[4][4]=0;
				linkss[4][5]=1100;
				linkss[4][6]=800;
				linkss[4][7]=9999;
				linkss[4][8]=9999;
				linkss[4][9]=9999;
				linkss[4][10]=9999;
				linkss[4][11]=9999;
				linkss[4][12]=9999;
				linkss[4][13]=9999;
				linkss[5][0]=9999;
				linkss[5][1]=9999;
				linkss[5][2]=2000;
				linkss[5][3]=9999;
				linkss[5][4]=1100;
				linkss[5][5]=0;
				linkss[5][6]=9999;
				linkss[5][7]=9999;
				linkss[5][8]=9999;
				linkss[5][9]=1200;
				linkss[5][10]=9999;
				linkss[5][11]=9999;
				linkss[5][12]=2000;
				linkss[5][13]=9999;
				linkss[6][0]=9999;
				linkss[6][1]=9999;
				linkss[6][2]=9999;
				linkss[6][3]=9999;
				linkss[6][4]=800;
				linkss[6][5]=9999;
				linkss[6][6]=0;
				linkss[6][7]=700;
				linkss[6][8]=9999;
				linkss[6][9]=9999;
				linkss[6][10]=9999;
				linkss[6][11]=9999;
				linkss[6][12]=9999;
				linkss[6][13]=9999;
				linkss[7][0]=2800;
				linkss[7][1]=9999;
				linkss[7][2]=9999;
				linkss[7][3]=9999;
				linkss[7][4]=9999;
				linkss[7][5]=9999;
				linkss[7][6]=700;
				linkss[7][7]=0;
				linkss[7][8]=700;
				linkss[7][9]=9999;
				linkss[7][10]=9999;
				linkss[7][11]=9999;
				linkss[7][12]=9999;
				linkss[7][13]=9999;
				linkss[8][0]=9999;
				linkss[8][1]=9999;
				linkss[8][2]=9999;
				linkss[8][3]=9999;
				linkss[8][4]=9999;
				linkss[8][5]=9999;
				linkss[8][6]=9999;
				linkss[8][7]=700;
				linkss[8][8]=0;
				linkss[8][9]=900;
				linkss[8][10]=9999;
				linkss[8][11]=500;
				linkss[8][12]=9999;
				linkss[8][13]=500;
				linkss[9][0]=9999;
				linkss[9][1]=9999;
				linkss[9][2]=9999;
				linkss[9][3]=9999;
				linkss[9][4]=9999;
				linkss[9][5]=1200;
				linkss[9][6]=9999;
				linkss[9][7]=9999;
				linkss[9][8]=900;
				linkss[9][9]=0;
				linkss[9][10]=9999;
				linkss[9][11]=9999;
				linkss[9][12]=9999;
				linkss[9][13]=9999;
				linkss[10][0]=9999;
				linkss[10][1]=9999;
				linkss[10][2]=9999;
				linkss[10][3]=2400;
				linkss[10][4]=9999;
				linkss[10][5]=9999;
				linkss[10][6]=9999;
				linkss[10][7]=9999;
				linkss[10][8]=9999;
				linkss[10][9]=9999;
				linkss[10][10]=0;
				linkss[10][11]=800;
				linkss[10][12]=9999;
				linkss[10][13]=800;
				linkss[11][0]=9999;
				linkss[11][1]=9999;
				linkss[11][2]=9999;
				linkss[11][3]=9999;
				linkss[11][4]=9999;
				linkss[11][5]=9999;
				linkss[11][6]=9999;
				linkss[11][7]=9999;
				linkss[11][8]=500;
				linkss[11][9]=9999;
				linkss[11][10]=800;
				linkss[11][11]=0;
				linkss[11][12]=300;
				linkss[11][13]=9999;
				linkss[12][0]=9999;
				linkss[12][1]=9999;
				linkss[12][2]=9999;
				linkss[12][3]=9999;
				linkss[12][4]=9999;
				linkss[12][5]=2000;
				linkss[12][6]=9999;
				linkss[12][7]=9999;
				linkss[12][8]=9999;
				linkss[12][9]=9999;
				linkss[12][10]=9999;
				linkss[12][11]=300;
				linkss[12][12]=0;
				linkss[12][13]=300;
				linkss[13][0]=9999;
				linkss[13][1]=9999;
				linkss[13][2]=9999;
				linkss[13][3]=9999;
				linkss[13][4]=9999;
				linkss[13][5]=9999;
				linkss[13][6]=9999;
				linkss[13][7]=9999;
				linkss[13][8]=500;
				linkss[13][9]=9999;
				linkss[13][10]=800;
				linkss[13][11]=9999;
				linkss[13][12]=300;
				linkss[13][13]=0;
				
				 link_number_counter=0;
				 
				for(int i=0;i<14;i++)
					for(int j=0;j<14;j++)
						linkk_numbers[i][j]=-1;
				
				linkk_numbers[0][1]=0;
				linkk_numbers[0][2]=1;
				linkk_numbers[0][7]=2;
				linkk_numbers[1][0]=3;
				linkk_numbers[1][2]=4;
				linkk_numbers[1][3]=5;
				linkk_numbers[2][0]=6;
				linkk_numbers[2][1]=7;
				linkk_numbers[2][5]=8;
				linkk_numbers[3][1]=9;
				linkk_numbers[3][4]=10;
				linkk_numbers[3][10]=11;
				linkk_numbers[4][3]=12;
				linkk_numbers[4][5]=13;
				linkk_numbers[4][6]=14;
				linkk_numbers[5][2]=15;
				linkk_numbers[5][4]=16;
				linkk_numbers[5][9]=17;
				linkk_numbers[5][12]=18;
				linkk_numbers[6][4]=19;
				linkk_numbers[6][7]=20;
				linkk_numbers[7][0]=21;
				linkk_numbers[7][6]=22;
				linkk_numbers[7][8]=23;
				linkk_numbers[8][7]=24;
				linkk_numbers[8][9]=25;
				linkk_numbers[8][11]=26;
				linkk_numbers[8][13]=27;
				linkk_numbers[9][5]=28;
				linkk_numbers[9][8]=29;
				linkk_numbers[10][3]=30;
				linkk_numbers[10][11]=31;
				linkk_numbers[10][13]=32;
				linkk_numbers[11][8]=33;
				linkk_numbers[11][10]=34;
				linkk_numbers[11][12]=35;
				linkk_numbers[12][5]=36;
				linkk_numbers[12][11]=37;
				linkk_numbers[12][13]=38;
				linkk_numbers[13][8]=39;
				linkk_numbers[13][10]=40;
				linkk_numbers[13][12]=41;
				
				
				
				
				
				
				
				for (int i=0;i<14;i++)
					for(int j=0;j<14;j++)
						for(int k=0;k<3;k++)
							for(int l=0;l<10;l++){
							KSP[i][j][k][l]=-1;}
				
				KSP[0][0][0][0]=0;
				KSP[0][0][0][1]=0;
				KSP[0][1][0][0]=0;
				KSP[0][1][0][1]=1;
				KSP[0][1][1][0]=0;
				KSP[0][1][1][1]=2;
				KSP[0][1][1][2]=1;
				KSP[0][1][2][0]=0;
				KSP[0][1][2][1]=7;
				KSP[0][1][2][2]=6;
				KSP[0][1][2][3]=4;
				KSP[0][1][2][4]=3;
				KSP[0][1][2][5]=1;
				KSP[0][2][0][0]=0;
				KSP[0][2][0][1]=2;
				KSP[0][2][1][0]=0;
				KSP[0][2][1][1]=1;
				KSP[0][2][1][2]=2;
				KSP[0][2][2][0]=0;
				KSP[0][2][2][1]=1;
				KSP[0][2][2][2]=3;
				KSP[0][2][2][3]=4;
				KSP[0][2][2][4]=5;
				KSP[0][2][2][5]=2;
				KSP[0][3][0][0]=0;
				KSP[0][3][0][1]=1;
				KSP[0][3][0][2]=3;
				KSP[0][3][1][0]=0;
				KSP[0][3][1][1]=2;
				KSP[0][3][1][2]=1;
				KSP[0][3][1][3]=3;
				KSP[0][3][2][0]=0;
				KSP[0][3][2][1]=7;
				KSP[0][3][2][2]=6;
				KSP[0][3][2][3]=4;
				KSP[0][3][2][4]=3;
				KSP[0][4][0][0]=0;
				KSP[0][4][0][1]=1;
				KSP[0][4][0][2]=3;
				KSP[0][4][0][3]=4;
				KSP[0][4][1][0]=0;
				KSP[0][4][1][1]=2;
				KSP[0][4][1][2]=1;
				KSP[0][4][1][3]=3;
				KSP[0][4][1][4]=4;
				KSP[0][4][2][0]=0;
				KSP[0][4][2][1]=7;
				KSP[0][4][2][2]=6;
				KSP[0][4][2][3]=4;
				KSP[0][5][0][0]=0;
				KSP[0][5][0][1]=2;
				KSP[0][5][0][2]=5;
				KSP[0][5][1][0]=0;
				KSP[0][5][1][1]=1;
				KSP[0][5][1][2]=2;
				KSP[0][5][1][3]=5;
				KSP[0][5][2][0]=0;
				KSP[0][5][2][1]=1;
				KSP[0][5][2][2]=3;
				KSP[0][5][2][3]=4;
				KSP[0][5][2][4]=5;
				KSP[0][6][0][0]=0;
				KSP[0][6][0][1]=1;
				KSP[0][6][0][2]=3;
				KSP[0][6][0][3]=4;
				KSP[0][6][0][4]=6;
				KSP[0][6][1][0]=0;
				KSP[0][6][1][1]=7;
				KSP[0][6][1][2]=6;
				KSP[0][6][2][0]=0;
				KSP[0][6][2][1]=2;
				KSP[0][6][2][2]=1;
				KSP[0][6][2][3]=3;
				KSP[0][6][2][4]=4;
				KSP[0][6][2][5]=6;
				KSP[0][7][0][0]=0;
				KSP[0][7][0][1]=7;
				KSP[0][7][1][0]=0;
				KSP[0][7][1][1]=1;
				KSP[0][7][1][2]=3;
				KSP[0][7][1][3]=4;
				KSP[0][7][1][4]=6;
				KSP[0][7][1][5]=7;
				KSP[0][7][2][0]=0;
				KSP[0][7][2][1]=2;
				KSP[0][7][2][2]=1;
				KSP[0][7][2][3]=3;
				KSP[0][7][2][4]=4;
				KSP[0][7][2][5]=6;
				KSP[0][7][2][6]=7;
				KSP[0][8][0][0]=0;
				KSP[0][8][0][1]=7;
				KSP[0][8][0][2]=8;
				KSP[0][8][1][0]=0;
				KSP[0][8][1][1]=1;
				KSP[0][8][1][2]=3;
				KSP[0][8][1][3]=4;
				KSP[0][8][1][4]=6;
				KSP[0][8][1][5]=7;
				KSP[0][8][1][6]=8;
				KSP[0][8][2][0]=0;
				KSP[0][8][2][1]=2;
				KSP[0][8][2][2]=5;
				KSP[0][8][2][3]=9;
				KSP[0][8][2][4]=8;
				KSP[0][9][0][0]=0;
				KSP[0][9][0][1]=7;
				KSP[0][9][0][2]=8;
				KSP[0][9][0][3]=9;
				KSP[0][9][1][0]=0;
				KSP[0][9][1][1]=2;
				KSP[0][9][1][2]=5;
				KSP[0][9][1][3]=9;
				KSP[0][9][2][0]=0;
				KSP[0][9][2][1]=1;
				KSP[0][9][2][2]=2;
				KSP[0][9][2][3]=5;
				KSP[0][9][2][4]=9;
				KSP[0][10][0][0]=0;
				KSP[0][10][0][1]=1;
				KSP[0][10][0][2]=3;
				KSP[0][10][0][3]=10;
				KSP[0][10][1][0]=0;
				KSP[0][10][1][1]=7;
				KSP[0][10][1][2]=8;
				KSP[0][10][1][3]=13;
				KSP[0][10][1][4]=10;
				KSP[0][10][2][0]=0;
				KSP[0][10][2][1]=7;
				KSP[0][10][2][2]=8;
				KSP[0][10][2][3]=11;
				KSP[0][10][2][4]=10;
				KSP[0][11][0][0]=0;
				KSP[0][11][0][1]=7;
				KSP[0][11][0][2]=8;
				KSP[0][11][0][3]=11;
				KSP[0][11][1][0]=0;
				KSP[0][11][1][1]=7;
				KSP[0][11][1][2]=8;
				KSP[0][11][1][3]=13;
				KSP[0][11][1][4]=12;
				KSP[0][11][1][5]=11;
				KSP[0][11][2][0]=0;
				KSP[0][11][2][1]=1;
				KSP[0][11][2][2]=3;
				KSP[0][11][2][3]=10;
				KSP[0][11][2][4]=11;
				KSP[0][12][0][0]=0;
				KSP[0][12][0][1]=7;
				KSP[0][12][0][2]=8;
				KSP[0][12][0][3]=13;
				KSP[0][12][0][4]=12;
				KSP[0][12][1][0]=0;
				KSP[0][12][1][1]=7;
				KSP[0][12][1][2]=8;
				KSP[0][12][1][3]=11;
				KSP[0][12][1][4]=12;
				KSP[0][12][2][0]=0;
				KSP[0][12][2][1]=1;
				KSP[0][12][2][2]=3;
				KSP[0][12][2][3]=10;
				KSP[0][12][2][4]=11;
				KSP[0][12][2][5]=12;
				KSP[0][13][0][0]=0;
				KSP[0][13][0][1]=7;
				KSP[0][13][0][2]=8;
				KSP[0][13][0][3]=13;
				KSP[0][13][1][0]=0;
				KSP[0][13][1][1]=7;
				KSP[0][13][1][2]=8;
				KSP[0][13][1][3]=11;
				KSP[0][13][1][4]=12;
				KSP[0][13][1][5]=13;
				KSP[0][13][2][0]=0;
				KSP[0][13][2][1]=1;
				KSP[0][13][2][2]=3;
				KSP[0][13][2][3]=10;
				KSP[0][13][2][4]=13;
				KSP[1][0][0][0]=1;
				KSP[1][0][0][1]=0;
				KSP[1][0][1][0]=1;
				KSP[1][0][1][1]=2;
				KSP[1][0][1][2]=0;
				KSP[1][0][2][0]=1;
				KSP[1][0][2][1]=3;
				KSP[1][0][2][2]=4;
				KSP[1][0][2][3]=6;
				KSP[1][0][2][4]=7;
				KSP[1][0][2][5]=0;
				KSP[1][1][0][0]=1;
				KSP[1][1][0][1]=1;
				KSP[1][2][0][0]=1;
				KSP[1][2][0][1]=2;
				KSP[1][2][1][0]=1;
				KSP[1][2][1][1]=0;
				KSP[1][2][1][2]=2;
				KSP[1][2][2][0]=1;
				KSP[1][2][2][1]=3;
				KSP[1][2][2][2]=4;
				KSP[1][2][2][3]=5;
				KSP[1][2][2][4]=2;
				KSP[1][3][0][0]=1;
				KSP[1][3][0][1]=3;
				KSP[1][3][1][0]=1;
				KSP[1][3][1][1]=2;
				KSP[1][3][1][2]=5;
				KSP[1][3][1][3]=4;
				KSP[1][3][1][4]=3;
				KSP[1][3][2][0]=1;
				KSP[1][3][2][1]=0;
				KSP[1][3][2][2]=7;
				KSP[1][3][2][3]=6;
				KSP[1][3][2][4]=4;
				KSP[1][3][2][5]=3;
				KSP[1][4][0][0]=1;
				KSP[1][4][0][1]=3;
				KSP[1][4][0][2]=4;
				KSP[1][4][1][0]=1;
				KSP[1][4][1][1]=2;
				KSP[1][4][1][2]=5;
				KSP[1][4][1][3]=4;
				KSP[1][4][2][0]=1;
				KSP[1][4][2][1]=0;
				KSP[1][4][2][2]=7;
				KSP[1][4][2][3]=6;
				KSP[1][4][2][4]=4;
				KSP[1][5][0][0]=1;
				KSP[1][5][0][1]=2;
				KSP[1][5][0][2]=5;
				KSP[1][5][1][0]=1;
				KSP[1][5][1][1]=3;
				KSP[1][5][1][2]=4;
				KSP[1][5][1][3]=5;
				KSP[1][5][2][0]=1;
				KSP[1][5][2][1]=0;
				KSP[1][5][2][2]=2;
				KSP[1][5][2][3]=5;
				KSP[1][6][0][0]=1;
				KSP[1][6][0][1]=3;
				KSP[1][6][0][2]=4;
				KSP[1][6][0][3]=6;
				KSP[1][6][1][0]=1;
				KSP[1][6][1][1]=2;
				KSP[1][6][1][2]=5;
				KSP[1][6][1][3]=4;
				KSP[1][6][1][4]=6;
				KSP[1][6][2][0]=1;
				KSP[1][6][2][1]=0;
				KSP[1][6][2][2]=7;
				KSP[1][6][2][3]=6;
				KSP[1][7][0][0]=1;
				KSP[1][7][0][1]=3;
				KSP[1][7][0][2]=4;
				KSP[1][7][0][3]=6;
				KSP[1][7][0][4]=7;
				KSP[1][7][1][0]=1;
				KSP[1][7][1][1]=0;
				KSP[1][7][1][2]=7;
				KSP[1][7][2][0]=1;
				KSP[1][7][2][1]=2;
				KSP[1][7][2][2]=0;
				KSP[1][7][2][3]=7;
				KSP[1][8][0][0]=1;
				KSP[1][8][0][1]=3;
				KSP[1][8][0][2]=4;
				KSP[1][8][0][3]=6;
				KSP[1][8][0][4]=7;
				KSP[1][8][0][5]=8;
				KSP[1][8][1][0]=1;
				KSP[1][8][1][1]=0;
				KSP[1][8][1][2]=7;
				KSP[1][8][1][3]=8;
				KSP[1][8][2][0]=1;
				KSP[1][8][2][1]=3;
				KSP[1][8][2][2]=10;
				KSP[1][8][2][3]=11;
				KSP[1][8][2][4]=8;
				KSP[1][9][0][0]=1;
				KSP[1][9][0][1]=2;
				KSP[1][9][0][2]=5;
				KSP[1][9][0][3]=9;
				KSP[1][9][1][0]=1;
				KSP[1][9][1][1]=3;
				KSP[1][9][1][2]=4;
				KSP[1][9][1][3]=5;
				KSP[1][9][1][4]=9;
				KSP[1][9][2][0]=1;
				KSP[1][9][2][1]=3;
				KSP[1][9][2][2]=4;
				KSP[1][9][2][3]=6;
				KSP[1][9][2][4]=7;
				KSP[1][9][2][5]=8;
				KSP[1][9][2][6]=9;
				KSP[1][10][0][0]=1;
				KSP[1][10][0][1]=3;
				KSP[1][10][0][2]=10;
				KSP[1][10][1][0]=1;
				KSP[1][10][1][1]=3;
				KSP[1][10][1][2]=4;
				KSP[1][10][1][3]=6;
				KSP[1][10][1][4]=7;
				KSP[1][10][1][5]=8;
				KSP[1][10][1][6]=11;
				KSP[1][10][1][7]=10;
				KSP[1][10][2][0]=1;
				KSP[1][10][2][1]=3;
				KSP[1][10][2][2]=4;
				KSP[1][10][2][3]=6;
				KSP[1][10][2][4]=7;
				KSP[1][10][2][5]=8;
				KSP[1][10][2][6]=13;
				KSP[1][10][2][7]=10;
				KSP[1][11][0][0]=1;
				KSP[1][11][0][1]=3;
				KSP[1][11][0][2]=10;
				KSP[1][11][0][3]=11;
				KSP[1][11][1][0]=1;
				KSP[1][11][1][1]=3;
				KSP[1][11][1][2]=4;
				KSP[1][11][1][3]=6;
				KSP[1][11][1][4]=7;
				KSP[1][11][1][5]=8;
				KSP[1][11][1][6]=11;
				KSP[1][11][2][0]=1;
				KSP[1][11][2][1]=3;
				KSP[1][11][2][2]=10;
				KSP[1][11][2][3]=13;
				KSP[1][11][2][4]=12;
				KSP[1][11][2][5]=11;
				KSP[1][12][0][0]=1;
				KSP[1][12][0][1]=3;
				KSP[1][12][0][2]=10;
				KSP[1][12][0][3]=11;
				KSP[1][12][0][4]=12;
				KSP[1][12][1][0]=1;
				KSP[1][12][1][1]=3;
				KSP[1][12][1][2]=10;
				KSP[1][12][1][3]=13;
				KSP[1][12][1][4]=12;
				KSP[1][12][2][0]=1;
				KSP[1][12][2][1]=3;
				KSP[1][12][2][2]=4;
				KSP[1][12][2][3]=6;
				KSP[1][12][2][4]=7;
				KSP[1][12][2][5]=8;
				KSP[1][12][2][6]=13;
				KSP[1][12][2][7]=12;
				KSP[1][13][0][0]=1;
				KSP[1][13][0][1]=3;
				KSP[1][13][0][2]=10;
				KSP[1][13][0][3]=13;
				KSP[1][13][1][0]=1;
				KSP[1][13][1][1]=3;
				KSP[1][13][1][2]=4;
				KSP[1][13][1][3]=6;
				KSP[1][13][1][4]=7;
				KSP[1][13][1][5]=8;
				KSP[1][13][1][6]=13;
				KSP[1][13][2][0]=1;
				KSP[1][13][2][1]=3;
				KSP[1][13][2][2]=10;
				KSP[1][13][2][3]=11;
				KSP[1][13][2][4]=12;
				KSP[1][13][2][5]=13;
				KSP[2][0][0][0]=2;
				KSP[2][0][0][1]=0;
				KSP[2][0][1][0]=2;
				KSP[2][0][1][1]=1;
				KSP[2][0][1][2]=0;
				KSP[2][0][2][0]=2;
				KSP[2][0][2][1]=5;
				KSP[2][0][2][2]=4;
				KSP[2][0][2][3]=3;
				KSP[2][0][2][4]=1;
				KSP[2][0][2][5]=0;
				KSP[2][1][0][0]=2;
				KSP[2][1][0][1]=1;
				KSP[2][1][1][0]=2;
				KSP[2][1][1][1]=0;
				KSP[2][1][1][2]=1;
				KSP[2][1][2][0]=2;
				KSP[2][1][2][1]=5;
				KSP[2][1][2][2]=4;
				KSP[2][1][2][3]=3;
				KSP[2][1][2][4]=1;
				KSP[2][2][0][0]=2;
				KSP[2][2][0][1]=2;
				KSP[2][3][0][0]=2;
				KSP[2][3][0][1]=1;
				KSP[2][3][0][2]=3;
				KSP[2][3][1][0]=2;
				KSP[2][3][1][1]=0;
				KSP[2][3][1][2]=1;
				KSP[2][3][1][3]=3;
				KSP[2][3][2][0]=2;
				KSP[2][3][2][1]=5;
				KSP[2][3][2][2]=4;
				KSP[2][3][2][3]=3;
				KSP[2][4][0][0]=2;
				KSP[2][4][0][1]=1;
				KSP[2][4][0][2]=3;
				KSP[2][4][0][3]=4;
				KSP[2][4][1][0]=2;
				KSP[2][4][1][1]=5;
				KSP[2][4][1][2]=4;
				KSP[2][4][2][0]=2;
				KSP[2][4][2][1]=0;
				KSP[2][4][2][2]=1;
				KSP[2][4][2][3]=3;
				KSP[2][4][2][4]=4;
				KSP[2][5][0][0]=2;
				KSP[2][5][0][1]=5;
				KSP[2][5][1][0]=2;
				KSP[2][5][1][1]=1;
				KSP[2][5][1][2]=3;
				KSP[2][5][1][3]=4;
				KSP[2][5][1][4]=5;
				KSP[2][5][2][0]=2;
				KSP[2][5][2][1]=0;
				KSP[2][5][2][2]=1;
				KSP[2][5][2][3]=3;
				KSP[2][5][2][4]=4;
				KSP[2][5][2][5]=5;
				KSP[2][6][0][0]=2;
				KSP[2][6][0][1]=1;
				KSP[2][6][0][2]=3;
				KSP[2][6][0][3]=4;
				KSP[2][6][0][4]=6;
				KSP[2][6][1][0]=2;
				KSP[2][6][1][1]=5;
				KSP[2][6][1][2]=4;
				KSP[2][6][1][3]=6;
				KSP[2][6][2][0]=2;
				KSP[2][6][2][1]=0;
				KSP[2][6][2][2]=7;
				KSP[2][6][2][3]=6;
				KSP[2][7][0][0]=2;
				KSP[2][7][0][1]=1;
				KSP[2][7][0][2]=3;
				KSP[2][7][0][3]=4;
				KSP[2][7][0][4]=6;
				KSP[2][7][0][5]=7;
				KSP[2][7][1][0]=2;
				KSP[2][7][1][1]=0;
				KSP[2][7][1][2]=7;
				KSP[2][7][2][0]=2;
				KSP[2][7][2][1]=1;
				KSP[2][7][2][2]=0;
				KSP[2][7][2][3]=7;
				KSP[2][8][0][0]=2;
				KSP[2][8][0][1]=5;
				KSP[2][8][0][2]=9;
				KSP[2][8][0][3]=8;
				KSP[2][8][1][0]=2;
				KSP[2][8][1][1]=1;
				KSP[2][8][1][2]=3;
				KSP[2][8][1][3]=4;
				KSP[2][8][1][4]=6;
				KSP[2][8][1][5]=7;
				KSP[2][8][1][6]=8;
				KSP[2][8][2][0]=2;
				KSP[2][8][2][1]=5;
				KSP[2][8][2][2]=12;
				KSP[2][8][2][3]=13;
				KSP[2][8][2][4]=8;
				KSP[2][9][0][0]=2;
				KSP[2][9][0][1]=5;
				KSP[2][9][0][2]=9;
				KSP[2][9][1][0]=2;
				KSP[2][9][1][1]=1;
				KSP[2][9][1][2]=3;
				KSP[2][9][1][3]=4;
				KSP[2][9][1][4]=5;
				KSP[2][9][1][5]=9;
				KSP[2][9][2][0]=2;
				KSP[2][9][2][1]=1;
				KSP[2][9][2][2]=3;
				KSP[2][9][2][3]=4;
				KSP[2][9][2][4]=6;
				KSP[2][9][2][5]=7;
				KSP[2][9][2][6]=8;
				KSP[2][9][2][7]=9;
				KSP[2][10][0][0]=2;
				KSP[2][10][0][1]=1;
				KSP[2][10][0][2]=3;
				KSP[2][10][0][3]=10;
				KSP[2][10][1][0]=2;
				KSP[2][10][1][1]=5;
				KSP[2][10][1][2]=12;
				KSP[2][10][1][3]=11;
				KSP[2][10][1][4]=10;
				KSP[2][10][2][0]=2;
				KSP[2][10][2][1]=5;
				KSP[2][10][2][2]=12;
				KSP[2][10][2][3]=13;
				KSP[2][10][2][4]=10;
				KSP[2][11][0][0]=2;
				KSP[2][11][0][1]=5;
				KSP[2][11][0][2]=12;
				KSP[2][11][0][3]=11;
				KSP[2][11][1][0]=2;
				KSP[2][11][1][1]=5;
				KSP[2][11][1][2]=9;
				KSP[2][11][1][3]=8;
				KSP[2][11][1][4]=11;
				KSP[2][11][2][0]=2;
				KSP[2][11][2][1]=1;
				KSP[2][11][2][2]=3;
				KSP[2][11][2][3]=10;
				KSP[2][11][2][4]=11;
				KSP[2][12][0][0]=2;
				KSP[2][12][0][1]=5;
				KSP[2][12][0][2]=12;
				KSP[2][12][1][0]=2;
				KSP[2][12][1][1]=5;
				KSP[2][12][1][2]=9;
				KSP[2][12][1][3]=8;
				KSP[2][12][1][4]=13;
				KSP[2][12][1][5]=12;
				KSP[2][12][2][0]=2;
				KSP[2][12][2][1]=5;
				KSP[2][12][2][2]=9;
				KSP[2][12][2][3]=8;
				KSP[2][12][2][4]=11;
				KSP[2][12][2][5]=12;
				KSP[2][13][0][0]=2;
				KSP[2][13][0][1]=5;
				KSP[2][13][0][2]=12;
				KSP[2][13][0][3]=13;
				KSP[2][13][1][0]=2;
				KSP[2][13][1][1]=5;
				KSP[2][13][1][2]=9;
				KSP[2][13][1][3]=8;
				KSP[2][13][1][4]=13;
				KSP[2][13][2][0]=2;
				KSP[2][13][2][1]=1;
				KSP[2][13][2][2]=3;
				KSP[2][13][2][3]=10;
				KSP[2][13][2][4]=13;
				KSP[3][0][0][0]=3;
				KSP[3][0][0][1]=1;
				KSP[3][0][0][2]=0;
				KSP[3][0][1][0]=3;
				KSP[3][0][1][1]=1;
				KSP[3][0][1][2]=2;
				KSP[3][0][1][3]=0;
				KSP[3][0][2][0]=3;
				KSP[3][0][2][1]=4;
				KSP[3][0][2][2]=6;
				KSP[3][0][2][3]=7;
				KSP[3][0][2][4]=0;
				KSP[3][1][0][0]=3;
				KSP[3][1][0][1]=1;
				KSP[3][1][1][0]=3;
				KSP[3][1][1][1]=4;
				KSP[3][1][1][2]=5;
				KSP[3][1][1][3]=2;
				KSP[3][1][1][4]=1;
				KSP[3][1][2][0]=3;
				KSP[3][1][2][1]=4;
				KSP[3][1][2][2]=6;
				KSP[3][1][2][3]=7;
				KSP[3][1][2][4]=0;
				KSP[3][1][2][5]=1;
				KSP[3][2][0][0]=3;
				KSP[3][2][0][1]=1;
				KSP[3][2][0][2]=2;
				KSP[3][2][1][0]=3;
				KSP[3][2][1][1]=1;
				KSP[3][2][1][2]=0;
				KSP[3][2][1][3]=2;
				KSP[3][2][2][0]=3;
				KSP[3][2][2][1]=4;
				KSP[3][2][2][2]=5;
				KSP[3][2][2][3]=2;
				KSP[3][3][0][0]=3;
				KSP[3][3][0][1]=3;
				KSP[3][4][0][0]=3;
				KSP[3][4][0][1]=4;
				KSP[3][4][1][0]=3;
				KSP[3][4][1][1]=1;
				KSP[3][4][1][2]=2;
				KSP[3][4][1][3]=5;
				KSP[3][4][1][4]=4;
				KSP[3][4][2][0]=3;
				KSP[3][4][2][1]=10;
				KSP[3][4][2][2]=11;
				KSP[3][4][2][3]=8;
				KSP[3][4][2][4]=7;
				KSP[3][4][2][5]=6;
				KSP[3][4][2][6]=4;
				KSP[3][5][0][0]=3;
				KSP[3][5][0][1]=4;
				KSP[3][5][0][2]=5;
				KSP[3][5][1][0]=3;
				KSP[3][5][1][1]=1;
				KSP[3][5][1][2]=2;
				KSP[3][5][1][3]=5;
				KSP[3][5][2][0]=3;
				KSP[3][5][2][1]=4;
				KSP[3][5][2][2]=6;
				KSP[3][5][2][3]=7;
				KSP[3][5][2][4]=8;
				KSP[3][5][2][5]=9;
				KSP[3][5][2][6]=5;
				KSP[3][6][0][0]=3;
				KSP[3][6][0][1]=4;
				KSP[3][6][0][2]=6;
				KSP[3][6][1][0]=3;
				KSP[3][6][1][1]=10;
				KSP[3][6][1][2]=11;
				KSP[3][6][1][3]=8;
				KSP[3][6][1][4]=7;
				KSP[3][6][1][5]=6;
				KSP[3][6][2][0]=3;
				KSP[3][6][2][1]=10;
				KSP[3][6][2][2]=13;
				KSP[3][6][2][3]=8;
				KSP[3][6][2][4]=7;
				KSP[3][6][2][5]=6;
				KSP[3][7][0][0]=3;
				KSP[3][7][0][1]=4;
				KSP[3][7][0][2]=6;
				KSP[3][7][0][3]=7;
				KSP[3][7][1][0]=3;
				KSP[3][7][1][1]=10;
				KSP[3][7][1][2]=11;
				KSP[3][7][1][3]=8;
				KSP[3][7][1][4]=7;
				KSP[3][7][2][0]=3;
				KSP[3][7][2][1]=10;
				KSP[3][7][2][2]=13;
				KSP[3][7][2][3]=8;
				KSP[3][7][2][4]=7;
				KSP[3][8][0][0]=3;
				KSP[3][8][0][1]=4;
				KSP[3][8][0][2]=6;
				KSP[3][8][0][3]=7;
				KSP[3][8][0][4]=8;
				KSP[3][8][1][0]=3;
				KSP[3][8][1][1]=10;
				KSP[3][8][1][2]=11;
				KSP[3][8][1][3]=8;
				KSP[3][8][2][0]=3;
				KSP[3][8][2][1]=10;
				KSP[3][8][2][2]=13;
				KSP[3][8][2][3]=8;
				KSP[3][9][0][0]=3;
				KSP[3][9][0][1]=4;
				KSP[3][9][0][2]=5;
				KSP[3][9][0][3]=9;
				KSP[3][9][1][0]=3;
				KSP[3][9][1][1]=4;
				KSP[3][9][1][2]=6;
				KSP[3][9][1][3]=7;
				KSP[3][9][1][4]=8;
				KSP[3][9][1][5]=9;
				KSP[3][9][2][0]=3;
				KSP[3][9][2][1]=10;
				KSP[3][9][2][2]=13;
				KSP[3][9][2][3]=8;
				KSP[3][9][2][4]=9;
				KSP[3][10][0][0]=3;
				KSP[3][10][0][1]=10;
				KSP[3][10][1][0]=3;
				KSP[3][10][1][1]=4;
				KSP[3][10][1][2]=6;
				KSP[3][10][1][3]=7;
				KSP[3][10][1][4]=8;
				KSP[3][10][1][5]=11;
				KSP[3][10][1][6]=10;
				KSP[3][10][2][0]=3;
				KSP[3][10][2][1]=4;
				KSP[3][10][2][2]=6;
				KSP[3][10][2][3]=7;
				KSP[3][10][2][4]=8;
				KSP[3][10][2][5]=13;
				KSP[3][10][2][6]=10;
				KSP[3][11][0][0]=3;
				KSP[3][11][0][1]=10;
				KSP[3][11][0][2]=11;
				KSP[3][11][1][0]=3;
				KSP[3][11][1][1]=4;
				KSP[3][11][1][2]=6;
				KSP[3][11][1][3]=7;
				KSP[3][11][1][4]=8;
				KSP[3][11][1][5]=11;
				KSP[3][11][2][0]=3;
				KSP[3][11][2][1]=10;
				KSP[3][11][2][2]=13;
				KSP[3][11][2][3]=12;
				KSP[3][11][2][4]=11;
				KSP[3][12][0][0]=3;
				KSP[3][12][0][1]=10;
				KSP[3][12][0][2]=11;
				KSP[3][12][0][3]=12;
				KSP[3][12][1][0]=3;
				KSP[3][12][1][1]=10;
				KSP[3][12][1][2]=13;
				KSP[3][12][1][3]=12;
				KSP[3][12][2][0]=3;
				KSP[3][12][2][1]=4;
				KSP[3][12][2][2]=6;
				KSP[3][12][2][3]=7;
				KSP[3][12][2][4]=8;
				KSP[3][12][2][5]=13;
				KSP[3][12][2][6]=12;
				KSP[3][13][0][0]=3;
				KSP[3][13][0][1]=10;
				KSP[3][13][0][2]=13;
				KSP[3][13][1][0]=3;
				KSP[3][13][1][1]=4;
				KSP[3][13][1][2]=6;
				KSP[3][13][1][3]=7;
				KSP[3][13][1][4]=8;
				KSP[3][13][1][5]=13;
				KSP[3][13][2][0]=3;
				KSP[3][13][2][1]=10;
				KSP[3][13][2][2]=11;
				KSP[3][13][2][3]=12;
				KSP[3][13][2][4]=13;
				KSP[4][0][0][0]=4;
				KSP[4][0][0][1]=3;
				KSP[4][0][0][2]=1;
				KSP[4][0][0][3]=0;
				KSP[4][0][1][0]=4;
				KSP[4][0][1][1]=3;
				KSP[4][0][1][2]=1;
				KSP[4][0][1][3]=2;
				KSP[4][0][1][4]=0;
				KSP[4][0][2][0]=4;
				KSP[4][0][2][1]=6;
				KSP[4][0][2][2]=7;
				KSP[4][0][2][3]=0;
				KSP[4][1][0][0]=4;
				KSP[4][1][0][1]=3;
				KSP[4][1][0][2]=1;
				KSP[4][1][1][0]=4;
				KSP[4][1][1][1]=5;
				KSP[4][1][1][2]=2;
				KSP[4][1][1][3]=1;
				KSP[4][1][2][0]=4;
				KSP[4][1][2][1]=6;
				KSP[4][1][2][2]=7;
				KSP[4][1][2][3]=0;
				KSP[4][1][2][4]=1;
				KSP[4][2][0][0]=4;
				KSP[4][2][0][1]=3;
				KSP[4][2][0][2]=1;
				KSP[4][2][0][3]=2;
				KSP[4][2][1][0]=4;
				KSP[4][2][1][1]=5;
				KSP[4][2][1][2]=2;
				KSP[4][2][2][0]=4;
				KSP[4][2][2][1]=3;
				KSP[4][2][2][2]=1;
				KSP[4][2][2][3]=0;
				KSP[4][2][2][4]=2;
				KSP[4][3][0][0]=4;
				KSP[4][3][0][1]=3;
				KSP[4][3][1][0]=4;
				KSP[4][3][1][1]=5;
				KSP[4][3][1][2]=2;
				KSP[4][3][1][3]=1;
				KSP[4][3][1][4]=3;
				KSP[4][3][2][0]=4;
				KSP[4][3][2][1]=6;
				KSP[4][3][2][2]=7;
				KSP[4][3][2][3]=8;
				KSP[4][3][2][4]=11;
				KSP[4][3][2][5]=10;
				KSP[4][3][2][6]=3;
				KSP[4][4][0][0]=4;
				KSP[4][4][0][1]=4;
				KSP[4][5][0][0]=4;
				KSP[4][5][0][1]=5;
				KSP[4][5][1][0]=4;
				KSP[4][5][1][1]=3;
				KSP[4][5][1][2]=1;
				KSP[4][5][1][3]=2;
				KSP[4][5][1][4]=5;
				KSP[4][5][2][0]=4;
				KSP[4][5][2][1]=6;
				KSP[4][5][2][2]=7;
				KSP[4][5][2][3]=8;
				KSP[4][5][2][4]=9;
				KSP[4][5][2][5]=5;
				KSP[4][6][0][0]=4;
				KSP[4][6][0][1]=6;
				KSP[4][6][1][0]=4;
				KSP[4][6][1][1]=5;
				KSP[4][6][1][2]=9;
				KSP[4][6][1][3]=8;
				KSP[4][6][1][4]=7;
				KSP[4][6][1][5]=6;
				KSP[4][6][2][0]=4;
				KSP[4][6][2][1]=5;
				KSP[4][6][2][2]=12;
				KSP[4][6][2][3]=13;
				KSP[4][6][2][4]=8;
				KSP[4][6][2][5]=7;
				KSP[4][6][2][6]=6;
				KSP[4][7][0][0]=4;
				KSP[4][7][0][1]=6;
				KSP[4][7][0][2]=7;
				KSP[4][7][1][0]=4;
				KSP[4][7][1][1]=5;
				KSP[4][7][1][2]=9;
				KSP[4][7][1][3]=8;
				KSP[4][7][1][4]=7;
				KSP[4][7][2][0]=4;
				KSP[4][7][2][1]=5;
				KSP[4][7][2][2]=12;
				KSP[4][7][2][3]=13;
				KSP[4][7][2][4]=8;
				KSP[4][7][2][5]=7;
				KSP[4][8][0][0]=4;
				KSP[4][8][0][1]=6;
				KSP[4][8][0][2]=7;
				KSP[4][8][0][3]=8;
				KSP[4][8][1][0]=4;
				KSP[4][8][1][1]=5;
				KSP[4][8][1][2]=9;
				KSP[4][8][1][3]=8;
				KSP[4][8][2][0]=4;
				KSP[4][8][2][1]=5;
				KSP[4][8][2][2]=12;
				KSP[4][8][2][3]=11;
				KSP[4][8][2][4]=8;
				KSP[4][9][0][0]=4;
				KSP[4][9][0][1]=5;
				KSP[4][9][0][2]=9;
				KSP[4][9][1][0]=4;
				KSP[4][9][1][1]=6;
				KSP[4][9][1][2]=7;
				KSP[4][9][1][3]=8;
				KSP[4][9][1][4]=9;
				KSP[4][9][2][0]=4;
				KSP[4][9][2][1]=5;
				KSP[4][9][2][2]=12;
				KSP[4][9][2][3]=11;
				KSP[4][9][2][4]=8;
				KSP[4][9][2][5]=9;
				KSP[4][10][0][0]=4;
				KSP[4][10][0][1]=3;
				KSP[4][10][0][2]=10;
				KSP[4][10][1][0]=4;
				KSP[4][10][1][1]=6;
				KSP[4][10][1][2]=7;
				KSP[4][10][1][3]=8;
				KSP[4][10][1][4]=13;
				KSP[4][10][1][5]=10;
				KSP[4][10][2][0]=4;
				KSP[4][10][2][1]=6;
				KSP[4][10][2][2]=7;
				KSP[4][10][2][3]=8;
				KSP[4][10][2][4]=11;
				KSP[4][10][2][5]=10;
				KSP[4][11][0][0]=4;
				KSP[4][11][0][1]=6;
				KSP[4][11][0][2]=7;
				KSP[4][11][0][3]=8;
				KSP[4][11][0][4]=11;
				KSP[4][11][1][0]=4;
				KSP[4][11][1][1]=6;
				KSP[4][11][1][2]=7;
				KSP[4][11][1][3]=8;
				KSP[4][11][1][4]=13;
				KSP[4][11][1][5]=12;
				KSP[4][11][1][6]=11;
				KSP[4][11][2][0]=4;
				KSP[4][11][2][1]=5;
				KSP[4][11][2][2]=12;
				KSP[4][11][2][3]=11;
				KSP[4][12][0][0]=4;
				KSP[4][12][0][1]=6;
				KSP[4][12][0][2]=7;
				KSP[4][12][0][3]=8;
				KSP[4][12][0][4]=13;
				KSP[4][12][0][5]=12;
				KSP[4][12][1][0]=4;
				KSP[4][12][1][1]=6;
				KSP[4][12][1][2]=7;
				KSP[4][12][1][3]=8;
				KSP[4][12][1][4]=11;
				KSP[4][12][1][5]=12;
				KSP[4][12][2][0]=4;
				KSP[4][12][2][1]=5;
				KSP[4][12][2][2]=12;
				KSP[4][13][0][0]=4;
				KSP[4][13][0][1]=6;
				KSP[4][13][0][2]=7;
				KSP[4][13][0][3]=8;
				KSP[4][13][0][4]=13;
				KSP[4][13][1][0]=4;
				KSP[4][13][1][1]=6;
				KSP[4][13][1][2]=7;
				KSP[4][13][1][3]=8;
				KSP[4][13][1][4]=11;
				KSP[4][13][1][5]=12;
				KSP[4][13][1][6]=13;
				KSP[4][13][2][0]=4;
				KSP[4][13][2][1]=5;
				KSP[4][13][2][2]=12;
				KSP[4][13][2][3]=13;
				KSP[5][0][0][0]=5;
				KSP[5][0][0][1]=2;
				KSP[5][0][0][2]=0;
				KSP[5][0][1][0]=5;
				KSP[5][0][1][1]=2;
				KSP[5][0][1][2]=1;
				KSP[5][0][1][3]=0;
				KSP[5][0][2][0]=5;
				KSP[5][0][2][1]=4;
				KSP[5][0][2][2]=3;
				KSP[5][0][2][3]=1;
				KSP[5][0][2][4]=0;
				KSP[5][1][0][0]=5;
				KSP[5][1][0][1]=2;
				KSP[5][1][0][2]=1;
				KSP[5][1][1][0]=5;
				KSP[5][1][1][1]=4;
				KSP[5][1][1][2]=3;
				KSP[5][1][1][3]=1;
				KSP[5][1][2][0]=5;
				KSP[5][1][2][1]=2;
				KSP[5][1][2][2]=0;
				KSP[5][1][2][3]=1;
				KSP[5][2][0][0]=5;
				KSP[5][2][0][1]=2;
				KSP[5][2][1][0]=5;
				KSP[5][2][1][1]=4;
				KSP[5][2][1][2]=3;
				KSP[5][2][1][3]=1;
				KSP[5][2][1][4]=2;
				KSP[5][2][2][0]=5;
				KSP[5][2][2][1]=4;
				KSP[5][2][2][2]=3;
				KSP[5][2][2][3]=1;
				KSP[5][2][2][4]=0;
				KSP[5][2][2][5]=2;
				KSP[5][3][0][0]=5;
				KSP[5][3][0][1]=4;
				KSP[5][3][0][2]=3;
				KSP[5][3][1][0]=5;
				KSP[5][3][1][1]=2;
				KSP[5][3][1][2]=1;
				KSP[5][3][1][3]=3;
				KSP[5][3][2][0]=5;
				KSP[5][3][2][1]=9;
				KSP[5][3][2][2]=8;
				KSP[5][3][2][3]=7;
				KSP[5][3][2][4]=6;
				KSP[5][3][2][5]=4;
				KSP[5][3][2][6]=3;
				KSP[5][4][0][0]=5;
				KSP[5][4][0][1]=4;
				KSP[5][4][1][0]=5;
				KSP[5][4][1][1]=2;
				KSP[5][4][1][2]=1;
				KSP[5][4][1][3]=3;
				KSP[5][4][1][4]=4;
				KSP[5][4][2][0]=5;
				KSP[5][4][2][1]=9;
				KSP[5][4][2][2]=8;
				KSP[5][4][2][3]=7;
				KSP[5][4][2][4]=6;
				KSP[5][4][2][5]=4;
				KSP[5][5][0][0]=5;
				KSP[5][5][0][1]=5;
				KSP[5][6][0][0]=5;
				KSP[5][6][0][1]=4;
				KSP[5][6][0][2]=6;
				KSP[5][6][1][0]=5;
				KSP[5][6][1][1]=9;
				KSP[5][6][1][2]=8;
				KSP[5][6][1][3]=7;
				KSP[5][6][1][4]=6;
				KSP[5][6][2][0]=5;
				KSP[5][6][2][1]=12;
				KSP[5][6][2][2]=13;
				KSP[5][6][2][3]=8;
				KSP[5][6][2][4]=7;
				KSP[5][6][2][5]=6;
				KSP[5][7][0][0]=5;
				KSP[5][7][0][1]=4;
				KSP[5][7][0][2]=6;
				KSP[5][7][0][3]=7;
				KSP[5][7][1][0]=5;
				KSP[5][7][1][1]=9;
				KSP[5][7][1][2]=8;
				KSP[5][7][1][3]=7;
				KSP[5][7][2][0]=5;
				KSP[5][7][2][1]=12;
				KSP[5][7][2][2]=11;
				KSP[5][7][2][3]=8;
				KSP[5][7][2][4]=7;
				KSP[5][8][0][0]=5;
				KSP[5][8][0][1]=9;
				KSP[5][8][0][2]=8;
				KSP[5][8][1][0]=5;
				KSP[5][8][1][1]=12;
				KSP[5][8][1][2]=11;
				KSP[5][8][1][3]=8;
				KSP[5][8][2][0]=5;
				KSP[5][8][2][1]=12;
				KSP[5][8][2][2]=13;
				KSP[5][8][2][3]=8;
				KSP[5][9][0][0]=5;
				KSP[5][9][0][1]=9;
				KSP[5][9][1][0]=5;
				KSP[5][9][1][1]=12;
				KSP[5][9][1][2]=13;
				KSP[5][9][1][3]=8;
				KSP[5][9][1][4]=9;
				KSP[5][9][2][0]=5;
				KSP[5][9][2][1]=12;
				KSP[5][9][2][2]=11;
				KSP[5][9][2][3]=8;
				KSP[5][9][2][4]=9;
				KSP[5][10][0][0]=5;
				KSP[5][10][0][1]=12;
				KSP[5][10][0][2]=11;
				KSP[5][10][0][3]=10;
				KSP[5][10][1][0]=5;
				KSP[5][10][1][1]=12;
				KSP[5][10][1][2]=13;
				KSP[5][10][1][3]=10;
				KSP[5][10][2][0]=5;
				KSP[5][10][2][1]=9;
				KSP[5][10][2][2]=8;
				KSP[5][10][2][3]=13;
				KSP[5][10][2][4]=10;
				KSP[5][11][0][0]=5;
				KSP[5][11][0][1]=12;
				KSP[5][11][0][2]=11;
				KSP[5][11][1][0]=5;
				KSP[5][11][1][1]=9;
				KSP[5][11][1][2]=8;
				KSP[5][11][1][3]=11;
				KSP[5][11][2][0]=5;
				KSP[5][11][2][1]=9;
				KSP[5][11][2][2]=8;
				KSP[5][11][2][3]=13;
				KSP[5][11][2][4]=12;
				KSP[5][11][2][5]=11;
				KSP[5][12][0][0]=5;
				KSP[5][12][0][1]=12;
				KSP[5][12][1][0]=5;
				KSP[5][12][1][1]=9;
				KSP[5][12][1][2]=8;
				KSP[5][12][1][3]=11;
				KSP[5][12][1][4]=12;
				KSP[5][12][2][0]=5;
				KSP[5][12][2][1]=9;
				KSP[5][12][2][2]=8;
				KSP[5][12][2][3]=13;
				KSP[5][12][2][4]=12;
				KSP[5][13][0][0]=5;
				KSP[5][13][0][1]=12;
				KSP[5][13][0][2]=13;
				KSP[5][13][1][0]=5;
				KSP[5][13][1][1]=9;
				KSP[5][13][1][2]=8;
				KSP[5][13][1][3]=13;
				KSP[5][13][2][0]=5;
				KSP[5][13][2][1]=9;
				KSP[5][13][2][2]=8;
				KSP[5][13][2][3]=11;
				KSP[5][13][2][4]=12;
				KSP[5][13][2][5]=13;
				KSP[6][0][0][0]=6;
				KSP[6][0][0][1]=7;
				KSP[6][0][0][2]=0;
				KSP[6][0][1][0]=6;
				KSP[6][0][1][1]=4;
				KSP[6][0][1][2]=3;
				KSP[6][0][1][3]=1;
				KSP[6][0][1][4]=0;
				KSP[6][0][2][0]=6;
				KSP[6][0][2][1]=4;
				KSP[6][0][2][2]=3;
				KSP[6][0][2][3]=1;
				KSP[6][0][2][4]=2;
				KSP[6][0][2][5]=0;
				KSP[6][1][0][0]=6;
				KSP[6][1][0][1]=4;
				KSP[6][1][0][2]=3;
				KSP[6][1][0][3]=1;
				KSP[6][1][1][0]=6;
				KSP[6][1][1][1]=4;
				KSP[6][1][1][2]=5;
				KSP[6][1][1][3]=2;
				KSP[6][1][1][4]=1;
				KSP[6][1][2][0]=6;
				KSP[6][1][2][1]=7;
				KSP[6][1][2][2]=0;
				KSP[6][1][2][3]=1;
				KSP[6][2][0][0]=6;
				KSP[6][2][0][1]=4;
				KSP[6][2][0][2]=3;
				KSP[6][2][0][3]=1;
				KSP[6][2][0][4]=2;
				KSP[6][2][1][0]=6;
				KSP[6][2][1][1]=4;
				KSP[6][2][1][2]=5;
				KSP[6][2][1][3]=2;
				KSP[6][2][2][0]=6;
				KSP[6][2][2][1]=4;
				KSP[6][2][2][2]=3;
				KSP[6][2][2][3]=1;
				KSP[6][2][2][4]=0;
				KSP[6][2][2][5]=2;
				KSP[6][3][0][0]=6;
				KSP[6][3][0][1]=4;
				KSP[6][3][0][2]=3;
				KSP[6][3][1][0]=6;
				KSP[6][3][1][1]=7;
				KSP[6][3][1][2]=8;
				KSP[6][3][1][3]=13;
				KSP[6][3][1][4]=10;
				KSP[6][3][1][5]=3;
				KSP[6][3][2][0]=6;
				KSP[6][3][2][1]=7;
				KSP[6][3][2][2]=8;
				KSP[6][3][2][3]=11;
				KSP[6][3][2][4]=10;
				KSP[6][3][2][5]=3;
				KSP[6][4][0][0]=6;
				KSP[6][4][0][1]=4;
				KSP[6][4][1][0]=6;
				KSP[6][4][1][1]=7;
				KSP[6][4][1][2]=8;
				KSP[6][4][1][3]=9;
				KSP[6][4][1][4]=5;
				KSP[6][4][1][5]=4;
				KSP[6][4][2][0]=6;
				KSP[6][4][2][1]=7;
				KSP[6][4][2][2]=8;
				KSP[6][4][2][3]=11;
				KSP[6][4][2][4]=12;
				KSP[6][4][2][5]=5;
				KSP[6][4][2][6]=4;
				KSP[6][5][0][0]=6;
				KSP[6][5][0][1]=4;
				KSP[6][5][0][2]=5;
				KSP[6][5][1][0]=6;
				KSP[6][5][1][1]=7;
				KSP[6][5][1][2]=8;
				KSP[6][5][1][3]=9;
				KSP[6][5][1][4]=5;
				KSP[6][5][2][0]=6;
				KSP[6][5][2][1]=7;
				KSP[6][5][2][2]=8;
				KSP[6][5][2][3]=13;
				KSP[6][5][2][4]=12;
				KSP[6][5][2][5]=5;
				KSP[6][6][0][0]=6;
				KSP[6][6][0][1]=6;
				KSP[6][7][0][0]=6;
				KSP[6][7][0][1]=7;
				KSP[6][7][1][0]=6;
				KSP[6][7][1][1]=4;
				KSP[6][7][1][2]=5;
				KSP[6][7][1][3]=9;
				KSP[6][7][1][4]=8;
				KSP[6][7][1][5]=7;
				KSP[6][7][2][0]=6;
				KSP[6][7][2][1]=4;
				KSP[6][7][2][2]=5;
				KSP[6][7][2][3]=12;
				KSP[6][7][2][4]=11;
				KSP[6][7][2][5]=8;
				KSP[6][7][2][6]=7;
				KSP[6][8][0][0]=6;
				KSP[6][8][0][1]=7;
				KSP[6][8][0][2]=8;
				KSP[6][8][1][0]=6;
				KSP[6][8][1][1]=4;
				KSP[6][8][1][2]=5;
				KSP[6][8][1][3]=9;
				KSP[6][8][1][4]=8;
				KSP[6][8][2][0]=6;
				KSP[6][8][2][1]=4;
				KSP[6][8][2][2]=5;
				KSP[6][8][2][3]=12;
				KSP[6][8][2][4]=13;
				KSP[6][8][2][5]=8;
				KSP[6][9][0][0]=6;
				KSP[6][9][0][1]=7;
				KSP[6][9][0][2]=8;
				KSP[6][9][0][3]=9;
				KSP[6][9][1][0]=6;
				KSP[6][9][1][1]=4;
				KSP[6][9][1][2]=5;
				KSP[6][9][1][3]=9;
				KSP[6][9][2][0]=6;
				KSP[6][9][2][1]=7;
				KSP[6][9][2][2]=8;
				KSP[6][9][2][3]=11;
				KSP[6][9][2][4]=12;
				KSP[6][9][2][5]=5;
				KSP[6][9][2][6]=9;
				KSP[6][10][0][0]=6;
				KSP[6][10][0][1]=7;
				KSP[6][10][0][2]=8;
				KSP[6][10][0][3]=11;
				KSP[6][10][0][4]=10;
				KSP[6][10][1][0]=6;
				KSP[6][10][1][1]=7;
				KSP[6][10][1][2]=8;
				KSP[6][10][1][3]=13;
				KSP[6][10][1][4]=10;
				KSP[6][10][2][0]=6;
				KSP[6][10][2][1]=7;
				KSP[6][10][2][2]=8;
				KSP[6][10][2][3]=11;
				KSP[6][10][2][4]=12;
				KSP[6][10][2][5]=13;
				KSP[6][10][2][6]=10;
				KSP[6][11][0][0]=6;
				KSP[6][11][0][1]=7;
				KSP[6][11][0][2]=8;
				KSP[6][11][0][3]=11;
				KSP[6][11][1][0]=6;
				KSP[6][11][1][1]=7;
				KSP[6][11][1][2]=8;
				KSP[6][11][1][3]=13;
				KSP[6][11][1][4]=12;
				KSP[6][11][1][5]=11;
				KSP[6][11][2][0]=6;
				KSP[6][11][2][1]=7;
				KSP[6][11][2][2]=8;
				KSP[6][11][2][3]=13;
				KSP[6][11][2][4]=10;
				KSP[6][11][2][5]=11;
				KSP[6][12][0][0]=6;
				KSP[6][12][0][1]=7;
				KSP[6][12][0][2]=8;
				KSP[6][12][0][3]=13;
				KSP[6][12][0][4]=12;
				KSP[6][12][1][0]=6;
				KSP[6][12][1][1]=7;
				KSP[6][12][1][2]=8;
				KSP[6][12][1][3]=11;
				KSP[6][12][1][4]=12;
				KSP[6][12][2][0]=6;
				KSP[6][12][2][1]=7;
				KSP[6][12][2][2]=8;
				KSP[6][12][2][3]=13;
				KSP[6][12][2][4]=10;
				KSP[6][12][2][5]=11;
				KSP[6][12][2][6]=12;
				KSP[6][13][0][0]=6;
				KSP[6][13][0][1]=7;
				KSP[6][13][0][2]=8;
				KSP[6][13][0][3]=13;
				KSP[6][13][1][0]=6;
				KSP[6][13][1][1]=7;
				KSP[6][13][1][2]=8;
				KSP[6][13][1][3]=11;
				KSP[6][13][1][4]=12;
				KSP[6][13][1][5]=13;
				KSP[6][13][2][0]=6;
				KSP[6][13][2][1]=7;
				KSP[6][13][2][2]=8;
				KSP[6][13][2][3]=11;
				KSP[6][13][2][4]=10;
				KSP[6][13][2][5]=13;
				KSP[7][0][0][0]=7;
				KSP[7][0][0][1]=0;
				KSP[7][0][1][0]=7;
				KSP[7][0][1][1]=6;
				KSP[7][0][1][2]=4;
				KSP[7][0][1][3]=3;
				KSP[7][0][1][4]=1;
				KSP[7][0][1][5]=0;
				KSP[7][0][2][0]=7;
				KSP[7][0][2][1]=6;
				KSP[7][0][2][2]=4;
				KSP[7][0][2][3]=3;
				KSP[7][0][2][4]=1;
				KSP[7][0][2][5]=2;
				KSP[7][0][2][6]=0;
				KSP[7][1][0][0]=7;
				KSP[7][1][0][1]=6;
				KSP[7][1][0][2]=4;
				KSP[7][1][0][3]=3;
				KSP[7][1][0][4]=1;
				KSP[7][1][1][0]=7;
				KSP[7][1][1][1]=0;
				KSP[7][1][1][2]=1;
				KSP[7][1][2][0]=7;
				KSP[7][1][2][1]=0;
				KSP[7][1][2][2]=2;
				KSP[7][1][2][3]=1;
				KSP[7][2][0][0]=7;
				KSP[7][2][0][1]=6;
				KSP[7][2][0][2]=4;
				KSP[7][2][0][3]=3;
				KSP[7][2][0][4]=1;
				KSP[7][2][0][5]=2;
				KSP[7][2][1][0]=7;
				KSP[7][2][1][1]=0;
				KSP[7][2][1][2]=2;
				KSP[7][2][2][0]=7;
				KSP[7][2][2][1]=0;
				KSP[7][2][2][2]=1;
				KSP[7][2][2][3]=2;
				KSP[7][3][0][0]=7;
				KSP[7][3][0][1]=6;
				KSP[7][3][0][2]=4;
				KSP[7][3][0][3]=3;
				KSP[7][3][1][0]=7;
				KSP[7][3][1][1]=8;
				KSP[7][3][1][2]=11;
				KSP[7][3][1][3]=10;
				KSP[7][3][1][4]=3;
				KSP[7][3][2][0]=7;
				KSP[7][3][2][1]=8;
				KSP[7][3][2][2]=13;
				KSP[7][3][2][3]=10;
				KSP[7][3][2][4]=3;
				KSP[7][4][0][0]=7;
				KSP[7][4][0][1]=6;
				KSP[7][4][0][2]=4;
				KSP[7][4][1][0]=7;
				KSP[7][4][1][1]=8;
				KSP[7][4][1][2]=9;
				KSP[7][4][1][3]=5;
				KSP[7][4][1][4]=4;
				KSP[7][4][2][0]=7;
				KSP[7][4][2][1]=8;
				KSP[7][4][2][2]=13;
				KSP[7][4][2][3]=12;
				KSP[7][4][2][4]=5;
				KSP[7][4][2][5]=4;
				KSP[7][5][0][0]=7;
				KSP[7][5][0][1]=6;
				KSP[7][5][0][2]=4;
				KSP[7][5][0][3]=5;
				KSP[7][5][1][0]=7;
				KSP[7][5][1][1]=8;
				KSP[7][5][1][2]=9;
				KSP[7][5][1][3]=5;
				KSP[7][5][2][0]=7;
				KSP[7][5][2][1]=8;
				KSP[7][5][2][2]=11;
				KSP[7][5][2][3]=12;
				KSP[7][5][2][4]=5;
				KSP[7][6][0][0]=7;
				KSP[7][6][0][1]=6;
				KSP[7][6][1][0]=7;
				KSP[7][6][1][1]=8;
				KSP[7][6][1][2]=9;
				KSP[7][6][1][3]=5;
				KSP[7][6][1][4]=4;
				KSP[7][6][1][5]=6;
				KSP[7][6][2][0]=7;
				KSP[7][6][2][1]=8;
				KSP[7][6][2][2]=13;
				KSP[7][6][2][3]=12;
				KSP[7][6][2][4]=5;
				KSP[7][6][2][5]=4;
				KSP[7][6][2][6]=6;
				KSP[7][7][0][0]=7;
				KSP[7][7][0][1]=7;
				KSP[7][8][0][0]=7;
				KSP[7][8][0][1]=8;
				KSP[7][8][1][0]=7;
				KSP[7][8][1][1]=6;
				KSP[7][8][1][2]=4;
				KSP[7][8][1][3]=5;
				KSP[7][8][1][4]=9;
				KSP[7][8][1][5]=8;
				KSP[7][8][2][0]=7;
				KSP[7][8][2][1]=6;
				KSP[7][8][2][2]=4;
				KSP[7][8][2][3]=5;
				KSP[7][8][2][4]=12;
				KSP[7][8][2][5]=11;
				KSP[7][8][2][6]=8;
				KSP[7][9][0][0]=7;
				KSP[7][9][0][1]=8;
				KSP[7][9][0][2]=9;
				KSP[7][9][1][0]=7;
				KSP[7][9][1][1]=6;
				KSP[7][9][1][2]=4;
				KSP[7][9][1][3]=5;
				KSP[7][9][1][4]=9;
				KSP[7][9][2][0]=7;
				KSP[7][9][2][1]=8;
				KSP[7][9][2][2]=11;
				KSP[7][9][2][3]=12;
				KSP[7][9][2][4]=5;
				KSP[7][9][2][5]=9;
				KSP[7][10][0][0]=7;
				KSP[7][10][0][1]=8;
				KSP[7][10][0][2]=11;
				KSP[7][10][0][3]=10;
				KSP[7][10][1][0]=7;
				KSP[7][10][1][1]=8;
				KSP[7][10][1][2]=13;
				KSP[7][10][1][3]=10;
				KSP[7][10][2][0]=7;
				KSP[7][10][2][1]=8;
				KSP[7][10][2][2]=11;
				KSP[7][10][2][3]=12;
				KSP[7][10][2][4]=13;
				KSP[7][10][2][5]=10;
				KSP[7][11][0][0]=7;
				KSP[7][11][0][1]=8;
				KSP[7][11][0][2]=11;
				KSP[7][11][1][0]=7;
				KSP[7][11][1][1]=8;
				KSP[7][11][1][2]=13;
				KSP[7][11][1][3]=12;
				KSP[7][11][1][4]=11;
				KSP[7][11][2][0]=7;
				KSP[7][11][2][1]=8;
				KSP[7][11][2][2]=13;
				KSP[7][11][2][3]=10;
				KSP[7][11][2][4]=11;
				KSP[7][12][0][0]=7;
				KSP[7][12][0][1]=8;
				KSP[7][12][0][2]=11;
				KSP[7][12][0][3]=12;
				KSP[7][12][1][0]=7;
				KSP[7][12][1][1]=8;
				KSP[7][12][1][2]=13;
				KSP[7][12][1][3]=12;
				KSP[7][12][2][0]=7;
				KSP[7][12][2][1]=8;
				KSP[7][12][2][2]=11;
				KSP[7][12][2][3]=10;
				KSP[7][12][2][4]=13;
				KSP[7][12][2][5]=12;
				KSP[7][13][0][0]=7;
				KSP[7][13][0][1]=8;
				KSP[7][13][0][2]=13;
				KSP[7][13][1][0]=7;
				KSP[7][13][1][1]=8;
				KSP[7][13][1][2]=11;
				KSP[7][13][1][3]=12;
				KSP[7][13][1][4]=13;
				KSP[7][13][2][0]=7;
				KSP[7][13][2][1]=8;
				KSP[7][13][2][2]=11;
				KSP[7][13][2][3]=10;
				KSP[7][13][2][4]=13;
				KSP[8][0][0][0]=8;
				KSP[8][0][0][1]=7;
				KSP[8][0][0][2]=0;
				KSP[8][0][1][0]=8;
				KSP[8][0][1][1]=7;
				KSP[8][0][1][2]=6;
				KSP[8][0][1][3]=4;
				KSP[8][0][1][4]=3;
				KSP[8][0][1][5]=1;
				KSP[8][0][1][6]=0;
				KSP[8][0][2][0]=8;
				KSP[8][0][2][1]=9;
				KSP[8][0][2][2]=5;
				KSP[8][0][2][3]=2;
				KSP[8][0][2][4]=0;
				KSP[8][1][0][0]=8;
				KSP[8][1][0][1]=7;
				KSP[8][1][0][2]=6;
				KSP[8][1][0][3]=4;
				KSP[8][1][0][4]=3;
				KSP[8][1][0][5]=1;
				KSP[8][1][1][0]=8;
				KSP[8][1][1][1]=7;
				KSP[8][1][1][2]=0;
				KSP[8][1][1][3]=1;
				KSP[8][1][2][0]=8;
				KSP[8][1][2][1]=11;
				KSP[8][1][2][2]=10;
				KSP[8][1][2][3]=3;
				KSP[8][1][2][4]=1;
				KSP[8][2][0][0]=8;
				KSP[8][2][0][1]=9;
				KSP[8][2][0][2]=5;
				KSP[8][2][0][3]=2;
				KSP[8][2][1][0]=8;
				KSP[8][2][1][1]=7;
				KSP[8][2][1][2]=6;
				KSP[8][2][1][3]=4;
				KSP[8][2][1][4]=3;
				KSP[8][2][1][5]=1;
				KSP[8][2][1][6]=2;
				KSP[8][2][2][0]=8;
				KSP[8][2][2][1]=13;
				KSP[8][2][2][2]=12;
				KSP[8][2][2][3]=5;
				KSP[8][2][2][4]=2;
				KSP[8][3][0][0]=8;
				KSP[8][3][0][1]=7;
				KSP[8][3][0][2]=6;
				KSP[8][3][0][3]=4;
				KSP[8][3][0][4]=3;
				KSP[8][3][1][0]=8;
				KSP[8][3][1][1]=11;
				KSP[8][3][1][2]=10;
				KSP[8][3][1][3]=3;
				KSP[8][3][2][0]=8;
				KSP[8][3][2][1]=13;
				KSP[8][3][2][2]=10;
				KSP[8][3][2][3]=3;
				KSP[8][4][0][0]=8;
				KSP[8][4][0][1]=7;
				KSP[8][4][0][2]=6;
				KSP[8][4][0][3]=4;
				KSP[8][4][1][0]=8;
				KSP[8][4][1][1]=9;
				KSP[8][4][1][2]=5;
				KSP[8][4][1][3]=4;
				KSP[8][4][2][0]=8;
				KSP[8][4][2][1]=11;
				KSP[8][4][2][2]=12;
				KSP[8][4][2][3]=5;
				KSP[8][4][2][4]=4;
				KSP[8][5][0][0]=8;
				KSP[8][5][0][1]=9;
				KSP[8][5][0][2]=5;
				KSP[8][5][1][0]=8;
				KSP[8][5][1][1]=11;
				KSP[8][5][1][2]=12;
				KSP[8][5][1][3]=5;
				KSP[8][5][2][0]=8;
				KSP[8][5][2][1]=13;
				KSP[8][5][2][2]=12;
				KSP[8][5][2][3]=5;
				KSP[8][6][0][0]=8;
				KSP[8][6][0][1]=7;
				KSP[8][6][0][2]=6;
				KSP[8][6][1][0]=8;
				KSP[8][6][1][1]=9;
				KSP[8][6][1][2]=5;
				KSP[8][6][1][3]=4;
				KSP[8][6][1][4]=6;
				KSP[8][6][2][0]=8;
				KSP[8][6][2][1]=11;
				KSP[8][6][2][2]=12;
				KSP[8][6][2][3]=5;
				KSP[8][6][2][4]=4;
				KSP[8][6][2][5]=6;
				KSP[8][7][0][0]=8;
				KSP[8][7][0][1]=7;
				KSP[8][7][1][0]=8;
				KSP[8][7][1][1]=9;
				KSP[8][7][1][2]=5;
				KSP[8][7][1][3]=4;
				KSP[8][7][1][4]=6;
				KSP[8][7][1][5]=7;
				KSP[8][7][2][0]=8;
				KSP[8][7][2][1]=11;
				KSP[8][7][2][2]=12;
				KSP[8][7][2][3]=5;
				KSP[8][7][2][4]=4;
				KSP[8][7][2][5]=6;
				KSP[8][7][2][6]=7;
				KSP[8][8][0][0]=8;
				KSP[8][8][0][1]=8;
				KSP[8][9][0][0]=8;
				KSP[8][9][0][1]=9;
				KSP[8][9][1][0]=8;
				KSP[8][9][1][1]=11;
				KSP[8][9][1][2]=12;
				KSP[8][9][1][3]=5;
				KSP[8][9][1][4]=9;
				KSP[8][9][2][0]=8;
				KSP[8][9][2][1]=13;
				KSP[8][9][2][2]=12;
				KSP[8][9][2][3]=5;
				KSP[8][9][2][4]=9;
				KSP[8][10][0][0]=8;
				KSP[8][10][0][1]=11;
				KSP[8][10][0][2]=10;
				KSP[8][10][1][0]=8;
				KSP[8][10][1][1]=13;
				KSP[8][10][1][2]=10;
				KSP[8][10][2][0]=8;
				KSP[8][10][2][1]=11;
				KSP[8][10][2][2]=12;
				KSP[8][10][2][3]=13;
				KSP[8][10][2][4]=10;
				KSP[8][11][0][0]=8;
				KSP[8][11][0][1]=11;
				KSP[8][11][1][0]=8;
				KSP[8][11][1][1]=13;
				KSP[8][11][1][2]=12;
				KSP[8][11][1][3]=11;
				KSP[8][11][2][0]=8;
				KSP[8][11][2][1]=13;
				KSP[8][11][2][2]=10;
				KSP[8][11][2][3]=11;
				KSP[8][12][0][0]=8;
				KSP[8][12][0][1]=11;
				KSP[8][12][0][2]=12;
				KSP[8][12][1][0]=8;
				KSP[8][12][1][1]=13;
				KSP[8][12][1][2]=12;
				KSP[8][12][2][0]=8;
				KSP[8][12][2][1]=11;
				KSP[8][12][2][2]=10;
				KSP[8][12][2][3]=13;
				KSP[8][12][2][4]=12;
				KSP[8][13][0][0]=8;
				KSP[8][13][0][1]=13;
				KSP[8][13][1][0]=8;
				KSP[8][13][1][1]=11;
				KSP[8][13][1][2]=12;
				KSP[8][13][1][3]=13;
				KSP[8][13][2][0]=8;
				KSP[8][13][2][1]=11;
				KSP[8][13][2][2]=10;
				KSP[8][13][2][3]=13;
				KSP[9][0][0][0]=9;
				KSP[9][0][0][1]=8;
				KSP[9][0][0][2]=7;
				KSP[9][0][0][3]=0;
				KSP[9][0][1][0]=9;
				KSP[9][0][1][1]=5;
				KSP[9][0][1][2]=2;
				KSP[9][0][1][3]=0;
				KSP[9][0][2][0]=9;
				KSP[9][0][2][1]=5;
				KSP[9][0][2][2]=2;
				KSP[9][0][2][3]=1;
				KSP[9][0][2][4]=0;
				KSP[9][1][0][0]=9;
				KSP[9][1][0][1]=5;
				KSP[9][1][0][2]=2;
				KSP[9][1][0][3]=1;
				KSP[9][1][1][0]=9;
				KSP[9][1][1][1]=5;
				KSP[9][1][1][2]=4;
				KSP[9][1][1][3]=3;
				KSP[9][1][1][4]=1;
				KSP[9][1][2][0]=9;
				KSP[9][1][2][1]=8;
				KSP[9][1][2][2]=7;
				KSP[9][1][2][3]=6;
				KSP[9][1][2][4]=4;
				KSP[9][1][2][5]=3;
				KSP[9][1][2][6]=1;
				KSP[9][2][0][0]=9;
				KSP[9][2][0][1]=5;
				KSP[9][2][0][2]=2;
				KSP[9][2][1][0]=9;
				KSP[9][2][1][1]=5;
				KSP[9][2][1][2]=4;
				KSP[9][2][1][3]=3;
				KSP[9][2][1][4]=1;
				KSP[9][2][1][5]=2;
				KSP[9][2][2][0]=9;
				KSP[9][2][2][1]=8;
				KSP[9][2][2][2]=7;
				KSP[9][2][2][3]=6;
				KSP[9][2][2][4]=4;
				KSP[9][2][2][5]=3;
				KSP[9][2][2][6]=1;
				KSP[9][2][2][7]=2;
				KSP[9][3][0][0]=9;
				KSP[9][3][0][1]=5;
				KSP[9][3][0][2]=4;
				KSP[9][3][0][3]=3;
				KSP[9][3][1][0]=9;
				KSP[9][3][1][1]=8;
				KSP[9][3][1][2]=7;
				KSP[9][3][1][3]=6;
				KSP[9][3][1][4]=4;
				KSP[9][3][1][5]=3;
				KSP[9][3][2][0]=9;
				KSP[9][3][2][1]=8;
				KSP[9][3][2][2]=13;
				KSP[9][3][2][3]=10;
				KSP[9][3][2][4]=3;
				KSP[9][4][0][0]=9;
				KSP[9][4][0][1]=5;
				KSP[9][4][0][2]=4;
				KSP[9][4][1][0]=9;
				KSP[9][4][1][1]=8;
				KSP[9][4][1][2]=7;
				KSP[9][4][1][3]=6;
				KSP[9][4][1][4]=4;
				KSP[9][4][2][0]=9;
				KSP[9][4][2][1]=8;
				KSP[9][4][2][2]=13;
				KSP[9][4][2][3]=12;
				KSP[9][4][2][4]=5;
				KSP[9][4][2][5]=4;
				KSP[9][5][0][0]=9;
				KSP[9][5][0][1]=5;
				KSP[9][5][1][0]=9;
				KSP[9][5][1][1]=8;
				KSP[9][5][1][2]=11;
				KSP[9][5][1][3]=12;
				KSP[9][5][1][4]=5;
				KSP[9][5][2][0]=9;
				KSP[9][5][2][1]=8;
				KSP[9][5][2][2]=13;
				KSP[9][5][2][3]=12;
				KSP[9][5][2][4]=5;
				KSP[9][6][0][0]=9;
				KSP[9][6][0][1]=8;
				KSP[9][6][0][2]=7;
				KSP[9][6][0][3]=6;
				KSP[9][6][1][0]=9;
				KSP[9][6][1][1]=5;
				KSP[9][6][1][2]=4;
				KSP[9][6][1][3]=6;
				KSP[9][6][2][0]=9;
				KSP[9][6][2][1]=5;
				KSP[9][6][2][2]=12;
				KSP[9][6][2][3]=11;
				KSP[9][6][2][4]=8;
				KSP[9][6][2][5]=7;
				KSP[9][6][2][6]=6;
				KSP[9][7][0][0]=9;
				KSP[9][7][0][1]=8;
				KSP[9][7][0][2]=7;
				KSP[9][7][1][0]=9;
				KSP[9][7][1][1]=5;
				KSP[9][7][1][2]=4;
				KSP[9][7][1][3]=6;
				KSP[9][7][1][4]=7;
				KSP[9][7][2][0]=9;
				KSP[9][7][2][1]=5;
				KSP[9][7][2][2]=12;
				KSP[9][7][2][3]=13;
				KSP[9][7][2][4]=8;
				KSP[9][7][2][5]=7;
				KSP[9][8][0][0]=9;
				KSP[9][8][0][1]=8;
				KSP[9][8][1][0]=9;
				KSP[9][8][1][1]=5;
				KSP[9][8][1][2]=12;
				KSP[9][8][1][3]=11;
				KSP[9][8][1][4]=8;
				KSP[9][8][2][0]=9;
				KSP[9][8][2][1]=5;
				KSP[9][8][2][2]=12;
				KSP[9][8][2][3]=13;
				KSP[9][8][2][4]=8;
				KSP[9][9][0][0]=9;
				KSP[9][9][0][1]=9;
				KSP[9][10][0][0]=9;
				KSP[9][10][0][1]=8;
				KSP[9][10][0][2]=13;
				KSP[9][10][0][3]=10;
				KSP[9][10][1][0]=9;
				KSP[9][10][1][1]=8;
				KSP[9][10][1][2]=11;
				KSP[9][10][1][3]=10;
				KSP[9][10][2][0]=9;
				KSP[9][10][2][1]=8;
				KSP[9][10][2][2]=13;
				KSP[9][10][2][3]=12;
				KSP[9][10][2][4]=11;
				KSP[9][10][2][5]=10;
				KSP[9][11][0][0]=9;
				KSP[9][11][0][1]=8;
				KSP[9][11][0][2]=11;
				KSP[9][11][1][0]=9;
				KSP[9][11][1][1]=8;
				KSP[9][11][1][2]=13;
				KSP[9][11][1][3]=12;
				KSP[9][11][1][4]=11;
				KSP[9][11][2][0]=9;
				KSP[9][11][2][1]=8;
				KSP[9][11][2][2]=13;
				KSP[9][11][2][3]=10;
				KSP[9][11][2][4]=11;
				KSP[9][12][0][0]=9;
				KSP[9][12][0][1]=8;
				KSP[9][12][0][2]=11;
				KSP[9][12][0][3]=12;
				KSP[9][12][1][0]=9;
				KSP[9][12][1][1]=8;
				KSP[9][12][1][2]=13;
				KSP[9][12][1][3]=12;
				KSP[9][12][2][0]=9;
				KSP[9][12][2][1]=5;
				KSP[9][12][2][2]=12;
				KSP[9][13][0][0]=9;
				KSP[9][13][0][1]=8;
				KSP[9][13][0][2]=13;
				KSP[9][13][1][0]=9;
				KSP[9][13][1][1]=8;
				KSP[9][13][1][2]=11;
				KSP[9][13][1][3]=12;
				KSP[9][13][1][4]=13;
				KSP[9][13][2][0]=9;
				KSP[9][13][2][1]=8;
				KSP[9][13][2][2]=11;
				KSP[9][13][2][3]=10;
				KSP[9][13][2][4]=13;
				KSP[10][0][0][0]=10;
				KSP[10][0][0][1]=3;
				KSP[10][0][0][2]=1;
				KSP[10][0][0][3]=0;
				KSP[10][0][1][0]=10;
				KSP[10][0][1][1]=11;
				KSP[10][0][1][2]=8;
				KSP[10][0][1][3]=7;
				KSP[10][0][1][4]=0;
				KSP[10][0][2][0]=10;
				KSP[10][0][2][1]=13;
				KSP[10][0][2][2]=8;
				KSP[10][0][2][3]=7;
				KSP[10][0][2][4]=0;
				KSP[10][1][0][0]=10;
				KSP[10][1][0][1]=3;
				KSP[10][1][0][2]=1;
				KSP[10][1][1][0]=10;
				KSP[10][1][1][1]=11;
				KSP[10][1][1][2]=8;
				KSP[10][1][1][3]=7;
				KSP[10][1][1][4]=6;
				KSP[10][1][1][5]=4;
				KSP[10][1][1][6]=3;
				KSP[10][1][1][7]=1;
				KSP[10][1][2][0]=10;
				KSP[10][1][2][1]=13;
				KSP[10][1][2][2]=8;
				KSP[10][1][2][3]=7;
				KSP[10][1][2][4]=6;
				KSP[10][1][2][5]=4;
				KSP[10][1][2][6]=3;
				KSP[10][1][2][7]=1;
				KSP[10][2][0][0]=10;
				KSP[10][2][0][1]=3;
				KSP[10][2][0][2]=1;
				KSP[10][2][0][3]=2;
				KSP[10][2][1][0]=10;
				KSP[10][2][1][1]=11;
				KSP[10][2][1][2]=12;
				KSP[10][2][1][3]=5;
				KSP[10][2][1][4]=2;
				KSP[10][2][2][0]=10;
				KSP[10][2][2][1]=13;
				KSP[10][2][2][2]=12;
				KSP[10][2][2][3]=5;
				KSP[10][2][2][4]=2;
				KSP[10][3][0][0]=10;
				KSP[10][3][0][1]=3;
				KSP[10][3][1][0]=10;
				KSP[10][3][1][1]=13;
				KSP[10][3][1][2]=8;
				KSP[10][3][1][3]=7;
				KSP[10][3][1][4]=6;
				KSP[10][3][1][5]=4;
				KSP[10][3][1][6]=3;
				KSP[10][3][2][0]=10;
				KSP[10][3][2][1]=11;
				KSP[10][3][2][2]=8;
				KSP[10][3][2][3]=7;
				KSP[10][3][2][4]=6;
				KSP[10][3][2][5]=4;
				KSP[10][3][2][6]=3;
				KSP[10][4][0][0]=10;
				KSP[10][4][0][1]=3;
				KSP[10][4][0][2]=4;
				KSP[10][4][1][0]=10;
				KSP[10][4][1][1]=13;
				KSP[10][4][1][2]=8;
				KSP[10][4][1][3]=7;
				KSP[10][4][1][4]=6;
				KSP[10][4][1][5]=4;
				KSP[10][4][2][0]=10;
				KSP[10][4][2][1]=11;
				KSP[10][4][2][2]=8;
				KSP[10][4][2][3]=7;
				KSP[10][4][2][4]=6;
				KSP[10][4][2][5]=4;
				KSP[10][5][0][0]=10;
				KSP[10][5][0][1]=13;
				KSP[10][5][0][2]=12;
				KSP[10][5][0][3]=5;
				KSP[10][5][1][0]=10;
				KSP[10][5][1][1]=11;
				KSP[10][5][1][2]=12;
				KSP[10][5][1][3]=5;
				KSP[10][5][2][0]=10;
				KSP[10][5][2][1]=13;
				KSP[10][5][2][2]=8;
				KSP[10][5][2][3]=9;
				KSP[10][5][2][4]=5;
				KSP[10][6][0][0]=10;
				KSP[10][6][0][1]=13;
				KSP[10][6][0][2]=8;
				KSP[10][6][0][3]=7;
				KSP[10][6][0][4]=6;
				KSP[10][6][1][0]=10;
				KSP[10][6][1][1]=11;
				KSP[10][6][1][2]=8;
				KSP[10][6][1][3]=7;
				KSP[10][6][1][4]=6;
				KSP[10][6][2][0]=10;
				KSP[10][6][2][1]=13;
				KSP[10][6][2][2]=12;
				KSP[10][6][2][3]=11;
				KSP[10][6][2][4]=8;
				KSP[10][6][2][5]=7;
				KSP[10][6][2][6]=6;
				KSP[10][7][0][0]=10;
				KSP[10][7][0][1]=13;
				KSP[10][7][0][2]=8;
				KSP[10][7][0][3]=7;
				KSP[10][7][1][0]=10;
				KSP[10][7][1][1]=11;
				KSP[10][7][1][2]=8;
				KSP[10][7][1][3]=7;
				KSP[10][7][2][0]=10;
				KSP[10][7][2][1]=13;
				KSP[10][7][2][2]=12;
				KSP[10][7][2][3]=11;
				KSP[10][7][2][4]=8;
				KSP[10][7][2][5]=7;
				KSP[10][8][0][0]=10;
				KSP[10][8][0][1]=11;
				KSP[10][8][0][2]=8;
				KSP[10][8][1][0]=10;
				KSP[10][8][1][1]=13;
				KSP[10][8][1][2]=8;
				KSP[10][8][2][0]=10;
				KSP[10][8][2][1]=11;
				KSP[10][8][2][2]=12;
				KSP[10][8][2][3]=13;
				KSP[10][8][2][4]=8;
				KSP[10][9][0][0]=10;
				KSP[10][9][0][1]=11;
				KSP[10][9][0][2]=8;
				KSP[10][9][0][3]=9;
				KSP[10][9][1][0]=10;
				KSP[10][9][1][1]=13;
				KSP[10][9][1][2]=8;
				KSP[10][9][1][3]=9;
				KSP[10][9][2][0]=10;
				KSP[10][9][2][1]=11;
				KSP[10][9][2][2]=12;
				KSP[10][9][2][3]=13;
				KSP[10][9][2][4]=8;
				KSP[10][9][2][5]=9;
				KSP[10][10][0][0]=10;
				KSP[10][10][0][1]=10;
				KSP[10][11][0][0]=10;
				KSP[10][11][0][1]=11;
				KSP[10][11][1][0]=10;
				KSP[10][11][1][1]=13;
				KSP[10][11][1][2]=12;
				KSP[10][11][1][3]=11;
				KSP[10][11][2][0]=10;
				KSP[10][11][2][1]=13;
				KSP[10][11][2][2]=8;
				KSP[10][11][2][3]=11;
				KSP[10][12][0][0]=10;
				KSP[10][12][0][1]=11;
				KSP[10][12][0][2]=12;
				KSP[10][12][1][0]=10;
				KSP[10][12][1][1]=13;
				KSP[10][12][1][2]=12;
				KSP[10][12][2][0]=10;
				KSP[10][12][2][1]=11;
				KSP[10][12][2][2]=8;
				KSP[10][12][2][3]=13;
				KSP[10][12][2][4]=12;
				KSP[10][13][0][0]=10;
				KSP[10][13][0][1]=13;
				KSP[10][13][1][0]=10;
				KSP[10][13][1][1]=11;
				KSP[10][13][1][2]=12;
				KSP[10][13][1][3]=13;
				KSP[10][13][2][0]=10;
				KSP[10][13][2][1]=11;
				KSP[10][13][2][2]=8;
				KSP[10][13][2][3]=13;
				KSP[11][0][0][0]=11;
				KSP[11][0][0][1]=8;
				KSP[11][0][0][2]=7;
				KSP[11][0][0][3]=0;
				KSP[11][0][1][0]=11;
				KSP[11][0][1][1]=12;
				KSP[11][0][1][2]=13;
				KSP[11][0][1][3]=8;
				KSP[11][0][1][4]=7;
				KSP[11][0][1][5]=0;
				KSP[11][0][2][0]=11;
				KSP[11][0][2][1]=10;
				KSP[11][0][2][2]=3;
				KSP[11][0][2][3]=1;
				KSP[11][0][2][4]=0;
				KSP[11][1][0][0]=11;
				KSP[11][1][0][1]=10;
				KSP[11][1][0][2]=3;
				KSP[11][1][0][3]=1;
				KSP[11][1][1][0]=11;
				KSP[11][1][1][1]=8;
				KSP[11][1][1][2]=7;
				KSP[11][1][1][3]=6;
				KSP[11][1][1][4]=4;
				KSP[11][1][1][5]=3;
				KSP[11][1][1][6]=1;
				KSP[11][1][2][0]=11;
				KSP[11][1][2][1]=12;
				KSP[11][1][2][2]=13;
				KSP[11][1][2][3]=10;
				KSP[11][1][2][4]=3;
				KSP[11][1][2][5]=1;
				KSP[11][2][0][0]=11;
				KSP[11][2][0][1]=12;
				KSP[11][2][0][2]=5;
				KSP[11][2][0][3]=2;
				KSP[11][2][1][0]=11;
				KSP[11][2][1][1]=8;
				KSP[11][2][1][2]=9;
				KSP[11][2][1][3]=5;
				KSP[11][2][1][4]=2;
				KSP[11][2][2][0]=11;
				KSP[11][2][2][1]=10;
				KSP[11][2][2][2]=3;
				KSP[11][2][2][3]=1;
				KSP[11][2][2][4]=2;
				KSP[11][3][0][0]=11;
				KSP[11][3][0][1]=10;
				KSP[11][3][0][2]=3;
				KSP[11][3][1][0]=11;
				KSP[11][3][1][1]=8;
				KSP[11][3][1][2]=7;
				KSP[11][3][1][3]=6;
				KSP[11][3][1][4]=4;
				KSP[11][3][1][5]=3;
				KSP[11][3][2][0]=11;
				KSP[11][3][2][1]=12;
				KSP[11][3][2][2]=13;
				KSP[11][3][2][3]=10;
				KSP[11][3][2][4]=3;
				KSP[11][4][0][0]=11;
				KSP[11][4][0][1]=8;
				KSP[11][4][0][2]=7;
				KSP[11][4][0][3]=6;
				KSP[11][4][0][4]=4;
				KSP[11][4][1][0]=11;
				KSP[11][4][1][1]=12;
				KSP[11][4][1][2]=13;
				KSP[11][4][1][3]=8;
				KSP[11][4][1][4]=7;
				KSP[11][4][1][5]=6;
				KSP[11][4][1][6]=4;
				KSP[11][4][2][0]=11;
				KSP[11][4][2][1]=12;
				KSP[11][4][2][2]=5;
				KSP[11][4][2][3]=4;
				KSP[11][5][0][0]=11;
				KSP[11][5][0][1]=12;
				KSP[11][5][0][2]=5;
				KSP[11][5][1][0]=11;
				KSP[11][5][1][1]=8;
				KSP[11][5][1][2]=9;
				KSP[11][5][1][3]=5;
				KSP[11][5][2][0]=11;
				KSP[11][5][2][1]=12;
				KSP[11][5][2][2]=13;
				KSP[11][5][2][3]=8;
				KSP[11][5][2][4]=9;
				KSP[11][5][2][5]=5;
				KSP[11][6][0][0]=11;
				KSP[11][6][0][1]=8;
				KSP[11][6][0][2]=7;
				KSP[11][6][0][3]=6;
				KSP[11][6][1][0]=11;
				KSP[11][6][1][1]=12;
				KSP[11][6][1][2]=13;
				KSP[11][6][1][3]=8;
				KSP[11][6][1][4]=7;
				KSP[11][6][1][5]=6;
				KSP[11][6][2][0]=11;
				KSP[11][6][2][1]=10;
				KSP[11][6][2][2]=13;
				KSP[11][6][2][3]=8;
				KSP[11][6][2][4]=7;
				KSP[11][6][2][5]=6;
				KSP[11][7][0][0]=11;
				KSP[11][7][0][1]=8;
				KSP[11][7][0][2]=7;
				KSP[11][7][1][0]=11;
				KSP[11][7][1][1]=12;
				KSP[11][7][1][2]=13;
				KSP[11][7][1][3]=8;
				KSP[11][7][1][4]=7;
				KSP[11][7][2][0]=11;
				KSP[11][7][2][1]=10;
				KSP[11][7][2][2]=13;
				KSP[11][7][2][3]=8;
				KSP[11][7][2][4]=7;
				KSP[11][8][0][0]=11;
				KSP[11][8][0][1]=8;
				KSP[11][8][1][0]=11;
				KSP[11][8][1][1]=12;
				KSP[11][8][1][2]=13;
				KSP[11][8][1][3]=8;
				KSP[11][8][2][0]=11;
				KSP[11][8][2][1]=10;
				KSP[11][8][2][2]=13;
				KSP[11][8][2][3]=8;
				KSP[11][9][0][0]=11;
				KSP[11][9][0][1]=8;
				KSP[11][9][0][2]=9;
				KSP[11][9][1][0]=11;
				KSP[11][9][1][1]=12;
				KSP[11][9][1][2]=13;
				KSP[11][9][1][3]=8;
				KSP[11][9][1][4]=9;
				KSP[11][9][2][0]=11;
				KSP[11][9][2][1]=10;
				KSP[11][9][2][2]=13;
				KSP[11][9][2][3]=8;
				KSP[11][9][2][4]=9;
				KSP[11][10][0][0]=11;
				KSP[11][10][0][1]=10;
				KSP[11][10][1][0]=11;
				KSP[11][10][1][1]=12;
				KSP[11][10][1][2]=13;
				KSP[11][10][1][3]=10;
				KSP[11][10][2][0]=11;
				KSP[11][10][2][1]=8;
				KSP[11][10][2][2]=13;
				KSP[11][10][2][3]=10;
				KSP[11][11][0][0]=11;
				KSP[11][11][0][1]=11;
				KSP[11][12][0][0]=11;
				KSP[11][12][0][1]=12;
				KSP[11][12][1][0]=11;
				KSP[11][12][1][1]=8;
				KSP[11][12][1][2]=13;
				KSP[11][12][1][3]=12;
				KSP[11][12][2][0]=11;
				KSP[11][12][2][1]=10;
				KSP[11][12][2][2]=13;
				KSP[11][12][2][3]=12;
				KSP[11][13][0][0]=11;
				KSP[11][13][0][1]=12;
				KSP[11][13][0][2]=13;
				KSP[11][13][1][0]=11;
				KSP[11][13][1][1]=8;
				KSP[11][13][1][2]=13;
				KSP[11][13][2][0]=11;
				KSP[11][13][2][1]=10;
				KSP[11][13][2][2]=13;
				KSP[12][0][0][0]=12;
				KSP[12][0][0][1]=11;
				KSP[12][0][0][2]=8;
				KSP[12][0][0][3]=7;
				KSP[12][0][0][4]=0;
				KSP[12][0][1][0]=12;
				KSP[12][0][1][1]=13;
				KSP[12][0][1][2]=8;
				KSP[12][0][1][3]=7;
				KSP[12][0][1][4]=0;
				KSP[12][0][2][0]=12;
				KSP[12][0][2][1]=11;
				KSP[12][0][2][2]=10;
				KSP[12][0][2][3]=3;
				KSP[12][0][2][4]=1;
				KSP[12][0][2][5]=0;
				KSP[12][1][0][0]=12;
				KSP[12][1][0][1]=13;
				KSP[12][1][0][2]=10;
				KSP[12][1][0][3]=3;
				KSP[12][1][0][4]=1;
				KSP[12][1][1][0]=12;
				KSP[12][1][1][1]=11;
				KSP[12][1][1][2]=10;
				KSP[12][1][1][3]=3;
				KSP[12][1][1][4]=1;
				KSP[12][1][2][0]=12;
				KSP[12][1][2][1]=13;
				KSP[12][1][2][2]=8;
				KSP[12][1][2][3]=7;
				KSP[12][1][2][4]=6;
				KSP[12][1][2][5]=4;
				KSP[12][1][2][6]=3;
				KSP[12][1][2][7]=1;
				KSP[12][2][0][0]=12;
				KSP[12][2][0][1]=5;
				KSP[12][2][0][2]=2;
				KSP[12][2][1][0]=12;
				KSP[12][2][1][1]=13;
				KSP[12][2][1][2]=8;
				KSP[12][2][1][3]=9;
				KSP[12][2][1][4]=5;
				KSP[12][2][1][5]=2;
				KSP[12][2][2][0]=12;
				KSP[12][2][2][1]=11;
				KSP[12][2][2][2]=8;
				KSP[12][2][2][3]=9;
				KSP[12][2][2][4]=5;
				KSP[12][2][2][5]=2;
				KSP[12][3][0][0]=12;
				KSP[12][3][0][1]=11;
				KSP[12][3][0][2]=10;
				KSP[12][3][0][3]=3;
				KSP[12][3][1][0]=12;
				KSP[12][3][1][1]=13;
				KSP[12][3][1][2]=10;
				KSP[12][3][1][3]=3;
				KSP[12][3][2][0]=12;
				KSP[12][3][2][1]=11;
				KSP[12][3][2][2]=8;
				KSP[12][3][2][3]=7;
				KSP[12][3][2][4]=6;
				KSP[12][3][2][5]=4;
				KSP[12][3][2][6]=3;
				KSP[12][4][0][0]=12;
				KSP[12][4][0][1]=11;
				KSP[12][4][0][2]=8;
				KSP[12][4][0][3]=7;
				KSP[12][4][0][4]=6;
				KSP[12][4][0][5]=4;
				KSP[12][4][1][0]=12;
				KSP[12][4][1][1]=13;
				KSP[12][4][1][2]=8;
				KSP[12][4][1][3]=7;
				KSP[12][4][1][4]=6;
				KSP[12][4][1][5]=4;
				KSP[12][4][2][0]=12;
				KSP[12][4][2][1]=5;
				KSP[12][4][2][2]=4;
				KSP[12][5][0][0]=12;
				KSP[12][5][0][1]=5;
				KSP[12][5][1][0]=12;
				KSP[12][5][1][1]=11;
				KSP[12][5][1][2]=8;
				KSP[12][5][1][3]=9;
				KSP[12][5][1][4]=5;
				KSP[12][5][2][0]=12;
				KSP[12][5][2][1]=13;
				KSP[12][5][2][2]=8;
				KSP[12][5][2][3]=9;
				KSP[12][5][2][4]=5;
				KSP[12][6][0][0]=12;
				KSP[12][6][0][1]=11;
				KSP[12][6][0][2]=8;
				KSP[12][6][0][3]=7;
				KSP[12][6][0][4]=6;
				KSP[12][6][1][0]=12;
				KSP[12][6][1][1]=13;
				KSP[12][6][1][2]=8;
				KSP[12][6][1][3]=7;
				KSP[12][6][1][4]=6;
				KSP[12][6][2][0]=12;
				KSP[12][6][2][1]=11;
				KSP[12][6][2][2]=10;
				KSP[12][6][2][3]=13;
				KSP[12][6][2][4]=8;
				KSP[12][6][2][5]=7;
				KSP[12][6][2][6]=6;
				KSP[12][7][0][0]=12;
				KSP[12][7][0][1]=13;
				KSP[12][7][0][2]=8;
				KSP[12][7][0][3]=7;
				KSP[12][7][1][0]=12;
				KSP[12][7][1][1]=11;
				KSP[12][7][1][2]=8;
				KSP[12][7][1][3]=7;
				KSP[12][7][2][0]=12;
				KSP[12][7][2][1]=13;
				KSP[12][7][2][2]=10;
				KSP[12][7][2][3]=11;
				KSP[12][7][2][4]=8;
				KSP[12][7][2][5]=7;
				KSP[12][8][0][0]=12;
				KSP[12][8][0][1]=11;
				KSP[12][8][0][2]=8;
				KSP[12][8][1][0]=12;
				KSP[12][8][1][1]=13;
				KSP[12][8][1][2]=8;
				KSP[12][8][2][0]=12;
				KSP[12][8][2][1]=11;
				KSP[12][8][2][2]=10;
				KSP[12][8][2][3]=13;
				KSP[12][8][2][4]=8;
				KSP[12][9][0][0]=12;
				KSP[12][9][0][1]=13;
				KSP[12][9][0][2]=8;
				KSP[12][9][0][3]=9;
				KSP[12][9][1][0]=12;
				KSP[12][9][1][1]=11;
				KSP[12][9][1][2]=8;
				KSP[12][9][1][3]=9;
				KSP[12][9][2][0]=12;
				KSP[12][9][2][1]=5;
				KSP[12][9][2][2]=9;
				KSP[12][10][0][0]=12;
				KSP[12][10][0][1]=13;
				KSP[12][10][0][2]=10;
				KSP[12][10][1][0]=12;
				KSP[12][10][1][1]=11;
				KSP[12][10][1][2]=10;
				KSP[12][10][2][0]=12;
				KSP[12][10][2][1]=13;
				KSP[12][10][2][2]=8;
				KSP[12][10][2][3]=11;
				KSP[12][10][2][4]=10;
				KSP[12][11][0][0]=12;
				KSP[12][11][0][1]=11;
				KSP[12][11][1][0]=12;
				KSP[12][11][1][1]=13;
				KSP[12][11][1][2]=8;
				KSP[12][11][1][3]=11;
				KSP[12][11][2][0]=12;
				KSP[12][11][2][1]=13;
				KSP[12][11][2][2]=10;
				KSP[12][11][2][3]=11;
				KSP[12][12][0][0]=12;
				KSP[12][12][0][1]=12;
				KSP[12][13][0][0]=12;
				KSP[12][13][0][1]=13;
				KSP[12][13][1][0]=12;
				KSP[12][13][1][1]=11;
				KSP[12][13][1][2]=8;
				KSP[12][13][1][3]=13;
				KSP[12][13][2][0]=12;
				KSP[12][13][2][1]=11;
				KSP[12][13][2][2]=10;
				KSP[12][13][2][3]=13;
				KSP[13][0][0][0]=13;
				KSP[13][0][0][1]=8;
				KSP[13][0][0][2]=7;
				KSP[13][0][0][3]=0;
				KSP[13][0][1][0]=13;
				KSP[13][0][1][1]=12;
				KSP[13][0][1][2]=11;
				KSP[13][0][1][3]=8;
				KSP[13][0][1][4]=7;
				KSP[13][0][1][5]=0;
				KSP[13][0][2][0]=13;
				KSP[13][0][2][1]=10;
				KSP[13][0][2][2]=3;
				KSP[13][0][2][3]=1;
				KSP[13][0][2][4]=0;
				KSP[13][1][0][0]=13;
				KSP[13][1][0][1]=10;
				KSP[13][1][0][2]=3;
				KSP[13][1][0][3]=1;
				KSP[13][1][1][0]=13;
				KSP[13][1][1][1]=8;
				KSP[13][1][1][2]=7;
				KSP[13][1][1][3]=6;
				KSP[13][1][1][4]=4;
				KSP[13][1][1][5]=3;
				KSP[13][1][1][6]=1;
				KSP[13][1][2][0]=13;
				KSP[13][1][2][1]=12;
				KSP[13][1][2][2]=11;
				KSP[13][1][2][3]=10;
				KSP[13][1][2][4]=3;
				KSP[13][1][2][5]=1;
				KSP[13][2][0][0]=13;
				KSP[13][2][0][1]=12;
				KSP[13][2][0][2]=5;
				KSP[13][2][0][3]=2;
				KSP[13][2][1][0]=13;
				KSP[13][2][1][1]=8;
				KSP[13][2][1][2]=9;
				KSP[13][2][1][3]=5;
				KSP[13][2][1][4]=2;
				KSP[13][2][2][0]=13;
				KSP[13][2][2][1]=10;
				KSP[13][2][2][2]=3;
				KSP[13][2][2][3]=1;
				KSP[13][2][2][4]=2;
				KSP[13][3][0][0]=13;
				KSP[13][3][0][1]=10;
				KSP[13][3][0][2]=3;
				KSP[13][3][1][0]=13;
				KSP[13][3][1][1]=8;
				KSP[13][3][1][2]=7;
				KSP[13][3][1][3]=6;
				KSP[13][3][1][4]=4;
				KSP[13][3][1][5]=3;
				KSP[13][3][2][0]=13;
				KSP[13][3][2][1]=12;
				KSP[13][3][2][2]=11;
				KSP[13][3][2][3]=10;
				KSP[13][3][2][4]=3;
				KSP[13][4][0][0]=13;
				KSP[13][4][0][1]=8;
				KSP[13][4][0][2]=7;
				KSP[13][4][0][3]=6;
				KSP[13][4][0][4]=4;
				KSP[13][4][1][0]=13;
				KSP[13][4][1][1]=12;
				KSP[13][4][1][2]=11;
				KSP[13][4][1][3]=8;
				KSP[13][4][1][4]=7;
				KSP[13][4][1][5]=6;
				KSP[13][4][1][6]=4;
				KSP[13][4][2][0]=13;
				KSP[13][4][2][1]=12;
				KSP[13][4][2][2]=5;
				KSP[13][4][2][3]=4;
				KSP[13][5][0][0]=13;
				KSP[13][5][0][1]=12;
				KSP[13][5][0][2]=5;
				KSP[13][5][1][0]=13;
				KSP[13][5][1][1]=8;
				KSP[13][5][1][2]=9;
				KSP[13][5][1][3]=5;
				KSP[13][5][2][0]=13;
				KSP[13][5][2][1]=12;
				KSP[13][5][2][2]=11;
				KSP[13][5][2][3]=8;
				KSP[13][5][2][4]=9;
				KSP[13][5][2][5]=5;
				KSP[13][6][0][0]=13;
				KSP[13][6][0][1]=8;
				KSP[13][6][0][2]=7;
				KSP[13][6][0][3]=6;
				KSP[13][6][1][0]=13;
				KSP[13][6][1][1]=12;
				KSP[13][6][1][2]=11;
				KSP[13][6][1][3]=8;
				KSP[13][6][1][4]=7;
				KSP[13][6][1][5]=6;
				KSP[13][6][2][0]=13;
				KSP[13][6][2][1]=10;
				KSP[13][6][2][2]=11;
				KSP[13][6][2][3]=8;
				KSP[13][6][2][4]=7;
				KSP[13][6][2][5]=6;
				KSP[13][7][0][0]=13;
				KSP[13][7][0][1]=8;
				KSP[13][7][0][2]=7;
				KSP[13][7][1][0]=13;
				KSP[13][7][1][1]=12;
				KSP[13][7][1][2]=11;
				KSP[13][7][1][3]=8;
				KSP[13][7][1][4]=7;
				KSP[13][7][2][0]=13;
				KSP[13][7][2][1]=10;
				KSP[13][7][2][2]=11;
				KSP[13][7][2][3]=8;
				KSP[13][7][2][4]=7;
				KSP[13][8][0][0]=13;
				KSP[13][8][0][1]=8;
				KSP[13][8][1][0]=13;
				KSP[13][8][1][1]=12;
				KSP[13][8][1][2]=11;
				KSP[13][8][1][3]=8;
				KSP[13][8][2][0]=13;
				KSP[13][8][2][1]=10;
				KSP[13][8][2][2]=11;
				KSP[13][8][2][3]=8;
				KSP[13][9][0][0]=13;
				KSP[13][9][0][1]=8;
				KSP[13][9][0][2]=9;
				KSP[13][9][1][0]=13;
				KSP[13][9][1][1]=12;
				KSP[13][9][1][2]=11;
				KSP[13][9][1][3]=8;
				KSP[13][9][1][4]=9;
				KSP[13][9][2][0]=13;
				KSP[13][9][2][1]=10;
				KSP[13][9][2][2]=11;
				KSP[13][9][2][3]=8;
				KSP[13][9][2][4]=9;
				KSP[13][10][0][0]=13;
				KSP[13][10][0][1]=10;
				KSP[13][10][1][0]=13;
				KSP[13][10][1][1]=12;
				KSP[13][10][1][2]=11;
				KSP[13][10][1][3]=10;
				KSP[13][10][2][0]=13;
				KSP[13][10][2][1]=8;
				KSP[13][10][2][2]=11;
				KSP[13][10][2][3]=10;
				KSP[13][11][0][0]=13;
				KSP[13][11][0][1]=12;
				KSP[13][11][0][2]=11;
				KSP[13][11][1][0]=13;
				KSP[13][11][1][1]=8;
				KSP[13][11][1][2]=11;
				KSP[13][11][2][0]=13;
				KSP[13][11][2][1]=10;
				KSP[13][11][2][2]=11;
				KSP[13][12][0][0]=13;
				KSP[13][12][0][1]=12;
				KSP[13][12][1][0]=13;
				KSP[13][12][1][1]=8;
				KSP[13][12][1][2]=11;
				KSP[13][12][1][3]=12;
				KSP[13][12][2][0]=13;
				KSP[13][12][2][1]=10;
				KSP[13][12][2][2]=11;
				KSP[13][12][2][3]=12;
				KSP[13][13][0][0]=13;
				KSP[13][13][0][1]=13;
				
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** state (st_0) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "st_0", "malayeryprocess2 [st_0 exit execs]")


			/** state (st_0) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "st_0", "st_1", "tr_0", "malayeryprocess2 [st_0 -> st_1 : default / ]")
				/*---------------------------------------------------------*/



			/** state (st_1) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, "st_1", state1_enter_exec, "malayeryprocess2 [st_1 enter execs]")

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,"malayeryprocess2")


			/** state (st_1) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "st_1", "malayeryprocess2 [st_1 exit execs]")


			/** state (st_1) transition processing **/
			FSM_PROFILE_SECTION_IN ("malayeryprocess2 [st_1 trans conditions]", state1_trans_conds)
			FSM_INIT_COND (rcv_pk)
			FSM_TEST_COND (release_pk)
			FSM_TEST_COND (end_ls)
			FSM_TEST_COND (reserv)
			FSM_DFLT_COND
			FSM_TEST_LOGIC ("st_1")
			FSM_PROFILE_SECTION_OUT (state1_trans_conds)

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "rcv_pk", "", "st_1", "st_2", "tr_2", "malayeryprocess2 [st_1 -> st_2 : rcv_pk / ]")
				FSM_CASE_TRANSIT (1, 3, state3_enter_exec, ;, "release_pk", "", "st_1", "st_4", "tr_6", "malayeryprocess2 [st_1 -> st_4 : release_pk / ]")
				FSM_CASE_TRANSIT (2, 4, state4_enter_exec, ;, "end_ls", "", "st_1", "st_5", "tr_8", "malayeryprocess2 [st_1 -> st_5 : end_ls / ]")
				FSM_CASE_TRANSIT (3, 5, state5_enter_exec, ;, "reserv", "", "st_1", "st_7", "tr_12", "malayeryprocess2 [st_1 -> st_7 : reserv / ]")
				FSM_CASE_TRANSIT (4, 1, state1_enter_exec, ;, "default", "", "st_1", "st_1", "tr_1", "malayeryprocess2 [st_1 -> st_1 : default / ]")
				}
				/*---------------------------------------------------------*/



			/** state (st_2) enter executives **/
			FSM_STATE_ENTER_FORCED (2, "st_2", state2_enter_exec, "malayeryprocess2 [st_2 enter execs]")
				FSM_PROFILE_SECTION_IN ("malayeryprocess2 [st_2 enter execs]", state2_enter_exec)
				{
				int needed_fs;
				int des;
				long int pk_id;
				double hl_t;
				double endingtime;
				int src;
				int pktype;
				Packet *pkptr;
				pkptr = op_pk_get (0);
				
				
				
				op_pk_nfd_get(pkptr,"id",&pk_id);
				
				op_pk_nfd_get(pkptr,"holding_time",&hl_t);
				op_pk_nfd_get(pkptr,"src",&src);
				
				op_pk_nfd_get(pkptr,"dest",&des);
				
				
				op_pk_nfd_get(pkptr,"need",&needed_fs);
				
				op_pk_nfd_get(pkptr,"endtime",&endingtime);
				op_pk_nfd_get(pkptr,"type",&pktype);
				
				if (pktype==0){
				
				bw_req=bw_req + needed_fs;
				number_of_req=number_of_req+1;
				
				
				
				if (number_of_req > 100000)//hadeaksar 1000000 packet bayad bashad
					{
					
						
						FILE* file2=fopen(fname,"a+");
						fprintf(file2,"\n");
						fprintf(file2,"number_of_req ,number_of_nack,number_of_ack ,   bw_req ,    bw_nack ,    bw_ack   ,    BOK    ,    BNOK   ,Assigned Ratio,  Blocking Rate  , Blocking connection rate" );
						fprintf(file2,"\n");  
						fprintf(file2,"   %8d   ,  %8d    ,  %8d    ,  %8d ,  %8d  , %8d  , %8d , %8d ,    %6.3f  ,     %6.3f,    %6.3f ", number_of_req, number_of_nack ,number_of_ack,bw_req,bw_nack,bw_ack,BOK,BNOK, (float) bw_ack/bw_req , (float) bw_nack/bw_req, (float)number_of_nack/100000 );
						fprintf(file2,"\n");
						//fprintf(file2,"*** class1: no:%d , BVTOK:%d , Applied:%d  *** class2: no:%d , BVTOK:%d , Applied:%d ***  class3: no:%d , BVTOK:%d , Applied:%d", classes[0][0],classes[0][1],classes[0][2],classes[1][0],classes[1][1],classes[1][2],classes[2][0],classes[2][1],classes[2][2]);
						fprintf(file2,"\n**********************\n");
						//fprintf(file2,"core 0 OK:%d,   NOK:%d  , Core1: OK:%d , NOK: %d , Core3
						int totl=0;
						for(int oh=0;oh<7;oh++){
						totl+=classes[oh][0];
						totl+=classes[oh][2];
						fprintf(file2,"\n Core %d : OK : %d , NOK: %d , ReCORE:%d",oh,classes[oh][0],classes[oh][1],classes[oh][2]);
						}
						fprintf(file2,"\n********\n TOTAL: %d",totl);
						fprintf(file2,"\n***defragcounter==>%d", defragcounter);
						fprintf(file2,"\n ---- time is: %f  ------------ defcc is:%d -------------------------- ",op_sim_time (),defcc);
						fprintf(file2,"\n\n TRTR:%d",trtr);
						fclose (file2);
					
						op_sim_end("1000000 paket generated","","","");
											
					}
				
				
				
				
				
				if(ff_rr==1)
					assign(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr);
					
				
				 else if (ff_rr==3){ 
					assign(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr);
					
					if (number_of_req  == 20){
					printf("\n\n pktnom is:%d",pktnom);
					op_intrpt_schedule_self(op_sim_time ()  + 0.01 ,20000000);}
					
					}
				 else if (ff_rr==4){ //defmove
					assign(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr);
					
					if (number_of_req  == 20){
					printf("\n\n pktnom is:%d",pktnom);
					op_intrpt_schedule_self(op_sim_time ()  + 0.01 ,20000000);}
					
					}
				 else if (ff_rr==5){ 
					assign(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr);
					
					if (number_of_req  == 20){
					printf("\n\n pktnom is:%d",pktnom);
					op_intrpt_schedule_self(op_sim_time ()  + 0.01 ,20000000);}
					
					}
				 else if(ff_rr==6){
				 bestfitassign(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr);
				 }
				 else if (ff_rr==7){
				 bestpathassign(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr);
				 }
				 
				 
				 
				 
				 
				 
				 
				else if (ff_rr==8){
				int c=0;
				if (hl_t<2)
					c=0;
				else if(hl_t<4)
					c=1;
				else if  (hl_t<6)
					c=2;
				else if(hl_t<8)
					c=3;
				else if (hl_t<10)
					c=4;
				else
					c=5;
				 bool ass=newassign(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr,c);
				
				bool temp=false;
				short int loopgaurd=0;
				while((!ass)&&(loopgaurd<5)){
				if((hl_t+10)>((c+1)*20)){
				c++;
				if(c>4)
					c=0;
				}
				else c--;
				if(c<0)
					c=4;
				
				ass=newassign(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr,c);
				temp=ass;
					loopgaurd++;
				}
				
				if(loopgaurd>4){
				//op_pk_destroy(pkptr);
				number_of_nack++;
							bw_nack= bw_nack + needed_fs;
				printf("\n Packet %d DESTROYED!!!",pk_id);
				}
				/*
				if(!ass){
				number_of_nack++;
							bw_nack= bw_nack + needed_fs;
				//printf("\n Packet %d DESTROYED!!!",pk_id);
				}
				*/
				if (number_of_req  == 20){
				printf("\n going to intruot : %d",pktnom);
				op_intrpt_schedule_self(op_sim_time ()  + 0.01 ,20000000);
				printf("\n FINISH!!!");}
				}
				
				
				
				
				else if (ff_rr==9){// this mode tries each core for assigning!!!
				bool ass=false;
				short int c=0;
				
				while((!ass)&&(c<9)){
				ass=assigncore(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr,c);
				c++;
				
				}
				if(!ass){
				op_pk_destroy(pkptr);
				number_of_nack++;
							bw_nack= bw_nack + needed_fs;
				
				
				}
				
				}
				
				else if(ff_rr==10){
				int c=0;
				if (hl_t<2)
					c=0;
				else if(hl_t<4)
					c=1;
				else if  (hl_t<6)
					c=2;
				else if(hl_t<8)
					c=3;
				else if (hl_t<10)
					c=4;
				else
					c=5;
				bool ass=bestassign(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr,c);
				
				bool temp=false;
				short int loopgaurd=0;
				while((!ass)&&(loopgaurd<5)){
				if((hl_t+10)>((c+1)*20)){
				c++;
				if(c>4)
					c=0;
				}
				else c--;
				if(c<0)
					c=4;
				
				ass=bestassign(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr,c);
				temp=ass;
					loopgaurd++;
				}
				
				if(loopgaurd>4){
				//op_pk_destroy(pkptr);
				number_of_nack++;
							bw_nack= bw_nack + needed_fs;
				//printf("\n Packet %d DESTROYED!!!",pk_id);
				}
				
				if (number_of_req  == 20){
				printf("\n going to intruot : %d",pktnom);
				//op_intrpt_schedule_self(op_sim_time ()  + 0.01 ,20000000);
				printf("\n FINISH!!!");}
				
				}
				
				
				
				else if(ff_rr==11){
				int c=0;
				if (hl_t<timeclass[0][1])//5//1
					c=0;
				else if(hl_t<timeclass[1][1])//10//2
					c=1;
				else if  (hl_t<timeclass[2][1])//20//5
					c=2;
				else if(hl_t<timeclass[3][1])//50//50
					c=3;
				else if (hl_t<timeclass[4][1])//90//70
					c=5;
				else if (hl_t<timeclass[5][1])//150//90
					c=6;
				else
					c=8;
				
				short int c2=0;
				bool ass=bestassign(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr,c);
				if(ass)
					classes[c][0]++;
				else if (c<3)
					classes[c][1]++;
				else if (c==3)
					c2=4;	
				else if (c==5)
					c2=4;
				else if(c==6)
					c2=7;
				if((!ass) && (c>2))
				ass=bestassign(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr,c2);
						
				if((!ass)&&(c2>0))
					classes[c2][1]++;// if second core dont have enough space!
						else if (c2>0)
				classes[c2][0]++;
				
				short int loopgaurd=0;
				int tc=c;
				c=9;
				
				
				
				while((!ass)&&(loopgaurd<3)){
				c--;
				if(c<0){
					c=8;
				//loopgaurd=6;
					}
				
				
				ass=bestassign(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr,c);
				loopgaurd++;
				if(ass){
					classes[c][2]++;
					//printf("\n^^^^^^^^^^^\n ID:%d",pk_id);
					}
				}
				
				if((!ass)){
				op_pk_destroy(pkptr);
				number_of_nack++;
							bw_nack= bw_nack + needed_fs;
				
				}
				
				if (number_of_req  == 20){
				//printf("\n going to intruot : %d",pktnom);
				//op_intrpt_schedule_self(op_sim_time ()  + 0.01 ,20000000);
				//printf("\n FINISH!!!");
				}
				
				}
				
				
				
				
				
				
				
				
				
				
				
				
				else if(ff_rr==20){
				int c=0;
				if (hl_t<timeclass[0][1])//5//1
					c=0;
				else if(hl_t<timeclass[1][1])//10//2
					c=1;
				else if  (hl_t<timeclass[2][1])//20//5
					c=2;
				else if(hl_t<timeclass[3][1])//50//50
					c=3;
				else if (hl_t<timeclass[4][1])//90//70
					c=5;
				else if (hl_t<timeclass[5][1])//150//90
					c=6;
				else
					c=8;
				
				short int c2=0;
				bool ass=bestassignmodul(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr,c);
				if(ass)
					classes[c][0]++;
				else if (c<3)
					classes[c][1]++;
				else if (c==3)
					c2=4;	
				else if (c==5)
					c2=4;
				else if(c==6)
					c2=7;
				if((!ass) && (c>2))
				ass=bestassignmodul(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr,c2);
						
				if((!ass)&&(c2>0))
					classes[c][1]++;// if second core dont have enough space!
						else if (c2>0)
				classes[c2][0]++;
				short int loopgaurd=0;
				int tc=c;
				c=9;
				
				
				
				while((!ass)&&(loopgaurd<3)){
				c--;
				if(c<0){
					c=8;
				//loopgaurd=6;
					}
				
				
				ass=bestassignmodul(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr,c);
				loopgaurd++;
				if(ass){
					classes[c][2]++;
					//printf("\n^^^^^^^^^^^\n ID:%d",pk_id);
					}
				}
				
				if((!ass)){
				op_pk_destroy(pkptr);
				number_of_nack++;
							bw_nack= bw_nack + needed_fs;
				
				}
				
				if (number_of_req  == 20){
				//printf("\n going to intruot : %d",pktnom);
				//op_intrpt_schedule_self(op_sim_time ()  + 0.01 ,20000000);
				//printf("\n FINISH!!!");
				}
				
				}
				
				
				
				
				
				
				else if (ff_rr==22){// this mode tries each core for assigning!!!
				bool ass=false;
				short int c=0;
				
				while((!ass)&&(c<9)){
				ass=assigncoremodul(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr,c);
				c++;
				
				}
				if(!ass){
				op_pk_destroy(pkptr);
				number_of_nack++;
							bw_nack= bw_nack + needed_fs;
				
				
				}
				
				}
				
				else if(ff_rr==100){ // this method tries classification based on FS
				printf("\n assigning!");
				int c=0;
				if (needed_fs==5)//5//1
					c=0;
				else if(needed_fs==6)//10//2
					c=1;
				else if  (needed_fs==7)//20//5
					c=2;
				else if(needed_fs==8)//50//50
					c=3;
				else if (needed_fs==9)//90//70
					c=4;
				else if (needed_fs==10)//150//90
					c=5;
				
				
				short int c2=0;
				bool ass=assigncoremodul(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr,c);
				if(ass)
					classes[c][0]++;
				else if ((c==0)||(c==1))
					c2=6;	
				else if ((c==2)||(c==3))
					c2=7;
				else if ((c==4)||(c==5))
					c2=8;
				
				if((!ass))
				ass=assigncoremodul(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr,c2);
						
				if((!ass)&&(c2>0))
					classes[c][1]++;// if second core dont have enough space!
						else if (c2>0)
				classes[c2][0]++;
				
				
				
				/*while((!ass)&&(loopgaurd<3)){
				c--;
				if(c<0){
					c=8;
				//loopgaurd=6;
					}
				
				
				ass=bestassignmodul(pk_id,src,des,hl_t,op_sim_time() + hl_t,needed_fs,pkptr,c);
				loopgaurd++;
				if(ass){
					classes[c][2]++;
					//printf("\n^^^^^^^^^^^\n ID:%d",pk_id);
					}
				}*/
				
				if((!ass)){
				op_pk_destroy(pkptr);
				number_of_nack++;
							bw_nack= bw_nack + needed_fs;
				
				}
				
				
				}
				}
				
				else
					{
					printf("\n********\n**********\n");
					op_pk_destroy(pkptr);
					
					}
				}
				FSM_PROFILE_SECTION_OUT (state2_enter_exec)

			/** state (st_2) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "st_2", "malayeryprocess2 [st_2 exit execs]")


			/** state (st_2) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "st_2", "st_1", "tr_3", "malayeryprocess2 [st_2 -> st_1 : default / ]")
				/*---------------------------------------------------------*/



			/** state (st_4) enter executives **/
			FSM_STATE_ENTER_FORCED (3, "st_4", state3_enter_exec, "malayeryprocess2 [st_4 enter execs]")
				FSM_PROFILE_SECTION_IN ("malayeryprocess2 [st_4 enter execs]", state3_enter_exec)
				{
				int pk_id_code;
				pk_id_code=op_intrpt_code();
				
				if((pk_id_code<20000000)){
				
				node *node1;
				node *prv;
				node *tmp;
				node1=first;
				prv=first;
				while (node1 != NULL)
					{
						
						
						if (node1->id==pk_id_code)
							{
							pktnom--;
								int id_elp=node1->id;
								int tx=node1->tbvt;
								int rx=node1->rbvt;
								int start=node1->start;
								int last=node1->finish;
								int src_node=node1->source;
								int des_node=node1->destination;
								int k=node1->k;
								int hltime=node1->holdingtime;
								short int plength=node1->path_length;
								short int pth[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
							short int core=node1->core;
								for(int i=0;i<plength;i++)
									pth[i]=node1->path[i];
								
								
												
									 for ( int i=0; i< plength ; i++)
										 {
										 	
														
											for ( int j=start ; j<=last; j++)
												{
													Slots[core][pth[i]][j]=0;
														times[core][pth[i]][j]=0;		
												}
										 }
									 
									 Receiver_BVTs[des_node][rx]=false;
									 Transmitter_BVTs[src_node][tx]=false;
								
								
								
								if (node1==first)
									  {
									    tmp=node1;
										node1=node1->next;
										first=node1;
										prv=node1;
										delete tmp;
										break;
									  }
								  else if (node1==end)
									  {
									  	tmp=node1;
									    end=prv;
										end->next=NULL;
										prv=NULL;
										delete tmp;
										node1=NULL;
										break;
									  }
								  
								  else
									  {
									  	 tmp=node1;
										 prv->next=node1->next;
										 node1=node1->next;
										 delete tmp;
										 break;
									  }
								  }
						else
							{
								
								prv=node1;
								node1=node1->next;
								}
								
						}
				
				
				
				}
				
				
				}
				FSM_PROFILE_SECTION_OUT (state3_enter_exec)

			/** state (st_4) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "st_4", "malayeryprocess2 [st_4 exit execs]")


			/** state (st_4) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "st_4", "st_1", "tr_7", "malayeryprocess2 [st_4 -> st_1 : default / ]")
				/*---------------------------------------------------------*/



			/** state (st_5) enter executives **/
			FSM_STATE_ENTER_FORCED (4, "st_5", state4_enter_exec, "malayeryprocess2 [st_5 enter execs]")
				FSM_PROFILE_SECTION_IN ("malayeryprocess2 [st_5 enter execs]", state4_enter_exec)
				{
					
						FILE* file2=fopen(fname,"a+");
						fprintf(file2,"\n");
						
						
						fprintf(file2,"Assigned Ratio,  Blocking Rate  , Blocking connection rate" );
						fprintf(file2,"\n");  
						fprintf(file2,"    %6.3f  ,     %6.3f,    %6.3f ",  (float) bw_ack/bw_req , (float) bw_nack/bw_req, (float)number_of_nack/100000 );
						fprintf(file2,"\n");
						//fprintf(file2,"*** class1: no:%d , BVTOK:%d , Applied:%d  *** class2: no:%d , BVTOK:%d , Applied:%d ***  class3: no:%d , BVTOK:%d , Applied:%d", classes[0][0],classes[0][1],classes[0][2],classes[1][0],classes[1][1],classes[1][2],classes[2][0],classes[2][1],classes[2][2]);
						fprintf(file2,"\n**********************\n");
						//fprintf(file2,"core 0 OK:%d,   NOK:%d  , Core1: OK:%d , NOK: %d , Core3
						int totl=0;
						for(int oh=0;oh<9;oh++){
						totl+=classes[oh][0];
						totl+=classes[oh][2];
						fprintf(file2,"\n Core %d : OK : %d , NOK: %d , ReCORE:%d",oh,classes[oh][0],classes[oh][1],classes[oh][2]);
						}
						fprintf(file2,"\n********\n TOTAL: %d",totl);
						
						
						fprintf(file2,"\n\n TRTR:%d",trtr);
						fclose (file2);
						//shows();
					
						op_sim_end("1000000 paket generated","","","");
											
					
				
				
				}
				FSM_PROFILE_SECTION_OUT (state4_enter_exec)

			/** state (st_5) exit executives **/
			FSM_STATE_EXIT_FORCED (4, "st_5", "malayeryprocess2 [st_5 exit execs]")


			/** state (st_5) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "st_5", "st_1", "tr_9", "malayeryprocess2 [st_5 -> st_1 : default / ]")
				/*---------------------------------------------------------*/



			/** state (st_7) enter executives **/
			FSM_STATE_ENTER_FORCED (5, "st_7", state5_enter_exec, "malayeryprocess2 [st_7 enter execs]")

			/** state (st_7) exit executives **/
			FSM_STATE_EXIT_FORCED (5, "st_7", "malayeryprocess2 [st_7 exit execs]")


			/** state (st_7) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "st_7", "st_1", "tr_13", "malayeryprocess2 [st_7 -> st_1 : default / ]")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"malayeryprocess2")
		}
	catch (...)
		{
		Vos_Error_Print (VOSC_ERROR_ABORT,
			(const char *)VOSC_NIL,
			"Unhandled C++ exception in process model (malayeryprocess2)",
			(const char *)VOSC_NIL, (const char *)VOSC_NIL);
		}
	}




void
malayeryprocess2_state::_op_malayeryprocess2_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}

void
malayeryprocess2_state::operator delete (void* ptr)
	{
	FIN (malayeryprocess2_state::operator delete (ptr));
	Vos_Poolmem_Dealloc (ptr);
	FOUT
	}

malayeryprocess2_state::~malayeryprocess2_state (void)
	{

	FIN (malayeryprocess2_state::~malayeryprocess2_state ())


	/* No Termination Block */


	FOUT
	}


#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

void *
malayeryprocess2_state::operator new (size_t)
#if defined (VOSD_NEW_BAD_ALLOC)
		throw (VOSD_BAD_ALLOC)
#endif
	{
	void * new_ptr;

	FIN_MT (malayeryprocess2_state::operator new ());

	new_ptr = Vos_Alloc_Object (malayeryprocess2_state::obtype);
#if defined (VOSD_NEW_BAD_ALLOC)
	if (new_ptr == VOSC_NIL) throw VOSD_BAD_ALLOC();
#endif
	FRET (new_ptr)
	}

/* State constructor initializes FSM handling */
/* by setting the initial state to the first */
/* block of code to enter. */

malayeryprocess2_state::malayeryprocess2_state (void) :
		_op_current_block (0)
	{
#if defined (OPD_ALLOW_ODB)
		_op_current_state = "malayeryprocess2 [st_0 enter execs]";
#endif
	}

VosT_Obtype
_op_malayeryprocess2_init (int * init_block_ptr)
	{
	FIN_MT (_op_malayeryprocess2_init (init_block_ptr))

	malayeryprocess2_state::obtype = Vos_Define_Object_Prstate ("proc state vars (malayeryprocess2)",
		sizeof (malayeryprocess2_state));
	*init_block_ptr = 0;

	FRET (malayeryprocess2_state::obtype)
	}

VosT_Address
_op_malayeryprocess2_alloc (VosT_Obtype, int)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	malayeryprocess2_state * ptr;
	FIN_MT (_op_malayeryprocess2_alloc ())

	/* New instance will have FSM handling initialized */
#if defined (VOSD_NEW_BAD_ALLOC)
	try {
		ptr = new malayeryprocess2_state;
	} catch (const VOSD_BAD_ALLOC &) {
		ptr = VOSC_NIL;
	}
#else
	ptr = new malayeryprocess2_state;
#endif
	FRET ((VosT_Address)ptr)
	}



void
_op_malayeryprocess2_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	malayeryprocess2_state		*prs_ptr;

	FIN_MT (_op_malayeryprocess2_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (malayeryprocess2_state *)gen_ptr;

	if (strcmp ("deftime" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->deftime);
		FOUT
		}
	if (strcmp ("matrix_counter" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->matrix_counter);
		FOUT
		}
	if (strcmp ("linkk_numbers" , var_name) == 0)
		{
		*var_p_ptr = (void *) (prs_ptr->linkk_numbers);
		FOUT
		}
	if (strcmp ("untransferable_counter" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->untransferable_counter);
		FOUT
		}
	if (strcmp ("timeclass" , var_name) == 0)
		{
		*var_p_ptr = (void *) (prs_ptr->timeclass);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

