dat=read.table("data.txt")
dat
plot(dat,type="p",main="Корреляционное поле",xlab="X",ylab="Y")

disp <- var (dat[,1])
sigma <- sqrt (disp)
sr <- mean (dat[,1])

gr1 <- subset (dat[,1], (dat[,1] >= (sr-sigma)) & (dat[,1] <= (sr+sigma)))
gr2 <- subset (dat[,1], (dat[,1] >= (sr-2*sigma)) & (dat[,1] <= (sr+2*sigma)))
gr3 <- subset (dat[,1], (dat[,1] >= (sr-3*sigma)) & (dat[,1] <= (sr+3*sigma)))

table2 <- matrix (0, 3, 5)

table2[1:3,1] <- c (sr-sigma, sr-2*sigma, sr-3*sigma)
table2[1:3,2] <- c (sr+sigma, sr+2*sigma, sr+3*sigma)
table2[1:3,3] <- c (length (gr1), length (gr2), length(gr3))
table2[1:3,4] <- table2[1:3,3]/length (dat[,1]) * 100
table2[1:3,5] <- c (68.3, 95.4, 99.7)

table2

range <- max (dat[,1]) - min (dat[,1])
k <- 1 + floor (log (length (dat[,1]), 2))       #number of groups
h <- range / k                                   #interval length

sorted <- sort (dat[,1])

table3 <- matrix (0, k, 5)

for (i in 0:(k-1)) {
  l <- sorted[1] + i * h
  r <- sorted[1] + (i + 1) * h
  gr <- subset (dat[,2], dat[,1]>=l & (dat[,1] < r | i == k - 1 & dat[,1] <= r))
  table3[i+1, 1:5] <- c(sorted[1]+i*h, sorted[1]+(i+1)*h, length (gr), sum (gr), mean (gr))
}

table3

v <- length(dat[,1]) - 2                          # число степеней свободы
corcof <- cor(dat[,1], dat[,2])                   # коэффициент корреляции
t <- abs (corcof) * sqrt (v / (1 - corcof ^2))    # значимость корреляции

corcof
t
lm (dat[,2]~dat[,1])     # basic linear model

n <- length(dat[,1])
b <- ( sum(dat[,1])*sum(dat[,2])/n - sum(dat[,1]*dat[,2]) ) / (sum(dat[,1])^2/n-sum(dat[,1]*dat[,1]))
b
a<-mean(dat[,2])-b*mean(dat[,1])
a

lines(dat[,1],a+b*dat[,1])
