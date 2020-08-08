%%
Fs=100;
t=linspace(-3,3,6*Fs);
t1=linspace(0,1/2,Fs);
k=[zeros(1,Fs/2) sin(2*pi*t1) zeros(1,Fs/2)];
x=[k k k];
c=cos(2*pi*4*t);
temp=x/max(abs(x));
am=(1+temp).*c;
figure(1),plot(t,x)

hold on;plot(t,am);grid on;

%%
Fs=1000;
t=linspace(-5,5,10*Fs);
t1=linspace(0,1,Fs);
x=[zeros(1,Fs/2) sin(2*pi*1/2*t1) zeros(1,Fs/2)];
s=[x x x x x];
plot(t,s)
xn=fft(s)/length(s);
n=-5000:4999;
stem(n,fftshift(abs(xn)));xlim([-10 10])

p=xn(1);
for k=2:35
   p=(p+xn(k)*exp(2i*pi*(k-1)/10*t))+(xn(10000-k+2)*exp(-2i*pi*(k-1)/10*t)); 
end
plot(t,p)

%%
load fmsignal.mat;
Ts=1/Fs;
t=(0:1:length(xfm)-1)/fc;
c=cos(2*pi*fc*t);
s=sin(2*pi*fc*t);
r=xfm.*c;
r1=-xfm.*s;
r2=filter(r,1,h);
r3=filter(r1,1,h);
p=atan2(r2,r3);
q=unwrap(p);
mr=diff(q)/(2*pi*Ts);
%%

n=randn(10^5,1);
d=0:0.5:4;

for i=1:9
    cnt(i)=0;
    for j=1:10^5
        x(j)=d(i)+n(j);
        if x(j)<0
            cnt(i)=cnt(i)+1;
        end
    end
    p(i)=cnt(i)/(10^5);
end
semilogy(d,p,'o-');