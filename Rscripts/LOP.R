install.packages("boot")
library(boot)

a <- c(2500, 3500)
A2 <- matrix(c(50, 150, 500, 250), ncol=2, nrow=2, byrow=TRUE)
b2 <- c(900, 2500)
simplex(a, A2 = A2, b2 = b2, maxi=FALSE)


install.packages("linprog")
library(linprog)

A <- matrix(c(-50,-150,-500,-250),nrow=2,ncol=2,byrow=TRUE)
a <- c(2500, 3500)
b <- c(-900, -2500)
solveLP(a,b,A,maximum=FALSE)




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
a <- c(0,0,0,0,1,1)
b_0 <- c(0.5,0.5,0.5,0.5, 1,1,  -0.5,-0.5,-0.5,-0.5, -1,-1)
sol <- solveLP(a,b_0,A,maximum=FALSE)
sol$solution

out = matrix(sol$solution, nrow=2, ncol=2)

setwd("/home/willy/8.Semester/Liebscher/OptimalTransport/MatchingMeasures/")
write.table(out, file="mymatrix.csv", row.names=FALSE, col.names=FALSE, sep = ";")


