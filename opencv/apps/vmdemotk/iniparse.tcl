# this line is needed for our install script, to keep up with different versions
# ini_version=1.4
#
##########
#
# INIParse v1.4 (C)2000
#
#   see AUTHORS
#
##########
#
# Usage:
#   iniparse:openfile <filename> ?RDONLY?
#   
# Reads an ini file into memory, for later access (such as read or write),
# and return an id which can be later used for writing/reading data, and
# flushing/closing file.
#
# Notes:
# - It doesn't leave the file open, just reads into memory, and returns an id.
# - If RDONLY is specified (case-sensetive), then calls to writeini will work
#   only in memory, and changes won't be saved with iniparse:flush, nor
#   iniparse:closefile.
#
####
#
# Usage:
#   iniparse:flushfile <fileId>
#   
# Writes an ini file in memory into its file, without removing data from
# memory.
#
####
#
# Usage:
#   iniparse:closefile <fileId>
#   
# Flushes an ini file in memory into its file, and then removes data from
# memory.
#
####
#
# Usage:
#   readini <fileId> [ [<keyname>] [<itemname>] ]
#       Reads <itemname> under <keyname> from <fileId>. If it cannot find
#       file, <itemname>, or <keyname>, returns an empty string.
#       If itemname is absent, returns list of all items under keyname.
#
# Notes:
# - This procedure doesn't read directly from the file, but from the
#   memory-version of the file. If directly the file (not memory version) is
#   modified after the call to iniparse:openfile, this procedure will not
#   see the changes in the file, but only changes in memory-version.
#
# See: writeini iniparse:openfile
#
####
#
# Usage:
#   writeini <fileId> <keyname> <itemname> <itemvalue>
#	Writes/modifies <itemname> under <keyname> in <fileId>. If cannot
#	find <itemname>, or <keyname>, creates a new one.
#
# Notes:
# - This procedure doesn't write directly to the file, but to the
#   memory-version of the file. If directly the file (not memory version) is
#   modified after the call to iniparse:openfile, this procedure will not
#   see the changes in the file, but only changes in memory-version.
#
# See: readini iniparse:openfile
#
####
#
# Usage:
#   iniparse:removeitem <fileId> <keyname> <itemname>
#	Removes <itemname> under <keyname> in <fileId>.
#
# Notes:
# - This procedure doesn't write directly to the file, but to the
#   memory-version of the file. If directly the file (not memory version) is
#   modified after the call to iniparse:openfile, this procedure will not
#   see the changes in the file, but only changes in memory-version.
#
# See: readini iniparse:openfile
#
####
#
# Usage:
#   iniparse:removekey <fileId> <keyname>
#	Removes <keyname> in <fileId>.
#
# Notes:
# - This procedure doesn't write directly to the file, but to the
#   memory-version of the file. If directly the file (not memory version) is
#   modified after the call to iniparse:openfile, this procedure will not
#   see the changes in the file, but only changes in memory-version.
#
# See: readini iniparse:openfile
#
####
#
# Usage:
#   iniparse:renameitem <fileId> <keyname> <itemName> <newItemName>
#	Renames <itemName> under <keyname> in <fileId> to <newItemName>.
#
# Notes:
# - This procedure doesn't write directly to the file, but to the
#   memory-version of the file. If directly the file (not memory version) is
#   modified after the call to iniparse:openfile, this procedure will not
#   see the changes in the file, but only changes in memory-version.
#
# See: readini iniparse:openfile
#
####
#
# Usage:
#   iniparse:renamekey <fileId> <keyname> <newKeyName>
#	Renames <keyname> in <fileId> to <newKeyName>.
#
# Notes:
# - This procedure doesn't write directly to the file, but to the
#   memory-version of the file. If directly the file (not memory version) is
#   modified after the call to iniparse:openfile, this procedure will not
#   see the changes in the file, but only changes in memory-version.
#
# See: readini iniparse:openfile
#
#############################################################################

package provide iniparse 1.4

