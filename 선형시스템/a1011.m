%% 
A=[cos(pi/3) -sin(pi/3) 0;sin(pi/3) cos(pi/3) 0;0 0 1];
x=[3;2;1];
y=A*x;
A1=[cos(pi/3) -sin(pi/3);sin(pi/3) cos(pi/3)];
x1=[3;2];
y1=A1*x1;

%%
x=[3;2;1];
A=[1 0 5;0 1 -5;0 0 1];
A1=[cos(pi/3) -sin(pi/3) 0;sin(pi/3) cos(pi/3) 0;0 0 1];
y=A*A1*x;

%%
clear all;close all;
th=pi/3;phi=pi/2;psi=pi/6;
x=[0;0;5];
Rx=[1 0 0;0 cos(th) -sin(th);0 sin(th) cos(th)];
Ry=[cos(phi) 0 sin(phi);0 1 0;-sin(phi) 0 cos(phi)];
Rz=[cos(psi) -sin(psi) 0;sin(psi) cos(psi) 0;0 0 1];
y1=Ry*x;


%%

figure;clf;
plot3([0 x(1)],[0 x(2)],[0 x(3)],'o-');grid;hold on
plot3([0 y1(1)],[0 y1(2)],[0 y1(3)],'*-');axis([-10 10 -10 10 -10 10])
xlabel('x1 axis');ylabel('x2 axis');zlabel('x3 axis');view([0 -90 0])