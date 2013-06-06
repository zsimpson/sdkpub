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

#set image_path "./"

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

set defaults {default_normal_bg default_normal_fg default_light_bg default_dark_bg\
                       default_window_bg default_window_fg default_select_bg default_select_fg}

# Default Colors
set EditorTextbg $default_window_bg
set EditorTextfg $default_window_fg
set EditorStringfg #00FF00
set EditorNumberfg #00FFFF
set EditorCommentfg #808080
set EditorKeywordfg #FFFF00
set EditorSelectbg $default_select_bg
set EditorSelectfg $default_select_fg
set EditorCursorbg $default_light_bg

# Default Fonts
set EditorTextfont    "{Courier} 12 normal roman"
set EditorStringfont  "{Courier} 12 normal roman"
set EditorNumberfont  "{Courier} 12 normal roman"
set EditorCommentfont "{Courier} 12 normal italic"
set EditorKeywordfont "{Courier} 12 normal roman"

pLoadColors

proc ClearColors {offset1 offset2 fedit} {
	foreach i [$fedit tag names] {
	#if {$i!="select"} then {
		$fedit tag remove $i "0.0 + $offset1 chars" "0.0 + $offset2 chars"
	#	}
	}
}

namespace eval CVEnv {
	variable mainf
	variable tb
	variable statustext
    variable inputvar ""
    variable inputdata ""
    variable inputlist {}

	variable pw
	variable ptop
	variable pbot
	variable pwch
	variable prig
	variable nblef
	variable nbrig
	variable nbbot
	variable outtx
    variable parsetx
	variable tree
    variable inputcb

	variable showtb 1
	variable showstb 1
	variable showlp 1
	variable showbp 1

    variable savebefore 1
    variable clearoutputbefore 1
    variable clearerrorbefore 1

	variable curfile
    variable curpage
    variable curframe
	variable curln "--"
	variable curcol "--"
    variable curinput 0

    variable pagesnum 0
    variable pagescount 0
    
    variable files {}
    variable pages {}
}

proc CVEnv::leftpane {on} {
	if {$on} {
	pack forget $CVEnv::nbrig
	
	pack $CVEnv::nbrig -in $CVEnv::prig -fill both -expand yes -padx 1 -pady 1
	pack $CVEnv::pwch -fill both -expand yes
	} else {
		pack forget $CVEnv::nbrig
		pack forget $CVEnv::pwch

		pack $CVEnv::nbrig -in $CVEnv::ptop -fill both -expand yes -padx 1 -pady 1
	}
}

proc CVEnv::longmenu {on} {
	if {$on} {
		.menubar.file entryconfig 2 -state active
		.menubar.file entryconfig 4 -state active
		.menubar.file entryconfig 5 -state active

		.menubar insert 1 cascade -label "Edit" -menu .menubar.edit\
			-underline 0
	} else {
		.menubar.file entryconfig 2 -state disabled
		.menubar.file entryconfig 4 -state disabled
		.menubar.file entryconfig 5 -state disabled
	    
		.menubar delete 1 1
	}
}

proc CVEnv::longstbar {on} {
	if {$on} {
		pack $CVEnv::mainf.status.indf.f0 -side left -fill y -expand 1		
	} else {
		pack forget $CVEnv::mainf.status.indf.f0		
	}
}

proc CVEnv::longbar {on} {
	if {$on} {
		pack $CVEnv::tb.bbox1 -side left -anchor w
		pack $CVEnv::tb.sep1 -side left -fill y -padx 4 -anchor w
		pack $CVEnv::tb.bbox2 -side left -anchor w
		pack $CVEnv::tb.sep2 -side left -fill y -padx 4 -anchor w
		pack $CVEnv::tb.bbox3 -side left -anchor w
		pack $CVEnv::tb.sep3 -side left -fill y -padx 4 -anchor w
	} else {
		pack forget $CVEnv::tb.sep3
		pack forget $CVEnv::tb.bbox3
		pack forget $CVEnv::tb.sep2
		pack forget $CVEnv::tb.bbox2
		pack forget $CVEnv::tb.sep1
		pack forget $CVEnv::tb.bbox1
	}
}

proc CVEnv::about {} {
    set dlg [Dialog .aboutdlg -parent . -modal local \
                 -separator 1		\
                 -title   "About CVEnv"	\
                 -side    right		\
                 -anchor  s			\
                 -default 0]
    $dlg add -name ok -width 5
    
	set top [$dlg getframe]
	    
	image create photo original -file [file join $::image_path pictures/CVEnv.gif]
	canvas $top.c -bd 2 -relief ridge -width 295 -height 195 
	$top.c create image 0 0 -anchor nw -image original
	pack $top.c -side top -expand yes -fill x

    set frame [frame $top.f -background white -bd 2 -relief ridge]
    set lab  [label $frame.lab1 -text \
		"Program CVEnv v. 1.0 \nIntel corporation. 2000-2001 y."	\
			   -background white -font {times 8}]
    pack $lab
    pack $frame -side top -expand yes -fill x -padx 2 -pady 2

    $dlg draw
    destroy $dlg
}

proc CVEnv::modify_font {lbtypes lbcolors samf font} {
    global EditorTextfont
    global EditorStringfont
    global EditorNumberfont
    global EditorCommentfont
    global EditorKeywordfont
    
    set curtype  [$lbtypes get [$lbtypes curselection]]
    set curcolor [$lbcolors get [$lbcolors curselection]]

    set name font
    set name $curtype$curcolor$name
    set $name $font

    $samf.label configure -font $font
}

proc CVEnv::modify_fg {lbtypes lbcolors samf cbfgf cbbgf color} {
    global EditorTextfg
    global EditorStringfg
    global EditorNumberfg
    global EditorCommentfg
    global EditorKeywordfg
    global EditorSelectfg

    set curtype  [$lbtypes get [$lbtypes curselection]]
    set curcolor [$lbcolors get [$lbcolors curselection]]

    set name fg
    set name $curtype$curcolor$name
    set $name $color

    $samf.label configure -fg $color
    $cbfgf configure -entrybg $color -selectbackground $color -text ""
}

