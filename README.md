# MiniRHex: An Open-source Walking Hexapod
Contact: nflowers@andrew.cmu.edu
![MiniRHex Prototype](Images/mini1.jpg)

MiniRHex is a miniature scale hexapod heavily based on the design of RHex. Notable features include a laser-cut frame and 3D printed legs for low cost construction and an intuitive software package that allows for highly-customizable control over the robot’s behavior. MiniRHex was designed to be an educational and outreach tool to allow students to experiment with a fully functional walking robot at a much lower cost. The low price tag lets research groups maintain a fleet of machines, allowing each student more hands-on interaction with the hardware. Possible educational principles include gait design and optimization, leg design and control, and mobile robot sensor incorporation.

![Payload Demonstration](Images/Brick_carrying.png)
## Setup Instructions

### Hardware
The Parts List and Links to order can be found in https://github.com/robomechanics/MiniRHex/blob/master/MiniRhexHardware.xlsx

Assembly Instructions available at https://github.com/robomechanics/MiniRHex/tree/master/Assembly
![Leg assembly close-up](Images/1.jpg)

### Software
1. Install OpenCM IDE from http://www.robotis.us/opencmide/
2. Clone primary repository at https://github.com/robomechanics/MiniRHex.git

### Leg Configuration
Several variables will have to be configured for each leg before we can upload code from the primary repository. First, we need to match the ID of each dynamixel servo to the diagram shown below. ID's can be changed using the OpenCM board and Robotis Example scripts. In the openCM IDE, go to File>Examples>Dynamixel Easy>b_setID. This script will let you set the ID number for a single servo attached through the openCM board. Change the NEW_ID variable to the ID number you are wanting to set, attach a single servo to the board and upload the code. Repeat this process for each servo. Next we need to set the servo zeros of each dynamixel. Due to slighly mechanical differences and leg mounting imperfections, each leg's zero position may not naturally point straight down. To fix, Clone support repository at https://github.com/nikolaif399/zero_finder.git and run zero_finder.ino on the OpenCM. Manually rotate each leg to be as close to straight down as possible. Open the serial monitor in the IDE and copy the zeros (printing) to the zeros array in leg_info.cpp.

![MiniRHex CAD](Images/RHex_Mini_IDS.JPG)

### Specifications
![MiniRHex Specifications](Images/Spec_Chart.png)





