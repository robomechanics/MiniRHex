# MiniRHex: An Open-Source Hexapod Robot

[Contact Info](https://www.cmu.edu/me/robomechanicslab/contact.html)

MiniRHex is a miniature-scale hexapod designed by the [Robomechanics Lab](https://www.cmu.edu/me/robomechanicslab/) based on the design of the cockroach-inspired [RHex](https://repository.upenn.edu/handle/20.500.14332/34172). Notable features include a 3D printed chassis and legs for low cost construction and an intuitive software package that allows for highly-customizable control over the robot’s behavior. MiniRHex is designed to be an educational and outreach tool enabling students to experiment with a fully functional walking robot at a much lower cost. The low price tag lets research groups maintain a fleet of machines, allowing each student more hands-on interaction with the hardware. Possible educational principles include gait design and optimization, leg design and control, and mobile robot sensor incorporation.

<img src="Images/assembledRobotFront.jpg" width="50%">

# Setup Instructions
Building a MiniRHex requires access to a 3D printer. The links for off the shelf parts can be found below.

## Acquire Parts
The Parts List and Links to order can be found in [Parts List](HardwareList).

## Assemble Robot
Assembly Instructions are available at [Assembly Instructions](Assembly).

## Install Software
1. Install the Arduino IDE from https://www.arduino.cc/en/software
2. Open the Arduino IDE and under "Tools" select "Manage Libraries..."
   - Type "DynamixelShield" into the search bar
   - Select "Install" for the DynamixelShield library
3. Under "Tools" hover over "Board" and select "Boards Manager..."
   - Type "Arduino SAMD Boards" into the search bar
   - Select "Install" for the Arduino SAMD Boards (32-bits ARM Cortex-M0+)
4. (Non-developers) Download the [MiniRHex repository](https://github.com/robomechanics/MiniRHex/archive/refs/heads/main.zip) and extract the downloaded zip file
5. (Developers) Clone the MiniRHex repository from https://github.com/robomechanics/MiniRHex.git

# Operating Instructions
## Upload Code
1. Connect the MiniRHex to your computer via the Micro USB port
2. Open MiniRHex.ino (located in the MiniRHex subfolder) in the Arduino IDE and check that under "Tools":
   - "Board" is set to "Arduino MKR WiFi 1010" (under "Arduino SAMD (32-bits ARM Cortex-M0+) Boards")
   - "Port" is set to the correct COM port, e.g. "COM# (Arduino MKR WiFi 1010)"
3. Upload code to the robot (the circular button near the top left with an arrow pointing to the right)
4. Insert a fully charged battery, fasten the velcro straps, connect the voltage monitor, and connect the battery cable
5. Open the Serial Monitor in the Arduino IDE (the circular button in the top right with a magnifying glass)
6. Type "w" into the text box and hit enter to start walking! ("q" to stop, "s" to reverse", "a" to turn left, "d" to turn right)
7. To modify the walking gait, go to the "gait_parameters.cpp" tab in the Arduino IDE and edit the parameters for each leg, then upload code again (see comments in the file for more details)
8. When finished, unplug the battery and store it in a fireproof container (never leave a battery in the robot!)

## Connect to Wi-Fi
1. After uploading code, the LED on the Arduino will turn green and the Serial monitor should initially print the following message:
> Starting WiFi network...  
> SSID: minirhex    
> Website: http://10.0.0.1
2. Connect to the wifi network listed after "SSID" from your phone or computer. The LED on the Arduino will turn blue and start flashing.
3. On your device, navigate to the provided website. Make sure to use http, not https.
4. Use the buttons or the indicated keys to wirelessly control the robot!

# Robot Specifications
|                       | MiniRHex              | X-RHex (2010)         |
|-----------------------|-----------------------|-----------------------|
| Mass                  | 0.40 kg               | 8.6 kg                |
| Carrying Capacity [^1]| 1.8-3 kg              | 5-10 kg               |
| Length                | 0.186 m               | 0.53 m                |
| Width                 | 0.100 m               | 0.39 m                |
| Leg Diameter          | 0.064 m               | 0.175 m               |
| Leg Spring Constant   | 0.3 N/mm              | 1.4-1.7 N/mm          |
| Leg Actuation         | Dynamixel XL330 Servo | Maxon Brushless Motor |
| Onboard Processor     | Arduino MKR WiFi 1010 | PC104, Intel Atom     |
| Single Unit Price     | <$300                 | ~$20,000              |

[^1]: Evaluated using legs with higher spring constant

<img src="Images/brickStanding.jpg" width="50%">

# Useful Links
### Parts List
The part list can be found at [Parts List](HardwareList).
### MiniRHex Repository
The MiniRHex repository can be found at [MiniRHex Repository](https://github.com/robomechanics/MiniRHex.git).
### Cite MiniRHex
If referencing MiniRHex in a paper, please cite [this abstract](http://www.andrew.cmu.edu/user/amj1/papers/RSS2018ws_MiniRHex.pdf).
Use [this BibTeX](/citation.txt) for citations:
> M. Barragan, N. Flowers, and A. M. Johnson. "MiniRHex: A Small, Open-source, Fully Programmable Walking Hexapod". In *Robotics: Science and Systems Workshop on ``Design and Control of Small Legged Robots''*, Pittsburgh, PA, June 2018.

### Images
See the [image gallery](Images) for more MiniRHex pictures.
        
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
* Catherine Pavlov (Ph.D ME '23)
* Paul Nadan (Ph.D RI)
* Aaron Johnson (Advisor)
