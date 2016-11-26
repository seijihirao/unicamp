import random
import numpy
import pandas
import time

#
# Control variables
#
average = 10
measures = 25

#
# results
#
sort_algorithms = ['quicksort', 'mergesort', 'heapsort']
times = {
    'kind': [],
    'size': [],
    'subject': [],
    'time': [],
}

#
# Calculating times
#
for i in range(measures):
    size = 2**i
    
    print('Creating array for size ' + str(size))

    for j in range(average):
        items = numpy.random.randint(0, size*10, size=size)

        for kind in sort_algorithms:
            to_sort = items[:]

            # Measuring time
            start = time.time()
            numpy.sort(to_sort, kind=kind)
            end = time.time()

            # Adding to object
            times['kind'] += [kind]
            times['size'] += [size]
            times['subject'] += [j]
            times['time'] += [end-start]


#
# Plotting
#
import seaborn as sns
sns.set(style="darkgrid")

for key in times:
    times[key] = pandas.Series(numpy.array(times[key]))

sns.tsplot(pandas.DataFrame(times), time="size", value="time", unit="subject", condition="kind")
print(pandas.DataFrame(times))
print(sns.load_dataset("gammas"))

sns.plt.show()