proc CVEnv::modify_bg {lbtypes lbcolors samf cbfgf cbbgf color} {
    global EditorTextbg
    global EditorSelectbg
    global EditorCursorbg

    set curtype  [$lbtypes get [$lbtypes curselection]]
    set curcolor [$lbcolors get [$lbcolors curselection]]

    set name bg
    set name $curtype$curcolor$name
    set $name $color

    $samf.label configure -bg $color
    $samf configure -bg $color
    $cbbgf configure -entrybg $color -selectbackground $color -text ""
}

proc getvar {name value} {
    upvar $name localVar
    upvar $value lvalue
	
    set localVar $lvalue
}

proc CVEnv::default_bg {lbtypes lbcolors samf cbfgf cbbgf} {
    global defaults
    global default_normal_bg
    global default_normal_fg
    global default_light_bg
    global default_dark_bg
    global default_window_bg
    global default_window_fg
    global default_select_bg
    global default_select_fg

    set index [$cbbgf getvalue]
    set name [lindex $defaults $index]
    set color ""

    ::getvar color $name

    if [string compare $color ""] {
	    CVEnv::modify_bg $lbtypes $lbcolors $samf $cbfgf $cbbgf $color
    }
}

proc CVEnv::default_fg {lbtypes lbcolors samf cbfgf cbbgf} {
    global defaults
    global default_normal_bg
    global default_normal_fg
    global default_light_bg
    global default_dark_bg
    global default_window_bg
    global default_window_fg
    global default_select_bg
    global default_select_fg

    set index [$cbfgf getvalue]
    set name [lindex $defaults $index]
    set color ""

    ::getvar color $name

    if [string compare $color ""] {
	    CVEnv::modify_fg $lbtypes $lbcolors $samf $cbfgf $cbbgf $color
    }
}

proc CVEnv::getconf {lbtypes lbcolors samf cbfgf cbbgf} {
    global EditorTextbg
    global EditorTextfg
    global EditorStringfg
    global EditorNumberfg
    global EditorCommentfg
    global EditorKeywordfg
    global EditorSelectbg
    global EditorSelectfg
    global EditorCursorbg
    global EditorTextfont
    global EditorStringfont
    global EditorNumberfont
    global EditorCommentfont
    global EditorKeywordfont
    
    set curtype  [$lbtypes get [$lbtypes curselection]]
    set curcolor [$lbcolors get [$lbcolors curselection]]

    if {([string compare $curcolor "Text"]) && ([string compare $curcolor "Select"])} {
        if {([string compare $curcolor "Cursor"])} {

            $cbbgf configure -state disabled
            $cbfgf configure -state normal

            set name fg
            set name $curtype$curcolor$name
            set tmp ""
            ::getvar tmp $name
            if [string compare $tmp ""] {
	            CVEnv::modify_fg $lbtypes $lbcolors $samf $cbfgf $cbbgf $tmp
            }

            CVEnv::modify_bg $lbtypes $lbcolors $samf $cbfgf $cbbgf $EditorTextbg

            set name font
            set name $curtype$curcolor$name
            set tmp ""
            ::getvar tmp $name

            CVEnv::modify_font $lbtypes $lbcolors $samf $tmp

        } else {

            $cbfgf configure -state disabled
            $cbbgf configure -state normal

            set name bg
            set name $curtype$curcolor$name
            set tmp ""
            ::getvar tmp $name
            if [string compare $tmp ""] {
    	        CVEnv::modify_bg $lbtypes $lbcolors $samf $cbfgf $cbbgf $tmp
            }

            CVEnv::modify_fg $lbtypes $lbcolors $samf $cbfgf $cbbgf $EditorTextfg
            CVEnv::modify_font $lbtypes $lbcolors $samf $EditorTextfont
        }
        
    } else {

        $cbbgf configure -state normal
        $cbfgf configure -state normal

        set name bg
        set name $curtype$curcolor$name
        set tmp ""
        ::getvar tmp $name
        if [string compare $tmp ""] {
    	    CVEnv::modify_bg $lbtypes $lbcolors $samf $cbfgf $cbbgf $tmp
        }
   
        set name fg
        set name $curtype$curcolor$name
        set tmp ""
        ::getvar tmp $name
        if [string compare $tmp ""] {
	        CVEnv::modify_fg $lbtypes $lbcolors $samf $cbfgf $cbbgf $tmp
        }

        if {([string compare $curcolor "Select"])} {
            set name font
            set name $curtype$curcolor$name
            set tmp ""
            ::getvar tmp $name

            CVEnv::modify_font $lbtypes $lbcolors $samf $tmp
        } else {
            CVEnv::modify_font $lbtypes $lbcolors $samf $EditorTextfont
        }
    }
}

proc CVEnv::custom_bg {lbtypes lbcolors samf cbfgf cbbgf} {

    #set initialColor [$button cget -$name]

    set color [tk_chooseColor -title "Choose a color" -parent .colordlg \
	-initialcolor blue]
    if [string compare $color ""] {
	    CVEnv::modify_bg $lbtypes $lbcolors $samf $cbfgf $cbbgf $color
    }

}

proc CVEnv::custom_fg {lbtypes lbcolors samf cbfgf cbbgf} {
    
    #set initialColor [$button cget -$name]

    set color [tk_chooseColor -title "Choose a color" -parent .colordlg \
	-initialcolor blue]
    if [string compare $color ""] {
	    CVEnv::modify_fg $lbtypes $lbcolors $samf $cbfgf $cbbgf $color
    }

}

