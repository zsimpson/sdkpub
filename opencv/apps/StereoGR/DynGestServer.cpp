/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/// DynGestServer.cpp: implementation of the CDynGestServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DynGestServer.h"
#include "StereoGR.h"

#include "math.h"
#include "assert.h"
#include "float.h"

#include "direct.h"



CDynGesture::CDynGesture( int num_states, int num_mix )
{
    m_hmm = NULL;
#if 0
    m_obsType  = OT_VELOCITY;
#else
	m_obsType  = OT_VELOCITY_ORIENTATION;
#endif
    m_trained = FALSE;
    m_num_states = num_states;
    m_num_mix = num_mix;      
    m_vect_size = 6;            
}          

CDynGesture::~CDynGesture()
{
    if ( m_hmm ) icvRelease1DHMM( &m_hmm );
    
    for ( int i = 0; i < m_Sequences.size() ; i++ )
    {
        cvReleaseObsInfo( &(m_Sequences[i]) );
    }
}

void CDynGesture::AddSequence( float* vectors, int seq_size, int vect_size )
{
    Cv1DObsInfo* obs_info;
    obs_info = cvCreateObsInfo( cvSize( seq_size,1), vect_size );
    
    memcpy( obs_info->obs, vectors, seq_size * vect_size * sizeof(float) );
    m_Sequences.push_back( obs_info );

    m_trained = FALSE;
    
}

void CDynGesture::Train()
{
    ExtractObservations();

    int num_seq = m_Sequences.size();

    if ( !num_seq ) ASSERT(0); 
    
    //create HMM
    if (!m_hmm) CreateHMM();
    
    for(int i = 0; i < num_seq; i++ )
    {
        icvUniform1DSegm( m_Sequences[i], m_hmm );
        //printf("uniform segmentation performed\n");     
    }
    
    icvInit1DMixSegm( &m_Sequences[0], num_seq, m_hmm );
    //printf("Init 1D mix segmentation performed\n");
    
    int trained = 0;
    float old_likelihood = 0;
    
    //printf("Begin training\n");
    //wait_key(0);         
    
    while( !trained )
    {            
        icvEstimate1DHMMStateParams( &m_Sequences[0], num_seq, m_hmm );
        //printf("HMMstate performed\n");
        icvEstimate1DTransProb( &m_Sequences[0], num_seq, m_hmm );
        //printf("Transprob performed\n"); 
        float likelihood = 0;  
        
        for( int j = 0; j < num_seq; j++ )
        {           
            icvEstimate1DObsProb( m_Sequences[j], m_hmm );
            likelihood += icvViterbi( m_Sequences[j], m_hmm );
            //wait_key(0);        
        }
        //printf("likelihood %f\n", likelihood );
        
        icv1DMixSegmL2( &m_Sequences[0], num_seq, m_hmm );
        //printf("1DMixSegm performed\n"); 
        
        trained = ( fabs(likelihood - old_likelihood) < 0.01 ); 
        old_likelihood = likelihood;                   
    }
    //printf("%d hmm trained\n", h );

    m_trained = TRUE;
    
}
BOOL  CDynGesture::SaveHMM(const char* filename)
{
    FILE* file;
    
    if (!m_hmm) return FALSE;
    file = fopen( filename, "wt" );
    if (!file) { assert(0); return false; }
    
    // write topology
    fprintf(file, "%s %d\n", "<NumStates>", m_hmm->num_states );
    fprintf(file, "%s ", "<NumMixtures>");
    for( int i = 0; i < m_hmm->num_states; i++ )
    {
        fprintf(file, "%d ", m_hmm->u.state[i].num_mix );        
    }
    fprintf(file, "\n");
    
    fprintf(file, "%s %d\n", "<VecSize>", m_vect_size );
    
    //consequently write all hmms
    CvEHMM* hmm = m_hmm;
    if (hmm->level == 0 )
    {
        for ( int j = 0; j < hmm->num_states; j++ )
        {
            CvEHMMState* state = &(hmm->u.state[j]);
            
            fprintf(file, "%s %d\n", "<State>", j);
            fprintf(file, "%s %d\n", "<NumMixes>", state->num_mix);
            
            float* mu = state->mu;
            float* inv_var = state->inv_var;
            
            for( int m = 0; m < state->num_mix; m++)
            {
                fprintf(file, "%s %d %s %f\n", "<Mixture>", m, "<Weight>", state->weight[m] );
                fprintf(file, "%s\n", "<Mean>");
                
                for (int k = 0; k <  m_vect_size; k++)
                {  
                    fprintf(file, "%f ", mu[0]); 
                    mu++;
                }            
                
                fprintf(file, "\n");
                fprintf(file, "%s\n", "<Inverted_Deviation>");
                
                for (k = 0; k <  m_vect_size; k++)
                {
                    fprintf(file, "%f ", inv_var[0]);
                    inv_var++;
                }
                fprintf(file, "\n");
                
                fprintf(file, "%s %f\n", "<LogVarVal>", state->log_var_val[m] );   
            }
        }
    }
    
    //write the transition probability matrix
        fprintf(file, "%s\n", "<TransP>" ); 
        float* prob = hmm->transP;

        for (int j = 0; j < hmm->num_states; j++)
        {
            for (int k = 0; k < hmm->num_states; k++)
            {
                fprintf(file, "%f ", *prob);
                prob++;
            }            
            fprintf(file, "\n");
        }
                
    fclose(file);
    return true;
}

