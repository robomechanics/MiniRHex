**MiniRHex: An Open-Source Hexapod Robot**

![MiniRHex Running](Images/miniOnStumpScaled.jpg)
Contact: 

MiniRHex is a miniature scale hexapod designed by the [Robomechanics Lab](https://www.cmu.edu/me/robomechanicslab/) based on the design of RHex. Notable features include a laser-cut frame and 3D printed legs for low cost construction and an intuitive software package that allows for highly-customizable control over the robot’s behavior. MiniRHex is designed to be an educational and outreach tool to allow students to experiment with a fully functional walking robot at a much lower cost. The low price tag lets research groups maintain a fleet of machines, allowing each student more hands-on interaction with the hardware. Possible educational principles include gait design and optimization, leg design and control, and mobile robot sensor incorporation.

![MiniRHex Running](Images/miniOnStumpScaled.jpg)

# Setup Instructions
Building a MiniRhex requires access to a 3D printer. The links for off the shelf parts can be found below.

![MiniRHex Prototype](Images/mini1.jpg)

### Acquire Parts
The Parts List and Links to order can be found in [Parts List](https://github.com/robomechanics/MiniRHex/tree/master/HardwareList).

### Assemble Robot
Assembly Instructions available at [Assembly Instructions](https://github.com/robomechanics/MiniRHex/tree/master/Assembly).

### Install Software
1. Install the Arduino IDE from https://www.arduino.cc/en/software
2. Open the Arduino IDE and under "Tools" select "Manage Libraries..."
   - Type "DynamixelShield" into the search bar
   - Select "Install" for the DynamixelShield library
3. Under "Tools" hover over "Board" and select "Boards Manager..."
   - Type "Arduino SAMD Boards" into the search bar
   - Select "Install" for the Arduino SAMD Boards (32-bits ARM Cortex-M0+)
4. (Non-developers) Download the MiniRHex repository from https://github.com/robomechanics/MiniRHex/archive/refs/heads/minirhex_redesign_2022.zip and extract the downloaded zip file
5. (Developers) Clone the MiniRHex repository from https://github.com/robomechanics/MiniRHex.git and checkout the "minirhex_redesign_2022" branch

### Configure Servo ID's
1. Use Dynamixel Wizard 2.0


![MiniRHex](Images/miniOnStumpScaled.jpg)


# Operating Instructions
1. Connect the MiniRHex to your computer via the Micro USB port
2. Open MiniRHex.ino (located in the MiniRHex subfolder) in the Arduino IDE and check that under "Tools":
   - "Board" is set to "Arduino MKR WiFi 1010"
   - "Port" is set to the correct COM port, e.g. "COM# (Arduino MKR WiFi 1010)"
3. Upload code to the robot (the circular button near the top left with an arrow pointing to the right)
4. Insert the battery, fasten the velcro straps, and connect the battery cable
5. Open the Serial Monitor in the Arduino IDE (the circular button in the top right with a magnifying glass)
6. Type "w" into the text box and hit enter to start walking! ("q" to stop, "s" to reverse", "A" to turn left, "D" to turn right)
7. To modify the walking gait, go to the "gait_parameters.cpp" tab in the Arduino IDE and edit the parameters for each leg, then upload code again (see comments in the file for more details)
8. When finished, unplug the battery and store it in a fireproof container (never leave a battery in the robot!)

# Robot Specifications
![MiniRHex Specifications](Images/Spec_Chart.png)

# Useful Links
### Parts List
The part list can be found at [Parts List](https://github.com/robomechanics/MiniRHex/tree/master/HardwareList).
### MiniRHex Repository
The MiniRHex repository can be found at [MiniRHex Repository](https://github.com/robomechanics/MiniRHex.git).
### Cite MiniRHex
If referencing MiniRHex in a paper, please cite [this abstract](http://www.andrew.cmu.edu/user/amj1/papers/RSS2018ws_MiniRHex.pdf).
Use [this BibTeX](https://github.com/robomechanics/MiniRHex/blob/master/citation.txt) for citations:
> M. Barragan, N. Flowers, and A. M. Johnson. "MiniRHex: A Small, Open-source, Fully Programmable Walking Hexapod". In *Robotics: Science and Systems Workshop on ``Design and Control of Small Legged Robots''*, Pittsburgh, PA, June 2018.

### Images
See the [image gallery](https://robomechanics.github.io/MiniRHex/Images/) for more MiniRHex pictures.
        
![MiniRHex Running](Images/miniOnStumpScaled.jpg)
### Videos
Check out the Robomechanics Lab [YouTube Page](https://www.youtube.com/watch?v=ldLXVDNCCzc&list=PLxHmBiQi0bD2aFgPKIrXhYXCCOGhTQmmk) for videos of MiniRHex in action!

# Contributors
MiniRHex was designed by the following people in the [Robomechanics Lab](https://www.cmu.edu/me/robomechanicslab/)
* Nikolai Flowers (BS ME '20)
* Barrett Werner (MS ME '19)
* Monica Barragan (BS ME '19)
* Cameron Selby (MS ME '18)
* Scott Phillips (BS ME '20)
* J. Joe Payne (Ph.D ME)
* Joe Norby (Ph.D ME '22)
* Catherine Pavlov (Ph.D ME)
* Aaron Johnson (Advisor)





