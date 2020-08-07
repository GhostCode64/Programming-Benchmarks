@echo off

echo *******************************************************************
echo * PROGRAMMING BENCHMARKS AUTOMATED TOOL                           *
echo * (C) GhostCode 2020. Code is available under the GNU GPL v3.0 *
echo * This software is provided AS-IS with no warrenty                *
echo *                                                                 *
echo * Current benchmark: FreeCAD                                      *
echo * Now executing: Setup base run                                   *
echo *******************************************************************

echo Checking to see if the workingDirectory folder exists...
dir
IF EXIST workingDirectory (
	echo It did, moving to directory...
	cd workingDirectory
) ELSE (
	echo It did not, creating and moving to the directory...
	mkdir workingDirectory
	cd workingDirectory
)

IF EXIST FreeCAD (
	echo It did, moving to directory...
	cd FreeCAD
) ELSE (
	echo It did not, creating and moving to the directory...
	git clone https://github.com/FreeCAD/FreeCAD.git
	cd FreeCAD
)