import sys
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

centre = []
eigs = []
for fI in xrange(num_func):
    f = Function(fI, num_args, dim)
    f.transform(had)
    f.compute_entropy_influence(wt_vec)

#    if (f.is_eig() == 1):
    if f.fEntropy == 4.0:
        centre.append(f)
#        eigs.append(f)

    if (f.is_character() == 1):
        centre.append(f)

max_mindist = 0
max_f = Function(0, num_args, dim)
for fI in xrange(num_func):
    f = Function(fI, num_args, dim)
    curr_mindist = f.min_hdist(centre)
    if curr_mindist > max_mindist:
        max_mindist = curr_mindist
        max_f = f

print(str(max_mindist))
max_f.transform(had)
max_f.display_info()
for c in centre:
    print(str(dot(c.vec, max_f.vec)))