
%%
x3=[0 1 1 1 1 1 1 4 4 4 7 7 7 7 7 7 8 8 8 8 8 8 7 7 7 4 4 4 1 1 1 0 0 0 0 0 1 1 4 7 7 8 8 7 4 1 0 0;...
    0 0 0 0 6 6 6 0 0 0 6 6 6 0 0 0 0 0 0 8 8 8 8 8 8 2 2 2 8 8 8 8 8 8 0 0 0 6 0 6 0 0 8 8 2 8 8 0;...
    0 0 1 0 0 1 0 0 1 0 0 1 0 0 1 0 0 1 0 0 1 0 0 1 0 0 1 0 0 1 0 0 1 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1;
    1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1];
%% 과제 5
for the=0:0.05:pi 
   Rx=[1 0 0 0;0 cos(the) -sin(the) 0;0 sin(the) cos(the) 0;0 0 0 1];
   y3=Rx*x3;
   clf;
   line(y3(1,:),y3(2,:),y3(3,:));xlabel('x1 axis');ylabel('x2 axis');zlabel('x3 axis');
   axis([-10 10 -10 10 -10 10]);grid on;
   pause(0.0001);
end
for phi=0:0.05:pi
   Ry=[cos(phi) 0 sin(phi) 0;0 1 0 0;-sin(phi) 0 cos(phi) 0;0 0 0 1];
   yy=Ry*x3;
   clf;
   line(yy(1,:),yy(2,:),yy(3,:));xlabel('x1 axis');ylabel('x2 axis');zlabel('x3 axis');
   axis([-10 10 -10 10 -10 10]);grid on;
   pause(0.0001);
end
for psi=0:0.05:pi
   Rz=[cos(psi) -sin(psi) 0 0;sin(psi) cos(psi) 0 0;0 0 1 0;0 0 0 1];
   yyy=Rz*x3;
   clf;
   line(yyy(1,:),yyy(2,:),yyy(3,:));xlabel('x1 axis');ylabel('x2 axis');zlabel('x3 axis');
   axis([-10 10 -10 10 -10 10]);grid on;
   pause(0.0001);
end
%% 과제 6
figure(5);
for th=0:0.01:pi
    clf;
    Rz=[cos(th) -sin(th) 0 0;sin(th) cos(th) 0 0;0 0 1 0;0 0 0 1];
    Ry=[cos(th) 0 sin(th) 0;0 1 0 0;-sin(th) 0 cos(th) 0;0 0 0 1];
    Rx=[1 0 0 0;0 cos(th) -sin(th) 0;0 sin(th) cos(th) 0;0 0 0 1];
    y=Rx*Ry*Rz*x3;
    line(y(1,:),y(2,:),y(3,:));axis([-10 10 -10 10 -10 10]);
    grid;
    pause(0.0001);
end

%% 과제 7
t=x3;
while(mean(t(:,3))>=-7)
  x=0.1*rand(1,4)-0.05;
  z=0.35*rand(1,1);
  th=7*rand(1,3)-3.5;
  th=th/180*pi;
  T1=[1 0 0 x(1);0 1 0 x(2);0 0 1 -z+x(1,3);0 0 0 1];
  Rz=[cos(th(1)) -sin(th(1)) 0 0;sin(th(1)) cos(th(1)) 0 0;0 0 1 0;0 0 0 1];
  Ry=[cos(th(2)) 0 sin(th(2)) 0;0 1 0 0;-sin(th(2)) 0 cos(th(2)) 0;0 0 0 1];
  Rx=[1 0 0 0;0 cos(th(3)) -sin(th(3)) 0;0 sin(th(3)) cos(th(3)) 0;0 0 0 1];
  t=Rx*Ry*Rz*T1*t;clf;
  line(t(1,:),t(2,:),t(3,:));axis([-40 40 -40 40 -40 40]);
  grid;xlabel('x1 axis');ylabel('x2 axis');zlabel('x3 axis');
  pause(0.000001);
end

