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
//M*/// ContEHMM.cpp: implementation of the CContEHMM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HMMDemo.h"
#include "ContEHMM.h"
#include <assert.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CContEHMM::CContEHMM()
{
    m_hmm = NULL;
    m_vectSize = 0;
}

CContEHMM::~CContEHMM()
{
    if (m_hmm) cvRelease2DHMM( &m_hmm );  
    m_vectSize = 0;

}

bool CContEHMM::CreateHMM( int* num_states, int* num_mix, int vect_size )
{
    if (m_hmm) cvRelease2DHMM( &m_hmm );
    m_hmm = 0;

    m_hmm = cvCreate2DHMM( num_states, num_mix, vect_size ); 
    
    m_vectSize = vect_size;
    return true;
    
    //else return false;
}


bool CContEHMM::Save( const char* filename )
{
    FILE* file;

    if (!m_hmm) return false;

    file = fopen( filename, "wt" );

    if (!file) return false;


    // write topology
    fprintf(file, "%s %d\n", "<NumSuperStates>", m_hmm->num_states );
    fprintf(file, "%s ", "<NumStates>");
    for( int i = 0; i < m_hmm->num_states; i++ )
    {
        fprintf(file, "%d ", m_hmm->u.ehmm[i].num_states );
    }
    fprintf(file, "\n");

    fprintf(file, "%s ", "<NumMixtures>");
    for( i = 0; i < m_hmm->num_states; i++ )
    {
        CvEHMM* ehmm = &(m_hmm->u.ehmm[i]);

        for( int j = 0; j < ehmm->num_states; j++ )
        {
            fprintf(file, "%d ", ehmm->u.state[j].num_mix );
        }
    }
    fprintf(file, "\n");

    fprintf(file, "%s %d\n", "<VecSize>", m_vectSize);

    //consequently write all hmms
    CvEHMM* hmm = m_hmm;
    for( i = 0; i < m_hmm->num_states + 1; i++ )
    {
        if (hmm->level == 0 )
            fprintf(file, "%s\n", "<BeginEmbeddedHMM>");
        else
            fprintf(file, "%s\n", "<BeginExternalHMM>");

        fprintf(file, "%s %d\n", "<NumStates>", hmm->num_states);

        if (hmm->level == 0 )
        {
            for ( int j = 0; j < hmm->num_states; j++)
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

                    for (int k = 0; k < m_vectSize; k++)
                    {  
                        fprintf(file, "%f ", mu[0]); 
                        mu++;
                    }            
                    
                    fprintf(file, "\n");
                    fprintf(file, "%s\n", "<Inverted_Deviation>");
                    
                    for (k = 0; k < m_vectSize; k++)
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

        if( hmm->level == 0 )
            fprintf(file, "%s\n", "<EndEmbeddedHMM>");
        else
            fprintf(file, "%s\n", "<EndExternalHMM>");

        hmm = &(m_hmm->u.ehmm[i]);
    }            
    fclose(file);
    return true;
} 

bool CContEHMM::Load( const char* filename )
{
    FILE* file;
    int num_states[128];
    int num_mix[128];
    char temp_char[128];

    if (m_hmm) cvRelease2DHMM( &m_hmm);

    file = fopen( filename, "rt" );

    if (!file) return false;

    // read topology
    fscanf(file, "%s %d\n", temp_char, num_states);
    fscanf(file, "%s ", temp_char); 
    for( int i = 0; i < num_states[0]; i++ )
    {
        fscanf(file, "%d ", num_states + i + 1 );
    }
    fscanf(file, "\n");
    
    //compute total number of internal states
    int total_states = 0;
    for( i = 0; i < num_states[0]; i++ )
    {
        total_states += num_states[i+1];
    }
    
    //read number of mixtures
    fscanf(file, "%s ", temp_char);
    for( i = 0; i < total_states; i++ )
    {
        fscanf(file, "%d ", &num_mix[i] );
    }
    fscanf(file, "\n");

    fscanf(file, "%s %d\n", temp_char, &m_vectSize);

    m_hmm = cvCreate2DHMM( num_states, num_mix, m_vectSize);

 
    //create HMM with known parameters
//!!!    cvCreate2DHMM( &m_hmm, num_states, num_mix, m_vectSize);
    if (!m_hmm ) return false;

    //consequently read all hmms
    CvEHMM* hmm = m_hmm;
    for( i = 0; i < num_states[0]+1; i++ )
    {
        fscanf(file, "%s\n", temp_char);
        int temp_int;
        fscanf(file, "%s %d\n", temp_char , &temp_int);  assert(temp_int==num_states[i]); 

        if ( i!= 0 )
        {
            for (int j = 0; j < num_states[i]; j++)
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

                    for (int k = 0; k < m_vectSize; k++)
                    {  
                        fscanf(file, "%f ", mu); 
                        mu++;
                    }            
                    
                    fscanf(file, "\n");
                    fscanf(file, "%s\n", temp_char);
                    
                    for (k = 0; k < m_vectSize; k++)
                    {
                        fscanf(file, "%f ", inv_var);
                        inv_var++;
                    }
                    fscanf(file, "\n");

                    fscanf(file, "%s %f\n", temp_char, &(state->log_var_val[m]) );
                    
                }
            }
        }

        //read the transition probability matrix
        fscanf(file, "%s\n", temp_char ); 
        float* prob = hmm->transP;

        for (int j = 0; j < hmm->num_states; j++)
        {
            for (int k = 0; k < hmm->num_states; k++)
            {
                fscanf(file, "%f ", prob);
                prob++;
            }            
            fscanf(file, "\n");
        }

        fscanf( file, "%s\n", temp_char );

        hmm = &(m_hmm->u.ehmm[i]);
    }
    fclose(file); 
    return true;
}
    
BOOL CContEHMM::Release()
{
    if (m_hmm)
    {
        cvRelease2DHMM( &m_hmm ); 
        m_hmm = 0;
    }

    return TRUE;
}
