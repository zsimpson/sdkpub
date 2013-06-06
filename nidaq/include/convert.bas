'******************************* convert.bas *******************************
'*
'*   This module contains all the necessary functions, constants, and
'*   polynomial factors to convert voltage read from the following
'*   transducers into the proper units:
'*
'*      Thermocouples (B, E, J, K, N, R, S, and T types)
'*      Thermistors (voltage-excited)
'*      RTDs (current-excited)
'*      Strain gauges
'*         (Qtr Bridge I&II, Half Bridge I&II, Full bridge I&II&III)
'*
'*   For more details, refer to the NI-DAQ User Manual.
'*
'*   (C) Copyright 1996, National Instruments Corp. All rights reserved.
'*
'* -------------------------------------------------------------------------
'*
'*   NOTE: One difference between calling the NI-DAQ functions and calling
'*         these Transducer Conversion functions in Visual Basic is in the
'*         way you pass in an array parameter into a function.
'*
'*         --> For NI-DAQ functions (defined in WDAQ_VB.BAS):
'*
'*               returnCode = NIDAQFunc(a%, b%, c#(0), ...)
'*
'*
'*         --> For Transducer Conversion functions (defined in CONVERT.BAS):
'*
'*               returnCode = ConversionFunc(a%, b%, c#(), ...)
'*
'*         where in both cases, c#() is an array of "doubles".
'*
'*         This is due to the fact that the NI-DAQ interface was written in
'*         C and such array parameters are accepted as a "pointer" of a
'*         specific type.  By passing in the first array entry, you are
'*         virtually passing in the address of that memory location.
'*         On the other hand, the Transducer Conversion functions in this
'*         module have been specifically prototyped to accept "arrays" of a
'*         specific type.
'*
'***************************************************************************
'***************************************************************************
'*
'*   Constant definitions used by the conversion functions
'*
'***************************************************************************
'---------------------------------------------------------------------------
' error codes
Global Const noErr = 0
Global Const invalidTCtype = -1
Global Const invalidBridgeConfig = -2
Global Const invalidRTDconv = -3
Global Const divideByZero = -4
Global Const imaginaryNumber = -5
Global Const invalidTempScale = -6
'---------------------------------------------------------------------------
' NOT DELETED FOR COMPATIBILITY WITH
' VERSIONS OF NIDAQ 4.6.1 and BEFORE
Global Const E = 1
Global Const J = 2
Global Const K = 3
Global Const R = 4
Global Const S = 5
Global Const T = 6
'---------------------------------------------------------------------------
' thermocouple types
Global Const E_TYPE_TC = 1
Global Const J_TYPE_TC = 2
Global Const K_TYPE_TC = 3
Global Const R_TYPE_TC = 4
Global Const S_TYPE_TC = 5
Global Const T_TYPE_TC = 6
Global Const B_TYPE_TC = 7
Global Const N_TYPE_TC = 8
'---------------------------------------------------------------------------
' temperature scales
Global Const CELSIUS = 1
Global Const FAHRENHEIT = 2
Global Const KELVIN = 3
Global Const RANKINE = 4
'---------------------------------------------------------------------------
'strain gauge bridge configurations
Global Const QTR_BRIDGE_I = 0
Global Const QTR_BRIDGE_II = 1
Global Const HALF_BRIDGE_I = 2
Global Const HALF_BRIDGE_II = 3
Global Const FULL_BRIDGE_I = 4
Global Const FULL_BRIDGE_II = 5
Global Const FULL_BRIDGE_III = 6
'---------------------------------------------------------------------------
' RTD conversion type
Global Const DEFAULT_RTD_CONV = 0
'---------------------------------------------------------------------------
' used for another TC type, strain configuration, or RTD conversion
' type to indicate a user defined conversion formula
Global Const USER_DEFINED = -1

'***************************************************************************
'*
'*  Supporting routines for Thermocouple_Buf_Convert function
'*  ----------------------------------------------------------
'*
'*  Supporting Functions
'*  --------------------
'*  * zCompute_equation
'*  * zTemp_to_volts
'*  * zVolts_to_temp
'*  * zChange_temp_scale
'*
'*  Data Structures & Global Variables
'*
'*  polynomial : Data Structure that contains polynomial coeffecients used
'*               by the thermocouple voltage and temperature conversion
'*               functions.
'*
'*  Bpoly_VtoT(2) : Type B thermocouple polynomial for converting a thermocouple
'*                  voltage to an equivalent temperature. The array subscript
'*                  of two indicates that there are two equations that characterize
'*                  B type thermocouples for the entire temperature range.
'*
'*  Bpoly_TtoV(2) : Type B thermocouple polynomial for converting a thermocouple
'*                  temperature to an equivalent voltage. The array subscript
'*                  of two indicates that there are two equations that characterize
'*                  B type thermocouples for the entire temperature range.
'*
'***************************************************************************
Const MAX_COEFF_INDEX = 15
Const MAX_ALPHA_INDEX = 2

' DATA STRUCTURE: Polynomial coefficients
Type Polynomial
   eq_type As Integer                ' Equation Type; for efficient computation
   c(MAX_COEFF_INDEX) As Double      ' polynomial coeffecients array
   alpha(MAX_ALPHA_INDEX) As Double  ' exponential factor used by K_type TCs
End Type

' FLAG: 1 if polynomial structures are initialized
Dim PolyInitFlag  As Integer

'***************************************************************************
'*
'*   Global declarations for the conversion functions
'*
'***************************************************************************
'---------------------------------------------------------------------------
' Voltage to temperature data structures
Dim Bpoly_VtoT(2) As Polynomial
Dim Epoly_VtoT(2) As Polynomial
Dim Jpoly_VtoT(3) As Polynomial
Dim Kpoly_VtoT(2) As Polynomial
Dim Npoly_VtoT(4) As Polynomial
Dim Rpoly_VtoT(4) As Polynomial
Dim Spoly_VtoT(4) As Polynomial
Dim Tpoly_VtoT(2) As Polynomial
'---------------------------------------------------------------------------
' Temperature to Voltagedata structures
Dim Bpoly_TtoV(2) As Polynomial
Dim Epoly_TtoV(2) As Polynomial
Dim Jpoly_TtoV(2) As Polynomial
Dim Kpoly_TtoV(2) As Polynomial
Dim Npoly_TtoV(3) As Polynomial
Dim Rpoly_TtoV(3) As Polynomial
Dim Spoly_TtoV(3) As Polynomial
Dim Tpoly_TtoV(2) As Polynomial
'---------------------------------------------------------------------------

