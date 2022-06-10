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
1. Install Arduino software
2. Install Robotis Arduino libraries
3. Upload code to robot

### Configure Servo ID's
1. 


![MiniRHex](Images/miniOnStumpScaled.jpg)


# Operating Instructions
1. Connect the MiniRHex to your computer via the Micro USB port
2. Open MiniRHex.ino in the OpenCM IDE and check that under "Tools":
   - "Board" is set to XX
   - "Port" is set to the correct COM port (whichever COM port is added when MiniRHex is plugged in)
3. XXXEnsure the motor zeros in leg_info.cpp are correct
4. Set desired gait parameters in gait_parameters.cpp
5. Click the download icon in the upper left corner of the OpenCM IDE (wait until it reports "Done Downloading")
6. Disconnect the Micro USB cable and connect the battery
7. 
8.
9. 
10. Press the "RESET" button again to return to the standing behavior

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





