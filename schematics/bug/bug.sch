EESchema Schematic File Version 2
LIBS:bug-rescue
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
LIBS:bug-cache
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
L CONN_01X09 P1
U 1 1 56F1A493
P 2900 3750
F 0 "P1" H 2900 4250 50  0000 C CNN
F 1 "CONN_01X09" V 3000 3750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x09" H 2900 3750 50  0001 C CNN
F 3 "" H 2900 3750 50  0000 C CNN
	1    2900 3750
	-1   0    0    1   
$EndComp
$Comp
L uln2803A U1
U 1 1 56F1AA0E
P 3700 3750
F 0 "U1" H 4000 4250 60  0000 C CNN
F 1 "uln2803A" H 3700 4300 60  0000 C CNN
F 2 "Housings_DIP:DIP-18_W7.62mm" H 3900 3900 60  0001 C CNN
F 3 "" H 3900 3900 60  0000 C CNN
	1    3700 3750
	-1   0    0    1   
$EndComp
$Comp
L R R2
U 1 1 56F1AE1A
P 6900 3350
F 0 "R2" V 6800 3350 50  0000 C CNN
F 1 "10k" V 6900 3350 50  0000 C CNN
F 2 "w_pth_resistors:rc05_vert" V 6830 3350 50  0001 C CNN
F 3 "" H 6900 3350 50  0000 C CNN
	1    6900 3350
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 56F1AE8B
P 7000 3350
F 0 "R3" V 7080 3350 50  0000 C CNN
F 1 "10k" V 7000 3350 50  0000 C CNN
F 2 "w_pth_resistors:rc05_vert" V 6930 3350 50  0001 C CNN
F 3 "" H 7000 3350 50  0000 C CNN
	1    7000 3350
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 56F1AEB7
P 7100 5150
F 0 "R4" V 7180 5150 50  0000 C CNN
F 1 "R" V 7100 5150 50  0000 C CNN
F 2 "w_pth_resistors:rc05_vert" V 7030 5150 50  0001 C CNN
F 3 "" H 7100 5150 50  0000 C CNN
	1    7100 5150
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 56F1AF1D
P 6800 5150
F 0 "R1" V 6880 5150 50  0000 C CNN
F 1 "R" V 6800 5150 50  0000 C CNN
F 2 "w_pth_resistors:rc05_vert" V 6730 5150 50  0001 C CNN
F 3 "" H 6800 5150 50  0000 C CNN
	1    6800 5150
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 56F1AFA5
P 6800 5550
F 0 "D1" H 6800 5650 50  0000 C CNN
F 1 "LED" H 6800 5450 50  0000 C CNN
F 2 "LEDs:LED-5MM" H 6800 5550 50  0001 C CNN
F 3 "" H 6800 5550 50  0000 C CNN
	1    6800 5550
	0    -1   -1   0   
$EndComp
$Comp
L LED D2
U 1 1 56F1B03A
P 7100 5550
F 0 "D2" H 7100 5650 50  0000 C CNN
F 1 "LED" H 7100 5450 50  0000 C CNN
F 2 "LEDs:LED-5MM" H 7100 5550 50  0001 C CNN
F 3 "" H 7100 5550 50  0000 C CNN
	1    7100 5550
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X06 P3
U 1 1 56F1BCB1
P 6000 3500
F 0 "P3" H 6000 3850 50  0000 C CNN
F 1 "CONN_01X06" V 6100 3500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06" H 6000 3500 50  0001 C CNN
F 3 "" H 6000 3500 50  0000 C CNN
	1    6000 3500
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P2
U 1 1 56F1C32B
P 5750 3000
F 0 "P2" H 5750 3150 50  0000 C CNN
F 1 "CONN_01X02" V 5850 3000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 5750 3000 50  0001 C CNN
F 3 "" H 5750 3000 50  0000 C CNN
	1    5750 3000
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P4
U 1 1 56F1CB48
P 4800 1600
F 0 "P4" H 4800 1750 50  0000 C CNN
F 1 "CONN_01X02" V 4900 1600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 4800 1600 50  0001 C CNN
F 3 "" H 4800 1600 50  0000 C CNN
	1    4800 1600
	-1   0    0    1   
$EndComp
$Comp
L SPX2920U-3.3 U3
U 1 1 56F1AC9B
P 6700 2450
F 0 "U3" H 6700 2700 50  0000 C CNN
F 1 "SPX2920U-3.3" H 6700 2650 50  0000 C CNN
F 2 "Power_Integrations:TO-220" H 6700 2550 50  0000 C CIN
F 3 "" H 6700 2450 50  0000 C CNN
	1    6700 2450
	1    0    0    -1  
$EndComp
$Comp
L CP C1
U 1 1 56F1E79A
P 6950 2750
F 0 "C1" H 6975 2850 50  0000 L CNN
F 1 "CP" H 6975 2650 50  0000 L CNN
F 2 "Discret:CPR10X16" H 6988 2600 50  0001 C CNN
F 3 "" H 6950 2750 50  0000 C CNN
	1    6950 2750
	0    1    1    0   
$EndComp
$Comp
L ESP8266 U4
U 1 1 56F1BA48
P 6950 4250
F 0 "U4" H 7200 4700 60  0000 C CNN
F 1 "ESP8266" H 6950 4250 60  0000 C CNN
F 2 "bugs:ESP8266" H 7000 4250 60  0001 C CNN
F 3 "" H 7000 4250 60  0000 C CNN
	1    6950 4250
	1    0    0    -1  
