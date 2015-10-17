from classes.function import Function

class EqCF(object):
    def __init__(self, func, is_verbose):
        self.name = func.name
        self.order = func.order
        self.dimension = func.dimension
        self.verbose = is_verbose
        self.rep = func
        self.funcs = [func]
        self.names = set([func.name])
        self.signature = func.signature


    def is_present(self, name):
        if name in self.names:
            return 1
        return 0

    def add(self, name):
        if self.verbose == 1:
            return
        self.names.add(str(name))

    def add_safe(self, name, mat):
        if self.verbose == 1:
            return
        func = Function(name, self.order, self.dimension)
        func.transform(mat)
        if func.signature == self.signature:
            self.add(name)

    def add_verbose(self, func):
        self.funcs.append(func)
        self.add(func.name)

    def print_names_to_file(self, fo, delim):
        for name in self.names:
            fo.write(name + delim)

    def print_to_file(self, fo):
        for func in self.funcs:
            func.print_info(fo)
        fo.write("\n")

