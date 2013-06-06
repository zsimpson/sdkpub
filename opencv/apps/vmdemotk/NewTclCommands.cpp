#include "VMDemoTk.h"
#include "NewTclCommands.h"
#include "DataandMorphing.h"
#include "Globals.h"
#include "CommandConcatenation.h"
#include <highgui.h>


int TKVMDemo_Setposition( ClientData cd, Tcl_Interp *interp,
                          int argc, char **argv)
{
    //Tk_Window win1 , win2 , win3;
    Tk_Window mainWindow = Tk_MainWindow(interp);
    Tk_MoveToplevelWindow(mainWindow,300,300);
    return 0;
}

int TKVMDemo_fileopen( ClientData cd, Tcl_Interp *interp,
                      int argc, char **argv)
{
    //Open file dialog and sets path to interp.result
    Tcl_Eval(interp,"tk_getOpenFile");
    if (!(*(interp->result))) return 2;
    HaveMorph   = false;
    
    //Initialising dynamic strings for storing data
    Tcl_DString s, dir, inifiletoken, file;
    Tcl_DStringInit(&s);
    Tcl_DStringInit(&dir);
    Tcl_DStringInit(&inifiletoken);
    Tcl_DStringInit(&file);
    
    //Saving path to the file
    Tcl_DStringGetResult(interp, &file);
    
    //Saving directory path
    Tcl_Eval(interp, CommandConcatenation(&s,"%s%s", "file dirname ", file.string));
    Tcl_DStringGetResult(interp, &dir);
    
    // Running package for parsing .ini files
    Tcl_EvalFile (interp, "iniparse.tcl");
    
    
    //Removing scanlines
    Tcl_Eval(interp, ".bottom.cb1 deselect");
    Tcl_Eval(interp, "CShowScanlines");
    
    // disable slider and checkbutton
    Tcl_Eval(interp, ".bottom.cb1 configure -state disabled");
    Tcl_Eval(interp, ".s configure -state disabled");
    
    // Opens project file
    Tcl_Eval (interp, CommandConcatenation(&s,"%s%s", "iniparse:openfile ", 
        file.string));
    
    // Saving opend file Tcl token
    Tcl_DStringAppend(&inifiletoken , (*interp).result,-1);
    
    // Saving token for opened ini file to a Tcl variable
    CommandConcatenation(&s,"%s%s", "set var ", inifiletoken.string);
    Tcl_Eval (interp, s.string);
    Tcl_DStringFree(&s);
    
    //Reading 1-st image from a file
    CommandConcatenation(&s,"%s%s%s", "readini ", inifiletoken.string,
        " Pair1 Image1" );
    Tcl_Eval (interp, s.string);
    if (!(*(interp->result))) return 2;
    
    CommandConcatenation(&s,
        "%s%s%s", 
        dir.string,"/", (*interp).result);
    char temp[1000];
    sprintf(temp, "%s", s.string);
    while( temp[strlen(temp) - 1] <= ' ' && temp[strlen(temp) - 1] > 0 )
        temp[strlen(temp) - 1] = 0;
    if( datal )
        cvReleaseImage( &datal );
    datal =  cvvLoadImage( temp );
    
    Tcl_DStringFree(&s);
    if( !datal ) return 2;
    
    //Reading 2-d image from a file
    CommandConcatenation(&s,"%s%s%s", "readini ", inifiletoken.string,
        " Pair1 Image2" );
    Tcl_Eval (interp, s.string);
    if (!(*(interp->result))) return 2;
    
    CommandConcatenation(&s,
        "%s%s%s", 
        dir.string,"/", (*interp).result);
    
    sprintf(temp, "%s", s.string);
    while( temp[strlen(temp) - 1] <= ' ' && temp[strlen(temp) - 1] > 0 )
        temp[strlen(temp) - 1] = 0;
    if( datar )
        cvReleaseImage( &datar );
    datar =  cvvLoadImage( temp );
    
    Tcl_DStringFree(&s);
    if( !datar ) return 2;
    
    // Loading images data and fundanental matrix 
    FreeMemory();
    if(loaddata( interp)) return 2;
    
    MemoryAllocation();
    
    Tcl_Eval(interp, "CSetpos");
    
    //Displaying source images
    cvvShowImage( "left", datal );
    cvvShowImage( "right", datar );
    
    Tcl_Eval(interp, ".s configure -state active");
    Tcl_Eval(interp, ".s set 0.0");
    Tcl_Eval(interp, ".bottom.cb1 configure -state normal");
    Tcl_Eval (interp, CommandConcatenation(&s,"%s%d%s%d%s", 
        ".top.l2 configure -text {",
        imgsize.width,"X ", imgsize.height,
        "}"));
    return 0;
}


