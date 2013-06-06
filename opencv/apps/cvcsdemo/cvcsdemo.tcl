#########################################################################################
#
#  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
#
#  By downloading, copying, installing or using the software you agree to this license.
#  If you do not agree to this license, do not download, install,
#  copy or use the software.
#
#
#                        Intel License Agreement
#                For Open Source Computer Vision Library
#
# Copyright (C) 2000, Intel Corporation, all rights reserved.
# Third party copyrights are property of their respective owners.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
#   * Redistribution's of source code must retain the above copyright notice,
#     this list of conditions and the following disclaimer.
#
#   * Redistribution's in binary form must reproduce the above copyright notice,
#     this list of conditions and the following disclaimer in the documentation
#     and/or other materials provided with the distribution.
#
#   * The name of Intel Corporation may not be used to endorse or promote products
#     derived from this software without specific prior written permission.
#
# This software is provided by the copyright holders and contributors "as is" and
# any express or implied warranties, including, but not limited to, the implied
# warranties of merchantability and fitness for a particular purpose are disclaimed.
# In no event shall the Intel Corporation or contributors be liable for any direct,
# indirect, incidental, special, exemplary, or consequential damages
# (including, but not limited to, procurement of substitute goods or services;
# loss of use, data, or profits; or business interruption) however caused
# and on any theory of liability, whether in contract, strict liability,
# or tort (including negligence or otherwise) arising in any way out of
# the use of this software, even if advised of the possibility of such damage.
#
#

if {$tcl_platform(platform) == "windows"} {
    set default_normal_bg SystemButtonFace
    set default_normal_fg SystemButtonText
    set default_light_bg SystemScrollbar
    set default_dark_bg SystemDisabledText
    set default_window_bg SystemWindow
    set default_window_fg SystemWindowText
    set default_select_bg SystemHighlight
    set default_select_fg SystemHighlightText
} else {
    set default_normal_bg #909090
    set default_normal_fg #000000
    set default_light_bg #000000
    set default_dark_bg #303030
    set default_window_bg #909090
    set default_window_fg #000000
    set default_select_bg #000080
    set default_select_fg #ffffff
}

namespace eval CVCsDemo {
	variable mainf
    variable sclframe
	variable tb
	variable statustext

    variable nb

	variable showtb 1
	variable showstb 1
	
    variable curcam

    variable curpage
    variable curframe
	variable curX "---"
	variable curY "---"
    
    variable pagesnum 0
    variable pagescount 0
    
    variable cams {}
    variable pages {}

    variable capturestate "0"
    variable pausestate "0"
	variable avistate "0"
    variable trackstate "0"
    variable nightstate "0"
    variable histstate "0"
    variable cam "0"
}

proc CVCsDemo::Modify {} {
    set CVCsDemo::cam [.dlg.frame.cb getvalue]
}

proc CVCsDemo::longmenu {on} {
	if {$on} {
		.menubar.file entryconfig 1 -state active
	} else {
		.menubar.file entryconfig 1 -state disabled
	}
}

proc CVCsDemo::longstbar {on} {
	if {$on} {
		pack $CVCsDemo::mainf.status.indf.f0 -side left -fill y -expand 1		
	} else {
		pack forget $CVCsDemo::mainf.status.indf.f0		
	}
}

proc CVCsDemo::longbar {on} {
	if {$on} {
		pack $CVCsDemo::tb.bbox1 -side left -anchor w
		pack $CVCsDemo::tb.sep1 -side left -fill y -padx 4 -anchor w
		pack $CVCsDemo::tb.bbox2 -side left -anchor w
		pack $CVCsDemo::tb.sep2 -side left -fill y -padx 4 -anchor w
        pack $CVCsDemo::tb.bbox3 -side left -anchor w
		pack $CVCsDemo::tb.sep3 -side left -fill y -padx 4 -anchor w
        pack $CVCsDemo::tb.bbox4 -side left -anchor w
        pack $CVCsDemo::sclframe -side bottom -expand no -anchor sw -fill x
	} else {
        pack forget $CVCsDemo::tb.bbox4
        pack forget $CVCsDemo::tb.sep3
		pack forget $CVCsDemo::tb.bbox3
		pack forget $CVCsDemo::tb.sep2
		pack forget $CVCsDemo::tb.bbox2
		pack forget $CVCsDemo::tb.sep1
		pack forget $CVCsDemo::tb.bbox1
        pack forget $CVCsDemo::sclframe
	}
}

