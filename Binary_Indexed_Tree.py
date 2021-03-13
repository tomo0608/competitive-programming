class Binary_Indexed_Tree:
    def __init__(self, n):
        self._n = n
        self.data = [0] * n
    
    def add(self, p, x):
        assert 0 <= p < self._n
        p += 1
        while p <= self._n:
            self.data[p-1] += x
            p += p & -p
    
    def sum(self, l, r):
        assert 0 <= l <= r <= self._n
        return self._sum(r) - self._sum(l)
    
    def _sum(self, x):
        s = 0
        while x > 0:
            s += self.data[x-1]
            x -= x & -x
        return s