proc CVEnv::colordialog {} {
    set dlg [Dialog .colordlg -parent . -modal local \
                 -separator 1		\
                 -title   "Colors configuration"	\
                 -side    bottom		\
                 -anchor  c			\
                 -default 2]
    #$dlg add -name reset -width 7 -text Reset
    $dlg add -name ok -width 7
    $dlg add -name cancel -width 7
    
	set top [$dlg getframe]
	    
	set frame [frame $top.flef ]
        set titlebox  [TitleFrame $top.flef.titlebox -font {times 8} \
                        -side left -text Types]
            set f [$titlebox getframe]
            set sw [ScrolledWindow $f.sw -auto both]
                set lbtypes [listbox $sw.lbtypes -width 21 -height 6 -exportselection no]
                $lbtypes insert end "Editor"
                $lbtypes selection set 0

                $sw setwidget $sw.lbtypes
    	        pack $sw.lbtypes -fill both -expand yes 
	        pack $sw  -side top  -expand yes -fill both
        pack $titlebox -side top

        set framebox  [TitleFrame $frame.framebox -font {times 8} \
                        -side left -text Sample]
            set f [$framebox getframe]

                set samf [frame $f.samf -width 148 -height 56 \
                      -bg white -bd 0 -relief flat \
                      -highlightthickness 1 -takefocus 0 \
                      -highlightbackground black \
                      -highlightcolor black]

                    set lab  [label $samf.label \
                      -background white -foreground black \
                      -borderwidth 0 -takefocus 0 -highlightthickness 0 \
                      -text "Sample text"]
                    place $lab -relx 0.5 -rely 0.5 -anchor c
                pack $samf -pady 4 -fill x
            
        pack $framebox -side top
    pack $frame -side left -expand yes -fill x -padx 2 -pady 2

    
    set frame [frame $top.frig]
        set tf [TitleFrame $top.frig.f -font {times 8} \
                        -side left -text Font]
            set f [$tf getframe]

            #set _wfont [SelectFont $f.font -type toolbar]
            set _wfont [SelectFont $f.font -type toolbar -command ""]
                    
            pack $_wfont -side left -anchor w

        pack $tf -side top -fill x -expand yes
        
        set titlebox  [TitleFrame $top.frig.titlebox -font {times 8} \
                        -side left -text Colors]
            set f [$titlebox getframe]
            set sw [ScrolledWindow $f.sw -auto both]
                set lbcolors [listbox $sw.lbcolors -width 41 -height 6 -exportselection no]

                $lbcolors insert end Text
                $lbcolors insert end String
	            $lbcolors insert end Number
	            $lbcolors insert end Comment
                $lbcolors insert end Keyword
	            $lbcolors insert end Select
                $lbcolors insert end Cursor
                $lbcolors selection set 0

                $sw setwidget $sw.lbcolors
    	        pack $sw.lbcolors -fill both -expand yes 
	        pack $sw  -side top  -expand yes -fill both

            set lef [frame $f.flef -bd 2 -relief ridge]
                set fontlab [label $lef.fontlab -text Foreground -font {times 8}]
                pack $fontlab -side top -anchor nw
                set fontcb [ComboBox $lef.fontcb -width 19 -editable no \
                -values {default_normal_bg default_normal_fg default_light_bg default_dark_bg\
                         default_window_bg default_window_fg default_select_bg default_select_fg}]
                
                pack $fontcb -side top
                pack $lef -side left -fill x -expand yes
            set rig [frame $f.frig -bd 2 -relief ridge]
                set sizelab [label $rig.sizelab -text Background -font {times 8}]
                pack $sizelab -side top -anchor nw
                set sizecb [ComboBox $rig.fontcb -width 19 -editable no\
                -values {default_normal_bg default_normal_fg default_light_bg default_dark_bg\
                         default_window_bg default_window_fg default_select_bg default_select_fg}]

                $fontcb configure -modifycmd "CVEnv::default_fg $lbtypes $lbcolors $samf $fontcb $sizecb"
                $fontcb bind <ButtonRelease-3> "CVEnv::custom_fg $lbtypes $lbcolors $samf $fontcb $sizecb"
                $fontcb bind <ButtonRelease-2> "CVEnv::custom_fg $lbtypes $lbcolors $samf $fontcb $sizecb"
                
                $sizecb configure -modifycmd "CVEnv::default_bg $lbtypes $lbcolors $samf $fontcb $sizecb"
                $sizecb bind <ButtonRelease-3> "CVEnv::custom_bg $lbtypes $lbcolors $samf $fontcb $sizecb"
                $sizecb bind <ButtonRelease-2> "CVEnv::custom_bg $lbtypes $lbcolors $samf $fontcb $sizecb"

                bind $lbcolors <<ListboxSelect>> "CVEnv::getconf $lbtypes $lbcolors $samf $fontcb $sizecb"
                CVEnv::getconf $lbtypes $lbcolors $samf $fontcb $sizecb
                pack $sizecb -side top
            pack $rig -side right -fill x -expand yes
        pack $titlebox -side top

        $_wfont configure -command "CVEnv::modify_font $lbtypes $lbcolors $samf \[$_wfont cget -font\]"
    pack $frame -side left -expand yes -fill x -padx 2 -pady 2

    set ret [$dlg draw]
    if {$ret == "1"} {
        pLoadColors
    } else {
        pSaveColors

        for {set i 1} {$i <= $CVEnv::pagesnum} {incr i} {
            set frame [$CVEnv::nbrig getframe p$i].sw.tx

            $frame configure -wrap none  -font $::EditorTextfont\
                -bg $::EditorTextbg -selectbackground $::EditorSelectbg \
	            -fg $::EditorTextfg -selectforeground $::EditorSelectfg \
	            -insertbackground $::EditorCursorbg

            $frame tag configure text    -font $::EditorTextfont    -foreground $::EditorTextfg
            $frame tag configure string  -font $::EditorStringfont  -foreground $::EditorStringfg
            $frame tag configure number  -font $::EditorNumberfont  -foreground $::EditorNumberfg
	        $frame tag configure comment -font $::EditorCommentfont -foreground $::EditorCommentfg
	        $frame tag configure keyword -font $::EditorKeywordfont -foreground $::EditorKeywordfg
        }

    }
    destroy $dlg
}