proc CVCsDemo::about {} {
    set dlg [Dialog .aboutdlg -parent . -modal local \
                 -separator 1		\
                 -title   "About CVCsDemo"	\
                 -side    right		\
                 -anchor  s			\
                 -default 0]
    $dlg add -name ok -width 5
    
	set top [$dlg getframe]
	    
	image create photo original -file [file join $::image_path pictures/CVCsDemo.gif]
	canvas $top.c -bd 2 -relief ridge -width 295 -height 195 
	$top.c create image 0 0 -anchor nw -image original
	pack $top.c -side top -expand yes -fill x

    set frame [frame $top.f -background white -bd 2 -relief ridge]
    set lab  [label $frame.lab1 -text \
		"Program CVCsDemo v. 1.0 \nIntel corporation. 2001 y."	\
			   -background white -font {times 8}]
    pack $lab
    pack $frame -side top -expand yes -fill x -padx 2 -pady 2

    $dlg draw
    destroy $dlg
}

proc getvar {name value} {
    upvar $name localVar
    upvar $value lvalue
	
    set localVar $lvalue
}

proc CVCsDemo::raisetab { } {
    set CVCsDemo::curpage [$CVCsDemo::nb raise]
    set CVCsDemo::curframe [$CVCsDemo::nb getframe $CVCsDemo::curpage].lab
    set pos [lsearch $CVCsDemo::pages $CVCsDemo::curpage]
    set CVCsDemo::curcam [lindex $CVCsDemo::cams $pos]   
}

proc CVCsDemo::createtab {page text} {
    set path [$CVCsDemo::nb insert end $page -text $text \
              -raisecmd CVCsDemo::raisetab]
    
    label $path.lab -text "" -bg black -relief sunken
    pack $path.lab  -side top  -expand yes -fill both

    bind $path.lab <ButtonPress-1> {
        pButtonPress %x %y
	}

    bind $path.lab <ButtonRelease-1> {
        pButtonRelease %x %y
	}

    bind $path.lab <Motion> {
        pMotion %x %y
	}

    bind $path.lab <Configure> {
        pConfigure
	}
}

proc CVCsDemo::new {} {

	if {$CVCsDemo::pagesnum == 0} {
		set CVCsDemo::avistate "0"
    
		incr CVCsDemo::pagescount
		incr CVCsDemo::pagesnum

        CVCsDemo::longmenu 1
        CVCsDemo::longbar 1
        CVCsDemo::longstbar 1

        set CVCsDemo::curpage p[expr $CVCsDemo::pagescount]
        lappend CVCsDemo::pages $CVCsDemo::curpage
        lappend CVCsDemo::cams $CVCsDemo::curcam

        set text [format "Camera %i" $CVCsDemo::pagescount]
        CVCsDemo::createtab $CVCsDemo::curpage $text
    
        $CVCsDemo::nb see [$CVCsDemo::nb pages end]
        $CVCsDemo::nb raise [$CVCsDemo::nb pages end]
        update
        pInitCamera
    } else {
		tk_dialog .mes {Message} { CVCsDemo support only one camera.} {} 0 OK" 
    }
}

proc CVCsDemo::close {} {

	set pos [lsearch $CVCsDemo::cams $CVCsDemo::curcam]
	set $CVCsDemo::cams [lreplace $CVCsDemo::cams $pos $pos]
	set $CVCsDemo::pages [lreplace $CVCsDemo::pages $pos $pos]

    $CVCsDemo::nb delete $CVCsDemo::curpage 1
    
	if {$CVCsDemo::curcam != ""} {
		#set ind [$CVCsDemo::tree index $CVCsDemo::curfile]
		#$CVCsDemo::tree delete $CVCsDemo::curfile
	}

    set CVCsDemo::pagesnum [expr $CVCsDemo::pagesnum - 1]

	if {$CVCsDemo::pagesnum == 0} {
		CVCsDemo::longmenu 0
		CVCsDemo::longbar 0
		#CVCsDemo::longstbar 0
		set CVCsDemo::curcam ""
	} else {
		set page [$CVCsDemo::nb pages end]

		set pos [lsearch $CVCsDemo::pages $CVCsDemo::curpage]
		set CVCsDemo::curcam [lindex $CVCsDemo::cams $pos]
			
		$CVCsDemo::nb see $page
        $CVCsDemo::nb raise $page
    }
    
    if {$CVCsDemo::avistate == 0} {
		pCloseCamera
	} else {
		pStopAvi
	}

    $CVCsDemo::tb.bbox1.b0 configure -relief raised \
            -image [Bitmap::get [file join $::image_path pictures/captureoff.gif]]
    set CVCsDemo::capturestate 0
}

