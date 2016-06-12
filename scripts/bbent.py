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
fo_level3 = open(os.path.join(data_dir, "level3_" + str(num_args)), "w")

levels01 = []
num = 0
for fI in xrange(num_func):
    f = Function(fI, num_args, dim)
    f.transform(had)
    f.compute_entropy_influence(wt_vec)
    if (f.is_bent() == 1) or (f.is_character() == 1):
        levels01.append(f)
        num += 1
 #       f.display_info()

print num
#print len(levels01)

max = 0
max_vecs = []

for fI in xrange(num_func):
    heartbeat(fI, start_time, 10000)
    f = Function(fI, num_args, dim)
    curr_dist = dist_to_fset(f.vec, levels01)
    if curr_dist > max:
        max_vecs = []
        max = curr_dist

    if curr_dist == max:
        max_vecs.append(f)

print max
print len(max_vecs)
for i in xrange(len(max_vecs)):
    levels01.append(max_vecs[i])

max = 0
max_vecs_level3 = []
for fI in xrange(num_func):
    heartbeat(fI, start_time, 10000)
    f = Function(fI, num_args, dim)
    curr_dist = dist_to_fset(f.vec, levels01)
    if curr_dist > max:
        max_vecs_level3 = []
        max = curr_dist

    if curr_dist == max:
        max_vecs_level3.append(f)

print max
print len(max_vecs_level3)

for i in xrange(len(max_vecs_level3)):
    max_vecs_level3[i].transform(had)
    max_vecs_level3[i].compute_entropy_influence(wt_vec)
    max_vecs_level3[i].print_info(fo_level3)