proc CVEnv::confdialog {} {
    set dlg [Dialog .confdlg -parent . -modal local \
                 -separator 1		\
                 -title   "Configuration"	\
                 -side    bottom		\
                 -anchor  c			\
                 -default 2]
    $dlg add -name ok -width 7
    $dlg add -name cancel -width 7
    
	set top [$dlg getframe]
	    
	set frame [frame $top.flef ]
        set titlebox  [TitleFrame $top.flef.titlebox \
                        -side left -text "Before execute options"]
            set f [$titlebox getframe]
            set chk1 [checkbutton $f.chk1 -text "Save text" \
                 -variable CVEnv::savebefore]
            pack $chk1 -side top -anchor nw

            set chk2 [checkbutton $f.chk2 -text "Clear output page" \
                 -variable CVEnv::clearoutputbefore]
            pack $chk2 -side top -anchor nw

            set chk3 [checkbutton $f.chk3 -text "Clear error page" \
                 -variable CVEnv::clearerrorbefore]
            pack $chk3 -side top -anchor nw

        pack $titlebox -side top
    pack $frame -side left -expand yes -fill x -padx 2 -pady 2

    
    set frame [frame $top.frig]
    pack $frame -side left -expand yes -fill x -padx 2 -pady 2

    set ret [$dlg draw]
    
    destroy $dlg
}

proc CVEnv::raiseeditor { } {
    set CVEnv::curpage [$CVEnv::nbrig raise]
    set CVEnv::curframe [$CVEnv::nbrig getframe $CVEnv::curpage].sw.tx
    set pos [lsearch $CVEnv::pages $CVEnv::curpage]
    set CVEnv::curfile [lindex $CVEnv::files $pos]   
}

proc CVEnv::createeditor {page text} {
	global EditorTextbg
    global EditorTextfg
    global EditorStringfg
    global EditorNumberfg
    global EditorCommentfg
    global EditorKeywordfg
    global EditorSelectbg
    global EditorSelectfg
    global EditorCursorbg

    global EditorTextfont
    global EditorStringfont
    global EditorNumberfont
    global EditorCommentfont
    global EditorKeywordfont
    
    set path [$CVEnv::nbrig insert end $page -text $text \
                -leavecmd { set CVEnv::curln "--"
		                    set CVEnv::curcol "--"} \
                -raisecmd CVEnv::raiseeditor]
    set sw [ScrolledWindow $path.sw -auto none]
    
    set CVEnv::curframe [text $sw.tx -wrap none  -font $EditorTextfont\
    -bg $EditorTextbg -selectbackground $EditorSelectbg \
	-fg $EditorTextfg -selectforeground $EditorSelectfg \
	-insertbackground $EditorCursorbg]

    $sw setwidget $sw.tx
	pack $sw.tx -fill both -expand yes 
	pack $sw  -side top  -expand yes -fill both
    
	$CVEnv::curframe tag configure text    -font $EditorTextfont    -foreground $EditorTextfg
    $CVEnv::curframe tag configure string  -font $EditorStringfont  -foreground $EditorStringfg
    $CVEnv::curframe tag configure number  -font $EditorNumberfont  -foreground $EditorNumberfg
	$CVEnv::curframe tag configure comment -font $EditorCommentfont -foreground $EditorCommentfg
	$CVEnv::curframe tag configure keyword -font $EditorKeywordfont -foreground $EditorKeywordfg
	
	$CVEnv::curframe tag add normal 0.0 end
	$CVEnv::curframe index 0.0

	#-----------------------------------------------------------
    bind $CVEnv::curframe <KeyPress> {
	    pParsebegin
    }

	bind $CVEnv::curframe <KeyRelease> {
		pParseend
        #set frame [$CVEnv::nbrig getframe $CVEnv::curpage]
    	set curindex [$CVEnv::curframe index insert]
    	set coordlist [split $curindex .]
		set CVEnv::curln [lindex $coordlist  0]
		set CVEnv::curcol [lindex $coordlist  1]
        incr CVEnv::curcol
	}

	bind $CVEnv::curframe <ButtonRelease-1> {
        #set frame [$CVEnv::nbrig getframe $CVEnv::curpage]
		set curindex [$CVEnv::curframe index insert]
		set coordlist [split $curindex .]
		set CVEnv::curln [lindex $coordlist  0]
		set CVEnv::curcol [lindex $coordlist  1]
        $CVEnv::nbrig see $CVEnv::curpage
	    
		incr CVEnv::curcol
        update
	}

	bind $CVEnv::curframe <FocusOut> {
        set CVEnv::curln "--"
		set CVEnv::curcol "--"
	}

    bind $CVEnv::curframe <F5> CVEnv::execute

   	#-----------------------------------------------------------
}

proc CVEnv::new {} {
    
    incr CVEnv::pagescount
    incr CVEnv::pagesnum

    set CVEnv::curpage p[expr $CVEnv::pagescount]
    set CVEnv::curfile ""
    lappend CVEnv::pages $CVEnv::curpage
    lappend CVEnv::files $CVEnv::curfile

    set text [format "/* %u */" $CVEnv::pagescount]
    CVEnv::createeditor $CVEnv::curpage $text
    
    if {$CVEnv::pagesnum == 1} {
        CVEnv::longmenu 1
        CVEnv::longbar 1
        CVEnv::longstbar 1
    }

    $CVEnv::nbrig see [$CVEnv::nbrig pages end]
    $CVEnv::nbrig raise [$CVEnv::nbrig pages end]
}

