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

namespace eval CVLkDemo {
	variable mainf
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
    variable trackstate "0"
    variable nightstate "0"
    variable cam "0"
}

proc CVLkDemo::Modify {} {
    set CVLkDemo::cam [.dlg.frame.cb getvalue]
}

proc CVLkDemo::longmenu {on} {
	if {$on} {
		.menubar.file entryconfig 1 -state active
	} else {
		.menubar.file entryconfig 1 -state disabled
	}
}

proc CVLkDemo::longstbar {on} {
	if {$on} {
		pack $CVLkDemo::mainf.status.indf.f0 -side left -fill y -expand 1		
	} else {
		pack forget $CVLkDemo::mainf.status.indf.f0		
	}
}

proc CVLkDemo::longbar {on} {
	if {$on} {
		pack $CVLkDemo::tb.bbox1 -side left -anchor w
		pack $CVLkDemo::tb.sep1 -side left -fill y -padx 4 -anchor w
		pack $CVLkDemo::tb.bbox2 -side left -anchor w
		pack $CVLkDemo::tb.sep2 -side left -fill y -padx 4 -anchor w
	} else {
		pack forget $CVLkDemo::tb.sep2
		pack forget $CVLkDemo::tb.bbox2
		pack forget $CVLkDemo::tb.sep1
		pack forget $CVLkDemo::tb.bbox1
	}
}

