EESchema Schematic File Version 4
LIBS:knuth-gateway-cache
EELAYER 29 0
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
L knuth-gateway-rescue:Conn_01x12_Female-Connector J1
U 1 1 5D3A6009
P 6800 4400
F 0 "J1" H 6600 5050 50  0000 L CNN
F 1 "FeatherLora1" V 6150 4050 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x12_P2.54mm_Vertical" H 6800 4400 50  0001 C CNN
F 3 "~" H 6800 4400 50  0001 C CNN
	1    6800 4400
	-1   0    0    1   
$EndComp
$Comp
L knuth-gateway-rescue:Conn_01x16_Female-Connector J2
U 1 1 5D3A613C
P 5650 4200
F 0 "J2" H 5500 5050 50  0000 L CNN
F 1 "FeatherLora2" V 5800 3950 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x16_P2.54mm_Vertical" H 5650 4200 50  0001 C CNN
F 3 "~" H 5650 4200 50  0001 C CNN
	1    5650 4200
	-1   0    0    1   
$EndComp
Text GLabel 7000 4900 2    50   Input ~ 0
VBAT
Text GLabel 7000 4800 2    50   Input ~ 0
EN
Text GLabel 7000 4700 2    50   Input ~ 0
VBUS
Text GLabel 7000 4600 2    50   Input ~ 0
D13
Text GLabel 7000 4500 2    50   Input ~ 0
D12
Text GLabel 7000 4400 2    50   Input ~ 0
D11
Text GLabel 7000 4300 2    50   Input ~ 0
D10
Text GLabel 7000 4200 2    50   Input ~ 0
D9
Text GLabel 7000 4100 2    50   Input ~ 0
D6
Text GLabel 7000 4000 2    50   Input ~ 0
D5
Text GLabel 7000 3900 2    50   Input ~ 0
SCL
Text GLabel 7000 3800 2    50   Input ~ 0
SDA
Text GLabel 5850 4900 2    50   Input ~ 0
RESET
Wire Wire Line
	5850 4800 6200 4800
Wire Wire Line
	6200 4800 6200 5000
$Comp
L knuth-gateway-rescue:+3V3-power #PWR0101
U 1 1 5D3A928A
P 6200 5000
F 0 "#PWR0101" H 6200 4850 50  0001 C CNN
F 1 "+3V3" H 6215 5173 50  0000 C CNN
F 2 "" H 6200 5000 50  0001 C CNN
F 3 "" H 6200 5000 50  0001 C CNN
	1    6200 5000
	-1   0    0    1   
$EndComp
Text GLabel 5850 4700 2    50   Input ~ 0
AREF
Wire Wire Line
	5850 4600 6200 4600
Wire Wire Line
	6200 4600 6200 4550
$Comp
L knuth-gateway-rescue:GND-power #PWR0103
U 1 1 5D3AC17C
P 6200 4550
F 0 "#PWR0103" H 6200 4300 50  0001 C CNN
F 1 "GND" H 6205 4377 50  0000 C CNN
F 2 "" H 6200 4550 50  0001 C CNN
F 3 "" H 6200 4550 50  0001 C CNN
	1    6200 4550
	-1   0    0    1   
$EndComp
Text GLabel 5850 4500 2    50   Input ~ 0
A0
Text GLabel 5850 4400 2    50   Input ~ 0
A1
Text GLabel 5850 4300 2    50   Input ~ 0
A2
Text GLabel 5850 4200 2    50   Input ~ 0
A3
Text GLabel 5850 4100 2    50   Input ~ 0
A4
Text GLabel 5850 4000 2    50   Input ~ 0
A5
Text GLabel 5850 3900 2    50   Input ~ 0
SCK
Text GLabel 5850 3800 2    50   Input ~ 0
MOSI
Text GLabel 5850 3700 2    50   Input ~ 0
MISO
Text GLabel 5850 3600 2    50   Input ~ 0
D0
Text GLabel 5850 3500 2    50   Input ~ 0
D1
Text GLabel 5850 3400 2    50   Input ~ 0
DI01
$Comp
L Connector:Conn_01x32_Male J3
U 1 1 5E0832D5
P 4400 3050
F 0 "J3" H 4508 4731 50  0000 C CNN
F 1 "Conn_01x32_Male" H 4508 4640 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x32_P2.54mm_Vertical" H 4400 3050 50  0001 C CNN
F 3 "~" H 4400 3050 50  0001 C CNN
	1    4400 3050
	-1   0    0    1   
$EndComp
Text GLabel 4200 3650 0    50   Input ~ 0
D11
Text GLabel 4200 3550 0    50   Input ~ 0
D12
$Comp
L knuth-gateway-rescue:+3V3-power #PWR0102
U 1 1 5E092B48
P 3700 4250
F 0 "#PWR0102" H 3700 4100 50  0001 C CNN
F 1 "+3V3" H 3715 4423 50  0000 C CNN
F 2 "" H 3700 4250 50  0001 C CNN
F 3 "" H 3700 4250 50  0001 C CNN
	1    3700 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 4250 3700 4250
