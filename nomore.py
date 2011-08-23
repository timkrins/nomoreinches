# nomoreinches, in python!
# by tim k.

# wow... comparing this output to my old program output, the values are quite different!
# so, that means one of these programs works terribly...

# not sure which one it is yet :)
# onward!

from decimal import Decimal 
import re, string, sys, decimal

def clearvalues():
	XValTemp = 0
	YValTemp = 0
	ZValTemp = 0
	FValTemp = 0
	XVals = 0
	YVals = 0
	ZVals = 0
	FVals = 0
	PrintX = 0
	G00Val = 0
	G01Val = 0
	printline = 0
	return

try:
	loadfile = sys.argv[1]
except IndexError:
	loadfile = "front.ngc"

XMulti = YMulti = ZMulti = FMulti = Decimal('25.4')
XMax = YMax = ZMax = FMax = -99999999999
XMin = YMin = ZMin = FMin =  99999999999
XMod = YMod = 0
printline = 0
XArray = []
YArray = []
ZArray = []
FArray = []
    
print "No more Inches, in Python! Arbitary Version 1.SeventyBagelZero, by Tim K. \n"
print "Processing file: " + loadfile + ". Output in millimetres.\n"

fLoad = open(loadfile, 'r')
	
for line in fLoad:
	clearvalues()
	
	try:
		XValTemp = re.findall('X([\d|\.]+)', line)
		XVals = Decimal(XValTemp[0])
		XArray.append(XVals)
	except:
		pass	
	
	try:
		YValTemp = re.findall('Y([\d|\.]+)', line)
		YVals = Decimal(YValTemp[0])
		YArray.append(YVals)
	except:
		pass
		
	try:
		ZValTemp = re.findall('Z([\d|\.]+)', line)
		ZVals = Decimal(ZValTemp[0])
		ZArray.append(ZVals)
	except:
		pass
		
	try:
		FValTemp = re.findall('F([\d|\.]+)', line)
		FVals = Decimal(FValTemp[0])
		FArray.append(FVals)
	except:
		pass

XMin = (XMulti*min(XArray))
XMax = (XMulti*max(XArray))
YMin = (YMulti*min(YArray))
YMax = (YMulti*max(YArray))
ZMin = (ZMulti*min(ZArray))
ZMax = (ZMulti*max(ZArray))
FMin = (FMulti*min(FArray))
FMax = (FMulti*max(FArray))

print ("XMin: "+repr(float(XMin+XMod))+", XMax: "+repr(float(XMax+XMod)))
print ("YMin: "+repr(float(YMin+YMod))+", YMax: "+repr(float(YMax+YMod)))
print ("ZMin: "+repr(float(ZMin))+", ZMax: "+repr(float(ZMax)))
print ("FMin: "+repr(float(FMin))+", FMax: "+repr(float(FMax)))

AutoMod = 1

try:
	AutoMod != ""
	XMod = (0-XMin)
	YMod = (0-YMin)
	print ("\nAutoMod enabled. X and Y minimums reset. New values:")
	print ("XMin: "+repr(float(XMin+XMod))+", XMax: "+repr(float(XMax+XMod)))
	print ("YMin: "+repr(float(YMin+YMod))+", YMax: "+repr(float(YMax+YMod)))
except:
	XMod = 0
	YMod = 0


fSave = open('converted-mm.ngc', 'w')

fLoad.seek(0)
for line in fLoad:
	clearvalues()
	printline = 0
	try:
		G00Val = re.findall('G00', line)
		if G00Val[0]:
			printline = 1
		fSave.write('G00 ')
		
	except:
		try:
			G01Val = re.findall('G01', line)
			if G01Val[0]:
				printline = 1
			fSave.write('G01 ')
		except:
			pass
	try:
		XValTemp = re.findall('X([\d|\.|-]+)', line)
		XVals = XMulti*Decimal(XValTemp[0])
		if XVals:
			printline = 1
		fSave.write('X'+repr(float(XVals))+' ')
	except:
		pass
	try:
		YValTemp = re.findall('Y([\d|\.|-]+)', line)
		YVals = YMulti*Decimal(YValTemp[0])
		if YVals:
			printline = 1
		fSave.write('Y'+repr(float(YVals))+' ')
	except:
		pass
	try:
		ZValTemp = re.findall('Z([\d|\.|-]+)', line)
		ZVals = ZMulti*Decimal(ZValTemp[0])
		if ZVals:
			printline = 1
		fSave.write('Z'+repr(float(ZVals))+' ')
	except:
		pass
	try:
		FValTemp = re.findall('F([\d|\.|-]+)', line)
		FVals = FMulti*Decimal(FValTemp[0])
		if FVals:
			printline = 1
		fSave.write('F'+repr(float(FVals))+' ')
	except:
		pass
		
	if printline > 0:
		fSave.write('\n')
fSave.close()
fLoad.close()
