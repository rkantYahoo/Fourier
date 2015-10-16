import sys
import timeit

from classes.function import Function
from utils.utils import create_had, increment, print_map, heartbeat


num_args = 3
dim = 2 ** num_args
num_func = 2 ** dim

had = []
create_had(had, num_args, dim)

start_time = timeit.default_timer()
fo = open("fourierFull" + str(num_args), "w")
fo_counts = open("fourierCounts" + str(num_args), "w")
ecCounts = {}
secCounts = {}

for fI in xrange(num_func):
    heartbeat(fI, start_time, 1000000)

    f = Function(fI, num_args, dim)
    f.transform(had)
    f.print_info(fo)
    increment(ecCounts, f.signature)
    increment(secCounts, f.ssignature)
fo.close()

fo_counts.write("unsigned counts:\n")
print_map(ecCounts, fo_counts)
fo_counts.write("\n\nsigned counts:\n")
print_map(secCounts, fo_counts)
print(sys.maxint)

