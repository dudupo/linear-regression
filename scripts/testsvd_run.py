import numpy as np

def compare(_file1 , _file2):

    x, y = ( np.array([ float( _word ) for _word in open(_file).read().split()])  for _file in [_file1, _file2])

    l = max( x.shape[0] , y.shape[0] )
    x.resize(l)
    y.resize(l)
    r = np.linalg.norm(x - y)
    return r

pre = "./tests/svd/{2}/"
hists = [ "svd-u/", "svd-s/", "svd-vh/" ]
if __name__ == '__main__':
    _file = "svd-{0}-{1}"
    for i in range(10 , 100, 10):
        for j in range(10 , 100 , 10):
            for hist in hists:
                a , b  = ( (pre + hist + _file).format(i, j, z) for z in ["in" , "out"])
                print(" {0} \n -> {1}".format( hist + _file.format(i,j), compare(a, b)))
