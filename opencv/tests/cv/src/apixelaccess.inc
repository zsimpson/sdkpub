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
//M*/

#define CHECK( value, error, message )          \
    if( value )                                 \
    {                                           \
        error++;                                \
        trsWrite( ATS_CON | ATS_LST, message ); \
    }

    /* Body function */
    
    TEST_TYPE  pos;
    DATA_TYPE* data = (DATA_TYPE*)icvAlloc( SIZE_X * SIZE_Y * sizeof(DATA_TYPE) );
    CvSize     roi;
    int        Errors = 0;

    roi.width  = SIZE_X;
    roi.height = SIZE_Y;

    /* Check for CV_INIT_PIXEL_POS */
    CV_INIT_PIXEL_POS( pos,
                        data,
                        SIZE_X * PLANS * sizeof( DATA_TYPE ),
                        roi,
                        BEGIN_X,
                        BEGIN_Y,
                        0 );
    CHECK( pos.topline != data - SIZE_X * PLANS, Errors, "INIT_PIXEL_POS: Wrong  topline\n" );
    CHECK( pos.currline != data + SIZE_X * PLANS * BEGIN_Y,
           Errors,
           "INIT_PIXEL_POS: Wrong  currline\n" );
    CHECK( pos.bottomline != data + SIZE_Y * PLANS * SIZE_X,
           Errors,
           "INIT_PIXEL_POS: Wrong  bottomline\n" );
    CHECK( pos.step != SIZE_X * PLANS, Errors, "INIT_PIXEL_POS: Wrong  step\n" );
    CHECK( pos.height != SIZE_Y, Errors, "INIT_PIXEL_POS: Wrong  height\n" );
    CHECK( pos.width != SIZE_X, Errors, "INIT_PIXEL_POS: Wrong  width\n" );
    CHECK( pos.step_arr[0] != 0, Errors, "INIT_PIXEL_POS: Wrong  step_arr[0]\n");
    CHECK( pos.step_arr[1] != -SIZE_X * PLANS, Errors, "INIT_PIXEL_POS: Wrong  step_arr[1]\n");
    CHECK( pos.step_arr[2] != SIZE_X * PLANS, Errors, "INIT_PIXEL_POS: Wrong  step_arr[2]\n");
    CHECK( pos.x != BEGIN_X, Errors, "INIT_PIXEL_POS: Wrong  x\n" );

    if( Errors ) return trsResult( TRS_FAIL, "Wrong initialisation. Test aborted !!!" );

    /* Check for CV_MOVE_TO */
    CHECK( CV_MOVE_TO( pos, SECOND_X, SECOND_Y, PLANS ) !=
           data + SECOND_Y * pos.step + SECOND_X * PLANS,
           Errors,
           "MOVE_TO: Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_TO: Wrong currline\n" );
    CHECK( pos.x != SECOND_X, Errors, "MOVE_TO: Wrong x\n" );


    /* Check for CV_GET_CURRENT */
    CHECK( CV_GET_CURRENT( pos, PLANS ) !=
           data + SECOND_Y * pos.step + SECOND_X * PLANS,
           Errors,
           "GET_CURRENT: Wrong pointer\n" );


    /* Check for CV_MOVE_LEFT */
    CHECK( CV_MOVE_LEFT( pos, PLANS ) != data + 
                                          pos.step * SECOND_Y +
                                          (SECOND_X - 1) * PLANS,
           Errors,
           "MOVE_LEFT: Wrong pointer\n" );
    CHECK( pos.x != SECOND_X - 1, Errors, "MOVE_LEFT: Wrong x\n" );

    /* Check for CV_MOVE_RIGHT */
    CHECK( CV_MOVE_RIGHT( pos, PLANS ) != data + 
                                          pos.step * SECOND_Y +
                                          SECOND_X * PLANS,
           Errors,
           "MOVE_RIGHT: Wrong pointer\n" );
    CHECK( pos.x != SECOND_X, Errors, "MOVE_RIGHT: Wrong x\n" );

    /* Check for CV_MOVE_UP */
    CHECK( CV_MOVE_UP( pos, PLANS ) != data + 
                                        pos.step * (SECOND_Y - 1)+
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_UP: Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * (SECOND_Y - 1),
           Errors,
           "MOVE_UP: Wrong currline\n" );

    /* Check for CV_MOVE_DOWN */
    CHECK( CV_MOVE_DOWN( pos, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_DOWN: Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_DOWN: Wrong currline\n" );

    /* Check for CV_MOVE_LU */
    CHECK( CV_MOVE_LU( pos, PLANS ) != data + 
                                        pos.step * (SECOND_Y - 1) +
                                        (SECOND_X - 1) * PLANS,
           Errors,
           "MOVE_LU: Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * (SECOND_Y - 1),
           Errors,
           "MOVE_LU: Wrong currline\n" );
    CHECK( pos.x != SECOND_X - 1,
           Errors,
           "MOVE_LU: Wrong x\n" );

    /* Check for CV_MOVE_RD */
    CHECK( CV_MOVE_RD( pos, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_RD: Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_RD: Wrong currline\n" );
    CHECK( pos.x != SECOND_X,
           Errors,
           "MOVE_RD: Wrong x\n" );

    /* Check for CV_MOVE_RU */
    CHECK( CV_MOVE_RU( pos, PLANS ) != data + 
                                        pos.step * (SECOND_Y - 1) +
                                        (SECOND_X + 1) * PLANS,
           Errors,
           "MOVE_RU: Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * (SECOND_Y - 1),
           Errors,
           "MOVE_RU: Wrong currline\n" );
    CHECK( pos.x != SECOND_X + 1,
           Errors,
           "MOVE_RU: Wrong x\n" );

    /* Check for CV_MOVE_LD */
    CHECK( CV_MOVE_LD( pos, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_LD: Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_LD: Wrong currline\n" );
    CHECK( pos.x != SECOND_X,
           Errors,
           "MOVE_LD: Wrong x\n" );


    /* Check for CV_MOVE_LEFT_WRAP */
    CHECK( CV_MOVE_LEFT_WRAP( pos, PLANS ) != data + 
                                          pos.step * SECOND_Y +
                                          (SECOND_X - 1) * PLANS,
           Errors,
           "MOVE_LEFT_WRAP: Wrong pointer\n" );
    CHECK( pos.x != SECOND_X - 1, Errors, "MOVE_LEFT: Wrong x\n" );

    /* Check for CV_MOVE_RIGHT_WRAP */
    CHECK( CV_MOVE_RIGHT_WRAP( pos, PLANS ) != data + 
                                          pos.step * SECOND_Y +
                                          SECOND_X * PLANS,
           Errors,
           "MOVE_RIGHT_WRAP: Wrong pointer\n" );
    CHECK( pos.x != SECOND_X, Errors, "MOVE_RIGHT: Wrong x\n" );

    /* Check for CV_MOVE_UP_WRAP */
    CHECK( CV_MOVE_UP_WRAP( pos, PLANS ) != data + 
                                        pos.step * (SECOND_Y - 1)+
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_UP_WRAP: Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * (SECOND_Y - 1),
           Errors,
           "MOVE_UP_WRAP: Wrong currline\n" );

    /* Check for CV_MOVE_DOWN_WRAP */
    CHECK( CV_MOVE_DOWN_WRAP( pos, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_DOWN_WRAP: Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_DOWN_WRAP: Wrong currline\n" );

    /* Check for CV_MOVE_LU_WRAP */
    CHECK( CV_MOVE_LU_WRAP( pos, PLANS ) != data + 
                                        pos.step * (SECOND_Y - 1) +
                                        (SECOND_X - 1) * PLANS,
           Errors,
           "MOVE_LU_WRAP: Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * (SECOND_Y - 1),
           Errors,
           "MOVE_LU_WRAP: Wrong currline\n" );
    CHECK( pos.x != SECOND_X - 1,
           Errors,
           "MOVE_LU_WRAP: Wrong x\n" );

    /* Check for CV_MOVE_RD_WRAP */
    CHECK( CV_MOVE_RD_WRAP( pos, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_RD: Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_RD_WRAP: Wrong currline\n" );
    CHECK( pos.x != SECOND_X,
           Errors,
           "MOVE_RD_WRAP: Wrong x\n" );

    /* Check for CV_MOVE_RU_WRAP */
    CHECK( CV_MOVE_RU_WRAP( pos, PLANS ) != data + 
                                        pos.step * (SECOND_Y - 1) +
                                        (SECOND_X + 1) * PLANS,
           Errors,
           "MOVE_RU_WRAP: Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * (SECOND_Y - 1),
           Errors,
           "MOVE_RU_WRAP: Wrong currline\n" );
    CHECK( pos.x != SECOND_X + 1,
           Errors,
           "MOVE_RU_WRAP: Wrong x\n" );

    /* Check for CV_MOVE_LD_WRAP */
    CHECK( CV_MOVE_LD_WRAP( pos, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_LD_WRAP: Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_LD_WRAP: Wrong currline\n" );
    CHECK( pos.x != SECOND_X,
           Errors,
           "MOVE_LD_WRAP: Wrong x\n" );


    /* Check for CV_MOVE_PARAM */
    CHECK( CV_MOVE_PARAM( pos, CV_SHIFT_NONE, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_PARAM(NONE): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_PARAM(NONE): Wrong currline\n" );
    CHECK( pos.x != SECOND_X,
           Errors,
           "MOVE_PARAM(NONE): Wrong x\n" );

    CHECK( CV_MOVE_PARAM( pos, CV_SHIFT_LEFT, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        (SECOND_X - 1) * PLANS,
           Errors,
           "MOVE_PARAM(LEFT): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_PARAM(LEFT): Wrong currline\n" );
    CHECK( pos.x != SECOND_X - 1,
           Errors,
           "MOVE_PARAM(LEFT): Wrong x\n" );

    CHECK( CV_MOVE_PARAM( pos, CV_SHIFT_RIGHT, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_PARAM(RIGHT): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_PARAM(RIGHT): Wrong currline\n" );
    CHECK( pos.x != SECOND_X,
           Errors,
           "MOVE_PARAM(RIGHT): Wrong x\n" );

    CHECK( CV_MOVE_PARAM( pos, CV_SHIFT_UP, PLANS ) != data + 
                                        pos.step * (SECOND_Y - 1) +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_PARAM(UP): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * (SECOND_Y - 1),
           Errors,
           "MOVE_PARAM(UP): Wrong currline\n" );
    CHECK( pos.x != SECOND_X,
           Errors,
           "MOVE_PARAM(UP): Wrong x\n" );

    CHECK( CV_MOVE_PARAM( pos, CV_SHIFT_DOWN, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_PARAM(DOWN): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_PARAM(DOWN): Wrong currline\n" );
    CHECK( pos.x != SECOND_X,
           Errors,
           "MOVE_PARAM(DOWN): Wrong x\n" );

    CHECK( CV_MOVE_PARAM( pos, CV_SHIFT_LU, PLANS ) != data + 
                                        pos.step * (SECOND_Y - 1) +
                                        (SECOND_X - 1) * PLANS,
           Errors,
           "MOVE_PARAM(LU): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * (SECOND_Y - 1),
           Errors,
           "MOVE_PARAM(LU): Wrong currline\n" );
    CHECK( pos.x != SECOND_X - 1,
           Errors,
           "MOVE_PARAM(LU): Wrong x\n" );

    CHECK( CV_MOVE_PARAM( pos, CV_SHIFT_RD, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_PARAM(RD): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_PARAM(RD): Wrong currline\n" );
    CHECK( pos.x != SECOND_X,
           Errors,
           "MOVE_PARAM(RD): Wrong x\n" );

    CHECK( CV_MOVE_PARAM( pos, CV_SHIFT_RU, PLANS ) != data + 
                                        pos.step * (SECOND_Y - 1) +
                                        (SECOND_X + 1) * PLANS,
           Errors,
           "MOVE_PARAM(RU): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * (SECOND_Y - 1),
           Errors,
           "MOVE_PARAM(RU): Wrong currline\n" );
    CHECK( pos.x != SECOND_X + 1,
           Errors,
           "MOVE_PARAM(RU): Wrong x\n" );

    CHECK( CV_MOVE_PARAM( pos, CV_SHIFT_LD, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_PARAM(LD): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_PARAM(LD): Wrong currline\n" );
    CHECK( pos.x != SECOND_X,
           Errors,
           "MOVE_PARAM(LD): Wrong x\n" );


    /* Check for CV_MOVE_PARAM_WRAP */
    CHECK( CV_MOVE_PARAM_WRAP( pos, CV_SHIFT_NONE, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_PARAM_WRAP(NONE): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_PARAM_WRAP(NONE): Wrong currline\n" );
    CHECK( pos.x != SECOND_X,
           Errors,
           "MOVE_PARAM_WRAP(NONE): Wrong x\n" );

    CHECK( CV_MOVE_PARAM_WRAP( pos, CV_SHIFT_LEFT, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        (SECOND_X - 1) * PLANS,
           Errors,
           "MOVE_PARAM_WRAP(LEFT): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_PARAM_WRAP(LEFT): Wrong currline\n" );
    CHECK( pos.x != SECOND_X - 1,
           Errors,
           "MOVE_PARAM_WRAP(LEFT): Wrong x\n" );

    CHECK( CV_MOVE_PARAM_WRAP( pos, CV_SHIFT_RIGHT, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_PARAM_WRAP(RIGHT): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_PARAM_WRAP(RIGHT): Wrong currline\n" );
    CHECK( pos.x != SECOND_X,
           Errors,
           "MOVE_PARAM_WRAP(RIGHT): Wrong x\n" );

    CHECK( CV_MOVE_PARAM_WRAP( pos, CV_SHIFT_UP, PLANS ) != data + 
                                        pos.step * (SECOND_Y - 1) +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_PARAM_WRAP(UP): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * (SECOND_Y - 1),
           Errors,
           "MOVE_PARAM_WRAP(UP): Wrong currline\n" );
    CHECK( pos.x != SECOND_X,
           Errors,
           "MOVE_PARAM_WRAP(UP): Wrong x\n" );

    CHECK( CV_MOVE_PARAM_WRAP( pos, CV_SHIFT_DOWN, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_PARAM_WRAP(DOWN): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_PARAM_WRAP(DOWN): Wrong currline\n" );
    CHECK( pos.x != SECOND_X,
           Errors,
           "MOVE_PARAM_WRAP(DOWN): Wrong x\n" );

    CHECK( CV_MOVE_PARAM_WRAP( pos, CV_SHIFT_LU, PLANS ) != data + 
                                        pos.step * (SECOND_Y - 1) +
                                        (SECOND_X - 1) * PLANS,
           Errors,
           "MOVE_PARAM_WRAP(LU): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * (SECOND_Y - 1),
           Errors,
           "MOVE_PARAM_WRAP(LU): Wrong currline\n" );
    CHECK( pos.x != SECOND_X - 1,
           Errors,
           "MOVE_PARAM_WRAP(LU): Wrong x\n" );

    CHECK( CV_MOVE_PARAM_WRAP( pos, CV_SHIFT_RD, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_PARAM_WRAP(RD): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_PARAM_WRAP(RD): Wrong currline\n" );
    CHECK( pos.x != SECOND_X,
           Errors,
           "MOVE_PARAM_WRAP(RD): Wrong x\n" );

    CHECK( CV_MOVE_PARAM_WRAP( pos, CV_SHIFT_RU, PLANS ) != data + 
                                        pos.step * (SECOND_Y - 1) +
                                        (SECOND_X + 1) * PLANS,
           Errors,
           "MOVE_PARAM_WRAP(RU): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * (SECOND_Y - 1),
           Errors,
           "MOVE_PARAM_WRAP(RU): Wrong currline\n" );
    CHECK( pos.x != SECOND_X + 1,
           Errors,
           "MOVE_PARAM_WRAP(RU): Wrong x\n" );

    CHECK( CV_MOVE_PARAM_WRAP( pos, CV_SHIFT_LD, PLANS ) != data + 
                                        pos.step * SECOND_Y +
                                        SECOND_X * PLANS,
           Errors,
           "MOVE_PARAM_WRAP(LD): Wrong pointer\n" );
    CHECK( pos.currline != data + pos.step * SECOND_Y,
           Errors,
           "MOVE_PARAM_WRAP(LD): Wrong currline\n" );
    CHECK( pos.x != SECOND_X,
           Errors,
           "MOVE_PARAM_WRAP(LD): Wrong x\n" );
    
    icvFree( &data );

    return Errors == 0 ? TRS_OK : trsResult( TRS_FAIL, "Fixed %d error(s)", Errors );

#undef CHECK
