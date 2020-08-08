%%
clear all;
dt=0.2;
t=0:dt:10;

Nsamples=length(t);

Avgsaved=zeros(Nsamples,1);
Xmsaved=zeros(Nsamples,1);

for k=1:Nsamples
    
    xm=GetVolt();
    avg=avgFilter(xm);
    
    Avgsaved(k)=avg;
    Xmsaved(k)=xm;
end
figure();
plot(t,Xmsaved,'r:*');
hold on;
plot(t,Avgsaved,'o-');
xlabel('Time (sec)');
ylabel('Voltage (V)');
legend('Raw data','Filtered data');

%%
clear all;
Nsamples=500;
Xsaved=zeros(Nsamples,1);
Xmsaved=zeros(Nsamples,1);

for k=1:Nsamples
    xm=GetSonar();
    x=avgFilter(xm);
    Xsaved(k)=x;
    Xmsaved(k)=xm;
end

dt=0.02;
t=0:dt:(Nsamples-1)*dt;

figure();
plot(t,Xmsaved,'r.');hold on;plot(t,Xsaved,'b');
legend('Measured','Average Filter');
xlabel('Time (sec)');
ylabel('Distance (cm)');
box on;

%%
clear all;
Nsamples=500;
Xsaved=zeros(Nsamples,1);
Xmsaved=zeros(Nsamples,1);

for k=1:Nsamples
    xm=GetSonar();
    x=MovAvgFilter(xm);
    Xsaved(k)=x;
    Xmsaved(k)=xm;
end

dt=0.02;
t=0:dt:(Nsamples-1)*dt;

figure();
plot(t,Xmsaved,'r.');hold on;plot(t,Xsaved,'b');
legend('Measured','Moving Filter');
xlabel('Time (sec)');
ylabel('Distance (cm)');
box on;

%%
clear all;
Nsamples=500;
Xsaved=zeros(Nsamples,1);
Xmsaved=zeros(Nsamples,1);

for k=1:Nsamples
    xm=GetSonar();
    x=LPF(xm);
    
    Xsaved(k)=x;
    Xmsaved(k)=xm;
end

dt=0.02;
t=0:dt:(Nsamples-1)*dt;

figure();
plot(t,Xmsaved,'r.');hold on;plot(t,Xsaved,'b');
legend('Measured','LPF');
box on;
xlabel('Time (sec)');
ylabel('Distance (cm)');