proc CVEnv::loadfile {name frame} {
	set file [::open $name r]
    pParsebegin

    $frame insert 0.0 [read $file]
    ::close $file
    $frame index 0.0

    pParseend
}

proc CVEnv::open {parent} {
	set types {
		{"C files"	{.c .h}		}
		{"Text files"		{.txt}	}
		{"All files"		*}
    }
    
    set file [tk_getOpenFile -filetypes $types -parent $parent]
    if [string compare $file ""] {

        if [$CVEnv::tree exists $file] {
            #set page [$CVEnv::tree itemcget $file -data]
			set pos [lsearch $CVEnv::files $file]
			set page [lindex $CVEnv::pages $pos]
			$CVEnv::nbrig see $page
            $CVEnv::nbrig raise $page
        } else {
            incr CVEnv::pagescount
            incr CVEnv::pagesnum
		    
            set CVEnv::curfile $file
            set text [lindex [split $file /] end]
		    set CVEnv::curpage p[expr $CVEnv::pagescount]
			lappend CVEnv::files $CVEnv::curfile
			lappend CVEnv::pages $CVEnv::curpage
        
			CVEnv::createeditor $CVEnv::curpage $text
            
			CVEnv::loadfile $file $CVEnv::curframe

			if {$CVEnv::pagesnum == 1} {
				CVEnv::longmenu 1
				CVEnv::longbar 1
				CVEnv::longstbar 1
			}

			$CVEnv::tree insert end files $file -text $file \
                -image [image create photo -file [file join $::image_path pictures/file.gif]]

			$CVEnv::nbrig see [$CVEnv::nbrig pages end]
			$CVEnv::nbrig raise [$CVEnv::nbrig pages end]
		}
	}
}

proc CVEnv::save {} {
    if {$CVEnv::curfile != ""} {
    	#set frame [ $CVEnv::nbrig getframe $CVEnv::curpage]
        CVEnv::writefile $CVEnv::curfile $CVEnv::curframe
    } else {
        CVEnv::saveas .
    }
}

proc CVEnv::writefile {name frame} {
	set file [::open $name w]
	set tx [$frame get 1.0 "end-1 chars"]
	puts $file $tx
    flush $file
    ::close $file
}

proc CVEnv::saveas {parent} {
	set types {
		{"C source files"	{.c}		}
        {"C header files"	{.h}		}
		{"Text files"		{.txt}	}
        {"All files"		*}
    }

    set file [tk_getSaveFile -filetypes $types -parent $parent \
                -initialfile Untitled -defaultextension ""]
    if [string compare $file ""] {
		
		if [$CVEnv::tree exists $file] {
            #set page [$CVEnv::tree itemcget $file -data]
			set pos [lsearch $CVEnv::files $file]
			set page [lindex $CVEnv::pages $pos]
			$CVEnv::nbrig see $page
            $CVEnv::nbrig raise $page
        } else {

		set pos [lsearch $CVEnv::files $CVEnv::curfile]
        set CVEnv::files [lreplace $CVEnv::files $pos $pos $file]
		
		set text [lindex [split $file /] end]                    
        $CVEnv::nbrig itemconfigure $CVEnv::curpage -text $text
		#set frame [ $CVEnv::nbrig getframe $CVEnv::curpage]
        CVEnv::writefile $file $CVEnv::curframe

		if {$CVEnv::curfile != ""} {
			set ind [$CVEnv::tree index $CVEnv::curfile]
			$CVEnv::tree delete $CVEnv::curfile
			$CVEnv::tree insert $ind files $file -text $file \
                -image [image create photo -file [file join $::image_path pictures/file.gif]]
		} else {
			$CVEnv::tree insert end files $file -text $file \
                -image [image create photo -file [file join $::image_path pictures/file.gif]]
		}
        
        set CVEnv::curfile $file
		}
    }
}

proc CVEnv::close {} {

	set pos [lsearch $CVEnv::files $CVEnv::curfile]
	set $CVEnv::files [lreplace $CVEnv::files $pos $pos]
	set $CVEnv::pages [lreplace $CVEnv::pages $pos $pos]

	$CVEnv::nbrig delete $CVEnv::curpage 1

	if {$CVEnv::curfile != ""} {
		set ind [$CVEnv::tree index $CVEnv::curfile]
		$CVEnv::tree delete $CVEnv::curfile
	}

    set CVEnv::pagesnum [expr $CVEnv::pagesnum - 1]

	if {$CVEnv::pagesnum == 0} {
		CVEnv::longmenu 0
		CVEnv::longbar 0
		#CVEnv::longstbar 0
		set CVEnv::curfile ""
	} else {
		set page [$CVEnv::nbrig pages end]

		set pos [lsearch $CVEnv::pages $CVEnv::curpage]
		set CVEnv::curfile [lindex $CVEnv::files $pos]
			
		$CVEnv::nbrig see $page
        $CVEnv::nbrig raise $page
    }
}

proc CVEnv::execute {} {

    if {$CVEnv::savebefore == "1"} {
        CVEnv::save
    } else {
        if {$CVEnv::curfile == ""} {
    	    CVEnv::saveas .
        }    
    }

    if {$CVEnv::clearoutputbefore == "1"} {
        $CVEnv::outtx delete 0.0 end
    }

    if {$CVEnv::clearerrorbefore == "1"} {
        $CVEnv::parsetx delete 0.0 end
    }

    pExecute $CVEnv::curfile
}

