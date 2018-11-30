# MiniRHex: An Open-source Walking Hexapod
Contact: nflowers@andrew.cmu.edu
![MiniRHex Running](Images/still.bmp)


MiniRHex is a miniature scale hexapod heavily based on the design of RHex. Notable features include a laser-cut frame and 3D printed legs for low cost construction and an intuitive software package that allows for highly-customizable control over the robot’s behavior. MiniRHex is designed to be an educational and outreach tool to allow students to experiment with a fully functional walking robot at a much lower cost. The low price tag lets research groups maintain a fleet of machines, allowing each student more hands-on interaction with the hardware. Possible educational principles include gait design and optimization, leg design and control, and mobile robot sensor incorporation.

![Payload Demonstration](Images/Brick_carrying.png)

# Setup Instructions
Building a MiniRhex requires access to a 3D printer and laser cutter. The links for off the shelf parts can be found below.
![MiniRHex Prototype](Images/mini1.jpg)

### Acquire Parts
The Parts List and Links to order can be found in [Parts List](https://github.com/robomechanics/MiniRHex/tree/master/Assembly).

### Assemble Robot
Assembly Instructions available at [Assembly Instructions](https://github.com/robomechanics/MiniRHex/tree/master/Assembly).

![Leg assembly close-up](Images/1.jpg)

### Install Software
1. Install OpenCM IDE from [http://www.robotis.us/opencmide/](http://www.robotis.us/opencmide/)
2. Clone primary repository at [https://github.com/robomechanics/MiniRHex.git](https://github.com/robomechanics/MiniRHex.git)

### Configure Servo ID's
1. In the openCM IDE, go to File>Examples>Dynamixel Easy>b_setID
2. Change the NEW_ID variable to the ID number according to the diagram below
3. Attach only the corresponding servo to the board (disconnect any other servos)
4. Upload the code
5. Repeat steps b-d for each servo

### Set Leg Zeros
1. Clone support repository at [https://github.com/nikolaif399/zero_finder.git](https://github.com/nikolaif399/zero_finder.git)
2. Manually rotate each leg to be as close to straight down as possible
3. Download zero_finder.ino to the OpenCM
4. Open the serial monitor in the IDE and copy the zeros (printing) to the zeros array in leg_info.cpp

![MiniRHex CAD](Images/RHex_Mini_IDS.JPG)

# Operating Instructions
1. Connect the MiniRHex to your computer via the Micro USB port
2. Open MiniRHex.ino in the OpenCM IDE
3. check that under "Tools", "Board" is set to ROBOTIS OpenCM9.04 and "Port" is set to the correct COM port (whichever COM port is added when MiniRhex is plugged in)
4. Ensure the motor zeros in leg_info.cpp are correct
5. Set desired gait parameters in gait_parameters.cpp
6. Click the download icon in the upper left corner of the OpenCM IDE (wait until it reports "Done Downloading")
7. Disconnect the Micro USB cable and connect the battery
8. Flip the power switch on the OpenCM board
9. Press the "RESET" button, make sure all motor LEDs are green
10. Press "USER SW" to execute the code!
11. Press the "RESET" button again to return to the standing behavior

![MiniRHex Running](Images/miniOnRock.bmp)

# Robot Specifications
![MiniRHex Specifications](Images/Spec_Chart.png)

# -----------------------------------------------

# Useful Links
### Parts List
The part list can be found at [Parts List](https://github.com/robomechanics/MiniRHex/blob/master/MiniRhexHardware.xlsx).
### MiniRhex Repository
The MiniRhex repository can be found at [MiniRhex Repository](https://github.com/robomechanics/MiniRHex.git).
### Cite MiniRHex
If referencing MiniRHex in a paper, please cite [this abstract](http://www.andrew.cmu.edu/user/amj1/papers/RSS2018ws_MiniRHex.pdf).
### Images
![MiniRHex Running](Images/miniOnRock.bmp)
### Video Links
Check out the Robomechanics Lab [YouTube Page](https://www.youtube.com/channel/UCKD78aZAsdB9-JTwrt6Q1KA) for videos of MiniRHex in action!





