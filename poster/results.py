
import numpy as np
import matplotlib.pyplot as plot

_dpi = 300

dMinor = np.loadtxt('dMinorRes.csv',dtype=np.int,delimiter=',')
cMelody = np.loadtxt('cMelodyRes.csv',dtype=np.int,delimiter=',')
chromatic = np.loadtxt('chromaticRes.csv',dtype=np.int,delimiter=',')



def label():
	plot.xlabel('Fitness')
	plot.ylabel('Occurences')
	plot.xticks([0,1,2,3,4,5,6,7,8,9,10,11,12,13])

def DM(res):
	global dpi
	plot.hist(res[:,1],bins=np.arange(13),color='#002855')
	plot.title('D Minor Response Frequencies')
	plot.ylim(0,30)
	plot.xlim(0,14)
	print(res)
	label()
	plot.savefig('dMinorHistogram',dpi=_dpi)
	plot.show()
	
def CMEL(res):
	global dpi
	plot.hist(res[:,1],bins=np.arange(13),color='#002855')
	plot.title('C Melody Response Frequencies')
	plot.ylim(0,30)
	plot.xlim(0,14)
	print(res)
	label()
	plot.savefig('cMelodyHistogram',dpi=_dpi)
	plot.show()

def CHROM(res):
	global dpi
	plot.hist(res[:,1],bins=np.arange(13),color='#002855')
	plot.title('Chromatic Scale Response Frequencies')
	plot.ylim(0,30)
	plot.xlim(0,14)
	print(res)
	label()
	plot.savefig('chromaticHistogram',dpi=_dpi)
	plot.show()
	
	
	

DM(dMinor)
CMEL(cMelody)
CHROM(chromatic)

