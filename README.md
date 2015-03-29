# Sonar Plotter
Provides radar-like visual representation of real time x,y coordinates sent via serial port.

**Objective:** Create a web app that provides an intuitive visualization of what an ultrasonic ping sensor "sees". 

**Project Details:** An Arudio Uno board controlling a hobby servo with a ping sensor attached is set to sweep 180 degrees of a given area back and forth. At each "tick" of the servo, the x and y coordinates of the nearest object sensed is calculated and output through the serial port. Using websockets, node.js, and the d3.js graphing library, a node web app will listen to incoming serial data and update a modified scatter plot in near real time to show a radar-like visual of what objects exist on the 2d plane being swept by the ultrasonic ping (short range sonar) sensor. Essentially you should see an outline of the room and objects being scanned within the sweep area. Speed and/or data accuracy adjustments should be available.

**Links:** JSFiddle with example data from an actual serial data stream for client's web app at [http://jsfiddle.net/lukeblechl/5D5eD/60/](http://jsfiddle.net/lukeblechl/5D5eD/60/).
