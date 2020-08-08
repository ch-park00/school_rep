Fs=1000;Ts=1/1000;
x=[ones(1,1000) -ones(1,1000) zeros(1,2000)];
x1=[linspace(0,1,Fs) linspace(1,0,Fs) zeros(1,2000)];
t=linspace(0,4,4*Fs);
y=conv(x,x1)*Ts;
plot(t,y(1,1:length(t)))

%% m=5,v=4/3
x=4*rand(10000,1)+3;
mean(x)
var(x)

%%
n=60;
d=randi(10,n,1);
c=cumsum(d);
H=100;
W=c(end);
G=zeros(H,W,'uint8');
G(:,1:c(1))=randi(256)-1;
for k=2:n
   G(:,c(k-1)-1:c(k))=randi(256)-1; 
end
imshow(G)

%%
for i=1:1:10000
x1=randn(100,1);
y1=randn(100,1);
x=cumsum(x1);y=cumsum(y1);
r(i)=sqrt(x(100,1)^2+y(100,1)^2);
end
histogram(r,'Normalization','pdf')


%%
x=[linspace(-0.5,0.5,1000) linspace(-0.5,0.5,1000) linspace(-0.5,0.5,1000)];
Fs=1000;Ts=1/Fs;
t=linspace(0,3,Fs*3);
c=cos(2*pi*4*t);
c_signal=c.*x;
plot(t,c_signal);hold on
plot(t,x);grid;axis([0 3 -1.5 1.5])
%%
x=[linspace(-0.5,0.5,1000) linspace(-0.5,0.5,1000) linspace(-0.5,0.5,1000)];
Fs=1000;Ts=1/Fs;
t=linspace(0,3,Fs*3);
c=1/2*cos(2*pi*4*t);
mn=x/max(abs(x));
c1=(1+mn).*c;
hold on;grid on;
plot(t,x);axis([0 3 -3 3])
plot(t,c1)

%%
Fs=48000;Ts=1/Fs;
t=linspace(-1,1,Fs*2);
r=sqrt((4000^2)*(1-t.^2));
p=cumsum(r)*Ts;
c=cos(2*pi*8000*t+2*pi*p);
c1=cos(2*pi*8000*t-2*pi*p);
t1=linspace(0,1,Fs);
c2=cos(2*pi*8000*t1);
x=[2*c2 c1+c 2*c2];
spectrogram(x,256,128,256,Fs,'yaxis')

%%
t=linspace(-1,1,2000);
r=1;
y=sqrt(1-t.^2);
x=[zeros(1,1000) y zeros(1,1000)];
x2=linspace(0,4,4000);
plot(x2,x);axis([-1 4 -3 3])

%%

t=linspace(0,2*pi/5,1000);
v1=18*sqrt(2)*sin(5*t);
v2=8*sqrt(2)*cos(60*t+pi/4);
v=v1+v2;
plot(t,v1,'r');hold on;
plot(t,v2,'b');plot(t,v,'k','linewidth',2)
