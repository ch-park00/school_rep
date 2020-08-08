%%
clear;clc
dt=0.01;t=0:dt:15;
ks1=0.1;ks2=1;ks3=7;
imp1=impulse(tf([0 0 ks1],[1 0.5 ks1]),t);
imp2=impulse(tf([0 0 ks2],[1 0.5 ks2]),t);
imp3=impulse(tf([0 0 ks3],[1 0.5 ks3]),t);

r=ones(1,length(t));
y1=conv(r,imp1)*dt;
y2=conv(r,imp2)*dt;
y3=conv(r,imp3)*dt;
figure(1);clf;
plot(t,r,'r','LineWidth',2);hold on;
plot(t,y1(1:length(t)),'r--','Linewidth',2);
plot(t,y2(1:length(t)),'b','Linewidth',2);
plot(t,y3(1:length(t)),'k--','Linewidth',2);
xlabel('Time (s)');ylabel('\theta(t)');