set iniparse(freeid) 0
set iniparse(idlist) {}
#$iniparse($id,fname)   - filename
#$iniparse($id,data)    - each line in file are read into an item in this list
#$iniparse($id,flags)   - this is a list containing these flags:
#                           RDONLY  : If this flag is set, iniparse:flush will
#                                     not write anything over file, but still
#                                     writeini will work (only in memory)
#

proc rtrimleft {bigstr srcstr} {
  set istring1 [string length $srcstr]
  if {$srcstr == [string range $bigstr 0 [expr $istring1-1]]} {
    return [string range $bigstr $istring1 end]
  }
}

proc chrchk {arg} {
  if {[string index $arg 0] == "\[" && [string index $arg end] == "\]"} {
    return 1
  } else {return 0}
  return 0
}

#
# Usage:
#   iniparse:openfile <filename> ?RDONLY?
#   
# Reads an ini file into memory, for later access (such as read or write),
# and return an id which can be later used for writing/reading data, and
# flushing/closing file.
#
# Notes:
# - It doesn't leave the file open, just reads into memory, and returns an id.
# - If RDONLY is specified (case-sensetive), then calls to writeini will work
#   only in memory, and changes won't be saved with iniparse:flush, nor
#   iniparse:closefile.
#
proc iniparse:openfile {file args} {
global iniparse

  set fileId [open $file {RDONLY CREAT}]
  set filedata {}

  while {![eof $fileId]} {
    set input [gets $fileId]
    if {[string match {\[*\]} $input]} {lappend filedata "" $input} \
    elseif {[string match {*=*} $input] || \
	[string match {#*} $input]} {lappend filedata $input}
  }

  close $fileId

  set id $iniparse(freeid)
  incr iniparse(freeid)

  set iniparse($id,fname) $file
  set iniparse($id,data)  $filedata
  set iniparse($id,flags) $args
  lappend iniparse(idlist) $id

  return $id
}

#
# Usage:
#   iniparse:flushfile <fileId>
#   
# Writes an ini file in memory into its file, without removing data from
# memory.
#
proc iniparse:flushfile {id} {
global iniparse

  if {[lsearch $iniparse(idlist) $id] == -1} return     ;# No such Id

  if {[lsearch $iniparse($id,flags) RDONLY] != -1} return ;# ReadOnly-Flag

  set fileId [open $iniparse($id,fname) {WRONLY CREAT TRUNC}]

  foreach line $iniparse($id,data) {
    if {[string match {\[*\]} $line]} {puts $fileId "\n$line"} \
    elseif {[string match {*=*} $line] || \
	[string match {#*} $line]} {puts $fileId $line}
  }
  close $fileId

  set iniparse($id,flags) [lreplace $iniparse($id,flags) [set idx [lsearch $iniparse($id,flags) CHANGED]] $idx]
}

#
# Usage:
#   iniparse:closefile <fileId>
#   
# Flushes an ini file in memory into its file, and then removes data from
# memory.
#
proc iniparse:closefile {id} {
global iniparse

  if {[lsearch $iniparse(idlist) $id] == -1} return     ;# No such Id

  iniparse:flushfile $id
  unset iniparse($id,fname)
  unset iniparse($id,data)
  unset iniparse($id,flags)
  set iniparse(idlist) [lreplace $iniparse(idlist) [set idx [lsearch $iniparse(idlist) $id]] $idx]
}

#
# Usage:
#   readini <fileId> [ [<keyname>] [<itemname>] ]
#       Reads <itemname> under <keyname> from <fileId>. If it cannot find
#       file, <itemname>, or <keyname>, returns an empty string.
#       If itemname is absent, returns list of all items under keyname.
#
# Notes:
# - This procedure doesn't read directly from the file, but from the
#   memory-version of the file. If directly the file (not memory version) is
#   modified after the call to iniparse:openfile, this procedure will not
#   see the changes in the file, but only changes in memory-version.
#
# See: writeini iniparse:openfile
#
proc readini {id args} {
global iniparse
  set keyfound 0 ; set itemfound 0
  set key [lindex $args 0]
  set item [lindex $args 1]
  set itemlength [string length $item]
  set item "$item="
  set kaccum [list]
  set iaccum [list]

  if {[lsearch $iniparse(idlist) $id] == -1} {return ""}   ;# No such Id

  set input ""
  set lidx 0                              ;# line index
  set llen [llength $iniparse($id,data)]
  set data $iniparse($id,data)            ;# for fast access

  while {$lidx < $llen} {
    set input [lindex $data $lidx]
    if {[chrchk $input]} {
      if {$input == "\[$key\]"} {
        # looks like we found our key..
        set keyfound 1 ; break
      } else {
        set keyfound 0
        regsub -all {\[|\]} $input {} baccum
        lappend kaccum $baccum
      }
    }
    incr lidx
  }
  incr lidx

  if {$keyfound == 1} {
    while {$lidx < $llen} {
      set input [lindex $data $lidx]
      if {![chrchk $input]} {
        if {[string range $input 0 $itemlength]==$item} {
          set fValue [rtrimleft $input $item]
          set itemfound 1
          break
        } else {
          set itemNdx [string first "=" $input]
          if {$itemNdx != -1} {
            lappend iaccum [string range $input 0 [expr $itemNdx - 1]]
          }
        }
      } elseif {[chrchk $input]} {
        # oops, we hit the next key.. looks like that item isnt here.
        break
      }
      incr lidx
    }
  } elseif {$keyfound == 0} {
    if {[llength $args] == 0} {
       return $kaccum
    } else {
       return ""       ;# no key exists called $key
    }
  }
  if {$itemfound == 1} {
    return $fValue
  } elseif {[llength $args] != 2} {
    return $iaccum
  } else {
    return ""       ;# no item exists called "[string range $item 0 [expr [string length $item] - 2]]"
  }
}

#
# Usage:
#   writeini <fileId> <keyname> <itemname> <itemvalue>
#	Writes/modifies <itemname> under <keyname> in <fileId>. If cannot
#	find <itemname>, or <keyname>, creates a new one.
#
# Notes:
# - This procedure doesn't write directly to the file, but to the
#   memory-version of the file. If directly the file (not memory version) is
#   modified after the call to iniparse:openfile, this procedure will not
#   see the changes in the file, but only changes in memory-version.
#
# See: readini iniparse:openfile
#
proc writeini {id key item value} {
global iniparse
  set fileline ""
  set keyfound 0
  set itemfound 0
  set itemlength [string length $item]
  set item "$item="

  if {[lsearch $iniparse(idlist) $id] == -1} return   ;# No such Id

  set input ""
  set lidx 0                              ;# line index
  set llen [llength $iniparse($id,data)]
  set fileline $iniparse($id,data)
  set data ""

  foreach line $fileline {
    if {(!$keyfound)} {          ;# We will search for the key.
	if {$line=="\[$key\]"} {
		lappend data "" $line
		set keyfound 1
		continue
	}
    }
    if {($keyfound) && (!$itemfound) && [chrchk $line]} {  ;# We hit the next key!
	lappend data "$item$value"
	lappend data "" $line
	set itemfound 1
	continue
    }
    if {($keyfound) && (!$itemfound)} {  ;# We will search for the item
	if {[string range $line 0 $itemlength]==$item} {
		lappend data "$item$value"
		set itemfound 1
		continue
	}
    }
    # Because it doesn't match anything above, we print the line to file
    if {[chrchk $line]} {lappend data "" $line} \
	else {lappend data $line}
  }

  if {(!$keyfound) && (!$itemfound)} {
	lappend data "" "\[$key\]"
	lappend data "$item$value"
  } elseif {$keyfound && (!$itemfound)} {
	lappend data "$item$value"
  }

  set iniparse($id,data) $data
}

#
# Usage:
#   iniparse:removeitem <fileId> <keyname> <itemname>
#	Removes <itemname> under <keyname> in <fileId>.
#
# Notes:
# - This procedure doesn't write directly to the file, but to the
#   memory-version of the file. If directly the file (not memory version) is
#   modified after the call to iniparse:openfile, this procedure will not
#   see the changes in the file, but only changes in memory-version.
#
# See: readini iniparse:openfile
#
proc iniparse:removeitem {id key item} {
global iniparse
  set fileline ""
  set keyfound 0
  set itemfound 0
  set itemlength [string length $item]
  set item "$item="

  if {[lsearch $iniparse(idlist) $id] == -1} return   ;# No such Id

  set fileline $iniparse($id,data)
  set data {}

  foreach line $fileline {
    if {(!$keyfound)} {          ;# We will search for the key.
	if {$line=="\[$key\]"} {
		lappend data "" $line
		set keyfound 1
		continue
	} else {lappend data $line; continue}
    }
    if {($keyfound) && (!$itemfound) && [chrchk $line]} {  ;# We hit the next key!
	lappend data "" $line
	set itemfound 1
	continue
    }
    if {($keyfound) && (!$itemfound)} {  ;# We will search for the item
	if {[string range $line 0 $itemlength]==$item} {
		set itemfound 1
		continue        ;# We don't print the line to file
	} else {lappend data $line; continue}
    }
    # Because it doesn't match anything above, we print the line to file
    if {[chrchk $line]} {lappend data "" $line} \
	else {lappend data $line}
  }

  set iniparse($id,data) $data
}

#
# Usage:
#   iniparse:removekey <fileId> <keyname>
#	Removes <keyname> in <fileId>.
#
# Notes:
# - This procedure doesn't write directly to the file, but to the
#   memory-version of the file. If directly the file (not memory version) is
#   modified after the call to iniparse:openfile, this procedure will not
#   see the changes in the file, but only changes in memory-version.
#
# See: readini iniparse:openfile
#
proc iniparse:removekey {id key} {
global iniparse
  set fileline ""
  set keyfound 0
  set keyfinished 0

  if {[lsearch $iniparse(idlist) $id] == -1} return   ;# No such Id

  set fileline $iniparse($id,data)
  set data {}

  foreach line $fileline {
    if {(!$keyfound)} {          ;# We will search for the key.
	if {$line=="\[$key\]"} {
		set keyfound 1
		continue
	}
    }
    if {($keyfound) && (!$keyfinished) && (![chrchk $line])} {  ;# We are waiting for the next key
	continue
    }
    if {($keyfound) && (!$keyfinished) && ([chrchk $line])} {  ;# We are hit the next key!
	lappend data "" $line
	set keyfinished 1
	continue
    }
    # Because it doesn't match anything above, we print the line to file
    if {[chrchk $line]} {lappend data "" $line} \
	else {lappend data $line}
  }

  set iniparse($id,data) $data
}

#
# Usage:
#   iniparse:renameitem <fileId> <keyname> <itemName> <newItemName>
#	Renames <itemName> under <keyname> in <fileId> to <newItemName>.
#
# Notes:
# - This procedure doesn't write directly to the file, but to the
#   memory-version of the file. If directly the file (not memory version) is
#   modified after the call to iniparse:openfile, this procedure will not
#   see the changes in the file, but only changes in memory-version.
#
# See: readini iniparse:openfile
#
proc iniparse:renameitem {id key olditem newitem} {
  writeini $id $key $newitem [readini $id $key $olditem]
  iniparse:removeitem $id $key $olditem
}

#
# Usage:
#   iniparse:renamekey <fileId> <keyname> <newKeyName>
#	Renames <keyname> in <fileId> to <newKeyName>.
#
# Notes:
# - This procedure doesn't write directly to the file, but to the
#   memory-version of the file. If directly the file (not memory version) is
#   modified after the call to iniparse:openfile, this procedure will not
#   see the changes in the file, but only changes in memory-version.
#
# See: readini iniparse:openfile
#
proc iniparse:renamekey {id oldkey newkey} {
global iniparse

  if {[lsearch $iniparse(idlist) $id] == -1} return   ;# No such Id

  set fileline $iniparse($id,data)
  set data {}

  foreach line $fileline {
	if {$line=="\[$oldkey\]"} {
		lappend data "" "\[$newkey\]"
		continue
	} else {
		if {[chrchk $line]} {lappend data "" $line} \
		else {lappend data $line}
	}
  }

  set iniparse($id,data) $data
}

