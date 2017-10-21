#!/usr/bin/env Rscript

distance <- function(x1,y1,x2,y2){
  
  dx = x1-x2
  dy = y1-y2
  
  d = sqrt(dx*dx + dy*dy)
  
  return(d)
}

# holds the values of all distances in a given pointcloud
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

# Dx and Dy are the matrices of distances of all points 
# in pointcloud x and y respectively
# eps > 0 ensures that D is pos definite
createDMatrix <- function(Dx,Dy,eps){
  #print(paste0(nrow(Dx)," ",nrow(Dy)))
  
  D <- matrix(0,length(Dx),length(Dy))
  
  diag(D) <- eps
  
  for(i in 1:nrow(Dx)){
    for(i_prime in 1:ncol(Dx)){
      for(j in 1:nrow(Dy)){
        for(j_prime in 1:ncol(Dy)){
          #print(paste0(j, ";", j_prime))
          D[i_prime+(i-1)*3, j_prime+(j-1)*3] = D[i_prime+(i-1)*3, j_prime+(j-1)*3] +
            (Dx[i,i_prime] - Dy[j,j_prime])*(Dx[i,i_prime] - Dy[j,j_prime]);
        }
      }
    }
  }
  
  return(D)
}

createAMatrix <- function(xSize, ySize){
  
  A <- matrix(0,xSize + ySize,xSize*ySize)
  
  # row constraints
  for(i in 1:xSize){
    for(j in 1:ySize){
      A[i,j+(i-1)*ySize] = 1
    }
  }
  
  # column constraints
  for(i in (xSize+1):nrow(A)){
    for(j in 1:ncol(A)){
      #print(paste0("j%%ySize", j%%ySize, " i-xSize ", i-xSize))
      if(j%%ySize == (i-xSize)%%ySize){
        A[i,j] = 1
      }
    }
  }
  
  return(A)
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

library(quadprog)

b_0 = c(measure1,measure2)

# must be a (2*6)x9-matrix
# A = matrix(
#   c(1,1,1, 0,0,0, 0,0,0,
#     0,0,0, 1,1,1, 0,0,0,
#     0,0,0, 0,0,0, 1,1,1,
#     
#     1,0,0, 1,0,0, 1,0,0,
#     0,1,0, 0,1,0, 0,1,0,
#     0,0,1, 0,0,1, 0,0,1), # the data elements 
#   nrow=6,              # number of rows 
#   ncol=9,              # number of columns 
#   byrow = TRUE)


Dmat = createDMatrix(distances1,distances2,50000000)
Dmat
dvec       <- c(rep(0,length(measure1)*length(measure2)))

A = createAMatrix(length(measure1),length(measure2))
sol <- solve.QP(Dmat,dvec,t(A),bvec=b_0,meq = nrow(A))





out = matrix(sol$solution, nrow=length(measure1), ncol=length(measure2))
write.table(t(out), file="mymatrix.csv", row.names=FALSE, col.names=FALSE, sep = ";")


