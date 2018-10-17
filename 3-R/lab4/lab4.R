dat<-read.table("data4.txt")
dat

# Сярэдні ўзровень шэрагу дынамікі
mediumlevel<-mean(dat[,2])         
mediumlevel

# Будуем шэраг для крытэра серый
result<-numeric()                      
for(i in 1:length(dat[,2])) {
  if(dat[i,2]>mediumlevel) result<-c(result, 1)
  if(dat[i,2]<mediumlevel) result<-c(result, 0)
}
result

# Лічым колькасць серый
numberofseries<-1
var<-result[1]
for(i in 2:length(result)) {
  if(result[i]!=var) {
    numberofseries<-numberofseries+1
    var<-result[i]
  }
}
numberofseries

#Правяраем прыналежнасць колькасці серый інтэрвалу
left<-as.integer((length(result)+1)/2-1.96*sqrt(length(result)-1)/2)
left
right<-as.integer((length(result)+1)/2+1.96*sqrt(length(result)-1)/2)
right
if(left<=numberofseries & numberofseries<=right) {
  answer<-"Заканамернасці ў змяненні ўзроўняў няма"
} else {
  answer<-"Заканамернасць ў змяненні ўзроўняў назіраецца"
}
answer

# Згладжванне шэрага дынамікі метадам трохузроўневай слізгальнай простай
y<-dat[,2]
smoothed<-numeric()
smoothed<-c(smoothed, (5*y[1]+2*y[2]-y[3])/6)
for(i in 2:(length(dat[,1])-1)) {
  smoothed<-c(smoothed, (y[i-1]+y[i]+y[i+1])/3)
}
smoothed<-c(smoothed, (5*y[length(dat[,1])-1]+2*y[length(dat[,1])-2]-y[length(dat[,1])-3])/6)
smoothed

# Згладжванне шэрага дынамікі метадам аналітычнага выраўнівання па ўраўненню простай
t<-numeric()
temp<-((-1)*as.integer(length(y)/2))
as.integer(length(y)/2)
for(i in 1:length(y)) {
  t<-c(t, temp)
  temp<-temp+1
  if(temp==0) temp<-temp+1
}
dat[,3]<-t
dat[,4]<-t*t
dat[,5]<-dat[,2]*dat[,3]
colnames(dat)<-c("x", "y", "t", "t^2", "y*t")
dat

a0<-sum(dat[,2]/length(dat[,2]))
a1<-sum(dat[,5])/sum(dat[,4])
eq<-paste("y(t)=", a0, "+", a1, "t")
eq

analyticsmoothed<-numeric()
for(i in 1:length(dat[,2])) {
  analyticsmoothed<-c(analyticsmoothed, a0+a1*(i-as.integer(length(y)/2)))
}

# Робім прагноз
nextT<-max(t)+1
nextT
yNext<-a0+a1*nextT
yNext

# Малюем графікі
graph1<-function(x) dat[,2]
graph2<-function(x) smoothed
graph3<-function(x) analyticsmoothed
matplot(dat[,1],cbind(graph1(x),graph2(x), graph3(x)),type="l",col=c("blue","red", "green"), xlab="Год", ylab="Паказчык")
legend(x="topright", y=0.92, legend=c("Зыходны", "Трохузроўневай сярэдняй", "Аналітычным выраўніваннем"), lty=c(1,1,1), lwd=c(2.5,2.5,2.5), col=c("blue", "red", "green"))