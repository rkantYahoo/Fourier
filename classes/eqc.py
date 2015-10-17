from classes.function import Function

class EqCF(object):
    def __init__(self, name, order, vec_dim, mat, wt_vec):
        self.name = str(name)
        self.order = order
        self.dimension = vec_dim
        self.rep = Function(name, order, vec_dim)
        self.names = set([name])

        self.rep.transform(mat)
        self.rep.compute_entropy_influence(wt_vec)
        self.signature = self.rep.signature


    def is_present(self, name):
        if name in self.names:
            return 1
        return 0

    def add(self, name):
        self.names.add(str(name))

    def add_safe(self, name, mat):
        func = Function(name, self.order, self.dimension)
        func.transform(mat)
        if func.signature == self.signature:
            self.add(name)

    def print_names_to_file(self, fo, delim):
        for name in self.names:
            fo.write(name + delim)

