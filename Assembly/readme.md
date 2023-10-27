# Preparation
1. Acquire the following equipment.
   * 3D printer + PLA filament
   * Wire cutters
   * Small Phillips head screwdriver
   * Small flat head screwdriver (basic users only)
   * Soldering station (advanced users only)

2. Purchase necessary components from the [Hardware List](/HardwareList).
   * Amazon: Arduino MKR, Battery, Plastidip, JST Connector, 5V UBEC, and Velcro Straps
   * Robotis: Dynamixel Servos, Arduino Shield

# Fabrication
1. 3D print the following parts. STL files can be found in [CAD/STL](/CAD/STL) and SolidWorks files are provided in [CAD](/CAD) to allow modification if needed. It is recommended to print with PLA, using the provided settings. Make sure to remove any support material from the legs before assembly.

   * 1 robot body ([robot_body.STL](/CAD/STL/robot_body.STL)): 15%-20% infill, no supports
   * 4 standard front/back legs ([standard_leg.STL](/CAD/STL/standard_leg.STL)): 100% infill, support on build plate
   * 2 standard middle legs ([standard_leg_middle.STL](/CAD/STL/standard_leg_middle.STL)): 100% infill, support on build plate

   Certain users may desire to frequently switch out different legs, for which a quick-connect leg design is also available. The quick-connect legs are faster to swap, but less durable. Quick-connect leg users should instead print the following.

   * 1 robot body ([robot_body.STL](/CAD/STL/robot_body.STL)): 15%-20% infill, no supports
   * 4 quick-connect front/back legs ([quick_connect_leg.STL](/CAD/STL/quick_connect_leg.STL)): 100% infill, support on build plate
   * 2 quick-connect middle legs ([quick_connect_leg_middle.STL](/CAD/STL/quick_connect_leg_middle.STL)): 100% infill, support on build plate
   * 6 quick-connect hubs ([quick_connect_hub.STL](/CAD/STL/quick_connect_hub.STL)): 100% infill, support on build plate

   Several additional leg variants exist, all compatible with the quick-connect system. For each additional set of legs you will need to 3D print 4 front/back legs and 2 middle legs of the appropriate type (but no additional hubs are needed).

2. Add Plastidip to legs for increased friction.
   * Use Plastidip (either dip or spray) to coat around 75% of each of the six legs until a high friction surface forms on each leg.
   * Between each coat, let dry for at least one hour.
   * Make sure the dip is evenly coated around the leg.
   * Do not cover the through holes for the screws.

<img src="Images/plastidipLeg.jpg" width="50%">

# Assembly
1. Locate and sort motor screws.
    * Each of the motors comes with a set of screws. Open all six motor packages and sort into short and long screws.
    * You will need 4 short screws (M2x6) and 48 long screws (M2x8) to assemble the robot.
  
2. Mount the servos to the robot body.
    * Each motor needs 4 long screws. The screws will tap directly into the motor's plastic, so do not over tighten them.

<img src="Images/motorMounting.jpg" width="50%">

3. Trim the leads on the Arduino shield.
    * The Robotis Arduino shield comes with leads that are too long. Using wire cutters, trim them to within 1-2mm of the board.
    * Only trim the leads on the shield, not the Arduino itself!

<img src="Images/shieldPinsRemoved.jpg" width="50%">

4. Attach the JST connectors to the Arduino shield.
    * Basic users can insert the red and black wires into the green screw terminals (red goes into the + side, and black goes into the - side), then tighten them using the flat head screwdriver. Do not swap the colors, or it could severely damage the electronics!
    * Advanced users can instead solder the wires directly to the Arduino shield for a more robust connection, as pictured below.
<img src="Images/shieldSolderConnectorFull.jpg" width="50%">

5. Mount the Arduino shield to the robot body.
    * You will needs 4 short screws. The screws will tap directly into the motor's plastic, so do not over tighten them.
<img src="Images/shieldMounting.jpg" width="50%">

6. Stack the Arduino on top of the Arduino shield.
<img src="Images/arduinoMounting.jpg" width="50%">

7. Mount each leg to the robot
    * Each leg needs 4 long screws. The screws will tap directly into the motor hub's plastic, do not over tighten them.
    * Ensure that the notch on the leg aligns with the single notch on the motor hub. If the notches are misaligned, the legs will not move to the correct angles.

  ![Leg Mounting](/Images/legMounting.jpg)

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




