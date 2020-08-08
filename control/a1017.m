%%
clear;close all;
% ms^2 +cs + k = 0
% s^2 + 2s+ 17 = 0
m=1;c=2;k=17;
wn=sqrt(k/m);
cc=2*sqrt(m*k);
zeta=c/cc;
root_sys1=(-c+sqrt(c^2-4*m*k))/(2*m);
root_sys2=(-c-sqrt(c^2-4*m*k))/(2*m);
wd=wn*sqrt(1-zeta^2);

t=0:0.001:5;
c_t=1-exp(-zeta*wn*t).*(cos(wd*t)+zeta/sqrt(1-zeta^2).*sin(wd*t));
figure(1);clf;plot(t,c_t);grid
xlabel('Time (s)'),ylabel('c(t)');

figure(2);clf;
plot(real(root_sys1),imag(root_sys1),'x');hold on;
plot(real(root_sys2),imag(root_sys2),'x');hold on;
axis([-5 2 -5 5]);grid on;xlabel('real'),ylabel('Imag');
%%
zeta_all=[0 0.1 0.5 0.7 0.9 1];
color_all=['r','k','g','m','c','r'];
x_all=['rx','kx','gx','mx','cx','rx'];
c=cc*zeta_all;
root_sys1_all=(-c+sqrt(c.^2-4*m*k))/(2*m);
root_sys2_all=(-c-sqrt(c.^2-4*m*k))/(2*m);
wd_all=wn*sqrt(1-zeta_all.^2);

for i=1:length(zeta_all)
   zeta=zeta_all(i);
   wd=wd_all(i);
   root_sys1=root_sys1_all(i);
   root_sys2=root_sys2_all(i);
   color_c=color_all(i);
   x_c=x_all(2*i-1:2*i);
   if i==length(zeta_all)
      c_t_zeta_d=1-exp(-zeta*wn*t).*(cos(wd*t)+wn.*t);
   else
      c_t_zeta=1-exp(-zeta*wn*t).*(cos(wd*t)+zeta/sqrt(1-zeta^2).*sin(wd*t));
   end
  figure(1);hold on;plot(t,c_t_zeta,color_c);
  figure(2);hold on;plot(real(root_sys1),imag(root_sys1),x_c);
            hold on;plot(real(root_sys2),imag(root_sys2),x_c);
end

%%
clear;close all;
dt=0.01;t=0:dt:10;
[imp]=impulse(tf([2 10],[1 5 4]),t);
r=ones(1,length(t));
y=conv(r,imp)*dt;

figure(1);clf;
plot(t,imp);
hold on;plot(t,r,'r');
plot(t,y(1:length(t)),'k','Linewidth',2);
xlabel('Time (s)');
ylabel('g(t), r(t), y(t)');

%%
clear;close all;
dt=0.01;t=0:dt:10;
[imp]=impulse(tf([0 0 1],[1 1 1]),t);
r=t;
y=conv(r,imp)*dt;

figure(1);clf;
plot(t,imp);
hold on;plot(t,r,'r');
plot(t,y(1:length(t)),'k','Linewidth',2);
xlabel('Time (s)');
ylabel('g(t), r(t), y(t)');

%%
clear;close all;
dt=0.01;t=0:dt:10;
[imp]=impulse(tf([0 2],[1 3]),t);
r=exp(-t);
y=conv(r,imp)*dt;

figure(1);clf;
plot(t,imp);
hold on;plot(t,r,'r');
plot(t,y(1:length(t)),'k','Linewidth',2);
xlabel('Time (s)');
ylabel('g(t), r(t), y(t)');

%%
clear;close all;
dt=0.01;t=0:dt:10;
[imp]=impulse(tf([0 2],[1 3]),t);
r=square(1.5*t);
y=conv(r,imp)*dt;

figure(1);clf;
plot(t,imp);
hold on;plot(t,r,'r');
plot(t,y(1:length(t)),'k','Linewidth',2);
xlabel('Time (s)');
ylabel('g(t), r(t), y(t)');

%%
clear;close all;
dt=0.01;t=0:dt:10;
[imp]=impulse(tf([0 17],[1 2 17]),t);
r=exp(-t);
y=conv(r,imp)*dt;

figure(1);clf;
plot(t,imp);
hold on;plot(t,r,'r');
plot(t,y(1:length(t)),'k','Linewidth',2);
axis([0 10 -1.5 3]);
xlabel('Time (s)');
ylabel('g(t), r(t), y(t)');

figure(2);clf;
plot(t,r,'r:');hold on;
plot(t,y(1:length(t)));
axis([0 10 -1.5 3]);
xlabel('Time (s)');
ylabel('g(t), r(t), y(t)');

%%
clear;close all;
dt=0.01;t=0:dt:10;
[imp]=impulse(tf([0 17],[1 2 17]),t);
r=square(0.5*t);
y=conv(r,imp)*dt;

figure(1);clf;
plot(t,imp);
hold on;plot(t,r,'r');
plot(t,y(1:length(t)),'k','Linewidth',2);
axis([0 10 -1.5 3]);
xlabel('Time (s)');
ylabel('g(t), r(t), y(t)');

figure(2);clf;
plot(t,r,'r:');hold on;
plot(t,y(1:length(t)));
axis([0 10 -1.5 3]);
xlabel('Time (s)');
ylabel('g(t), r(t), y(t)');


%%
clear;close all;
dt=0.01;t=0:dt:10;
[imp]=impulse(tf([0 17],[1 2 17]),t);
r=sin(2*t);
y=conv(r,imp)*dt;

figure(1);clf;
plot(t,imp);
hold on;plot(t,r,'r');
plot(t,y(1:length(t)),'k','Linewidth',2);
axis([0 10 -1.5 3]);
xlabel('Time (s)');
ylabel('g(t), r(t), y(t)');

figure(2);clf;
plot(t,r,'r:');hold on;
plot(t,y(1:length(t)));
axis([0 10 -1.5 3]);
xlabel('Time (s)');
ylabel('g(t), r(t), y(t)');

%%
clear;close all;
dt=0.01;t=0:dt:10;
[imp]=impulse(tf([0 17],[1 2 17]),t);
r=randn(1,length(t));
y=conv(r,imp)*dt;

figure(1);clf;
plot(t,imp,'Linewidth',2);
hold on;plot(t,r,'r');
axis([0 10 -1.5 3]);
xlabel('Time (s)');
ylabel('g(t), r(t), y(t)');

figure(2);clf;
plot(t,r,'r:');hold on;
plot(t,y(1:length(t)));
axis([0 10 -1.5 3]);
xlabel('Time (s)');
ylabel('g(t), r(t), y(t)');