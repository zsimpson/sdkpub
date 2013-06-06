BOOL RegisterWindow(char *lpClass, HANDLE instance);

HWND CreateWin(		  int x, 
					  int y, 
					  int width, 
					  int height, 
					  char *lpClass, 
					  char *name,
					  HANDLE instance);
int WINAPI ImageWndProc(
    HWND hwnd,
    UINT message,
    DWORD wParam,
    LONG lParam);

void Show_Bitmap( HDC dc, unsigned char *data);
void Draw_Image( HWND wnd );
HPALETTE Create_Palette(int red, int blue, int green);
void Update_Bitmap( HWND hwnd, unsigned short *data , int flag);
void Update_Strip( HWND hwnd, unsigned short *data , int flag);
void SetShift( void );