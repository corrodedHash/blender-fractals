import fractal
v, e = fractal.x("grammars/bla.txt", 4)
for i in range(10):
    print(" ".join([str(v[i][j]) for j in range(3)]))
print("ayyy")
for i in range(10):
    print(" ".join([str(e[i][j]) for j in range(2)]))
