%%
clear all;
Nsamples=41500;
EulerSaved=zeros(Nsamples,3);

dt=0.01;
for k=1:Nsamples
    [p q r]=Getgyro();
    [phi theta psi]=EulerGyro(p,q,r,dt);
    
    EulerSaved(k,:)=[phi theta psi];
end

Phisaved=EulerSaved(:,1)*180/pi;
Thetasaved=EulerSaved(:,2)*180/pi;
Psisaved=EulerSaved(:,3)*180/pi;

t=0:dt:(Nsamples-1)*dt;
figure(1);plot(t,Phisaved);
figure(2);plot(t,Thetasaved);
figure(3);plot(t,Psisaved);