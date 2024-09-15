/* Process model C++ form file: malayeriprocess1.pr.cpp */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char malayeriprocess1_pr_cpp [] = "MIL_3_Tfile_Hdr_ 145A 30A modeler 7 5E1D9363 5E1D9363 1 ali-PC ali 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1e80 8                                                                                                                                                                                                                                                                                                                                                                                                               ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */

#define intrupt ((op_intrpt_type ()== OPC_INTRPT_SELF ) && (op_intrpt_code ()< 20000000))
#define		SSC_STRM_TO_LOW			0
#define regular  ((op_intrpt_type () == OPC_INTRPT_SELF) &&  (op_intrpt_code () >= 20000000) && ((op_intrpt_code () < 30000000)))

long int connect_create=1;
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;
FILE* file2;
FILE* f;
char fname2[30]="e:/out1/randomfit/res.txt";
int prob=10;
int reg=0;

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
class malayeriprocess1_state
	{
	private:
		/* Internal state tracking for FSM */
		FSM_SYS_STATE

	public:
		malayeriprocess1_state (void);

		/* Destructor contains Termination Block */
		~malayeriprocess1_state (void);

		/* State Variables */
		Distribution *	         		src                                             ;
		Distribution *	         		des                                             ;
		Distribution *	         		needed                                          ;
		Distribution *	         		pos                                             ;
		double	                 		arrival                                         ;
		Distribution *	         		ppp                                             ;

		/* FSM code */
		void malayeriprocess1 (OP_SIM_CONTEXT_ARG_OPT);
		/* Diagnostic Block */
		void _op_malayeriprocess1_diag (OP_SIM_CONTEXT_ARG_OPT);

#if defined (VOSD_NEW_BAD_ALLOC)
		void * operator new (size_t) throw (VOSD_BAD_ALLOC);
#else
		void * operator new (size_t);
#endif
		void operator delete (void *);

		/* Memory management */
		static VosT_Obtype obtype;
	};

VosT_Obtype malayeriprocess1_state::obtype = (VosT_Obtype)OPC_NIL;

