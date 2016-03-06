import os.path
import sys
import timeit
from array import array
from classes.function import Function
from utils.utils import *


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


for fI in xrange(num_func):
    heartbeat(fI, start_time, 1000000)

    f = Function(fI, num_args, dim)
    f.transform(had)
    f.compute_entropy_influence(wt_vec)
    f.print_info(fo)