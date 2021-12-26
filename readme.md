
# Purpose

The purpose of this repo is for learning.  I am evaluating SAMD devices and using the following tools:  

- ARM GNU Toolchain  
<https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm>
- Segger's Ozone Debugger  
<https://www.segger.com/products/development-tools/ozone-j-link-debugger/>
- CMake  
<https://cmake.org/>
- VS Code  
<https://code.visualstudio.com/>  
- Advanced Software Framework v3.51.0 from Microchip (Atmel).  
<https://asf.microchip.com/docs/latest/index.html>  
<https://www.microchip.com/en-us/tools-resources/develop/libraries/advanced-software-framework>

I was looking for svd files, to use with Segger's Ozone debugger, which didn't appear to be part of the xdk download.  I found them here  
<http://packs.download.atmel.com/>

I am currently using the following evaluation boards for developemnt along with a couple of devices on surf boards with a breadboard.

1. samd10_xplained_mini  
<https://www.microchip.com/en-us/development-tool/ATSAMD10-XMINI>
2. saml21_xplained_pro  
<https://www.microchip.com/en-us/development-tool/atsamd21-xpro>

# Repository Structure

- build (ignored)
- projects
- tools
- xdk-asf-3.51.0 (need to trim files not needed)
- svd
