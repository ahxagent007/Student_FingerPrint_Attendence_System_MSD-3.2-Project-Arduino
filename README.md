Introduction: In our country every school, collage, university, corporate office has an attendance calling system. For now, attendance calling for school, collage, university takes around 10-15 mins. Our system is a automated attendance system with finger print input system that will make the attendance process lot more faster and easier in our county. We are looking forward to make a industrial level device that can be used anywhere in any environment.


Components: 

Hardware Components: 

•	Arduino UNO REV3 – used as a microcontroller.
•	20x4 LCD – used to see all data and manage stuffs
•	R305 Fingerprint module – use to input fingerprints 
•	ESP8266 Wi-Fi Module – gives microcontroller access to Wi-Fi network.
In our project it is used to connect with student’s mobiles and capture MAC address generated in that device.
•	Mini circuit Boards – use to solve the common connections / extra connection between Arduino & other hardware components.
•	Male/Female Jumper Wires – use to give connection between two points/ports.
•	Resistances – use with the LCD.  
•	Keypad – use to make the controller

Software Components: 

•	Arduino IDE – for burning code on Arduino UNO REV3.
•	Proteus –to design the hardware component model.




Features: 

•	The device will be portable.
•	Visualization of student attendance with the LCD screen
•	Basically, initially the device will get fingerprint from the students for registration. 
•	Then every time a student enters a class, he/she will put his/her finger to give the attendance.
•	Our device will receive the fingerprint and match it with the registered fingerprints and give attendance of that class to the student.
•	A teacher is the main operator of this device.
•	Teacher will start the attendance count by giving his course id after that student can enter their finger to get the attendance in a very fast way.
•	Our device is anti-proxy system, there is near zero percent chance that in a class 2 people will have the same finger print. So, no one can give any proxy.
•	Our UI will be very simple.



Working Principle: 

•	First there will be a main menu. Options are given below-
•	Take Attendance
•	Teacher will enter course number to start the attendance system
•	Attendance system will auto magically wait for each student’s finger  
•	After getting attendance teacher will stop the system
•	Add Students
•	For adding student, first need to enter Student id then system will ask for their finger.
•	After giving the fingerprint system will register the student
•	See Attendance
•	Here Teacher can have a short look on the presented ID’s 
•	Also, teacher can clear the attendance if he wants to.
•	Send data to server
•	Here System will send all the presented data to the server.
•	Teacher can see the data from the server after this step
