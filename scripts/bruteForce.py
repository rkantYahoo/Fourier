import os.path
import sys
import timeit
from array import array
from classes.function import Function
from classes.eqc import EqCF
from utils.utils import create_had, increment, print_map, heartbeat, create_wt_vec

#cfg = ConfigParser.ConfigParser()
#cfg.readfp(open('settings.cfg'))

num_args = 4
dim = 2 ** num_args
num_func = 2 ** dim

had = []
create_had(had, num_args, dim)
wt_vec = array('i', [])
create_wt_vec(wt_vec, dim)

start_time = timeit.default_timer()
curr_dir = os.path.dirname(__file__)
parent_dir = os.path.split(curr_dir)[0]
data_dir = os.path.join(parent_dir, 'data')
fo = open(os.path.join(data_dir, "fFull" + str(num_args)), "w")
fo_counts = open(os.path.join(data_dir, "fCounts" + str(num_args)), "w")
fo_eqcs = open(os.path.join(data_dir, "fEqCs" + str(num_args)), "w")

ecCounts = {}
secCounts = {}
eqcs = {}

for fI in xrange(num_func):
    heartbeat(fI, start_time, 1000000)

    f = Function(fI, num_args, dim)
    f.transform(had)
    f.compute_entropy_influence(wt_vec)
    f.print_info(fo)
    if f.signature not in ecCounts:
        new_eqc = EqCF(f, 1)
        eqcs[f.signature] = new_eqc
    else:
        eqcs[f.signature].add_verbose(f)

    increment(ecCounts, f.signature)
    increment(secCounts, f.ssignature)
fo.close()

fo_counts.write("unsigned counts:\n")
print_map(ecCounts, fo_counts)
fo_counts.write("\n\nsigned counts:\n")
print_map(secCounts, fo_counts)
fo_counts.close()
for eqc in eqcs:
    eqcs[eqc].print_to_file(fo_eqcs)

print(sys.maxint)
