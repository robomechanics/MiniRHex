
# Required Equipment

* 3D printer
* Small Phillips head screwdriver

# MiniRHex Assembly Instructions

1. Purchase all necessary components
  * Amazon: Arduino MKR, Battery, Plastidip, charger, velcro straps for battery, and battery connectors
  * Robotis: Dynamixels, Arduino Shield, Bluetooth(optional)

2. Locate Solidworks files for printing
 * STL files for printing are available in /CAD, and Solidworks files are provided for modification if needed. Any updated or changed STL files or SolidWorks parts will be uploaded here

3. Print the following parts. .stl files can be found in /CAD/STL. It is recommended that you print with PLA, and with the following print parameters:
 * 1 robot body (XX.STL): 15%-20% infill, no supports
 * 6 legs (XX.STL): 100% infill, support on build plate

 All in all, the parts should look as follows:

 ![Everything](Images/miniOnStumpScaled.jpg)
 Make sure to remove any support material from the legs before assembly.

4. Add Plastidip to legs for better friction
  *  Use Plastidip (either dip or spray) to coat around 75% of each of the six legs until a high friction surface forms on each leg.
  * Between each coat, let dry for at least one hour.
  * Make sure the dip is evenly coated around the leg.
  * Do not cover the through holes for the screws.

  The legs should look as follows:

  ![Final Legs](Images/miniOnStumpScaled.jpg)

5. Locate and sort motor screws
  * Each of the motors comes with a set of screws. Open all six motor packages and sort into short and long screws.
  * You will need XX short screws and XX long screws to assemble the robot.

6. Mount the servos to the robot body
  *  Each motor needs 4 long screws. The screws will tap directly into the motor's plastic, do not over tighten them.

  ![Leg Orientation](Images/miniOnStumpScaled.jpg)

7. Mount each leg to the robot
  * Each leg needs 4 long screws. The screws will tap directly into the motor hub's plastic, do not over tighten them.
  * Ensure that the notch on the leg aligns with the single notch on the motor hub. If the legs are misaligned, the legs will not be at the correct angles.

8. Prep Arduino and shield
  * The Arduino comes with leads that are too long. Using flush cutters, trim them to within 1-2mm of the board.
  * Stack the shield on top of the Arduino and make sure the power selector is set to 5V, as in XXX

9. Configure the servo IDs for each leg
  * Before connecting each servo sleeve to the foundation, configure each of the servo IDs by connecting them with the provided wires individually to the Arduino shield.

Instructions on how to [Configure Servo IDs](https://github.com/robomechanics/MiniRHex#configure-servo-ids).

10. Connect power distribution to boards and mount boards
  * TODO add directions


11. Connect motor cables
  * Daisy chain cables between motors and connect one motor to the port on the Aduino shield. 
  
12. Charge battery(ies) and check voltage(s)
  * Maximum voltage:  8.4V
  * Charge if below:  7.0V
  * Dispose if below: 5.0V

13. Upload code using the micro-USB port. More detailed instructions can be found [here](https://robomechanics.github.io/MiniRHex).

14. Plug in the battery and run the robot!




