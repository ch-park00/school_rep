%%
clear all;
dt=0.05;
t=0:dt:20;

Nsamples=length(t);
Xsaved=zeros(Nsamples,3);
Zsaved=zeros(Nsamples,1);

for k=1:Nsamples
    r=GetRadar(dt);
    [pos vel alt]=RadarEKF(r,dt);
    
    Xsaved(k,:)=[pos vel alt];
    Zsaved(k)=r;
end

Possaved=Xsaved(:,1);
Velsaved=Xsaved(:,2);
Altsaved=Xsaved(:,3);

t=0:dt:(Nsamples-1)*dt;

figure;
plot(t,Possaved);xlabel('Time (sec)');ylabel('speed [m/s]');
figure;
plot(t,Velsaved);xlabel('Time (sec)');ylabel('Altitude [m]');
figure;
plot(t,Altsaved);xlabel('Time (sec)');ylabel('position [m]');
