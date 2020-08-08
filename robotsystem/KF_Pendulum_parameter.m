Ts=0.01;
g=9.81;
m=1;
l=0.5;
A=[0 1;-g/l 0];
B=[0; 1/(m*l^2)];
C=[1 0];
D=0;
Q=1e-3;
R=1e-4;

%theta_0=pi/16;
theta_0=pi/2;
theta_dot_0=0;
x1_init=pi/16;