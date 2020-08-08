%%
dt=0.1;
t=0:dt:10;
Nsamples=length(t);
Xsaved=zeros(Nsamples,2);
DeXsaved=zeros(Nsamples,2);
Zsaved=zeros(Nsamples,1);

for k=1:Nsamples
    [z vel]=GetPos();
    [dpos dvel]=DeDvKalman(z);
    [pos vel1]=DvKalman(z);
    
    Xsaved(k,:)=[pos vel1];
    Zsaved(k,:)=z;
    DeXsaved(k,:)=[dpos dvel];
end

figure;hold on;
plot(t,Xsaved(:,1),'ro');
plot(t,DeXsaved(:,1));
xlabel('Time (sec)');
ylabel('position (P)');
legend('matrix', 'Decomposed');

figure;plot(t,Xsaved(:,2),'ro');hold on;
plot(t,DeXsaved(:,2));xlabel('Time (sec)');
ylabel('Velocity (m/s)');
legend('matrix', 'decomposed');

%%
clear all;
NoOfImg=24;
Xmsaved=zeros(2,NoOfImg);
Xhsaved=zeros(2,NoOfImg);
Xcsaved=zeros(2,NoOfImg);
figure(1)
for k=1:NoOfImg
    [xm,ym,rx,ry]=GetBallPos(k);
    [xh,yh]=TrackKalman(xm,ym);
    
    hold on;
    plot(xm,ym,'r*');
    plot(xh,yh,'bs');
    pause(1)
    
    Xmsaved(:,k)=[xm ym]';
    Xhsaved(:,k)=[xh yh]';
    Xcsaved(:,k)=[rx ry]';
end
figure(2);hold on;
plot(Xmsaved(1,:),Xmsaved(2,:),'r*');
plot(Xhsaved(1,:),Xhsaved(2,:),'bs');
set(gca,'Ydir','reverse');
legend('Object Detection','Kalman Filtere tracking');
box on;
xlabel('x (pixel)');ylabel('y (pixel)');

%%
t=1:NoOfImg;
x1=Xmsaved(1,:);
x2=Xhsaved(1,:);
x3=Xcsaved(1,:);
y1=Xmsaved(2,:);
y2=Xhsaved(2,:);
y3=Xcsaved(2,:);
figure;hold on;plot(t,x1,'r');plot(t,x2,'b');plot(t,x3,'k')
legend('detection','kalman','real');xlabel('sample Number'),ylabel(' x value (pixel)');

figure;hold on;plot(t,y1,'r');plot(t,y2,'b');plot(t,y3,'k')
legend('detection','kalman','real','Location','northwest');xlabel('sample Number'),ylabel(' y value (pixel)');

