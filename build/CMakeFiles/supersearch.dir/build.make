# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/build

# Include any dependencies generated for this target.
include CMakeFiles/supersearch.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/supersearch.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/supersearch.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/supersearch.dir/flags.make

CMakeFiles/supersearch.dir/src/Document.cpp.o: CMakeFiles/supersearch.dir/flags.make
CMakeFiles/supersearch.dir/src/Document.cpp.o: /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/Document.cpp
CMakeFiles/supersearch.dir/src/Document.cpp.o: CMakeFiles/supersearch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/supersearch.dir/src/Document.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/supersearch.dir/src/Document.cpp.o -MF CMakeFiles/supersearch.dir/src/Document.cpp.o.d -o CMakeFiles/supersearch.dir/src/Document.cpp.o -c /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/Document.cpp

CMakeFiles/supersearch.dir/src/Document.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/supersearch.dir/src/Document.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/Document.cpp > CMakeFiles/supersearch.dir/src/Document.cpp.i

CMakeFiles/supersearch.dir/src/Document.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/supersearch.dir/src/Document.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/Document.cpp -o CMakeFiles/supersearch.dir/src/Document.cpp.s

CMakeFiles/supersearch.dir/src/DocumentParser.cpp.o: CMakeFiles/supersearch.dir/flags.make
CMakeFiles/supersearch.dir/src/DocumentParser.cpp.o: /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/DocumentParser.cpp
CMakeFiles/supersearch.dir/src/DocumentParser.cpp.o: CMakeFiles/supersearch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/supersearch.dir/src/DocumentParser.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/supersearch.dir/src/DocumentParser.cpp.o -MF CMakeFiles/supersearch.dir/src/DocumentParser.cpp.o.d -o CMakeFiles/supersearch.dir/src/DocumentParser.cpp.o -c /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/DocumentParser.cpp

CMakeFiles/supersearch.dir/src/DocumentParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/supersearch.dir/src/DocumentParser.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/DocumentParser.cpp > CMakeFiles/supersearch.dir/src/DocumentParser.cpp.i

CMakeFiles/supersearch.dir/src/DocumentParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/supersearch.dir/src/DocumentParser.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/DocumentParser.cpp -o CMakeFiles/supersearch.dir/src/DocumentParser.cpp.s

CMakeFiles/supersearch.dir/src/IndexHandler.cpp.o: CMakeFiles/supersearch.dir/flags.make
CMakeFiles/supersearch.dir/src/IndexHandler.cpp.o: /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/IndexHandler.cpp
CMakeFiles/supersearch.dir/src/IndexHandler.cpp.o: CMakeFiles/supersearch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/supersearch.dir/src/IndexHandler.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/supersearch.dir/src/IndexHandler.cpp.o -MF CMakeFiles/supersearch.dir/src/IndexHandler.cpp.o.d -o CMakeFiles/supersearch.dir/src/IndexHandler.cpp.o -c /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/IndexHandler.cpp

CMakeFiles/supersearch.dir/src/IndexHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/supersearch.dir/src/IndexHandler.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/IndexHandler.cpp > CMakeFiles/supersearch.dir/src/IndexHandler.cpp.i

CMakeFiles/supersearch.dir/src/IndexHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/supersearch.dir/src/IndexHandler.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/IndexHandler.cpp -o CMakeFiles/supersearch.dir/src/IndexHandler.cpp.s

CMakeFiles/supersearch.dir/src/QueryProcessor.cpp.o: CMakeFiles/supersearch.dir/flags.make
CMakeFiles/supersearch.dir/src/QueryProcessor.cpp.o: /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/QueryProcessor.cpp
CMakeFiles/supersearch.dir/src/QueryProcessor.cpp.o: CMakeFiles/supersearch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/supersearch.dir/src/QueryProcessor.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/supersearch.dir/src/QueryProcessor.cpp.o -MF CMakeFiles/supersearch.dir/src/QueryProcessor.cpp.o.d -o CMakeFiles/supersearch.dir/src/QueryProcessor.cpp.o -c /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/QueryProcessor.cpp

CMakeFiles/supersearch.dir/src/QueryProcessor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/supersearch.dir/src/QueryProcessor.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/QueryProcessor.cpp > CMakeFiles/supersearch.dir/src/QueryProcessor.cpp.i

CMakeFiles/supersearch.dir/src/QueryProcessor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/supersearch.dir/src/QueryProcessor.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/QueryProcessor.cpp -o CMakeFiles/supersearch.dir/src/QueryProcessor.cpp.s

CMakeFiles/supersearch.dir/src/Stemmer.cpp.o: CMakeFiles/supersearch.dir/flags.make
CMakeFiles/supersearch.dir/src/Stemmer.cpp.o: /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/Stemmer.cpp
CMakeFiles/supersearch.dir/src/Stemmer.cpp.o: CMakeFiles/supersearch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/supersearch.dir/src/Stemmer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/supersearch.dir/src/Stemmer.cpp.o -MF CMakeFiles/supersearch.dir/src/Stemmer.cpp.o.d -o CMakeFiles/supersearch.dir/src/Stemmer.cpp.o -c /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/Stemmer.cpp

CMakeFiles/supersearch.dir/src/Stemmer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/supersearch.dir/src/Stemmer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/Stemmer.cpp > CMakeFiles/supersearch.dir/src/Stemmer.cpp.i

