from random import randint

TESTS = [ ( 2 , 5 ) , ( 7 ,7 ) , ( 40 ,21) ]
for i , (n,m) in enumerate(TESTS):
    _file = open("test-{0}-{1}".format(n,m), "w" )
    _str = "{0} {1} ".format(n ,m)
    for __ in range(m):
        for _ in range(n):
            _str += "{0} ".format(randint(-10,10))
    _file.write( _str )
