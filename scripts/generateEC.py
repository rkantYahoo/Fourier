import timeit
from array import array

from classes.function import Function

from utils.utils import create_had, print_map, heartbeat, hdot, vec_to_i


num_args = 3
dim = 2 ** num_args

lo = 0
hi = 2 ** (dim - 1)

had = []
create_had(had, num_args, dim)

fo_map = open("map_" + str(num_args) + "_" + str(hi), "w")
fo_rep = open("rep_" + str(num_args) + "_" + str(hi), "w")

ec_map = {}
ec_rep = {}

start_time = timeit.default_timer()
for fI in xrange(lo, hi):
    heartbeat(fI, start_time, 1000000)
    f = Function(fI, num_args, dim)
    if f.name not in ec_map:
        ec_rep[f.name] = 1
        for i in xrange(dim):
            curr_vec = array('i', [])
            hdot(f.vec, had[i], curr_vec)
            curr_name = vec_to_i(curr_vec)
            if curr_name < hi:
                ec_map[curr_name] = f.name
            fo_map.write(str(curr_name) + "\t" + str(f.name) + "\n")

fo_map.close()
print_map(ec_rep, fo_rep)
fo_rep.close()
