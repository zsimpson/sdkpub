/* the script demostrates iterative construction of
   delaunay triangulation and voronoi tesselation */

CvSubdiv2D* init_delaunay( CvMemStorage* storage,
                           CvRect rect )
{
    CvSubdiv2D* subdiv;
    
    subdiv = cvCreateSubdiv2D( CV_SEQ_KIND_SUBDIV2D, sizeof(*subdiv),
                               sizeof(CvSubdiv2DPoint),
                               sizeof(CvQuadEdge2D),
                               storage );
    cvInitSubdivDelaunay2D( subdiv, rect );
    
    return subdiv;
}


void draw_subdiv_point( IplImage* img, CvPoint2D32f fp, int color )
{
    cvCircle( img, cvPoint(cvRound(fp.x), cvRound(fp.y)), 3, color, CV_FILLED );    
}


void draw_subdiv_edge( IplImage* img, CvSubdiv2DEdge edge, int color )
{
    CvSubdiv2DPoint* org_pt;
    CvSubdiv2DPoint* dst_pt;
    CvPoint2D32f org;
    CvPoint2D32f dst;
    CvPoint iorg, idst;
    
    org_pt = cvSubdiv2DEdgeOrg(edge);
    dst_pt = cvSubdiv2DEdgeDst(edge);
    
    if( org_pt && dst_pt )
    {
        org = org_pt->pt;
        dst = dst_pt->pt;
        
        iorg = cvPoint( cvRound( org.x ), cvRound( org.y ));
        idst = cvPoint( cvRound( dst.x ), cvRound( dst.y ));
    
        cvLineAA( img, iorg, idst, color, 0 );
    }
}


void draw_subdiv( IplImage* img, CvSubdiv2D* subdiv,
                  int delaunay_color, int voronoi_color )
{
    CvSeqReader  reader;
    int i, total = subdiv->edges->total;
    int elem_size = subdiv->edges->elem_size;
    int color;
    
    cvStartReadSeq( (CvSeq*)(subdiv->edges), &reader, 0 );
    
    for( i = 0; i < total; i++ )
    {
        CvQuadEdge2D* edge = (CvQuadEdge2D*)(reader.ptr);
        
        if( CV_IS_SET_ELEM_EXISTS( edge ))
        {
            draw_subdiv_edge( img, (CvSubdiv2DEdge)edge + 1, voronoi_color );
            draw_subdiv_edge( img, (CvSubdiv2DEdge)edge, delaunay_color );
        }
        
        CV_NEXT_SEQ_ELEM( elem_size, reader );
    }
}


void locate_point( CvSubdiv2D* subdiv, CvPoint2D32f fp, IplImage* img,
                   int active_color )
{
    CvSubdiv2DEdge e = 0;
    CvSubdiv2DEdge e0 = 0;
    CvSubdiv2DPoint* p = 0;
    CvSubdiv2DPointLocation location = cvSubdiv2DLocate( subdiv, fp, &e0, &p );
    
    if( e0 )
    {
        e = e0;
        do
        {
            draw_subdiv_edge( img, e, active_color );
            e = cvSubdiv2DGetEdge(e,CV_NEXT_AROUND_LEFT);
        }
        while( e != e0 );
    }
    
    draw_subdiv_point( img, fp, active_color );
}


