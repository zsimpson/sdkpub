
wm geometry . 500x200
wm title . "VMDemo"
wm resizable . 0 0
frame .top
pack .top -side top -fill x -pady 2m
label .top.l1 -text "Imaging Size"
pack .top.l1 -side left -expand 1 -padx 0 -pady 0

label .top.l2 -text " " -relief sunken -width 10
pack .top.l2 -side left -expand 1 -padx 0 -pady 0
button .top.b -text "Open Project" -command Cfileopen
#Cfileopen
pack .top.b -side left -expand 1 -padx 10 -pady 10
scale .s -orient horizontal -command Cscale -from 0.0 -to 1.0 -resolution 0.01 -state disabled
pack .s -anchor center
label .l3 -text "Camera Position"
pack .l3 -anchor center
frame .bottom
pack .bottom -side bottom -fill x -pady 2m
button .bottom.b1 -text "Set Original Windows Position" -command CSetpos
pack .bottom.b1 -side left -expand 1 -padx 10 -pady 10
set chb 0.0
checkbutton .bottom.cb1 -text "Show Scanlines" -command CShowScanlines -variable chb
pack .bottom.cb1 -side left -expand 1 -padx 10 -pady 10

#wm resizable .win1 0 0
#wm resizable .win2 0 0
#wm resizable .win3 0 0
