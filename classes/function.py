from array import array
from utils.utils import *


class Function(object):
    def __init__(self, name, order, vec_dim):
        self.name = name
        self.order = order
        self.dimension = vec_dim
        self.vec = array("i", [])
        self.hat = array("i", [])
        self.inf = array("i", [])
        self.deg = 0
        self.nInfVar = 0
        self.fEntropy = 0
        self.tInf = 0
        self.signature = ''
        self.ssignature = ''
        self.__to_func(name, vec_dim)

    def compute_entropy_influence(self, wt_vec):
        hatsq = array('f', [])
        for i in xrange(self.dimension):
            hatsq.append(square(float(self.hat[i])/self.dimension))
        self.fEntropy = entropy(hatsq)
        self.tInf = dot(wt_vec, hatsq)

    def __to_func(self, name, vec_dim):
        f_bin = array('i', [])
        i_to_b(name, f_bin, vec_dim)
        for i in xrange(len(f_bin)):
            if f_bin[i] == 0:
                self.vec.append(1)
            else:
                self.vec.append(-1)

    def __degree(self):
        n = self.dimension
        deg = 0
        for i in xrange(n):
            if self.hat[i] == 0:
                continue
            curr_deg = num_ones_in_int(i)
            if deg < curr_deg:
                deg = curr_deg
        return deg

    def __num_inf_var(self):
        inf_arr = [0] * self.order
        for i in xrange(self.dimension):
            if self.hat[i] == 0:
                continue
            curr_input = array('i', [])
            i_to_b(i, curr_input, self.order)
            for j in xrange(self.order):
                inf_arr[j] += curr_input[j]
        return sparsity(inf_arr)

    def print_info(self, fo):
        fo.write("[" + ','.join(str(x) for x in self.vec) + "]\t")
        fo.write("[" + ','.join(str(x) for x in self.hat) + "]\t")
        fo.write(str(self.deg) + "\t")
        fo.write(str(self.signature) + "\t")
        fo.write(str(self.ssignature) + "\t")
        fo.write(str(self.nInfVar) + "\n")

    def transform(self, mat):
        mult_m_v(mat, self.vec, self.hat)
        self.deg = self.__degree()
        self.nInfVar = self.__num_inf_var()
        abs_hat = map(abs, self.hat)
        sorted_hat = sorted(abs_hat)
        sorted_hat_signed = sorted(self.hat)
        sorted_hat_str = map(str, sorted_hat)
        sorted_hat_signed_str = map(str, sorted_hat_signed)
        self.signature = ','.join(sorted_hat_str)
        self.ssignature = ','.join(sorted_hat_signed_str)