proc CVCsDemo::pause {} {
	
	if { $CVCsDemo::pausestate == 1 } {
        $CVCsDemo::tb.bbox1.b1 configure -relief raised \
            -image [Bitmap::get [file join $::image_path pictures/pause.gif]]
        set CVCsDemo::pausestate 0
		
		if {$CVCsDemo::avistate == 0} {
			pResumeCamera
		} else {
			pResumeAvi
		}

        #$CVCsDemo::tb.bbox1.b1 configure -state disable
		#$CVCsDemo::tb.bbox2.b0 configure -state disable
        #$CVCsDemo::tb.bbox2.b1 configure -state disable
        #$CVCsDemo::tb.bbox2.b2 configure -state disable
    } else {
        $CVCsDemo::tb.bbox1.b1 configure -relief sunken \
            -image [Bitmap::get [file join $::image_path pictures/pause.gif]]
        set CVCsDemo::pausestate 1

        if {$CVCsDemo::avistate == 0} {
			pPauseCamera
		} else {
			pPauseAvi
		}

        #$CVCsDemo::tb.bbox1.b1 configure -state active
		#$CVCsDemo::tb.bbox2.b0 configure -state active
        #$CVCsDemo::tb.bbox2.b1 configure -state disable
        #$CVCsDemo::tb.bbox2.b2 configure -state disable
    }
}

proc CVCsDemo::capture {} {
	
	if { $CVCsDemo::capturestate == 1 } {
        $CVCsDemo::tb.bbox1.b0 configure -relief raised \
            -image [Bitmap::get [file join $::image_path pictures/captureoff.gif]]
        set CVCsDemo::capturestate 0
        pStopCamera

        $CVCsDemo::tb.bbox1.b1 configure -state disable
		$CVCsDemo::tb.bbox2.b0 configure -state disable
        $CVCsDemo::tb.bbox2.b1 configure -state disable
        $CVCsDemo::tb.bbox2.b2 configure -state disable
    } else {
        $CVCsDemo::tb.bbox1.b0 configure -relief sunken \
            -image [Bitmap::get [file join $::image_path pictures/capture.gif]]
        set CVCsDemo::capturestate 1

        if {$CVCsDemo::avistate == 0} {
			pStartCamera
		} else {
			pStartAvi
		}

        $CVCsDemo::tb.bbox1.b1 configure -state active
		$CVCsDemo::tb.bbox2.b0 configure -state active
        $CVCsDemo::tb.bbox2.b1 configure -state disable
        $CVCsDemo::tb.bbox2.b2 configure -state disable
    }
}

proc CVCsDemo::track {} {

    if { $CVCsDemo::trackstate == 1 } {
        $CVCsDemo::tb.bbox2.b0 configure -relief raised \
            -image [Bitmap::get [file join $::image_path pictures/trackoff.gif]]
        set CVCsDemo::trackstate 0
        pResetTrack
        $CVCsDemo::tb.bbox2.b1 configure -state disable
        $CVCsDemo::tb.bbox2.b2 configure -state disable
    } else {
        $CVCsDemo::tb.bbox2.b0 configure -relief sunken \
            -image [Bitmap::get [file join $::image_path pictures/track.gif]]
        set CVCsDemo::trackstate 1
        pSetTrack
        $CVCsDemo::tb.bbox2.b1 configure -state active
        $CVCsDemo::tb.bbox2.b2 configure -state active
    }
}

proc CVCsDemo::night {} {

    if { $CVCsDemo::nightstate == 1 } {
        $CVCsDemo::tb.bbox2.b1 configure -relief raised \
            -image [Bitmap::get [file join $::image_path pictures/nightoff.gif]]
        set CVCsDemo::nightstate 0
        pResetNight
        $CVCsDemo::tb.bbox2.b2 configure -state active
    } else {
        $CVCsDemo::tb.bbox2.b1 configure -relief sunken \
            -image [Bitmap::get [file join $::image_path pictures/night.gif]]
        set CVCsDemo::nightstate 1
        pSetNight
        $CVCsDemo::tb.bbox2.b2 configure -state disable
    }
}

