        @echo off
        if (%1)==(?) goto :usage
        if not (%1)==() goto :arg
		goto :noarg

rem =============================================================
rem ==== Usage
rem =============================================================

:usage
        echo Usage: perftool [function_name]
        goto :end

rem =============================================================
rem ==== Jump Table
rem =============================================================

:arg
        set oldpath=%path%
        set path=..\..\bin;%path%
        @echo on
        perftool.exe -m -B -R FAIL -lperftool.lst -sperftool.fts -C -cTiming -f%1
		@echo off
		set path=%oldpath%
		set oldpath=
		goto :end

:noarg
        set oldpath=%path%
        set path=..\..\bin;%path%
        @echo on
        perftool.exe -m -B -R FAIL -lperftool.lst -sperftool.fts -C -cTiming
		@echo off
		set path=%oldpath%
		set oldpath=

:end
