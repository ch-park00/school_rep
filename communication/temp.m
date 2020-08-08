%%
[m,Fs]=audioread('hello.mp4');Ts=1/Fs;
fc=8000;N=length(m);
t=(0:N-1)*(1/Fs);
mn=m/max(abs(m));
c=cos(2*pi*fc*t)';
x=(1+mn).*c;


figure(1);plot(t,m,'b');xlabel('time $t$ (sec)','Interpreter','Latex');
figure(2);spectrogram(m(:,1),512,256,512,Fs,'yaxis');
figure(3);plot(t,x,'b');xlabel('time $t$ (sec)','Interpreter','Latex');
figure(4);spectrogram(x(:,1),512,256,512,Fs,'yaxis');
%%
y=x.*c;
y1=filter(h,1,y);
Dc=mean(y1);
mh=y1-Dc;
mh(1:length(h),1)=0;

mrc=mh/max(abs(mh));
figure(5);plot(t,mrc);
figure(6);spectrogram(mrc(:,1),512,256,512,Fs,'yaxis');

sound(y,Fs);pause(5);
sound(mrc,Fs);
%%
y2=zeros(size(x));

y2(x>0)=x(x>0);
T=1/8000;
tau=100/(2*pi*4000);
hRc=0.05*exp(-(0:Ts:(40*tau))/tau);
y3=filter(hRc,1,y2);
Dc=mean(y3(500:20000));
mh=y3-Dc;
mh(1:length(hRc))=0;
mrn=mh/max(abs(mh));

figure(7);plot(t,mrn,'b');hold on;
plot(t,m,'r');xlabel('time $t$ (sec)','Interpreter','Latex');legend('비동기 신호','원래 신호')
figure(8);spectrogram(mrn(:,1),512,256,512,Fs,'yaxis');
sound(mrn,Fs);