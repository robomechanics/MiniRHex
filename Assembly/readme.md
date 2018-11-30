# MiniRHex Assembly Instructions

1. Solidworks files available in /CAD
 * Any updated or changed SolidWorks parts will be uploaded here
  
2. Look at the MiniRhexHardware file to see the needed parts and links to the items.
  * McMaster: M3 locknuts, button head screws, and spacer; 3mm acrylic
  * Amazon: Battery, Plastidip, charger, and battery connectors
  * Robotis: Main board, Dynamixels, Bluetooth(optional)
  
3. Print the following (PLA), .stl files can be found in /CAD/STL
 * 6 servo sleeve parts, for best results print with the back side on the build plate 
 * 4 shaft-edge parts
 * 2 shaft-mid parts 
 * 1 battery case part 
 * 6 leg parts
 * if you have access to an Ultimaker 3 Extended printer gcode can be found in /STL 
  
4. Open base.sldprt and save as a .dxf file. Use this file to laser cut 3-mm thick acrylic to
serve as the foundation for the robot.

5. Prepare the mainboard for use.
 * Solder the battery connector onto one positive pinhole and one negative pinhole
  for power. The location on the board is shown below
  
  ![Power pin location](Images/MiniRhex_power_pins.PNG)
  
6. First, connect the battery case and mainboard to the foundation, with the USB port facing outwards
 * Connections:
    * Battery case: M3 button head x 10 mm, M3 nut
    * Mainboard: M3 spacer, M3 button head x 10 mm, M3 lock nut
  * Battery case is near the center of the foundation.
  * The mainboard’s micro-USB port should face out.
  * The mainboard will be towards the front of the robot.
  
7. Next, prepare the legs by using Plastidip (either dip or spray) and coating each of the six
legs until high friction surface forms on each leg.
  * Between each coat, let dry for at least one hour.
  * Make sure the dip is evenly coated around the leg.
  * Do not cover the through holes for the screws.
  
8. Connect four of the six legs to edge shafts (shorter shafts).
  * Align the leg through holes with the holes on the cut-out portion of the shaft.
  * Connection: M3 socket head x 10 mm
  * Ensure that there are two legs facing each direction (two for each side of the robot)
  
9. Connect the other two legs to the mid shafts (longer shaft).
  * Align the leg through holes with the holes on the cut-out portion of the shaft.
  * Connection: M3 socket head x 10 mm
  * For one of the two connections, be sure to switch the orientation of the leg
  because those will be attached to the opposite side of the robot.
  
10. Connect each shaft-leg apparatus to the Dynamixel XL-320 servo motor.
  * Orientation: Make sure the half circle each leg forms faces the front of the robot:
  towards the side with the mainboard.
  * Detach the center screw in the servo horn, and pry off the horn itself.
    * The horn looks like a small, black plastic cylinder.
  * Align the 4 through holes on the servo horn with the 4 extruded pieces on the shaft
  face (the shaft length doesn’t matter).
  * Align the horn (now connected to the leg apparatus) to its key on the body of the servo.
    * Once the horn is flush against the body, connect the horn/shaft/leg apparatus
    to the servo motor.
    * Connection: center screw that came with the servo

11. Slide each servo into a servo sleeve.

12. Connect each servo sleeve to the foundation.
  * Orientation: Be sure all legs face forward (semicircle faces the mainboard).
  * Connection: M3 button head x 10 mm, M3 nut
  
13. Connect the servos to the mainboard.
  * Connect such that no wires interfere with leg rotation.
14. Charge battery(ies) and check voltage(s).

15. Upload code using the micro-USB port.

16. Take electronic wires that come with the servos, and connect them like below

![wiring diagram](Images/MiniRhex_wiring_diagram.png)
 
 
