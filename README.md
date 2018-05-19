# MiniRHex: An Open-source Walking Hexapod

![MiniRHex Prototype](Images/mini1.png)
This page demonstrates the design and capabilities of MiniRHex, a $200 hardware platform for robotics research and outreach. In addition to educational goals, the platform provides us with an opportunity to study the scaling of locomotion principles. By modifying the control strategies currently utilized in RHex, we’ve been able to develop an affordable and easily-constructed version that still offers many of the same capabilities as it’s full-scale cousin. Some features include a rugged frame and stable stance that allow it to traverse moderate to rough terrain and a highly configurable software package that can be modified to add new behaviors and abilities. MiniRHex is designed to lower the entry barrier to dynamic gait research and allow researchers to test novel algorithms on a physical machine without the risk or expense of a full-scale platform.

## Setup instructions

### Hardware
Assembly Instructions available in git repository under Assembly_Instructions.pdf
![MiniRHex Prototype](Images/RHex_Mini.jpg)

### Software
1. Install OpenCM IDE from http://www.robotis.us/opencmide/
2. Clone primary repository at https://github.com/robomechanics/MiniRHex.git
3. Clone support repository at https://github.com/nikolaif399/zero_finder.git
4. Open OpenCM IDE, open calculate_zeros and run
5. Pull up serial monitor, move legs to face directly downward and copy zeros over to array in leg_info.cpp
6. Open MiniRHex.ino, attach micro-usb to robot and download code to robot
7. Use user button on robot to toggle through gaits (stand, forward, left, reverse, right, pronk)