int TKVMDemo_scale(ClientData cd, Tcl_Interp *interp,
                   int argc, char **argv)
{
    Tcl_Eval(interp, ".s get");
    float sk = (float)atof((*interp).result);
    static float previosposition = 0.0;
    
    if ((sk-previosposition)*(sk-previosposition)>= 0.01)
    {
        OnMakeMorphing(sk, interp);
        
        previosposition=sk;
        Tcl_DString setposition;
        Tcl_DStringInit(&setposition);
        char position = (char)sk;
        Tcl_DStringAppend(&setposition,".s set",-1);
        Tcl_DStringAppend(&setposition,&position,-1);
        Tcl_Eval(interp, setposition.string);
    }
    
    return 0;
}


int TKVMDemo_ShowScanlines(ClientData cd, Tcl_Interp *interp,
                           int argc, char **argv)
{
    Tcl_Eval(interp, "set chb");
    int chb = atoi(interp->result);
    Tcl_DString drawlinecommand;
    Tcl_DStringInit(&drawlinecommand);
    int     n;
    int     x1,y1,x2,y2;
    
    if (numScanlines>0 && chb ) 
    {
        for (n = 0; n < numScanlines; n +=10) 
        {
            x1 = (scanlines_2)[n * 4    ];
            y1 = (scanlines_2)[n * 4 + 1];
            x2 = (scanlines_2)[n * 4 + 2];
            y2 = (scanlines_2)[n * 4 + 3];
            
            CommandConcatenation(&drawlinecommand,"%s%s%d%d%d%d%s",
                "set numlines1 [ ",
                ".win1.c create line ",
                x1, y1, x2, y2,
                "]"); 
            Tcl_Eval(interp, drawlinecommand.string);
            Tcl_DStringFree(&drawlinecommand);
            
            x1 = (scanlines_1)[n * 4    ];
            y1 = (scanlines_1)[n * 4 + 1];
            x2 = (scanlines_1)[n * 4 + 2];
            y2 = (scanlines_1)[n * 4 + 3];
            
            CommandConcatenation(&drawlinecommand,"%s%d%d%d%d",
                ".win2.c create line ",
                x1, y1, x2, y2
                ); 
            
            Tcl_Eval(interp, drawlinecommand.string);
            Tcl_DStringFree(&drawlinecommand);
            
            x1 = (scanlines_a)[n * 4    ];
            y1 = (scanlines_a)[n * 4 + 1];
            x2 = (scanlines_a)[n * 4 + 2];
            y2 = (scanlines_a)[n * 4 + 3];
            CommandConcatenation(&drawlinecommand,"%s%d%d%d%d",
                ".win3.c create line ",
                x1, y1, x2, y2
                ); 
            
            Tcl_Eval(interp, drawlinecommand.string);
            
            Tcl_DStringFree(&drawlinecommand);
        }
        return 0;
    }
    
    if (numScanlines>0 && !chb ) 
    {
        Tcl_Eval(interp,"set numlines1");
        int numlines1 = atoi(interp->result);
        
        Tcl_DString deletelinecommand;
        Tcl_DStringInit(&deletelinecommand);
        
        for (n = 0; n < numScanlines; n +=10) 
        {
            int m = n/10;
            CommandConcatenation(&deletelinecommand,"%s%d%d%d%d",
                ".win1.c delete ",
                numlines1 - m
                ); 
            
            Tcl_Eval(interp, deletelinecommand.string);
            Tcl_DStringFree(&deletelinecommand);
            
            CommandConcatenation(&deletelinecommand,"%s%d%d%d%d",
                ".win2.c delete ",
                numlines1 - m
                ); 
            
            Tcl_Eval(interp, deletelinecommand.string);
            Tcl_DStringFree(&deletelinecommand);
            
            CommandConcatenation(&deletelinecommand,"%s%d%d%d%d",
                ".win3.c delete ",
                numlines1 - m
                ); 
            
            Tcl_Eval(interp, deletelinecommand.string);
            Tcl_DStringFree(&deletelinecommand);
        }
    }
    
    return 0;
}

////////////////////////////////////////////////////////////////////////////
void    OnExit(ClientData clientData)
{
    FreeMemory();
}