proc CVCsDemo::gist {} {

    if { $CVCsDemo::histstate == 1 } {
        $CVCsDemo::tb.bbox2.b2 configure -relief raised \
            -image [Bitmap::get [file join $::image_path pictures/gist.gif]]
        set CVCsDemo::histstate 0
        pResetHist
        $CVCsDemo::tb.bbox2.b1 configure -state active
    } else {
        $CVCsDemo::tb.bbox2.b2 configure -relief sunken \
            -image [Bitmap::get [file join $::image_path pictures/gist.gif]]
        set CVCsDemo::histstate 1
        pSetHist
        $CVCsDemo::tb.bbox2.b1 configure -state disable
    }
}

proc CVCsDemo::setvideo {} {
    pSetVideo
}

proc CVCsDemo::camera {} {
    pSetCameraOpt
}

proc CVCsDemo::create { } {
	variable prgindic 0
	variable prgtext
	## Create intro
    ###################################################################
    set top [toplevel .intro -relief raised -borderwidth 2]
    wm withdraw $top
    wm overrideredirect $top 1
	
	image create photo original -file [file join $::image_path pictures/CVCsDemo.gif]
	canvas $top.c -bd 2 -relief ridge -width 295 -height 195 
	$top.c create image 0 0 -anchor nw -image original
	pack $top.c -side top -expand yes -fill x

    set frame [frame $top.f -background white -bd 2 -relief ridge]
    set lab1  [label $frame.lab1 -text "Please wait for loading..."	\
			   -background white -font {times 8}]
    set lab2  [label $frame.lab2 -textvariable CVCsDemo::prgtext	\
			   -background white -font {times 8} -width 35]
    set prg   [ProgressBar $frame.prg -width 50 -height 10		\
			   -background white -variable CVCsDemo::prgindic -maximum 7]
    pack $lab1 $prg $lab2
    pack $frame -side top -expand yes -fill x -padx 2 -pady 2

    BWidget::place $top 0 0 center
    wm deiconify $top

	###################################################################
	
	set CVCsDemo::prgtext "Loading font..."
	update
	SelectFont::loadfont

	incr CVCsDemo::prgindic
	set CVCsDemo::prgtext   "Creating menu..."
    update

    #### Menu
    set menu {
        "&File" all file 0 {
            {command "&New" {} "New document" {} -command CVCsDemo::new}
			{command "&Close" {} "Close the document" {} -state disable	\
				-command CVCsDemo::close}
			{separator}
			{command "E&xit" {} "Exit the program" {} -command exit}
        }
        "&View" all view 0 {
            {checkbutton "&Toolbar" {all view} "Show/hide toolbar" {}	\
                -variable CVCsDemo::showtb	\
                -command {$CVCsDemo::mainf showtoolbar 0 $CVCsDemo::showtb}
            }
			{checkbutton "&Statusbar" {all view} "Show/hide statusbar" {}	\
                -variable CVCsDemo::showstb	\
                -command {
							if {$CVCsDemo::showstb} {
								pack $CVCsDemo::mainf.botf -side bottom -fill x	
							} else {
								pack forget $CVCsDemo::mainf.botf
							}
						 }
            }
        }
		"&Options" all options 0 {
			{command "Came&ra" {} "Colors & fonts setup" {} -command CVCsDemo::camera}
            {command "&Video" {} "Colors & fonts setup" {} -command CVCsDemo::setvideo}
		}
		"&Help" all help 0 {
			{command "&About CVCsDemo" {} "Display the program info" {}	\
			 -command CVCsDemo::about}
        }
    }

    incr CVCsDemo::prgindic
	set CVCsDemo::prgtext   "Creating MainFrame..."
    update

    set CVCsDemo::mainf [MainFrame .mainf -menu $menu	\
                      -textvariable CVCsDemo::statustext]

    menu .menubar.edit -tearoff 0 -background $::default_normal_bg
    MainFrame::_create_entries .mainf .menubar.edit \
		$::default_normal_bg {\
			{command "Cu&t" {} "Cut the selection" {} -command cut}
			{command "&Copy" {} "Copy the selection" {} -command copy}
			{command "&Paste" {} "Paste the clipboard" {} -command paste}
			{separator}
			{command "&Go to.." {} "Move to a specified place" {} -command paste}
        }

	incr CVCsDemo::prgindic
	set CVCsDemo::prgtext   "Creating toolbar..."
    update

    #### toolbars creation
    set CVCsDemo::tb  [$CVCsDemo::mainf addtoolbar]

    set bbox [ButtonBox $CVCsDemo::tb.bbox0 -spacing 0 -padx 1 -pady 1]
    $bbox add -image [Bitmap::get [file join $::image_path pictures/new.gif]] \
        -highlightthickness 0 -takefocus 0 -relief link -borderwidth 2	\
		-padx 1 -pady 1 -helptext "Add new camera" -command CVCsDemo::new
	$bbox add -image [Bitmap::get [file join $::image_path pictures/open.gif]] \
        -highlightthickness 0 -takefocus 0 -relief link -borderwidth 2	\
		-padx 1 -pady 1 -helptext "Load Avi" -command pInitAvi
    pack $bbox -side left -anchor w
    
    set sep [Separator $CVCsDemo::tb.sep0 -orient vertical]
    pack $sep -side left -fill y -padx 4 -anchor w

	set bbox [ButtonBox $CVCsDemo::tb.bbox1 -spacing 0 -padx 1 -pady 1]
    $bbox add -image [Bitmap::get [file join $::image_path pictures/captureoff.gif]] \
        -highlightthickness 0 -takefocus 0 -relief raised -borderwidth 2	\
		-padx 1 -pady 1 -helptext "Start/Stop capture" -command CVCsDemo::capture
	$bbox add -image [Bitmap::get [file join $::image_path pictures/pause.gif]] \
        -highlightthickness 0 -takefocus 0 -relief raised -borderwidth 2	\
		-padx 1 -pady 1 -helptext "Pause" -command CVCsDemo::pause -state disable
	   
    set sep [Separator $CVCsDemo::tb.sep1 -orient vertical]

    set bbox [ButtonBox $CVCsDemo::tb.bbox2 -spacing 0 -padx 1 -pady 1]
    $bbox add -image [Bitmap::get [file join $::image_path pictures/trackoff.gif]] \
        -highlightthickness 0 -takefocus 0 -relief raised -borderwidth 2	\
		-padx 1 -pady 1 -helptext "Start/Stop tracking" -command CVCsDemo::track
    $bbox add -image [Bitmap::get [file join $::image_path pictures/nightoff.gif]] \
        -highlightthickness 0 -takefocus 0 -relief raised -borderwidth 2	\
		-padx 1 -pady 1 -helptext "Turn On/Off night mode" -command CVCsDemo::night
    $bbox add -image [Bitmap::get [file join $::image_path pictures/gist.gif]] \
        -highlightthickness 0 -takefocus 0 -relief raised -borderwidth 2	\
		-padx 1 -pady 1 -helptext "Turn On/Off histogram mode" -command CVCsDemo::gist


	set sep [Separator $CVCsDemo::tb.sep2 -orient vertical]

    set bbox [ButtonBox $CVCsDemo::tb.bbox3 -spacing 0 -padx 1 -pady 1]
    $bbox add -image [Bitmap::get [file join $::image_path pictures/vidopt.gif]] \
        -highlightthickness 0 -takefocus 0 -relief link -borderwidth 1	\
		-padx 1 -pady 1 -helptext "Set video format" \
		-command CVCsDemo::setvideo 
    $bbox add -image [Bitmap::get [file join $::image_path pictures/camopt.gif]] \
        -highlightthickness 0 -takefocus 0 -relief link -borderwidth 1	\
		-padx 1 -pady 1 -helptext "Camera options"\
		-command CVCsDemo::camera 

    set sep [Separator $CVCsDemo::tb.sep3 -orient vertical]

    set bbox [ButtonBox $CVCsDemo::tb.bbox4 -spacing 0 -padx 1 -pady 1]
    
    set CVCsDemo::sclframe [frame $CVCsDemo::mainf.sclf]
    set lab1 [label $CVCsDemo::sclframe.lab1 -text "Bins:"]
    set scl1 [scale $CVCsDemo::sclframe.scale1 -orient horizontal -length 32 -from 1 -to 255 \
	    -command "pSetBins" -tickinterval 254]
    set lab2 [label $CVCsDemo::sclframe.lab2 -text "S:"]
    set scl2 [scale $CVCsDemo::sclframe.scale2 -orient horizontal -length 32 -from 0 -to 255 \
	    -command "pSetS" -tickinterval 255]
    set lab3 [label $CVCsDemo::sclframe.lab3 -text "V1:"]
    set scl3 [scale $CVCsDemo::sclframe.scale3 -orient horizontal -length 32 -from 0 -to 255 \
	    -command "pSetV1" -tickinterval 255]
    set lab4 [label $CVCsDemo::sclframe.lab4 -text "V2:"]
    set scl4 [scale $CVCsDemo::sclframe.scale4 -orient horizontal -length 32 -from 0 -to 255 \
	    -command "pSetV2" -tickinterval 255]

    pack $lab1 -side left -expand no -anchor n
    pack $scl1 -side left -expand yes -anchor n -fill x
    pack $lab2 -side left -expand no -anchor n
    pack $scl2 -side left -expand yes -anchor n -fill x
    pack $lab3 -side left -expand no -anchor n
    pack $scl3 -side left -expand yes -anchor n -fill x
    pack $lab4 -side left -expand no -anchor n
    pack $scl4 -side left -expand yes -anchor n -fill x
    
    $scl1 set 10
    $scl2 set 20
    $scl3 set 40
    $scl4 set 255

    $CVCsDemo::tb.bbox2.b0 configure -state disable
    $CVCsDemo::tb.bbox2.b1 configure -state disable
    $CVCsDemo::tb.bbox2.b2 configure -state disable

    incr CVCsDemo::prgindic
    set CVCsDemo::prgtext   "Creating statusbar..."
    update

	$CVCsDemo::mainf addindicator
	$CVCsDemo::mainf.status.indf.f0 configure -relief flat

	label $CVCsDemo::mainf.status.indf.f0.l0  -relief sunken -borderwidth 1 \
        -takefocus 0 -highlightthickness 0 -textvariable CVCsDemo::curcam
	pack $CVCsDemo::mainf.status.indf.f0.l0 -side left -fill y -expand 1

	label $CVCsDemo::mainf.status.indf.f0.l1  -relief flat -borderwidth 1 \
        -takefocus 0 -highlightthickness 0 -text "X:"
	pack $CVCsDemo::mainf.status.indf.f0.l1 -side left -fill y -expand 1

	label $CVCsDemo::mainf.status.indf.f0.l2  -relief sunken -borderwidth 1 \
        -takefocus 0 -highlightthickness 0 -textvariable CVCsDemo::curX
	pack $CVCsDemo::mainf.status.indf.f0.l2 -side left -fill y -expand 1

	label $CVCsDemo::mainf.status.indf.f0.l3  -relief flat -borderwidth 1 \
        -takefocus 0 -highlightthickness 0 -text "Y:"
	pack $CVCsDemo::mainf.status.indf.f0.l3 -side left -fill y -expand 1

	label $CVCsDemo::mainf.status.indf.f0.l4  -relief sunken -borderwidth 1 \
        -takefocus 0 -highlightthickness 0 -textvariable CVCsDemo::curY
	pack $CVCsDemo::mainf.status.indf.f0.l4 -side left -fill y -expand 1
	pack forget $CVCsDemo::mainf.status.indf.f0

	set CVCsDemo::prgtext   "Creating manadger..."
    incr CVCsDemo::prgindic
    set CVCsDemo::nb [NoteBook $CVCsDemo::mainf.frame.nb -side top]
    pack $CVCsDemo::nb -fill both -expand yes -padx 1 -pady 1
    
	set CVCsDemo::prgtext   "Done"
    incr CVCsDemo::prgindic

    pack $CVCsDemo::mainf -fill both -expand yes
    update idletasks

	unset CVCsDemo::prgindic
	unset CVCsDemo::prgtext

    destroy .intro
}

proc main {} {
    package require BWidget
    wm withdraw .
    wm title . "CVCsDemo"

    CVCsDemo::create

    BWidget::place . 640 480 center
    wm deiconify .
    raise .
    wm geometry . 640x480

    focus -force .
}

main
