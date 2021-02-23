## Moria CNC
The Moira CNC project was started as an exploration into computer numeric controlled machine technology. The goal was to build a custom CNC from scratch using no existing frameworks or designs.

## Printable Files

#### Coordinate Trace (.ct)
Coordinate trace files instruct the CNC with a sequence of coordinates to 'trace'. They have a simple structure in order to keep file size manageable and to make them easy for the C program to read. Each line of the file is prefixed with a single character denoting the instruction type followed by the appropriate payload for that instruction. Instructions are listed below:

Type `c`  
Payload `x,y,z`  
Example `c 5,10,25`  
Execution `Instructs the CNC to set the print head to the given coordinate from the instruction line.`

Upon execution the CNC will iterate over all of the instructions listed in the file and execute them in order.

#### CTXML (.ctxml)
CTXML files wre created for the purpose of being a readable/editable version of coordinate trace files. It is easy to write a `.ct` file with definitive coordinates, however, `.ctxml` files give additional functionality for creating instructions. This functionality comes from the ability to define routines, which are a series of instructions that can be called, and coordinates can be prepended with wither a `+` or `-` to denote an addition or subtraction to the previous coordinate. This comes in handy if you have a routine such as lifting the print head up by x units from its current position.