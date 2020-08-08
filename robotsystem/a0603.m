%% 201401653 ¹ÚÃ¶Èñ
clear all;
Nsamples=500;

Xsaved=zeros(Nsamples,1);
X1saved=zeros(Nsamples,1);
X2saved=zeros(Nsamples,1);
Xmsaved=zeros(Nsamples,1);
for k=1:Nsamples
    zm=GetSonar();
    x=HPF(zm);
    x1=HPF1(zm);
    x2=HPF2(zm);
    Xsaved(k)=x;
    X1saved(k)=x1;
    X2saved(k)=x2;
    Xmsaved(k)=zm;
end

dt=0.02;
t=0:dt:(Nsamples-1)*dt;

figure;
plot(t,Xmsaved,'r.');hold on;
plot(t,Xsaved,'b');
legend('Measured','HPF','Location','northwest');

figure;
plot(t,Xmsaved,'r.');hold on;
plot(t,Xmsaved-Xsaved,'b');
legend('Measured','Measured-HPF','Location','northwest');

figure;
plot(t,Xmsaved,'r');hold on;
plot(t,Xmsaved-Xsaved,'b');
plot(t,Xmsaved-X1saved,'k');
plot(t,Xmsaved-X2saved,'g');
legend('Measured','tau=0.0233','tau=0.01','tau=0.05','Location','northwest');