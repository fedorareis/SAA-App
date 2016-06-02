# Team Rocket: Sense And Avoid Application
#### Version 0.1.0.a1

##### Changelog
##### Version 0.2.0.b1
- Beta release.
- Documentation update for build script issues
- Brand new CDTI!
- Corrected Radar and TCAS sensors
- Mean Shift actually works!
##### Version 0.1.0.a1
- Alpha release! 
- Added build script to assist testers in building
- Documentation for tool added.

***

# How to use this document:
The documentation provided here is intended mostly for system configurators and testers. The document covers the basics of the SAA system, installation instructions, and provides reference links to other major documentation for the project.

Goals of the project are contained in Section 1. Installation instructions are contained in Section 2. Using the system is described in Section 3. System Architecture is found in Section 4. A guide to for test cases can be found in Section 5.

*****
### Version
0.2.0.b1

### Table of Contents
1. Project Goals / Use Cases
    1. Introduction
    2. Target Users
2. Installation and Dependencies
    1. List of Dependencies
    2. Installation Instructions
    3. Building 
3. Running the System
4. System Architecture
5. Build issues? Look here!
6. Test Case Documentation

### Section 1: Project Goals and Use Cases
For a more detailed overview of the system and it's requirements, please refer to the [Software Requirements Specification][SRS]

The Sense and Avoid Application is a program framework to analyze the effectiveness of data correlation algorithms. The application consists of three standalone programs.

##### The Test Server
The ```test-server``` application provides a program to generate sensor data for several types of sensors (TCAS, ADS-B, RADAR) from a test case specification. The test server also handles analyzing and verifying the results of correlation, allowing the correlation tests to run without having to manually validate the correlation algorithm.

##### The SAA Application
The ```saa-application``` models a UAV in an airspace. The application reads in simulated airspace data, and outputs an approximate view of the airspace using a correlation algorithm. The saa-application is the main interest of the whole SAA application.

##### The CDTI
The ```cdti``` application provides a simple graphical view into the current simulation state. The CDTI is meant to help in debugging the simulation, as well as providing a more understandable look into the end result of the correlation algorithm. The CDTI does not need to be running, and is an optional component.

#### Use Cases
The major use case for the Saa Application is to provide a framework for analyzing, testing, and comparing correlation algorithms. Most research work with the application will occur in the saa-application. The test server and CDTI provide tools for analyzing the research done.

#### Target Users
The target users for Version 0.1.0 A are testers, and team members. This version is not meant as a public release, but an early preview to ensure that the software runs successfully. Several large features are missing from this release, the most glaring being a good correlation algorithm.

### Section 2: Installation and Dependencies 
To download project dependencies and build the application, run ```./build.sh``` from the home folder.

 > Note, this script is still in early alpha. If you experience problems, please contact the project maintainers with your error log.
 
The SAA application relies on the following dependencies:

* [CMake][cmake] (Ver 2.8.12 +) to handle building the application
* [QT5][qt] for displaying the CDTI
* [Google Protocol Buffers][protobuf] (Ver 3.0.0) to handle encoding and decoding messages between each component of the application.
* [MLPack][mlpack] provides some of the base methods used in our clustering techniques.
   *   MLPack depends on the following:
   *    Armadillo     >= 4.100.0
   *    Boost (program_options, math_c99, unit_test_framework, serialization)
  
* [GoogleTest][gtest] allows us to test our application, and write mock objects.

 Once the system is built, Unit tests can be run by running ```test-all```

### Section 3: Running the system
 
 For a basic run of the system, run ```app/test-server```, then ```app/saa-application```. from the build folder The application will load a default test case, and begin simulating data.
 
 To specify a test case, run the command ```test-server <test case>```, where test case is the path to a properly formatted XML test case. 
 
 At any point during a simulation, you may also run the program ```app/cdti``` to view the current state of the simulation on a display.
 
### Section 4: System Architecture
 This section is provided as a quick reference of the major components of the system. It is meant to help a new team member get quickly acquainted with the structure of the program.

The SAA Application is broken up into four major modules, found in the ```src``` folder. ```common```, ```cdti```, ```saa-application``` and ```test-server```.

The Common folder contains functions and classes used across all three sub-applications of the project, including the networking code, and some plane math.

The other three submodules contain support classes for their sub-applications. Correlation and decision making code exists in  ```saa-application```, Test case code exists in ```test-server```, and graphics code exists in ```cdti```

The main methods for each application exist in the top level ```app``` directory.

A third top level directory, ```test``` contains unit tests.

### Section 5: Build issue FAQ
We’ve had a few issues with the build process due to the difficulty of wrangling C++ dependencies. If you have run ```build.sh``` and are having trouble building the project, try these steps:

1. On OSX: use Homebrew to install the following dependencies:
 ```brew install homebrew/science/armadillo
 brew install boost
 brew install qt5
 brew install autoconf
 brew install automake
 brew install libtool```

2. On Linux:
 ```sudo apt-get install libarmadillo-dev libboost-all-dev qtdeclarative5-dev autoconf automake libtool```

3. Re-run ```cmake ..``` from the build folder, then ```make```.

4. If all else fails, please contact the project maintainer at kpidding@calpoly.edu.

### Section 6: Test Case Documentation
Below is an example Test Case from the application. Test cases are a standard xml document. More examples of test cases can be found under ```resources/testCases```.

    <test name="Two Planes Crossing"
      description="The two planes approach each other, but remain seperate correlations"
      time = "120"
      sensorError="false">

    <ownship tag="ABC123">
        <tcas enabled="true" error="1.5"/>
        <radar enabled="true"/>
        <ads-b enabled="true" error="0.2"/>
        <movement type="linear">
            <position x="0" y="0" z="0"/>
            <direction x="200" y="0" z="0"/>
        </movement>
    </ownship>
    
    <plane tag="N11111">
        <ads-b enabled="true"/>
        <tcas enabled="true"/>
        <movement type="linear">
            <position x="-2" y="10" z="0.3"/> <!--NED in Nautical Miles-->
            <direction x="800" y="0" z="0"/> <!--Feet/second-->
        </movement>
    </plane>
    
    <plane tag="N22222">
        <ads-b enabled="true"/>
        <tcas enabled="true"/>
        <movement type="linear">
            <position x="2" y="14" z="0.3"/> <!--NED in Nautical Miles-->
            <direction x="-800" y="300" z="0"/> <!--Feet/second-->
        </movement>
    </plane>
    </test>

The basic structure of a test case is:

    <test name = ""
          description = string
          time = number
          sensorError = bool
        <ownship tag = "">
            <Sensor tags>
            <Movement tag>
         </ownship>
         <plane tag = "">
            <Sensor options>
            <Movement option>
         ...
         </plane>
    </test>


 
 
 

 
 
 






[SRS]:[https://docs.google.com/viewer?a=v&pid=sites&srcid=ZGVmYXVsdGRvbWFpbnxzZWNhcHN0b25lMTUxNmdhfGd4OjQwZjA0YTk4YmEwYjI1YzU]
[cmake]:(www.cmake.org)
[qt]:(http://www.qt.io/)
[protobuf]:(https://github.com/google/protobuf)
[mlpack]:(https://github.com/mlpack/mlpack)
[gtest]:(https://github.com/google/googletest)