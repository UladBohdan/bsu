library(MASS)
x1<-rnorm(20,mean = 0,sd = 6/3)    # мат чаканне 0
y1<-rnorm(20,0,6/3)
x2<-rnorm(10,6,6/3)         # мат чаканне 6
y2<-rnorm(10,6,6/3)
xy<-cbind(c(x1, x2),c(y1, y2))
xy

n<-30
n.train<-floor(n*0.7)   # абучальная выбарка
n.test<-n-n.train       # тэставая выбарка

idx.train<-sample(1:n,n.train)   # выпадковы выбар індэксаў
idx.test<-(1:n)[!(1:n %in% idx.train)]    # выбраць рэшту ў тэставую выбарку

data.train<-xy[idx.train,]   #абіраем дадзеныя па атрыманых раней рандомных індэксах
data.test<-xy[idx.test,] 

# першы выпадак
cl<-kmeans(xy,2)              # праводзім кластарны аналіз для пачатковых дадзеных
cl.cluster<-cl$cluster
cl.train<-cl.cluster[idx.train]
cl.test<-cl.cluster[idx.test]

mod<-qda(data.train, cl.train)                 # абучэнне тэставай выбаркі
cl.test_est<-predict(mod, data.test)$class     # класіфікацыя атрыманых дадзеных
sum(cl.test_est!=cl.test)/n.test               # падлічваем памылку
idx<-idx.test[cl.test_est!=cl.test]            # выбіраем індэксы не адпаведныя сапраўднасці

# першы графік
plot(xy, type="n")
points(data.train,pch=24, col=ifelse(cl.train==1,"blue","green"))
legend("topleft",legend=c("train 1","train 2"),pch=24,col=c("blue","green"))
points(data.test,pch=21, col=ifelse(cl.test==1,"blue","green"))
legend("bottomright",legend=c("test 1","test 2"),pch=21,col=c("blue","green"))
if (length(idx)==1){
  points(xy[idx,1],xy[idx,2],col="red", pch=4) 
}else
  points(xy[idx,],col="red", pch=4)
legend("bottom",legend=c("wrong"),pch=4,col="red")


# другі выпадак
idd<-sample(1:n.train,n.train * 0.2)  # выбіраем індэксы 20% абучальнай
for(i in idd) 
  cl.train[i]=ifelse(cl.train[i]==1,2,1)  # інверсуем нумары кластараў

mod2<-qda(data.train, cl.train)                  # абучэнне тэставай выбаркі
cl.test_est<-predict(mod2, data.test)$class      # класіфікацыя атрыманых дадзеных
sum(cl.test_est!=cl.test)/n.test                 # падлічваем памылку
idx2<-idx.test[cl.test_est!=cl.test]             # выбіраем індэксы не адпаведныя сапраўднасці

# другі графік
plot(xy, type="n")
points(data.train,pch=24, col=ifelse(cl.train==1,"blue","green"))
legend("topleft",legend=c("train 1","train 2"),pch=24,col=c("blue","green"))
points(data.test,pch=21, col=ifelse(cl.test==1,"blue","green"))
legend("bottomright",legend=c("test 1","test 2"),pch=21,col=c("blue","green"))
if (length(idx2)==1){
  points(xy[idx2,1],xy[idx2,2],col="red", pch=4) 
}else
  points(xy[idx2,],col="red", pch=4)
legend("bottom",legend=c("wrong"),pch=4,col="red")

