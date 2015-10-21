from array import array
from utils.utils import *


class Function(object):
    def __init__(self, name, order, vec_dim):
        self.name = name
        self.order = order
        self.dimension = vec_dim
        self.wt = 0
        self.vec = array("i", [])
        self.tvec = array("i", [])
        self.hat = array("i", [])
        self.inf = array("i", [])
        self.deg = 0
        self.nInfVar = 0
        self.fEntropy = 0
        self.tInf = 0
        self.signature = ''
        self.ssignature = ''
        self.__to_func(name, vec_dim)

    def hdist(self, f):
        dist = 0;
        for i in xrange(self.dimension):
            if self.vec[i] != f.vec[i]:
                dist += 1
        return dist

    def min_hdist(self, f_set):
        min = self.dimension
        for f in f_set:
            curr_hdist = self.hdist(f)
            if curr_hdist < min:
                min = curr_hdist
        return min

    def is_eig(self):
        ev = 0.0
        for i in xrange(self.dimension):
            if (self.vec[i] == 0) and (self.hat[i] != 0):
                return 0
            r = float(self.hat[i]/self.vec[i])
            if r == 0.0:
                return 0
            if (ev != 0) and (ev != r):
                return 0
            else:
                ev = r
        return 1

    def is_character(self):
        if self.fEntropy == 0.0:
            return 1
        else:
            return 0

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
                self.tvec.append(i)
                self.wt += 1

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
 #       fo.write(str(self.tInf) + "\t")
        fo.write("[" + ','.join(str(x) for x in self.tvec) + "]\t")
 #       fo.write(str(self.deg) + "\t")
 #       fo.write(str(self.nInfVar) + "\t")
        fo.write("[" + ','.join(str(x) for x in self.hat) + "]\n")
 #       fo.write(str(self.wt) + "\t")
 #       fo.write(str(self.fEntropy) + "\n")
#        fo.write(str(self.signature) + "\t")
#        fo.write(str(self.ssignature) + "\n")

    def display_info(self):
 #       fo.write(str(self.tInf) + "\t")
 #       print("[" + ','.join(str(x) for x in self.tvec) + "]\t")
 #       fo.write(str(self.deg) + "\t")
 #       fo.write(str(self.nInfVar) + "\t")
        print("[" + ','.join(str(x) for x in self.hat) + "]")
 #       fo.write(str(self.wt) + "\t")
 #       fo.write(str(self.fEntropy) + "\n")
#        fo.write(str(self.signature) + "\t")
#        fo.write(str(self.ssignature) + "\n")

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