Wire Wire Line
	4200 4350 3700 4350
Wire Wire Line
	3700 4350 3700 4250
Connection ~ 3700 4250
$Comp
L knuth-gateway-rescue:GND-power #PWR0104
U 1 1 5E095FD5
P 3700 3350
F 0 "#PWR0104" H 3700 3100 50  0001 C CNN
F 1 "GND" H 3705 3177 50  0000 C CNN
F 2 "" H 3700 3350 50  0001 C CNN
F 3 "" H 3700 3350 50  0001 C CNN
	1    3700 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 3350 3700 3350
Wire Wire Line
	4200 3150 3700 3150
$Comp
L knuth-gateway-rescue:+3V3-power #PWR0105
U 1 1 5E097FB8
P 3700 3150
F 0 "#PWR0105" H 3700 3000 50  0001 C CNN
F 1 "+3V3" H 3715 3323 50  0000 C CNN
F 2 "" H 3700 3150 50  0001 C CNN
F 3 "" H 3700 3150 50  0001 C CNN
	1    3700 3150
	1    0    0    -1  
$EndComp
$Comp
L knuth-gateway-rescue:GND-power #PWR0106
U 1 1 5E098404
P 3700 2350
F 0 "#PWR0106" H 3700 2100 50  0001 C CNN
F 1 "GND" H 3705 2177 50  0000 C CNN
F 2 "" H 3700 2350 50  0001 C CNN
F 3 "" H 3700 2350 50  0001 C CNN
	1    3700 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 2350 3700 2350
$Comp
L knuth-gateway-rescue:+3V3-power #PWR0107
U 1 1 5E09B0E8
P 3700 1850
F 0 "#PWR0107" H 3700 1700 50  0001 C CNN
F 1 "+3V3" H 3715 2023 50  0000 C CNN
F 2 "" H 3700 1850 50  0001 C CNN
F 3 "" H 3700 1850 50  0001 C CNN
	1    3700 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 2050 3700 2050
Wire Wire Line
	4200 1850 3700 1850
Wire Wire Line
	3700 1850 3700 2050
Connection ~ 3700 1850
Wire Wire Line
	4200 1950 3500 1950
$Comp
L knuth-gateway-rescue:GND-power #PWR0108
U 1 1 5E0A0260
P 3500 1950
F 0 "#PWR0108" H 3500 1700 50  0001 C CNN
F 1 "GND" H 3505 1777 50  0000 C CNN
F 2 "" H 3500 1950 50  0001 C CNN
F 3 "" H 3500 1950 50  0001 C CNN
	1    3500 1950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x32_Male J4
U 1 1 5E0A14C3
P 4800 3050
F 0 "J4" H 4908 4731 50  0000 C CNN
F 1 "Conn_01x32_Male" H 4908 4640 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x32_P2.54mm_Vertical" H 4800 3050 50  0001 C CNN
F 3 "~" H 4800 3050 50  0001 C CNN
	1    4800 3050
	-1   0    0    1   
$EndComp
Wire Wire Line
	4600 1450 4200 1450
Wire Wire Line
	4600 1650 4200 1650
Wire Wire Line
	4600 1750 4200 1750
Wire Wire Line
	4600 1850 4200 1850
Connection ~ 4200 1850
Wire Wire Line
	4600 1950 4200 1950
Connection ~ 4200 1950
Wire Wire Line
	4600 2050 4200 2050
Connection ~ 4200 2050
Wire Wire Line
	4600 2150 4200 2150
Wire Wire Line
	4600 2250 4200 2250
Wire Wire Line
	4600 2350 4200 2350
Connection ~ 4200 2350
Wire Wire Line
	4200 2450 4600 2450
Wire Wire Line
	4600 2550 4200 2550
Wire Wire Line
	4200 2650 4600 2650
Wire Wire Line
	4600 2750 4200 2750
Wire Wire Line
	4200 2850 4600 2850
Wire Wire Line
	4600 2950 4200 2950
Wire Wire Line
	4200 3050 4600 3050
Wire Wire Line
	4600 3150 4200 3150
Connection ~ 4200 3150
Wire Wire Line
	4200 3250 4600 3250
Wire Wire Line
	4600 3350 4200 3350
Connection ~ 4200 3350
Wire Wire Line
	4200 3450 4600 3450
Wire Wire Line
	4600 3550 4200 3550
Wire Wire Line
	4200 3650 4600 3650
Wire Wire Line
	4600 3750 4200 3750
Wire Wire Line
	4200 3850 4600 3850
Wire Wire Line
	4600 3950 4200 3950
Wire Wire Line
	4200 4050 4600 4050
Wire Wire Line
	4600 4250 4200 4250
