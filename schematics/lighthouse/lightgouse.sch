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
LIBS:lightgouse-cache
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
L rc522 U?
U 1 1 5718CF80
P 5250 2900
F 0 "U?" H 5550 2950 60  0000 C CNN
F 1 "rc522" H 5550 3100 60  0000 C CNN
F 2 "" H 5150 3100 60  0000 C CNN
F 3 "" H 5150 3100 60  0000 C CNN
	1    5250 2900
	1    0    0    -1  
$EndComp
$Comp
L ESP-201 U?
U 1 1 5718D2DA
P 3200 3150
F 0 "U?" H 3300 3300 60  0000 C CNN
F 1 "ESP-201" H 3200 3450 60  0000 C CNN
F 2 "" H 3450 3350 60  0000 C CNN
F 3 "" H 3450 3350 60  0000 C CNN
	1    3200 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 2550 4700 1950
Wire Wire Line
	4700 1950 2200 1950
Wire Wire Line
	2200 1950 2200 2750
Wire Wire Line
	2200 2750 2600 2750
Wire Wire Line
	3800 2750 4700 2750
Wire Wire Line
	3800 2950 4400 2950
Wire Wire Line
	3800 2850 4700 2850
Wire Wire Line
	4700 3900 4700 3250
Wire Wire Line
	2600 3900 4700 3900
Wire Wire Line
	2600 3900 2600 3650
Wire Wire Line
	4400 2950 4400 2650
Wire Wire Line
	4400 2650 4700 2650
Wire Wire Line
	4700 3050 3950 3050
Wire Wire Line
	3950 3050 3950 3550
Wire Wire Line
	3950 3550 3800 3550
$Comp
L +3V3 #PWR?
U 1 1 5718DC65
P 3050 1650
F 0 "#PWR?" H 3050 1500 50  0001 C CNN
F 1 "+3V3" H 3050 1790 50  0000 C CNN
F 2 "" H 3050 1650 50  0000 C CNN
F 3 "" H 3050 1650 50  0000 C CNN
	1    3050 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 1650 3050 2300
$Comp
L GND #PWR?
U 1 1 5718DCCC
P 3350 1650
F 0 "#PWR?" H 3350 1400 50  0001 C CNN
F 1 "GND" H 3350 1500 50  0000 C CNN
F 2 "" H 3350 1650 50  0000 C CNN
F 3 "" H 3350 1650 50  0000 C CNN
	1    3350 1650
	-1   0    0    1   
$EndComp
Wire Wire Line
	3350 1650 3350 2300
Wire Wire Line
	4750 3150 4200 3150
Wire Wire Line
	4200 3150 4200 3850
Wire Wire Line
	4200 3850 2500 3850
Wire Wire Line
	2500 3850 2500 3450
Wire Wire Line
	2500 3450 2600 3450
$Comp
L R 10k
U 1 1 5718DD6D
P 2850 1800
F 0 "10k" V 2930 1800 50  0000 C CNN
F 1 "R" V 2850 1800 50  0000 C CNN
F 2 "" V 2780 1800 50  0000 C CNN
F 3 "" H 2850 1800 50  0000 C CNN
	1    2850 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	3000 1800 3050 1800
Connection ~ 3050 1800
Wire Wire Line
	3800 3150 3900 3150
Wire Wire Line
	3900 3150 3900 1350
Wire Wire Line
	3900 1350 2650 1350
Wire Wire Line
	2650 1350 2650 1800
Wire Wire Line
	2650 1800 2700 1800
$Comp
L R 10k
U 1 1 5718DDEA
P 3550 1800
F 0 "10k" V 3630 1800 50  0000 C CNN
F 1 "R" V 3550 1800 50  0000 C CNN
F 2 "" V 3480 1800 50  0000 C CNN
F 3 "" H 3550 1800 50  0000 C CNN
	1    3550 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 1800 3350 1800
Connection ~ 3350 1800
Wire Wire Line
	3700 1800 3800 1800
Wire Wire Line
	3800 1800 3800 2650
$EndSCHEMATC