BOOL CDynGesture::LoadHMM(const char* filename)
{   
    FILE* file;
    int num_states;
    int num_mix[128];
    char temp_char[128];
    int vec_size;

    if (m_hmm) icvRelease1DHMM( &m_hmm);

    file = fopen( filename, "rt" );

    if (!file) return false;

    // read topology
    fscanf(file, "%s %d\n", temp_char, &num_states);
    fscanf(file, "%s ", temp_char); 
    
    //compute total number of internal states
    int total_states = num_states;
    
    //read number of mixtures
    //fscanf(file, "%s ", temp_char);
    for( int i = 0; i < total_states; i++ )
    {
        fscanf(file, "%d ", &num_mix[i] );
    }
    fscanf(file, "\n");

    fscanf(file, "%s %d\n", temp_char, &vec_size);


    icvCreate1DHMM( &m_hmm, num_states, num_mix, vec_size);
 
    //create HMM with known parameters
//!!!    cvCreate2DHMM( &m_hmm, num_states, num_mix, m_vectSize);
    if (!m_hmm ) return FALSE;
    
    //consequently read all hmms
    CvEHMM* hmm = m_hmm;
    int temp_int;
    
    for (int j = 0; j < num_states; j++)
    {
        CvEHMMState* state = &(hmm->u.state[j]);
        
        fscanf(file, "%s %d\n", temp_char, &temp_int); assert(temp_int == j);
        
        fscanf(file, "%s %d\n", temp_char, &temp_int); assert(temp_int == state->num_mix);
        
        float* mu = state->mu;
        float* inv_var = state->inv_var;
        
        for( int m = 0; m < state->num_mix; m++)
        {
            int temp_int;
            fscanf(file, "%s %d %s %f\n", temp_char, &temp_int, temp_char, &(state->weight[m]) );
            assert( temp_int == m );
            fscanf(file, "%s\n", temp_char );
            
            for (int k = 0; k < vec_size; k++)
            {  
                fscanf(file, "%f ", mu); 
                mu++;
            }            
            
            fscanf(file, "\n");
            fscanf(file, "%s\n", temp_char);  //  <Inverted_Deviation>
            
            for (k = 0; k < vec_size; k++)
            {
                fscanf(file, "%f ", inv_var);
                inv_var++;
            }
            fscanf(file, "\n");
            
            fscanf(file, "%s %f\n", temp_char, &(state->log_var_val[m]) );  // <LogVarVal>                   
        }
    }
    
    //read the transition probability matrix
    fscanf(file, "%s\n", temp_char ); // <TransP>
    float* prob = hmm->transP;
    
    for ( j = 0; j < hmm->num_states; j++)
    {
        for (int k = 0; k < hmm->num_states; k++)
        {
            fscanf(file, "%f ", prob);
            prob++;
        }            
        fscanf(file, "\n");
    }       
    
    
    fclose(file); 
    return TRUE;
}

int CDynGesture::GetSeqNumber()
{
    return m_Params.size();
} 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDynGestServer::CDynGestServer()
{
    m_fullTrained = FALSE;
}

CDynGestServer::~CDynGestServer()
{

}

CDynGesture* CDynGestServer::FindGesture( const char* name )
{
    for( int i = 0; i < m_gestures.size() ; i++ )
    {
        CString exist_name = m_gestures[i]->GetName();
        if ( name ==  exist_name ) return m_gestures[i];
    }
    return 0; 
}