'*************************************************************************
'*
'*   RTD_Buf_Convert
'*
'*      Uses either the formula given below or a user defined formula
'*      to convert a buffer of RTD voltages to resistances and then
'*      to temperatures in Celsius.
'*
'*      A, B, and C are coefficients for the Callendar-Van Dusen
'*      equation for RTD's that gives RTD resistance as a
'*      function of temperature:
'*
'*          Rt = Ro[1 + At + Bt^2 + C(t-100)t^3]
'*          where
'*          Ro = RTD resistance at 0C
'*          A = alpha(1 + delta/100)
'*          B = -alpha*delta/100^2
'*          C = -alpha*beta/100^4
'*
'*      For temperatures above 0C, beta = 0; so the equation reduces to a
'*      quadratic formula for which we have found the appropriate root:
'*      (so this function is only for temperatures above 0C)
'*
'*          Rt = Ro[1 + At + Bt^2]
'*
'*      All the RTD documentation we have found either gives values for
'*      A and B, or for alpha and delta, in which case A and B can be
'*      calculated from the equations given above.  The user must be careful
'*      that the A and B that are passed to the function do not already
'*      incorporate Ro.
'*
'*      The most common RTDs are 100 ohm platinum RTDs that follow the
'*      European Curve (DIN 43760) or the American Curve.  The A and B
'*      coefficients for those two types are given below:
'*
'*      European (DIN 43760 standard - default values on function panel):
'*      A = 3.90802e-03, B = -5.80195e-07  (alpha = 0.00385, delta = 1.492)
'*
'*      American:
'*      A = 3.9784e-03, B = -5.8408e-07  (alpha = 0.00392, delta = 1.492)
'*
'*      The four wire measurement technique should be used for best
'*      results.  In this techique, the RTD resistance can be calculated very
'*      easily from the measured voltage and the excitation current:
'*
'*          Rt = RTDvolts / Iex
'*
'*      Function parameters:
'*      convType - conversion to be used (constant defines given in convert.h)
'*           Iex - excitation current used
'*            Ro - RTD resistance in ohms at 0C
'*         A & B - coefficients to the Callendar Van-Dusen equation above
'*     tempScale - temperature scale of return temperature (C, F, etc)
'*        numPts - number of data points to convert
'*    voltBuffer - buffer of voltages to convert
'*      RTDtemps - return buffer of temperatures in Celsius
'*
'**************************************************************************
Function RTD_Buf_Convert (ByVal convType As Integer, ByVal Iex As Double, ByVal Ro As Double, ByVal a As Double, ByVal b As Double, ByVal TempScale As Integer, ByVal numPts As Integer, voltBuffer() As Double, RTDtemps() As Double) As Integer
    
    Dim i As Integer
    Dim errNum As Integer
    Dim aa As Double
    Dim bb As Double
    Dim cc As Double
    Dim q As Double
    Dim Rt As Double
    Dim argu As Double
    Dim tempTemp As Double
    Dim tempRTD As Double

    ' default excitation current is 150 microAmps
    If (Iex = 0#) Then
        Iex = .00015
    End If

    Select Case convType
    
        Case DEFAULT_RTD_CONV
            ' -------------------------------------------------------------
            ' aa, bb, and cc are the coefficients for the ax^2 + bx + c = 0
            ' form of the equation:  Rt = Ro[1 + At + Bt^2]
            ' -------------------------------------------------------------
            aa = Ro * b
            bb = Ro * a

            For i = 0 To numPts - 1
            
                ' convert voltage to RTD resistance
                Rt = voltBuffer(i) / Iex
                cc = Ro - Rt
                ' method taken from Numerical Recipes; there is another root
                ' (q/aa), but it always comes out an unreasonable number
                argu = (bb * bb - 4# * aa * cc)

                If (argu < 0) Then
                    returnCode = imaginaryNumber
                    GoTo outa_RTD_Buf_Convert
                End If

                q = -.5 * (bb + Sqr(argu))
                tempTemp = (cc / q)
                returnCode = zConvertTemperature(TempScale, tempTemp, RTDtemps(i))
                
                If (returnCode < 0) Then
                    GoTo outa_RTD_Buf_Convert
                End If
            Next

        Case USER_DEFINED
            '
            'put your user defined formula here:
            'for i = 0 to numPts - 1
            '    RTDtemps[i] = .....
            'next
            '
        Case Else
            returnCode = invalidRTDconv

    End Select

outa_RTD_Buf_Convert:

    RTD_Buf_Convert = returnCode

End Function

'**************************************************************************
'*
'*   RTD_Convert
'*
'*   same as RTD_Buf_Convert, but for a single point
'*
'**************************************************************************
Function RTD_Convert (ByVal convType As Integer, ByVal Iex As Double, ByVal Ro As Double, ByVal a As Double, ByVal b As Double, ByVal TempScale As Integer, ByVal RTDvolts As Double, RTDtemp As Double) As Integer
    
    Dim aa As Double
    Dim bb As Double
    Dim cc As Double
    Dim q As Double
    Dim Rt As Double
    Dim argu As Double
    Dim tempTemp As Double
    Dim returnCode As Integer

    returnCode = noErr
    RTDtemp = 0#

    ' default excitation current is 150 microAmps
    If (Iex = 0#) Then
        Iex = .00015
    End If

    Select Case convType
    
        Case DEFAULT_RTD_CONV
            '---------------------------------------------------------------
            ' aa, bb, and cc are the coefficients for the ax^2 + bx + c = 0
            ' form of the equation:  Rt = Ro[1 + At + Bt^2]
            '---------------------------------------------------------------
            aa = Ro * b
            bb = Ro * a
            'convert voltage to RTD resistance
            Rt = RTDvolts / Iex
            cc = Ro - Rt
            ' method taken from Numerical Recipes; there is another root
            ' (q/aa), but it always comes out an unreasonable number
            argu = (bb * bb - 4# * aa * cc)
            
            If argu < 0 Then
                returnCode = imaginaryNumber
                GoTo outa_RTD_Convert
            End If

            q = -.5 * (bb + Sqr(argu))
            tempTemp = cc / q
            returnCode = zConvertTemperature(TempScale, tempTemp, RTDtemp)

        Case USER_DEFINED
            '
            ' put your user defined formula here:
            '    RTDtemp = .....
            '
            
        Case Else
            returnCode = invalidRTDconv

    End Select

outa_RTD_Convert:

    RTD_Convert = returnCode


End Function

'*************************************************************************
'*
'*  Strain_Buf_Convert
'*
'*    Converts a buffer of strain gauge voltages to strain values using
'*    the formula appropriate for the given bridge configuration.
'*
'*    bridgeConfig - code indicating the strain gauge bridge configuration
'*                   used (constant defines given in convert.h)
'*             Vex - excitation voltage used
'*              GF - gauge factor
'*               v - Poisson's ratio (if applicable)
'*              Rg - strain gauge nominal value
'*              Rl - lead resistance
'*           Vinit - initial unstrained voltage of the strain gauge after
'*                   mounting in the configuration
'*          numPts - number of data points to be converted
'*      voltBuffer - buffer of strain gauge voltages to be converted
'*      strainVals - return buffer of strain values
'*
'**************************************************************************
Function Strain_Buf_Convert (ByVal bridgeConfig As Integer, ByVal Vex As Double, ByVal GF As Double, ByVal v As Double, ByVal Rg As Double, ByVal Rl As Double, ByVal Vinit As Double, ByVal numPts As Integer, voltBuffer() As Double, strainVals() As Double) As Integer
    
    Dim i As Integer
    Dim Vr As Double
    Dim temp1 As Double
    Dim temp2 As Double
    Dim returnCode As Integer

    returnCode = noErr

    ' default excitation voltage is 3.333V
    If (Vex = 0#) Then
        Vex = 3.333
    End If
    
    If (GF = 0) Then
        returnCode = divideByZero
        GoTo outa_Strain_Buf_Convert
    End If
    
    ' -------------------------------
    '  for all bridge configurations:
    '     Vr = (V - Vinit) / Vex
    ' -------------------------------
    Select Case bridgeConfig
    
        Case QTR_BRIDGE_I, QTR_BRIDGE_II
            ' -------------------------------------------
            '  strain = -4Vr / [GF(1+2Vr)] * (1 + Rl/Rg)
            ' -------------------------------------------
            If (Rg = 0) Then
                returnCode = divideByZero
                GoTo outa_Strain_Buf_Convert
            End If

            temp1 = -4# / GF * (1# + Rl / Rg)

            For i = 0 To numPts - 1
            
                Vr = (voltBuffer(i) - Vinit) / Vex
                temp2 = 1# + 2# * Vr

                If (temp2 = 0) Then
                    returnCode = divideByZero
                    GoTo outa_Strain_Buf_Convert
                End If

                strainVals(i) = Vr / temp2 * temp1
            Next
            
        Case HALF_BRIDGE_I
            ' ----------------------------------------------------
            '  strain = -4Vr / [GF[(1+v)-2Vr(v-1)]] * (1 + Rl/Rg)
            ' ----------------------------------------------------
            If (Rg = 0) Then
                returnCode = divideByZero
                GoTo outa_Strain_Buf_Convert
            End If

            temp1 = -4# / GF * (1# + Rl / Rg)
            For i = 0 To numPts - 1
            
                Vr = (voltBuffer(i) - Vinit) / Vex
                temp2 = (1# + v) - 2# * Vr * (v - 1#)
                If (temp2 = 0) Then
                    returnCode = divideByZero
                    GoTo outa_Strain_Buf_Convert
                End If

                strainVals(i) = Vr / temp2 * temp1
            Next
            
        Case HALF_BRIDGE_II
            ' ----------------------------------
            '  strain = -2Vr / GF * (1 + Rl/Rg)
            ' ----------------------------------
            If (Rg = 0) Then
                returnCode = divideByZero
                GoTo outa_Strain_Buf_Convert
            End If

            temp1 = -2# / GF * (1# + Rl / Rg)
            For i = 0 To numPts - 1
            
                Vr = (voltBuffer(i) - Vinit) / Vex
                strainVals(i) = Vr * temp1

            Next
            
        Case FULL_BRIDGE_I
            ' -------------------
            '  strain = -Vr / GF
            ' -------------------
            For i = 0 To numPts - 1
                Vr = (voltBuffer(i) - Vinit) / Vex
                strainVals(i) = -1# * Vr / GF
            Next
            
        Case FULL_BRIDGE_II
            ' -------------------------
            '  strain = -2Vr / GF(v+1)
            ' -------------------------
            If (v = -1#) Then
                returnCode = divideByZero
                GoTo outa_Strain_Buf_Convert
            End If

            temp1 = -2# / GF * (1# + v)
            For i = 0 To numPts - 1
                Vr = (voltBuffer(i) - Vinit) / Vex
                strainVals(i) = Vr * temp1
            Next
            
        Case FULL_BRIDGE_III
            ' -------------------------------------
            '  strain = -2Vr / [GF[(v+1)-Vr(v-1)]]
            ' -------------------------------------
            temp1 = -2# / GF
            For i = 0 To numPts - 1
                Vr = (voltBuffer(i) - Vinit) / Vex
                temp2 = (v + 1#) - Vr * (v - 1#)
                If (temp2 = 0) Then
                    returnCode = divideByZero
                    GoTo outa_Strain_Buf_Convert
                End If

                strainVals(i) = Vr / temp2 * temp1
            Next
            
        Case USER_DEFINED
            '
            ' put your user defined formula here:
            ' for i = 0 to numPts - 1
            '    strainVals(i) = .....
            ' next
            '
        
        Case Else
            returnCode = invalidBridgeConfig

    End Select

outa_Strain_Buf_Convert:

    Strain_Buf_Convert = returnCode

End Function

'*************************************************************************
'*
'*  Strain_Convert
'*
'*  same as Strain_Buf_Convert, but for single point
'*
'**************************************************************************
Function Strain_Convert (ByVal bridgeConfig As Integer, ByVal Vex As Double, ByVal GF As Double, ByVal v As Double, ByVal Rg As Double, ByVal Rl As Double, ByVal Vinit As Double, ByVal strainVolts As Double, strainVal As Double) As Integer

    Dim Vr As Double
    Dim temp1 As Double
    Dim returnCode As Integer

    strainVal = 0#

    ' default excitation voltage is 3.333V
    If (Vex = 0#) Then
        Vex = 3.333
    End If

    If (GF = 0) Then
        returnCode = divideByZero
        GoTo outa_Strain_Convert
    End If

    ' -------------------------------
    '  for all bridge configurations:
    '     Vr = (V - Vinit) / Vex
    ' -------------------------------
    Vr = (strainVolts - Vinit) / Vex

    Select Case bridgeConfig
    
        Case QTR_BRIDGE_I, QTR_BRIDGE_II
            ' -------------------------------------------
            '  strain = -4Vr / [GF(1+2Vr)] * (1 + Rl/Rg)
            ' -------------------------------------------
            If (Rg = 0) Then
                returnCode = divideByZero
                GoTo outa_Strain_Convert
            End If

            temp1 = 1# + 2# * Vr

            If (temp1 = 0) Then
                returnCode = divideByZero
                GoTo outa_Strain_Convert
            End If

            strainVal = -4# * Vr / (GF * temp1) * (1# + Rl / Rg)
            
        Case HALF_BRIDGE_I
            ' ----------------------------------------------------
            '  strain = -4Vr / [GF[(1+v)-2Vr(v-1)]] * (1 + Rl/Rg)
            ' ----------------------------------------------------
            If (Rg = 0) Then
                returnCode = divideByZero
                GoTo outa_Strain_Convert
            End If

            temp1 = (1# + v) - 2# * Vr * (v - 1#)

            If (temp1 = 0) Then
                returnCode = divideByZero
                GoTo outa_Strain_Convert
            End If
            strainVal = -4# * Vr / (GF * temp1) * (1# + Rl / Rg)
            
        Case HALF_BRIDGE_II
            ' ----------------------------------
            '  strain = -2Vr / GF * (1 + Rl/Rg)
            ' ----------------------------------
            If (Rg = 0) Then
                returnCode = divideByZero
                GoTo outa_Strain_Convert
            End If

            strainVal = -2# * Vr / GF * (1# + Rl / Rg)
            
        Case FULL_BRIDGE_I
            ' -------------------
            '  strain = -Vr / GF
            ' -------------------
            strainVal = -1# * Vr / GF
            
        Case FULL_BRIDGE_II
            ' -------------------------
            '  strain = -2Vr / GF(v+1)
            ' -------------------------
            If (v = -1#) Then
                returnCode = divideByZero
                GoTo outa_Strain_Convert
            End If

            strainVal = -2# * Vr / (GF * (1# + v))
            
        Case FULL_BRIDGE_III
            ' -------------------------------------
            '  strain = -2Vr / [GF[(v+1)-Vr(v-1)]]
            ' -------------------------------------
            temp1 = (v + 1#) - Vr * (v - 1#)
            If (temp1 = 0) Then
                returnCode = divideByZero
                GoTo outa_Strain_Convert
            End If

            strainVal = -2# * Vr / (GF * temp1)

        Case USER_DEFINED:
            '
            ' put your user defined formula here:
            ' strainVal = .....
            '
            
        Case Else
            returnCode = invalidBridgeConfig

    End Select

outa_Strain_Convert:

    Strain_Convert = returnCode


End Function

'*************************************************************************
'*  Thermistor_Buf_Convert
'*
'*      Uses the formula given below
'*      to convert a buffer of Thermistor voltages to resistances and then
'*      calls the function Rt_to_Temp to convert them to temperatures. Use
'*      this function when the thermistor is connected to a voltage
'*      reference (Vref) with a series resistor (R1). Volts is the voltage
'*      across the thermistor.
'*
'*          Rt = R1 * (Volts / (Vref- Volts))
'*          where
'*          Rt = Themistor resistance in ohms
'*
'**************************************************************************/
Function Thermistor_Buf_Convert (ByVal R1 As Double, ByVal Vref As Double, ByVal numPts As Integer, VoltBuf() As Double, ByVal TempScale As Integer, TempBuf() As Double) As Integer

   Dim i As Integer
   Dim Rt As Double
   Dim logRt As Double
   Dim logRtCubed As Double
   Dim returnCode As Integer

   returnCode = noErr
   
    For i = 0 To numPts - 1
   
        If Vref = VoltBuf(i) Then
            returnCode = divideByZero
            GoTo outa_Thermistor_Buf_Convert
        End If

        Rt = R1 * (VoltBuf(i) / (Vref - VoltBuf(i)))

        status = zRt_to_Temp(Rt, TempBuf(i), TempScale)

        If status <> 0 Then
           returnCode = status
           GoTo outa_Thermistor_Buf_Convert
        End If
    Next


outa_Thermistor_Buf_Convert:

    Thermistor_Buf_Convert = returnCode


End Function

'*************************************************************************
'*  Thermistor_Convert
'*
'*      Uses the Thermistor_Buf_Convert function to convert a voltage
'*      to thermistor resistance and then to a temperature.
'*
'**************************************************************************
Function Thermistor_Convert (ByVal R1 As Double, ByVal Vref As Double, ByVal Volts As Double, ByVal TempScale As Integer, temperature As Double) As Integer
   
   ReDim arrVolts#(1)
   ReDim arrTemp#(1)
   
   arrVolts#(0) = Volts
   arrTemp#(0) = temperature

   Thermistor_Convert = Thermistor_Buf_Convert(R1, Vref, 1, arrVolts#(), TempScale, arrTemp#())
   temperature = arrTemp#(0)

End Function

'*************************************************************************
'*  Thermistor_CrntSrc_Buf_Convert
'*
'*      Uses the formula given below
'*      to convert a buffer of Thermistor voltages to resistances and then
'*      calls the function zRt_to_Temp to convert them to temperatures. Use
'*      this function when the thermistor is connected to a current source
'*      of Iex Amps. Volts is the voltage across the thermistor.
'*
'*          Rt = Volts / Current
'*          where
'*          Rt = Themistor resistance in ohms
'*
'**************************************************************************
Function Thermistor_CrntSrc_Buf_Convert (ByVal Iex As Double, ByVal numPts As Long, VoltBuf() As Double, ByVal TempScale As Integer, TempBuf() As Double) As Integer

  Dim i As Long
  Dim Rt As Double
  Dim status As Integer
  Dim returnCode As Integer

  returnCode = noErr
  
  For i = 0 To numPts - 1
      If Iex = 0# Then
          returnCode = divideByZero
          GoTo outa_Thermistor_CrntSrc_Buf_Convert
      End If
      
      Rt = VoltBuf#(i) / Iex

      status = zRt_to_Temp(Rt, TempBuf#(i), TempScale)
      If status <> 0 Then
          returnCode = status
          GoTo outa_Thermistor_CrntSrc_Buf_Convert
      End If
  Next i
  
outa_Thermistor_CrntSrc_Buf_Convert:

  Thermistor_CrntSrc_Buf_Convert = returnCode

End Function

'*************************************************************************
'*  Thermistor_CrntSrc_Convert
'*
'*      Uses the Thermistor_CrntSrc_Buf_Convert function to convert a voltage
'*      to thermistor resistance and then to a temperature. This version is
'*      used for current excited thermistor
'*
'**************************************************************************
Function Thermistor_CrntSrc_Convert (ByVal Iex As Double, ByVal Volts As Double, ByVal TempScale As Integer, temperature As Double) As Integer
  ReDim arrVolts#(1)
  ReDim arrTemp#(1)
   
  arrVolts#(0) = Volts
  arrTemp#(0) = temperature
   
  Thermistor_CrntSrc_Convert = Thermistor_CrntSrc_Buf_Convert(Iex, 1, arrVolts#(), TempScale, arrTemp#())
  temperature = arrTemp#(0)
  
End Function

'*************************************************************************
'*
'*  Thermocouple_Buf_Convert
'*
'*    Converts a buffer of thermocouple voltages to temperatures
'*    using the formula appropriate for the given thermocouple type.
'*
'*      TCtype - the thermocouple type (constant defines in convert.h)
'*     CJCtemp - temperature (in Celsius) to be used for cold-junction
'*               compensation
'*   tempScale - code for temperature scale (constant defines in convert.h)
'*      numPts - number of points to convert
'*    TCbuffer - buffer of thermocouple voltages in volts
'*     TCtemps - return buffer of temperatures in Celsius
'*
'**************************************************************************
Function Thermocouple_Buf_Convert (ByVal TCtype As Integer, ByVal CJCtemp As Double, ByVal TempScale As Integer, ByVal numPts As Long, TCbuffer#(), TCtemps#()) As Integer

    Dim i As Long
    Dim CJCvolts As Double
    Dim returnCode As Integer


    returnCode = noErr

    ' see if polynomials have been initialized yet
    If (PolyInitFlag = 0) Then
        Call zInitialize_Polynomials
    End If

    '
    ' Convert the cold junction temperature into an thermocouple equivalent
    ' voltage using the NIST standard.
    '

    returnCode = zTemp_to_volts(TCtype, CJCtemp, CJCvolts)

    If returnCode = invalidTCtype Then
        GoTo outa_Thermocouple_Buf_Convert
    End If

    For i = 0 To numPts - 1
    
        returnCode = zVolts_to_temp(TCtype, TCbuffer#(i) + CJCvolts, TCtemps#(i))
        If returnCode = invalidTCtype Then
            GoTo outa_Thermocouple_Buf_Convert
        End If

        If (TempScale <> CELSIUS) Then
            returnCode = zChange_temp_scale(TempScale, TCtemps#(i))
            If returnCode = invalidTempScale Then
                GoTo outa_Thermocouple_Buf_Convert
            End If
        End If

    Next

outa_Thermocouple_Buf_Convert:
    Thermocouple_Buf_Convert = returnCode


End Function

'*************************************************************************
'*
'*  Thermocouple_Convert
'*
'*      Uses the Thermocouple_Buf_Convert function to convert a thermocouple
'*      voltage to temperature
'*
'**************************************************************************/
Function Thermocouple_Convert (ByVal TCtype As Integer, ByVal CJCtemp As Double, ByVal TempScale As Double, ByVal TCvolts As Double, TCtemp As Double) As Integer

   ReDim arrTCvolts#(1)
   ReDim arrTCtemp#(1)
   arrTCvolts#(0) = TCvolts
   arrTCtemp#(0) = TCtemp
   
   Thermocouple_Convert = Thermocouple_Buf_Convert(TCtype, CJCtemp, TempScale, 1, arrTCvolts#(), arrTCtemp#())
   
   TCtemp = arrTCtemp#(0)

End Function

'*************************************************************************
'*
'*  zChange_temp_scale
'*
'*
'*    FUNCTION:
'*    Converts a temperature in degree's centigrade into another valid
'*    scale. The allowed units of temperature are KELVIN, FAHRENHEIT and RANKINE.
'*
'*
'*    INPUTS:
'*    TempScale   : The units to which the temperature is to be converted.
'*    temperature : Temperature in degree's Celsius.
'*
'*
'*    OUTPUTS:
'*    temperature : The temperature in the new units.
'*                  Returns an error if an invalid Temp_Scale is specified.
'*
'*
'**************************************************************************/
Function zChange_temp_scale (ByVal TempScale As Integer, temperature As Double) As Integer
  
    zChange_temp_scale = noErr

    Select Case TempScale
        Case CELSIUS
              temperature = temperature

        Case KELVIN
              temperature = temperature + 273.15
              
        Case FAHRENHEIT
              temperature = temperature * 1.8 + 32#
              
        Case RANKINE
              temperature = temperature * 1.8 + 491.67

        Case Else
              zChange_temp_scale = invalidTempScale

    End Select

End Function

'*************************************************************************
'*   zCompute_equation
'*
'*   FUNCTION:
'*    Evaluates a polynomial equation.
'*
'*   INPUTS:
'*    poly1    : Structure that holds the polynomial coeffecients and the
'*               equation type to be evaluated.
'*    inputVal : Input variable to be used to evaluate the polynomial.
'*
'*   OUTPUTS:
'*    outputVal: Contains the value of the evaluated polynomial. It is a
'*               call by reference parameter.
'*
'**************************************************************************/
Function zCompute_equation (poly1 As Polynomial, ByVal inputVal As Double, outputVal As Double) As Integer

    Dim tempVal0 As Double
    Dim tempVal1 As Double
    Dim tempVal2 As Double
    Dim tempVal3 As Double
    Dim tempAlpha As Double

    Select Case poly1.eq_type

        Case 4
            outputVal = poly1.c(0) + inputVal * (poly1.c(1) + inputVal * (poly1.c(2) + inputVal * (poly1.c(3) + inputVal * poly1.c(4))))
           
        Case 5
            outputVal = poly1.c(0) + inputVal * (poly1.c(1) + inputVal * (poly1.c(2) + inputVal * (poly1.c(3) + inputVal * (poly1.c(4) + inputVal * poly1.c(5)))))
        
        Case 6
            tempVal0 = poly1.c(3) + inputVal * (poly1.c(4) + inputVal * (poly1.c(5) + inputVal * poly1.c(6)))
            outputVal = poly1.c(0) + inputVal * (poly1.c(1) + inputVal * (poly1.c(2) + inputVal * tempVal0))
            
        Case 7
            tempVal0 = poly1.c(6) + inputVal * poly1.c(7)
            tempVal1 = poly1.c(3) + inputVal * (poly1.c(4) + inputVal * (poly1.c(5) + inputVal * tempVal0))
            outputVal = poly1.c(0) + inputVal * (poly1.c(1) + inputVal * (poly1.c(2) + inputVal * tempVal1))
            
        Case 8
            tempVal0 = poly1.c(6) + inputVal * (poly1.c(7) + inputVal * poly1.c(8))
            tempVal1 = poly1.c(3) + inputVal * (poly1.c(4) + inputVal * (poly1.c(5) + inputVal * tempVal0))
            outputVal = poly1.c(0) + inputVal * (poly1.c(1) + inputVal * (poly1.c(2) + inputVal * tempVal1))
            
        Case 9
            tempVal0 = poly1.c(6) + inputVal * (poly1.c(7) + inputVal * (poly1.c(8) + inputVal * poly1.c(9)))
            tempVal1 = poly1.c(3) + inputVal * (poly1.c(4) + inputVal * (poly1.c(5) + inputVal * tempVal0))
            outputVal = poly1.c(0) + inputVal * (poly1.c(1) + inputVal * (poly1.c(2) + inputVal * tempVal1))
           
        Case 10
            tempVal0 = poly1.c(9) + inputVal * poly1.c(10)
            tempVal1 = poly1.c(6) + inputVal * (poly1.c(7) + inputVal * (poly1.c(8) + inputVal * tempVal0))
            tempVal2 = poly1.c(3) + inputVal * (poly1.c(4) + inputVal * (poly1.c(5) + inputVal * tempVal1))
            outputVal = poly1.c(0) + inputVal * (poly1.c(1) + inputVal * (poly1.c(2) + inputVal * tempVal2))
            
        Case 13
            tempVal0 = poly1.c(12) + inputVal * poly1.c(13)
            tempVal1 = poly1.c(9) + inputVal * (poly1.c(10) + inputVal * (poly1.c(11) + inputVal * tempVal0))
            tempVal2 = poly1.c(6) + inputVal * (poly1.c(7) + inputVal * (poly1.c(8) + inputVal * tempVal1))
            tempVal3 = poly1.c(3) + inputVal * (poly1.c(4) + inputVal * (poly1.c(5) + inputVal * tempVal2))
            outputVal = poly1.c(0) + inputVal * (poly1.c(1) + inputVal * (poly1.c(2) + inputVal * tempVal3))
            
        Case 14
            tempVal0 = poly1.c(12) + inputVal * (poly1.c(13) + inputVal * poly1.c(14))
            tempVal1 = poly1.c(9) + inputVal * (poly1.c(10) + inputVal * (poly1.c(11) + inputVal * tempVal0))
            tempVal2 = poly1.c(6) + inputVal * (poly1.c(7) + inputVal * (poly1.c(8) + inputVal * tempVal1))
            tempVal3 = poly1.c(3) + inputVal * (poly1.c(4) + inputVal * (poly1.c(5) + inputVal * tempVal2))
            outputVal = poly1.c(0) + inputVal * (poly1.c(1) + inputVal * (poly1.c(2) + inputVal * tempVal3))
            
        Case 100   ' check this
            tempAlpha = poly1.alpha(0) * (2.718281828 ^ (poly1.alpha(1) * (inputVal - 126.9686) * (inputVal - 126.9686)))
            tempVal0 = poly1.c(6) + inputVal * (poly1.c(7) + inputVal * (poly1.c(8) + inputVal * poly1.c(9)))
            tempVal1 = poly1.c(3) + inputVal * (poly1.c(4) + inputVal * (poly1.c(5) + inputVal * tempVal0))
            outputVal = tempAlpha + poly1.c(0) + inputVal * (poly1.c(1) + inputVal * (poly1.c(2) + inputVal * tempVal1))
            
        Case Else   ' check this
            tempAlpha = poly1.alpha(0) * (2.718281828 ^ ((poly1.alpha(1) * (inputVal - 126.9686)) ^ 2#))
            tempVal0 = poly1.c(12) + inputVal * (poly1.c(13) + inputVal * poly1.c(14))
            tempVal1 = poly1.c(9) + inputVal * (poly1.c(10) + inputVal * (poly1.c(11) + inputVal * tempVal0))
            tempVal2 = poly1.c(6) + inputVal * (poly1.c(7) + inputVal * (poly1.c(8) + inputVal * tempVal1))
            tempVal3 = poly1.c(3) + inputVal * (poly1.c(4) + inputVal * (poly1.c(5) + inputVal * tempVal2))
            outputVal = tempAlpha + poly1.c(0) + inputVal * (poly1.c(1) + inputVal * (poly1.c(2) + inputVal * tempVal3))
           
    End Select

    zCompute_equation = noErr

End Function

' internal utility routine to convert a temperature from Celsius to
' another temperature scale
Function zConvertTemperature (ByVal TempScale As Integer, ByVal celsiusTemp As Double, newTemp As Double) As Integer
    
    Dim returnCode As Integer
    
    returnCode = noErr

    Select Case TempScale
        Case CELSIUS
            newTemp = celsiusTemp
                
        Case KELVIN
            newTemp = celsiusTemp + 273.15
            
        Case FAHRENHEIT
            newTemp = celsiusTemp * 1.8 + 32#
        
        Case RANKINE
            newTemp = celsiusTemp * 1.8 + 491.67
            
        Case Else
            returnCode = invalidTempScale

    End Select

    zConvertTemperature = returnCode

End Function

Sub zInitialize_Polynomials ()
    
    Dim i As Integer

    ' check if polynomials have never been initialized
    If (PolyInitFlag = 0) Then
        ' set flag so that no more initialzation is needed
        PolyInitFlag = 1

        ' initialize coefficients with 0
        For i = 0 To MAX_COEFF_INDEX - 1
            Bpoly_VtoT(0).c(i) = 0#: Bpoly_VtoT(1).c(i) = 0#
            Epoly_VtoT(0).c(i) = 0#: Epoly_VtoT(1).c(i) = 0#
            Jpoly_VtoT(0).c(i) = 0#: Jpoly_VtoT(1).c(i) = 0#: Jpoly_VtoT(2).c(i) = 0#
            Kpoly_VtoT(0).c(i) = 0#: Kpoly_VtoT(1).c(i) = 0#: Kpoly_VtoT(2).c(i) = 0#
            Npoly_VtoT(0).c(i) = 0#: Npoly_VtoT(1).c(i) = 0#: Npoly_VtoT(2).c(i) = 0#: Npoly_VtoT(3).c(i) = 0#
            Rpoly_VtoT(0).c(i) = 0#: Rpoly_VtoT(1).c(i) = 0#: Rpoly_VtoT(2).c(i) = 0#: Rpoly_VtoT(3).c(i) = 0#
            Spoly_VtoT(0).c(i) = 0#: Spoly_VtoT(1).c(i) = 0#: Spoly_VtoT(2).c(i) = 0#: Spoly_VtoT(3).c(i) = 0#
            Tpoly_VtoT(0).c(i) = 0#: Tpoly_VtoT(1).c(i) = 0#

            Bpoly_TtoV(0).c(i) = 0#: Bpoly_TtoV(1).c(i) = 0#
            Epoly_TtoV(0).c(i) = 0#: Epoly_TtoV(1).c(i) = 0#
            Jpoly_TtoV(0).c(i) = 0#: Jpoly_TtoV(1).c(i) = 0#
            Kpoly_TtoV(0).c(i) = 0#: Kpoly_TtoV(1).c(i) = 0#
            Npoly_TtoV(0).c(i) = 0#: Npoly_TtoV(1).c(i) = 0#
            Rpoly_TtoV(0).c(i) = 0#: Rpoly_TtoV(1).c(i) = 0#: Rpoly_TtoV(2).c(i) = 0#
            Spoly_TtoV(0).c(i) = 0#: Spoly_TtoV(1).c(i) = 0#: Spoly_TtoV(2).c(i) = 0#
            Tpoly_TtoV(0).c(i) = 0#: Tpoly_TtoV(1).c(i) = 0#
        Next i
        
        ' initialize alpha factors with 0
        ' this is really only for K-type TCs when doing TtoV
        For i = 0 To MAX_ALPHA_INDEX - 1
            Bpoly_VtoT(0).alpha(i) = 0#: Bpoly_VtoT(1).alpha(i) = 0#
            Epoly_VtoT(0).alpha(i) = 0#: Epoly_VtoT(1).alpha(i) = 0#
            Jpoly_VtoT(0).alpha(i) = 0#: Jpoly_VtoT(1).alpha(i) = 0#: Jpoly_VtoT(2).alpha(i) = 0#
            Kpoly_VtoT(0).alpha(i) = 0#: Kpoly_VtoT(1).alpha(i) = 0#: Kpoly_VtoT(2).alpha(i) = 0#
            Npoly_VtoT(0).alpha(i) = 0#: Npoly_VtoT(1).alpha(i) = 0#: Npoly_VtoT(2).alpha(i) = 0#: Npoly_VtoT(3).alpha(i) = 0#
            Rpoly_VtoT(0).alpha(i) = 0#: Rpoly_VtoT(1).alpha(i) = 0#: Rpoly_VtoT(2).alpha(i) = 0#: Rpoly_VtoT(3).alpha(i) = 0#
            Spoly_VtoT(0).alpha(i) = 0#: Spoly_VtoT(1).alpha(i) = 0#: Spoly_VtoT(2).alpha(i) = 0#: Spoly_VtoT(3).alpha(i) = 0#
            Tpoly_VtoT(0).alpha(i) = 0#: Tpoly_VtoT(1).alpha(i) = 0#
            
            Bpoly_TtoV(0).alpha(i) = 0#: Bpoly_TtoV(1).alpha(i) = 0#
            Epoly_TtoV(0).alpha(i) = 0#: Epoly_TtoV(1).alpha(i) = 0#
            Jpoly_TtoV(0).alpha(i) = 0#: Jpoly_TtoV(1).alpha(i) = 0#
            Kpoly_TtoV(0).alpha(i) = 0#: Kpoly_TtoV(1).alpha(i) = 0#
            Npoly_TtoV(0).alpha(i) = 0#: Npoly_TtoV(1).alpha(i) = 0#
            Rpoly_TtoV(0).alpha(i) = 0#: Rpoly_TtoV(1).alpha(i) = 0#: Rpoly_TtoV(2).alpha(i) = 0#
            Spoly_TtoV(0).alpha(i) = 0#: Spoly_TtoV(1).alpha(i) = 0#: Spoly_TtoV(2).alpha(i) = 0#
            Tpoly_TtoV(0).alpha(i) = 0#: Tpoly_TtoV(1).alpha(i) = 0#
        
        Next i

        ' ----------------------------------------
        ' Setting the VtoT coefficients
        ' ----------------------------------------
        ' B Type TC VtoT(0): TempRange -50 to 250
        Bpoly_VtoT(0).eq_type = 8
        Bpoly_VtoT(0).c(0) = 98.423321
        Bpoly_VtoT(0).c(1) = .699715
        Bpoly_VtoT(0).c(2) = -.00084765304
        Bpoly_VtoT(0).c(3) = .000001005264
        Bpoly_VtoT(0).c(4) = -8.3345952E-10
        Bpoly_VtoT(0).c(5) = 4.5508542E-13
        Bpoly_VtoT(0).c(6) = -1.5523037E-16
        Bpoly_VtoT(0).c(7) = 2.988675E-20
        Bpoly_VtoT(0).c(8) = -2.474286E-24
        ' ----------------------------------------
        ' B Type TC VtoT(1): TempRange 700 to 1820
        Bpoly_VtoT(1).eq_type = 8
        Bpoly_VtoT(1).c(0) = 213.5071
        Bpoly_VtoT(1).c(1) = .28510504
        Bpoly_VtoT(1).c(2) = -.000052742887
        Bpoly_VtoT(1).c(3) = 9.9160804E-09
        Bpoly_VtoT(1).c(4) = -1.2965303E-12
        Bpoly_VtoT(1).c(5) = 1.119587E-16
        Bpoly_VtoT(1).c(6) = -6.0625199E-21
        Bpoly_VtoT(1).c(7) = 1.8661696E-25
        Bpoly_VtoT(1).c(8) = -2.4878585E-30
        ' ----------------------------------------
        ' E Type VtoT(0): TempRange -200 to 0
        Epoly_VtoT(0).eq_type = 8
        Epoly_VtoT(0).c(0) = 0#
        Epoly_VtoT(0).c(1) = .016977288
        Epoly_VtoT(0).c(2) = -.0000004351497
        Epoly_VtoT(0).c(3) = -1.5859697E-10
        Epoly_VtoT(0).c(4) = -9.2502871E-14
        Epoly_VtoT(0).c(5) = -2.6084314E-17
        Epoly_VtoT(0).c(6) = -4.1360199E-21
        Epoly_VtoT(0).c(7) = -3.403403E-25
        Epoly_VtoT(0).c(8) = -1.156489E-29
        ' ----------------------------------------
        ' E Type VtoT(1): TempRange 0 to 1000
        Epoly_VtoT(1).eq_type = 9
        Epoly_VtoT(1).c(0) = 0#
        Epoly_VtoT(1).c(1) = .017057035
        Epoly_VtoT(1).c(2) = -.00000023301759
        Epoly_VtoT(1).c(3) = 6.5435585E-12
        Epoly_VtoT(1).c(4) = -7.3562749E-17
        Epoly_VtoT(1).c(5) = -1.7896001E-21
        Epoly_VtoT(1).c(6) = 8.4036165E-26
        Epoly_VtoT(1).c(7) = -1.3735879E-30
        Epoly_VtoT(1).c(8) = 1.0629823E-35
        Epoly_VtoT(1).c(9) = -3.2447087E-41
        ' ----------------------------------------
        ' J Type VtoT(0): TempRange -210 to 0
        Jpoly_VtoT(0).eq_type = 8
        Jpoly_VtoT(0).c(0) = 0#
        Jpoly_VtoT(0).c(1) = .019528268
        Jpoly_VtoT(0).c(2) = -.0000012286185
        Jpoly_VtoT(0).c(3) = -1.0752178E-09
        Jpoly_VtoT(0).c(4) = -5.9086933E-13
        Jpoly_VtoT(0).c(5) = -1.7256713E-16
        Jpoly_VtoT(0).c(6) = -2.8131513E-20
        Jpoly_VtoT(0).c(7) = -2.396337E-24
        Jpoly_VtoT(0).c(8) = -8.3823321E-29
        ' ----------------------------------------
        ' J Type VtoT(1): TempRange 0 to 760
        Jpoly_VtoT(1).eq_type = 7
        Jpoly_VtoT(1).c(0) = 0#
        Jpoly_VtoT(1).c(1) = .01978425
        Jpoly_VtoT(1).c(2) = -.0000002001204
        Jpoly_VtoT(1).c(3) = 1.036969E-11
        Jpoly_VtoT(1).c(4) = -2.549687E-16
        Jpoly_VtoT(1).c(5) = 3.585153E-21
        Jpoly_VtoT(1).c(6) = -5.344285E-26
        Jpoly_VtoT(1).c(7) = 5.09989E-31
        ' ----------------------------------------
        ' J Type VtoT(2): TempRange 760 to 1200
        Jpoly_VtoT(2).eq_type = 5
        Jpoly_VtoT(2).c(0) = -3113.58187
        Jpoly_VtoT(2).c(1) = .300543684
        Jpoly_VtoT(2).c(2) = -.0000099477323
        Jpoly_VtoT(2).c(3) = 1.7027663E-10
        Jpoly_VtoT(2).c(4) = -1.43033468E-15
        Jpoly_VtoT(2).c(5) = 4.73886084E-21
        ' ----------------------------------------
        ' K Type VtoT(0): TempRange -200 to 0
        Kpoly_VtoT(0).eq_type = 8
        Kpoly_VtoT(0).c(0) = 0#
        Kpoly_VtoT(0).c(1) = .025173462
        Kpoly_VtoT(0).c(2) = -.0000011662878
        Kpoly_VtoT(0).c(3) = -1.0833638E-09
        Kpoly_VtoT(0).c(4) = -8.977354E-13
        Kpoly_VtoT(0).c(5) = -3.7342377E-16
        Kpoly_VtoT(0).c(6) = -8.6632643E-20
        Kpoly_VtoT(0).c(7) = -1.0450598E-23
        Kpoly_VtoT(0).c(8) = -5.1920577E-28
        ' ----------------------------------------
        ' K Type VtoT(1): TempRange 0 to 500
        Kpoly_VtoT(1).eq_type = 9
        Kpoly_VtoT(1).c(0) = 0#
        Kpoly_VtoT(1).c(1) = .02508355
        Kpoly_VtoT(1).c(2) = .00000007860106
        Kpoly_VtoT(1).c(3) = -2.503131E-10
        Kpoly_VtoT(1).c(4) = 8.31527E-14
        Kpoly_VtoT(1).c(5) = -1.228034E-17
        Kpoly_VtoT(1).c(6) = 9.804036E-22
        Kpoly_VtoT(1).c(7) = -4.41303E-26
        Kpoly_VtoT(1).c(8) = 1.057734E-30
        Kpoly_VtoT(1).c(9) = -1.052755E-35
        ' ----------------------------------------
        ' K Type VtoT(2): TempRange 500 to 1372
        Kpoly_VtoT(2).eq_type = 6
        Kpoly_VtoT(2).c(0) = -131.8058
        Kpoly_VtoT(2).c(1) = .04830222
        Kpoly_VtoT(2).c(2) = -.000001646031
        Kpoly_VtoT(2).c(3) = 5.464731E-11
        Kpoly_VtoT(2).c(4) = -9.650715E-16
        Kpoly_VtoT(2).c(5) = 8.802193E-21
        Kpoly_VtoT(2).c(6) = -3.11081E-26
        ' ----------------------------------------
        ' N Type VtoT(0): TempRange -200 to 0
        Npoly_VtoT(0).eq_type = 9
        Npoly_VtoT(0).c(0) = 0#
        Npoly_VtoT(0).c(1) = .038436847
        Npoly_VtoT(0).c(2) = .0000011010485
        Npoly_VtoT(0).c(3) = 5.2229312E-09
        Npoly_VtoT(0).c(4) = 7.2060525E-12
        Npoly_VtoT(0).c(5) = 5.8488586E-15
        Npoly_VtoT(0).c(6) = 2.7754916E-18
        Npoly_VtoT(0).c(7) = 7.7075166E-22
        Npoly_VtoT(0).c(8) = 1.1582665E-25
        Npoly_VtoT(0).c(9) = 7.3138868E-30
        ' ----------------------------------------
        ' N Type VtoT(1): TempRange 0 to 600
        Npoly_VtoT(1).eq_type = 7
        Npoly_VtoT(1).c(0) = 0#
        Npoly_VtoT(1).c(1) = .0386896
        Npoly_VtoT(1).c(2) = -.00000108267
        Npoly_VtoT(1).c(3) = 4.70205E-11
        Npoly_VtoT(1).c(4) = -2.12169E-18
        Npoly_VtoT(1).c(5) = -1.17272E-19
        Npoly_VtoT(1).c(6) = 5.3928E-24
        Npoly_VtoT(1).c(7) = -7.98156E-29
        ' ----------------------------------------
        ' N Type VtoT(2): TempRange 600 to 1300
        Npoly_VtoT(2).eq_type = 5
        Npoly_VtoT(2).c(0) = 19.72485
        Npoly_VtoT(2).c(1) = .03300943
        Npoly_VtoT(2).c(2) = -.0000003915159
        Npoly_VtoT(2).c(3) = 9.855391E-12
        Npoly_VtoT(2).c(4) = -1.274371E-16
        Npoly_VtoT(2).c(5) = 7.767022E-22
        ' ----------------------------------------
        ' N Type VtoT(3): TempRange ??? to ???
        Npoly_VtoT(3).eq_type = 8
        Npoly_VtoT(3).c(0) = 0#
        Npoly_VtoT(3).c(1) = .038783277
        Npoly_VtoT(3).c(2) = -.0000011612344
        Npoly_VtoT(3).c(3) = 6.9525655E-11
        Npoly_VtoT(3).c(4) = -3.0090077E-15
        Npoly_VtoT(3).c(5) = 8.8311584E-20
        Npoly_VtoT(3).c(6) = -1.6213839E-24
        Npoly_VtoT(3).c(7) = 1.6693362E-29
        Npoly_VtoT(3).c(8) = -7.311754E-35
        ' ----------------------------------------
        ' R Type VtoT(0): TempRange -50 to 250
        Rpoly_VtoT(0).eq_type = 10
        Rpoly_VtoT(0).c(0) = 0#
        Rpoly_VtoT(0).c(1) = .1889138
        Rpoly_VtoT(0).c(2) = -.00009383529
        Rpoly_VtoT(0).c(3) = .00000013068619
        Rpoly_VtoT(0).c(4) = -2.270358E-10
        Rpoly_VtoT(0).c(5) = 3.5145659E-13
        Rpoly_VtoT(0).c(6) = -3.89539E-16
        Rpoly_VtoT(0).c(7) = 2.8239471E-19
        Rpoly_VtoT(0).c(8) = -1.2607281E-22
        Rpoly_VtoT(0).c(9) = 3.1353611E-26
        Rpoly_VtoT(0).c(10) = -3.3187769E-30
        ' ----------------------------------------
        ' R Type VtoT(1): TempRange 250 to 1200
        Rpoly_VtoT(1).eq_type = 9
        Rpoly_VtoT(1).c(0) = 13.34584505
        Rpoly_VtoT(1).c(1) = .1472644573
        Rpoly_VtoT(1).c(2) = -.00001844024844
        Rpoly_VtoT(1).c(3) = 4.031129726E-09
        Rpoly_VtoT(1).c(4) = -6.24942836E-13
        Rpoly_VtoT(1).c(5) = 6.468412046E-17
        Rpoly_VtoT(1).c(6) = -4.458750426E-21
        Rpoly_VtoT(1).c(7) = 1.994710149E-25
        Rpoly_VtoT(1).c(8) = -5.31340179E-30
        Rpoly_VtoT(1).c(9) = 6.481976217E-35
        ' ----------------------------------------
        ' R Type VtoT(2): TempRange 1064 to 1664.5
        Rpoly_VtoT(2).eq_type = 5
        Rpoly_VtoT(2).c(0) = -81.99599416
        Rpoly_VtoT(2).c(1) = .1553962042
        Rpoly_VtoT(2).c(2) = -.000008342197663
        Rpoly_VtoT(2).c(3) = 4.279433549E-10
        Rpoly_VtoT(2).c(4) = -1.19157791E-14
        Rpoly_VtoT(2).c(5) = 1.492290091E-19
        ' ----------------------------------------
        ' R Type VtoT(3): TempRange 1664.5 to 1768.1
        Rpoly_VtoT(3).eq_type = 4
        Rpoly_VtoT(3).c(0) = 34061.77836
        Rpoly_VtoT(3).c(1) = -7.023729171
        Rpoly_VtoT(3).c(2) = .0005582903813
        Rpoly_VtoT(3).c(3) = -1.952394635E-08
        Rpoly_VtoT(3).c(4) = 2.560740231E-13
        ' ----------------------------------------
        ' S Type VtoT(0): TempRange -50 to 250
        Spoly_VtoT(0).eq_type = 9
        Spoly_VtoT(0).c(0) = 0#
        Spoly_VtoT(0).c(1) = .18494946
        Spoly_VtoT(0).c(2) = -.0000800504062
        Spoly_VtoT(0).c(3) = .00000010223743
        Spoly_VtoT(0).c(4) = -1.52248592E-10
        Spoly_VtoT(0).c(5) = 1.88821343E-13
        Spoly_VtoT(0).c(6) = -1.59085941E-16
        Spoly_VtoT(0).c(7) = 8.2302788E-20
        Spoly_VtoT(0).c(8) = -2.34181944E-23
        Spoly_VtoT(0).c(9) = 2.7978626E-27
        ' ----------------------------------------
        ' S Type VtoT(1): TempRange 250 to 1200
        Spoly_VtoT(1).eq_type = 9
        Spoly_VtoT(1).c(0) = 12.91507177
        Spoly_VtoT(1).c(1) = .1466298863
        Spoly_VtoT(1).c(2) = -.00001534713402
        Spoly_VtoT(1).c(3) = 3.145945973E-09
        Spoly_VtoT(1).c(4) = -4.163257839E-13
        Spoly_VtoT(1).c(5) = 3.187963771E-17
        Spoly_VtoT(1).c(6) = -1.2916375E-21
        Spoly_VtoT(1).c(7) = 2.183475087E-26
        Spoly_VtoT(1).c(8) = -1.447379511E-31
        Spoly_VtoT(1).c(9) = 8.211272125E-36
        ' ----------------------------------------
        ' S Type VtoT(2): TempRange 1064 to 1664.5
        Spoly_VtoT(2).eq_type = 5
        Spoly_VtoT(2).c(0) = -80.87801117
        Spoly_VtoT(2).c(1) = .1621573104
        Spoly_VtoT(2).c(2) = -.000008536869453
        Spoly_VtoT(2).c(3) = 4.719686976E-10
        Spoly_VtoT(2).c(4) = -1.441693666E-14
        Spoly_VtoT(2).c(5) = 2.08161889E-19
        ' ----------------------------------------
        ' S Type VtoT(3): TempRange 1664.5 to 1768.1
        Spoly_VtoT(3).eq_type = 4
        Spoly_VtoT(3).c(0) = 53338.75126
        Spoly_VtoT(3).c(1) = -12.35892298
        Spoly_VtoT(3).c(2) = .001092657613
        Spoly_VtoT(3).c(3) = -4.265693686E-08
        Spoly_VtoT(3).c(4) = 6.24720542E-13
        ' ----------------------------------------
        ' T Type VtoT(0): TempRange -200 to 0
        Tpoly_VtoT(0).eq_type = 7
        Tpoly_VtoT(0).c(0) = 0#
        Tpoly_VtoT(0).c(1) = .025949192
        Tpoly_VtoT(0).c(2) = -.00000021316967
        Tpoly_VtoT(0).c(3) = 7.9018692E-10
        Tpoly_VtoT(0).c(4) = 4.2527777E-13
        Tpoly_VtoT(0).c(5) = 1.3304473E-16
        Tpoly_VtoT(0).c(6) = 2.0241446E-20
        Tpoly_VtoT(0).c(7) = 1.2668171E-24
        ' ----------------------------------------
        ' T Type VtoT(1): TempRange 0 to 1000
        Tpoly_VtoT(1).eq_type = 6
        Tpoly_VtoT(1).c(0) = 0#
        Tpoly_VtoT(1).c(1) = .025928
        Tpoly_VtoT(1).c(2) = -.0000007602961
        Tpoly_VtoT(1).c(3) = 4.637791E-11
        Tpoly_VtoT(1).c(4) = -2.165394E-15
        Tpoly_VtoT(1).c(5) = 6.048144E-20
        Tpoly_VtoT(1).c(6) = -7.293422E-25

        ' ----------------------------------------
        ' Setting the TtoV coefficients
        ' ----------------------------------------
        ' ----------------------------------------
        ' B Type TtoV(0): TempRange 0 to 630.615
        Bpoly_TtoV(0).eq_type = 6
        Bpoly_TtoV(0).c(0) = 0#
        Bpoly_TtoV(0).c(1) = -.24650818346
        Bpoly_TtoV(0).c(2) = .0059040421171
        Bpoly_TtoV(0).c(3) = -1.3257931636E-06
        Bpoly_TtoV(0).c(4) = 1.5668291901E-09
        Bpoly_TtoV(0).c(5) = -1.694452924E-12
        Bpoly_TtoV(0).c(6) = 6.2990347094E-16
        ' ----------------------------------------
        ' B Type TtoV(1): TempRange 630.615  to 1820
        Bpoly_TtoV(1).eq_type = 8
        Bpoly_TtoV(1).c(0) = -3893.8168621
        Bpoly_TtoV(1).c(1) = 28.57174747
        Bpoly_TtoV(1).c(2) = -.084885104785
        Bpoly_TtoV(1).c(3) = .00015785280164
        Bpoly_TtoV(1).c(4) = -1.6835344864E-07
        Bpoly_TtoV(1).c(5) = 1.1109794013E-10
        Bpoly_TtoV(1).c(6) = -4.4515431033E-14
        Bpoly_TtoV(1).c(7) = 9.8975640821E-18
        Bpoly_TtoV(1).c(8) = -9.3791330289E-22

        ' ----------------------------------------
        ' E Type TtoV(0): TempRange -200 to 0
        Epoly_TtoV(0).eq_type = 13
        Epoly_TtoV(0).c(0) = 0#
        Epoly_TtoV(0).c(1) = 58.665508708
        Epoly_TtoV(0).c(2) = .045410977124
        Epoly_TtoV(0).c(3) = -.00077998048686
        Epoly_TtoV(0).c(4) = -.000025800160843
        Epoly_TtoV(0).c(5) = -5.9452583057E-07
        Epoly_TtoV(0).c(6) = -9.3214058667E-09
        Epoly_TtoV(0).c(7) = -1.0287605534E-10
        Epoly_TtoV(0).c(8) = -8.0370123621E-13
        Epoly_TtoV(0).c(9) = -4.3979497391E-15
        Epoly_TtoV(0).c(10) = -1.6414776355E-17
        Epoly_TtoV(0).c(11) = -3.9673619516E-20
        Epoly_TtoV(0).c(12) = -5.5827328721E-23
        Epoly_TtoV(0).c(13) = -3.4657842013E-26
        ' ----------------------------------------
        ' E Type TtoV(1): TempRange 0 to 1000
        Epoly_TtoV(1).eq_type = 10
        Epoly_TtoV(1).c(0) = 0#
        Epoly_TtoV(1).c(1) = 58.66550871
        Epoly_TtoV(1).c(2) = .045032275582
        Epoly_TtoV(1).c(3) = .000028908407212
        Epoly_TtoV(1).c(4) = -3.3056896652E-07
        Epoly_TtoV(1).c(5) = 6.502440327E-10
        Epoly_TtoV(1).c(6) = -1.9197495504E-13
        Epoly_TtoV(1).c(7) = -1.2536600497E-15
        Epoly_TtoV(1).c(8) = 2.1489217569E-18
        Epoly_TtoV(1).c(9) = -1.4388041782E-21
        Epoly_TtoV(1).c(10) = 3.5960899481E-25
        ' ----------------------------------------
        ' J Type TtoV(0): TempRange -210 to 760
        Jpoly_TtoV(0).eq_type = 8
        Jpoly_TtoV(0).c(0) = 0#
        Jpoly_TtoV(0).c(1) = 50.381187815
        Jpoly_TtoV(0).c(2) = .03047583693
        Jpoly_TtoV(0).c(3) = -.00008568106572
        Jpoly_TtoV(0).c(4) = 1.3228195295E-07
        Jpoly_TtoV(0).c(5) = -1.7052958337E-10
        Jpoly_TtoV(0).c(6) = 2.0948090697E-13
        Jpoly_TtoV(0).c(7) = -1.2538395336E-16
        Jpoly_TtoV(0).c(8) = 1.5631725697E-20
        ' ----------------------------------------
        ' J Type TtoV(1): TempRange 760 to 1200
        Jpoly_TtoV(1).eq_type = 5
        Jpoly_TtoV(1).c(0) = 296456.25681
        Jpoly_TtoV(1).c(1) = -1497.6127786
        Jpoly_TtoV(1).c(2) = 3.1787103924
        Jpoly_TtoV(1).c(3) = -.0031847686701
        Jpoly_TtoV(1).c(4) = 1.5720819004E-06
        Jpoly_TtoV(1).c(5) = -3.0691369056E-10
        ' ----------------------------------------
        ' K Type TtoV(0): TempRange -270 to 0
        Kpoly_TtoV(0).eq_type = 10
        Kpoly_TtoV(0).c(0) = 0#
        Kpoly_TtoV(0).c(1) = 39.450128025
        Kpoly_TtoV(0).c(2) = .023622373598
        Kpoly_TtoV(0).c(3) = -.00032858906784
        Kpoly_TtoV(0).c(4) = -4.9904828777E-06
        Kpoly_TtoV(0).c(5) = -6.7509059173E-08
        Kpoly_TtoV(0).c(6) = -5.7410327428E-10
        Kpoly_TtoV(0).c(7) = -3.1088872894E-12
        Kpoly_TtoV(0).c(8) = -1.0451609365E-14
        Kpoly_TtoV(0).c(9) = -1.9889266878E-17
        Kpoly_TtoV(0).c(10) = -1.6322697486E-20
        ' ----------------------------------------
        ' K Type TtoV(1): TempRange 0 to 1372
        ' notice: special polynomial
        Kpoly_TtoV(1).eq_type = 100
        Kpoly_TtoV(1).c(0) = -17.600413686
        Kpoly_TtoV(1).c(1) = 38.921204975
        Kpoly_TtoV(1).c(2) = .018558770032
        Kpoly_TtoV(1).c(3) = -.000099457592874
        Kpoly_TtoV(1).c(4) = 3.1840945719E-07
        Kpoly_TtoV(1).c(5) = -5.6072844889E-10
        Kpoly_TtoV(1).c(6) = 5.6075059059E-13
        Kpoly_TtoV(1).c(7) = -3.2020720003E-16
        Kpoly_TtoV(1).c(8) = 9.7151147152E-20
        Kpoly_TtoV(1).c(9) = -1.2104721275E-23
        Kpoly_TtoV(1).alpha(0) = 118.5976
        Kpoly_TtoV(1).alpha(1) = -.0001183432
        ' ----------------------------------------
        ' N Type TtoV(0): TempRange -270 to 0
        Npoly_TtoV(0).eq_type = 8
        Npoly_TtoV(0).c(0) = 0#
        Npoly_TtoV(0).c(1) = 26.159105962
        Npoly_TtoV(0).c(2) = .010957484228
        Npoly_TtoV(0).c(3) = -.000093841111554
        Npoly_TtoV(0).c(4) = -4.6412039759E-08
        Npoly_TtoV(0).c(5) = -2.6303357716E-09
        Npoly_TtoV(0).c(6) = -2.2653438003E-11
        Npoly_TtoV(0).c(7) = -7.6089300791E-14
        Npoly_TtoV(0).c(8) = -9.3419667835E-17
        ' ----------------------------------------
        ' N Type TtoV(1): TempRange 0 to 400
        Npoly_TtoV(1).eq_type = 10
        Npoly_TtoV(1).c(0) = 0#
        Npoly_TtoV(1).c(1) = 25.929394601
        Npoly_TtoV(1).c(2) = .01571014188
        Npoly_TtoV(1).c(3) = .000043825627237
        Npoly_TtoV(1).c(4) = -2.5261169794E-07
        Npoly_TtoV(1).c(5) = 6.4311819339E-10
        Npoly_TtoV(1).c(6) = -1.0063471519E-12
        Npoly_TtoV(1).c(7) = 9.9745338992E-16
        Npoly_TtoV(1).c(8) = -6.0863245607E-19
        Npoly_TtoV(1).c(9) = 2.0849229339E-22
        Npoly_TtoV(1).c(10) = -3.0682196151E-26
        ' ----------------------------------------
        ' R Type TtoV(0): TempRange -50 to 1064.18
        Rpoly_TtoV(0).eq_type = 9
        Rpoly_TtoV(0).c(0) = 0#
        Rpoly_TtoV(0).c(1) = 5.28961729765
        Rpoly_TtoV(0).c(2) = .0139166589782
        Rpoly_TtoV(0).c(3) = -2.38855693017E-05
        Rpoly_TtoV(0).c(4) = 3.56916001063E-08
        Rpoly_TtoV(0).c(5) = -4.62347666298E-11
        Rpoly_TtoV(0).c(6) = 5.00777441034E-14
        Rpoly_TtoV(0).c(7) = -3.73105886191E-17
        Rpoly_TtoV(0).c(8) = 1.57716482367E-20
        Rpoly_TtoV(0).c(9) = -2.81038625251E-24
        ' ----------------------------------------
        ' R Type TtoV(1): TempRange 1064.18 to 1664.5
        Rpoly_TtoV(1).eq_type = 5
        Rpoly_TtoV(1).c(0) = 2951.57925316
        Rpoly_TtoV(1).c(1) = -2.52061251332
        Rpoly_TtoV(1).c(2) = .0159564501865
        Rpoly_TtoV(1).c(3) = -7.64085947576E-06
        Rpoly_TtoV(1).c(4) = 2.05305291024E-09
        Rpoly_TtoV(1).c(5) = -2.93359668173E-13
        ' ----------------------------------------
        ' R Type TtoV(2): TempRange 1664.5 to 1768.1
        Rpoly_TtoV(2).eq_type = 4
        Rpoly_TtoV(2).c(0) = 152232.118209
        Rpoly_TtoV(2).c(1) = -268.819888545
        Rpoly_TtoV(2).c(2) = .171280280471
        Rpoly_TtoV(2).c(3) = -3.45895706453E-05
        Rpoly_TtoV(2).c(4) = -9.34633971046E-12
        ' ----------------------------------------
        ' S Type TtoV(0): TempRange -50 to 1064.18
        Spoly_TtoV(0).eq_type = 8
        Spoly_TtoV(0).c(0) = 0#
        Spoly_TtoV(0).c(1) = 5.40313308631
        Spoly_TtoV(0).c(2) = .012593428974
        Spoly_TtoV(0).c(3) = -2.32477968689E-05
        Spoly_TtoV(0).c(4) = 3.22028823036E-08
        Spoly_TtoV(0).c(5) = -3.31465196389E-11
        Spoly_TtoV(0).c(6) = 2.55744251786E-14
        Spoly_TtoV(0).c(7) = -1.25068871393E-17
        Spoly_TtoV(0).c(8) = 2.71443176145E-21
        ' ----------------------------------------
        ' S Type TtoV(1): TempRange 1064.18 to 1664.5
        Spoly_TtoV(1).eq_type = 4
        Spoly_TtoV(1).c(0) = 1329.00444085
        Spoly_TtoV(1).c(1) = 3.34509311344
        Spoly_TtoV(1).c(2) = .00654805192818
        Spoly_TtoV(1).c(3) = -1.64856259209E-06
        Spoly_TtoV(1).c(4) = 1.29989605174E-11
        ' ----------------------------------------
        ' S Type TtoV(2): TempRange 1664.5 to 1768.1
        Spoly_TtoV(2).eq_type = 4
        Spoly_TtoV(2).c(0) = 146628.232636
        Spoly_TtoV(2).c(1) = -258.430516752
        Spoly_TtoV(2).c(2) = .163693574641
        Spoly_TtoV(2).c(3) = -3.30439046987E-05
        Spoly_TtoV(2).c(4) = -9.43223690612E-12
        ' ----------------------------------------
        ' T Type TtoV(0): TempRange -200 to 0
        Tpoly_TtoV(0).eq_type = 14
        Tpoly_TtoV(0).c(0) = 0#
        Tpoly_TtoV(0).c(1) = 38.748106364
        Tpoly_TtoV(0).c(2) = .044194434347
        Tpoly_TtoV(0).c(3) = .00011844323105
        Tpoly_TtoV(0).c(4) = .000020032973554
        Tpoly_TtoV(0).c(5) = 9.0138019559E-07
        Tpoly_TtoV(0).c(6) = 2.2651156593E-08
        Tpoly_TtoV(0).c(7) = 3.6071154205E-10
        Tpoly_TtoV(0).c(8) = 3.8493939883E-12
        Tpoly_TtoV(0).c(9) = 2.8213521925E-14
        Tpoly_TtoV(0).c(10) = 1.4251594779E-16
        Tpoly_TtoV(0).c(11) = 4.8768662286E-19
        Tpoly_TtoV(0).c(12) = 1.079553927E-21
        Tpoly_TtoV(0).c(13) = 1.3945027062E-24
        Tpoly_TtoV(0).c(14) = 7.9795153927E-28
        ' ----------------------------------------
        ' T Type TtoV(1): TempRange 0 to 400
        Tpoly_TtoV(1).eq_type = 8
        Tpoly_TtoV(1).c(0) = 0#
        Tpoly_TtoV(1).c(1) = 38.748106364
        Tpoly_TtoV(1).c(2) = .03329222788
        Tpoly_TtoV(1).c(3) = .00020618243404
        Tpoly_TtoV(1).c(4) = -2.1882256846E-06
        Tpoly_TtoV(1).c(5) = 1.0996880928E-08
        Tpoly_TtoV(1).c(6) = -3.0815758772E-11
        Tpoly_TtoV(1).c(7) = 4.547913529E-14
        Tpoly_TtoV(1).c(8) = -2.7512901673E-17

    'Else
        '
        ' polynomials are already initialized!
        ' do nothing here
        '
    End If

End Sub

'*************************************************************************
'*  zRt_to_Temp
'*
'*      Uses the formula given below
'*      to convert a thermistor resistance to temperature in Kelvin
'*      then converts this temparature to the required scale.
'*
'*      a,b,c are coefficients taken from a precision thermistor handbook
'*
'*          a = 1.295361e-3
'*          b = 2.343159e-4
'*          c = 1.018703e-7
'*
'*      1/Tk = a + b*ln(Rt) + c*ln(Rt)^3
'*
'*      Tk is the temperature reading in Kelvin
'*
'**************************************************************************
Function zRt_to_Temp (ByVal Rt As Double, temperature As Double, ByVal TempScale As Integer) As Integer
  
  Dim a, b, c, logRt, logRtCubed As Double
  Dim returnCode As Integer
  
  returnCode = noErr
  
  a = .001295361
  b = .0002343159
  c = .0000001018703

  If Rt <= 0# Then
    returnCode = imaginaryNumber
    GoTo outa_zRt_to_Temp
  End If
    
  logRt = Log(Rt)
  logRtCubed = logRt * logRt * logRt
  temperature = 1 / (a + b * logRt + c * logRtCubed)

  '   Convert the temperature(s) from degrees Kelvin to ...
  Select Case TempScale
    
    Case CELSIUS
      temperature = temperature - 273.15
      
    Case KELVIN
      temperature = temperature
      
    Case FAHRENHEIT
      temperature = 1.8 * temperature - 459.67

    Case RANKINE
      temperature = 1.8 * temperature
      
    Case Else
      returnCode = invalidTempScale
      GoTo outa_zRt_to_Temp
      
  End Select

outa_zRt_to_Temp:

  zRt_to_Temp = returnCode

End Function

'*************************************************************************
'*   zTemp_to_volts
'*
'*    FUNCTION:
'*    Converts a thermocouple temperature to an equivalent thermocouple voltage
'*    using the NIST standards. Several equations characterize
'*    a thermocouple type corresponding to different temperature ranges.
'*    The equations are mostly Nth order polynomials.
'*
'*    INPUTS:
'*     TCtype       : The thermocouple type (constant defines in convert.h).
'*     temperature  : The temperature to be converted in degree Celsius.
'*
'*    OUTPUTS:
'*     volts        : parameter that returns the equivalent
'*                    voltage. Returns an error if the thermocouple type is invalid.
'*
'*
'**************************************************************************
Function zTemp_to_volts (ByVal TCtype As Integer, ByVal temperature As Double, Volts As Double) As Integer

    Dim poly1 As Polynomial
    Dim returnCode As Integer

    returnCode = noErr

    Select Case TCtype

        Case B_TYPE_TC
            If temperature <= 630.615 Then      ' TempRange 0 to 630.615
                poly1 = Bpoly_TtoV(0)
            Else                                ' TempRange 630.615 to 1820
                poly1 = Bpoly_TtoV(1)
            End If

        Case J_TYPE_TC
            If temperature <= 760 Then          ' TempRange -210 to 760
                poly1 = Jpoly_TtoV(0)
            Else                                ' TempRange 760 to 1200
                poly1 = Jpoly_TtoV(1)
            End If

        Case K_TYPE_TC
            If temperature <= 0 Then            ' TempRange -270 to 0
                poly1 = Kpoly_TtoV(0)
            Else                                ' TempRange 0 to 1372
                poly1 = Kpoly_TtoV(1)
            End If

        Case N_TYPE_TC
            If temperature <= 0 Then            ' TempRange -270 to 0
                poly1 = Npoly_TtoV(0)
            Else                                ' TempRange 0 to 1300
                poly1 = Npoly_TtoV(1)
            End If

        Case T_TYPE_TC
            If temperature <= 0 Then            ' TempRange -200 to 0
                poly1 = Tpoly_TtoV(0)
            Else                                ' TempRange 0 to 400
                poly1 = Tpoly_TtoV(1)
            End If

        Case E_TYPE_TC
            If temperature <= 0 Then            ' TempRange -200 to 0
                poly1 = Epoly_TtoV(0)
            Else                                ' TempRange 0 to 1000
                poly1 = Epoly_TtoV(1)
            End If

        Case R_TYPE_TC
            If temperature <= 1064.18 Then      ' TempRange -50 to 1064.18
                poly1 = Rpoly_TtoV(0)
            ElseIf temperature <= 1664.5 Then   ' TempRange 1064.18 to 1664.5
                poly1 = Rpoly_TtoV(1)
            Else                                ' TempRange 1664.5 to 1768.1
                poly1 = Rpoly_TtoV(2)
            End If

        Case S_TYPE_TC
            If temperature <= 1064.18 Then      ' TempRange -50 to 1064.18
                poly1 = Spoly_TtoV(0)
            ElseIf temperature <= 1664.5 Then   ' TempRange 1064.18 to 1664.5
                poly1 = Spoly_TtoV(1)
            Else                                ' TempRange 1664.5 to 1768.1
                poly1 = Spoly_TtoV(2)
            End If

        Case Else
            returnCode = invalidTCtype

  End Select
  
  returnCode = zCompute_equation(poly1, temperature, Volts)

  ' return voltage in volts
  Volts = Volts / 1000000#

  zTemp_to_volts = returnCode

End Function

'*************************************************************************
'*   zVolts_to_temp
'*
'*    FUNCTION:
'*    Converts a single thermocouple voltage value to a corresponding
'*    temperature using the NIST standards. Several equations characterize
'*    a thermocouple type corresponding to different temperature ranges.
'*    The equations are mostly Nth order polynomials.
'*
'*    INPUTS:
'*     TCtype       : The thermocouple type (constant defines in convert.h).
'*     volts        : The thermocouple voltage in micro volts.
'*
'*    OUTPUTS:
'*     temperature  : Call by reference parameter that returns the temperature.
'*                    Returns an error if the thermocouple type is invalid.
'*
'*
'**************************************************************************
Function zVolts_to_temp (ByVal TCtype As Integer, ByVal Volts As Double, temperature As Double) As Integer

    Dim poly1 As Polynomial
    Dim returnCode As Integer

    returnCode = noErr

    ' convert voltage into micro volts
    Volts = Volts * 1000000#

    Select Case TCtype
        Case B_TYPE_TC

            If Volts <= 2431 Then       ' TempRange -50 to 250 ; ErrRange   0.03 to -0.02
                poly1 = Bpoly_VtoT(0)
            Else                        ' TempRange 700 to 1820 ; ErrRange 0.02 to -0.01
                poly1 = Bpoly_VtoT(1)
            End If

        Case J_TYPE_TC
            If Volts <= 0 Then          ' TempRange -210 to 0 ; ErrRange 0.03 to -0.05
                poly1 = Jpoly_VtoT(0)
            ElseIf Volts <= 42919 Then  ' TempRange 0 to 760 ; ErrRange 0.04 to -0.04
                poly1 = Jpoly_VtoT(1)
            Else                        ' TempRange 760 to 1200 ; ErrRange 0.03 to -0.04
                poly1 = Jpoly_VtoT(2)
            End If

        Case K_TYPE_TC
            If Volts <= 0 Then          ' TempRange -200 to 0 ; ErrRange   0.04 to -0.02
                poly1 = Kpoly_VtoT(0)
            ElseIf Volts <= 20644 Then  ' TempRange 0 to 500 ; ErrRange 0.04 to -0.05
                poly1 = Kpoly_VtoT(1)
            Else                        ' TempRange 500 to 1372 ; ErrRange  0.06 to -0.05
                poly1 = Kpoly_VtoT(2)
            End If
     
        Case N_TYPE_TC
            If Volts <= 0 Then          ' TempRange -200 to 0 ; ErrRange   0.03 to -0.02
                poly1 = Npoly_VtoT(0)
            ElseIf Volts <= 20613 Then  ' TempRange 0 to 600 ; ErrRange 0.03 to -0.02
                poly1 = Npoly_VtoT(1)
            Else                        ' TempRange 600 to 1300 ; ErrRange  0.02 to -0.04
                poly1 = Npoly_VtoT(2)
            End If

        Case T_TYPE_TC
            If Volts <= 0 Then          ' TempRange -200 to 0 ; ErrRange 0.04 to -0.02
                poly1 = Tpoly_VtoT(0)
            Else                        ' TempRange 0 to 400 ; ErrRange  0.03 to -0.03
                poly1 = Tpoly_VtoT(1)
            End If

        Case E_TYPE_TC
            If Volts <= 0 Then          ' TempRange -200 to 0 ; ErrRange 0.03 to -0.01
                poly1 = Epoly_VtoT(0)
            Else                        ' TempRange 0 to 1000 ; ErrRange  0.02 to -0.02
                poly1 = Epoly_VtoT(1)
            End If

        Case R_TYPE_TC
            If Volts <= 1923 Then       ' TempRange -50 to 250 ; ErrRange   0.02 to -0.02
                poly1 = Rpoly_VtoT(0)
            ElseIf Volts <= 13228 Then  ' TempRange 250 to 1200 ; ErrRange 0.005 to -0.005
                poly1 = Rpoly_VtoT(1)
            ElseIf Volts <= 19739 Then  ' TempRange 1064 to 1664.5 ; ErrRange  0.001 to -0.0005
                poly1 = Rpoly_VtoT(2)
            Else                        ' TempRange 1664.5 to 1768.1 ; ErrRange 0.002 to -0.001
                poly1 = Rpoly_VtoT(3)
            End If

        Case S_TYPE_TC
            If Volts <= 1874 Then       ' TempRange -50 to 250 ; ErrRange   0.02 to -0.02
                poly1 = Spoly_VtoT(0)
            ElseIf Volts <= 11950 Then  ' TempRange 250 to 1200 ; ErrRange 0.005 to -0.005
                poly1 = Spoly_VtoT(1)
            ElseIf Volts <= 17536 Then  ' TempRange 1064 to 1664.5 ; ErrRange  0.001 to -0.0005
                poly1 = Spoly_VtoT(2)
            Else                        ' TempRange 1664.5 to 1768.1 ; ErrRange 0.002 to -0.002
                poly1 = Spoly_VtoT(3)
            End If

        Case Else
            returnCode = invalidTCtype

    End Select

    ' come back here
    returnCode = zCompute_equation(poly1, Volts, temperature)

    zVolts_to_temp = returnCode

End Function

