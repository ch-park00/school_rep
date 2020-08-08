t1=linspace(-1,1,1000);
t=linspace(-0.15,0.15,3000);
x=[t1 t1 t1]; %Åé´ÏÆÄ(saw tooth wave)
Ts=1/10000;
c=cos(200*pi*t);
xfm = cos(2*pi*100*t + 2*pi*100*cumtrapz(x)*Ts);
figure(1);plot(t,x);
figure(2);plot(t,xfm)
