class unionfind:
    def __init__(self, n):
        self._n = n
        self.parent_or_size = [-1] * n
    
    def merge(self, a, b):
        assert 0 <= a < self._n
        assert 0 <= b < self._n
        x,y = self.leader(a),self.leader(b)
        if x == y:return x
        if -self.parent_or_size[x] < -self.parent_or_size[y]:x,y = y,x
        self.parent_or_size[x] += self.parent_or_size[y]
        self.parent_or_size[y] = x
        return x
    
    def leader(self, a):
        assert 0 <= a < self._n
        if self.parent_or_size[a] < 0: return a
        self.parent_or_size[a] = self.leader(self.parent_or_size[a])
        return self.parent_or_size[a]
    
    def same(self, a, b):
        assert 0 <= a < self._n
        assert 0 <= b < self._n
        return self.leader(a) == self.leader(b)
    
    def size(self, a):
        assert 0 <= a < self._n
        return -self.parent_or_size[self.leader(a)]
    
    def groups(self):
        leader_buf = [self.leader(i) for i in range(self._n)]
        result = [[] for _ in range(self._n)]
        for i in range(self._n): result[leader_buf[i]].append(i)
        return [r for r in result if r != []]


# https://old.yosupo.jp/problem/unionfind
n,q = map(int,input().split())
uf = unionfind(n)
for _ in range(q):
    t,u,v = map(int,input().split())
    if t:
        print(1 if uf.same(u,v) else 0)
    else:
        uf.merge(u,v)