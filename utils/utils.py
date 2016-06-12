from array import array
import timeit
from math import log

__author__ = 'rkant'

def eq(vec1, vec2):
    """ Assumes dimensions match
    :return: 1 if equal, 0 otherwise
    >>> eq([1, 0, 1], [1, 0, 1])
    1
    >>> eq([1, 0, 1], [1, 0, 0])
    0
    """
    for i in xrange(len(vec1)):
        if vec1[i] != vec2[i]:
            return 0
    return 1

def dot(vec1, vec2):
    """ Assumes dimensions match
    >>> dot([1, -1, 1], [-1, -1, 1])
    1
    """
    s = 0
    for i in xrange(len(vec1)):
        s += vec1[i] * vec2[i]
    return s

def hdist(vec1, vec2):
    """
    >>> hdist([1, -1, -1], [-1, -1, 1])
    2
    """
    d = 0
    for i in xrange(len(vec1)):
        if vec1[i] != vec2[i]:
            d += 1
    return d

def dist_to_set(vec, set):
    """
    >>> dist_to_set([1, -1, -1], [[-1, -1, 1], [1, -1, 1]])
    1
    """
    min = len(vec)
    for i in xrange(len(set)):
        curr_dist = hdist(vec, set[i])
        if min > curr_dist:
            min = curr_dist
    return min

def dist_to_fset(vec, set):
    min = len(vec)
    for i in xrange(len(set)):
        curr_dist = hdist(vec, set[i].vec)
        if min > curr_dist:
            min = curr_dist
    return min

def hdot(vec1, vec2, result):
    """ Assumes dimensions match
    >>> result = array('i', [])
    >>> hdot([1, -1, 1], [-1, -1, 1], result)
    >>> result
    array('i', [-1, 1, 1])
    """
    for i in xrange(len(vec1)):
        result.append(vec1[i] * vec2[i])


def mult_m_v(mat, vec, res):
    for i in xrange(len(mat)):
        res.append(dot(mat[i], vec))


def i_to_b(num, b_arr, n_args):
    """
    :param num: int
    :param b_arr: binary array
    :param n_args: dimension of b_arr
    >>> result = array('i', [])
    >>> i_to_b(5, result, 4)
    >>> result
    array('i', [0, 1, 0, 1])
    """
    curr_v = num
    for i in xrange(n_args):
        b_arr.append(curr_v % 2)
        curr_v /= 2
    b_arr.reverse()

def i_to_bstr(num, b_arr, n_args):
    """
    :param num: int
    :param b_arr: binary array
    :param n_args: dimension of b_arr
    >>> result = array('i', [])
    >>> i_to_b(5, result, 4)
    >>> result
    array('i', [0, 1, 0, 1])
    """
    curr_v = num
    for i in xrange(n_args):
        b_arr.append(str(curr_v % 2))
        curr_v /= 2
    b_arr.reverse()

def print_poly(num, num_var, dim):
    """
    :param num: integer encoding of poly
    :param dim: dimension of polyvec
    >>> print_poly(5, 3, 8)
    [101] + [111]
    """
    polyvec = array('i', [])
    i_to_b(num, polyvec, dim)
    monomials = []
    for i in xrange(dim):
        if polyvec[i] == 1:
            monovec = []
            i_to_bstr(i, monovec, num_var)
            monomial = '[' + ''.join(monovec) + ']'
            monomials.append(monomial)
    print " + ".join(monomials)

def i_to_poly(num, f_arr, n_var, dim_f):
    """
    :param num: int encoding of poly
    :param f_arr: polynomial function in {-1, 1}
    :param dim_f: dimension of f_arr
    >>> f_arr = array('i', [])
    >>> i_to_poly(1, f_arr, 4, 16)
    >>> f_arr
    array('i', [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1])
    """
    polyvec = array('i', [])
    i_to_b(num, polyvec, dim_f)
    for i in xrange(dim_f):
        x = array('i', [])
        i_to_b(i, x, n_var)
        val = polyfunc(polyvec, x, n_var, dim_f)
        if (val % 2) == 0:
            f_arr.append(1)
        else:
            f_arr.append(-1)

