import os.path
import sys
import timeit
from array import array
from classes.function import Function
from classes.eqc import EqCF
from utils.utils import *

num_args = 4
dim = 2 ** num_args
num_func = 2 ** dim
wt_by_2 = dim/2

had = []
create_had(had, num_args, dim)
wt_vec = array('i', [])
create_wt_vec(wt_vec, dim)

start_time = timeit.default_timer()
curr_dir = os.path.dirname(__file__)
parent_dir = os.path.split(curr_dir)[0]
data_dir = os.path.join(parent_dir, 'data')
fo_max = open(os.path.join(data_dir, "max_" + str(num_args)), "w")

max = 0
maxf = []
for fI in xrange(num_func):
    f = Function(fI, num_args, dim)
    f.transform(had)
    f.compute_entropy_influence(wt_vec)
    if f.ei_ratio > max:
        maxf = []
        max = f.ei_ratio
    if f.ei_ratio == max:
        maxf.append(f)

for i in xrange(len(maxf)):
    maxf[i].print_info(fo_max)