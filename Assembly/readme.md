# Required Equipment

* 3D printer
* Small Phillips head screwdriver

# MiniRHex Basic Assembly

1. Purchase all necessary components from the [Hardware List](/HardwareList).
  * Amazon: Arduino MKR, Battery, Plastidip, JST Connector, 5V UBEC, and Velcro Straps
  * Robotis: Dynamixel Servos, Arduino Shield

2. Locate Solidworks files for printing.
 * STL files for printing are available in [CAD](/CAD), and Solidworks files are provided for modification if needed. Any updated or changed STL files or SolidWorks parts will be uploaded here.

3. Print the following parts. STL files can be found in [CAD/STL](/CAD/STL). It is recommended that you print with PLA, using the following print parameters:
 * 1 robot body ([robot_body.STL](/CAD/STL/robot_body.STL)): 15%-20% infill, no supports
 * 6 legs ([standard_leg.STL](/CAD/STL/standard_leg.STL)): 100% infill, support on build plate

 ![Everything](/Images/3dPrintedComponents.jpg)
 Make sure to remove any support material from the legs before assembly.

4. Add Plastidip to legs for better friction.
  * Use Plastidip (either dip or spray) to coat around 75% of each of the six legs until a high friction surface forms on each leg.
  * Between each coat, let dry for at least one hour.
  * Make sure the dip is evenly coated around the leg.
  * Do not cover the through holes for the screws.

  ![Final Legs](/Images/finalLegs.jpg)

5. Locate and sort motor screws.
  * Each of the motors comes with a set of screws. Open all six motor packages and sort into short and long screws.
  * You will need 4 short screws (M2x6) and 48 long screws (M2x8) to assemble the robot.

6. Mount the servos to the robot body.
  *  Each motor needs 4 long screws. The screws will tap directly into the motor's plastic, do not over tighten them.

  ![Servo Mounting](/Images/servoMounting.jpg)

7. Mount each leg to the robot
  * Each leg needs 4 long screws. The screws will tap directly into the motor hub's plastic, do not over tighten them.
  * Ensure that the notch on the leg aligns with the single notch on the motor hub. If the notches are misaligned, the legs will not move to the correct angles.

  ![Leg Mounting](/Images/legMounting.jpg)
  
8. Prep Arduino and shield
  * The Dynamixel shield comes with leads that are too long. Using flush cutters, trim them to within 1-2mm of the board.
  * Stack the Arduino on top of the shield.

  ![Arduino Shield](/Images/arduinoShield.jpg)

9. Configure the servo IDs for each leg
  * Before connecting each servo sleeve to the foundation, configure each of the servo IDs by connecting them with the provided wires individually to the Arduino shield.

Instructions on how to [Configure Servo IDs](/#configure-servo-id-numbers).

10. Connect power distribution to boards and mount boards
  * TODO add directions

11. Connect motor cables
  * Daisy chain cables between motors and connect one motor to the port on the Aduino shield. 
  
12. Charge battery(ies) and check voltage(s)
  * Maximum voltage:  8.4V
  * Charge if below:  7.0V
  * Dispose if below: 5.0V

13. Upload code using the micro-USB port. More detailed instructions can be found [here](/#install-software).

14. Plug in the battery and run the robot!