Connection ~ 4200 4250
Wire Wire Line
	4200 4450 4600 4450
Wire Wire Line
	4600 4550 4200 4550
$Comp
L Connector:Conn_01x04_Female J5
U 1 1 5E0BD889
P 5150 1650
F 0 "J5" H 5042 1225 50  0000 C CNN
F 1 "Conn_01x04_Female" H 5042 1316 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 5150 1650 50  0001 C CNN
F 3 "~" H 5150 1650 50  0001 C CNN
	1    5150 1650
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Female J6
U 1 1 5E0D7070
P 5700 2850
F 0 "J6" H 5728 2876 50  0000 L CNN
F 1 "Conn_01x03_Female" H 5728 2785 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 5700 2850 50  0001 C CNN
F 3 "~" H 5700 2850 50  0001 C CNN
	1    5700 2850
	-1   0    0    1   
$EndComp
$Comp
L power:GNDREF #PWR0109
U 1 1 5E0D7AA6
P 3350 3250
F 0 "#PWR0109" H 3350 3000 50  0001 C CNN
F 1 "GNDREF" H 3355 3077 50  0000 C CNN
F 2 "" H 3350 3250 50  0001 C CNN
F 3 "" H 3350 3250 50  0001 C CNN
	1    3350 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 3250 3350 3250
Connection ~ 4200 3250
$Comp
L power:GNDREF #PWR0110
U 1 1 5E0DADF7
P 6450 2950
F 0 "#PWR0110" H 6450 2700 50  0001 C CNN
F 1 "GNDREF" H 6455 2777 50  0000 C CNN
F 2 "" H 6450 2950 50  0001 C CNN
F 3 "" H 6450 2950 50  0001 C CNN
	1    6450 2950
	-1   0    0    1   
$EndComp
Wire Wire Line
	5900 2950 6450 2950
Wire Wire Line
	4600 1550 4200 1550
Text GLabel 4200 1450 0    50   Input ~ 0
PT4
Text GLabel 4200 1550 0    50   Input ~ 0
PT3
Text GLabel 4200 1650 0    50   Input ~ 0
PT2
Text GLabel 4200 1750 0    50   Input ~ 0
PT1
Text GLabel 5350 1450 2    50   Input ~ 0
PT4
Text GLabel 5350 1550 2    50   Input ~ 0
PT3
Text GLabel 5350 1650 2    50   Input ~ 0
PT2
Text GLabel 5350 1750 2    50   Input ~ 0
PT1
Text GLabel 6200 2100 2    50   Input ~ 0
PT1
$Comp
L Connector:Conn_01x02_Female J7
U 1 1 5E10B3E5
P 6000 2200
F 0 "J7" H 6028 2176 50  0000 L CNN
F 1 "Conn_01x02_Female" H 6028 2085 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 6000 2200 50  0001 C CNN
F 3 "~" H 6000 2200 50  0001 C CNN
	1    6000 2200
	-1   0    0    1   
$EndComp
Wire Wire Line
	5900 2850 6200 2850
Wire Wire Line
	6200 2850 6200 2200
Text GLabel 5900 2750 2    50   Input ~ 0
D10
Text GLabel 4200 4050 0    50   Input ~ 0
A3
Text GLabel 4200 3950 0    50   Input ~ 0
A2
Text GLabel 4200 4450 0    50   Input ~ 0
A4
Text GLabel 4200 4550 0    50   Input ~ 0
A5
Text GLabel 4200 3750 0    50   Input ~ 0
A0
Text GLabel 4200 3850 0    50   Input ~ 0
A1
Wire Wire Line
	4600 4350 4600 4250
Connection ~ 4600 4250
$Comp
L Mechanical:MountingHole H2
U 1 1 5E21CAD6
P 6050 1200
F 0 "H2" H 6150 1246 50  0000 L CNN
F 1 "MountingHole" H 6150 1155 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm" H 6050 1200 50  0001 C CNN
F 3 "~" H 6050 1200 50  0001 C CNN
	1    6050 1200
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5E21CEB8
P 6050 1400
F 0 "H3" H 6150 1446 50  0000 L CNN
F 1 "MountingHole" H 6150 1355 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm" H 6050 1400 50  0001 C CNN
F 3 "~" H 6050 1400 50  0001 C CNN
	1    6050 1400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5E21D442
P 6050 1600
F 0 "H4" H 6150 1646 50  0000 L CNN
F 1 "MountingHole" H 6150 1555 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm" H 6050 1600 50  0001 C CNN
F 3 "~" H 6050 1600 50  0001 C CNN
	1    6050 1600
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 5E21D8B9
P 6050 1000
F 0 "H1" H 6150 1046 50  0000 L CNN
F 1 "MountingHole" H 6150 955 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm" H 6050 1000 50  0001 C CNN
F 3 "~" H 6050 1000 50  0001 C CNN
	1    6050 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 4150 4200 4150
$EndSCHEMATC
