IPLIMAGE src;
IPLIMAGE image;
IPLIMAGE dest;
//the address of variable which receives trackbar position update 
int pos[1]={0};

src=load_iplimage("expo0001.bmp");
image=cvCloneImage(src);
dest=cvCloneImage(src);

//create windows for output images
named_window("Opening&Closing window",0);
named_window("Erosion&Dilation window",0);

show_iplimage("Opening&Closing window",src);
show_iplimage("Erosion&Dilation window",src);


//callback function for slider , implements opening 
void Opening(int id)   
  {
        cvErode(src,image,NULL,pos[0]);
        cvDilate(image,dest,NULL,pos[0]);
        show_iplimage("Opening&Closing window",dest);
   
  }   
//callback function for slider , implements closing 

void Closing(int id)   
  {
        cvDilate(src,image,NULL,pos[0]);
        cvErode(image,dest,NULL,pos[0]);
        show_iplimage("Opening&Closing window",dest);
   
  }   
//callback function for slider , implements erosion 

void Erosion(int id)   
  {
        
        cvErode(src,dest,NULL,pos[0]);
        show_iplimage("Erosion&Dilation window",dest);
        
  }   
//callback function for slider , implements dilation

void Dilation(int id)   
  {
        
        cvDilate(src,dest,NULL,pos[0]);
        show_iplimage("Erosion&Dilation window",dest);
        
  }   

  

  
      create_slider("slider1","Opening&Closing window",&pos,10,Opening);
      create_slider("slider4","Opening&Closing window",&pos,10,Closing);
      create_slider("slider2","Erosion&Dilation window",&pos,10,Dilation);
      create_slider("slider3","Erosion&Dilation window",&pos,10,Erosion);

  wait_key(0);
      //releases header an dimage data  
      cvReleaseImage(&src);
      cvReleaseImage(&image);
      cvReleaseImage(&dest);
      //destroys windows 
      destroy_window("Opening&Closing window"); 
      destroy_window("Erosion&Dilation window"); 
  

