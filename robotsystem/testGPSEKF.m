%%
clear all;clc

Nsamples=12990;
dt=0.05;

gpsSaved=zeros(Nsamples,2);
gspEKFSaved=zeros(Nsamples,2);

f_utm_x=290600;
f_utm_y=14139116;

before_h=zeros(Nsamples,1);
after_h2=zeros(Nsamples,1);

flag=1;

for k=1:Nsamples
    
    [ax ay aVel aYawRate aStrAngs]=GetGPS();
    gpsSaved(k,:)=[ax ay];
    
    brforeH=calHeading(ax,ay,flag);
    before_h(k)=brforeH;
    flag=~flag;
    
    [x y]=GPSEKF(ax-f_utm_x,ay-f_utm_y,aVel,aYawRate,aStrAngs,dt);
    gpsEKFSaved(k,:)=[x+f_utm_x y+f_utm_y];
    
    afterH=calHeading(x+f_utm_x,y+f_utm_y,flag);
    after_h2(k)=afterH;
    flag=~flag;
end

ori_X=gpsSaved(:,1);
ori_Y=gpsSaved(:,2);

X=gpsEKFSaved(:,1);
Y=gpsEKFSaved(:,2);

figure(1);clf;
plot(ori_X,ori_Y);
grid on;box on;
xlabel('UTM latitude [m]');ylabel('UTM longitude [m]');
title('original UTM GPS data');


figure(2);clf;
plot(X,Y);
grid on;box on;
xlabel('UTM latitude [m]');ylabel('UTM longitude [m]');
title('AFTER EKF UTM GPS data');

figure(3);clf;
plot(ori_X,ori_Y,'Linewidth',1.5);hold on;
grid on;box on;
plot(X,Y);
xlabel('UTM latitude [m]');ylabel('UTM longitude [m]');
legend('original UTM GPS data','AFTER EKF UTM GPS data');

figure(4);clf;
plot(unwrap(before_h+2*pi)*180/pi,'r','Linewidth',1.3);hold on;
plot(unwrap(after_h2)*180/pi,'g','Linewidth',1.3);
grid on;box on;
xlabel('Samples [20Hz]');ylabel('GPS heading angle [deg]');
axis([0 14000 0 700]);
legend('before EKF heading','After EKF heading');
title('left turn -deg, right turn + deg');
title('original UTM GPS data');