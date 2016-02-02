# Capstone Shared # 

##### Goals of this project 

The ultimate purpose of this repository is to define a common test format, so each team can swap out their correlation module, test server module, and CDTI module with another team. This goal should be realized by the end of capstone. However, it's not a requirement of the vertical prototype.  

##### Ground Rules
 You are free to make changes on a fork of this project and make local changes, but please do not commit to master without notifying and discussing your changes with the teams. 


##### Description of Connection
The protocols in this repository should be used over a TCP socket. When sending data, the following standard should be used:

```
[ length | Google protocol Buffer ]
  4 Bytes       n Bytes
  
```
  
When reading from a TCP socket, read the first four bites to recieve the length (in bytes) of the Google protobuffer. Buffer length should be consistant for most of the RADAR, TCAS, ADS-B, and Ownship data, but will not be consistant for the CDTI display.
  
  The Following Protocols are specified in the respositry:
* TCAS: (tcas.proto)
* ADS-B: (adsb.proto)
* RADAR: (radar.proto)
* Ownship: (ownshp.proto)
* CDTI: (cdti.proto)
  
 

### How do I get set up? ###

* Summary of set up
* Configuration
* Dependencies
* Database configuration
* How to run tests
* Deployment instructions

### Contribution guidelines ###

* Writing tests
* Code review
* Other guidelines

### Who do I talk to? ###

* Repo owner or admin
* Other community or team contact