$EndComp
$Comp
L Arduino_Mini U2
U 1 1 56F1A6A1
P 4850 3600
F 0 "U2" H 5200 4450 60  0000 C CNN
F 1 "Arduino_Mini" H 4850 4450 60  0000 C CNN
F 2 "bugs:arduino_mini_pro" H 6000 4450 60  0001 C CNN
F 3 "" H 6000 4450 60  0000 C CNN
	1    4850 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 3650 7100 3650
Wire Wire Line
	4300 3850 4150 3850
Wire Wire Line
	4150 3950 4300 3950
Wire Wire Line
	4300 4150 4150 4150
Connection ~ 6900 3150
Wire Wire Line
	6750 3650 6800 3650
Wire Wire Line
	6750 3150 6750 3650
Connection ~ 7000 3150
Wire Wire Line
	6900 3150 6900 3200
Wire Wire Line
	6750 3150 7000 3150
Connection ~ 7100 2750
Wire Wire Line
	7000 2950 7000 3200
Wire Wire Line
	7100 2950 7000 2950
Wire Wire Line
	7100 2400 7100 2950
Wire Wire Line
	6400 2750 6800 2750
Wire Wire Line
	6700 2700 6700 3100
Wire Wire Line
	6400 2550 6400 2750
Wire Wire Line
	5750 1550 5750 2550
Connection ~ 5650 2400
Wire Wire Line
	5400 2400 5400 3050
Wire Wire Line
	5400 2400 6300 2400
Wire Wire Line
	5650 1650 5650 2400
Wire Wire Line
	5500 3150 5400 3150
Wire Wire Line
	5550 2950 5500 2950
Wire Wire Line
	5550 3350 5400 3350
Wire Wire Line
	5550 3050 5550 3350
Wire Wire Line
	5650 3250 5800 3250
Wire Wire Line
	5650 4700 5650 3250
Wire Wire Line
	5700 3350 5700 4800
Wire Wire Line
	5800 3350 5700 3350
Wire Wire Line
	5700 4800 4700 4800
Wire Wire Line
	4700 4800 4700 4600
Wire Wire Line
	4800 4700 5650 4700
Wire Wire Line
	4800 4600 4800 4700
Wire Wire Line
	5400 3450 5800 3450
Wire Wire Line
	5400 3550 5800 3550
Wire Wire Line
	5400 3650 5800 3650
Wire Wire Line
	5400 3750 5800 3750
Wire Wire Line
	3100 3350 3250 3350
Wire Wire Line
	3100 3450 3250 3450
Wire Wire Line
	3250 3550 3100 3550
Wire Wire Line
	3100 3650 3250 3650
Wire Wire Line
	3250 3750 3100 3750
Wire Wire Line
	3100 3850 3250 3850
Wire Wire Line
	3250 3950 3100 3950
Wire Wire Line
	3100 4050 3250 4050
Wire Wire Line
	3250 4150 3100 4150
Wire Wire Line
	4300 4050 4150 4050
Wire Wire Line
	4150 3750 4300 3750
Wire Wire Line
	4300 3650 4150 3650
Wire Wire Line
	4150 3550 4300 3550
Wire Wire Line
	4300 3450 4150 3450
Wire Wire Line
	7250 5750 6800 5750
Wire Wire Line
	6900 3500 6900 3650
Wire Wire Line
	7000 3500 7000 3650
Connection ~ 6800 5750
Connection ~ 7100 5750
Wire Wire Line
	7250 4850 7250 5750
Wire Wire Line
	7100 4850 7350 4850
Wire Wire Line
	6800 5300 6800 5350
Wire Wire Line
	7100 5350 7100 5300
Wire Wire Line
	6900 5000 6800 5000
Wire Wire Line
	6900 4850 6900 5000
Wire Wire Line
	7000 5000 7000 4850
Wire Wire Line
	7100 5000 7000 5000
Wire Wire Line
	7350 4850 7350 3100
Wire Wire Line
	7350 3100 6700 3100
Connection ~ 6700 2750
Connection ~ 7250 4850
Wire Wire Line
	3200 2050 5650 2050
Connection ~ 5650 2050
Wire Wire Line
	3200 2050 3200 3350
Connection ~ 3200 3350
Wire Wire Line
	4150 3350 4300 3350
Wire Wire Line
	7250 3650 7250 2150
Wire Wire Line
	7250 2150 4250 2150
Wire Wire Line
	4250 2150 4250 3150
Wire Wire Line
	4250 3150 4300 3150
Wire Wire Line
	4300 3050 4300 2700
Wire Wire Line
	4300 2700 6300 2700
Wire Wire Line
	6300 2700 6300 4850
Wire Wire Line
	6300 4850 6800 4850
Wire Wire Line
	5000 1550 5750 1550
$Comp
L button U5
U 1 1 56F2F512
P 5350 1150
F 0 "U5" H 5400 1150 60  0000 C CNN
F 1 "button" H 5400 1150 60  0000 C CNN
F 2 "bugs:button" H 5400 1150 60  0001 C CNN
F 3 "" H 5400 1150 60  0000 C CNN
	1    5350 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 1650 5350 1650
Wire Wire Line
	5350 1650 5350 1450
Wire Wire Line
	5100 1650 5100 700 
Wire Wire Line
	5100 700  5450 700 
Wire Wire Line
	5450 700  5450 850 
Wire Wire Line
	5100 1650 5000 1650
Wire Wire Line
	5500 2950 5500 3150
Wire Wire Line
	4200 2550 6400 2550
Wire Wire Line
	4200 3350 4200 2550
Connection ~ 5750 2550
Connection ~ 4200 3350
$EndSCHEMATC