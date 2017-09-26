import random
import numpy
import pandas
import time
import seaborn

def inorder(x):
    i = 0
    j = len(x)
    while i + 1 < j:
        if x[i] > x[i + 1]:
            return False
        i += 1
    return True

#
# Sort function
#
def sort(items, kind):
    if kind == 'bogosort':
        while not inorder(items):
            random.shuffle(items)
        return numpy.array(items)
    elif kind == 'bubblesort':
        for i in range(len(items)):
            for j in range(len(items)-1-i):
                if items[j] > items[j+1]:
                    items[j], items[j+1] = items[j+1], items[j]
        return numpy.array(items)

    elif kind == 'insertsort':
        for i in range(1, len(items)):
            j = i
            while j > 0 and items[j] < items[j-1]:
                items[j], items[j-1] = items[j-1], items[j]
                j -= 1
        return numpy.array(items)

    else:
        return numpy.sort(items, kind=kind)

#
# Calculating times
#
def plot(sort_algorithms, measures=20, average=10, start_step=0, step=2, time_limit=False):
    times = {
        'kind': [],
        'size': [],
        'subject': [],
        'time': [],
    }

    for i in range(measures+1):
        size = step**(i+start_step)  
        print('Creating array for size ' + str(size))

        to_remove = []

        for j in range(average):
            items = numpy.random.randint(0, size*10, size=size)

            for kind in sort_algorithms:
                to_sort = items[:]

                # Measuring time
                start = time.time()
                sort(to_sort, kind=kind)
                end = time.time()

                if time_limit:
                    if end-start > time_limit:
                        print('"' + kind + '" exceeded time limit: ' + str(end-start))
                        if kind not in to_remove:
                            to_remove += [kind]

                # Adding to object
                times['kind'] += [kind]
                times['size'] += [size]
                times['subject'] += [j]
                times['time'] += [end-start]
        
        for remove in to_remove:
            sort_algorithms.remove(remove)
        
        if len(sort_algorithms) == 0:
            break

    #
    # Plotting
    #
    seaborn.set(style="darkgrid")

    for key in times:
        times[key] = pandas.Series(numpy.array(times[key]))

    return pandas.DataFrame(times)


if __name__ == '__main__':
    # Plot
    def plotAlone():
        seaborn.plt.subplot(3, 2, 1)
        seaborn.tsplot(plot(['bogosort'], measures=100, step=1.05, time_limit=0.5), 
            time='size', value='time', unit='subject', condition='kind')
        seaborn.plt.subplot(3, 2, 2)
        seaborn.tsplot(plot(['bubblesort'], measures=100, step=1.3, time_limit=0.5), 
            time='size', value='time', unit='subject', condition='kind')
        seaborn.plt.subplot(3, 2, 3)
        seaborn.tsplot(plot(['insertsort'], measures=100, step=1.4, time_limit=0.5), 
            time='size', value='time', unit='subject', condition='kind')
        seaborn.plt.subplot(3, 2, 4)
        seaborn.tsplot(plot(['heapsort'], measures=100, step=2, time_limit=0.5), 
            time='size', value='time', unit='subject', condition='kind')
        seaborn.plt.subplot(3, 2, 5)
        seaborn.tsplot(plot(['mergesort'], measures=100, step=2, time_limit=0.5), 
            time='size', value='time', unit='subject', condition='kind')
        seaborn.plt.subplot(3, 2, 6)
        seaborn.tsplot(plot(['quicksort'], measures=100, step=2, time_limit=0.5), 
            time='size', value='time', unit='subject', condition='kind')
    
    def plotTogether():
        seaborn.tsplot(plot(['bogosort', 'bubblesort', 'insertsort', 'heapsort', 'mergesort', 'quicksort'], time_limit=0.5), 
            time='size', value='time', unit='subject', condition='kind')

    def plotMaxer():
        seaborn.plt.subplot(2, 1, 1)
        seaborn.tsplot(plot(['bubblesort', 'insertsort'], 5), 
            time='size', value='time', unit='subject', condition='kind')

        seaborn.plt.subplot(2, 1, 2)
        seaborn.tsplot(plot(['mergesort', 'quicksort'], 25), 
            time='size', value='time', unit='subject', condition='kind')
    
    def plotCompareMax():
        seaborn.factorplot(data=plot(['heapsort', 'mergesort', 'quicksort'], 3, start_step=17, step=2), 
            x='size', y='time', units='subject', hue='kind', kind='bar')

    def plotCompareMin():
        seaborn.factorplot(data=plot(['bubblesort', 'insertsort'], 3, start_step=1, step=2), 
            x='size', y='time', units='subject', hue='kind', kind='bar')

    plotAlone()

    #
    # Show
    #
    seaborn.plt.show()
