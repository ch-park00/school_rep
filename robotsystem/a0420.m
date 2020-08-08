%%
clear all;
Nsamples=41500;
EulerSaved=zeros(Nsamples,2);

for k=1:Nsamples
    [ax ay]=GetAccel();
    [phi theta]=EulerAccel(ax,ay);
    
    EulerSaved(k,:)=[phi theta];
end

phisaved=EulerSaved(:,1)*180/pi;
thetasaved=EulerSaved(:,2)*180/pi;

dt=0.01;
t=0:dt:(Nsamples-1)*dt;
figure(1);
plot(t,phisaved);xlabel('Time (sec)');ylabel('Roll angle (deg)');

figure(2);
plot(t,thetasaved);xlabel('Time (sec)');ylabel('Pitch angle (deg)');