CDynGesture* CDynGestServer::AddGesture( const char* name )
{
    CDynGesture* new_gest = new CDynGesture( m_num_states, m_num_mix);
    new_gest->SetName( name );
    m_gestures.push_back( new_gest );

    m_fullTrained = FALSE;
    
    return m_gestures.back();
} 

BOOL CDynGestServer::AddGesture( CDynGesture* new_gest )
{
    if ( FindGesture( new_gest->GetName() )  ) return FALSE;

    m_gestures.push_back( new_gest );

    m_fullTrained = FALSE;
    
    return TRUE;
} 



void CDynGestServer::TrainAllGestures()
{
	int size = m_gestures.size();
    for( int i = 0; i < size; i++ )
    {
        m_gestures[i]->Train();
    }  
    m_fullTrained = TRUE;

}

void CDynGesture::CreateHMM()
{
    int* numix = new int[m_num_states];
    for( int i = 0; i < m_num_states; i++ )
    {
        numix[i] = m_num_mix;
    }
    
    icvCreate1DHMM( &m_hmm, m_num_states, numix, 6 );
        
}

BOOL CDynGesture::LoadFromFile(const char *obsFilename)
{   
    ASSERT(0);

    return TRUE;
}

BOOL CDynGesture::AddParams( vector<_gr_pose>& input_vect )
{
	m_Params.push_back( input_vect );
    m_trained = FALSE;

	return TRUE;
}

BOOL CDynGesture::SaveParams(const char* path)
{
    FILE* file;
    CString filename;

    _mkdir( path );

    for ( int i = 0; i < m_Params.size(); i++ )
    {
        vector<_gr_pose> seq = m_Params[i];

        // construct name
        filename.Format( "%s\\%s_%03d%s", path, m_name, i,".obs" );
        file = fopen( filename, "wt");


        for(int i = 0; i < seq.size(); i++)
        {               
            const fvector& ref = seq[i];
            CvHuMoments& hu = seq[i].pose;
            __int64 time = seq[i].time;
            __int64 time0 = seq[0].time;

		    fprintf(file, "%d %s %f %f %f %f %f %f %f %f %f %f %f %f %f\n", 
			    long(time - time0), "*.bmp"/*LPCTSTR(mask_name)*/, ref[0], ref[1], ref[2], 
                                                                   ref[3], ref[4], ref[5],
			                                                       (float)hu.hu1, (float)hu.hu2, 
                                                                   (float)hu.hu3, (float)hu.hu4, 
                                                                   (float)hu.hu5, (float)hu.hu6,
                                                                   (float)hu.hu7);
        }
        fclose(file);
        file = 0;
    }

    return TRUE;
}

BOOL CDynGesture::LoadParams(const char* path)
{
    //check if path exist
    if ( _chdir( path ) < 0 )
        return FALSE;

    BOOL end = FALSE;
    int i = 0;
    m_Params.clear();
        
    while (!end)
    {
        CString filename;
        FILE* file;
        //construct file name and load
        filename.Format( "%s_%03d%s", path, i,".obs" );
        file = fopen( filename, "r");

        if ( !file ) { end = TRUE; continue; }

        //Read file
        vector<_gr_pose> positions;
        positions.clear();

        char bmpname[256];

        _gr_pose pose;
        pose.resize(6);//construct vector of 6 elements

        int int_time;
        float hu[7];
        //compute number of observations
        while(fscanf(file, "%d %s %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
                     &int_time, bmpname,  
                     &pose[0], &pose[1], &pose[2], 
                     &pose[3], &pose[4], &pose[5],
                     &hu[0], &hu[1], &hu[2], &hu[3],
                     &hu[4], &hu[5], &hu[6] )!= EOF)
        {   
            pose.time = int_time;
            pose.pose.hu1 = hu[0];
            pose.pose.hu2 = hu[1];
            pose.pose.hu3 = hu[2];
            pose.pose.hu4 = hu[3];
            pose.pose.hu5 = hu[4];
            pose.pose.hu6 = hu[5];
            pose.pose.hu7 = hu[6]; 

            positions.push_back( pose );                        
        }

        fclose(file); 
        m_Params.push_back( positions );
        i++;
    }
    if ( i == 0 ) return FALSE; 

    //goto parent directory
    _chdir("..\\" );

    return TRUE;
}

