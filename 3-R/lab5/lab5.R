dat<-read.table("data5.txt")
dat
plot(dat,type="p",main="Дыяграма рассеяння")

# Разбіваем на два кластэры
cl<-kmeans(dat,2)
table(cl$cluster)
# Цэнтры кластараў
cl$centers
# Кластары на графіку рознымі колерамі
plot(dat,col=ifelse(cl$cluster==1,"blue","green"))
legend("bottomleft",legend=c("1","2"),fill=c("blue","green"))
plot(dat,pch=ifelse(cl$cluster==1,1,2))
legend("bottomleft",legend=c("1","2"),pch=c(1,2))

# Разбіваем на тры кластэры
cl<-kmeans(dat,3)
table(cl$cluster)
cl$centers
plot(dat,col=ifelse(cl$cluster==1,"blue", ifelse(cl$cluster == 2, "green", "red")))
legend("bottomleft",legend=c("1","2", "3"),fill=c("blue","green","red"))
plot(dat,pch=ifelse(cl$cluster==1, 1, ifelse(cl$cluster == 2, 2,3)))
legend("bottomleft",legend=c("1","2", "3"),pch=c(1,2, 3))