EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:bugs
LIBS:espDebug-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ESP-201 U2
U 1 1 571A7E1E
P 3950 2850
F 0 "U2" H 4350 3550 60  0000 C CNN
F 1 "ESP-201" H 3450 3550 60  0000 C CNN
F 2 "bugs:ESP201" H 4200 3050 60  0001 C CNN
F 3 "" H 4200 3050 60  0000 C CNN
	1    3950 2850
	1    0    0    -1  
$EndComp
$Comp
L ESP8266 U3
U 1 1 571A7E76
P 5250 2700
F 0 "U3" H 5500 3150 60  0000 C CNN
F 1 "ESP8266" H 5250 2700 60  0000 C CNN
F 2 "bugs:esp8266" H 5300 2700 60  0001 C CNN
F 3 "" H 5300 2700 60  0000 C CNN
	1    5250 2700
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P2
U 1 1 571A7F11
P 5150 450
F 0 "P2" H 5150 600 50  0000 C CNN
F 1 "3V3" V 5250 450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 5150 450 50  0001 C CNN
F 3 "" H 5150 450 50  0000 C CNN
	1    5150 450 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X02 P3
U 1 1 571A7F86
P 3950 800
F 0 "P3" H 3950 950 50  0000 C CNN
F 1 "RX/TX" V 4050 800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 3950 800 50  0001 C CNN
F 3 "" H 3950 800 50  0000 C CNN
	1    3950 800 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X02 P1
U 1 1 571A7FC6
P 4350 -150
F 0 "P1" H 4350 0   50  0000 C CNN
F 1 "RAW" V 4450 -150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 4350 -150 50  0001 C CNN
F 3 "" H 4350 -150 50  0000 C CNN
	1    4350 -150
	-1   0    0    1   
$EndComp
$Comp
L SPX2920T-3.3 U1
U 1 1 571A8159
P 5100 -50
F 0 "U1" H 5100 200 50  0000 C CNN
F 1 "SPX2920T-3.3" H 5100 150 50  0000 C CNN
F 2 "Power_Integrations:TO-220" H 5100 50  50  0000 C CIN
F 3 "" H 5100 -50 50  0000 C CNN
	1    5100 -50 
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 571A8389
P 4650 1600
F 0 "R3" V 4730 1600 50  0000 C CNN
F 1 "10k" V 4650 1600 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" V 4580 1600 50  0001 C CNN
F 3 "" H 4650 1600 50  0000 C CNN
	1    4650 1600
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 571A84A6
P 4850 1600
F 0 "R4" V 4930 1600 50  0000 C CNN
F 1 "10k" V 4850 1600 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" V 4780 1600 50  0001 C CNN
F 3 "" H 4850 1600 50  0000 C CNN
	1    4850 1600
	-1   0    0    1   
$EndComp
$Comp
L R R2
U 1 1 571A85F0
P 4550 2150
F 0 "R2" V 4630 2150 50  0000 C CNN
F 1 "10k" V 4550 2150 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" V 4480 2150 50  0001 C CNN
F 3 "" H 4550 2150 50  0000 C CNN
	1    4550 2150
	-1   0    0    1   
$EndComp
$Comp
L R R1
U 1 1 571A8628
P 6100 3500
F 0 "R1" V 6180 3500 50  0000 C CNN
F 1 "1k" V 6100 3500 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" V 6030 3500 50  0001 C CNN
F 3 "" H 6100 3500 50  0000 C CNN
	1    6100 3500
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 571A86F8
P 6100 3100
F 0 "D1" H 6100 3200 50  0000 C CNN
F 1 "LED" H 6100 3000 50  0000 C CNN
F 2 "LEDs:LED-3MM" H 6100 3100 50  0001 C CNN
F 3 "" H 6100 3100 50  0000 C CNN
	1    6100 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	6100 3350 6100 3300
Wire Wire Line
	4550 -100 4700 -100
Wire Wire Line
	4550 -200 4650 -200
Wire Wire Line
	4650 -200 4650 200 
Wire Wire Line
	4650 200  5350 200 
Wire Wire Line
	5200 650  5350 650 
Wire Wire Line
	5350 650  5350 200 
Connection ~ 5100 200 
Wire Wire Line
	5500 -100 5500 300 
Wire Wire Line
	5500 300  4850 300 
Wire Wire Line
	4850 300  4850 650 
Wire Wire Line
	4850 650  5100 650 
Wire Wire Line
	3800 1400 5100 1400
Wire Wire Line
	4650 1400 4650 1450
Wire Wire Line
	4850 1450 4850 1400
Connection ~ 4850 1400
Wire Wire Line
	4650 1750 4650 2950
Wire Wire Line
	5200 2100 5200 1950
Wire Wire Line
	5200 1950 4850 1950
Connection ~ 4850 1950
Wire Wire Line
	5300 2100 5300 1850
Wire Wire Line
	5300 1850 4650 1850
Connection ~ 4650 1850
Connection ~ 5100 1400
Wire Wire Line
	3800 1400 3800 2000
Connection ~ 4650 1400
Wire Wire Line
	4550 2350 4550 2300
Wire Wire Line
	4550 2000 4100 2000
Wire Wire Line
	4100 2000 4100 1350
Wire Wire Line
	4100 1350 5600 1350
Connection ~ 5200 1350
Wire Wire Line
	5600 1350 5600 3300
Wire Wire Line
	5600 3300 5400 3300
Wire Wire Line
	5200 650  5200 1350
Wire Wire Line
	3900 2000 3900 1000
Wire Wire Line
	4000 1000 4000 2000
Wire Wire Line
	5100 650  5100 2100
Wire Wire Line
	5400 2100 5400 1100
Wire Wire Line
	5400 1100 4000 1100
Connection ~ 4000 1100
Wire Wire Line
	5100 3300 5100 3550
Wire Wire Line
	5100 3550 5750 3550
Wire Wire Line
	5750 3550 5750 1050
Wire Wire Line
	5750 1050 3900 1050
Connection ~ 3900 1050
Wire Wire Line
	3350 2450 3150 2450
Wire Wire Line
	3150 2450 3150 3700
Wire Wire Line
	3150 3700 6100 3700
Wire Wire Line
	6100 3700 6100 3650
Wire Wire Line
	5600 2600 6100 2600
Wire Wire Line
	6100 2600 6100 2900
Connection ~ 5600 2600
Wire Wire Line
	5300 3700 5300 3300
Connection ~ 5300 3700
Wire Wire Line
	3350 2350 3050 2350
Wire Wire Line
	3050 2350 3050 3850
Wire Wire Line
	5200 3300 5200 3850
Connection ~ 5200 3850
Wire Wire Line
	6550 3850 6550 1800
Connection ~ 6550 3850
Wire Wire Line
	3050 3850 6550 3850
$Comp
L button U4
U 1 1 571AAEA1
P 6250 1500
F 0 "U4" H 6300 1500 60  0000 C CNN
F 1 "button" H 6300 1500 60  0000 C CNN
F 2 "bugs:button" H 6300 1500 60  0001 C CNN
F 3 "" H 6300 1500 60  0000 C CNN
	1    6250 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 1800 6350 1800
Wire Wire Line
	6250 1800 6250 1900
Wire Wire Line
	6250 1900 5600 1900
Connection ~ 5600 1900
Wire Wire Line
	4650 2950 4550 2950
Wire Wire Line
	4850 2850 4550 2850
Wire Wire Line
	4850 1750 4850 2850
$EndSCHEMATC
