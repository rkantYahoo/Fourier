import unittest
from classes.function import Function
from utils.utils import *

__author__ = 'Ravi'


class FunctionTestCase(unittest.TestCase):
    def setUp(self):
        self.name = 6

        self.func1 = Function(self.name, 2, 4)

        self.had1 = []
        create_had(self.had1, 2, 4)
        self.wt_vec1 = array('i', [])
        create_wt_vec(self.wt_vec1, 4)

        self.func1.transform(self.had1)
        self.func1.compute_entropy_influence(self.wt_vec1)

        self.func2 = Function(self.name, 3, 8)

        self.had2 = []
        create_had(self.had2, 3, 8)
        self.wt_vec2 = array('i', [])
        create_wt_vec(self.wt_vec2, 8)

        self.func2.transform(self.had2)
        self.func2.compute_entropy_influence(self.wt_vec2)


    def tearDown(self):
        self.func1 = None
        self.func2 = None
        self.had1 = None
        self.had2 = None

    def test_degree(self):
        self.assertEqual(self.func1.deg, 2,
                         'degree 2 expected, received ' +
                         str(self.func1.deg))
        self.assertEqual(self.func2.deg, 3,
                         'degree 3 expected, received ' +
                         str(self.func2.deg))

    def test_signature(self):
        self.assertEqual(self.func1.signature, '0,0,0,4',
                         'Wrong signature in case 1: ' +
                         str(self.func1.signature))
        self.assertEqual(self.func2.signature, '0,0,0,0,4,4,4,4',
                         'Wrong signature in case 2: ' +
                         str(self.func2.signature))

    def test_ssignature(self):
        self.assertEqual(self.func1.ssignature, '0,0,0,4',
                         'Wrong ssignature in case 1: ' +
                         str(self.func1.ssignature))
        self.assertEqual(self.func2.ssignature, '-4,0,0,0,0,4,4,4',
                         'Wrong ssignature in case 2: ' +
                         str(self.func2.ssignature))

    def test_entropy(self):
        self.assertEqual(self.func1.fEntropy, 0,
                         'Wrong entropy in case 1: ' + str(self.func1.fEntropy))
        self.assertEqual(self.func2.fEntropy, 2,
                         'Wrong entropy in case 2: ' + str(self.func2.fEntropy))

    def test_influence(self):
        self.assertEqual(self.func1.tInf, 2,
                         'Wrong tInf in case 1: ' + str(self.func1.tInf))
        self.assertEqual(self.func2.tInf, 1.5,
                         'Wrong tInf in case 2: ' + str(self.func2.fEntropy))


suite = unittest.TestLoader().loadTestsFromTestCase(FunctionTestCase)

if __name__ == '__main__':
    unittest.main()

