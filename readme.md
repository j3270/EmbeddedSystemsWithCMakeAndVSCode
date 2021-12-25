
# Purpose 

The purpose of this repo is for learning.  I am evaluating SAMD devices and using the ARM GNU Toolchain with CMake and VS Code.  To get started with the SAMD devices I am using the stand alone Advanced Software Framework v3.51.0 from Microchip (Atmel).  

1. SAMD Devices  
https://www.microchip.com/en-us/parametric-search.html/650  
2. ARM GNU Toolchain  
https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm
3. CMake  
https://cmake.org/
4. VS Code  
https://code.visualstudio.com/  
5. ASF Home Page  
https://asf.microchip.com/docs/latest/index.html  
6. xdk-asf-3.51.0 download (hard to find)  
https://www.microchip.com/en-us/tools-resources/develop/libraries/advanced-software-framework
7.  Atmel Packs  
http://packs.download.atmel.com/,  
I was looking for svd files, to use with Segger's Ozone debugger, which didn't appear to be part of the xdk download.

I am currently using the following evaluation boards for developemnt along with a couple devices on surf boards with a breadboard.

1.  samd10_xplained_mini  
https://www.microchip.com/en-us/development-tool/ATSAMD10-XMINI
2.  saml21_xplained_pro  
https://www.microchip.com/en-us/development-tool/atsamd21-xpro

# Repository Structure

- build (ignored)
- projects
- tools
- xdk-asf-3.51.0 (need to trim files not needed)
- packs
