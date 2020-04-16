import numpy as np
from os import system
import difflib


if __name__ == '__main__':


    def write_matrix( _matrix, _filename, shape = True ):
        hist = " ".join( str(i) for i in  _matrix.shape) + "\n" if shape else " "
        open( _filename , "w" ).write( \
             hist + " ".join( str(i) for i in _matrix.ravel() ))

    def _call(_filename_in, _filename_outs ):
        system( ".\\bin\\svdlib.exe  {0} {1}".format(_filename_in, " ".join( _filename_outs) ))


    hists = [ "./tests/svd/{2}/svd-u/", "./tests/svd/{2}/svd-s", "./tests/svd/{2}/svd-vh/" ]
    for i in range(1 , 10):
        for j in range(1 , 10):
            _matrix = np.random.randn(i, j)
            _filename_in  = "./tests/svd/test-svd-{0}-{1}"
            _filename_out = "./tests/svd/out/test-svd-{0}-{1}"
            write_matrix( _matrix, _filename_in.format(i,j))
            u, s, vh = np.linalg.svd( _matrix, full_matrices = True )

            for uu , _file in zip( [u, s, vh ], hists):
                write_matrix( uu,   (_file + "/svd-{0}-{1}").format(i,j , "in"), shape = False)

            _outs = [ (hist + "/svd-{0}-{1}").format(i,j, "out") for hist in hists ]
            _call( _filename_in.format(i,j), _outs )