proc CVEnv::create { } {
	variable prgindic 0
	variable prgtext
	## Create intro
    ###################################################################
    set top [toplevel .intro -relief raised -borderwidth 2]
    wm withdraw $top
    wm overrideredirect $top 1
	
	image create photo original -file [file join $::image_path pictures/CVEnv.gif]
	canvas $top.c -bd 2 -relief ridge -width 295 -height 195 
	$top.c create image 0 0 -anchor nw -image original
	pack $top.c -side top -expand yes -fill x

    set frame [frame $top.f -background white -bd 2 -relief ridge]
    set lab1  [label $frame.lab1 -text "Please wait for loading..."	\
			   -background white -font {times 8}]
    set lab2  [label $frame.lab2 -textvariable CVEnv::prgtext	\
			   -background white -font {times 8} -width 35]
    set prg   [ProgressBar $frame.prg -width 50 -height 10		\
			   -background white -variable CVEnv::prgindic -maximum 7]
    pack $lab1 $prg $lab2
    pack $frame -side top -expand yes -fill x -padx 2 -pady 2

    BWidget::place $top 0 0 center
    wm deiconify $top

	###################################################################
	
	set CVEnv::prgtext "Loading font..."
	update
	SelectFont::loadfont

	incr CVEnv::prgindic
	set CVEnv::prgtext   "Creating menu..."
    update

    #### Menu
    set menu {
        "&File" all file 0 {
            {command "&New" {} "New document" {} -command CVEnv::new}
			{command "&Open" {} "Open a document" {} -command "CVEnv::open ."}
			{command "&Close" {} "Close the document" {} -state disable	\
				-command CVEnv::close}
			{separator}
			{command "&Save" {} "Save the document" {} -state disable	\
				-command CVEnv::save}
			{command "Save &As..." {} "Save the document as..." {}	\
                -state disable -command "CVEnv::saveas ."}
			{separator}
			{command "E&xit" {} "Exit the program" {} -command exit}
        }
        "&View" all view 0 {
            {checkbutton "&Toolbar" {all view} "Show/hide toolbar" {}	\
                -variable CVEnv::showtb	\
                -command {$CVEnv::mainf showtoolbar 0 $CVEnv::showtb}
            }
			{checkbutton "&Statusbar" {all view} "Show/hide statusbar" {}	\
                -variable CVEnv::showstb	\
                -command {
							if {$CVEnv::showstb} {
								pack $CVEnv::mainf.botf -side bottom -fill x	
							} else {
								pack forget $CVEnv::mainf.botf
							}
						 }
            }
			{checkbutton "&File pane" {all view} "" {}	\
                -variable CVEnv::showlp					\
                -command {CVEnv::leftpane $CVEnv::showlp}
            }
			
        }
		"&Options" all options 0 {
			{command "&Configuration" {} "Enviroments settings" {}	\
				-command CVEnv::confdialog}
			{command "&Appearance" {} "Colors & fonts setup" {} -command CVEnv::colordialog}
		}
		"&Help" all help 0 {
			{command "&About CVEnv" {} "Display the program info" {}	\
			 -command CVEnv::about}
        }
    }

    #{checkbutton "&Execute pane" {all view} "" {}	\
            #    -variable CVEnv::showbp					\
            #    -command {CVEnv::bottompane $CVEnv::showbp}
            #}

	incr CVEnv::prgindic
	set CVEnv::prgtext   "Creating MainFrame..."
    update

    set CVEnv::mainf [MainFrame .mainf -menu $menu	\
                      -textvariable CVEnv::statustext]

    menu .menubar.edit -tearoff 0 -background $::default_normal_bg
    MainFrame::_create_entries .mainf .menubar.edit \
		$::default_normal_bg {\
			{command "Cu&t" {} "Cut the selection" {} -command cut}
			{command "&Copy" {} "Copy the selection" {} -command copy}
			{command "&Paste" {} "Paste the clipboard" {} -command paste}
			{separator}
			{command "&Go to.." {} "Move to a specified place" {} -command paste}
        }

	incr CVEnv::prgindic
	set CVEnv::prgtext   "Creating toolbar..."
    update

    #### toolbars creation
    set CVEnv::tb  [$CVEnv::mainf addtoolbar]

    set bbox [ButtonBox $CVEnv::tb.bbox0 -spacing 0 -padx 1 -pady 1]
    $bbox add -image [image create photo -file [file join $::image_path pictures/new.gif]] \
        -highlightthickness 0 -takefocus 0 -relief link -borderwidth 2	\
		-padx 1 -pady 1 -helptext "Create a new file" -command CVEnv::new
    $bbox add -image [image create photo -file [file join $::image_path pictures/open.gif]] \
        -highlightthickness 0 -takefocus 0 -relief link -borderwidth 2	\
		-padx 1 -pady 1 -helptext "Open an existing file" -command "CVEnv::open ."
    pack $bbox -side left -anchor w
    
    set sep [Separator $CVEnv::tb.sep0 -orient vertical]
    pack $sep -side left -fill y -padx 4 -anchor w

    set bbox [ButtonBox $CVEnv::tb.bbox1 -spacing 0 -padx 1 -pady 1]
    $bbox add -image [image create photo -file [file join $::image_path pictures/save.gif]] \
              -highlightthickness 0 -takefocus 0 -relief link -borderwidth 2 \
			  -padx 1 -pady 1 -helptext "Save file" -command CVEnv::save

        #$bbox.b2 configure -state active -relief link
	    #$bbox.b2 _leave

    set sep [Separator $CVEnv::tb.sep1 -orient vertical]
    
	set bbox [ButtonBox $CVEnv::tb.bbox2 -spacing 0 -padx 1 -pady 1]
    $bbox add -image [image create photo -file [file join $::image_path pictures/cut.gif]] \
        -highlightthickness 0 -takefocus 0 -relief link -borderwidth 1	\
		-padx 1 -pady 1 -helptext "Cut (Ctrl-X)"
    $bbox add -image [image create photo -file [file join $::image_path pictures/copy.gif]] \
        -highlightthickness 0 -takefocus 0 -relief link -borderwidth 1	\
		-padx 1 -pady 1 -helptext "Copy (Ctrl-C)"
    $bbox add -image [image create photo -file [file join $::image_path pictures/paste.gif]] \
        -highlightthickness 0 -takefocus 0 -relief link -borderwidth 1	\
		-padx 1 -pady 1 -helptext "Paste (Ctrl-V)"

	set sep [Separator $CVEnv::tb.sep2 -orient vertical]

    set bbox [ButtonBox $CVEnv::tb.bbox3 -spacing 0 -padx 1 -pady 1]
    $bbox add -image [image create photo -file [file join $::image_path pictures/exec.gif]] \
        -highlightthickness 0 -takefocus 0 -relief link -borderwidth 1	\
		-padx 1 -pady 1 -helptext "Execute the script (F5)" \
		-command CVEnv::execute 

    $bbox add -image [image create photo -file [file join $::image_path pictures/stop.gif]] \
        -highlightthickness 0 -takefocus 0 -relief link -borderwidth 1	\
		-padx 1 -pady 1 -helptext "Stop the execution (Shift-F5)"\
		-command pStop

    set sep [Separator $CVEnv::tb.sep3 -orient vertical]

    $CVEnv::tb.bbox3.b1 configure -state disable -relief link
    
    incr CVEnv::prgindic
    set CVEnv::prgtext   "Creating statusbar..."
    update

	$CVEnv::mainf addindicator
	$CVEnv::mainf.status.indf.f0 configure -relief flat

	label $CVEnv::mainf.status.indf.f0.l0  -relief sunken -borderwidth 1 \
        -takefocus 0 -highlightthickness 0 -textvariable CVEnv::curfile
	pack $CVEnv::mainf.status.indf.f0.l0 -side left -fill y -expand 1

	label $CVEnv::mainf.status.indf.f0.l1  -relief flat -borderwidth 1 \
        -takefocus 0 -highlightthickness 0 -text "Ln"
	pack $CVEnv::mainf.status.indf.f0.l1 -side left -fill y -expand 1

	label $CVEnv::mainf.status.indf.f0.l2  -relief sunken -borderwidth 1 \
        -takefocus 0 -highlightthickness 0 -textvariable CVEnv::curln
	pack $CVEnv::mainf.status.indf.f0.l2 -side left -fill y -expand 1

	label $CVEnv::mainf.status.indf.f0.l3  -relief flat -borderwidth 1 \
        -takefocus 0 -highlightthickness 0 -text "Col"
	pack $CVEnv::mainf.status.indf.f0.l3 -side left -fill y -expand 1

	label $CVEnv::mainf.status.indf.f0.l4  -relief sunken -borderwidth 1 \
        -takefocus 0 -highlightthickness 0 -textvariable CVEnv::curcol
	pack $CVEnv::mainf.status.indf.f0.l4 -side left -fill y -expand 1
	pack forget $CVEnv::mainf.status.indf.f0

	set CVEnv::prgtext   "Creating panes..."
    incr CVEnv::prgindic
    CVEnv::createpanes $CVEnv::mainf.frame
    
	set CVEnv::prgtext   "Done"
    incr CVEnv::prgindic

    pack $CVEnv::mainf -fill both -expand yes
    update idletasks

	unset CVEnv::prgindic
	unset CVEnv::prgtext

    destroy .intro
}

