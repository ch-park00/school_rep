%%
function [out_x out_y]=GPSEKF(ax,ay,aVel,aYawRate,aStrAngs,dt)
persistent H Q R x P
persistent v_ beta_ gam_ yaw_ x_ y_
persistent firstrun
if isempty(firstrun)
    H=[0 0 1 0 0 0;0 0 0 0 1 0;
        0 0 0 0 0 1];
    Q=[1 0 0 0 0 0;0 1 0 0 0 0;
        0 0 1 0 0 0;0 0 0 0.1 0 0;
        0 0 0 0 1 0;0 0 0 0 0 1];
    R=[0.1 0 0;0 20 0;0 0 20];
    x=[0 0 0 0 0 0]';
    P=eye(6,6);
    v_=0;
    beta_=0;
    gam_=0;
    yaw_=0;
    x_=0;
    y_=0;
    firstrun=1;
end
str_angle=aStrAngs*pi/180;
v_=aVel/3.6;
aYawRate=(aYawRate+0.4780)*pi/180;
A=Ajacob1(x,dt,v_,str_angle);
lf=2.650;lr=0.0;
beta_=atan2((lf+lr),lr*tan(str_angle));
gam_=(x(1)*cos(x(2))*tan(str_angle)/(lf+lr));
yaw_=x(4)+dt*x(3);
x_=x(5)+dt*x(1)*cos((x(4)+x(2))+(x(3)*dt/2));
y_=x(6)+dt*x(1)*sin((x(4)+x(2))+(x(3)*dt/2));
xp=[v_,beta_,gam_,yaw_,x_,y_]';
Pp=A*P*A'+Q;
K=Pp*H'*inv(H*Pp*H'+R);
z(1)=aYawRate;
z(2)=ax;
z(3)=ay;

x=xp+K*(z'-H*xp);
P=Pp-K*H*Pp;

out_x=x(5);
out_y=x(6);
end
