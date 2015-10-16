from array import array
import timeit

__author__ = 'rkant'


def dot(vec1, vec2):
    s = 0
    for i in xrange(len(vec1)):
        s += vec1[i] * vec2[i]
    return s


def hdot(vec1, vec2, result):
    for i in xrange(len(vec1)):
        result.append(vec1[i] * vec2[i])


def mult_m_v(mat, vec, res):
    for i in xrange(len(mat)):
        res.append(dot(mat[i], vec))


def i_to_b(num, b_arr, n_args):
    curr_v = num
    for i in xrange(n_args):
        b_arr.append(curr_v % 2)
        curr_v /= 2
    b_arr.reverse()


def b_to_i(b_arr):
    curr_v = 0
    for i in xrange(len(b_arr)):
        curr_v = 2*curr_v + b_arr[i]
    return curr_v


def vec_to_i(vec):
    b_vec = array('i', [])
    for i in xrange(len(vec)):
        if vec[i] == 1:
            b_vec.append(0)
        else:
            b_vec.append(1)
    return b_to_i(b_vec)


def num_ones_in_int(num):
    curr_v = num
    n = 0
    while curr_v > 0:
        n += (curr_v % 2)
        curr_v /= 2
    return n


def to_func(num_f, f_arr, vec_dim):
    f_bin = array('i', [])
    i_to_b(num_f, f_bin, vec_dim)
    for i in xrange(len(f_bin)):
        if f_bin[i] == 0:
            f_arr.append(1)
        else:
            f_arr.append(-1)


def sparsity(arr):
    n = 0
    for i in xrange(len(arr)):
        if arr[i] != 0:
            n += 1
    return n


def create_had(mat, order, vec_dim):
    for i in xrange(vec_dim):
        curr_row = array('i', [])
        curr_index_i = array('i', [])
        i_to_b(i, curr_index_i, order)
        for j in xrange(vec_dim):
            curr_index_j = array('i', [])
            i_to_b(j, curr_index_j, order)
            if ((dot(curr_index_i, curr_index_j) % 2) == 0):
                curr_row.append(1)
            else:
                curr_row.append(-1)
        mat.append(curr_row)


def increment(hash_map, key):
    if key not in hash_map:
        hash_map[key] = 0
    hash_map[key] += 1


def print_map(hash_map, out_fo):
    for key in hash_map:
        out_fo.write(str(key) + "  -->  " + str(hash_map[key]) + "\n")


def heartbeat(count, start, interval):
    if (count % interval) == 0:
        currTime = timeit.default_timer() - start
        print("Finished " + str(count) + ". Time Taken: " + str(currTime) + " seconds")