Building for the first time:

Visual Studio:
	Open Saa-Application.sln in the _build_win folder
Unix/Linux
	Create a new _build_xxx folder, with xxx as your target OS.
	CD into the folder
	run Cmake .. to generate a makefile
	run Make to build the application
	run make install to copy the built application into _build_xxx/bin
	run the tests to verify the code built correctly.

Updating Files:
	If you are adding new files, run ```cmake .```
	If you are adding new folders, open up the CMakeLists.txt of the source tree you are in (Include, src, app)
	Add a new pair of the following:
	```
	file (GLOB $FOLDERNAME_[Sources/Headers/Tests]
		"$FOLDERNAME/*.cpp"
	    source_group("$FOLDERNAME" FILES ${$FOLDERNAME_[Sources/Headers/Tests]})```
	Ping Kyle P if Cmake is giving you crap

