#include "CommandConcatenation.h"
#include <stdlib.h>

char* CommandConcatenation (Tcl_DString *string, char *str, ...)
{
    Tcl_DStringFree(string);
    va_list marker;
    //char buffer[10];
    va_start(marker,str);
    while(*str)
    {
        if (*str == '%')
        {
            switch (*(++str))
            {
            case 's': 
                Tcl_DStringAppend(string, va_arg(marker, char*), -1);
                break;
               
            case 'd': 
                {
                    char tmp_str[100];
                    sprintf(tmp_str, "%d", va_arg(marker, int));
                    Tcl_DStringAppend(string, tmp_str /*_itoa( (va_arg(marker, int)), buffer, 10)*/,-1);
                    Tcl_DStringAppend(string, " ", -1);
                    break;
                }
            }
        }
        str++;
    }
    
    va_end(marker);
    return string->string;
}
