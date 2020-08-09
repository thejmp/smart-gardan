# Smart Gardan
[![version](https://img.shields.io/badge/version-0.1-yellow.svg)](https://semver.org)
[![GPLv3 license](https://img.shields.io/badge/License-GPLv3-blue.svg)](http://perso.crans.org/besson/LICENSE.html)
## This project as been moved for continued development [Version 0.2](https://github.com/promise333-smart-garden) 

This is the Smart Garden Project for Embedded Systems class

## Introduction
Many people have trouble keeping plants because of the pain of remembering to water them. This makes most people either chose to not keep plants or keep forgetting to water them and constantly having to replace them. This dilemma led us to want to explore the possibility of making an automated mentoring and watering system that allows you the piece of mind that your plants are healthy and happy so you can enjoy them without the unneeded stress of remembering to water your plants. 

## Objectives

* Develop a system to track soil water content
* Check to see if a plant is over watered or underwatered
* Integrate a pump fed watering structure to water plants
* Connect to the internet to supply information to the user using an MQTT server
* Integrate with smart assistants like Google Assistant and Amazon Alexa to allow easer access to the information and watering schedule
* Make an intuitive and easy to use setup page to allow the user to connect to their Wi-Fi.

## Materials

* Water pump
* Solenoids
* Power adapter
* Glass water tank
* Soil moisture sensors
* Aquarium tubing
* Float sensor
* ESP 32
* Power Relay

## Code
The webhooks folder contains the node.js project to pull data from adafurit.io and server it to Google Assistant and Amazon Alexa

The final_code.ino contains the code for the esp32. You will need to install its includeed librarys as well as your mqtt server details

## Checkpoints
- [x] Get the soil moisture sensors working and communicating with ESP 32
- [x] Get water system integrated with ESP 32 and working
- [x] Get the water system working with the moisture sensors
- [x] Get float sensor working with led indicator
- [x] Send soil moisture and watering to MQTT(Adafruit IO)
- [x] Develop AP, DHCP, DNS, captive portal and Configuration page to setup device
- [x] Develop webhooks to get data from MQTT server and to send data to Google Assistant and Amazon Alexa 
- [x] Use dialog flow to develop Google Assistant app
- [x] Use Amazon API to develop Amazon Alexa skill

## Future Objectives
- [ ] Design a custom PCB to incorporate all electronic parts in to one contained board.
- [ ] Make a 3D printed housing for solenoids.
- [ ] Make an enclosure and connecters for PCB and plugs
- [ ] Expand watering system to hard tube to make a larger irrigation system.