CMakeFiles/supersearch.dir/src/Stemmer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/supersearch.dir/src/Stemmer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/Stemmer.cpp -o CMakeFiles/supersearch.dir/src/Stemmer.cpp.s

CMakeFiles/supersearch.dir/src/StopWords.cpp.o: CMakeFiles/supersearch.dir/flags.make
CMakeFiles/supersearch.dir/src/StopWords.cpp.o: /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/StopWords.cpp
CMakeFiles/supersearch.dir/src/StopWords.cpp.o: CMakeFiles/supersearch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/supersearch.dir/src/StopWords.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/supersearch.dir/src/StopWords.cpp.o -MF CMakeFiles/supersearch.dir/src/StopWords.cpp.o.d -o CMakeFiles/supersearch.dir/src/StopWords.cpp.o -c /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/StopWords.cpp

CMakeFiles/supersearch.dir/src/StopWords.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/supersearch.dir/src/StopWords.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/StopWords.cpp > CMakeFiles/supersearch.dir/src/StopWords.cpp.i

CMakeFiles/supersearch.dir/src/StopWords.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/supersearch.dir/src/StopWords.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/StopWords.cpp -o CMakeFiles/supersearch.dir/src/StopWords.cpp.s

CMakeFiles/supersearch.dir/src/UserInterface.cpp.o: CMakeFiles/supersearch.dir/flags.make
CMakeFiles/supersearch.dir/src/UserInterface.cpp.o: /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/UserInterface.cpp
CMakeFiles/supersearch.dir/src/UserInterface.cpp.o: CMakeFiles/supersearch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/supersearch.dir/src/UserInterface.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/supersearch.dir/src/UserInterface.cpp.o -MF CMakeFiles/supersearch.dir/src/UserInterface.cpp.o.d -o CMakeFiles/supersearch.dir/src/UserInterface.cpp.o -c /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/UserInterface.cpp

CMakeFiles/supersearch.dir/src/UserInterface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/supersearch.dir/src/UserInterface.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/UserInterface.cpp > CMakeFiles/supersearch.dir/src/UserInterface.cpp.i

CMakeFiles/supersearch.dir/src/UserInterface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/supersearch.dir/src/UserInterface.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/UserInterface.cpp -o CMakeFiles/supersearch.dir/src/UserInterface.cpp.s

CMakeFiles/supersearch.dir/src/main.cpp.o: CMakeFiles/supersearch.dir/flags.make
CMakeFiles/supersearch.dir/src/main.cpp.o: /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/main.cpp
CMakeFiles/supersearch.dir/src/main.cpp.o: CMakeFiles/supersearch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/supersearch.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/supersearch.dir/src/main.cpp.o -MF CMakeFiles/supersearch.dir/src/main.cpp.o.d -o CMakeFiles/supersearch.dir/src/main.cpp.o -c /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/main.cpp

CMakeFiles/supersearch.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/supersearch.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/main.cpp > CMakeFiles/supersearch.dir/src/main.cpp.i

CMakeFiles/supersearch.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/supersearch.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/src/main.cpp -o CMakeFiles/supersearch.dir/src/main.cpp.s

# Object files for target supersearch
supersearch_OBJECTS = \
"CMakeFiles/supersearch.dir/src/Document.cpp.o" \
"CMakeFiles/supersearch.dir/src/DocumentParser.cpp.o" \
"CMakeFiles/supersearch.dir/src/IndexHandler.cpp.o" \
"CMakeFiles/supersearch.dir/src/QueryProcessor.cpp.o" \
"CMakeFiles/supersearch.dir/src/Stemmer.cpp.o" \
"CMakeFiles/supersearch.dir/src/StopWords.cpp.o" \
"CMakeFiles/supersearch.dir/src/UserInterface.cpp.o" \
"CMakeFiles/supersearch.dir/src/main.cpp.o"

# External object files for target supersearch
supersearch_EXTERNAL_OBJECTS =

supersearch: CMakeFiles/supersearch.dir/src/Document.cpp.o
supersearch: CMakeFiles/supersearch.dir/src/DocumentParser.cpp.o
supersearch: CMakeFiles/supersearch.dir/src/IndexHandler.cpp.o
supersearch: CMakeFiles/supersearch.dir/src/QueryProcessor.cpp.o
supersearch: CMakeFiles/supersearch.dir/src/Stemmer.cpp.o
supersearch: CMakeFiles/supersearch.dir/src/StopWords.cpp.o
supersearch: CMakeFiles/supersearch.dir/src/UserInterface.cpp.o
supersearch: CMakeFiles/supersearch.dir/src/main.cpp.o
supersearch: CMakeFiles/supersearch.dir/build.make
supersearch: CMakeFiles/supersearch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable supersearch"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/supersearch.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/supersearch.dir/build: supersearch
.PHONY : CMakeFiles/supersearch.dir/build

CMakeFiles/supersearch.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/supersearch.dir/cmake_clean.cmake
.PHONY : CMakeFiles/supersearch.dir/clean

CMakeFiles/supersearch.dir/depend:
	cd /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4 /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4 /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/build /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/build /Users/davidzachariah/Desktop/Zachariah_CS53-002_Project4/build/CMakeFiles/supersearch.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/supersearch.dir/depend