proc CVLkDemo::about {} {
    set dlg [Dialog .aboutdlg -parent . -modal local \
                 -separator 1		\
                 -title   "About CVLkDemo"	\
                 -side    right		\
                 -anchor  s			\
                 -default 0]
    $dlg add -name ok -width 5
    
	set top [$dlg getframe]
	    
	image create photo original -file [file join $::image_path pictures/CVLkDemo.gif]
	canvas $top.c -bd 2 -relief ridge -width 295 -height 195 
	$top.c create image 0 0 -anchor nw -image original
	pack $top.c -side top -expand yes -fill x

    set frame [frame $top.f -background white -bd 2 -relief ridge]
    set lab  [label $frame.lab1 -text \
		"Program CVLkDemo v. 1.0 \nIntel corporation. 2001 y."	\
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

proc CVLkDemo::raisetab { } {
    set CVLkDemo::curpage [$CVLkDemo::nb raise]
    set CVLkDemo::curframe [$CVLkDemo::nb getframe $CVLkDemo::curpage].lab
    set pos [lsearch $CVLkDemo::pages $CVLkDemo::curpage]
    set CVLkDemo::curcam [lindex $CVLkDemo::cams $pos]   
}

proc CVLkDemo::createtab {page text} {
    set path [$CVLkDemo::nb insert end $page -text $text \
              -raisecmd CVLkDemo::raisetab]
    
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

proc CVLkDemo::new {} {
    
    incr CVLkDemo::pagescount
    incr CVLkDemo::pagesnum


    if {$CVLkDemo::pagesnum == 1} {
        CVLkDemo::longmenu 1
        CVLkDemo::longbar 1
        CVLkDemo::longstbar 1

        set CVLkDemo::curpage p[expr $CVLkDemo::pagescount]
        lappend CVLkDemo::pages $CVLkDemo::curpage
        lappend CVLkDemo::cams $CVLkDemo::curcam

        set text [format "Camera %i" $CVLkDemo::pagescount]
        CVLkDemo::createtab $CVLkDemo::curpage $text
    
        $CVLkDemo::nb see [$CVLkDemo::nb pages end]
        $CVLkDemo::nb raise [$CVLkDemo::nb pages end]
        update
        pInitCamera
    } else {
    tk_dialog .mes {Message} { CVLkDemo support only one camera.} {} 0 OK" 
    }
}

proc CVLkDemo::close {} {

	set pos [lsearch $CVLkDemo::cams $CVLkDemo::curcam]
	set $CVLkDemo::cams [lreplace $CVLkDemo::cams $pos $pos]
	set $CVLkDemo::pages [lreplace $CVLkDemo::pages $pos $pos]

    $CVLkDemo::nb delete $CVLkDemo::curpage 1
    
	if {$CVLkDemo::curcam != ""} {
		#set ind [$CVLkDemo::tree index $CVLkDemo::curfile]
		#$CVLkDemo::tree delete $CVLkDemo::curfile
	}

    set CVLkDemo::pagesnum [expr $CVLkDemo::pagesnum - 1]

	if {$CVLkDemo::pagesnum == 0} {
		CVLkDemo::longmenu 0
		CVLkDemo::longbar 0
		#CVLkDemo::longstbar 0
		set CVLkDemo::curcam ""
	} else {
		set page [$CVLkDemo::nb pages end]

		set pos [lsearch $CVLkDemo::pages $CVLkDemo::curpage]
		set CVLkDemo::curcam [lindex $CVLkDemo::cams $pos]
			
		$CVLkDemo::nb see $page
        $CVLkDemo::nb raise $page
    }
    
    pCloseCamera
    $CVLkDemo::tb.bbox1.b0 configure -relief raised \
            -image [Bitmap::get [file join $::image_path pictures/captureoff.gif]]
    set CVLkDemo::capturestate 0
}

proc CVLkDemo::capture {} {

    if { $CVLkDemo::capturestate == 1 } {
        $CVLkDemo::tb.bbox1.b0 configure -relief raised \
            -image [Bitmap::get [file join $::image_path pictures/captureoff.gif]]
        set CVLkDemo::capturestate 0
        pStopCamera
        $CVLkDemo::tb.bbox1.b1 configure -state disable
    } else {
        $CVLkDemo::tb.bbox1.b0 configure -relief sunken \
            -image [Bitmap::get [file join $::image_path pictures/capture.gif]]
        set CVLkDemo::capturestate 1
        pStartCamera
        $CVLkDemo::tb.bbox1.b1 configure -state active
    }
}

proc CVLkDemo::track {} {

    if { $CVLkDemo::trackstate == 1 } {
        $CVLkDemo::tb.bbox1.b1 configure -relief raised \
            -image [Bitmap::get [file join $::image_path pictures/trackoff.gif]]
        set CVLkDemo::trackstate 0
        pResetTrack
        $CVLkDemo::tb.bbox1.b2 configure -state disable
    } else {
        $CVLkDemo::tb.bbox1.b1 configure -relief sunken \
            -image [Bitmap::get [file join $::image_path pictures/track.gif]]
        set CVLkDemo::trackstate 1
        pSetTrack
        $CVLkDemo::tb.bbox1.b2 configure -state active
    }
}

proc CVLkDemo::night {} {

    if { $CVLkDemo::nightstate == 1 } {
        $CVLkDemo::tb.bbox1.b2 configure -relief raised \
            -image [Bitmap::get [file join $::image_path pictures/nightoff.gif]]
        set CVLkDemo::nightstate 0
        pResetNight
    } else {
        $CVLkDemo::tb.bbox1.b2 configure -relief sunken \
            -image [Bitmap::get [file join $::image_path pictures/night.gif]]
        set CVLkDemo::nightstate 1
        pSetNight
    }
}

proc CVLkDemo::setvideo {} {
    pSetVideo
}

proc CVLkDemo::camera {} {
    pSetCameraOpt
}

proc CVLkDemo::create { } {
	variable prgindic 0
	variable prgtext
	## Create intro
    ###################################################################
    set top [toplevel .intro -relief raised -borderwidth 2]
    wm withdraw $top
    wm overrideredirect $top 1
	
	image create photo original -file [file join $::image_path pictures/CVLkDemo.gif]
	canvas $top.c -bd 2 -relief ridge -width 295 -height 195 
	$top.c create image 0 0 -anchor nw -image original
	pack $top.c -side top -expand yes -fill x

    set frame [frame $top.f -background white -bd 2 -relief ridge]
    set lab1  [label $frame.lab1 -text "Please wait for loading..."	\
			   -background white -font {times 8}]
    set lab2  [label $frame.lab2 -textvariable CVLkDemo::prgtext	\
			   -background white -font {times 8} -width 35]
    set prg   [ProgressBar $frame.prg -width 50 -height 10		\
			   -background white -variable CVLkDemo::prgindic -maximum 7]
    pack $lab1 $prg $lab2
    pack $frame -side top -expand yes -fill x -padx 2 -pady 2

    BWidget::place $top 0 0 center
    wm deiconify $top

	###################################################################
	
	set CVLkDemo::prgtext "Loading font..."
	update
	SelectFont::loadfont

	incr CVLkDemo::prgindic
	set CVLkDemo::prgtext   "Creating menu..."
    update

    #### Menu
    set menu {
        "&File" all file 0 {
            {command "&New" {} "New document" {} -command CVLkDemo::new}
			{command "&Close" {} "Close the document" {} -state disable	\
				-command CVLkDemo::close}
			{separator}
			{command "E&xit" {} "Exit the program" {} -command exit}
        }
        "&View" all view 0 {
            {checkbutton "&Toolbar" {all view} "Show/hide toolbar" {}	\
                -variable CVLkDemo::showtb	\
                -command {$CVLkDemo::mainf showtoolbar 0 $CVLkDemo::showtb}
            }
			{checkbutton "&Statusbar" {all view} "Show/hide statusbar" {}	\
                -variable CVLkDemo::showstb	\
                -command {
							if {$CVLkDemo::showstb} {
								pack $CVLkDemo::mainf.botf -side bottom -fill x	
							} else {
								pack forget $CVLkDemo::mainf.botf
							}
						 }
            }
        }
		"&Options" all options 0 {
			{command "Came&ra" {} "Colors & fonts setup" {} -command CVLkDemo::camera}
            {command "&Video" {} "Colors & fonts setup" {} -command CVLkDemo::setvideo}
		}
		"&Help" all help 0 {
			{command "&About CVLKDemo" {} "Display the program info" {}	\
			 -command CVLkDemo::about}
        }
    }

    incr CVLkDemo::prgindic
	set CVLkDemo::prgtext   "Creating MainFrame..."
    update

    set CVLkDemo::mainf [MainFrame .mainf -menu $menu	\
                      -textvariable CVLkDemo::statustext]

    menu .menubar.edit -tearoff 0 -background $::default_normal_bg
    MainFrame::_create_entries .mainf .menubar.edit \
		$::default_normal_bg {\
			{command "Cu&t" {} "Cut the selection" {} -command cut}
			{command "&Copy" {} "Copy the selection" {} -command copy}
			{command "&Paste" {} "Paste the clipboard" {} -command paste}
			{separator}
			{command "&Go to.." {} "Move to a specified place" {} -command paste}
        }

	incr CVLkDemo::prgindic
	set CVLkDemo::prgtext   "Creating toolbar..."
    update

    #### toolbars creation
    set CVLkDemo::tb  [$CVLkDemo::mainf addtoolbar]

    set bbox [ButtonBox $CVLkDemo::tb.bbox0 -spacing 0 -padx 1 -pady 1]
    $bbox add -image [Bitmap::get [file join $::image_path pictures/new.gif]] \
        -highlightthickness 0 -takefocus 0 -relief link -borderwidth 2	\
		-padx 1 -pady 1 -helptext "Add new camera" -command CVLkDemo::new
    pack $bbox -side left -anchor w
    
    set sep [Separator $CVLkDemo::tb.sep0 -orient vertical]
    pack $sep -side left -fill y -padx 4 -anchor w

	set bbox [ButtonBox $CVLkDemo::tb.bbox1 -spacing 0 -padx 1 -pady 1]
    $bbox add -image [Bitmap::get [file join $::image_path pictures/captureoff.gif]] \
        -highlightthickness 0 -takefocus 0 -relief raised -borderwidth 2	\
		-padx 1 -pady 1 -helptext "Start/Stop capture" -command CVLkDemo::capture
    $bbox add -image [Bitmap::get [file join $::image_path pictures/trackoff.gif]] \
        -highlightthickness 0 -takefocus 0 -relief raised -borderwidth 2	\
		-padx 1 -pady 1 -helptext "Start/Stop tracking" -command CVLkDemo::track
    $bbox add -image [Bitmap::get [file join $::image_path pictures/nightoff.gif]] \
        -highlightthickness 0 -takefocus 0 -relief raised -borderwidth 2	\
		-padx 1 -pady 1 -helptext "Turn On/Off night mode" -command CVLkDemo::night

	set sep [Separator $CVLkDemo::tb.sep1 -orient vertical]

    set bbox [ButtonBox $CVLkDemo::tb.bbox2 -spacing 0 -padx 1 -pady 1]
    $bbox add -image [Bitmap::get [file join $::image_path pictures/vidopt.gif]] \
        -highlightthickness 0 -takefocus 0 -relief link -borderwidth 1	\
		-padx 1 -pady 1 -helptext "Set video format" \
		-command CVLkDemo::setvideo 

    $bbox add -image [Bitmap::get [file join $::image_path pictures/camopt.gif]] \
        -highlightthickness 0 -takefocus 0 -relief link -borderwidth 1	\
		-padx 1 -pady 1 -helptext "Camera options"\
		-command CVLkDemo::camera 

    set sep [Separator $CVLkDemo::tb.sep2 -orient vertical]

    $CVLkDemo::tb.bbox1.b1 configure -state disable
    $CVLkDemo::tb.bbox1.b2 configure -state disable
    
    incr CVLkDemo::prgindic
    set CVLkDemo::prgtext   "Creating statusbar..."
    update

	$CVLkDemo::mainf addindicator
	$CVLkDemo::mainf.status.indf.f0 configure -relief flat

	label $CVLkDemo::mainf.status.indf.f0.l0  -relief sunken -borderwidth 1 \
        -takefocus 0 -highlightthickness 0 -textvariable CVLkDemo::curcam
	pack $CVLkDemo::mainf.status.indf.f0.l0 -side left -fill y -expand 1

	label $CVLkDemo::mainf.status.indf.f0.l1  -relief flat -borderwidth 1 \
        -takefocus 0 -highlightthickness 0 -text "X:"
	pack $CVLkDemo::mainf.status.indf.f0.l1 -side left -fill y -expand 1

	label $CVLkDemo::mainf.status.indf.f0.l2  -relief sunken -borderwidth 1 \
        -takefocus 0 -highlightthickness 0 -textvariable CVLkDemo::curX
	pack $CVLkDemo::mainf.status.indf.f0.l2 -side left -fill y -expand 1

	label $CVLkDemo::mainf.status.indf.f0.l3  -relief flat -borderwidth 1 \
        -takefocus 0 -highlightthickness 0 -text "Y:"
	pack $CVLkDemo::mainf.status.indf.f0.l3 -side left -fill y -expand 1

	label $CVLkDemo::mainf.status.indf.f0.l4  -relief sunken -borderwidth 1 \
        -takefocus 0 -highlightthickness 0 -textvariable CVLkDemo::curY
	pack $CVLkDemo::mainf.status.indf.f0.l4 -side left -fill y -expand 1
	pack forget $CVLkDemo::mainf.status.indf.f0

	set CVLkDemo::prgtext   "Creating manadger..."
    incr CVLkDemo::prgindic
    set CVLkDemo::nb [NoteBook $CVLkDemo::mainf.frame.nb -side top]
    pack $CVLkDemo::nb -fill both -expand yes -padx 1 -pady 1
    
	set CVLkDemo::prgtext   "Done"
    incr CVLkDemo::prgindic

    pack $CVLkDemo::mainf -fill both -expand yes
    update idletasks

	unset CVLkDemo::prgindic
	unset CVLkDemo::prgtext

    destroy .intro
}

proc main {} {
    package require BWidget
    wm withdraw .
    wm title . "CVLKDemo"

    CVLkDemo::create

    BWidget::place . 640 480 center
    wm deiconify .
    raise .
    wm geometry . 640x480

    focus -force .
}

main
