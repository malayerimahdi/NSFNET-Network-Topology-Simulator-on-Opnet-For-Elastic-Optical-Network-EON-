MIL_3_Tfile_Hdr_ 145A 140A modeler 9 5DF79F92 5E1D9362 1D ali-PC ali 0 0 none none 0 0 none 62D53317 18F0 0 0 0 0 0 0 1e80 8                                                                                                                                                                                                                                                                                                                                                                                                    ��g�      @   D   H      �  �  �  �  �  �  �  �  �           	   begsim intrpt         
   ����   
   doc file            	nd_module      endsim intrpt         
   ����   
   failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue                     count    ���   
   ����   
      list   	���   
          
      super priority             ����             Distribution *	\src;       Distribution *	\des;       Distribution *	\needed;       Distribution *	\pos;       double	\arrival;       Distribution *	\ppp;              Y#define intrupt ((op_intrpt_type ()== OPC_INTRPT_SELF ) && (op_intrpt_code ()< 20000000))   #define		SSC_STRM_TO_LOW			0   �#define regular  ((op_intrpt_type () == OPC_INTRPT_SELF) &&  (op_intrpt_code () >= 20000000) && ((op_intrpt_code () < 30000000)))       long int connect_create=1;   #include <fstream>   #include <iostream>   #include <cmath>   using namespace std;   FILE* file2;   FILE* f;   ,char fname2[30]="e:/out1/randomfit/res.txt";   int prob=10;   
int reg=0;                                             �            
   st_0   
       J      *des = op_dist_load ("uniform_int", 0, 13);   *src = op_dist_load ("uniform_int", 0, 13);   <needed = op_dist_load ("uniform_int", 5, 10);//5-20 for IDF!   +ppp = op_dist_load ("uniform_int", 0, 100);   arrival=0.01;   (pos=op_dist_load ("poisson", 0.01, 0.0);   FILE* file2=fopen(fname2,"w");   d		fprintf(file2,"\n****************\n Arrival:%f Erlang:%f\n************\n",arrival,(1/arrival)*20);   fclose(file2);   Iop_intrpt_schedule_self (op_sim_time() + op_dist_exponential(arrival),0);   //for (int i=1;i<=100;i++){   //Packet *pkptr;   #//pkptr=op_pk_create_fmt("infopk");   !//op_pk_nfd_set (pkptr, "id",i );   !//op_pk_nfd_set (pkptr, "tim",i);   &//op_pk_send (pkptr, SSC_STRM_TO_LOW);   2op_intrpt_schedule_self ( op_sim_time(),20000001);   //}       J                     
   ����   
          pr_state        �   Z          
   st_1   
                                       ����             pr_state        �  J          
   st_2   
       J   1   Packet *pkptr;    pkptr=op_pk_create_fmt("EONPK");   int des_pk;   int needed_pk;   int src_pk;   //int regularity;   "//regularity=op_dist_outcome(ppp);       #needed_pk=op_dist_outcome (needed);           des_pk=op_dist_outcome (des);       Csrc_pk=op_dist_outcome (src);//std::fmod(op_dist_outcome (src),14);       .double holding_time = op_dist_exponential(20);       while (des_pk==src_pk)   	{    	  des_pk=op_dist_outcome (des);   	}               ,op_pk_nfd_set (pkptr, "id",connect_create );   3op_pk_nfd_set (pkptr, "holding_time",holding_time);   $op_pk_nfd_set (pkptr, "src",src_pk);   %op_pk_nfd_set (pkptr, "dest",des_pk);   (op_pk_nfd_set (pkptr, "need",needed_pk);   ?op_pk_nfd_set (pkptr, "endtime",op_sim_time () + holding_time);    op_pk_nfd_set (pkptr, "type",0);   if (pkptr!=NULL)   	{   %	op_pk_send (pkptr, SSC_STRM_TO_LOW);   4	//printf("\n size:%d",op_pk_total_size_get(pkptr));   }           $connect_create++ ;// tedade etesalat   if(connect_create<=100000){       	   J	op_intrpt_schedule_self (op_sim_time() + op_dist_exponential(arrival),0);   -		file2=fopen("E:/malayeri/cons22.txt","a+");   �		fprintf(file2,"\n SIMTIME: %f   source:%d and Dest:%d and needed:%d and holding time:%f",op_sim_time(),src_pk,des_pk,needed_pk,holding_time);   	fclose(file2);   		}else   (	printf("\n simtime: %f",op_sim_time());       J                     
   ����   
          pr_state        :            
   st_3   
       J   #   	if (reg<100){   +	file2=fopen("E:/malayeri/cons3.txt","a+");   .	fprintf(file2,"sim time:%f\n",op_sim_time());   	fclose(file2);   	   Packet *pkptra;   !pkptra=op_pk_create_fmt("EONPK");   int des_pk;   int needed_pk;   int src_pk;   needed_pk=5;   
des_pk=10;   	src_pk=1;   .double holding_time = op_dist_exponential(20);       reg++;   -op_pk_nfd_set (pkptra, "id",connect_create );   4op_pk_nfd_set (pkptra, "holding_time",holding_time);   %op_pk_nfd_set (pkptra, "src",src_pk);   &op_pk_nfd_set (pkptra, "dest",des_pk);   )op_pk_nfd_set (pkptra, "need",needed_pk);   @op_pk_nfd_set (pkptra, "endtime",op_sim_time () + holding_time);   !op_pk_nfd_set (pkptra, "type",1);   	   if (pkptra!=NULL)   	{   &	op_pk_send (pkptra, SSC_STRM_TO_LOW);   	connect_create++ ;   }   	else{   	printf("\n Error");   	}   ;	op_intrpt_schedule_self ( op_sim_time()+reg,20000000+reg);   	}   	   J                     
   ����   
          pr_state                       	   �      �     y   K          
   tr_0   
       ����          ����          
    ����   
          ����                       pr_transition              �   =     �   j  �     9     �   I          
   tr_1   
       
   default   
       ����          
    ����   
          ����                       pr_transition              {   �     |   i  z  ?          
   tr_2   
       
   intrupt   
       ����          
    ����   
          ����                       pr_transition              �   �     �  W  �   K          
   tr_3   
       ����          ����          
    ����   
          ����                       pr_transition              �   �     �   l  >   �          
   tr_4   
       
   regular   
       ����          
    ����   
          ����                       pr_transition              �   �     3  "  �   K          
   tr_5   
       ����          ����          
    ����   
          ����                       pr_transition                                             