proc CVEnv::treeclick {node} {
    set file [lindex $node 0]
    set data [$CVEnv::tree itemcget $file -data]
        
    if [string compare $data "Files"] {
        set pos [lsearch $CVEnv::files $file]
	    set page [lindex $CVEnv::pages $pos]

        $CVEnv::nbrig see $page
        $CVEnv::nbrig raise $page
    }
}

proc CVEnv::gotoline { line } {
    $CVEnv::curframe see $line.0
    focus -force $CVEnv::curframe

    $CVEnv::curframe tag remove sel 0.0 $line.0
	$CVEnv::curframe tag add sel $line.0 [expr $line +1].0
	$CVEnv::curframe tag remove sel [expr $line +1].0 end
	update idletasks
}

proc CVEnv::createpanes { parent } {
    set CVEnv::pw    [PanedWindow $parent.pw -side left]
    set CVEnv::ptop  [$CVEnv::pw add]
    
    set CVEnv::pwch  [PanedWindow $CVEnv::ptop.pw -side bottom]
    set plef  [$CVEnv::pwch add]
    set CVEnv::prig  [$CVEnv::pwch add]

    set CVEnv::nblef [NoteBook $plef.nb -side bottom]
    set files [$CVEnv::nblef insert end "files" -text "Files" \
        -image [image create photo -file [file join $::image_path pictures/file.gif]]]
    set sw    [ScrolledWindow $files.sw \
                  -relief sunken -borderwidth 2]
    set CVEnv::tree  [Tree $sw.tree \
                -relief flat -borderwidth 0 -width 15 -highlightthickness 0\
				-redraw 1]
	$sw setwidget $CVEnv::tree
	$CVEnv::tree insert end root files -text Files -data Files \
        -image [image create photo -file [file join $::image_path pictures/openfold.gif]]
    pack $sw    -side top  -expand yes -fill both
	#$CVEnv::nblef compute_size
    pack $CVEnv::nblef -fill both -expand yes -padx 1 -pady 1

	set CVEnv::nbrig [NoteBook $CVEnv::ptop.nb -side top]
	
	#$CVEnv::nbrig compute_size
	pack $CVEnv::nbrig -in $CVEnv::prig -fill both -expand yes -padx 1 -pady 1
	pack $CVEnv::pwch -fill both -expand yes

	set CVEnv::pbot  [$CVEnv::pw add]
    set CVEnv::inputcb [Entry $CVEnv::pbot.combo \
                   -textvariable CVEnv::inputvar \
                   -helptext "Input box. In order to input data press Enter."\
                   -command {
                             set CVEnv::inputdata $CVEnv::inputvar
                             lappend CVEnv::inputlist $CVEnv::inputdata
                             set CVEnv::curinput [lsearch -exact $CVEnv::inputlist $CVEnv::inputdata]
                             $CVEnv::inputcb configure -fg #00FFFF
                             pInput
                            } ]
    pack $CVEnv::inputcb -fill x -side bottom

    bind $CVEnv::inputcb <KeyPress> {
                                        set CVEnv::inputdata ""
                                        $CVEnv::inputcb configure \
                                            -fg $::default_window_fg
                                    }
    bind $CVEnv::inputcb <Up> {
                                    if {$CVEnv::curinput != 0} {
                                      set CVEnv::curinput [expr $CVEnv::curinput -1]
                                      set CVEnv::inputvar [lindex $CVEnv::inputlist $CVEnv::curinput]
                                      set CVEnv::inputdata $CVEnv::inputvar
                                      $CVEnv::inputcb configure \
                                        -fg #00FFFF
                                    }
                              }
    bind $CVEnv::inputcb <Down> {
                                    incr CVEnv::curinput
                                    set CVEnv::inputvar [lindex $CVEnv::inputlist $CVEnv::curinput]
                                    set CVEnv::inputdata $CVEnv::inputvar
                                    $CVEnv::inputcb configure \
                                        -fg #00FFFF
                                }


	set CVEnv::nbbot  [NoteBook $CVEnv::pbot.nb -side bottom]
	
	set parse  [$CVEnv::nbbot insert end parse  -text "Errors"]
	set sw [ScrolledWindow $parse.sw -auto vertical]
	set CVEnv::parsetx [text $sw.tx -wrap none]
	$sw setwidget $CVEnv::parsetx
	pack $CVEnv::parsetx -fill both -expand yes 
	pack $sw  -side top  -expand yes -fill both

    bind $CVEnv::parsetx <Button-2> {
        set pos [$CVEnv::parsetx index @%x,%y]
        set listpos [split $pos "."]
        set line [lindex $listpos 0]

        set data [$CVEnv::parsetx get "insert linestart" "insert lineend"]
        set datalist [split $data " "]
        set file [lindex $datalist 2]
        set line [lindex [split [lindex $datalist 5] ":"] 0]

        if [string compare $file ""] {
        set pos [lsearch -exact $CVEnv::files $file]
        set page [lindex $CVEnv::pages $pos]
            if [string compare $page ""] { 
                $CVEnv::nbrig see $page
                $CVEnv::nbrig raise $page 
                CVEnv::gotoline $line
            }
        }  
    }
    bind $CVEnv::parsetx <Button-3> {
        set pos [$CVEnv::parsetx index @%x,%y]
        set listpos [split $pos "."]
        set line [lindex $listpos 0]

        set data [$CVEnv::parsetx get "insert linestart" "insert lineend"]
        set datalist [split $data " "]
        set file [lindex $datalist 2]
        set line [lindex [split [lindex $datalist 5] ":"] 0]

        if [string compare $file ""] {
        set pos [lsearch -exact $CVEnv::files $file]
        set page [lindex $CVEnv::pages $pos]
            if [string compare $page ""] { 
                $CVEnv::nbrig see $page
                $CVEnv::nbrig raise $page 
                CVEnv::gotoline $line
            }
        }  
    }
	
	set output [$CVEnv::nbbot insert end output -text "Output"]	
	set sw [ScrolledWindow $output.sw -auto vertical]
	set CVEnv::outtx [text $sw.tx -wrap none]
	$sw setwidget $CVEnv::outtx
	pack $CVEnv::outtx -fill both -expand yes 
	pack $sw  -side top  -expand yes -fill both
	
	bind $CVEnv::outtx <KeyPress> {$CVEnv::outtx configure -state disable}
	bind $CVEnv::outtx <KeyRelease> {$CVEnv::outtx configure -state normal}
    bind $CVEnv::outtx <Button-1> {$CVEnv::outtx configure -state normal}
    bind $CVEnv::parsetx <KeyPress> {$CVEnv::parsetx configure -state disable}
	bind $CVEnv::parsetx <KeyRelease> {$CVEnv::parsetx configure -state normal}
    bind $CVEnv::parsetx <Button-1> {$CVEnv::parsetx configure -state normal}
	
	#$CVEnv::nbbot compute_size
	pack $CVEnv::nbbot -fill both -expand yes -padx 1 -pady 1 -side top

    $CVEnv::tree bindText <Double-Button-1> "CVEnv::treeclick"
    #Tree::bindImage $path <Button-1> "$path selection set"

	
	pack $CVEnv::pw -fill both -expand yes
}

proc CVEnv::update_font { newfont } {
    variable _wfont
    variable notebook
    variable font
    variable font_name

    . configure -cursor watch
    if { $font != $newfont } {
        $_wfont configure -font $newfont
        $notebook configure -font $newfont
        set font $newfont
    }
    . configure -cursor ""
}

proc main {} {
    package require BWidget
    #option add *TitleFrame.l.font {helvetica 11 bold italic}
    wm withdraw .
    wm title . "CVEnv"

    CVEnv::create

    BWidget::place . 640 480 center
    wm deiconify .
    raise .
    wm geometry . 640x480

    set y0 [winfo y .]
    set x0 [winfo x .]
    set ypw [expr $y0 + 360]
    set xpw [expr $x0 + 130]
    
    update
    PanedWindow::_end_move_sash $CVEnv::pw $CVEnv::pw.sash		\
		1 0 0x0FFFFFFF $ypw rooty height
    PanedWindow::_end_move_sash $CVEnv::pwch $CVEnv::pwch.sash	\
		1 0 0x0FFFFFFF $xpw rootx width

	$CVEnv::nblef raise [$CVEnv::nblef page 0]
	$CVEnv::nbbot raise [$CVEnv::nbbot page 1]
    
    update

    focus -force .
}

main