def polyfunc(polyvec, x, n_var, dim):
    """
    :param polyvec: vec encoding of polyfunc
    :param x: input vector
    :param dim: dimension of polyvec
    >>> polyfunc([0, 1, 0, 1, 0, 0, 0, 1], [0, 1, 1], 3, 8)
    2
    """
#    assert(len(x) == n_var)
#    assert(2**n_var == dim)

    sum = 0
    for i in xrange(dim):
        if polyvec[i] == 0:
            continue
        sum += monofunc(i, x, n_var)
    return sum

def monofunc(num, x, n_var):
    """
    :param num: int encoding of monomial
    :param x: input vector
    :param n_var: dimension of x
    :return: monomial evaluated on x
    >>> monofunc(5, [0, 1, 1, 1], 4)
    1
    """
    val = 1
    num_arr = array('i', [])
    i_to_b(num, num_arr, n_var)
    for i in xrange(n_var):
        if num_arr[i] == 1:
            val *= x[i]
    return val

def b_to_i(b_arr):
    """
    :param b_arr: binary arr
    :return: b_arr converted to int
    >>> b_to_i([0, 1, 0, 1])
    5
    >>> b_to_i([1,0,1,0])
    10
    """
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
    """
    :param num_f: integer encoding of func
    :param f_arr: arr representation of func
    :param vec_dim: dim of f_arr. Always a power of 2

    >>> f_arr = array('i', [])
    >>> to_func(22, f_arr, 8)
    >>> f_arr
    array('i', [1, 1, 1, -1, 1, -1, -1, 1])
    """
    f_bin = array('i', [])
    i_to_b(num_f, f_bin, vec_dim)
    for i in xrange(len(f_bin)):
        if f_bin[i] == 0:
            f_arr.append(1)
        else:
            f_arr.append(-1)


def sparsity(arr):
    """
    >>> sparsity([0.25, 0, 0, 0.25, 0.25, 0, 0, 0.25])
    4
    """
    n = 0
    for x in arr:
        if x != 0:
            n += 1
    return n


def square(num):
    return num * num


def entropy(arr):
    """ Assumes arr is a valid prob distribution
    >>> entropy([0.25, 0, 0, 0.25, 0.25, 0, 0, 0.25])
    2.0
    """
    h = 0
    for x in arr:
        if (x > 0) and (x < 1):
            h += x * log(1/x, 2)
    return h


def create_wt_vec(wt_vec, vec_dim):
    """
    :param wt_vec: vector where i'th position denotes num_ones in i
    :param vec_dim: dimension of wt_vec
    >>> wt_vec = array('i', [])
    >>> create_wt_vec(wt_vec, 8)
    >>> wt_vec
    array('i', [0, 1, 1, 2, 1, 2, 2, 3])
    """
    for i in xrange(vec_dim):
        wt_vec.append(num_ones_in_int(i))


def create_had(mat, order, vec_dim):
    for i in xrange(vec_dim):
        curr_row = array('i', [])
        curr_index_i = array('i', [])
        i_to_b(i, curr_index_i, order)
        for j in xrange(vec_dim):
            curr_index_j = array('i', [])
            i_to_b(j, curr_index_j, order)
            if (dot(curr_index_i, curr_index_j) % 2) == 0:
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

def arr_to_line(arr, out_fo, delim):
#    out_fo.write(delim.join(arr) + "\t" + str(len(arr)) + "\n")
    out_fo.write(delim.join(arr) + "\n")

def heartbeat(count, start, interval):
    if (count % interval) == 0:
        curr_time = timeit.default_timer() - start
        print("Finished " + str(count) + ". Time Taken: " + str(curr_time) + " seconds")


if __name__ == '__main__':
    import doctest
    doctest.testmod()
