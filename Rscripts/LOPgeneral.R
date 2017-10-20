#!/usr/bin/env Rscript

distance <- function(x1,y1,x2,y2){
  
  dx = x1-x2
  dy = y1-y2
  
  d = sqrt(dx*dx + dy*dy)
  
  return(d)
}

createDistMatrix <- function(X,Y){
  
  pointNum = length(X)
  xDistances <- matrix(0,pointNum, pointNum)
  for(i in 1:pointNum){
    for(j in 1:pointNum){
      xDistances[i,j] = distance(X[i],Y[i],
                                 X[j],Y[j])
    }
  }
  
  return(xDistances)
}

createMeasure <- function(X){
  
  pointNum = length(X)
  measure = X
  total = sum(X)
  for(i in 1:pointNum){
    measure[i] = measure[i]/total
  }
  
  return(measure)
}

#---------------------------------------------------------------------------
setwd("/home/willy/8.Semester/Liebscher/OptimalTransport/MatchingMeasures/")

pointCloud1 <- read.table("../PointClouds/pc1.txt", header=FALSE, sep = ";")
# Calculate all pairwise distances
distances1 <- createDistMatrix(pointCloud1$V1, pointCloud1$V2)
measure1 <- createMeasure(pointCloud1$V3)

pointCloud2 <- read.table("../PointClouds/pc2.txt", header=FALSE, sep = ";")
# Calculate all pairwise distances
distances2 <- createDistMatrix(pointCloud2$V1, pointCloud2$V2)
measure2 <- createMeasure(pointCloud2$V3)

library(linprog)

b_0 = c(measure1,measure2, distances1[1,2], distances2[1,2],
        -measure1,-measure2, -distances1[1,2], -distances2[1,2])

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
sol <- solveLP(a,b_0,A,maximum=FALSE)

out = matrix(sol$solution, nrow=2, ncol=2)
write.table(out, file="mymatrix.csv", row.names=FALSE, col.names=FALSE, sep = ";")


# A = matrix(
#   c(1,1,0,0,0,0,
#     0,0,1,1,0,0,
#     1,0,1,0,0,0,
#     0,1,0,1,0,0,
#     0,0,0,0,1,0,
#     0,0,0,0,0,1,
#     
#     -1,-1,0,0,0,0,
#     0,0,-1,-1,0,0,
#     -1,0,-1,0,0,0,
#     0,-1,0,-1,0,0,
#     0,0,0,0,-1,0,
#     0,0,0,0,0,-1), # the data elements 
#   nrow=12,              # number of rows 
#   ncol=6,              # number of columns 
#   byrow = TRUE)
# a <- c(0,0,0,0,1,1)
# b_0 <- c(0.5,0.5,0.5,0.5, 1,1,  -0.5,-0.5,-0.5,-0.5, -1,-1)
# sol <- solveLP(a,b_0,A,maximum=FALSE)
# 
# out = matrix(sol$solution, nrow=2, ncol=2)
# 
# write.table(out, file="mymatrix.csv", row.names=FALSE, col.names=FALSE, sep = ";")


