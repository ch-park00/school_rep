%%
clear all;
Nsamples=41500;
EulerSaved=zeros(Nsamples,3);
dt=0.01;
for k=1:Nsamples
    [p q r]=Getgyro();
    A=eye(4)+dt*1/2*[0 -p -q -r;p 0 r -q;q -r 0 p;r q -p 0;];
    [ax,ay]=GetAccel();
    [phi,theta]=EulerAccel(ax,ay);
    z=EulerToQuaternion(phi,theta,0);
    [phi,theta,psi]=EulerKalman(A,z);
    EulerSaved(k,:)=[phi theta psi];
end

phisaved=EulerSaved(:,1)*180/pi;
thetasaved=EulerSaved(:,2)*180/pi;
psisaved=EulerSaved(:,3)*180/pi;

t=0:dt:(Nsamples-1)*dt;
figure(1);
plot(t,phisaved);xlabel('Time (sec)');ylabel('Roll angle (deg)');

figure(2);
plot(t,thetasaved);xlabel('Time (sec)');ylabel('Pitch angle (deg)');