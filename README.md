Linear Regression
======
efficiently linear regression ``` O( n^2 log( √n/ε ) ) ``` Time algorithm ( ε-accuracy ).
an Hebrew analyze of the time running could be found here : https://github.com/dudupo/linear-regression/blob/master/svd.pdf

I have 'copy-pasted' the document as it was, directly from assignment, so it might seem strange (for who is't an exercises examiner). I hope to update the manner in future.

currently, it's not working (yet), and has a buggy nature. As a first step I focusing on demonstrate a polynomial regression. after that I planning to improve the code by constant Time factor, and 'righter cpp literary'.


## Issuses

### (I) reordering the vectors of the orthonormal matrix 
the svd decompaction, calculating the vectors by ascending order ( matched to the eigenvalue ), currently there is no regard to the subject while assembling back. 
### (II) results of polynomial regression aren't even similar to the expectations.     

## Testing
note that you might want to decrease the of the matrix.
```
mingw32-make
python ./scripts/svdtest_gen.py
python ./scripts/svdtest_run.py
 ```
 
 