BOOL CDynGesture::LoadSequence( const char* filename )
{
        FILE* file;
        //construct file name and load
        file = fopen( filename, "r");

        if ( !file ) return FALSE;

        //Read file
        vector<_gr_pose> positions;
        positions.clear();

        char bmpname[256];

        _gr_pose pose;
        pose.resize(6);//construct vector of 6 elements

        int int_time;
        float hu[7];
        //compute number of observations
        while(fscanf(file, "%d %s %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
                     &int_time, bmpname,  
                     &pose[0], &pose[1], &pose[2], 
                     &pose[3], &pose[4], &pose[5],
                     &hu[0], &hu[1], &hu[2], &hu[3],
                     &hu[4], &hu[5], &hu[6] )!= EOF)
        {   
            pose.time = int_time;
            pose.pose.hu1 = hu[0];
            pose.pose.hu2 = hu[1];
            pose.pose.hu3 = hu[2];
            pose.pose.hu4 = hu[3];
            pose.pose.hu5 = hu[4];
            pose.pose.hu6 = hu[5];
            pose.pose.hu7 = hu[6]; 

            positions.push_back( pose );                        
        }

        fclose(file); 
        m_Params.push_back( positions );   

        m_trained = FALSE;
        
    return TRUE;
}

void CDynGesture::CleanSequences()
{
    for( int i = 0; i < m_Sequences.size(); i++ )
    {
        cvReleaseObsInfo( &m_Sequences[i] );
    }
    m_Sequences.clear();
    m_trained = FALSE;
}

void CDynGesture::ExtractObservations()
{
	//clean all observations
	CleanSequences();

	//extract observations from parameters
	for( int i = 0; i < m_Params.size(); i++ )
	{
        vector<_gr_pose>& seq = m_Params[i];
        int seq_size = seq.size();
        Cv1DObsInfo* obs_info = NULL;
        
        switch ( m_obsType )
	    {
	    case OT_VELOCITY:
		    {
                seq_size--; //velocities has 1 less observation than positions
			    m_vect_size = 3;
                obs_info = cvCreateObsInfo( cvSize( seq_size, 1 ), m_vect_size );
                int counter = 0;
                //construct velocities
                for( int j = 0; j < seq_size; j++ )
                {                       
                    fvector& cur_obs = seq[j];
                    fvector& next_obs = seq[j+1];
                    
                    for( int k = 0; k < 3; k++ )
                    { 
                        obs_info->obs[counter] = 100.f * (next_obs[k] - cur_obs[k]);
                        counter++;
                    }
                }
            }
            break;

	    case OT_VELOCITY_ORIENTATION:
		    {
                seq_size--; //velocities has 1 less observation than positions
			    m_vect_size = 6;
                obs_info = cvCreateObsInfo( cvSize( seq_size, 1 ), m_vect_size );
                int counter = 0;
                //construct velocities
                for( int j = 0; j < seq_size; j++ )
                {                       
                    fvector& cur_obs = seq[j];
                    fvector& next_obs = seq[j+1];
                    
                    for( int k = 0; k < 3; k++ )
                    { 
                        obs_info->obs[counter] = 100.f * (next_obs[k] - cur_obs[k]);
                        counter++;
                    }
                    for(; k < 6; k++ )
                    { 
                        obs_info->obs[counter] = 10.0f * (next_obs[k] - cur_obs[k]);
                        counter++;
                    }

                }
            }
            break;

        default: ASSERT(0);
        }//switch
        
        // push observations 
        m_Sequences.push_back( obs_info );

    }//for
}   

int CDynGestServer::RecognizeDynGesture(CDynGesture *gesture, float* likelihood)
{
    float likelihoodproxy[256]; //256 gestures - maximum
    if (!likelihood) likelihood = likelihoodproxy;
    /* recognition stage */

    int num_gestures = m_gestures.size();
    
    for( int i = 0; i < m_gestures.size(); i++ )
    {
        if ( !m_gestures[i]->m_trained )
        {
            //AfxMessageBox( "Not all Dynamic Gestures are trained! ", MB_ICONSTOP|MB_OK, 0 );
            return -1;
        }
    }

    //ASSERT( m_fullTrained );//all stored gestures must be trained
    
    float max_like = - FLT_MAX;
    int recognized = INT_MAX;
    
    ASSERT( gesture->GetSeqNumber() == 1 );

    Cv1DObsInfo** obs_arr = gesture->GetSequences();
    Cv1DObsInfo* obs = obs_arr[0];
        
    for( int h = 0; h < num_gestures; h++ )
    {                          
        CvEHMM* hmm = m_gestures[h]->GetHMM(); 

        icvEstimate1DObsProb( obs, hmm );
        
        likelihood[h] = icvViterbi( obs, hmm );
        
        if (likelihood[h] > max_like )
        {
            max_like = likelihood[h];
            recognized = h;
        }
    }
    
    //printf("%d-th gesture recognized as %d\n", j, image );
    return recognized;
}

