## Moria CNC
The Moira CNC project was started as an exploration into computer numeric controlled machine technology. The goal was to build a custom CNC from scratch using no existing frameworks or designs.

## Printable Files

#### Machine Instruction File (.mi)
Coordinate trace files instruct the CNC with a sequence of instructions. They have a simple structure in order to keep file size manageable and to make them easy for the C program to read. Each line of the file is prefixed with a single character denoting the instruction type followed by the appropriate payload for that instruction. Instructions are listed below:

Type `Empty line`
Execution `All empty lines are skipped.`

Type `D`  
Payload `count` type `int`  
Example `D 1`  
Execution `The number of defined routines in the file.`

Type `R`  
Payload `id:count` type `int:int`  
Example `R 0:2`  
Execution `Defines a routine with the 'id' given that will span the subsequent 'count' instructions.`

Type `c`  
Payload `x,y,z` type `int,int,int` with optional `+` or `-` prefix  
Example `c 5,10,25` or `c +5,-10,25`  
Execution `Instructs the CNC to set the axis to the given coordinate from the instruction line. If an axis has a + or - the coordinate is determined by the previous coordinate plus that value.`

Type `r`  
Payload `id` type `int`  
Example `r 0`  
Execution `Calls the defined routine with the matching 'id'.`

Type `s`  
Payload `id payload` type `int any`  
Example `s 0 50,10,75`  
Execution `Calls a predefined "special" instruction with the matching 'id' then passes the 'payload' to that special instruction.`

Type `w`  
Payload `milliseconds` type `int`  
Example `w 1000`  
Execution `Waits the given number of milliseconds before continuing to the next instruction.`

Upon execution the CNC will iterate over all of the instructions listed in the file and execute them in order.
