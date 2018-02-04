# coding: utf-8
import matplotlib.pyplot as plot
import numpy as np
notes = [1,1,1,3,5]
barsX = [0,1,2,3,4,5,6]
notesHist = []

for note in barsX:
    notesHist.append(notes.count(note))
    



plot.ylabel('Occurences')
plot.bar(barsX, notesHist,color='#eaaa00')
plot.xlabel('Note')
plot.xticks(np.arange(8),('G','A','B','C','D','E','F','G'))
plot.title(r'Histogram for user input queue, $(A_4,A_2,C_4,E_4,A_3)$')
plot.savefig('histogramExample',dpi=300)
plot.show()