CvImgObsInfo** CDynGesture::GetSequences()
{
   return &(m_Sequences[0]);
}

BOOL CDynGestServer::LoadGestureBase(const char *filename)
{   
    CleanAll();

    FILE* file;
    file = fopen( filename, "r" );

    if (!file ) return FALSE;
        
    char gesture_name[256];

    //read main file
    while ( fscanf( file, "%s\n", gesture_name )!=EOF )
    {
        CDynGesture* gesture = new CDynGesture( m_num_states, m_num_mix );
        gesture->SetName( gesture_name );
        gesture->LoadParams( gesture_name );
        
        //try to load hmm
        if ( ! _chdir( gesture->GetName() ) )
        {
            if ( gesture->LoadHMM(gesture->GetName() + ".hmm") )
            {
                gesture->m_trained = TRUE;
                //change value of m_hmmParams control
                CStereoGRApp* app = (CStereoGRApp*)AfxGetApp();
                app->m_hmmParams->m_num_states = gesture->GetHMM()->num_states;
                app->m_hmmParams->m_num_mix = gesture->GetHMM()->u.state->num_mix;
                SetHMMParams( app->m_hmmParams->m_num_states,
                              app->m_hmmParams->m_num_mix );

            }
        
            _chdir( "..\\" );
        }        
                
        AddGesture( gesture );         
    }                          
    fclose( file );
    m_loaded_base = filename;
    return TRUE; 
}

BOOL CDynGestServer::SaveGestureBase(const char *name)
{   
    FILE* file;
    file = fopen( name, "wt" );

    for( int i = 0; i < m_gestures.size(); i++ )
    {
        CDynGesture* gesture = m_gestures[i];
        fprintf( file, "%s\n", gesture->GetName() );
        gesture->SaveParams( gesture->GetName() );
        if ( gesture->m_trained )
        {
            _chdir( gesture->GetName() );
            gesture->SaveHMM(gesture->GetName() + ".hmm");
            _chdir( "..\\" );            
        }
    } 

    fclose( file );

    m_loaded_base = name;
 
    return TRUE;   
}

void CDynGestServer::CleanAll()
{
    for( int i = 0; i < m_gestures.size(); i++ )
        delete m_gestures[i];
    m_gestures.clear();

    m_fullTrained = false;

}

void CDynGestServer::SetHMMParams( int num_state, int num_mix )
{
    if ( m_num_states != num_state || m_num_mix != num_mix )
    {
        m_num_states = num_state;
        m_num_mix    = num_mix;
        //change every gesture params
        for( int i = 0; i < m_gestures.size(); i++ )
        {
            m_gestures[i]->m_num_mix = num_mix;
            m_gestures[i]->m_num_states = num_state;
            m_gestures[i]->m_trained = FALSE;
            m_gestures[i]->DestroyHMM();
        }
        m_fullTrained = FALSE;
    }
}

BOOL CDynGestServer::RemoveGesture( const char* name )
{   
    for( vector<CDynGesture*>::iterator it = m_gestures.begin(); it < m_gestures.end(); it++ )
    {
        if ( (*it)->GetName() == name )
        {
            m_gestures.erase( it );
            return TRUE;
        }
    }
    return FALSE;
}


void CDynGesture::DestroyHMM()
{
    if (m_hmm) icvRelease1DHMM( &m_hmm );
    m_trained = FALSE;
}   


void CDynGestServer::DeleteHMMInfo()
{
    for( int i = 0; i < m_gestures.size(); i++ )
    {
        m_gestures[i]->DeleteHMM();
        if( !_chdir( m_gestures[i]->GetName() ) )
        {
            remove( m_gestures[i]->GetName() + ".hmm" );
            _chdir( "..\\" );
        }                    
    }
    m_fullTrained = FALSE;
}

void CDynGesture::DeleteHMM()
{
    icvRelease1DHMM( &m_hmm );
    m_trained = FALSE;
}
