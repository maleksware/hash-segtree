import random
alphabet = "qwertyuiopasdfghjklzxvbnm"

step = 1000
maxval = 10 ** 6


for i in range(step, maxval + 1, step):
    for q in range(3):
        with open(f"tests/qp/test{i}_{q}.in", "w") as f:
            string_length = i
            print(string_length, file=f)
            s = ""
            for j in range(string_length):
                s += random.choice(alphabet)
            print(s, file=f)
            k = maxval
            print(k, file=f)
            for j in range(k):
                qtype = random.randint(1, 2)
                if qtype == 1:
                    a = random.randint(0, len(s) - 1)
                    b = random.randint(a + 1, len(s)) # [l; r)

                    print(1, a, b, file=f)
                else:
                    l = random.randint(0, len(s) - 1)
                    print(2, l, random.choice(alphabet), file=f)

    print(f"QP: generated group {i}")

print("FINISHED QP GENERATION")

for i in range(step, maxval + 1, step):
    for q in range(3):
        with open(f"tests/ln/test{i}_{q}.in", "w") as f:
            string_length = maxval
            print(string_length, file=f)
            s = ""
            for j in range(string_length):
                s += random.choice(alphabet)
            print(s, file=f)
            k = i
            print(k, file=f)
            for j in range(k):
                qtype = random.randint(1, 2)
                if qtype == 1:
                    a = random.randint(0, len(s) - 1)
                    b = random.randint(a + 1, len(s)) # [l; r)
                    
                    print(1, a, b, file=f)
                else:
                    l = random.randint(0, len(s) - 1)
                    print(2, l, random.choice(alphabet), file=f)

    print(f"LN: generated group {i}")

print("FINISHED LN GENERATION")

