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
L CONN_01X03 P1
U 1 1 574172D3
P 2150 3800
F 0 "P1" H 2150 4000 50  0000 C CNN
F 1 "mass_start" V 2250 3800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 2150 3800 50  0001 C CNN
F 3 "" H 2150 3800 50  0000 C CNN
	1    2150 3800
	-1   0    0    1   
$EndComp
$Comp
L button U1
U 1 1 57417361
P 3050 2850
F 0 "U1" V 3250 2800 60  0000 C CNN
F 1 "STOP" V 2850 2750 60  0000 C CNN
F 2 "bugs:button" H 3100 2850 60  0001 C CNN
F 3 "" H 3100 2850 60  0000 C CNN
	1    3050 2850
	1    0    0    -1  
$EndComp
$Comp
L button U2
U 1 1 574173D9
P 3050 4400
F 0 "U2" V 3250 4350 60  0000 C CNN
F 1 "START" V 2850 4300 60  0000 C CNN
F 2 "bugs:button" H 3100 4400 60  0001 C CNN
F 3 "" H 3100 4400 60  0000 C CNN
	1    3050 4400
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 P2
U 1 1 57417557
P 3650 3650
F 0 "P2" H 3650 3900 50  0000 C CNN
F 1 "VCC/GND/Start/Stop" V 3750 3650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 3650 3650 50  0001 C CNN
F 3 "" H 3650 3650 50  0000 C CNN
	1    3650 3650
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 574175AE
P 2700 3700
F 0 "R1" V 2780 3700 50  0000 C CNN
F 1 "10k" V 2700 3700 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" V 2630 3700 50  0001 C CNN
F 3 "" H 2700 3700 50  0000 C CNN
	1    2700 3700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2350 3800 3450 3800
Wire Wire Line
	2350 3700 2550 3700
Wire Wire Line
	2500 3900 2350 3900
Connection ~ 2500 3700
Wire Wire Line
	2500 3600 2500 3900
Wire Wire Line
	2850 3700 3450 3700
Wire Wire Line
	2500 3600 3450 3600
Wire Wire Line
	3150 3300 3150 4100
Connection ~ 3150 3800
Wire Wire Line
	2950 4100 2950 3600
Connection ~ 2950 3600
Wire Wire Line
	2950 3300 2950 3500
Wire Wire Line
	2950 3500 3450 3500
$Comp
L R R2
U 1 1 5741799C
P 2750 3350
F 0 "R2" V 2830 3350 50  0000 C CNN
F 1 "10k" V 2750 3350 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" V 2680 3350 50  0001 C CNN
F 3 "" H 2750 3350 50  0000 C CNN
	1    2750 3350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2900 3350 2950 3350
Connection ~ 2950 3350
Wire Wire Line
	2600 3350 2600 3550
Wire Wire Line
	2600 3550 2900 3550
Wire Wire Line
	2900 3550 2900 3700
Connection ~ 2900 3700
$Comp
L CONN_01X04 P3
U 1 1 57417A47
P 3750 2250
F 0 "P3" H 3750 2500 50  0000 C CNN
F 1 "LED" V 3850 2250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 3750 2250 50  0001 C CNN
F 3 "" H 3750 2250 50  0000 C CNN
	1    3750 2250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3400 3800 3400 4200
Wire Wire Line
	3400 4200 3900 4200
Wire Wire Line
	3900 4200 3900 2800
Connection ~ 3400 3800
$Comp
L R R4
U 1 1 57417B40
P 3900 2650
F 0 "R4" V 3980 2650 50  0000 C CNN
F 1 "200" V 3900 2650 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" V 3830 2650 50  0001 C CNN
F 3 "" H 3900 2650 50  0000 C CNN
	1    3900 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 2500 3900 2450
$Comp
L R R3
U 1 1 57417C07
P 3700 2650
F 0 "R3" V 3780 2650 50  0000 C CNN
F 1 "200" V 3700 2650 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" V 3630 2650 50  0001 C CNN
F 3 "" H 3700 2650 50  0000 C CNN
	1    3700 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 2800 3700 2900
Wire Wire Line
	3700 2900 3900 2900
Connection ~ 3900 2900
Wire Wire Line
	3700 2500 3700 2450
Wire Wire Line
	3800 2850 3800 2450
Wire Wire Line
	3400 2850 3800 2850
Wire Wire Line
	3600 2850 3600 2450
Wire Wire Line
	3400 2850 3400 3700
Connection ~ 3400 3700
Connection ~ 3600 2850
$EndSCHEMATC
