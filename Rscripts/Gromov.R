install.packages("quadprog")
library(quadprog)

## EXAMPLE:
## Assume we want to minimize: -(0 5 0) %*% b + 1/2 b^T b
## under the constraints:      A^T b >= b0
## with b0 = (-8,2,0)^T
## and      (-4  2  0)
##      A = (-3  1 -2)
##          ( 0  0  1)
## we can use solve.QP as follows:
##
Dmat       <- matrix(0,3,3)
diag(Dmat) <- 1
dvec       <- c(0,5,0)
Amat       <- matrix(c(-4,-3,0,2,1,0,0,-2,1),3,3)
bvec       <- c(-8,2,0)
solve.QP(Dmat,dvec,Amat,bvec=bvec)


mue_x = c(0.5,0.5)
mue_y = c(0.5,0.5)

b_0 <- c(0.5,0.5,0.5,0.5, 1,1,  -0.5,-0.5,-0.5,-0.5, -1,-1)
??solve.QP


A = matrix( 
  c(1,1,0,0,0,0,
    0,0,1,1,0,0,
    1,0,1,0,0,0,
    0,1,0,1,0,0,
    0,0,0,0,1,0,
    0,0,0,0,0,1,
    
    -1,-1,0,0,0,0,
    0,0,-1,-1,0,0,
    -1,0,-1,0,0,0,
    0,-1,0,-1,0,0,
    0,0,0,0,-1,0,
    0,0,0,0,0,-1), # the data elements 
  nrow=12,              # number of rows 
  ncol=6,              # number of columns 
  byrow = TRUE)
A

D = matrix( 
  c(0,0,0,0,0,0,
    0,0,0,0,0,0,
    0,0,0,0,0,0,
    0,0,0,0,0,0,
    0,0,0,0,1,0,
    0,0,0,0,0,1), # the data elements 
  nrow=6,              # number of rows 
  ncol=6,              # number of columns 
  byrow = TRUE)

install.packages("matrixcalc")
library(matrixcalc)
D

Dmat       <- matrix(1,3,3)
diag(Dmat) <- 1

is.positive.definite(Dmat)


dvec = c(rep(0,6))
dvec

solve.QP(D,dvec,t(A),bvec=b_0)



