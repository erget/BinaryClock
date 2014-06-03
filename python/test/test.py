'''
Unit tests on iwes_package
'''

import unittest

from bin_clock import Binary, NegativeBinaryError

class BinaryTests(unittest.TestCase):

    """Tests for ``Binary``"""

    def test_known_values(self):
        """Binary has values matching passed decimal number."""
        self.assertEqual(str(Binary(4)), "100")
        self.assertEqual(int(Binary(365)), 365)

    def test_incrementing(self):
        """Binary increments correctly."""
        b = Binary()
        self.assertEqual(str(b.increment()), "1")

    def test_decrementing(self):
        """Binary decrements correctly."""
        b = Binary()
        self.assertRaises(NegativeBinaryError, b.decrement)
        b = Binary(10)
        for i in range(9, -1, -1):
            b.decrement()
            self.assertEqual(int(b), i)

    def test_array_length(self):
        """Binary adjusts its length as needed."""
        b = Binary(1)
        b.increment()
        self.assertEqual(len(str(b)), 2)
        b.decrement()
        self.assertEqual(len(str(b)), 1)



if __name__ == "__main__":
    unittest.main()
