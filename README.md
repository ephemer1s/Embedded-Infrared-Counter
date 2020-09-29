# Embedded Infrared Counter based on STC89C52 MicroProcessor

## File Index

* `Blueprint` - Circuit design of this embedded system.

* `HostApp` - C# Host GUI source code.

    * `Form1.cs` - GUI Implementations.

    * `ComVars.cs` - ComVars class, stores some of static variables.

* `Objects` - Compiled embedded codes.

    * `embedded.hex` - Compiled hex file.

* `SerialCom-py` - python serialport communication codes.

* `embedded.uvproj` - Keil uVision5 project.

* `STARTUP.A51` - AT89C51RC MPU Init Program.

* `ir.h` - Define functions and variables for Infrared sensors.

* `ir.c` - Implement functions in `ir.h`.

* `lcd.h` - Define functions and variables for LCD screen display.

* `lcd.c` - Implement functions in `lcd.h`.

* `main.c` - Main entrance of embedded codes.

* `x5045.h` - Define functions and variables for EEPROM save.

* `x5045.c` - Implement functions in `lcd.h`.