void draw_subdiv_facet( IplImage* img, CvSubdiv2DEdge edge )
{
    CvSubdiv2DEdge t = edge;
    int i, count = 0;
    CvPoint* buf = 0;

    // count number of edges in facet 
    do
    {
        count++;
        t = cvSubdiv2DGetEdge( t, CV_NEXT_AROUND_LEFT );
    } while (t != edge );
    
    buf = (CvPoint*)malloc( count * sizeof(buf[0]));
    
    // gather points
    t = edge;
    for( i = 0; i < count; i++ )
    {
        CvSubdiv2DPoint* pt = cvSubdiv2DEdgeOrg( t );
        if( !pt ) break;
        buf[i] = cvPoint( cvRound(pt->pt.x), cvRound(pt->pt.y));
        t = cvSubdiv2DGetEdge( t, CV_NEXT_AROUND_LEFT );
    }
    
    if( i == count )
    {
        CvSubdiv2DPoint* pt = cvSubdiv2DEdgeDst( cvSubdiv2DRotateEdge( edge, 1 ));
        cvFillConvexPoly( img, buf, count, CV_RGB(rand(),rand(),rand()));
        cvPolyLineAA( img, &buf, &count, 1, 1, CV_RGB(0,0,0), 0);
        draw_subdiv_point( img, pt->pt, CV_RGB(0,0,0));
    }
    free( buf );        
}

void paint_voronoi( CvSubdiv2D* subdiv, IplImage* img )
{
    CvSeqReader  reader;
    int i, total = subdiv->edges->total;
    int elem_size = subdiv->edges->elem_size;

    cvCalcSubdivVoronoi2D( subdiv );
    
    cvStartReadSeq( (CvSeq*)(subdiv->edges), &reader, 0 );
    
    for( i = 0; i < total; i++ )
    {
        CvQuadEdge2D* edge = (CvQuadEdge2D*)(reader.ptr);
        
        if( CV_IS_SET_ELEM_EXISTS( edge ))
        {
            CvSubdiv2DEdge e = (CvSubdiv2DEdge)edge;
            // left
            draw_subdiv_facet( img, cvSubdiv2DRotateEdge( e, 1 ));
            
            // right
            draw_subdiv_facet( img, cvSubdiv2DRotateEdge( e, 3 ));
        }
        
        CV_NEXT_SEQ_ELEM( elem_size, reader );
    }    
}


void run(void)
{
    char win[] = "source";
    int i;
    int q_flag = 0;
    int draw_flag = 0;
    CvRect rect = { 0, 0, 600, 600 };
    CvMemStorage* storage;
    CvSubdiv2D* subdiv;
    IplImage* img;
    int active_facet_color, delaunay_color, voronoi_color, bkgnd_color;
    
    active_facet_color = CV_RGB( 255, 0, 0 );
    delaunay_color  = CV_RGB( 0,0,0);
    voronoi_color = CV_RGB(0, 180, 0);
    bkgnd_color = CV_RGB(255,255,255);
    
    img = cvCreateImage( cvSize(rect.width,rect.height), 8, 3 );
     
    named_window( win, 0 );
    cvFillImage( img, bkgnd_color );
     
    storage = cvCreateMemStorage(0);
    subdiv = init_delaunay( storage, rect );
    
    printf("Delaunay triangulation will be build now interactively.\n"
           "To stop the process, press Escape\n\n");    
    
    for( i = 0; i < 200; i++ )
    {
        CvPoint2D32f fp = cvPoint2D32f( (float)(rand()%(rect.width-10)+5),
                                        (float)(rand()%(rect.height-10)+5));
                                        
        locate_point( subdiv, fp, img, active_facet_color );
        show_iplimage( win, img );
        
        q_flag = wait_key_ex( win, 100 ) == 27;
        if( q_flag ) break;
        
        cvSubdivDelaunay2DInsert( subdiv, fp );
        cvCalcSubdivVoronoi2D( subdiv );
        cvFillImage( img, bkgnd_color );
        draw_subdiv( img, subdiv, delaunay_color, voronoi_color );
        show_iplimage( win, img );
        
        q_flag = wait_key_ex( win, 100 ) == 27;
        if( q_flag ) break;
    }
    
    if( !q_flag ) wait_key( win );
    cvFillImage( img, bkgnd_color );
    paint_voronoi( subdiv, img );
    show_iplimage( win, img );
    
    cvReleaseMemStorage( &storage );
    cvReleaseImage(&img);
}

run();