#define src                     		op_sv_ptr->src
#define des                     		op_sv_ptr->des
#define needed                  		op_sv_ptr->needed
#define pos                     		op_sv_ptr->pos
#define arrival                 		op_sv_ptr->arrival
#define ppp                     		op_sv_ptr->ppp

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	malayeriprocess1_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((malayeriprocess1_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


/* No Function Block */

#if !defined (VOSD_NO_FIN)
enum { _op_block_origin = __LINE__ };
#endif

/* Undefine optional tracing in FIN/FOUT/FRET */
/* The FSM has its own tracing code and the other */
/* functions should not have any tracing.		  */
#undef FIN_TRACING
#define FIN_TRACING

#undef FOUTRET_TRACING
#define FOUTRET_TRACING

/* Undefine shortcuts to state variables because the */
/* following functions are part of the state class */
#undef src
#undef des
#undef needed
#undef pos
#undef arrival
#undef ppp

/* Access from C kernel using C linkage */
extern "C"
{
	VosT_Obtype _op_malayeriprocess1_init (int * init_block_ptr);
	VosT_Address _op_malayeriprocess1_alloc (VosT_Obtype, int);
	void malayeriprocess1 (OP_SIM_CONTEXT_ARG_OPT)
		{
		((malayeriprocess1_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr))->malayeriprocess1 (OP_SIM_CONTEXT_PTR_OPT);
		}

	void _op_malayeriprocess1_svar (void *, const char *, void **);

	void _op_malayeriprocess1_diag (OP_SIM_CONTEXT_ARG_OPT)
		{
		((malayeriprocess1_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr))->_op_malayeriprocess1_diag (OP_SIM_CONTEXT_PTR_OPT);
		}

	void _op_malayeriprocess1_terminate (OP_SIM_CONTEXT_ARG_OPT)
		{
		/* The destructor is the Termination Block */
		delete (malayeriprocess1_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr);
		}


} /* end of 'extern "C"' */




/* Process model interrupt handling procedure */


void
malayeriprocess1_state::malayeriprocess1 (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (malayeriprocess1_state::malayeriprocess1 ());
	try
		{


		FSM_ENTER ("malayeriprocess1")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (st_0) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (0, "st_0", "malayeriprocess1 [st_0 enter execs]")
				FSM_PROFILE_SECTION_IN ("malayeriprocess1 [st_0 enter execs]", state0_enter_exec)
				{
				des = op_dist_load ("uniform_int", 0, 13);
				src = op_dist_load ("uniform_int", 0, 13);
				needed = op_dist_load ("uniform_int", 5, 10);//5-20 for IDF!
				ppp = op_dist_load ("uniform_int", 0, 100);
				arrival=0.01;
				pos=op_dist_load ("poisson", 0.01, 0.0);
				FILE* file2=fopen(fname2,"w");
						fprintf(file2,"\n****************\n Arrival:%f Erlang:%f\n************\n",arrival,(1/arrival)*20);
				fclose(file2);
				op_intrpt_schedule_self (op_sim_time() + op_dist_exponential(arrival),0);
				//for (int i=1;i<=100;i++){
				//Packet *pkptr;
				//pkptr=op_pk_create_fmt("infopk");
				//op_pk_nfd_set (pkptr, "id",i );
				//op_pk_nfd_set (pkptr, "tim",i);
				//op_pk_send (pkptr, SSC_STRM_TO_LOW);
				op_intrpt_schedule_self ( op_sim_time(),20000001);
				//}
				
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** state (st_0) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "st_0", "malayeriprocess1 [st_0 exit execs]")


			/** state (st_0) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "st_0", "st_1", "tr_0", "malayeriprocess1 [st_0 -> st_1 : default / ]")
				/*---------------------------------------------------------*/



			/** state (st_1) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, "st_1", state1_enter_exec, "malayeriprocess1 [st_1 enter execs]")

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,"malayeriprocess1")


			/** state (st_1) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "st_1", "malayeriprocess1 [st_1 exit execs]")


			/** state (st_1) transition processing **/
			FSM_PROFILE_SECTION_IN ("malayeriprocess1 [st_1 trans conditions]", state1_trans_conds)
			FSM_INIT_COND (intrupt)
			FSM_TEST_COND (regular)
			FSM_DFLT_COND
			FSM_TEST_LOGIC ("st_1")
			FSM_PROFILE_SECTION_OUT (state1_trans_conds)

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "intrupt", "", "st_1", "st_2", "tr_2", "malayeriprocess1 [st_1 -> st_2 : intrupt / ]")
				FSM_CASE_TRANSIT (1, 3, state3_enter_exec, ;, "regular", "", "st_1", "st_3", "tr_4", "malayeriprocess1 [st_1 -> st_3 : regular / ]")
				FSM_CASE_TRANSIT (2, 1, state1_enter_exec, ;, "default", "", "st_1", "st_1", "tr_1", "malayeriprocess1 [st_1 -> st_1 : default / ]")
				}
				/*---------------------------------------------------------*/



			/** state (st_2) enter executives **/
			FSM_STATE_ENTER_FORCED (2, "st_2", state2_enter_exec, "malayeriprocess1 [st_2 enter execs]")
				FSM_PROFILE_SECTION_IN ("malayeriprocess1 [st_2 enter execs]", state2_enter_exec)
				{
				Packet *pkptr;
				pkptr=op_pk_create_fmt("EONPK");
				int des_pk;
				int needed_pk;
				int src_pk;
				//int regularity;
				//regularity=op_dist_outcome(ppp);
				
				needed_pk=op_dist_outcome (needed);
				
				
				des_pk=op_dist_outcome (des);
				
				src_pk=op_dist_outcome (src);//std::fmod(op_dist_outcome (src),14);
				
				double holding_time = op_dist_exponential(20);
				
				while (des_pk==src_pk)
					{
					  des_pk=op_dist_outcome (des);
					}
				
				
				
				op_pk_nfd_set (pkptr, "id",connect_create );
				op_pk_nfd_set (pkptr, "holding_time",holding_time);
				op_pk_nfd_set (pkptr, "src",src_pk);
				op_pk_nfd_set (pkptr, "dest",des_pk);
				op_pk_nfd_set (pkptr, "need",needed_pk);
				op_pk_nfd_set (pkptr, "endtime",op_sim_time () + holding_time);
				op_pk_nfd_set (pkptr, "type",0);
				if (pkptr!=NULL)
					{
					op_pk_send (pkptr, SSC_STRM_TO_LOW);
					//printf("\n size:%d",op_pk_total_size_get(pkptr));
				}
				
				
				connect_create++ ;// tedade etesalat
				if(connect_create<=100000){
				
					
					op_intrpt_schedule_self (op_sim_time() + op_dist_exponential(arrival),0);
						file2=fopen("E:/malayeri/cons22.txt","a+");
						fprintf(file2,"\n SIMTIME: %f   source:%d and Dest:%d and needed:%d and holding time:%f",op_sim_time(),src_pk,des_pk,needed_pk,holding_time);
					fclose(file2);
						}else
					printf("\n simtime: %f",op_sim_time());
				
				}
				FSM_PROFILE_SECTION_OUT (state2_enter_exec)

			/** state (st_2) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "st_2", "malayeriprocess1 [st_2 exit execs]")


			/** state (st_2) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "st_2", "st_1", "tr_3", "malayeriprocess1 [st_2 -> st_1 : default / ]")
				/*---------------------------------------------------------*/



			/** state (st_3) enter executives **/
			FSM_STATE_ENTER_FORCED (3, "st_3", state3_enter_exec, "malayeriprocess1 [st_3 enter execs]")
				FSM_PROFILE_SECTION_IN ("malayeriprocess1 [st_3 enter execs]", state3_enter_exec)
				{
					if (reg<100){
					file2=fopen("E:/malayeri/cons3.txt","a+");
					fprintf(file2,"sim time:%f\n",op_sim_time());
					fclose(file2);
					
				Packet *pkptra;
				pkptra=op_pk_create_fmt("EONPK");
				int des_pk;
				int needed_pk;
				int src_pk;
				needed_pk=5;
				des_pk=10;
				src_pk=1;
				double holding_time = op_dist_exponential(20);
				
				reg++;
				op_pk_nfd_set (pkptra, "id",connect_create );
				op_pk_nfd_set (pkptra, "holding_time",holding_time);
				op_pk_nfd_set (pkptra, "src",src_pk);
				op_pk_nfd_set (pkptra, "dest",des_pk);
				op_pk_nfd_set (pkptra, "need",needed_pk);
				op_pk_nfd_set (pkptra, "endtime",op_sim_time () + holding_time);
				op_pk_nfd_set (pkptra, "type",1);
					
				if (pkptra!=NULL)
					{
					op_pk_send (pkptra, SSC_STRM_TO_LOW);
					connect_create++ ;
				}
					else{
					printf("\n Error");
					}
					op_intrpt_schedule_self ( op_sim_time()+reg,20000000+reg);
					}
					
				}
				FSM_PROFILE_SECTION_OUT (state3_enter_exec)

			/** state (st_3) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "st_3", "malayeriprocess1 [st_3 exit execs]")


			/** state (st_3) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "st_3", "st_1", "tr_5", "malayeriprocess1 [st_3 -> st_1 : default / ]")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"malayeriprocess1")
		}
	catch (...)
		{
		Vos_Error_Print (VOSC_ERROR_ABORT,
			(const char *)VOSC_NIL,
			"Unhandled C++ exception in process model (malayeriprocess1)",
			(const char *)VOSC_NIL, (const char *)VOSC_NIL);
		}
	}




void
malayeriprocess1_state::_op_malayeriprocess1_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}

void
malayeriprocess1_state::operator delete (void* ptr)
	{
	FIN (malayeriprocess1_state::operator delete (ptr));
	Vos_Poolmem_Dealloc (ptr);
	FOUT
	}

malayeriprocess1_state::~malayeriprocess1_state (void)
	{

	FIN (malayeriprocess1_state::~malayeriprocess1_state ())


	/* No Termination Block */


	FOUT
	}


#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

void *
malayeriprocess1_state::operator new (size_t)
#if defined (VOSD_NEW_BAD_ALLOC)
		throw (VOSD_BAD_ALLOC)
#endif
	{
	void * new_ptr;

	FIN_MT (malayeriprocess1_state::operator new ());

	new_ptr = Vos_Alloc_Object (malayeriprocess1_state::obtype);
#if defined (VOSD_NEW_BAD_ALLOC)
	if (new_ptr == VOSC_NIL) throw VOSD_BAD_ALLOC();
#endif
	FRET (new_ptr)
	}

/* State constructor initializes FSM handling */
/* by setting the initial state to the first */
/* block of code to enter. */

malayeriprocess1_state::malayeriprocess1_state (void) :
		_op_current_block (0)
	{
#if defined (OPD_ALLOW_ODB)
		_op_current_state = "malayeriprocess1 [st_0 enter execs]";
#endif
	}

VosT_Obtype
_op_malayeriprocess1_init (int * init_block_ptr)
	{
	FIN_MT (_op_malayeriprocess1_init (init_block_ptr))

	malayeriprocess1_state::obtype = Vos_Define_Object_Prstate ("proc state vars (malayeriprocess1)",
		sizeof (malayeriprocess1_state));
	*init_block_ptr = 0;

	FRET (malayeriprocess1_state::obtype)
	}

VosT_Address
_op_malayeriprocess1_alloc (VosT_Obtype, int)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	malayeriprocess1_state * ptr;
	FIN_MT (_op_malayeriprocess1_alloc ())

	/* New instance will have FSM handling initialized */
#if defined (VOSD_NEW_BAD_ALLOC)
	try {
		ptr = new malayeriprocess1_state;
	} catch (const VOSD_BAD_ALLOC &) {
		ptr = VOSC_NIL;
	}
#else
	ptr = new malayeriprocess1_state;
#endif
	FRET ((VosT_Address)ptr)
	}



void
_op_malayeriprocess1_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	malayeriprocess1_state		*prs_ptr;

	FIN_MT (_op_malayeriprocess1_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (malayeriprocess1_state *)gen_ptr;

	if (strcmp ("src" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->src);
		FOUT
		}
	if (strcmp ("des" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->des);
		FOUT
		}
	if (strcmp ("needed" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->needed);
		FOUT
		}
	if (strcmp ("pos" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->pos);
		FOUT
		}
	if (strcmp ("arrival" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->arrival);
		FOUT
		}
	if (strcmp ("ppp" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->ppp);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

