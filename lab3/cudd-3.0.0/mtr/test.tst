# TestMtr Version #0.6, Release date 2/6/12
# mtr/testmtr -p 2 ./mtr/test.groups
N=0x7fe8dd402b00 C=0x7fe8dd402b90 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=0
N=0x7fe8dd402b90 C=0x0        Y=0x7fe8dd402bc0 E=0x0        P=0x7fe8dd402b00 F=3 L=0 S=0
N=0x7fe8dd402bc0 C=0x0        Y=0x7fe8dd402b30 E=0x7fe8dd402b90 P=0x7fe8dd402b00 F=4 L=0 S=0
N=0x7fe8dd402b30 C=0x0        Y=0x7fe8dd402b60 E=0x7fe8dd402bc0 P=0x7fe8dd402b00 F=1 L=0 S=0
N=0x7fe8dd402b60 C=0x0        Y=0x0        E=0x7fe8dd402b30 P=0x7fe8dd402b00 F=2 L=0 S=0
#------------------------
N=0x7fe8dd402b00 C=0x0        Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
#  (0,11)

N=0x7fe8dd402b00 C=0x7fe8dd402b30 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
N=0x7fe8dd402b30 C=0x0        Y=0x7fe8dd402b60 E=0x0        P=0x7fe8dd402b00 F=0 L=0 S=6
N=0x7fe8dd402b60 C=0x0        Y=0x0        E=0x7fe8dd402b30 P=0x7fe8dd402b00 F=0 L=6 S=6
#  (0(0,5)(6,11)11)

N=0x7fe8dd402b00 C=0x7fe8dd402c30 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
N=0x7fe8dd402c30 C=0x7fe8dd402b30 Y=0x0        E=0x0        P=0x7fe8dd402b00 F=4 L=0 S=12
N=0x7fe8dd402b30 C=0x7fe8dd402b90 Y=0x7fe8dd402b60 E=0x0        P=0x7fe8dd402c30 F=0 L=0 S=6
N=0x7fe8dd402b90 C=0x0        Y=0x7fe8dd402bc0 E=0x0        P=0x7fe8dd402b30 F=0 L=0 S=2
N=0x7fe8dd402bc0 C=0x0        Y=0x7fe8dd402c00 E=0x7fe8dd402b90 P=0x7fe8dd402b30 F=0 L=2 S=2
N=0x7fe8dd402c00 C=0x0        Y=0x0        E=0x7fe8dd402bc0 P=0x7fe8dd402b30 F=0 L=4 S=2
N=0x7fe8dd402b60 C=0x0        Y=0x0        E=0x7fe8dd402b30 P=0x7fe8dd402c30 F=0 L=6 S=6
#  (0(0(0(0,1)(2,3)(4,5)5)(6,11)11|F)11)

#  (0(0(0,1)(2,3)(4,5)5)(6,11)11|F)
N=0x7fe8dd402b00 C=0x7fe8dd402c30 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
N=0x7fe8dd402c30 C=0x7fe8dd402b90 Y=0x0        E=0x0        P=0x7fe8dd402b00 F=4 L=0 S=12
N=0x7fe8dd402b90 C=0x0        Y=0x7fe8dd402bc0 E=0x0        P=0x7fe8dd402c30 F=0 L=0 S=2
N=0x7fe8dd402bc0 C=0x0        Y=0x7fe8dd402c00 E=0x7fe8dd402b90 P=0x7fe8dd402c30 F=0 L=2 S=2
N=0x7fe8dd402c00 C=0x0        Y=0x7fe8dd402b60 E=0x7fe8dd402bc0 P=0x7fe8dd402c30 F=0 L=4 S=2
N=0x7fe8dd402b60 C=0x0        Y=0x0        E=0x7fe8dd402c00 P=0x7fe8dd402c30 F=0 L=6 S=6
#  (0(0(0,1)(2,3)(4,5)(6,11)11|F)11)

N=0x7fe8dd402b00 C=0x7fe8dd402c30 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
N=0x7fe8dd402c30 C=0x7fe8dd402b90 Y=0x0        E=0x0        P=0x7fe8dd402b00 F=4 L=0 S=12
N=0x7fe8dd402b90 C=0x0        Y=0x7fe8dd402bc0 E=0x0        P=0x7fe8dd402c30 F=0 L=0 S=2
N=0x7fe8dd402bc0 C=0x0        Y=0x7fe8dd402b60 E=0x7fe8dd402b90 P=0x7fe8dd402c30 F=0 L=2 S=2
N=0x7fe8dd402b60 C=0x0        Y=0x7fe8dd402c00 E=0x7fe8dd402bc0 P=0x7fe8dd402c30 F=0 L=4 S=6
N=0x7fe8dd402c00 C=0x0        Y=0x0        E=0x7fe8dd402b60 P=0x7fe8dd402c30 F=0 L=10 S=2
#  (0(0(0,1)(2,3)(4,9)(10,11)11|F)11)
#------------------------
N=0x7fe8dd402b00 C=0x0        Y=0x0        E=0x0        P=0x0        F=0 L=0 S=4
#  (0,3)

N=0x7fe8dd402b00 C=0x7fe8dd402b30 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=4
N=0x7fe8dd402b30 C=0x0        Y=0x7fe8dd402b60 E=0x0        P=0x7fe8dd402b00 F=4 L=0 S=2
N=0x7fe8dd402b60 C=0x0        Y=0x0        E=0x7fe8dd402b30 P=0x7fe8dd402b00 F=4 L=2 S=2
#  (0(0,1|F)(2,3|F)3)

#------------------------
N=0x7fe8dd402b00 C=0x7fe8dd500000 Y=0x0        E=0x0        P=0x0        F=0 L=0 S=12
N=0x7fe8dd500000 C=0x7fe8dd500060 Y=0x7fe8dd500030 E=0x0        P=0x7fe8dd402b00 F=0 L=0 S=6
N=0x7fe8dd500060 C=0x0        Y=0x7fe8dd500090 E=0x0        P=0x7fe8dd500000 F=0 L=0 S=2
N=0x7fe8dd500090 C=0x0        Y=0x7fe8dd5000c0 E=0x7fe8dd500060 P=0x7fe8dd500000 F=0 L=2 S=2
N=0x7fe8dd5000c0 C=0x0        Y=0x0        E=0x7fe8dd500090 P=0x7fe8dd500000 F=0 L=4 S=2
N=0x7fe8dd500030 C=0x0        Y=0x0        E=0x7fe8dd500000 P=0x7fe8dd402b00 F=4 L=6 S=6
#  (0(0(0,1)(2,3)(4,5)5)(6,11|F)11)

