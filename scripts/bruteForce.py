import os.path
import sys
import timeit
from array import array
from classes.function import Function
from classes.eqc import EqCF
from utils.utils import *

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
#fo = open(os.path.join(data_dir, "fFull" + str(num_args)), "w")
#fo_counts = open(os.path.join(data_dir, "fCounts" + str(num_args)), "w")
#fo_eqcs = open(os.path.join(data_dir, "fEqCs" + str(num_args)), "w")
#fo_eigs = open(os.path.join(data_dir, "fEigsT" + str(num_args)), "w")
fo_eig_w_dot = open(os.path.join(data_dir, "fEigMatrix" + str(num_args)), "w")

ecCounts = {}
secCounts = {}
eqcs = {}
eigs = []
all_eigs = []

for fI in xrange(num_func):
#    heartbeat(fI, start_time, 1000000)

    f = Function(fI, num_args, dim)
    f.transform(had)
    f.compute_entropy_influence(wt_vec)
#    f.print_info(fo)

    if (f.is_eig() == 1):
        all_eigs.append(f)
        if len(f.tvec) == 6:
            eigs.append(f)

#for i in xrange(len(eigs)):
#    fo_eig_w_dot.write(str(i) + ": ")
#    f.print_info(fo_eig_w_dot)
#fo_eig_w_dot.write("\n\n")

for i in xrange(len(eigs)):
    curr_f = eigs[i]
    curr_vec = []
    curr_non = []
    for j in xrange(len(eigs)):
        if dot(curr_f.vec, eigs[j].vec) == 0:
            curr_vec.append(str(j))
        else:
            curr_non.append(str(j))

#    fo_eig_w_dot.write(','.join(curr_non) + ": ")
#    curr_f.print_info(fo_eig_w_dot)

for i in xrange(len(eigs)):
    curr_fi = eigs[i]
    curr_vec = []
    for j in xrange(len(eigs)):
        curr_fj = eigs[j]
        curr_vec.append(str(dot(curr_fi.vec, curr_fj.vec)))
    arr_to_line(curr_vec, fo_eig_w_dot, '\t')

#        arr_to_line(curr_vec, fo_eig_w_dot, ',')

    # if f.signature not in ecCounts:
    #     new_eqc = EqCF(f, 1)
    #     eqcs[f.signature] = new_eqc
    # else:
    #     eqcs[f.signature].add_verbose(f)
    #
    # increment(ecCounts, f.signature)
    # increment(secCounts, f.ssignature)
# fo.close()
#
# fo_counts.write("unsigned counts:\n")
# print_map(ecCounts, fo_counts)
# fo_counts.write("\n\nsigned counts:\n")
# print_map(secCounts, fo_counts)
# fo_counts.close()
# for eqc in eqcs:
#     eqcs[eqc].print_to_file(fo_eqcs)
#fo_eqcs.close()

fo_eig_w_dot.close()
print(sys.maxint)
