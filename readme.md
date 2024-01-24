
# Purpose

The purpose of this repo is for learning new (and old) tools used in embedded development.  I am currently using the following tools:  

- [ARM GNU Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)
- [Segger's Ozone Debugger](https://www.segger.com/products/development-tools/ozone-j-link-debugger/)
- [CMake](https://cmake.org/)
- [Ninja](https://ninja-build.org/)
- [VS Code](https://code.visualstudio.com/)
- [Advanced Software Framework v3.51.0 from Microchip (Atmel)](https://www.microchip.com/en-us/tools-resources/develop/libraries/advanced-software-framework)  
<https://asf.microchip.com/docs/latest/index.html>

The ASF download didn't include SVD files for peripheral register viewing in VS Code and Ozone.  I found them here,  
[SVD Files](http://packs.download.atmel.com/)

# Repository Structure

- build (ignored)
- devices (future work for sensors, external memory, etc..)
- projects
- Submodules (External repos)
- scheduler (Simple CoOp scheduler I am playing with)
- tools (Cmake files/modules, svd files, SeggerRTT, etc.)
- xdk-asf-3.52.0 (need to trim files not needed)

# Boards

I am currently using the following evaluation boards for developemnt.

1. [samd21_xplained_pro](https://www.microchip.com/en-us/development-tool/atsamd21-xpro)  
a. CMake arg for target is __SAMD21J18A__  
b. J-Link arg for target is ATSAMD21J18  
c. SVD file is ATSAMD21J18A.svd  
2. [Adafruit Feather M0 Basic Proto](https://www.adafruit.com/product/2772?gclid=Cj0KCQiA6NOPBhCPARIsAHAy2zCJ24o8rdmKfSZByKKUvmDvdK_EmlqnPDycbiYHH-I0W7Z0hW63EnwaArjrEALw_wcB)  
a. CMake arg for target is __SAMD21G18A__  
b. J-Link arg for target is ATSAMD21G18  
c. SVD file is ATSAMD21G18A.svd  

I updated the EDBG firmware on the SAMD21_Xplained_pro evaluation board to Segger_OB firmware by following the instructions at this link, [Firmware for Atmel EDBG on Xplained Platforms](https://www.segger.com/products/debug-probes/j-link/models/other-j-links/j-link-edbg/).  This firmware makes the EDBG mcu J-Link compatiable with some limitations that are documented at the previous link.

# VS Code & CMake Workspace/Project structure

I have structured my CMake and VS Code workspace files to support a workspace/project structure.  The root CmakeLists.txt file adds a subdirectory 'projects'.  The projects directory CmakeLists.txt file adds each project as a sub directory allowing for a workspace/project perspective from the root of the repo.  All projects are buildable and debugable from the root VS Code workspace.

In addition, each project has its own VS Code workspace file allowing for working with that project stand alone if desired.

To add a new project, start at the project level.

1. Add a new folder under projects with your project name.
2. Add a CmakeLists.txt file to the root of your project using an existing project's CmakeLists.txt file as an example.
3. Add .vscode folder and copy contents of existing projects .vscode folder to yours.  Update appropriately.
4. Add a jdebug project file for your project for Ozone
5. In the 'projects' directories CmakeLists.txt file insert an add_subdirectory() command for your project.
6. Update the top level launch.json and tasks.json files for your project.

If anyone has suggestions for improvements on this strategy with respect to my use of Cmake and VS Code workspaces, I would appreciate the feedback.  Please be constructive.

# Building Projects

The workspace uses Cmake with Cmake tools for VS code to configure the build for each project and Ninja as the build generator.  To build the projects you will need to install the following tools:

1. [VS Code](https://code.visualstudio.com/) with the following extensions:  
a. C/C++ Extension Pack  
b. Cmake Tools  
c. Cmake language support (optional)  
d. Cortex-Debug  
2. [CMake](https://cmake.org/) build configuration tool
3. [Ninja](https://ninja-build.org/) build generator
4. [ARM GNU Toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)

After installing the above tools, add the following environment variable:  
**ARM_NONE_EABI_TOOLCHAIN**, which should point to something like */home/username/arm_gnu_toolchain/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi* depending on where you have installed it too.

With the above tools installed, you should be able to open the top level workspace file (or an individual project workspace file) with VS Code and select **GNU ARM Embeeded Toolchain** as the active kit.  If the CMake extension hasn't already started configuring the build for the project(s), use ctrl+shift+p to bring up the command pallate, type CMake and select CMake: Configure.

Once the build configurations have completed successfully, click the build icon (with 'all' selected, or the individual project you want to build) in the bottom ribon of VS code.

# Debugging Projects

Launch configurations have already been added for debugging existing projects with gdb and VS Code.  There are plenty of tutorials out there for doing this.

I have also added tasks for debugging with [Segger's Ozone](https://www.segger.com/products/development-tools/ozone-j-link-debugger/).  You will need to download and install Ozone, add it to your path, and add the environment variable **OZONE** for the tasks to work.  Running the task should launch Ozone for the project named by the task.

# Feedback welcome

For anyone stumbling across this repo and finds these notes to brief, constructive feedback is welcome
